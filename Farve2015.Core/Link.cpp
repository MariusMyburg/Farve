#include "Link.h"
#include "ComputeIsSignallingImplFuncs.h"
#include "IsSignallingChangedImplFuncs.h"
#include "Node.h"
#include "Synapse.h"


CLink::CLink(std::string id) : CSignallingEntityBase(
	id, 
	Link_Default_ComputeIsSignallingImpl,
	Link_Default_IsSignallingChangedImpl)
{
	_IsSignalling = false;
}

CLink::CLink(std::string id, CNode* SourceNode, CSynapse* DestinationSynapse) : 
	CSignallingEntityBase(id, 
	Link_Default_ComputeIsSignallingImpl,
	Link_Default_IsSignallingChangedImpl)
{
	m_Incoming= SourceNode;
	m_Outgoing= DestinationSynapse;

	_IsSignalling = false;

	Connect(m_Incoming, m_Outgoing);
}

CLink::~CLink()
{
}

CNode* CLink::get_Incoming()
{
	return m_Incoming;
}

CLink * CLink::set_Incoming(CNode * node)
{
	m_Incoming = node;
	ComputeIsSignalling();
	return this;
}

CLink* CLink::unset_Incoming()
{
	m_Incoming->remove_Outgoing(this);
	ComputeIsSignalling();
	return this;
}

CSynapse * CLink::get_Outgoing()
{
	return m_Outgoing;
}

CLink * CLink::set_Outgoing(CSynapse * node)
{
	m_Outgoing = node;
	m_Outgoing->ComputeIsSignalling();
	return this;
}

CLink* CLink::unset_Outgoing()
{
	m_Outgoing->unset_Incoming();
	m_Outgoing->ComputeIsSignalling();
	return this;
}

CLink* CLink::Connect(CNode * SourceNode, CSynapse * DestinationSynapse)
{
	printf("%s %s %s %s %s %s\n", "Connecting", SourceNode->m_ID.c_str(), "to", DestinationSynapse->get_Outgoing()->m_ID.c_str(), "via", DestinationSynapse->m_ID.c_str());
	unset_Incoming();
	unset_Outgoing();

	//m_Incoming = SourceNode;
	//m_Outgoing = DestinationSynapse;
	SourceNode->add_Outgoing(this);
	set_Incoming(SourceNode);
	set_Outgoing(DestinationSynapse);
	DestinationSynapse->set_Incoming(this);
	
	printf("%s %s %s %s %s %s\n", "Done connecting", SourceNode->m_ID.c_str(), "to", DestinationSynapse->get_Outgoing()->m_ID.c_str(), "via", DestinationSynapse->m_ID.c_str());
	return this;
}
