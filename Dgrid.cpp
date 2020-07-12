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