import sys
from PIL import Image, ImageDraw
import time
import random


from inputPaser import inputParser
from A_Star import *

width = int(input("Enter the grid width: "))
height = int(input("Enter the grid height: "))
start_time = time.time()


path = input('Enter the netlist path: ')

# start of the parsing
input_parser = inputParser(path)

input_parser.parseFile(path)

input_parser.createGrid()

# generated the routing paths
paths = astar(input_parser.pinsGrid, input_parser.nets, input_parser.layers, width, height)

print("--- %s seconds ---" % (time.time() - start_time))


img = []
pixelImage = []
index = input_parser.layers
for i in range(index):
    img.append(Image.new('RGB', (width, height), color = (256, 256, 256)) )
    draw = ImageDraw.Draw(img[i])
    pixelImage.append( img[i].load() )

# output the layers images

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

#output the routed netlists
output = []
for net in input_parser.nets:
    output.append([net[0].id])

for index, path in enumerate(paths):
    for route in path:
        output[index].append(route)
outFile = open("Routed.txt", 'w+')
for index, out in enumerate(output):

    outFile.write(out[0]+ ' '+ str(out[1::])[1:len(str(out[1::]))-1]+'\n')


print ("DONE")
