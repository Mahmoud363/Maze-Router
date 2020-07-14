#pragma once

#include "Headers.h"

class Dgrid
{
public:
	Dgrid(int const& layers,  netList const& net);
	cellGrid getCellGrid();
	visGrid getVisitedGrid();
	void findpath(netList& nets);
	~Dgrid();

private:
	bool isValid(cell current);
	bool isDestination(cell current, cell dest);
	int calculateHeuristic(cell current, cell target);
	void clearGrids(cell start, cell target, net& nets);
	mypq_type pqueue;
	cellGrid Dcells;
	visGrid Dvisited;
};

