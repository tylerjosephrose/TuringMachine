#pragma once
#ifndef STATE_H
#define STATE_H

#include <set>
#include <string>
#include <vector>

using namespace std;

struct TransitionFunction {
	char read;
	char write;
	char direction;
	string nextState;
};

class State
{
public:
	State(string n, bool initial = false, bool final = false);
	~State();

	void setInitial() { initialState = true; }
	void setFinal() { finalState = true; }

	void addTransitionFunction(TransitionFunction* func);

	string getName() { return name; }

	set<TransitionFunction*> getFunctions() { return functions; }

	TransitionFunction* getFunction(char read);

	bool isFinal() { return finalState; }

private:
	bool initialState;
	bool finalState;
	string name;
	set<TransitionFunction*> functions;
};

#endif