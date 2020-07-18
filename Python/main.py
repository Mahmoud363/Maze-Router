import sys
from PIL import Image, ImageDraw
import time


from inputPaser import inputParser
from A_Star import *

"""width = input("Enter the grid width: ")
height = input("Enter the grid height: ")"""
start_time = time.time()
width = 1000
height = 1000

path = 'test.txt' 

input_parser = inputParser(path)

input_parser.parseFile(path)

input_parser.createGrid()

paths = astar(input_parser.pinsGrid, input_parser.nets, input_parser.layers+1, width, height)
print("--- %s seconds ---" % (time.time() - start_time))
img = []
pixelImage = []
index = input_parser.layers
for i in range(index):
    img.append(Image.new('RGB', (1000, 1000), color = (256, 256, 256)) )
    draw = ImageDraw.Draw(img[i])
    pixelImage.append( img[i].load() )

# output the layers images

for  patharray in paths: 

    for path in (patharray):
        (templayer, tempy, tempx) = path
        pixelImage[templayer][tempx, tempy]= (0,0,0,255)

for i in range(index):
    text = "layer"+str(i+1)+".png"
    img[i].save(text)

#output the routed netlists
output = []
for net in input_parser.nets:
    output.append([net[0].id])

for index, path in enumerate(paths):
    path
    for route in path:
        output[index].append(route)
outFile = open("Routed.txt", 'w+')
for index, out in enumerate(output):

    outFile.write(out[0]+ ' '+ str(out[1::])[1:len(str(out[1::]))-1]+'\n')


print ("DONE")
