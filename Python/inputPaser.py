import re

from pin import Pin 

class inputParser:
    
    

    def __init__(self, path):
        self.pattern = r'\((.*?)\)' # regex to extract the pins
        self.layers = 0
        self.nets = []
        self.pinsGrid = {}

    def parseFile(self,path):
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
                self.layers = max(self.layers, int(newPin.layer)+1) # calculating the maximum layer from the input
                
                cell.append(newPin)
            count = count+1
            self.nets.append(cell)
    
    def createGrid(self):
        for cell in self.nets:
            for pin in cell:
                # mark each tuple of the pins as visited to avoid and wrong routing
                self.pinsGrid[(pin.layer, pin.y, pin.x)] =  1
    
    def getIDs(self):
        return self.IDs




 


