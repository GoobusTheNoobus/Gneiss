# =============================================================
#
#                       G N E I S S
#
# =============================================================
#
# Gneiss is a toy programming language developed in C++20
#
# Gneiss is licenced under the MIT license
# Copyright (c) 2026  GoobusTheNoobus

import argparse
import subprocess
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
LEXER_DIR = SCRIPT_DIR / "lexer"
PARSER_DIR = SCRIPT_DIR / "parser"

# In case we add more
LEXER_ID = 0
PARSER_ID = 1


def run_test(executable: Path, input_file: Path, id: int) -> bool:
    expected_file = Path(str(input_file).replace(".gneiss", "_expected.txt"))

    result = subprocess.run(
        [executable, "--lexa" if id == LEXER_ID else "--syna", input_file],
        capture_output=True,
        text=True,
    )

    actual = result.stdout.strip()
    expected = expected_file.read_text().strip()

    if actual != expected:
        print(f"FAIL: {input_file.name}")
        print()
        print("Expected:")
        print(expected)
        print()
        print("Actual:")
        print(actual)
        return False

    print(f"PASS: {input_file.name}")
    return True


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("executable", type=Path)

    args = parser.parse_args()

    executable = args.executable

    if not executable.exists():
        print(f"Executable not found: {executable}")
        return 1

    lexer_tests = sorted(LEXER_DIR.glob("*.gneiss"))
    parser_tests = sorted(PARSER_DIR.glob("*.gneiss"))

    if not lexer_tests:
        print(f"No tests found in {LEXER_DIR}")
        return 1

    if not parser_tests:
        print(f"No tests found in {PARSER_DIR}")
        return 1

    passed = 0

    print("Running Lexer tests...")

    for test in lexer_tests:
        if run_test(executable, test, LEXER_ID):
            passed += 1
            print(f"Test {test} passed.")
        else:
            print(f"Test {test} failed.")
            return 1

    print("\nRunning Parser tests...")

    for test in parser_tests:
        if run_test(executable, test, PARSER_ID):
            passed += 1
            print(f"Test {test} passed.")
        else:
            print(f"Test {test} failed.")
            return 1

    print(f"\n{passed}/{len(lexer_tests + parser_tests)} tests passed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
