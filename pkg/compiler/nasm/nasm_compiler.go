package nasm

import (
	"fmt"
	"strings"

	"github.com/VzoelFox/morph/pkg/checker"
	"github.com/VzoelFox/morph/pkg/parser"
)

type NASMCompiler struct {
	output     strings.Builder
	data       strings.Builder
	text       strings.Builder
	checker    *checker.Checker
	entryBody  strings.Builder
	
	// Track string literals to deduplicate
	stringMap  map[string]string
	stringID   int
	
	// Label generation
	labelID    int

	// Variable tracking (simple stack allocator)
	// Map identifier name -> stack offset (negative from RBP)
	varMap     map[string]int
	currentOffset int
	
	// Struct definitions
	// Map struct name -> (size, map[field_name]offset)
	structs    map[string]structInfo
	
	// Global variables (name -> label)
	globals    map[string]string
	
	inFunction bool
}

type structInfo struct {
	size   int
	fields map[string]int
}

func New(c *checker.Checker) *NASMCompiler {
	return &NASMCompiler{
		checker:   c,
		stringMap: make(map[string]string),
		varMap:    make(map[string]int),
		structs:   make(map[string]structInfo),
		globals:   make(map[string]string),
	}
}

func (c *NASMCompiler) nextLabel(prefix string) string {
	c.labelID++
	return fmt.Sprintf(".%s_%d", prefix, c.labelID)
}

func (c *NASMCompiler) Compile(node parser.Node) (string, error) {
	// Magic Header in Data Section
	// "V Z O E L F O XS" -> 16 bytes
	c.data.WriteString("section .data\n")
	c.data.WriteString("    magic_header db \"V Z O E L F O XS\"\n") 

	// Standard text section
	c.text.WriteString("section .text\n")
	c.text.WriteString("    global _start\n\n")
	
	// Pre-compile program to gather functions
	if prog, ok := node.(*parser.Program); ok {
		if err := c.compileProgram(prog); err != nil {
			return "", err
		}
	} else {
		return "", fmt.Errorf("expected *parser.Program, got %T", node)
	}
	
	// Create _start entry point that calls main
	c.text.WriteString("_start:\n")
	c.text.WriteString("    ; Initialize stack frame\n")
	c.text.WriteString("    mov rbp, rsp\n\n")

	// Global Init
	c.text.WriteString("    ; Global Init\n")
	c.text.WriteString(c.entryBody.String())
	c.text.WriteString("\n")
	
	c.text.WriteString("    ; Call main\n")
	c.text.WriteString("    call main\n\n")

	// Exit syscall (default)
	c.text.WriteString("    ; Default exit\n")
	c.text.WriteString("    mov rax, 60         ; sys_exit\n")
	c.text.WriteString("    xor rdi, rdi        ; status 0\n")
	c.text.WriteString("    syscall\n")

	// Helper functions (print, etc)
	c.appendHelpers()

	// Combine
	c.output.WriteString(c.data.String())
	c.output.WriteString("\n")
	c.output.WriteString(c.text.String())
	
	return c.output.String(), nil
}

func (c *NASMCompiler) compileProgram(prog *parser.Program) error {
	for _, stmt := range prog.Statements {
		if err := c.compileStatement(stmt); err != nil {
			return err
		}
	}
	return nil
}

func (c *NASMCompiler) compileStatement(stmt parser.Statement) error {
	switch s := stmt.(type) {
	case *parser.ExpressionStatement:
		return c.compileExpression(s.Expression)
	case *parser.VarStatement:
		return c.compileVarStatement(s)
	case *parser.StructStatement:
		return c.compileStructStatement(s)
	case *parser.ReturnStatement:
		return c.compileReturn(s)
	default:
		// Ignore others for now
		return nil
	}
}

func (c *NASMCompiler) compileVarStatement(stmt *parser.VarStatement) error {
	if !c.inFunction {
		// Global variable
		for i, name := range stmt.Names {
			label := name.Value
			c.globals[name.Value] = label
			c.data.WriteString(fmt.Sprintf("    global %s\n", label))
			c.data.WriteString(fmt.Sprintf("    %s dq 0\n", label))
			
			// If there's an initialization, we need a .init section or do it in _start?
			// For now, only support initialization if it's constant literal?
			// Or generate code in _start to init globals.
			if i < len(stmt.Values) {
				// Initialize string literals in global
				if strLit, ok := stmt.Values[i].(*parser.StringLiteral); ok {
					// Define string constant
					strLabel := c.addStringConstant(strLit.Value)
					// Redefine global to point to it (requires overwriting previous 'dq 0')
					// Since we are writing to strings.Builder, we can't easily overwrite.
					// But we can just emit code in _start to init it.
					
					// HACK: Append to a buffer for _start initialization
					c.entryBody.WriteString(fmt.Sprintf("    mov rax, %s\n", strLabel))
					c.entryBody.WriteString(fmt.Sprintf("    mov [%s], rax\n", label))
				}
			}
		}
		return nil
	}

	// For each variable in the statement: var x, y = 1, 2
	for i, name := range stmt.Names {
		// 1. Compile value expression
		if i < len(stmt.Values) {
			if err := c.compileExpression(stmt.Values[i]); err != nil {
				return err
			}
		} else {
			// Default value (0 or nil)
			c.text.WriteString("    xor rax, rax\n")
		}
		
		// 2. Allocate stack space
		c.currentOffset += 8 // Assume 64-bit for everything for now
		c.varMap[name.Value] = c.currentOffset
		
		// 3. Store result (rax) to stack
		c.text.WriteString(fmt.Sprintf("    ; var %s\n", name.Value))
		c.text.WriteString(fmt.Sprintf("    mov [rbp - %d], rax\n", c.currentOffset))
		
		c.text.WriteString("    sub rsp, 8\n")
	}
	return nil
}

func (c *NASMCompiler) compileExpression(expr parser.Expression) error {
	switch e := expr.(type) {
	case *parser.CallExpression:
		return c.compileCall(e)
	case *parser.FunctionLiteral:
		return c.compileFunction(e)
	case *parser.StringLiteral:
		label := c.addStringConstant(e.Value)
		c.text.WriteString(fmt.Sprintf("    mov rax, %s\n", label))
		return nil
	case *parser.Identifier:
		return c.compileIdentifier(e)
	case *parser.InfixExpression:
		return c.compileInfixExpression(e)
	case *parser.IntegerLiteral:
		c.text.WriteString(fmt.Sprintf("    mov rax, %d\n", e.Value))
		return nil
	case *parser.IfExpression:
		return c.compileIfExpression(e)
	case *parser.StructLiteral:
		return c.compileStructLiteral(e)
	case *parser.MemberExpression:
		return c.compileMemberExpression(e)
	}
	return nil
}

func (c *NASMCompiler) compileStructStatement(stmt *parser.StructStatement) error {
	// Calculate offsets
	// Assume 8 bytes per field for now (all 64-bit pointers/ints)
	info := structInfo{
		fields: make(map[string]int),
	}
	
	offset := 0
	for _, field := range stmt.Fields {
		info.fields[field.Name] = offset
		offset += 8 // Size of field
	}
	info.size = offset
	
	c.structs[stmt.Name.Value] = info
	return nil
}

func (c *NASMCompiler) compileStructLiteral(sl *parser.StructLiteral) error {
	// 1. Get Struct Info
	name := sl.Name.(*parser.Identifier).Value
	info, ok := c.structs[name]
	if !ok {
		return fmt.Errorf("unknown struct: %s", name)
	}
	
	// 2. Allocate space on stack (size bytes)
	// We want to return a pointer to this space in RAX
	c.currentOffset += info.size
	baseOffset := c.currentOffset
	
	// Sub stack pointer (alloc)
	c.text.WriteString(fmt.Sprintf("    sub rsp, %d\n", info.size))
	
	// 3. Fill fields
	for fieldName, expr := range sl.Fields {
		fieldOffset, ok := info.fields[fieldName]
		if !ok {
			return fmt.Errorf("unknown field: %s", fieldName)
		}
		
		// Compile expression -> RAX
		if err := c.compileExpression(expr); err != nil {
			return err
		}
		
		// Store RAX -> [rbp - baseOffset + fieldOffset]
		target := baseOffset - fieldOffset
		c.text.WriteString(fmt.Sprintf("    mov [rbp - %d], rax ; field %s\n", target, fieldName))
	}
	
	// 4. Return pointer to struct (the bottom address, which is the first field)
	// Address is RBP - baseOffset
	c.text.WriteString(fmt.Sprintf("    lea rax, [rbp - %d]\n", baseOffset))
	
	return nil
}

func (c *NASMCompiler) compileMemberExpression(mem *parser.MemberExpression) error {
	// 1. Compile Object (should return pointer in RAX)
	if err := c.compileExpression(mem.Object); err != nil {
		return err
	}
	
	// Assume object is struct pointer in RAX.
	// Find offset. HACK: Global search for field name
	fieldName := mem.Member.Value
	offset := -1
	
	for _, s := range c.structs {
		if off, ok := s.fields[fieldName]; ok {
			offset = off
			break
		}
	}
	
	if offset == -1 {
		return fmt.Errorf("unknown field: %s", fieldName)
	}
	
	// Field is at [RAX + offset]
	c.text.WriteString(fmt.Sprintf("    mov rax, [rax + %d] ; load field %s\n", offset, fieldName))
	
	return nil
}

func (c *NASMCompiler) compileIfExpression(ie *parser.IfExpression) error {
	elseLabel := c.nextLabel("else")
	endLabel := c.nextLabel("end")
	
	// 1. Compile Condition
	if err := c.compileExpression(ie.Condition); err != nil {
		return err
	}
	
	// 2. Check condition (assuming rax has boolean/int result)
	c.text.WriteString("    cmp rax, 0\n")
	c.text.WriteString(fmt.Sprintf("    je %s\n", elseLabel))
	
	// 3. Compile Consequence
	if err := c.compileBlockStatement(ie.Consequence); err != nil {
		return err
	}
	c.text.WriteString(fmt.Sprintf("    jmp %s\n", endLabel))
	
	// 4. Else Label
	c.text.WriteString(fmt.Sprintf("%s:\n", elseLabel))
	
	// 5. Compile Alternative (Else)
	if ie.Alternative != nil {
		if err := c.compileBlockStatement(ie.Alternative); err != nil {
			return err
		}
	} else {
		// Handle ElseIfs if any (Not implemented fully yet, usually ElseIfs are syntactic sugar or nested)
		// Assuming simple if-else for now
	}
	
	// 6. End Label
	c.text.WriteString(fmt.Sprintf("%s:\n", endLabel))
	
	return nil
}

func (c *NASMCompiler) compileBlockStatement(block *parser.BlockStatement) error {
	for _, stmt := range block.Statements {
		if err := c.compileStatement(stmt); err != nil {
			return err
		}
	}
	return nil
}

func (c *NASMCompiler) compileInfixExpression(infix *parser.InfixExpression) error {
	// Compile Left
	if err := c.compileExpression(infix.Left); err != nil {
		return err
	}
	c.text.WriteString("    push rax\n")
	
	// Compile Right
	if err := c.compileExpression(infix.Right); err != nil {
		return err
	}
	c.text.WriteString("    mov rbx, rax\n")
	c.text.WriteString("    pop rax\n")
	
	switch infix.Operator {
	case "+":
		c.text.WriteString("    add rax, rbx\n")
	case "-":
		c.text.WriteString("    sub rax, rbx\n")
	case "*":
		c.text.WriteString("    imul rax, rbx\n")
	case "/":
		c.text.WriteString("    cqo\n") // sign extend rax to rdx:rax
		c.text.WriteString("    idiv rbx\n")
	// Comparisons
	case "==":
		c.compileComparison("e")
	case "!=":
		c.compileComparison("ne")
	case "<":
		c.compileComparison("l")
	case ">":
		c.compileComparison("g")
	case "<=":
		c.compileComparison("le")
	case ">=":
		c.compileComparison("ge")
	case "dan":
		// Logical AND
		c.text.WriteString("    and rax, rbx\n")
	case "atau":
		// Logical OR
		c.text.WriteString("    or rax, rbx\n")
	default:
		return fmt.Errorf("unknown operator: %s", infix.Operator)
	}
	
	return nil
}

func (c *NASMCompiler) compileComparison(cc string) {
	c.text.WriteString("    cmp rax, rbx\n")
	c.text.WriteString(fmt.Sprintf("    set%s al\n", cc))
	c.text.WriteString("    movzx rax, al\n")
}

func (c *NASMCompiler) compileIdentifier(ident *parser.Identifier) error {
	// 1. Look up in local vars (varMap)
	if offset, ok := c.varMap[ident.Value]; ok {
		c.text.WriteString(fmt.Sprintf("    ; load var %s\n", ident.Value))
		c.text.WriteString(fmt.Sprintf("    mov rax, [rbp - %d]\n", offset))
		return nil
	}
	
	// 2. Look up in globals
	if label, ok := c.globals[ident.Value]; ok {
		c.text.WriteString(fmt.Sprintf("    ; load global %s\n", ident.Value))
		c.text.WriteString(fmt.Sprintf("    mov rax, [%s]\n", label))
		return nil
	}
	
	return fmt.Errorf("undefined variable: %s", ident.Value)
}

func (c *NASMCompiler) compileFunction(fn *parser.FunctionLiteral) error {
	// If it has a name (e.g. main), make a label
	name := fn.Name
	if name == "" {
		// Anonymous function? Skip for now or generate temp name
		return nil
	}
	
	c.inFunction = true
	c.currentOffset = 0 // Reset stack for local vars
	c.text.WriteString(fmt.Sprintf("\n%s:\n", name))
	c.text.WriteString("    push rbp\n")
	c.text.WriteString("    mov rbp, rsp\n")
	
	// Handle parameters
	// Store registers to stack as local variables
	regs := []string{"rdi", "rsi", "rdx", "rcx", "r8", "r9"}
	for i, param := range fn.Parameters {
		if i < len(regs) {
			// Allocate stack space
			c.currentOffset += 8
			c.varMap[param.Name.Value] = c.currentOffset
			
			c.text.WriteString(fmt.Sprintf("    ; param %s\n", param.Name.Value))
			c.text.WriteString(fmt.Sprintf("    mov [rbp - %d], %s\n", c.currentOffset, regs[i]))
			c.text.WriteString("    sub rsp, 8\n")
		}
	}
	
	// Compile body
	if fn.Body != nil {
		for _, stmt := range fn.Body.Statements {
			if err := c.compileStatement(stmt); err != nil {
				return err
			}
		}
	}
	
	c.text.WriteString("    leave\n")
	c.text.WriteString("    ret\n")
	
	c.inFunction = false
	return nil
}

func (c *NASMCompiler) compileReturn(stmt *parser.ReturnStatement) error {
	// Only support single return value for now
	if len(stmt.ReturnValues) > 0 {
		if err := c.compileExpression(stmt.ReturnValues[0]); err != nil {
			return err
		}
	} else {
		c.text.WriteString("    xor rax, rax\n")
	}
	
	c.text.WriteString("    leave\n")
	c.text.WriteString("    ret\n")
	return nil
}

func (c *NASMCompiler) compileCall(call *parser.CallExpression) error {
	// Handle native calls specially
	// e.g., io.Write(io.Stdout, "Hello")
	
	// Check if it's a member expression like io.Write
	if mem, ok := call.Function.(*parser.MemberExpression); ok {
		if ident, ok := mem.Object.(*parser.Identifier); ok {
			if ident.Value == "io" && mem.Member.Value == "Write" {
				return c.compileIOWrite(call.Arguments)
			}
		}
	}
	
	// General function call
	// Calling convention: RDI, RSI, RDX, RCX, R8, R9
	regs := []string{"rdi", "rsi", "rdx", "rcx", "r8", "r9"}
	
	// Evaluate arguments (Left to right? or Right to left for stack?)
	// Register passing implies order doesn't matter for stack, but we must be careful not to overwrite registers needed for next arg calculation?
	// Safest: Calculate all args to stack, then pop to registers.
	
	for _, arg := range call.Arguments {
		if err := c.compileExpression(arg); err != nil {
			return err
		}
		c.text.WriteString("    push rax\n")
	}
	
	nArgs := len(call.Arguments)
	if nArgs > 6 {
		return fmt.Errorf("too many arguments (max 6 supported)")
	}
	
	for i := nArgs - 1; i >= 0; i-- {
		c.text.WriteString(fmt.Sprintf("    pop %s\n", regs[i]))
	}
	
	// Get function name
	var funcName string
	if ident, ok := call.Function.(*parser.Identifier); ok {
		funcName = ident.Value
	} else {
		return fmt.Errorf("indirect calls not supported yet")
	}
	
	c.text.WriteString(fmt.Sprintf("    call %s\n", funcName))
	return nil
}

func (c *NASMCompiler) compileIOWrite(args []parser.Expression) error {
	if len(args) < 2 {
		return fmt.Errorf("io.Write expects 2 arguments")
	}
	
	// Arg 1: File (Stdout is fd 1)
	// Arg 2: String
	
	// Compile Arg 2 (The string)
	// The result should be in RAX (pointer to string)
	if err := c.compileExpression(args[1]); err != nil {
		return err
	}
	
	// If it's a string literal, we can know the length statically
	// If it's a variable, we assume it's a null-terminated string or we need to find length
	// For now, let's assume we can handle string literals specially for length, 
	// and for variables we might need strlen (or just hardcode a length for POC)
	
	// Save RAX (string pointer) to RSI for syscall
	c.text.WriteString("    push rax\n")
	
	length := 0
	if strLit, ok := args[1].(*parser.StringLiteral); ok {
		length = len(strLit.Value)
		c.text.WriteString("    pop rsi\n")
		c.text.WriteString(fmt.Sprintf("    mov rdx, %d\n", length))
	} else {
		// It's a variable or expression.
		// We need to calculate length dynamically or assume fixed max
		// Implementing strlen loop in ASM
		c.text.WriteString("    pop rsi             ; string pointer\n")
		c.text.WriteString("    ; Calculate strlen\n")
		c.text.WriteString("    xor rdx, rdx\n")
		c.text.WriteString(".strlen_loop:\n")
		c.text.WriteString("    cmp byte [rsi + rdx], 0\n")
		c.text.WriteString("    je .strlen_done\n")
		c.text.WriteString("    inc rdx\n")
		c.text.WriteString("    jmp .strlen_loop\n")
		c.text.WriteString(".strlen_done:\n")
	}

	c.text.WriteString("    ; io.Write\n")
	c.text.WriteString("    mov rax, 1          ; sys_write\n")
	c.text.WriteString("    mov rdi, 1          ; fd 1 (stdout)\n")
	// RSI and RDX are already set above
	c.text.WriteString("    syscall\n")
	
	return nil
}

func (c *NASMCompiler) addStringConstant(s string) string {
	if label, exists := c.stringMap[s]; exists {
		return label
	}
	
	label := fmt.Sprintf("str_%d", c.stringID)
	c.stringID++
	c.stringMap[s] = label
	
	// Sanitize string for db? 
	// Escape newlines and other chars
	sEscaped := strings.ReplaceAll(s, "\n", "\", 10, \"")
	sEscaped = strings.ReplaceAll(sEscaped, "\r", "\", 13, \"")
	sEscaped = strings.ReplaceAll(sEscaped, "\t", "\", 9, \"")
	
	// If the string starts/ends with special char replacement, we might have empty quotes like "" at edges
	// NASM handles `db "", 10` fine.
	
	c.data.WriteString(fmt.Sprintf("    %s db \"%s\", 0\n", label, sEscaped))
	
	return label
}

func (c *NASMCompiler) appendHelpers() {
	// Add runtime helpers here if needed
}
