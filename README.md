# open_rvl

## Overview  
 This repo contains a WIP decompilation of the Revolution (RVL) SDK.  

 This project targets the version in Wii Sports (`__MWCC__ == 0x4199_60831`), but it should be adaptable to other projects with minimal effort.  

 The Revolution SDK makes up a considerable portion of most game binaries (avg. > 20%), so this project is designed to save other projects' time by containing common code for anyone to use.  

 File, function, symbol, variable, and other names come from various games' debugging information (symbol map, DWARF, etc.).  
 
 <u>Leaked material must not be referenced, as doing so will jeopardize the legality of any project that uses open_rvl.</u>  

## Testing
 Because open_rvl does not build a binary, a new method of testing was implemented to ensure function/data equivalence.  

 All unit test files exist in `tests/`. The `tests/` directory mirrors the structure of the `src/` directory, so that unit tests can be mapped to the corresponding source file.
 - Unit test files consist of SHA-256 hashes of any code/data that should be tested.
 - The file is in JSON format, and can be generated from an assembly file (`*.s`) or object file (`*.o`) by using `tester.py`.
 
 However, there are some caveats. The open_rvl code is not linked, so non-local symbol references will stay unresolved.

 The tester is automatically run on push/pull request.

 **Only files that are fully matching should have a corresponding unit test.**

## Using the tester
 When using the tester, you can either create or run a unit test.  
   
 Configurable arguments:
 - `--make_asm={ASM_FILE}`
   - Creates a unit test from the specified assembly file, and writes the JSON data to the console.
 - `--make_obj={OBJ_FILE}`
   - Creates a unit test from the specified object file, and writes the JSON data to the console.
 - `--run={UNIT_TEST}`
   - Runs the specified unit test, and displays whether each case passes or fails.
   - **Specify "`all`" as the unit test name to recursively run everything under `tests/`.**  
   - The program returns an exit code of zero if all test cases pass, otherwise 1.
