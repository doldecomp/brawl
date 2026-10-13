from sys import argv
from os import remove, walk
from os.path import exists, isdir, join
from json import loads, dumps
from subprocess import run, PIPE
from argparse import ArgumentParser

from src.elf import ELFFile, ELFSection
from src.stream import InputStream
from src.hasher import Hasher
from src.fixer import Fixer

# Can be overridden per unit test
DEFAULT_CC_ARCH = "GC"
DEFAULT_CC_VERSION = "3.0a5.2"
DEFAULT_CFLAGS = "-msgstyle gcc -lang c -enum int -inline auto -ipa file -Cpp_exceptions off -RTTI off -proc gekko -fp hard -I- -Iinclude -ir include/stl -ir include/revolution -nodefaults -w unused,missingreturn,err -requireprotos"
DEFAULT_OPT = "-O4,p"

AS = join("tools", "powerpc-eabi-as.exe")
ASFLAGS = "-mgekko -I tools/tester/include"

TESTS_DIR = "tests/"
CC_DIR = join("tools", "GC_WII_COMPILERS")

WIBO = ""


def make_obj(obj_file: str) -> str:
    """Generate unit test from a given object file
    """
    # Parse object file
    try:
        strm = InputStream.open_file(obj_file, InputStream.ENDIAN_BIG)
        elf = ELFFile(strm)
    except FileNotFoundError:
        print(f"[FATAL] Object file could not be opened: {obj_file}")
        return

    hasher = Hasher()
    test = {}
    # Hash code/data and output to JSON
    for sect in elf.all_sections():
        if not sect.is_code() and not sect.is_data():
            continue

        test[sect.name] = list()
        for sym in sect.all_symbols():
            digest = hasher.hash_symbol(sym)
            if digest != None:
                test[sect.name].append([sym.name, digest.hex()])

    return dumps(test, indent=4)


def make_asm(asm_file: str) -> str:
    """Generate unit test from a given assembly file
    """
    # Fixup assembly for tester
    fx = Fixer()
    with open(asm_file, "r") as f:
        asm = f.readlines()
    asm = fx.fix(asm)
    # Write to temp file
    with open("temp_asm.s", "w+") as f:
        f.writelines(asm)

    # Assemble temp file
    cmd = f"{AS} {ASFLAGS} -o temp_asm.o temp_asm.s"
    result = run(cmd, shell=True, stdout=PIPE,
                 stderr=PIPE, universal_newlines=True)
    if result.returncode != 0:
        print("[FATAL] Assembler threw an error:")
        print(result.returncode, result.stdout, result.stderr)
        return

    # Hand off object to make_obj
    test_data = make_obj("temp_asm.o")

    # Delete temp files
    if exists("temp_asm.s"):
        remove("temp_asm.s")
    if exists("temp_asm.o"):
        remove("temp_asm.o")

    return test_data


def run_test(test_file: str) -> bool:
    """Run unit test file
    Only returns True if ALL cases pass
    """

    # Open unit test file
    try:
        with open(test_file, "rb") as f:
            test_json = loads(f.read())
    except FileNotFoundError:
        print(f"[FATAL] Unit test could not be opened: {test_file}")
        return
    except UnicodeDecodeError:
        print(f"[FATAL] JSON data could not be decoded. {test_file}")
        return

    # TU-specific compiler/flags overrides
    cc_arch = DEFAULT_CC_ARCH
    cc_ver = DEFAULT_CC_VERSION
    cflags = DEFAULT_CFLAGS
    opt = DEFAULT_OPT
    if "CC_ARCH" in test_json:
        cc_arch = test_json["CC_ARCH"]
    if "CC_VERSION" in test_json:
        cc_ver = test_json["CC_VERSION"]
    if "CFLAGS" in test_json:
        cflags = test_json["CFLAGS"]
    if "OPT" in test_json:
        opt = test_json["OPT"]

    # Compile source file
    src_file = test_file.replace(".json", "")
    src_file = src_file.replace("tests", "src")
    cc_path = f"{WIBO} {join(CC_DIR, cc_arch, cc_ver, 'mwcceppc.exe')}"
    cmd = f"{cc_path} {cflags} {opt} -c -o temp.o {src_file}"

    result = run(cmd, shell=True, stdout=PIPE,
                 stderr=PIPE, universal_newlines=True)
    if result.returncode != 0:
        print("[FATAL] Compiler threw an error:")
        print(result.returncode, result.stdout, result.stderr)
        return

    # Hash stuff in object file
    try:
        strm = InputStream.open_file("temp.o", InputStream.ENDIAN_BIG)
        elf = ELFFile(strm)
    except FileNotFoundError:
        print("[FATAL] Temporary object file could not be opened")

    # Validate section-by-section
    print(f"Unit test: {test_file}")
    any_fail = False
    for name in ELFSection.ALL_SECTIONS:
        # Test cases for this section
        cases = test_json.get(name, [])
        # Compiled data for this section
        my_sect = elf.section(name)

        if len(cases) > 0:
            print(f"{name} section:")

        # Compare hashes
        for case in cases:
            if my_sect == None:
                print(f"    [WARN] Missing section {name}")
                break

            # Expected
            test_name = case[0]
            test_hash = case[1]

            # Find target symbol in ELF
            my_sym = my_sect.symbol(test_name)
            if my_sym == None:
                # Symbol is missing from user code
                print(f"    [FAIL] {test_name} (Missing symbol)")
                any_fail = True
            else:
                # Compare hash
                hasher = Hasher()
                my_hash = hasher.hash_symbol(my_sym)
                if my_hash != None and my_hash.hex() == test_hash:
                    print(f"    [OK] {test_name}")
                else:
                    print(f"    [FAIL] {test_name} (Hash mismatch)")
                    any_fail = True

    # Delete temp object file
    if exists("temp.o"):
        remove("temp.o")

    # The program must know if any case failed,
    # so it can return the proper error code
    return not any_fail


def dir_path(path):
    if isdir(path):
        return path
    else:
        raise NotADirectoryError(path)


def main():
    global WIBO, CC_DIR

    parser = ArgumentParser()
    group = parser.add_mutually_exclusive_group(required=False)
    group.add_argument("--make_asm", type=str, required=False,
                       help="Assembly file (*.s) to create unit test from")
    group.add_argument("--make_obj", type=str, required=False,
                       help="Object file (*.o) to create unit test from")
    parser.add_argument("--compilers", type=dir_path, required=False,
                        help="Path to compilers")
    parser.add_argument("--run", type=str, required=False,
                        help="Unit test to run (specify \"all\" to run everything")
    parser.add_argument("--wibo", type=str, required=False,
                        help="Whether to use WiBo to run CodeWarrior")
    args = parser.parse_args(argv[1:])

    if args.compilers:
        CC_DIR = args.compilers

    # Create unit test from object file
    if args.make_obj != None:
        # Create unit test
        test_data = make_obj(args.make_obj)
        # Print data to console
        print(test_data)

    # Create unit test from assembly file
    elif args.make_asm != None:
        # Create unit test
        test_data = make_asm(args.make_asm)
        # Print data to console
        print(test_data)

    if args.wibo != None:
        WIBO = args.wibo

    # Run unit test
    elif args.run != None:
        # Run all tests?
        if args.run == "all":
            # Scan tests root directory
            for _path, _dir, _files, in walk(TESTS_DIR, topdown=True):
                for file in _files:
                    if file.endswith(".json"):
                        test_path = join(_path, file)
                        if not run_test(test_path):
                            print(f"[FAIL] {test_path}")
                            exit(1)

        # Run single test
        elif not run_test(args.run):
            print(f"[FAIL] {args.run}")
            exit(1)

        print("[OK] All tests OK")

    exit(0)

if __name__ == '__main__':
    main()
