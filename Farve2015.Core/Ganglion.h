#pragma once

#include <set>
#include <map>
#include <memory>
#include <string>

#include "..\Farve2015.Core\Delegate.h"
#include "..\Farve2015.Core\Node.h"
#include "..\Farve2015.Core\Link.h"
#include "..\Farve2015.Core\Synapse.h"

#include "RecruitImplFuncs.h"



class CGanglion
{
public:
	CGanglion(std::string name);
	~CGanglion();

	// EVENT FUNCTIONS
private:
	std::vector<std::function<void(CNode* addedNode)>> _OnNodeAdded;
	std::vector<std::function<void(CNode* removedNode)>> _OnNodeRemoved;
	std::vector<std::function<void(CGanglion* addedGanglion)>> _OnGanglionAdded;
	std::vector<std::function<void(CGanglion* removedGanglion)>> _OnGanglionRemoved;
	
public:
	CGanglion* add_OnNodeAddedFunction(std::function<void(CNode* addedNode)> func);
	
	CGanglion* add_OnNodeRemovedFunction(std::function<void(CNode* removedNode)> func);
	CGanglion* add_OnGanglionAddedFunction(std::function<void(CGanglion* addedGanglion)> func);
	CGanglion* add_OnGanglionRemovedFunction(std::function<void(CGanglion* removedGanglion)> func);

	// EVENT FUNCTIONS
		

public:
	std::string get_Name() const;

	CGanglion*	add_Node(std::string id, std::function<void(CNode* node, bool desiredSIgnallingState)> recruitImpl = Node_Default_RecruitImpl);
	CGanglion*	add_Ganglion(std::string name);
	CGanglion*	add_Ganglion_2DSurface(std::string name, int width, int height);

	CNode*		get_LastNode();

	void		remove_Node(CNode* NodeToRemove);
	int			FindNodeIndex(CNode* NodeToFind);

	bool operator ==(CGanglion const &) const;

	//CNode* getNode()

private:
	std::string _Name;
	std::set<CGanglion*> _Ganglions;
	std::map<std::string, CNode> _Nodes;

	CNode* _lastNode;
};

