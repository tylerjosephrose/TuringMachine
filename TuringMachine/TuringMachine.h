#pragma once
#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <set>
#include <string>

#include "State.h"

using namespace std;

class TuringMachine
{
public:
	TuringMachine(set<string> states, set<string> inputAlphabet, set<string> tapeAlphabet, set<string> transitionFunctions, string initialState, set<string> finalStates);
	~TuringMachine();

	bool run(string input);

private:
	set<State*> states;
	set<string> inputAlphabet;
	set<string> tapeAlphabet;
	string initialState;

	State* findState(string name);
	bool validateFunction(vector<string> args);

	vector<string> splitString(string input, string delimiter) {
		vector<string> result;
		size_t pos;
		string token;
		while ((pos = input.find(delimiter)) != string::npos) {
			result.push_back(input.substr(0, pos));
			input.erase(0, pos + delimiter.length());
		}
		result.push_back(input);
		return result;
	}
};

#endif