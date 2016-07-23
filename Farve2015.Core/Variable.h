#pragma once
#include <string>

class CVariable
{
public:
	CVariable();
	~CVariable();


private:
	std::string m_VariableName;
	std::string m_VariableValue;
};

