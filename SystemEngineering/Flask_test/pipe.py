import os

pipein = os.pipe()

print pipein.readline()
