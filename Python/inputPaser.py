import re
import numpy as np
from pin import Pin 

class inputParser:
    
    

    def __init__(self, path, flag):
        self.pattern = r'\((.*?)\)' # regex to extract the pins
        self.layers = 0
        self.nets = []
        self.pinsGrid = {}
        self.manual = flag
        self.width=0
        self.height=0


    def parseFile(self,path):
        if self.manual == 1:
            self.width = int(input("Enter the grid width: "))
            self.height = int(input("Enter the grid height: "))
            self.layers = int(input("Enter the number of layers: "))
        else:
            textFile = open(path,'r')
            dim = textFile.readline().split(',')
            self.width = int(dim[1])
            self.height = int(dim[0])
            self.layers = int(dim[2])
            textFile.close()
        textFile = open(path,'r')
        lines = textFile.readlines()
        for line in lines:
            # parsing the input file to generate the netlist structure
            netID = line.split(' ')[0]
            parse = re.findall(self.pattern,line)
            cell = []
            count=0
            for pins in parse:
                pins  = pins.split(',')
                pins = [p.strip(' ') for p in pins]
                layer = int(pins[0])-1
                y = int(pins[1])-1
                x = int(pins[2])-1
                ID = netID
                newPin = Pin(layer, y, x, ID)
                #self.layers = max(self.layers, int(newPin.layer)+1) # calculating the maximum layer from the input
                
                cell.append(newPin)
            count = count+1
            self.nets.append(cell)
    
    def createGrid(self):
        self.pinsGrid = [[ ['0' for col in range(self.width)] for col in range(self.height)] for row in range(self.layers)]
        for cell in self.nets:
            for pin in cell:
                # mark each tuple of the pins as visited to avoid and wrong routing
                self.pinsGrid[pin.layer][pin.y][pin.x] =  '1'
    
    def getIDs(self):
        return self.IDs




 


