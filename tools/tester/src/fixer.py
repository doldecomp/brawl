"""Fixes assembly to conform with what the GNU assembler expects.
Used to properly emit symbol type/size in the object file."""

from dataclasses import dataclass
from typing import List
from re import match


@dataclass()
class Fixer():
    __curr_sect: str
    __curr_sym: str
    __asm: List[str]

    SECTION_REGEX = r"^\s*.section\s+(?P<Name>.[a-zA-Z0-9_$]+)"
    LABEL_REGEX = r"^\s*(?P<Name>[0-9a-zA-Z_!@#$]+)\s*\:"
    GLABEL_REGEX = r"^\s*.global\s*(\")*(?P<Name>[0-9A-Za-z_$@()#$]+)"
    ADDI_REGEX = r"^\/\*.+\*\/\s+addi\s+(?P<dst>r[0-9]+),\s+(r13)*(r2)*,\s+(?P<sym>[a-zA-Z0-9_@$#]+)@sda21"
    FUNC_REGEX = r"(?P<Name>^\w+):"
    BRANCH_REGEX = r"^\/\*.+\*\/\s+(?P<insn>b[+-]?|bne[+-]?|beq[+-]?|bgt[+-]?|blt[+-]?|bge[+-]?|ble[+-]?|bl[+-]?|bdnz[+-]?)\s+(?P<cr>\w+\,\s*)?(?P<dst>[0-9a-zA-Z_]+)"

    def __init__(self):
        self.__curr_sect = None
        self.__curr_sym = None
        self.__asm = []

    def fix(self, asm: List[str]) -> List[str]:
        self.__asm = []

        for i, line in enumerate(asm):
            # Replace tabs with spaces
            line = line.replace("\t", "    ")

            sect_match = match(self.SECTION_REGEX, line)
            glabel_match = match(self.GLABEL_REGEX, line)
            label_match = match(self.LABEL_REGEX, line)

            # Entered a new section
            if sect_match != None:
                sect_name = sect_match.group("Name")
                self.begin_section(sect_name)
                self.__asm.append(line)

            # Entered a new global symbol
            elif glabel_match != None:
                glabel_name = glabel_match.group("Name")
                self.begin_symbol(glabel_name)

            # Entered a new symbol
            elif label_match != None:
                label_name = label_match.group("Name")
                # Is it local?
                if i > 0 and match(self.GLABEL_REGEX, asm[i - 1]) == None:
                    # Convert function local label
                    if self.__curr_sect == ".text" and label_name.startswith("lbl_"):
                        self.proc_fn_local_lbl(label_name)
                    # Not fn-local, make it global
                    else:
                        self.begin_symbol(label_name)

            # Looking at an instruction?
            elif line.startswith("/*"):
                self.proc_insn(line)

            # This line does not matter
            else:
                self.__asm.append(line)

        # End last symbol
        self.end_symbol()
        return self.__asm

    def begin_section(self, sect: str):
        """Begin a new section
        """
        self.end_symbol()
        self.__curr_sect = sect

    def begin_symbol(self, sym: str):
        """Begin a new symbol
        """
        self.end_symbol()
        self.__curr_sym = sym

        if self.__curr_sect == ".text":
            self.__asm.append(f"fn global {self.__curr_sym}\n")
        else:
            self.__asm.append(f"obj global {self.__curr_sym}\n")

    def end_symbol(self):
        """End the current symbol
        """
        if self.__curr_sym != None:
            # Remove trailing newline
            if self.__asm[-1] == "\n":
                self.__asm.pop()
            self.__asm.append(f"end {self.__curr_sym}\n\n")
        self.__curr_sym = None

    def proc_fn_local_lbl(self, lbl: str):
        """Convert doldisasm-format local label (lbl_*)
        to what GAS expects (.L_*)
        """
        self.__asm.append(f"{lbl.replace('lbl_', '.L_')}:\n")
        pass

    def proc_insn(self, line: str):
        """Fix instruction.
        This entails fixing SDA/label relocations and
        replacing SDA addi accesses with li accesses.
        """
        # Fix SDA relocations
        line = line.replace("-_SDA_BASE_", "@sda21")
        line = line.replace("-_SDA2_BASE_", "@sda21")
        line = line.replace("@sda21(r13)", "@sda21(0)")
        line = line.replace("@sda21(r2)", "@sda21(0)")

        addi_match = match(self.ADDI_REGEX, line)
        branch_match = match(self.BRANCH_REGEX, line)

        # Convert GAS addi -> CW li
        if addi_match != None:
            # Insn operands
            dst = addi_match.group("dst")
            sym = addi_match.group("sym")
            line = f"li {dst}, {sym}@sda21\n"

        # Patch local branch destination
        elif branch_match != None:
            insn = branch_match.group("insn")
            cr = branch_match.group("cr")
            dst = branch_match.group("dst")

            if cr == None:
                cr = ""

            if insn != "bl" and dst.startswith("lbl_"):
                line = f"{insn} {cr} {dst.replace('lbl_', '.L_')}\n"

        self.__asm.append(line)
