#pragma once
#include "Delegate.h"
#include <functional>


//#define SAFE(type) std::shared_ptr<type>
//#define MAKESAFE(type) std::make_shared<type>

//#define empty_signallingchanged_event ([](CSignallingEntityBase* entity) { /* Do nothing */ printf("%s Signalling state changed.", entity->m_ID); })


class CSignallingEntityBase
{
public:
	CSignallingEntityBase(std::string id, std::function<bool(CSignallingEntityBase* entity)> ComputeIsSignallingImpl,
		std::function<void(CSignallingEntityBase* entity)> _OnSignallingChanged/* = empty_signallingchanged_event*/);
	~CSignallingEntityBase();

	/* Private Variables */
protected:
	bool _IsSignalling { false };

	std::vector<std::function<void(CSignallingEntityBase* entity)>> _OnSignallingChanged;

	/* Public Property Methods */
public:
	std::string m_ID;

	CSignallingEntityBase* add_OnSignallingChangedFunction(std::function<void(CSignallingEntityBase* entity)> func);
	
	virtual void set_IsSignalling(bool newIsSIgnalling);
	virtual bool get_IsSignalling();


	
	bool operator == (CSignallingEntityBase const &) const;

	void ComputeIsSignalling();

	/* Private Methods */
private:
	std::function<bool(CSignallingEntityBase* entity)> _ComputeIsSignallingImpl;
};





