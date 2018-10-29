#include "stdafx.h"
#include "State.h"


State::State(string n, bool i, bool f)
{
	name = n;
	initialState = i;
	finalState = f;
}


State::~State()
{
	for (auto func : functions) {
		delete func;
	}
}

void State::addTransitionFunction(TransitionFunction* func)
{
	functions.insert(func);
}

TransitionFunction* State::getFunction(char read) {
	for (set<TransitionFunction*>::iterator it = functions.begin(); it != functions.end(); it++) {
		if ((*it)->read == read) {
			return (*it);
		}
	}
	return NULL;
}
