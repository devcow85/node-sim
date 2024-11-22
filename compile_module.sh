#!/bin/bash

# 가상 디바이스 커널 모듈 컴파일
echo "Compiling the virtual device kernel module..."
make -C /lib/modules/$(uname -r)/build M=$(pwd) modules

# 커널 모듈 로드
echo "Loading the virtual device kernel module..."
insmod virtual_device.ko

# 디바이스 확인
echo "Checking for /dev/virtual_device..."
ls /dev/virtual_device || echo "Virtual device not found. Check the module."

echo "Setup complete. Ready to test."
