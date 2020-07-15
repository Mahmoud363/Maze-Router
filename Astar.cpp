<<<<<<< HEAD
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
        h=abs(current.x-target.x)+10*(current.y-target.y)+10*(current.layer-target.layer);
    else
        h=abs(current.y-target.y)+10*(current.x-target.x)+10*(current.layer-target.layer);
    
    return h;
}

vector<pin> findpath(cell source, cell target, cellGrid dcell, visGrid dvisit){
    pin start(source.x,source.y,source.layer,source.id);
    vector<pin>path;
    path.push_back(start);
    vector<cell>openList;
    openList.push_back(source);
    cell temp;
    pin temp1;
    bool destination_found=false;
    
    
    cell current =source;
    
    while(!openList.empty())
    {
        for(int i=0;i<6;i++){
            temp.x=current.x+directions[i].x;
            temp.y=current.y+directions[i].y;
            temp.layer= current.layer+directions[i].z;
            if(isValid(temp))
            {
            //dvisit[temp.x][temp.y][temp.z]=1;
            if(current.layer%2==1){
                if(isDestination(temp,target)){
                    dcell[temp.x][temp.y][temp.layer].id=current.id;
                    temp1(temp.x,temp.y,temp.layer,temp.id);
                    path.push_back(temp1);
                    destination_found=true;
                     return path;
                }
                else if(dvisit[temp.x][temp.y][temp.z]==false)
                {
                    if(i%3==0)
                        gnew=1;
                    else if(i%3==1)
                        gnew=10;
                    else
                        gnew=10*abs(temp.layer-current.layer);
                    
                    hnew=calculateHeuristic(temp,target);
                    fnew=gnew+hnew;
                    dcell[temp.x][temp.y][temp.layer].f=fnew;
                    if(fnew<min_cost)
                    {
                        mincell=temp;
                        min_cost=fnew;
                        temp1(temp.x,temp.y,temp.layer,temp.id);
                        
                    }
                        
                }
                
                   
        
            }
                else
                {
                    if(isDestination(temp,target)){
                        dcell[temp.x][temp.y][temp.layer].id=current.id;
                        temp1(temp.x,temp.y,temp.layer,temp.id);
                        path.push_back(temp1);
                        destination_found=true;
                         return path;
                    }
                    else if(dvisit[temp.x][temp.y][temp.z]==false)
                    {
                        if(i%3==0)
                            gnew=10;
                        else if(i%3==1)
                            gnew=1;
                        else
                            gnew=10*abs(temp.layer-current.layer);
                        
                        hnew=calculateHeuristic(temp,target);
                        fnew=gnew+hnew;
                        dcell[temp.x][temp.y][temp.layer].f=fnew;
                        if(fnew<min_cost)
                        {
                            mincell=temp;
                            min_cost=fnew;
                            temp1(temp.x,temp.y,temp.layer,temp.id);
                            
                        }
                            
                    }
                    
                }
            }
            
        }
        
        mincell=current;
        
        dcell[mincell.x][mincell.y][mincell.layer].id = current.id;
        openList.pop_back();
        path.push_back(temp1);
        openList.push_back(mincell);
        
    }
    
    
    return path;
    

}
=======
#include "AStar.h"
#include <algorithm>

using namespace std::placeholders;

bool AStar::Vec2i::operator == (const Vec2i& coordinates_)
{
    return (x == coordinates_.x && y == coordinates_.y);
}

AStar::Vec2i operator + (const AStar::Vec2i& left_, const AStar::Vec2i& right_)
{
    return{ left_.x + right_.x, left_.y + right_.y };
}

AStar::Node::Node(Vec2i coordinates_, Node* parent_)
{
    parent = parent_;
    coordinates = coordinates_;
    G = H = 0;
}

AStar::uint AStar::Node::getScore()
{
    return G + H;
}

AStar::Generator::Generator()
{
    setDiagonalMovement(false);
    setHeuristic(&Heuristic::manhattan);
    direction = {
        { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
        { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }
    };
}

void AStar::Generator::setWorldSize(Vec2i worldSize_)
{
    worldSize = worldSize_;
}

void AStar::Generator::setDiagonalMovement(bool enable_)
{
    directions = (enable_ ? 8 : 4);
}

void AStar::Generator::setHeuristic(HeuristicFunction heuristic_)
{
    heuristic = std::bind(heuristic_, _1, _2);
}

void AStar::Generator::addCollision(Vec2i coordinates_)
{
    walls.push_back(coordinates_);
}

void AStar::Generator::removeCollision(Vec2i coordinates_)
{
    auto it = std::find(walls.begin(), walls.end(), coordinates_);
    if (it != walls.end()) {
        walls.erase(it);
    }
}

void AStar::Generator::clearCollisions()
{
    walls.clear();
}

AStar::CoordinateList AStar::Generator::findPath(Vec2i source_, Vec2i target_)
{
    Node* current = nullptr;
    NodeSet openSet, closedSet;
    openSet.reserve(100);
    closedSet.reserve(100);
    openSet.push_back(new Node(source_));

    while (!openSet.empty()) {
        auto current_it = openSet.begin();
        current = *current_it;

        for (auto it = openSet.begin(); it != openSet.end(); it++) {
            auto node = *it;
            if (node->getScore() <= current->getScore()) {
                current = node;
                current_it = it;
            }
        }

        if (current->coordinates == target_) {
            break;
        }

        closedSet.push_back(current);
        openSet.erase(current_it);

        for (uint i = 0; i < directions; ++i) {
            Vec2i newCoordinates(current->coordinates + direction[i]);
            if (detectCollision(newCoordinates) ||
                findNodeOnList(closedSet, newCoordinates)) {
                continue;
            }

            uint totalCost = current->G + ((i < 4) ? 10 : 14);

            Node* successor = findNodeOnList(openSet, newCoordinates);
            if (successor == nullptr) {
                successor = new Node(newCoordinates, current);
                successor->G = totalCost;
                successor->H = heuristic(successor->coordinates, target_);
                openSet.push_back(successor);
            }
            else if (totalCost < successor->G) {
                successor->parent = current;
                successor->G = totalCost;
            }
        }
    }

    CoordinateList path;
    while (current != nullptr) {
        path.push_back(current->coordinates);
        current = current->parent;
    }

    releaseNodes(openSet);
    releaseNodes(closedSet);

    return path;
}

AStar::Node* AStar::Generator::findNodeOnList(NodeSet& nodes_, Vec2i coordinates_)
{
    for (auto node : nodes_) {
        if (node->coordinates == coordinates_) {
            return node;
        }
    }
    return nullptr;
}

void AStar::Generator::releaseNodes(NodeSet& nodes_)
{
    for (auto it = nodes_.begin(); it != nodes_.end();) {
        delete* it;
        it = nodes_.erase(it);
    }
}

bool AStar::Generator::detectCollision(Vec2i coordinates_)
{
    if (coordinates_.x < 0 || coordinates_.x >= worldSize.x ||
        coordinates_.y < 0 || coordinates_.y >= worldSize.y ||
        std::find(walls.begin(), walls.end(), coordinates_) != walls.end()) {
        return true;
    }
    return false;
}

AStar::Vec2i AStar::Heuristic::getDelta(Vec2i source_, Vec2i target_)
{
    return{ abs(source_.x - target_.x),  abs(source_.y - target_.y) };
}

AStar::uint AStar::Heuristic::manhattan(Vec2i source_, Vec2i target_)
{
    auto delta = std::move(getDelta(source_, target_));
    return static_cast<uint>(10 * (delta.x + delta.y));
}

AStar::uint AStar::Heuristic::euclidean(Vec2i source_, Vec2i target_)
{
    auto delta = std::move(getDelta(source_, target_));
    return static_cast<uint>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

AStar::uint AStar::Heuristic::octagonal(Vec2i source_, Vec2i target_)
{
    auto delta = std::move(getDelta(source_, target_));
    return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
}
>>>>>>> parent of 6771202... Merge branch 'master' of https://github.com/Mahmoud363/Maze-Router
