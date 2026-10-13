"""Utilities for hashing ELF code/data
"""

from dataclasses import dataclass
from hashlib import sha256

from .elf import ELFSymbol


@dataclass
class Hasher():
    def hash_symbol(self, sym: ELFSymbol):
        """Calculate hash of ELF symbol
        """
        if sym.data == None:
            return None
        return self.__hash_data(sym.data)

    def __hash_data(self, data: bytearray) -> bytes:
        """Calculate hash of ELF data
        """
        sha = sha256()
        sha.update(data)
        return sha.digest()
