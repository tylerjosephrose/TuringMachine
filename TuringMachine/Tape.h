#pragma once
#ifndef TAPE_H
#define TAPE_H

#include "DLinkedList.h"

class Tape : public DLinkedList<char>
{
public:
	Tape(vector<char> list) : DLinkedList(list) {
		ptr = head;
	}

	bool operate(char read, char write, char dir) {
		if (ptr->val == read) {
			ptr->val = write;
			if (dir == 'L') {
				// If our next ptr is NULL then we will add a node there with no value in it
				if (ptr->prev == NULL) {
					insert(0, '\0');
				}
				ptr = ptr->prev;
			}
			else {
				// If our next ptr is NULL then we will add a node there with no value in it
				if (ptr->prev == NULL) {
					insert(-1, '\0');
				}
				ptr = ptr->next;
			}
		}
		return false;
	}

	char getReadVal() { return ptr->val; }

	void print() {
		std::stringstream ss;
		if (sz == 0)
			ss << "The list is empty" << endl;
		else {
			Node<char>* n = head;
			while (n->next != NULL) {
				if (n == ptr)
					ss << "*";
				ss << n->val << " | ";
				n = n->next;
			}
			if (n == ptr)
				ss << "*";
			ss << n->val;
		}
		printf("%s\n", ss.str().c_str());
	}

private:
	Node<char>* ptr;
};

#endif