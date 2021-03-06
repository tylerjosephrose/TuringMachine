// TuringMachine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DLinkedList.h"
#include "TuringMachine.h"

int main()
{
	set<string> states = { "q0", "q1", "q2", "q3", "q4" };
	set<string> inputAlphabet = { "a", "b" };
	set<string> tapeAlphabet = { "a", "b", "x", "y" };
	set<string> transitionFunctions = {
		"q0, a, q1, x, R",
		"q0, y, q3, y, R",
		"q1, a, q1, a, R",
		"q1, y, q1, y, R",
		"q1, b, q2, y, L",
		"q2, a, q2, a, L",
		"q2, y, q2, y, L",
		"q2, x, q0, x, R",
		"q3, y, q3, y, R",
		"q3, , q4, , L"
	};
	string initialState = "q0";
	set<string> finalStates = { "q4" };
	TuringMachine* m = new TuringMachine(states, inputAlphabet, tapeAlphabet, transitionFunctions, initialState, finalStates);

	string test = "aaaaaaaaaaaabbbbbbbbbbbb";
	if (m->run(test))
		printf("%s is accepted\n", test.c_str());
	else
		printf("%s is rejected\n", test.c_str());

	system("pause");
    return 0;
}

