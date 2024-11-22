OP_CODES = {
    "add": 0x01,
    "multiply": 0x02,
    "power": 0x03,
}

DEVICE_PATH = "/dev/virtual_device"

def isa_encode(operation, a, b):
    """고수준 API를 ISA 명령어로 변환"""
    if operation not in OP_CODES:
        raise ValueError(f"Unsupported operation: {operation}")
    op_code = OP_CODES[operation]
    return f"{op_code} {a} {b}"

def execute_operation(a, b, operation):
    """ISA 명령어 생성 및 디바이스 통신"""
    isa_command = isa_encode(operation, a, b)
    with open(DEVICE_PATH, 'w') as device_file:
        device_file.write(isa_command)
    with open(DEVICE_PATH, 'r') as device_file:
        return device_file.read()
