#include <algorithm>
#include "Dgrid.cpp"


int min_cost= INT_MAX;
//bool is_valid(cell current){
//    if(current.x<0
//}
struct direction{
    direction(int x_,int y_,int z_){
        x=x_;
        y=y_;
        z=z_;
    }
    int x;
    int y;
    int z;
};
int gnew,hnew,fnew;
cell mincell;
direction d1(1,0,0),d2(0,1,0),d3(0,0,1),d4(-1,0,0),d5(0,-0,0),d6(0,0,-0);
direction directions[6]={d1,d2,d3,d4,d5,d6};

bool isValid(cell current){
    if(current.x<0||current.y<0||current.layer<0 || current.x>=1000 || current.y>=1000 || current.id !="" )
        return false;
    return true;
}

bool isDestination(cell current, cell dest)
{
    if(current.x==dest.x && current.y==dest.y && current.layer==dest.layer)
        return true;
    return false;
}
int calculateHeuristic(cell current, cell target)
{
    int h;
    if(target.layer%2==1)
        h=abs(current.x-target.x)+15*(current.y-target.y)+10*(current.layer-target.layer);
    else
        h=abs(current.y-target.y)+15*(current.x-target.x)+10*(current.layer-target.layer);
    
    return h;
}

void findpath(netList& nets) {

    for (int i = 0; i < nets.size(); i++)
    {
        for (int j = 0; j < nets[i].pins.size(); j++){
            mypq_type pqueue;
            cell start = 
            pqueue.push(nets[i].pins[j]);
            nets[i].paths.push_back(nets[i].pins[j]);
            
            cell temp;
            pin temp1;
            bool destination_found = false;


            cell current = source;

            while (!openList.empty())
            {
                for (int i = 0; i < 6; i++) {
                    temp.x = current.x + directions[i].x;
                    temp.y = current.y + directions[i].y;
                    temp.layer = current.layer + directions[i].z;
                    if (isValid(temp))
                    {
                        //dvisit[temp.x][temp.y][temp.z]=1;
                        if (current.layer % 2 == 1) {
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
