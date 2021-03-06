﻿#include "stdafx.h"

#include "Tape.h"
#include "TuringMachine.h"

TuringMachine::TuringMachine(set<string> sts, set<string> iA, set<string> tA, set<string> transitionFunctions, string is, set<string> finalStates)
{
	for (auto state : sts) {
		if (state == is) {
			states.insert(new State(state, true));
			initialState = state;
		}
		else if (finalStates.find(state) != finalStates.end())
			states.insert(new State(state, false, true));
		else
			states.insert(new State(state));
	}

	inputAlphabet = iA;
	tapeAlphabet = tA;

	// We also need to include NULL in the alphabet in case we are looking for nothing in our tape spot
	tapeAlphabet.insert("");

	for (string fn : transitionFunctions) {
		vector<string> args = splitString(fn, ", ");
		if (!validateFunction(args))
			continue;
		
		State* s = findState(args[0]);
		TransitionFunction* func = new TransitionFunction();
		func->read = args[1][0];
		func->nextState = args[2];
		func->write = args[3][0];
		func->direction = args[4][0];
		s->addTransitionFunction(func);
	}
}


TuringMachine::~TuringMachine()
{
	for (auto state : states) {
		delete state;
	}
}

bool TuringMachine::run(string input) {
	if (input == "") {
		printf("Blank strings are not allowed\n");
		return false;
	}

	Tape tape = Tape(vector<char>(input.begin(), input.end()));
	tape.print();
	printf("\n");
	State* state = findState(initialState);
	TransitionFunction* func = state->getFunction(tape.getReadVal());
	while (func != NULL) {
		printf("delta(%s, %c) = (%s, %c, %c)\n", state->getName().c_str(), func->read, func->nextState.c_str(), func->write, func->direction);
		tape.operate(func->read, func->write, func->direction);
		state = findState(func->nextState);
		if (state == NULL)
			break;
		tape.print();
		printf("\n");
		func = state->getFunction(tape.getReadVal());
	}

	printf("last state is %s\n", state->getName().c_str());
	if (state->isFinal())
		return true;
	return false;
}

State* TuringMachine::findState(string name) {
	for (auto state : states) {
		if (state->getName().compare(name) == 0)
			return state;
	}
	return NULL;
}

bool TuringMachine::validateFunction(vector<string> args) {
	bool result = true;
	if (findState(args[0]) == NULL) {
		printf("The rule \"(%s, %s) = (%s, %s, %s)\" is invalid because the initial state is not in this machine\n", args[0].c_str(), args[1].c_str(), args[2].c_str(), args[3].c_str(), args[4].c_str());
		result = false;
	}

	if (tapeAlphabet.find(args[1]) == tapeAlphabet.end()) {
		printf("The rule \"(%s, %s) = (%s, %s, %s)\" is invalid because the read is not in the tape Alphabet\n", args[0].c_str(), args[1].c_str(), args[2].c_str(), args[3].c_str(), args[4].c_str());
		result = false;
	}

	if (findState(args[2]) == NULL) {
		printf("The rule \"(%s, %s) = (%s, %s, %s)\" is invalid because the next state is not in this machine\n", args[0].c_str(), args[1].c_str(), args[2].c_str(), args[3].c_str(), args[4].c_str());
		result = false;
	}

	if (tapeAlphabet.find(args[3]) == tapeAlphabet.end()) {
		printf("The rule \"(%s, %s) = (%s, %s, %s)\" is invalid because the write is not in the tape Alphabet\n", args[0].c_str(), args[1].c_str(), args[2].c_str(), args[3].c_str(), args[4].c_str());
		result = false;
	}
	
	if (args[4].compare("L") != 0 && args[4].compare("R") != 0) {
		printf("The rule \"(%s, %s) = (%s, %s, %s)\" is invalid because the direction is not \"L\" or \"R\"\n", args[0].c_str(), args[1].c_str(), args[2].c_str(), args[3].c_str(), args[4].c_str());
		result = false;
	}

	return result;
}
