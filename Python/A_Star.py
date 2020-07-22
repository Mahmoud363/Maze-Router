from queue import PriorityQueue
import numpy as np
from inputPaser import inputParser
from pin import Pin


class Node():
    """A node class for A* Pathfinding"""

    def __init__(self, parent=None, pin=None ):
        self.parent = parent
        self.pin = pin
        self.indx=0
        self.g = 0
        self.h = 0
        self.f = 0

    def __hash__(self):
        return hash(str(self))

    def __eq__(self, other):
        return (self.pin.x == other.pin.x and\
         self.pin.y == other.pin.y and \
         self.pin.layer == other.pin.layer) 
    def __lt__(self, other):
        return self.f < other.f


def astar(Dgrid, nets, layers, width, height):
    """Returns a list of tuples as a path from the given start to the given end in the given Dgrid"""
    paths = []
    costs =[]
    for index, net in enumerate(nets):
        # Create start and end node
        net1 = net
        if(len(net)==0):
            print('pin done')
            continue
        start = net[0]
        start_nodes = [Node(None, start)]
        net1.pop(0)

        path = []
        if (len(net) == 0):
            path.append((start.layer, start.y, start.x))
            print('a pin done')

        for p in net1:
            end = p

            end_node = Node(None, end)
            Dgrid[p.layer][p.y][p.x] ='0'
            # Initialize both open and closed list
            open_list = PriorityQueue()
            closed_list = []

            # Add the start nodes
            for start_node in start_nodes:
                open_list.put(start_node)

            # Loop until you find the end
            while open_list.qsize() > 0:

                # Get the current node
                current_node = open_list.get()
                current_index = 0
                """
                for indx, item in enumerate(open_list):
                    if item.f <= current_node.f:
                        current_node = item
                        current_index = indx"""

                # Pop current off open list, add to closed list
                
               # closed_list.append(current_node)
                
                # Found the goal and add it to the net path
                if current_node == end_node:
                    tempPath = []
                    startList = []
                    current = current_node
                    while current is not None:
                        tempPath.append((current.pin.layer+1, current.pin.y+1, current.pin.x+1))
                        #costs.append([current.f,current.g, current.h])
                        current.f=0
                        current.g=0
                        current.h=0
                        startList.append(current)
                        Dgrid[current.pin.layer][current.pin.y][current.pin.x] = '1'
                        current = current.parent
                    #costs = costs[::-1]
                    path.extend(list(dict.fromkeys(tempPath[::-1])))
                    path = list( dict.fromkeys(path ) )
                    start_nodes.extend(list(dict.fromkeys(startList[::-1])))
                    start_nodes = list( dict.fromkeys(start_nodes ) )
                    print('a pin done')
                    break
                # Generate children
                children = []
                for i, new_position in enumerate([(0, 0, 1), (0, 1, 0), (1, 0, 0), (0, 0, -1), (0, -1, 0), (-1, 0, 0)]): # Adjacent squares

                    # Get node pin
                    node_pin = Pin(current_node.pin.layer + new_position[0], current_node.pin.y + new_position[1],  current_node.pin.x + new_position[2], start.id ) # fix this
                    
                    # Make sure within range
                    if node_pin.layer >= (layers) or node_pin.layer < 0 or node_pin.y > (height -1) or node_pin.y < 0 \
                    or node_pin.x > (width -1) or node_pin.x < 0 :
                        continue

                    # Make sure walkable terrain
                    if Dgrid[node_pin.layer][node_pin.y][node_pin.x] == '1':
                        continue
                    if(current_node.parent):
                        if( (node_pin.layer==current_node.parent.pin.layer and node_pin.y == current_node.parent.pin.y and node_pin.x == current_node.parent.pin.x ) ):
                            continue

                    # Create new node

                    new_node = Node(current_node, node_pin)
                    new_node.indx=i

                    # Append
                    children.append(new_node)

                # Loop through children
                for child in children:
                    flag1 = True
                    # Child is on the closed list
                    

                    if(flag1):
                        # Create the f, g, and h values
                        if(child.pin.layer %2==0):  # horizontal layers
                            child.h = abs(child.pin.x-end_node.pin.x) + \
                                1*abs(child.pin.y-end_node.pin.y) + \
                                1*abs(child.pin.layer-end_node.pin.layer)
                            if(child.indx%3==0):
                                child.g = child.parent.g + 1
                            elif(child.indx%3==1):
                                child.g = child.parent.g + 10
                            else:
                                child.g = child.parent.g + 10 * abs(current_node.pin.layer-child.pin.layer)

                        else:   # vertical layers
                            child.h =  1*abs(child.pin.x-end_node.pin.x) + \
                                abs(child.pin.y-end_node.pin.y) + \
                                1* abs(child.pin.layer-end_node.pin.layer)
                            if(child.indx%3==0):
                                child.g = child.parent.g + 10
                            elif(child.indx%3==1): 
                                child.g = child.parent.g + 1
                            else:
                                child.g = child.parent.g + 10 * abs(current_node.pin.layer-child.pin.layer)

                        
                        child.f =  child.h + child.g

                        # Child is already in the open list
                        flag2 = True

                        if(flag2):
                            Dgrid[child.pin.layer][child.pin.y][child.pin.x] = '2'
                            open_list.put(child)
            for closed in open_list.queue:
                if Dgrid[closed.pin.layer][closed.pin.y][closed.pin.x] == '2':
                    Dgrid[closed.pin.layer][closed.pin.y][closed.pin.x] =  '0'
            if (open_list.qsize() == 0):
                print("Net n" + str(index) + " Failed")
                break
        paths.append(path)
        for place in path:
            Dgrid[place[0]-1][place[1]-1][place[2]-1] =  '1'
        if(len(path)):
            print('net done')
        
    return paths