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

    def __eq__(self, other):
        return (self.pin.x == other.pin.x and\
         self.pin.y == other.pin.y and \
         self.pin.layer == other.pin.layer)


def astar(Dgrid, nets):
    """Returns a list of tuples as a path from the given start to the given end in the given Dgrid"""
    paths = []
    for index, net in enumerate(nets):
        # Create start and end node
        start = net[0]
        start_nodes = [Node(None, start)]
        net.pop(0)

        path = []
        
        for p in net:
            end = p

            end_node = Node(None, end)

            # Initialize both open and closed list
            open_list = []
            closed_list = []

            # Add the start node
            for start_node in start_nodes:
                open_list.append(start_node)

            # Loop until you find the end
            while len(open_list) > 0:

                # Get the current node
                current_node = open_list[0]
                current_index = 0
                for index, item in enumerate(open_list):
                    if item.f < current_node.f:
                        current_node = item
                        current_index = index

                # Pop current off open list, add to closed list
                open_list.pop(current_index)
                closed_list.append(current_node)

                # Found the goal and add it to the net path
                if current_node == end_node:
                    tempPath = []
                    startList = []
                    current = current_node
                    while current is not None:
                        tempPath.append((current.pin.layer, current.pin.y, current.pin.x))
                        current.f=0
                        current.g=0
                        current.h=0
                        startList.append(current)
                        current = current.parent
                    path = list( dict.fromkeys(path.extend(list(dict.fromkeys(tempPath[::-1]))) ) )
                    start_nodes = list( dict.fromkeys(start_nodes.extend(list(dict.fromkeys(startList[::-1]))) ) )

                # Generate children
                children = []
                for i, new_position in enumerate([(0, 0, 1), (0, 1, 0), (1, 0, 0), (0, 0, -1), (0, -1, 0), (-1, 0, 0)]): # Adjacent squares

                    # Get node pin
                    node_pin = Pin(current_node.pin.layer + new_position[0], current_node.pin.y + new_position[1],  current_node.pin.x + new_position[2], start.id ) # fix this
                    
                    # Make sure within range
                    if node_pin.layer > (len(Dgrid) - 1) or node_pin.layer < 0 or node_pin.y > (len(Dgrid[len(Dgrid)-1]) -1) or node_pin.y < 0 \
                    or node_pin.x > (len(Dgrid[0][0]) -1) or node_pin.x < 0 :
                        continue

                    # Make sure walkable terrain
                    if Dgrid[node_pin.layer][node_pin.y][node_pin.x] != 0:
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
                    for closed_child in closed_list:
                        if child == closed_child:
                            flag1 = False

                    if(flag1):
                        # Create the f, g, and h values
                        if(child.pin.layer %2):
                            child.h = abs(current_node.pin.x-end.pin.x) + \
                                15 * abs(current_node.pin.y-end.pin.y) + \
                                10 * abs(current_node.pin.layer-end.pin.layer)
                            if(child.indx%3==0):
                                child.g += 1
                            elif(child.indx%3==1):
                                child.g += 15
                            else:
                                child.g += 10 * abs(current.pin.layer-child.pin.layer)

                        else:
                            child.h = abs(current_node.pin.x-end.pin.x) + \
                                15 * abs(current_node.pin.y-end.pin.y) + \
                                10 * abs(current_node.pin.layer-end.pin.layer)
                            if(child.indx%3==0):
                                child.g += 15
                            elif(child.indx%3==1):
                                child.g += 1
                            else:
                                child.g += 10 * abs(current.pin.layer-child.pin.layer)

                        
                        child.f = child.g + child.h

                        # Child is already in the open list
                        flag2 = True
                        for open_node in open_list:
                            if child == open_node and child.g > open_node.g:
                                flag2 = False

                        if(flag2):
                            # Add the child to the open list
                            Dgrid[child.pin.layer][child.pin.y][child.pin.x] = (child.pin.id,0)
                            open_list.append(child)
        paths.append(path)
        for place in path:
            Dgrid[place[0]][place[1]][place[2]] = ('nf'+str(index), 1) 

"""
def main():

    maze = [[0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]

    start = (0, 0)
    end = (7, 5)

    path = astar(maze, start, end)
    print(path)


if __name__ == '__main__':
    main()
    """