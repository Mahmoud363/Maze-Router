# Maze-Router
Project 2 (Digital Design II) supervised by Dr. Shalan
By:
- Mahmoud Ahmed - 900172747
- Ismael Elsharkawi - 900173030 
- Ahmed Ehab Hamouda- 900172637
***********************************************************************************************
**Description:**
------------------
Presented is a python application which performs wiring of a given netlist of the format:
net (layer, y, x) (layer, y, x) ...\
The application takes the input and converts the text file to its suitable structures in the code. Then, It performs an A* routing on the netlist.\
The output of the application is the new routed list under the name "Routed.txt" along with PNG pictures to visualize each layer.
***********************************************************************************************
**Phases of Execution:**
-------------------------
1- Input Parsing to generate the suitable data structure for the program\
2- The netlist is passed to the A* function which finds the best route for each net\
3- The generated paths are used to generate visual representation of the routed netlist\
4- The routed netlist is outputted to a file under the name "Router.txt"
***********************************************************************************************
**Algorithm:**
---------------
For this application, A* was used since it guarantees the shortest path while being more intelligent in choosing the next cell to traverse than Lee algorithm.\
The algorithm chooses the next position based on its own cost function and keeps choosing the least one until the target is reached
***********************************************************************************************
**Technical Details of Routing**
----------------------
The routing process is as follows:  
1. Pin locations of the nets, read from the input file, are marked in a python dictionary as visited to avoid trying to route on a pin  
2. A detailed routing is performed under the following assumptions:  
    - There are no obstruction in the grid  
    - there are no vias and it is allowed to move from one layer to the other under certain conditions  
3. Each net is routed one by one  
    - The source is first routed to the next pin and so on  
    - In case of more than two pins, all the previously routed places on the grid for this net are considered as possible starting positions to reach the new target.  
    - When the target is reached, the algorithm back-traverses throught the parents of each node untill the start node is reached.  
    - A shortest path is found by the A* algorithm for this pin.   
*********************************************************************************************
**Issues and Limitations**
--------------------------
1. Using python for this project slows down the runtime compared to C++ projects.  
2. Need to implement the rip-up reroute to handle unroutable nets   
3. Some nets don't have a dependency or routes crossed, so they could have been parallelized to achieve better performance.  
********************************************************************************************

**How to use:**
----------------
1. Run the command python main.py  
2. When propted, enter the width, height, and the file containing the netlist you want to route
***********************************************************************************************
