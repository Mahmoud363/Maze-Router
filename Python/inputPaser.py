import re

from pin import Pin 

class inputParser:
    
    

    def __init__(self, path):
        self.dim = 1000
        self.pattern = r'\((.*?)\)'
        self.layers = 0
        self.nets = []
        self.pinsGrid = []
        self.parseFile(path)
        self.createGrid()

    def parseFile(self,path):
        textFile = open(path,'r')
        lines = textFile.readlines()
        for line in lines:
            netID = line.split(' ')[0]
            parse = re.findall(self.pattern,line)
            cell = []
            count=0
            for pins in parse:
                pins  = pins.split(',')
                pins = [p.strip(' ') for p in pins]
                layer = int(pins[0])-1
                x = int(pins[1])-1
                y = int(pins[2])-1
                ID = netID+"_p"+str(count)
                newPin = Pin(layer= layer, x=x, y=x, _id=ID)
                self.layers = max(self.layers, int(newPin.layer)+1)
                
                count = count+1
                cell.append(newPin)
            self.nets.append(cell)
    
    def createGrid(self):
        self.pinsGrid = [[ [('',0) for i in range(self.dim)] for j in range(self.dim)] for k in range(self.layers)] 
        for cell in self.nets:
            for pin in cell:
                #print(str(pin.layer)+ " " +str(pin.y)+ " "+ str(pin.x ))
                self.pinsGrid[pin.layer][pin.y][pin.x] = (pin.id, 1)





 


