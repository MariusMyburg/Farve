#include "Node.h"
#include "Synapse.h"
#include "ComputeIsSignallingImplFuncs.h"
#include "IsSignallingChangedImplFuncs.h"

CNode::CNode(std::string id, std::function<void(CNode* node, bool desiredSIgnallingState)> recruitImpl) :
	CSignallingEntityBase(
		id, 
		Node_Default_ComputeIsSignallingImpl, 
		Node_Default_IsSignallingChangedImpl)
{
	_RecruitImpl = recruitImpl;
	_IsSignalling = false;
}

CNode::~CNode()
{
}

const std::vector<CSynapse*> CNode::get_Incoming()
{
	return _Incoming;
}

const std::vector<CLink*> CNode::get_Outgoing()
{
	return _Outgoing;
}

void CNode::Recruit(bool DesiredIsSignalling)
{
	std::string strDesiredSignallingState = (DesiredIsSignalling ? "true" : "false");
	printf("%s%s%s%s%s\n", "Recruit(", strDesiredSignallingState.c_str(), ") called on ", this->m_ID.c_str(), ". Deferring to _RecruitImpl...");
	_RecruitImpl(this, DesiredIsSignalling);
	printf("%s%s%s\n", "Recruit for ", this->m_ID.c_str(), " is done.");
}

CNode*CNode::add_Incoming(std::string id)
{
	CSynapse* newSynapse = new CSynapse(id);	
	newSynapse->set_Outgoing(this);
	_Incoming.push_back(newSynapse);

	return this;
}

CNode* CNode::remove_Incoming(CSynapse* NodeToRemove)
{
	int nodeIndex = FindSynapseIndex(NodeToRemove);
	_Incoming.erase(_Incoming.cbegin() + nodeIndex);
	return this;
}

const int CNode::FindSynapseIndex(CSynapse * synapseToFind)
{
	int idx = 0;
	for each (auto node in _Incoming)
	{
		if (node->m_ID == synapseToFind->m_ID)
		{
			return idx;
		}

		idx++;
	}

	return -1;
}

const CSynapse* CNode::get_LastSynapse()
{
	auto last = _Incoming.cend()-1;
	return *last;
}

CNode*CNode::add_Outgoing(std::string id)
{
	CLink* newLink = new CLink(id);
	_Outgoing.push_back(newLink);

	return this;
}

CNode*CNode::add_Outgoing(CLink* outgoing)
{	
	_Outgoing.push_back(outgoing);

	return this;
}

CNode* CNode::remove_Outgoing(CLink* LinkToRemove)
{
	int nodeIndex = FindLinkIndex(LinkToRemove);
	if (nodeIndex != -1)
	{
		_Outgoing.erase(_Outgoing.cbegin() + nodeIndex);
	}
	return this;
}

const int CNode::FindLinkIndex(CLink* linkToFind)
{
	int idx = 0;
	for each (auto node in _Outgoing)
	{
		if (node->m_ID == linkToFind->m_ID)
		{
			return idx;
		}

		idx++;
	}

	return -1;
}


CNode* CNode::ConnectTo(CNode* otherNode)
{
	// Find an available synapse in otherNode to connect to. If one is not found,
	// create a new one. Then create a Link, and connect this node to the synapse
	// in otherNode.
	CSynapse* targetSynapse = nullptr;

	// Try to find existing unused synapse.
	for each (CSynapse* existingSynapse in otherNode->get_Incoming())
	{
		if (existingSynapse->get_Incoming() == nullptr)
		{
			targetSynapse = existingSynapse;
			break;
		}
	}

	// If one is not found, create a new one.
	if (targetSynapse == nullptr)
	{
		std::string strNewSynapseID = this->m_ID + "->" + otherNode->m_ID;
		auto lastSynapse = otherNode->add_Incoming(strNewSynapseID)->get_LastSynapse();
		targetSynapse = const_cast<CSynapse*>(lastSynapse);
	}

	
	// Create a Link and connect this node to targetSynapse.
	std::string strNewLinkID = this->m_ID + "->" + otherNode->m_ID;
	CLink* newLink = new CLink(strNewLinkID, this, targetSynapse);

	return this;
}