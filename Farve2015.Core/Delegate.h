#pragma once
#include <functional>
#include <vector>

class CDelegate
{
private:
	std::vector<std::function<void()>> funcs;

public:
	CDelegate();
	~CDelegate();
	

	void operator+ (std::function<void()> func)
	{
		funcs.push_back(func);
	}

	CDelegate& operator+= (std::function<void()> func)
	{
		funcs.push_back(func);
		return *this;
	}

	
	void operator()()
	{
		for each (auto f in funcs)
		{
			f();
		}
	}
};

