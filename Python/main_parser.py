from lef_parser import *
from def_parser import *

def_text = "/home/ismael/Downloads/lef-parser-master/o8_cpu.def"
def_p = DefParser(def_text)
def_p.parse()
for net in def_p.nets:
    print(str(net.comp_pin)+"\n")

lef_text = "/home/ismael/Downloads/lef-parser-master/osu035.lef"
lef_p = LefParser(lef_text)
lef_p.parse()
#print(lef_p.macro_dict)
for  index in lef_p.macro_dict.keys():

    #name = macro.name
    for pin in lef_p.macro_dict[index].pin_dict:
        print(lef_p.macro_dict[index].pin_dict[pin])
