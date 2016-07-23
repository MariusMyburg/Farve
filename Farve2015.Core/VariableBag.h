#pragma once
#include <vector>
#include "Variable.h"

class CVariableBag
{
public:
	CVariableBag();
	~CVariableBag();


private:
	std::vector<CVariable> m_Variables;
};

