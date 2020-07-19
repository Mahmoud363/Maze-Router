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
x=[]
y=[]
z=[]
index = input_parser.layers
for i in range(index):
    img.append(Image.new('RGB', (1000, 1000), color = (256, 256, 256)) )
    draw = ImageDraw.Draw(img[i])
    pixelImage.append( img[i].load() )
    x.append( random.randint(100,255) )
    y.append(random.randint(100,255) )
    z.append(random.randint(100,255) )
for  patharray in paths: 

    for path in (patharray):
        (templayer, tempy, tempx) = path
        pixelImage[templayer][tempx, tempy]= ( x[templayer-1], y[templayer-1], z[templayer-1])

for i in range(index):
    text = "layer"+str(i+1)+".png"
    img[i].save(text)

print(paths)

print ("DONE")
