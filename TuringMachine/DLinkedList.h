#pragma once
#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <class T>
struct Node {
	Node<T>* next;
	Node<T>* prev;
	T val;
};

template <class T>
class DLinkedList
{
public:
	DLinkedList() {
		head = NULL;
		tail = NULL;
		sz = 0;
	}

	DLinkedList(vector<T> list) {
		DLinkedList();
		for (T item : list) {
			insert(-1, item);
		}
	}

	~DLinkedList() {
		if (sz > 0) {
			Node<T>* node = head;
			while (node != NULL) {
				Node<T>* tmp = node;
				node = node->next;
				delete tmp;
			}
		}
	}

	void insert(int pos, T value) {
		if (pos > sz+1 || pos < sz*-1 - 2 ) {
			printf("Position: %d is not within the bounds of the size: %d\n", pos, sz);
			return;
		}

		// If there is nothing in the list
		if (head == NULL && tail == NULL) {
			Node<T>* n = new Node<T>();
			n->next = NULL;
			n->prev = NULL;
			n->val = value;
			head = n;
			tail = n;
			sz++;
			return;
		}

		// If we are inserting at the beginning
		if (pos == 0) {
			Node<T>* newNode = new Node<T>();
			newNode->next = head;
			newNode->prev = NULL;
			newNode->val = value;
			head->prev = newNode;
			head = newNode;

		}
		// If we are inserting at the end
		else if (pos == -1) {
			Node<T>* newNode = new Node<T>();
			newNode->next = NULL;
			newNode->prev = tail;
			newNode->val = value;
			tail->next = newNode;
			tail = newNode;
		}
		// If we are going forward from the beginning
		else if (pos > 0) {
			// Navigate to the position we want to insert at
			Node<T>* node = head;
			for (int i = 0; i < pos - 1; i++) {
				node = node->next;
			}

			// This is the end of the list
			if (node == tail) {
				Node<T>* newNode = new Node<T>();
				newNode->next = NULL;
				newNode->prev = node;
				newNode->val = value;
				node->next = newNode;
				tail = newNode;
			}
			// This is somewhere between two nodes
			else {
				Node<T>* newNode = new Node<T>();
				newNode->next = node->next;
				newNode->prev = node;
				newNode->val = value;
				node->next->prev = newNode;
				node->next = newNode;
			}
		}
		// If we are going backward from the end
		else {
			// Navigate to the position we want to insert at
			Node<T>* node = tail;
			for (int i = pos + 1; i > 0; i++) {
				node = node->prev;
			}

			// This is the first item in the list
			if (node == head) {
				Node<T>* newNode = new Node<T>();
				newNode->next = head;
				newNode->prev = NULL;
				newNode->val = value;
				head->prev = newNode;
				head = newNode;
			}
			// This is somewhere between two nodes
			else {
				Node<T>* newNode = new Node<T>();
				newNode->next = node;
				newNode->prev = node->prev;
				newNode->val = value;
				node->prev->next = newNode;
				node->prev = newNode;
			}
		}
		sz++;
	}

	void remove(int pos) {
		if (pos > sz || pos < sz*-1 - 1) {
			printf("Position: %d is not within the bounds of the size: %d\n", pos, sz);
			return;
		}

		if (sz == 0) {
			return;
		}
		else if (sz == 1) {
			Node<T>* tmp = head;
			head = NULL;
			tail = NULL;
			delete tmp;
		}

		if (pos == 0) {
			Node<T>* tmp = head;
			head = tmp->next;
			tmp->next->prev = NULL;
			delete tmp;
		}
		else if (pos == -1) {
			Node<T>* tmp = tail;
			tail = tmp->prev;
			tmp->prev->next = NULL;
			delete tmp;
		}
		else if (pos > 0) {
			// Navigate to the position we want to insert at
			Node<T>* tmp = head;
			for (int i = 0; i < pos - 1; i++) {
				tmp = tmp->next;
			}

			// This is the end of the list
			if (tmp == tail) {
				tail = tmp->prev;
				tmp->prev->next = NULL;
				delete tmp;
			}
			// This is somewhere between two nodes
			else {
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				delete tmp;
			}
		}
		else {
			// Navigate to the position we want to insert at
			Node<T>* tmp = tail;
			for (int i = pos + 1; i > 0; i++) {
				tmp = tmp->prev;
			}

			// This is the first item in the list
			if (node == head) {
				head = tmp->next;
				tmp->next->prev = NULL;
				delete tmp;
			}
			// This is somewhere between two nodes
			else {
				tmp->next->prev = tmp->prev;
				tmp->prev->next = tmp->next;
				delete tmp;
			}
		}
		sz--;
	}

	int size() { return sz; }
	
	void print() {
		std::stringstream ss;
		if (sz == 0)
			 ss << "The list is empty" << endl;
		else {
			Node<T>* ptr = head;
			while (ptr->next != NULL) {
				ss << ptr->val << " <-> ";
				ptr = ptr->next;
			}
			ss << ptr->val;
		}
		printf("%s\n", ss.str().c_str());
	}

	void printBackwards() {
		std::stringstream ss;
		if (sz == 0)
			ss << "The list is empty" << endl;
		else {
			Node<T>* ptr = tail;
			while (ptr->prev != NULL) {
				ss << ptr->val << " <-> ";
				ptr = ptr->prev;
			}
			ss << ptr->val;
		}
		printf("%s\n", ss.str().c_str());
	}

protected:
	Node<T>* head;
	Node<T>* tail;
	int sz;
};

#endif