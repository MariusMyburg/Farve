/*
*   ComputeIsSignallingImplFuncs.cpp
*   This file contains the function definitions for a set of 'default' methods for computing
*   signalling state.
*/

#include "ComputeIsSignallingImplFuncs.h"
#include "Node.h"
#include "Link.h"
#include "Synapse.h"



bool Node_Default_ComputeIsSignallingImpl(CSignallingEntityBase* entity)
{
	CNode* asNode = static_cast<CNode*>(entity);

	// If asNode has any signalling ForceSignallingFalse inputs, IsSignalling is false.
	for each (auto input in asNode->get_Incoming())
	{
		if ((input->get_IsSignalling() == true) && (input->get_EffectOnOutgoing() == ESynapseEffect::ForceSignallingFalse))
		{
			return false;
		}
	}

	// If we are here, there are no signalling inhibitory synapses.
	// Do we have signalling excitory synapses?
	for each (auto input in asNode->get_Incoming())
	{
		if ((input->get_IsSignalling() == true) && (input->get_EffectOnOutgoing() == ESynapseEffect::TrySetSignallingTrue))
		{
			return true;
		}
	}

	// No signalling excitory or inhibitory inputs. Just return current (manually set) IsSignalling.
	return asNode->get_IsSignalling();
}

bool Link_Default_ComputeIsSignallingImpl(CSignallingEntityBase* entity)
{
	CLink* asLink = static_cast<CLink*>(entity);

	if (asLink->get_Incoming() == nullptr)
	{
		return false;
	}

	return asLink->get_Incoming()->get_IsSignalling();
}

bool Synapse_Default_ComputeIsSignallingImpl(CSignallingEntityBase* entity)
{
	CSynapse* asSynapse = static_cast<CSynapse*>(entity);

	if (asSynapse->get_Incoming() == nullptr)
	{
		return false;
	}

	return asSynapse->get_Incoming()->get_IsSignalling();
}





