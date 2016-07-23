#pragma once
#include "SignallingEntityBase.h"
#include "RecruitImplFuncs.h"

#include <vector>
#include <memory>

class CSynapse;
class CLink;




class CNode: public CSignallingEntityBase
{
	/* Public Methods */
public:
	void Recruit(bool DesiredIsSignalling);

	CNode*add_Incoming(std::string id);
	CNode*remove_Incoming(CSynapse* toRemove);
	const int FindSynapseIndex(CSynapse * synapseToFind);

	CNode*add_Outgoing(std::string id);
	CNode*remove_Outgoing(CLink* toRemove);
	const int FindLinkIndex(CLink* linkToFind);

	CNode*add_Outgoing(CLink* outgoing);	

	const CSynapse*get_LastSynapse();

	/* Constructor and destructor */
	CNode(std::string id, std::function<void(CNode* node, bool desiredSIgnallingState)> recruitImpl = Node_Default_RecruitImpl);
	~CNode();

	CNode* ConnectTo(CNode* otherNode);

	const std::vector<CSynapse*> get_Incoming();
	const std::vector<CLink*> get_Outgoing();

	


private:
	std::vector<CSynapse*> _Incoming;
	std::vector<CLink*> _Outgoing;

	std::function<void(CNode* node, bool desiredSIgnallingState)> _RecruitImpl;
};

