#pragma once
#include "SignallingEntityBase.h"
#include "Link.h"

class CNode;

enum ESynapseEffect
{
	Unassigned,
	ForceSignallingFalse,
	TrySetSignallingTrue,
	InduceRecruit
};

class CSynapse: public CSignallingEntityBase
{
public:
	CSynapse(std::string id);
	~CSynapse();

	CSynapse*set_Incoming(CLink* link);
	CSynapse*unset_Incoming();
	
	CSynapse*set_Outgoing(CNode* node);
	CSynapse*unset_Outgoing();	

public:
	CLink*get_Incoming() const;
	CNode*get_Outgoing() const;

	ESynapseEffect get_EffectOnOutgoing() const
	{
		return m_EffectOnOutgoing;
	}

	void set_EffectOnOutgoing(ESynapseEffect newEffect);


private:
	CLink* m_Incoming;
	CNode* m_Outgoing;
	ESynapseEffect m_EffectOnOutgoing = ESynapseEffect::Unassigned;
};

