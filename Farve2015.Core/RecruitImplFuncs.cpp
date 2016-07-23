#include "RecruitImplFuncs.h"
#include "../Farve2015.Core/Node.h"
#include "../Farve2015.Core/Synapse.h"

#include <stdio.h>
#include <string>


// The following class holds information about recruit calls made to a node.
// It is used for slightly more advanced decision-making as to what to do
// when recruit is called for a node multiple times (ie. with no success).
// To avoid infinite loops, we need to catch this and deal with it.
class CNodeRecruitCallHistoryEntry
{
public:
	CNode* m_Node;
	bool   m_DesiredSignallingState;
	time_t m_Time;
};

class CNodeRecruitCallHistory
{
public:
	std::vector<CNodeRecruitCallHistoryEntry*> m_Entries;

public:
	void AddEntry(CNode* node, bool desiredSignallingState)
	{
		CNodeRecruitCallHistoryEntry* newEntry = new CNodeRecruitCallHistoryEntry();		
		//newEntry->m_Time = ();
		newEntry->m_Node = node;
		newEntry->m_DesiredSignallingState = desiredSignallingState;
		m_Entries.push_back(newEntry);
	}
};




//CNodeRecruitCallHistory g_NodeRecruitCallHistory;




void Node_Default_RecruitImpl(CNode* node, bool desiredSignallingState)
{
	printf("%s %s\n", "Recruit for", node->m_ID.c_str());
	if (node->get_IsSignalling() == desiredSignallingState)
	{
		printf("%s\n", "Returning, signalling state == desired signalling state.");
		printf("%s %s\n", "Recruit success? ", (node->get_IsSignalling() == desiredSignallingState ? "YES" : "NO"));
		return;
	}

	//g_NodeRecruitCallHistory.AddEntry(node, desiredSignallingState);

	// If desiredSignallingState is true
	if (desiredSignallingState == true)
	{
		printf("%s\n", "desiredSignallingState == true");

		// If node is inhibited, nothing can make it signal. So we first try to get rid of all inhibitions.
		
		bool bInhibitorDeactivated = false; // Just to track if we did deactivate one or more inhibitors.
		
		printf("%s %s %d %s\n", node->m_ID.c_str(), "has", (int)node->get_Incoming().size(), "inputs.");
		for each (auto input in node->get_Incoming())
		{
			if (input->get_IsSignalling() == true) // We only consider active/signalling synapses.
			{
				printf("%s %s %s\n", "Input", input->m_ID.c_str(), " is signalling.");
				if (input->get_EffectOnOutgoing() == ESynapseEffect::ForceSignallingFalse)
				{
					// If we get here, it means node is being inhibited by (at least) this input.
					printf("%s%s%s%s%s%s\n", node->m_ID.c_str(), " is being inhibited by ", input->m_ID.c_str(), " so calling ", input->get_Incoming()->get_Incoming()->m_ID.c_str(), ".Recruit(false)");
					input->get_Incoming()->get_Incoming()->Recruit(false);
					bInhibitorDeactivated = true;
				}
			}
			else
			{
				printf("%s %s %s\n", "Input", input->m_ID.c_str(), " is not signalling.");
			}
		}

		// If we have no more active inhibitors, then after getting rid of any inhibitors, 
		// does node's signalling state match desiredSignallingState?
		// If so, we are done. If not, we try more mechanisms to make node signalling.
		if ((node->get_IsSignalling() == desiredSignallingState) && (bInhibitorDeactivated == true))
		{
			printf("%s", "Returning. One or more inhibiitor has been deactivated, and now signalling state == desiredSignallingState.");
			printf("%s %s\n", "Recruit success? ", (node->get_IsSignalling() == desiredSignallingState ? "YES" : "NO"));
			return;
		}

		// If we are here, we did not manage to attain desiredSignallingState for node by deactivating
		// active inhibitors. If we did attempt to deactivate active inhibitors, the question is;
		// did we just fail to deactivate all active inhibitors, or do we just not have any active
		// excitors?
		bool bHasActiveExcitors = false;
		bool bHasActiveInhibitors = false;

		for each (auto input in node->get_Incoming())
		{
			if (input->get_IsSignalling() == true) // We only consider active/signalling synapses.
			{
				if (input->get_EffectOnOutgoing() == ESynapseEffect::TrySetSignallingTrue)
				{
					bHasActiveExcitors = true;
				}else if (input->get_EffectOnOutgoing() == ESynapseEffect::ForceSignallingFalse)
				{
					bHasActiveInhibitors = true;
				}

				// Can we bail out of the search early?
				if (bHasActiveExcitors == true && bHasActiveInhibitors == true)
				{
					break;
				}
			}
		}

		// So, do we still have active inhibitors?
		if (bHasActiveInhibitors)
		{
			// We simply must deactivate the active inhibitors, OR we must do something extreme
			// like actually add nodes to make deactivating the inhibitors possible.
			Node_Default_RecruitImpl(node, desiredSignallingState);
		}
		else
		{
			// We have no active inhibitors. This could be enough for node to now be signalling.
			// If that is the case, mission accomplished, we can exit.
			if (node->get_IsSignalling() == desiredSignallingState)
			{
				printf("%s %s\n", "Recruit success? ", (node->get_IsSignalling() == desiredSignallingState ? "YES" : "NO"));
				return;
			}


			// If we have signalling but inactive inputs, then we do an actual EXCON change - we
			// make the input synapse active.
			for each (auto input in node->get_Incoming())
			{
				if ((input->get_EffectOnOutgoing() == ESynapseEffect::Unassigned) && (input->get_IsSignalling() == true))
				{
					input->set_EffectOnOutgoing(ESynapseEffect::TrySetSignallingTrue);
				}
			}

			// If node's signalling state now matches desiredSignallingState, mission
			// accomplished, we can exit.
			if (node->get_IsSignalling() == desiredSignallingState)
			{
				printf("%s %s\n", "Recruit success? ", (node->get_IsSignalling() == desiredSignallingState ? "YES" : "NO"));
				return;
			}


			// If we get here, node has no active TrySetSignallingTrue inputs. So we do Recruit(true)
			// on each inactive input until node's signalling state is desiredSignallingState, or until
			// we have no more inactive inputs to do this for.
			for each (auto input in node->get_Incoming())
			{
				if (input->get_EffectOnOutgoing() == ESynapseEffect::Unassigned)
				{
					if (input->get_Incoming() != nullptr
						&& input->get_Incoming()->get_Incoming() != nullptr)
					{
						input->get_Incoming()->get_Incoming()->Recruit(true);
					}
				}
			}

		}

		
	}
	else // If desiredSignallingState is false
	{

	}


	printf("%s %s\n", "Recruit success? ", (node->get_IsSignalling() == desiredSignallingState ? "YES" : "NO"));
}