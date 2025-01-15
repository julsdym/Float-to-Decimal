import subprocess

FILE_NAME = "part3"

def compile_program():
	compile_result = subprocess.run(["gcc", "-fsanitize=address", FILE_NAME+".c", "-o", FILE_NAME,"-lm"], capture_output=True, text=True)
	if compile_result.returncode != 0:
		print("Compilation failed:", compile_result.stderr)
		return False
	return True

def run_test(test_number, test_input, expected_output):
    process = subprocess.Popen(["./"+FILE_NAME, *(test_input.split(' '))], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    stdout, stderr = process.communicate()

    print(f"Test Case {test_number}: Input = {test_input}, stderr: {stderr.strip()}, Output: {expected_output.strip()}", end=" ")

    if stdout.strip() == expected_output.strip() or stderr.strip() == expected_output.strip():
        print("✓ Passed")
        return True
    else:
        print("✗ Failed")
        print(f"   Expected Output: {expected_output.strip()}")
        print(f"   Actual Output: {stdout.strip() if stdout != '' else stderr.strip()}")
        return False

def main():
	if not compile_program():
		return

	test_cases = [
		(2, "101", "insert IEEE754 string with length >= 16"),
		(3,"0123456789ABCDEF0", "invalid binary format"),
		(4, "0000000000000000", "0.00000000"),
		(5, "0000001111111111", "0.00006098"),
        (6, "0111101000000000", "49152.00000000"),
        (7, "0111110000000000", "+infinity"),
        (8, "1111110000000000", "-infinity"),
        (9, "0111110100000000", "NaN")
	]

	all_passed = True
	for test_number, test_input, expected_output in test_cases:
		if not run_test(test_number, test_input, expected_output):
			all_passed = False

	if all_passed:
		print("All tests passed successfully!")
	else:
		print("Some tests failed.")

if __name__ == "__main__":
	main()
