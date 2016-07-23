#pragma once
#include <unordered_map>
#include "Node.h"
#include "VariableBag.h"


class CNodeHasher
{
public:
	std::size_t operator()(const CNode &node)
	{
		return 0;
	}
};


// Manages the per-node setting and getting of arbitrary variables.
// TODO.
class VariableBagManager
{
public:
	VariableBagManager();
	~VariableBagManager();

private:
	std::unordered_map<CNode, CVariableBag, CNodeHasher> m_VariableBagPerNode_Map;
};

