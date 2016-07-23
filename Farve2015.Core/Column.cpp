#include "Column.h"
#include <string>
#include <iostream>
using namespace std;


CColumn::CColumn()
{
}


CColumn::~CColumn()
{
}

CColumn* CColumn::Create(CGanglion* Parent, std::string ColumnName, int NumberOfLayers, int SquareRootOfNumberOfNodesPerColumnLayerSheet)
{
	if (Parent == nullptr)
	{
		Parent = new CGanglion(ColumnName + "Ganglion");
	}

	char buffer[10];

	auto column = Parent->add_Ganglion(ColumnName);

	for (int layer = 0; layer < NumberOfLayers; layer++)
	{
		sprintf(buffer, "%i", layer);
		std::string strLayerName = "Layer" + std::string(buffer);
		auto layerSurfaceGanglion = column->add_Ganglion_2DSurface(strLayerName, SquareRootOfNumberOfNodesPerColumnLayerSheet, SquareRootOfNumberOfNodesPerColumnLayerSheet);

		cout << "Layer " << layer << " / " << NumberOfLayers << " created." << endl;
	}


	return this;
}

