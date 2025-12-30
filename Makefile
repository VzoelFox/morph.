# Morph Build and Deploy Makefile
VPS_HOST = root@144.202.18.239
VPS_PASS = w{U6YsKM+Q9AaX2F
BUILD_DIR = /root/morph.
TIMEOUT = 60

.PHONY: build deploy clean

build:
	@echo "Building morph..."
	timeout $(TIMEOUT) go build -o morph~main ./cmd/morph || (echo "Build timeout after $(TIMEOUT)s" && exit 1)

deploy: build
	@echo "Deploying to VPS..."
	timeout $(TIMEOUT) sshpass -p '$(VPS_PASS)' scp -o StrictHostKeyChecking=no -o ConnectTimeout=30 morph~main $(VPS_HOST):$(BUILD_DIR)/ || (echo "Deploy timeout" && make clean && exit 1)
	timeout $(TIMEOUT) sshpass -p '$(VPS_PASS)' scp -o StrictHostKeyChecking=no -o ConnectTimeout=30 *.fox $(VPS_HOST):$(BUILD_DIR)/ || (echo "File sync timeout" && make clean && exit 1)
	@echo "Deployment complete!"
	@make clean

sync:
	@echo "Syncing all files to VPS..."
	timeout $(TIMEOUT) sshpass -p '$(VPS_PASS)' scp -r -o StrictHostKeyChecking=no -o ConnectTimeout=30 . $(VPS_HOST):$(BUILD_DIR)/ || (echo "Sync timeout" && exit 1)
	@echo "Sync complete!"

test-remote:
	@echo "Running tests on VPS..."
	timeout $(TIMEOUT) sshpass -p '$(VPS_PASS)' ssh -o StrictHostKeyChecking=no -o ConnectTimeout=30 $(VPS_HOST) "cd $(BUILD_DIR) && timeout 30 ./morph~main test.fox" || echo "Test timeout or failed"

clean:
	@echo "Cleaning build artifacts..."
	rm -f morph~main

install-deps:
	@echo "Installing sshpass if needed..."
	@which sshpass > /dev/null || (echo "Installing sshpass..." && apt-get update && apt-get install -y sshpass)
