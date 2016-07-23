#pragma once
#include "SignallingEntityBase.h"
#include <memory>

/* Forward declarations */
class CNode;
class CSynapse;

class CLink: public CSignallingEntityBase
{
public:
	CLink(std::string id);
	CLink(std::string id, CNode* SourceNode, CSynapse* DestinationSynapse);
	~CLink();

public:	
	CNode* get_Incoming();
	CLink* set_Incoming(CNode* node);
	CLink* unset_Incoming();

	CSynapse* get_Outgoing();
	CLink* set_Outgoing(CSynapse* node);
	CLink* unset_Outgoing();


	CLink* CLink::Connect(CNode * SourceNode, CSynapse * DestinationSynapse);

	

private:
	CNode* m_Incoming;
	CSynapse* m_Outgoing;
};

