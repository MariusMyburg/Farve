#include "Synapse.h"
#include "ComputeIsSignallingImplFuncs.h"
#include "IsSignallingChangedImplFuncs.h"
#include "Node.h"




CSynapse::CSynapse(std::string id) : CSignallingEntityBase(
	id, 
	Synapse_Default_ComputeIsSignallingImpl,
	Synapse_Default_IsSignallingChangedImpl)
{
	m_ID = id;	
	_IsSignalling = false;
	m_Incoming = nullptr;
	m_Outgoing = nullptr;
}


CSynapse::~CSynapse()
{
}

CSynapse * CSynapse::set_Incoming(CLink * link)
{
	m_Incoming = link;
	ComputeIsSignalling();
	return this;
}

CSynapse * CSynapse::unset_Incoming()
{
	this->m_Incoming = nullptr;
	ComputeIsSignalling();
	return this;
}

CSynapse*CSynapse::set_Outgoing(CNode * node)
{
	if (get_Outgoing() != nullptr)
	{
		printf_s("%s", "Unable to attach, unset_Outgoing must be called first.");
	}

	m_Outgoing = node;
	m_Outgoing->ComputeIsSignalling();
	return this;
}

CSynapse*CSynapse::unset_Outgoing()
{
	if (get_Outgoing() == nullptr)
	{
		printf_s("%s", "unset_Outgoing is not required, ContainingNode is not set.");
	}
	else
	{
		get_Outgoing()->remove_Incoming(this);
	}

	return this;
}

CNode*CSynapse::get_Outgoing() const
{
	return m_Outgoing;
}

void CSynapse::set_EffectOnOutgoing(ESynapseEffect newEffect)
{
	if (get_EffectOnOutgoing() != newEffect)
	{
		printf("%s%s%s%s.\n", "Synapse ", m_ID.c_str(), " effect changed. Forcing ComputeIsSignalling on ", get_Outgoing()->m_ID.c_str());
		m_EffectOnOutgoing = newEffect;
		get_Outgoing()->ComputeIsSignalling();
	}
}

CLink*CSynapse::get_Incoming() const
{
	return m_Incoming;
}

