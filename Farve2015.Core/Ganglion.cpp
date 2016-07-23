#include "Ganglion.h"
#include <memory>
using namespace std;




CGanglion::CGanglion(std::string name)
{
	_Name = name;
	//_Ganglions = std::make_unique<std::set<CGanglion>>(*(new std::set<unique_ptr<CGanglion>>()));
}


CGanglion::~CGanglion()
{
}

CGanglion * CGanglion::add_OnNodeAddedFunction(std::function<void(CNode*addedNode)> func)
{
	_OnNodeAdded.push_back(func);
	return this;
}

CGanglion * CGanglion::add_OnNodeRemovedFunction(std::function<void(CNode*removedNode)> func)
{
	_OnNodeRemoved.push_back(func);
	return this;
}

std::string CGanglion::get_Name() const
{
	return _Name;
}

bool CGanglion::operator ==(CGanglion const &) const
{
	return false;
}

CGanglion* CGanglion::add_Node(std::string id, std::function<void(CNode* node, bool desiredSIgnallingState)> recruitImpl)
{
	CNode* newN = new CNode(id, recruitImpl);	
	_Nodes.insert_or_assign(id, *newN);
	

	_lastNode = newN;

	for each(auto func in _OnNodeAdded)
	{
		func(newN);
	}

	return this;
}


CNode* CGanglion::get_LastNode()
{
	auto last = _lastNode;// _Nodes.end() - 1;
	return last;
}

void CGanglion::remove_Node(CNode* NodeToRemove)
{
	//int nodeIndex = FindNodeIndex(NodeToRemove);
	_Nodes.erase(NodeToRemove->m_ID);
}

//int CGanglion::FindNodeIndex(CNode * NodeToFind)
//{
//	int idx = 0;
//	for each (auto node in _Nodes)
//	{
//		if (node->m_ID == NodeToFind->m_ID)
//		{
//			return idx;
//		}
//
//		idx++;
//	}
//
//	return -1;
//}

CGanglion*	CGanglion::add_Ganglion(std::string name)
{
	CGanglion* newG = new CGanglion(name);
	_Ganglions.insert(newG);
	return newG;
}

CGanglion* CGanglion::add_Ganglion_2DSurface(std::string name, int width, int height)
{
	CGanglion* newG = new CGanglion(name);
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			char buf[255];
			_itoa(x + (y * height), buf, 10);
			newG->add_Node(buf);
		}
	}
		
	_Ganglions.insert(newG);

	return newG;
}
