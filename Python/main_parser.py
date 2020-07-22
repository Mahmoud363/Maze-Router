from lef_parser import *
from def_parser import *
import os

def prepend_line(file_name, line):
    """ Insert given string as a new line at the beginning of a file """
    # define name of temporary dummy file
    dummy_file = file_name + '.bak'
    # open original file in read mode and dummy file in write mode
    with open(file_name, 'r') as read_obj, open(dummy_file, 'w') as write_obj:
        # Write given line to the dummy file
        write_obj.write(line + '\n')
        # Read lines from original file one by one and append them to the dummy file
        for line in read_obj:
            write_obj.write(line)
    # remove original file
    os.remove(file_name)
    # Rename dummy file as the original file
    os.rename(dummy_file, file_name)




def_text = input('Enter the Def path: ')
def_p = DefParser(def_text)
def_p.parse()
for net in def_p.nets:
    print(str(net.comp_pin)+"\n")

lef_text = input('Enter the LEF path: ')
lef_p = LefParser(lef_text)
lef_p.parse()
#print(lef_p.macro_dict)
"""for  index in lef_p.macro_dict.keys():
    print(lef_p.macro_dict[index].name)
    for pin in lef_p.macro_dict[index].info.keys():
        if(pin =="PIN"):
            for pin_1 in lef_p.macro_dict[index].info[pin]:
                print(pin_1.name)
                for key,pin_2 in pin_1.info.items():
                    if(key=="PORT"):
                        for key_3, pin_3 in pin_2.info.items():
                            for layer_item in pin_3:
                                print(int(layer_item.name[-1], 10))
                                #layer_item.name is the layer we want to take
                                for rectangle in layer_item.shapes:
                                    avgx=0
                                    avgy=0
                                    totalx=0
                                    totaly=0
                                    for point in rectangle.points:
                                        (tempx,tempy)= point
                                        totalx+=tempx*10        #as per requirements
                                        totaly+=tempy*10
                                avgx = totalx / len(layer_item.shapes)
                                avgy = totaly / len(layer_item.shapes)
                                print("X: ",avgx, " Y: ", avgy)

                """
    #name = macro.name
    #for pin in lef_p.macro_dict[index].pin_dict.keys():
        #print(pin)
        #print(" \n")
fil1 = open("MyFile.txt","w+")
i=0
maxx=0
maxy=0
maxlayer=0


for net in def_p.nets:
    i=i+1
   # print(net.name)
    #(x) = net.comp_pin
    name= "net"+str(i)
    fil1.write(name)
    #print("\\\ /n")
    for route in net.comp_pin:
        for component in def_p.components:
            
            if(component.name== route[0]):
                flag = False
                if(route[1]=="CLK" or route[1]=="vdd" or route[1]=="VDD" or route[1]=="gnd" or route[1]=="GND"):
                    continue
                for pin in def_p.pins:
                    
                    if(pin.name == route[1]):
                        flag = True
                        print("Similarity: ", pin.name)
                if(flag):
                    continue
               # print(component.name)
                #print(component.macro)
                (originx, originy) = component.placed
                for  index in lef_p.macro_dict.keys():
                    if(lef_p.macro_dict[index].name==component.macro):
                        for pin in lef_p.macro_dict[index].info.keys():
                            if(pin =="PIN"):
                                for pin_1 in lef_p.macro_dict[index].info[pin]:
                                    if(pin_1.name==route[1]):
                                        for key,pin_2 in pin_1.info.items():
                                            if(key=="PORT"):
                                                for key_3, pin_3 in pin_2.info.items():
                                                    for layer_item in pin_3:
                                                        #print(int(layer_item.name[-1], 10))
                                                        #layer_item.name is the layer we want to take
                                                        for rectangle in layer_item.shapes:
                                                            avgx=0
                                                            avgy=0
                                                            totalx=0
                                                            totaly=0
                                                            for point in rectangle.points:
                                                                (tempx,tempy)= point
                                                                totalx+=tempx#*10        #as per requirements
                                                                totaly+=tempy#*10
                                                        avgx = totalx / len(layer_item.shapes)
                                                        avgy = totaly / len(layer_item.shapes)
                                                        maxx= max(maxx, int(originx+avgx))
                                                        maxy= max(maxy, int(originy+avgy))
                                                        maxlayer= max(maxlayer, int(layer_item.name[-1], 10) )
                                                        string = " ("+ str(int(layer_item.name[-1], 10)) + " , "+str(int(originx/10.0+avgx/100.0-def_p.diearea[0][0]/10.0))+ " , " + str(int(originy/10.0+avgy/100.0 -def_p.diearea[0][1]/10.0))+" )"
                                                        fil1.write(string)
                                                        #if(i<10):
                                                         #   print(route[0]," :: ",route[1]," :: ", originx," , ", originy, "\n")
    if(i<10):
        print(net.name)
    fil1.write("\n")
                #for pin in lef_p.pin_dict
                #print("placed")
        #print(route[0])
        #print("--")
   # print("+++++")
fil1.close()
width = int((def_p.diearea[1][0] - def_p.diearea[0][0])/10)
height = int((def_p.diearea[1][1] - def_p.diearea[0][1])/10)
layer = str(list(lef_p.layer_dict.keys())[-1]).split('l')[1]
dimensions = str(width)+", "+str(height)+ ", " +layer+"\n"
prepend_line("MyFile.txt",dimensions)
