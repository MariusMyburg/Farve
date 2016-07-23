///////////////////////////////////////////////////////////
// A System takes an input and upon evaluation, produces 
// a pattern of activation in an output Ganglion.

#pragma once

//#include "SignallingEntityBase.h"
#include "Ganglion.h"

template<typename InputType>
class CSystem
{
private:
	InputType m_Input;
	CGanglion* m_ptrGanglion;

public:
	//CSystem<InputType>::CSystem(InputType);
	//CSystem(InputType input);
	//~CSystem();
	CSystem(InputType param)
	{
		m_Input = param;
		m_ptrGanglion = new CGanglion("Output");
	}

	~CSystem()
	{
	}


	InputType get_Input() const
	{
		return m_Input;
	}

	CGanglion* get_Output() const
	{
		return m_ptrGanglion;
	}
	

	// Takes the input and calculates activations
	// of output Ganglion Nodes.
	virtual void Evaluate() = 0;
};

