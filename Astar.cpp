

#include <algorithm>
#include "Dgrid.cpp"


int min_cost= INT_MAX;

struct direction{ // a stract to define directions
    int x;
       int y;
       int z;
    direction(int x_,int y_,int z_){
        x=x_;
        y=y_;
        z=z_;
    }

};
int gnew,hnew,fnew; //values of g,h,f for cells
cell mincell; //a cell that stores the cell with minimum f
direction d1(1,0,0),d2(0,1,0),d3(0,0,1),d4(-1,0,0),d5(0,-1,0),d6(0,0,-1); // cpp did some errors so I do==had to initialize directions this way
direction directions[6]={d1,d2,d3,d4,d5,d6}; //array of the six directions

bool isValid(cell current){ // this function checks if this is a valid cell
    if(current.x<0||current.y<0||current.layer<0 || current.x>=1000 || current.y>=1000 || current.id !="" )
        return false;
    return true;
}

bool isDestination(cell current, cell dest)
{
    if((current.x==dest.x && current.y==dest.y && current.layer==dest.layer) || current.id == dest.id)
        return true;
    return false;
}
int calculateHeuristic(cell current, cell target)
{
    int h;
    if(target.layer%2==1)
        h=abs(current.x-target.x)+10*(current.y-target.y)+10*(current.layer-target.layer);
    else
        h=abs(current.y-target.y)+10*(current.x-target.x)+10*(current.layer-target.layer);

    return h;
}

cell select_source(vector<cell>sources, cell target) // compares between source cells to choose the one closest to the the target
{
    int min_dis=INT_MAX;
    cell best;
    for (int i=0; i<sources.size(); i++) {
        int h=calculateHeuristic(sources[i], target);
        if (h<min_dis) {
            best=sources[i];
            min_dis=h;
        }
    }
    return best;
    
}

vector<pin> findpath(cell source, cell target, cellGrid &dcell, visGrid &dvisit){ // the main A* function
    pin start(source.x,source.y,source.layer,source.id); //the pin of the starting cell
    vector<pin>path;
    path.push_back(start);//inserting the source pin in the path
    vector<cell>openList; // a list that would contain the cells of the path
    openList.push_back(source); //pushing the source cell
    cell temp;
    pin temp1;
    bool destination_found=false;


    cell current =source;

    while(!openList.empty())
    {
        for(int i=0;i<6;i++){ // trying the cells in the 6 differenct directions
            temp.x=current.x+directions[i].x;
            temp.y=current.y+directions[i].y;
            temp.layer= current.layer+directions[i].z;
            if(isValid(temp))
            {
            //dvisit[temp.x][temp.y][temp.z]=1;
            if(current.layer%2==1){ //checking for odd metal layers
                if(isDestination(temp,target)){ //if the destination is the current cell
                    dcell[temp.layer][temp.y][temp.x].id=current.id; //storing the cell in the grid
                    temp1=pin(temp.x,temp.y,temp.layer,temp.id);
                    path.push_back(temp1);
                    destination_found=true;
                     return path;
                }
                else if(dvisit[temp.x][temp.y][temp.layer]==false) //checking if the cell is not visited
                {
                    if(i%3==0)
                        gnew=1;
                    else if(i%3==1)
                        gnew=10;
                    else
                        gnew=10*abs(temp.layer-current.layer);

                    hnew=calculateHeuristic(temp,target);
                    fnew=gnew+hnew;
                    dcell[temp.layer][temp.y][temp.x].f=fnew;
                    if(fnew<min_cost)
                    {
                        mincell=temp;
                        min_cost=fnew;
                        temp1=pin(temp.x,temp.y,temp.layer,temp.id);

                    }

                }



            }
                else
                {
                    if(isDestination(temp,target)){ //even case
                        dcell[temp.layer][temp.y][temp.x].id=current.id;
                        temp1=pin(temp.x,temp.y,temp.layer,temp.id);
                        path.push_back(temp1);
                        destination_found=true;
                         return path;
                    }
                    else if(dvisit[temp.x][temp.y][temp.layer]==false)
                    {
                        if(i%3==0)
                            gnew=10;
                        else if(i%3==1)
                            gnew=1;
                        else
                            gnew=10*abs(temp.layer-current.layer);

                        hnew=calculateHeuristic(temp,target);
                        fnew=gnew+hnew;
                        dcell[temp.layer][temp.y][temp.x].f=fnew;
                        if(fnew<min_cost)
                        {
                            mincell=temp;
                            min_cost=fnew;
                            temp1=pin(temp.x,temp.y,temp.layer,temp.id);

                        }

                    }

                }
            }

        }



        dcell[mincell.x][mincell.y][mincell.layer].id = current.id;
        dvisit[mincell.x][mincell.y][mincell.layer]=1;
        current=mincell;
        openList.pop_back();
        path.push_back(temp1);
        openList.push_back(mincell);

    }


    return path;


}

vector<vector<pin> > mazeRouter(cellGrid &dcell, visGrid &dvisit, net Net) // this function inserts first to pins then do the routing for thrm
                                                                        // then it finds the path of each pin with a vector of perceeding pin
{
    vector<cell>sources;
    pin pin1=Net.pins[0];
    pin pin2=Net.pins[1];
    cell temp;
    cell source(pin1);
    cell target(pin2);
    sources.push_back(source);
    sources.push_back(target);
    
    Net.paths.push_back(findpath(source, target, dcell, dvisit));
           
              
    for (int i=2; i<Net.pins.size()-1; i++) {
        target=cell(Net.pins[i]);
        temp=select_source(sources, target);
        sources.push_back(target);
        
        Net.paths.push_back(findpath(temp, target, dcell, dvisit));
    }
    
    return Net.paths;
    
}



