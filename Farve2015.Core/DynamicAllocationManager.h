#pragma once

#include "..\Farve2015.Core\Delegate.h"
#include "..\Farve2015.Core\Node.h"
#include "..\Farve2015.Core\Link.h"
#include "..\Farve2015.Core\Synapse.h"
#include "..\Farve2015.Core\Ganglion.h"

class CDynamicAllocationManager
{
public:
	CDynamicAllocationManager(CGanglion* ptrRootGanglion);
	~CDynamicAllocationManager();
};

