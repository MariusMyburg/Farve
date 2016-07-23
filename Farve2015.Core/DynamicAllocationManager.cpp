#include "DynamicAllocationManager.h"
#include <iostream>



CDynamicAllocationManager::CDynamicAllocationManager(CGanglion * ptrRootGanglion)
{
	ptrRootGanglion->add_OnNodeAddedFunction(
		[](CNode* node)
	{
		std::cout << "Dynamic Allocation Manager detected that Node " << node->m_ID.c_str() << " was added." << std::endl;
		node->add_OnSignallingChangedFunction([](CSignallingEntityBase* node)
		{
			std::cout << "Dynamic Allocation Manager detected that Node " << node->m_ID.c_str() << " IsSignalling state changed." << std::endl;

			// TODO: Add logic to handle dynamic allocation based on signalling state change.
			//ptrRootGanglion->add_Node(std::string("") + std::string(""));
		});
	}
	);
}

CDynamicAllocationManager::~CDynamicAllocationManager()
{
}
