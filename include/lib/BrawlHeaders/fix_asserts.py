import os
import sys
import re
import subprocess

from pathlib import Path
result = list(Path(".").rglob("*.[hH]"))

for path in result:
    print(path)
    f = open(path, 'a+')
    f.seek(0)
    data = f.read()
    f.truncate(0)
    data = re.sub(r'STATIC_CHECK\((.*)\)\s*\};', r'};\nstatic_assert(\1, "Class is wrong size!");',data,flags=re.MULTILINE)
    f.write(data)
    f.close()
    res=subprocess.run(["clang-format", "-i","--style=file", path], check=True)
    