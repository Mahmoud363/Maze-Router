import sys

from inputPaser import inputParser
from A_Star import *

path = 'test.txt' 

input_parser = inputParser(path)

input_parser.parseFile(path)

input_parser.createGrid()

paths = astar(input_parser.pinsGrid, input_parser.nets)

print(paths)

print ("DONE")
