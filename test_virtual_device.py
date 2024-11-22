from device_runtime import execute_operation

# 테스트
print("5 + 3 =", execute_operation(5, 3, "add"))          # ISA: 0x01 5 3
print("2 * 4 =", execute_operation(2, 4, "multiply"))    # ISA: 0x02 2 4
print("2 ^ 10 =", execute_operation(2, 10, "power"))     # ISA: 0x03 2 10
