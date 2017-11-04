#ifndef INPUT_CALLBACK_SHARDLITE
#define INPUT_CALLBACK_SHARDLITE

#include "MappedInput.h"

#include <iostream>

// =======================================
// BASE FUNCTION CALLBACK CLASS
// =======================================
class IInputCallback
{
public:
	virtual ~IInputCallback() {};

	virtual void operator() (MappedInput& mappedInput) = 0;
};

// =======================================
// MEMBER FUNCTION CALLBACK CLASS
// =======================================
template <class ClassType>
class InputCallbackMember : public IInputCallback
{
public:
	InputCallbackMember() {}
	explicit InputCallbackMember(ClassType* in_classPointer, void (ClassType::*in_inputCallbackFunc)(MappedInput&));
	~InputCallbackMember() {}

	void operator() (MappedInput& mappedInput);

	void SetArgs(ClassType* in_classPointer, void (ClassType::*in_inputCallbackFunc)(MappedInput&));

public:
	void (ClassType::*m_eventCallbackFunc)(MappedInput&);
	ClassType* m_classPointer;
};

template <class ClassType>
InputCallbackMember<ClassType>::InputCallbackMember(ClassType* in_classPointer, void (ClassType::*inEventCallbackFunc)(MappedInput&)) :
	m_classPointer(in_classPointer),
	m_eventCallbackFunc(inEventCallbackFunc)
{
	assert(m_classPointer && m_eventCallbackFunc);
}

template <class ClassType>
void InputCallbackMember<ClassType>::SetArgs(ClassType* in_classPointer, void (ClassType::*in_inputCallbackFunc)(MappedInput&))
{
	m_classPointer = in_classPointer;
	m_eventCallbackFunc = in_inputCallbackFunc;

	assert(m_classPointer && m_eventCallbackFunc);
}

template <class ClassType>
void InputCallbackMember<ClassType>::operator() (MappedInput& mappedInput)
{
	(m_classPointer->*m_eventCallbackFunc)(mappedInput);
}

// =======================================
// FREE FUNCTION CALLBACK CLASS
// =======================================
class InputCallbackFree : public IInputCallback
{
public:
	InputCallbackFree() {}
	explicit InputCallbackFree(void(*in_eventCallbackFunc)(MappedInput&)) { m_eventCallbackFunc = in_eventCallbackFunc; }
	~InputCallbackFree() {}

	void operator() (MappedInput& mappedInput);

	void SetArgs(void(*in_inputCallbackFunc)(MappedInput&));

public:
	void(*m_eventCallbackFunc)(MappedInput&);
};

#endif //include guard