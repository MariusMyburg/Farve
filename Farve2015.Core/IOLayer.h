#pragma once
#include "Node.h"
#include <vector>
class IOLayer
{
public:
	IOLayer();
	~IOLayer();

public:


private:
	std::vector<CNode*> m_InputNodes;
	std::vector<CNode*> m_OutputNodes;

	// TODO:
	// Implement a 'Connectivity Strategy'.
};

