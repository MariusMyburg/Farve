#include "SignallingEntityBase.h"



CSignallingEntityBase::CSignallingEntityBase(std::string id, std::function<bool(CSignallingEntityBase* entity)> computeIsSignallingImpl,
	std::function<void(CSignallingEntityBase* entity)> onSignallingChanged)
{
	m_ID = id;
	_ComputeIsSignallingImpl = computeIsSignallingImpl;
	_OnSignallingChanged.push_back(onSignallingChanged);
	
}




CSignallingEntityBase::~CSignallingEntityBase()
{
}


CSignallingEntityBase * CSignallingEntityBase::add_OnSignallingChangedFunction(std::function<void(CSignallingEntityBase* entity)> func)
{
	_OnSignallingChanged.push_back(func);
	return this;
}

bool CSignallingEntityBase::operator ==(CSignallingEntityBase const &other) const
{
	long long thisaddr = (long long)this;
	long long otheraddr = (long long)&other;
	return (thisaddr == otheraddr);
}



void CSignallingEntityBase::set_IsSignalling(bool newIsSIgnalling)
{
	if (get_IsSignalling() != newIsSIgnalling)
	{
		_IsSignalling = newIsSIgnalling;

		for each (auto func in _OnSignallingChanged)
		{
			func(this);
		}		
	}
}

bool CSignallingEntityBase::get_IsSignalling()
{	
	return _IsSignalling;
}

void CSignallingEntityBase::ComputeIsSignalling()
{
	set_IsSignalling(_ComputeIsSignallingImpl(this));
}
