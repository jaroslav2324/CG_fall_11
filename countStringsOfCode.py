
# Count amount of code strings in src folder

import os
import pathlib

stringsAmount = 0

rootPath = pathlib.Path(__file__).parent.resolve()
rootPath = os.path.join(rootPath, 'src')

for root, dirs, files in os.walk(rootPath):
   for name in files:
        filePath = os.path.join(root, name)
        with open(filePath, 'r') as f:
            for line in f:
                stringsAmount += 1

print(stringsAmount)
