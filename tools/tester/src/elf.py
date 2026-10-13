"""Minimal ELF implementation to extract information required for testing.
"""

from dataclasses import dataclass
from typing import List, Dict

from .stream import InputStream


@dataclass
class ELFSection():
    name: str
    data: bytearray
    symbol_list: "List[ELFSymbol]"
    symbol_dict: "Dict[str, ELFSymbol]"

    sh_name: int
    sh_type: int
    sh_flags: int
    sh_addr: int
    sh_offset: int
    sh_size: int
    sh_link: int
    sh_info: int
    sh_addralign: int
    sh_entsize: int

    CODE_SECTIONS = [".init", ".text"]
    DATA_SECTIONS = [".ctors", ".dtors",
                     ".rodata", ".data", ".bss", ".sdata", ".sbss", ".sdata2", ".sbss2"]
    BSS_SECTIONS = [".bss", ".sbss", ".sbss2"]
    ALL_SECTIONS = [".init", ".text", ".ctors", ".dtors",
                    ".rodata", ".data", ".bss", ".sdata", ".sbss", ".sdata2", ".sbss2"]

    def __init__(self, strm: InputStream):
        """Parse ELF section header from stream
        """
        assert not strm.eof()

        # Manually set later
        self.name = "NoName"
        self.data = None
        self.symbol_list = list()
        self.symbol_dict = dict()

        self.sh_name = strm.get_u32()
        self.sh_type = strm.get_u32()
        self.sh_flags = strm.get_u32()
        self.sh_addr = strm.get_u32()
        self.sh_offset = strm.get_u32()
        self.sh_size = strm.get_u32()
        self.sh_link = strm.get_u32()
        self.sh_info = strm.get_u32()
        self.sh_addralign = strm.get_u32()
        self.sh_entsize = strm.get_u32()

        # TODO: Actually fix BSS
        try:
            # Read section data
            if self.sh_size > 0:
                strm.seek(self.sh_offset, InputStream.SEEK_BEGIN)
                self.data = strm.read(self.sh_size)
        except Exception:
            self.data = bytearray(self.sh_size)

    def all_symbols(self) -> "List[ELFSymbol]":
        """Access all ELF symbols in section
        """
        return self.symbol_list

    def symbol(self, name: str) -> "ELFSymbol":
        """Access ELF symbol by name
        """
        return self.symbol_dict.get(name, None)

    def is_code(self) -> bool:
        """Check if this section contains code
        """
        return self.name in self.CODE_SECTIONS

    def is_data(self) -> bool:
        """Check if this section contains data
        """
        return self.name in self.DATA_SECTIONS

    def is_bss(self) -> bool:
        """Check if this section contains zero-initialized data
        """
        return self.name in self.BSS_SECTIONS


@dataclass
class ELFSymbol():
    name: str
    data: bytearray
    parent: ELFSection

    st_name: int
    st_value: int
    st_size: int
    st_info: int
    st_other: int
    st_shndx: int

    STT_OBJECT = 1
    STT_FUNC = 2

    def __init__(self, strm: InputStream):
        """Parse ELF symbol (.symtab entry) from stream.
        NOTE: Symbol data is not read here, because some symbols
        need their sizes corrected first.
        """
        assert not strm.eof()

        # Manually set later
        self.name = "NoName"
        self.data = None
        self.parent = None

        self.st_name = strm.get_u32()
        self.st_value = strm.get_u32()

        # NOTE: Most symbols have zero size for some reason.
        # We calculate the size later in the parent ELFFile (if needed)
        self.st_size = strm.get_u32()

        self.st_info = strm.get_u8()
        self.st_other = strm.get_u8()
        self.st_shndx = strm.get_u16()


@dataclass
class ELFHeader():
    ei_mag: str
    ei_class: int
    ei_data: int
    ei_version: int
    ei_osabi: int
    ei_abiversion: int
    e_type: int
    e_machine: int
    e_version: int
    e_entry: int
    e_phoff: int
    e_shoff: int
    e_flags: int
    e_ehsize: int
    e_phentsize: int
    e_phnum: int
    e_shentsize: int
    e_shnum: int
    e_shstrndx: int

    E_CLASS_32 = 1
    E_DATA_BE = 2
    E_MACHINE_PPC = 0x14

    def __init__(self, strm: InputStream):
        """Parse ELF file header from stream
        """
        assert not strm.eof()

        self.ei_mag = strm.get_string_sz(4)
        self.ei_class = strm.get_u8()
        self.ei_data = strm.get_u8()
        self.ei_version = strm.get_u8()
        self.ei_osabi = strm.get_u8()
        self.ei_abiversion = strm.get_u8()

        # Skip padding
        strm.read(7)

        self.e_type = strm.get_u16()
        self.e_machine = strm.get_u16()
        self.e_version = strm.get_u32()
        self.e_entry = strm.get_u32()
        self.e_phoff = strm.get_u32()
        self.e_shoff = strm.get_u32()
        self.e_flags = strm.get_u32()
        self.e_ehsize = strm.get_u16()
        self.e_phentsize = strm.get_u16()
        self.e_phnum = strm.get_u16()
        self.e_shentsize = strm.get_u16()
        self.e_shnum = strm.get_u16()
        self.e_shstrndx = strm.get_u16()

    def is_valid(self) -> bool:
        """Confirm that the ELF header is of the type
        expected by this tool (32-bit, PowerPC, Big Endian)
        """
        if self.ei_mag != "\x7FELF":
            return False

        if self.ei_class != self.E_CLASS_32:
            return False

        if self.ei_data != self.E_DATA_BE:
            return False

        if self.e_machine != self.E_MACHINE_PPC:
            return False

        return self.e_shnum > 0


def sym_sort_key_func(sym: ELFSymbol):
    """Sort key for symbol list.
    Because we dynamically calculate the size of GAS symbols,
    we first need to sort the symbols by their offset.
    """
    return sym.st_value


@dataclass
class ELFFile():
    header: ELFHeader
    section_list: List[ELFSection]
    section_dict: Dict[str, ELFSection]

    def __init__(self, strm: InputStream):
        """Parse ELF file
        """
        assert not strm.eof()

        # File header
        self.header = ELFHeader(strm)
        assert self.header.is_valid(), "Invalid ELF header"

        # Section headers
        self.section_list = list()
        for i in range(self.header.e_shnum):
            # Seek to section
            strm.seek(self.header.e_shoff +
                      (i * self.header.e_shentsize), InputStream.SEEK_BEGIN)
            # Append section to list
            self.section_list.append(ELFSection(strm))

        # Fixup section names using the string table
        self.section_dict = dict()
        for sect in self.section_list:
            sect.name = self.__get_shstrtab_name(sect.sh_name)
            # Insert section into dictionary
            if sect.name != "":
                assert sect.name not in self.section_dict, "Duplicate section?"
                self.section_dict[sect.name] = sect

        # Open stream to .symtab data
        sh_symtab = self.section_dict[".symtab"]
        symtab = InputStream(sh_symtab.data, InputStream.ENDIAN_BIG)
        # Parse symbol table data
        for i in range(sh_symtab.sh_size // sh_symtab.sh_entsize):
            symbol = ELFSymbol(symtab)
            # Set parent section (if not special section)
            if symbol.st_shndx < self.header.e_shnum:
                symbol.parent = self.section_list[symbol.st_shndx]
                symbol.parent.symbol_list.append(symbol)

        # Second pass through symbols.
        # Here we do the following:
        #   1. Apply symbol names from .strtab
        #   2. Calculate size of symbols where size=0
        #   3. Read symbol data from stream
        for sect in self.section_list:
            # Sort symbol list by offset to ensure
            # sizes calculated later are correct
            sect.symbol_list.sort(key=sym_sort_key_func)

            for i, sym in enumerate(sect.symbol_list):
                # Apply symbol name
                sym.name = self.__get_strtab_name(sym.st_name)
                if sym.name == "":
                    sym.name = sect.name

                # Store symbol in parent dictionary
                if sym.st_shndx < self.header.e_shnum:
                    sym.parent = self.section_list[sym.st_shndx]
                    sym.parent.symbol_dict[sym.name] = sym

                # Only read data if there is data to read :)
                if sect.data != None:
                    # Calculate symbol size if it was read as zero
                    if sym.st_size == 0:
                        if i + 1 < len(sect.symbol_list):
                            sym.st_size = sect.symbol_list[i +
                                                           1].st_value - sym.st_value
                        else:
                            sym.st_size = sect.sh_size - sym.st_value

                    # Read symbol data
                    if sym.st_size > 0:
                        # Zero-initialized data
                        if sect.is_bss():
                            sym.data = bytearray(sym.st_size)
                        else:
                            strm.seek(sect.sh_offset, InputStream.SEEK_BEGIN)
                            strm.seek(sym.st_value, InputStream.SEEK_CURRENT)
                            sym.data = strm.read(sym.st_size)

    def all_sections(self) -> List[ELFSection]:
        """Access all ELF sections in file
        """
        # Skip UNDEF section
        return [x for x in self.section_list if x.name != ""]

    def section(self, name: str) -> ELFSection:
        """Access ELF section by name
        """
        return self.section_dict.get(name, None)

    def __get_strtab_name(self, ofs: int) -> str:
        """Get name from .strtab section, given an offset
        """
        assert ".strtab" in self.section_dict, ".strtab section missing?"
        strm = InputStream(
            self.section_dict[".strtab"].data, InputStream.ENDIAN_BIG)
        strm.seek(ofs, InputStream.SEEK_BEGIN)
        return strm.get_string()

    def __get_shstrtab_name(self, ofs: int) -> str:
        """Get name from .shstrtab section, given an offset
        """
        assert self.header.e_shstrndx != -1, ".shstrtab section missing?"
        strm = InputStream(
            self.section_list[self.header.e_shstrndx].data, InputStream.ENDIAN_BIG)
        strm.seek(ofs, InputStream.SEEK_BEGIN)
        return strm.get_string()
