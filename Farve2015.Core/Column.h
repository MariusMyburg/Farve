#pragma once
#include "Ganglion.h"

class CColumn
{
public:
	CColumn();
	~CColumn();

	CColumn* Create(CGanglion* Parent, std::string ColumnName, int NumberOfLayers, int SquareRootOfNumberOfNodesPerColumnLayerSheet);
	
};

