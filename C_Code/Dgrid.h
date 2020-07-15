#pragma once

#include "Headers.h"

class Dgrid
{
public:
	Dgrid(int const& layers,  netList const& net);
	cellGrid getCellGrid();
	visGrid getVisitedGrid();
	~Dgrid();

private:
	cellGrid Dcells;
	visGrid Dvisited;
};

