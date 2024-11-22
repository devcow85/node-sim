# Node-Sim

`Node-Sim` is a virtual device simulation package designed to emulate device interactions and perform instruction-based computations. This package includes a Linux kernel module (`.ko`) to create a virtual device and provides Python runtime APIs to interact with it. It also supports running in a Docker environment for ease of use and portability.


## Features

- Virtual device creation and management using Linux kernel modules.
- ISA-based command transmission and processing.
- Python APIs for easy interaction with the virtual device.
- Docker support for isolated and reproducible environments.

## Installation
### 1. Download Source Code
Clone the repository and navigate to the project directory:
```bash
git clone https://github.com/devcow85/node-sim.git
cd node-sim
```
### 2. Compile Kernel Module
Run the `compile_module.sh` script to build the kernel module:
```bash
./compile_module.sh
```
### 3. Build and Run Docker
Execute the `docker_build_exec.sh` script to build the Docker image and start the container:
```bash
./docker_build_exec.sh
```

## Usage
### 1. Kernel Module Management (Inside Docker)
- Load the kernel module:
```bash
insmod /app/virtual_device.ko
```
- Check the device file:
```bash
ls /dev/virtual_device
```
- Unload the kernel module:
```bash
rmmod virtual_device
```

## Test (Python)
The package provides a Python API to interact with the virtual device. The following example demonstrates how to send commands to the virtual device and retrieve results:

```python
from device_runtime import execute_operation

# Perform addition
result = execute_operation(5, 3, "add")
print("5 + 3 =", result)

# Perform multiplication
result = execute_operation(2, 4, "multiply")
print("2 * 4 =", result)

# Perform power operation
result = execute_operation(2, 10, "power")
print("2 ^ 10 =", result)

```
Save the above code as test_virtual_device.py and execute it inside the container:

```bash
python3 test_virtual_device.py

# result
5 + 3 = 8
2 * 4 = 8
2 ^ 10 = 1024
```

## File Descriptions

### Scripts
- `compile_module.sh`: Automates the kernel module compilation process.
- `docker_build_exec.sh`: Builds the Docker image and runs the container.
### Source Code
- `virtual_device.c`: The Linux kernel module implementation for the virtual device.
- `device_runtime.py`: Python API for interacting with the virtual device.
- `test_virtual_device.py`: Python script for testing the virtual device.