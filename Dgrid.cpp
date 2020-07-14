#include "Dgrid.h"
#include "inputParser.h"
Dgrid::Dgrid(int const& layers, netList const& net) // takes the maximum number of layers as input and the netlist to fill the grid
{
	Dcells = vector<vector<vector<cell> > >(layers+1, vector<vector<cell> >(1000, vector<cell>(1000)));
	Dvisited = vector<vector<vector<int> > >(layers+1, vector<vector<int> >(1000, vector<int>(1000, 0)));

	for (int i = 0; i < net.size(); i++)
	{
		for (int j = 0; j < net[i].pins.size(); j++) {
			pin p = net[i].pins[j];
			cell tempCell(p);
			Dcells[p.layer][p.y][p.x] = tempCell;
			Dvisited[p.layer][p.y][p.x] = 1;
		}
	}

}

Dgrid::~Dgrid()
{
}

cellGrid Dgrid::getCellGrid() {
	return Dcells;
}

visGrid Dgrid::getVisitedGrid() {
	return Dvisited;
}


int min_cost = INT_MAX;
//bool is_valid(cell current){
//    if(current.x<0
//}
struct direction {
    direction(int x_, int y_, int z_) {
        x = x_;
        y = y_;
        z = z_;
    }
    int x;
    int y;
    int z;
};
int gnew, hnew, fnew;
cell mincell;
direction d1(1, 0, 0), d2(0, 1, 0), d3(0, 0, 1), d4(-1, 0, 0), d5(0, -1, 0), d6(0, 0, -1);  // E,N,U,W,S,D
direction directions[6] = { d1,d2,d3,d4,d5,d6 };

bool Dgrid::isValid(cell current) {
    if (current.x < 0 || current.y < 0 || current.layer < 0 || current.x >= 1000 || current.y >= 1000 || current.id != "")
        return false;
    return true;
}

bool Dgrid::isDestination(cell current, cell dest)
{
    if (current.x == dest.x && current.y == dest.y && current.layer == dest.layer)
        return true;
    return false;
}
int Dgrid::calculateHeuristic(cell current, cell target)
{
    int h;
    if (target.layer % 2 == 1)
        h = abs(current.x - target.x) + 15 * (current.y - target.y) + 10 * (current.layer - target.layer);
    else
        h = abs(current.y - target.y) + 15 * (current.x - target.x) + 10 * (current.layer - target.layer);

    return h;
}

void Dgrid::clearGrids(cell start, cell target, net& nets) { // just use pointers instead
    cell curCell;
    pin curr;
    curr.x = target.x; curr.y = target.y; curr.layer = target.layer; curr.id = target.id;
    while (curCell.x != start.x || curCell.y != start.y || curCell.layer != start.layer) {
        curr.x = target.x; curr.y = target.y; curr.layer = target.layer; curr.id = target.id;
        nets.paths.push_back(curr);
        char pre = Dcells[curr.x][curr.y][curr.layer].pre;
        switch (pre)
        {
        case 'N':
            curr.y = curr.y + 1;
        case 'E':
            curr.x++;
        case 'U':
            curr.layer++;
        case 'S':
            curr.y--;
        case 'W':
            curr.x--;
        case 'D':
            curr.layer--;
        default:
            break;
        }
    }

}
void Dgrid::findpath(netList& nets) {

    for (int i = 0; i < nets.size(); i++)
    {
        cell start(nets[i].pins[0]);
        pqueue.push(start);
        nets[i].paths.push_back(nets[i].pins[0]);
        for (int j = 1; j < nets[i].pins.size(); j++) {
            
            cell target(nets[i].pins[j + 1]);
            
            //nets[i].paths.push_back(nets[i].pins[j]);

            cell childCell;
            pin temp1;
            bool destination_found = false;


            /*
            Traverse the children till you find the target.
            after finding the target, empty the queue, clear all n1 cells from the grid for example
            traverse from the target to the source and mark them as nf1. this allows for distinction between the path and the children generated
            add each cell on the path to
            */

            while (!pqueue.empty())
            {
                cell current = pqueue.top();
                pqueue.pop();
                for (int i = 0; i < 6; i++) {
                    childCell.x = current.x + directions[i].x;
                    childCell.y = current.y + directions[i].y;
                    childCell.layer = current.layer + directions[i].z;

                    // E,N,U,W,S,D
                    switch (i)
                    {
                    case 0:
                        childCell.pre = 'W';
                    case 1:
                        childCell.pre = 'S';
                    case 2:
                        childCell.pre = 'D';
                    case 3:
                        childCell.pre = 'E';
                    case 4:
                        childCell.pre = 'N';
                    case 5:
                        childCell.pre = 'U';
                    default:
                        break;
                    }


                    if (isValid(childCell))
                    {
                        //dvisit[temp.x][temp.y][temp.z]=1;
                        if (current.layer % 2 == 1) {
                            if (isDestination(childCell, target)) {
                                Dcells[childCell.x][childCell.y][childCell.layer].id = "nf" + to_string(i);;
                                temp1(childCell.x, childCell.y, childCell.layer, childCell.id);
                                path.push_back(temp1);
                                destination_found = true;
                                return path;
                            }
                            else if (dvisit[temp.x][temp.y][temp.z] == false)
                            {
                                if (i % 3 == 0)
                                    gnew = 1;
                                else if (i % 3 == 1)
                                    gnew = 10;
                                else
                                    gnew = 10 * abs(temp.layer - current.layer);

                                hnew = calculateHeuristic(temp, target);
                                fnew = gnew + hnew;
                                dcell[temp.x][temp.y][temp.layer].f = fnew;
                                if (fnew < min_cost)
                                {
                                    mincell = temp;
                                    min_cost = fnew;
                                    temp1(temp.x, temp.y, temp.layer, temp.id);

                                }

                            }



                        }
                        else
                        {
                            if (isDestination(temp, target)) {
                                dcell[temp.x][temp.y][temp.layer].id = current.id;
                                temp1(temp.x, temp.y, temp.layer, temp.id);
                                path.push_back(temp1);
                                destination_found = true;
                                return path;
                            }
                            else if (dvisit[temp.x][temp.y][temp.z] == false)
                            {
                                if (i % 3 == 0)
                                    gnew = 10;
                                else if (i % 3 == 1)
                                    gnew = 1;
                                else
                                    gnew = 10 * abs(temp.layer - current.layer);

                                hnew = calculateHeuristic(temp, target);
                                fnew = gnew + hnew;
                                dcell[temp.x][temp.y][temp.layer].f = fnew;
                                if (fnew < min_cost)
                                {
                                    mincell = temp;
                                    min_cost = fnew;
                                    temp1(temp.x, temp.y, temp.layer, temp.id);

                                }

                            }

                        }
                    }

                }

                mincell = current;

                dcell[mincell.x][mincell.y][mincell.layer].id = current.id;
                openList.pop_back();
                path.push_back(temp1);
                openList.push_back(mincell);

            }
        }
    }

}




/*
int main() {

	string str;
	cin >> str;

	InputParser inp(str);

	netList ne = inp.getNetList();
	int mylayer = inp.getMaxLayer();


	Dgrid grid(mylayer, ne);

	return 0;
}

*/