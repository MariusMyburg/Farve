#include "IsSignallingChangedImplFuncs.h"
#include "Node.h"
#include "Link.h"
#include "Synapse.h"
#include <iostream>



/*
*  The default handler for Nodes' IsSignallingChanged event.
*  This calls ComputeIsSignalling on all Outgoings.
*/
void Node_Default_IsSignallingChangedImpl(CSignallingEntityBase* entity)
{
	std::cout << "[Node_Default_IsSignallingChangedImpl START] Node " << entity->m_ID.c_str() << " Signalling state changed." << std::endl;
	CNode* asNode = static_cast<CNode*>(entity);

	for each (auto outgoing in asNode->get_Outgoing())
	{
		std::cout <<  "Calling ComputeIsSignalling on " << outgoing->m_ID.c_str() << std::endl;
		//bool preSignalling = outgoing->get_IsSignalling();
		outgoing->ComputeIsSignalling();
		//bool postSignalling = outgoing->get_IsSignalling();
		//if (preSignalling != postSignalling)
		//{
			// 'outgoing's signalling state changed.
			//outgoing->
		//}
	}

	std::cout << "[Node_Default_IsSignallingChangedImpl END] Node " << entity->m_ID.c_str() << " Signalling state changed." << std::endl;
}



void Link_Default_IsSignallingChangedImpl(CSignallingEntityBase* entity)
{
	printf("[Link_Default_IsSignallingChangedImpl START] Link (%s) Signalling state changed.\n", entity->m_ID.c_str());
	CLink* asLink = static_cast<CLink*>(entity);

	
	printf("Calling ComputeIsSignalling on [%s]\n", asLink->get_Outgoing()->m_ID.c_str());
	asLink->get_Outgoing()->ComputeIsSignalling();


	printf("[Link_Default_IsSignallingChangedImpl END] Node (%s) Signalling state changed.\n", entity->m_ID.c_str());
}

void Synapse_Default_IsSignallingChangedImpl(CSignallingEntityBase* entity)
{
	printf("[Synapse_Default_IsSignallingChangedImpl START] Synapse (%s) Signalling state changed.\n", entity->m_ID.c_str());
	CSynapse* asSynapse = static_cast<CSynapse*>(entity);

	if (asSynapse->get_Outgoing() != nullptr)
	{
		printf("Calling ComputeIsSignalling on [%s]\n", asSynapse->get_Outgoing()->m_ID.c_str());
		asSynapse->get_Outgoing()->ComputeIsSignalling();
	}

	printf("[Synapse_Default_IsSignallingChangedImpl END] Synapse (%s) Signalling state changed.\n", entity->m_ID.c_str());
}