#pragma once
#include "IOLayer.h"
#include <vector>

class IOBlock
{
public:
	IOBlock();
	~IOBlock();

private:
	std::vector<IOLayer*> m_Layers;
};

