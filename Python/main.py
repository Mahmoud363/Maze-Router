import sys
from PIL import Image, ImageDraw
import time
import random
import copy


from inputPaser import inputParser
from A_Star import *




path = input('Enter the netlist path: ')
choice = int(input("Enter 1 to enter dimensions manually: "))
"""if choice== 1:
    width = int(input("Enter the grid width: "))
    height = int(input("Enter the grid height: "))
    layers = int(input("Enter the number of layers: "))
else:
    textFile = open(path,'r')
    dim = textFile.readline().split(',')
    width = int(dim[1])
    height = int(dim[0])
    layers = 4
    textFile.close()"""



# start of the parsing
input_parser = inputParser(path,choice)

input_parser.parseFile(path)


input_parser.createGrid()
layers = input_parser.layers
width = input_parser.width
height = input_parser.height
# generated the routing paths
netList = copy.deepcopy(input_parser.nets)

start_time = time.time()
paths = astar(input_parser.pinsGrid, netList, layers, width, height)
print("--- %s seconds ---" % (time.time() - start_time))


img = []
pixelImage = []
index = layers
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
    if(len(net)>0):
        output.append([net[0].id])

for indx, path in enumerate(paths):
    for route in path:
        output[indx].append(route)
outFile = open("Routed.txt", 'w+')
for index, out in enumerate(output):

    outFile.write(out[0]+ ' '+ str(out[1::])[1:len(str(out[1::]))-1]+'\n')


print ("DONE")