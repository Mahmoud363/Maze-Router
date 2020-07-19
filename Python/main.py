import sys
import random 
from PIL import Image, ImageDraw


from inputPaser import inputParser
from A_Star import *









path = 'test.txt' 

input_parser = inputParser(path)

input_parser.parseFile(path)

input_parser.createGrid()

paths = astar(input_parser.pinsGrid, input_parser.nets)

img = []
pixelImage = []

index = input_parser.layers
for i in range(index):
    img.append(Image.new('RGB', (1000, 1000), color = (256, 256, 256)) )
    draw = ImageDraw.Draw(img[i])
    pixelImage.append( img[i].load() )
  
for  patharray in paths: 
    x= random.randint(0,150) 
    y=random.randint(0,150) 
    z=random.randint(0,150) 
    for path in (patharray):
        (templayer, tempy, tempx) = path
        pixelImage[templayer-1][tempx-1, tempy-1]= ( x,y,z)

for i in range(index):
    text = "layer"+str(i+1)+".png"
    img[i].save(text)

print(paths)

print ("DONE")
