#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//#include "../LinkedList/LinkedList.h"

template <typename T>
class LinkedList {

public:
	struct Node {
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
	};

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	unsigned int nodeCount;

public:
	//behaviors
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;
	
	//accessors
	unsigned int NodeCount() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;

	//Insertion
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	//removal
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	void Clear();

	//operators
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList<T>& rhs) const;

	//constructors
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList<T>& operator=(const LinkedList<T>& rhs);
	~LinkedList();
};

template <typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	tail = nullptr;
	nodeCount = 0;
}

template <typename T> //copy constructor
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	nodeCount = 0;
	for (unsigned int i = 0; i < (list.nodeCount); i++) {
		AddTail((list.GetNode(i)->data));
	}
}

template <typename T> //copy assignment
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& rhs) { 
	Clear();
	nodeCount = 0;
	for (unsigned int i = 0; i < (rhs.nodeCount); i++) {
		AddTail(rhs.GetNode(i)->data);
	}
	return *this;
}

template <typename T> //destructor
LinkedList<T>::~LinkedList() {
	Clear();
}

template <typename T>
void LinkedList<T>::PrintForward() const {
	Node* temp = head;
	for (unsigned int i = 0; i < nodeCount; i++) {
		cout << temp->data << endl;
		temp = temp->next;
	}
	delete temp;
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
	Node* temp = tail;
	for (unsigned int i = nodeCount; i > 0; i--) {
		cout << temp->data << endl;
		temp = temp->prev;
	}
	delete temp;
}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
	return nodeCount;
}

template <typename T>
void LinkedList<T>::AddHead(const T& data) {
	Node* newHead = new Node();
	newHead->data = data;
	if (head == nullptr) {
		head = newHead;
		tail = newHead;
	}
	else {
		newHead->next = head;
		head->prev = newHead;
		head = newHead;
	}
	nodeCount++;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
	Node* newTail = new Node();
	newTail->data = data;
	if (head == nullptr) {
		head = newTail;
		tail = newTail;
	}
	else {
		newTail->prev = tail;
		tail->next = newTail;
		tail = newTail;
	}
	nodeCount++;
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
	for (unsigned int i = (count - 1); i > 0; i--) {
		AddHead(data[i]);
	}
	AddHead(data[0]);
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
	for (unsigned int i = 0; i < count; i++) {
		AddTail(data[i]);
	}
}

template <typename T> 
typename LinkedList<T>::Node* LinkedList<T>::Head(){
	return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
	return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
	return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
	return tail;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
	if (index > nodeCount) {
		throw out_of_range("Error: Index is out of range.");
	}
	else {
		Node* temp = head;
		unsigned int _index = 0;
		while (_index != index) {
			temp = temp->next;
			_index++;
		}
		return temp;
	}
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
	if (index > nodeCount) {
		throw out_of_range("Error: Index is out of range.");
	}
	else {
		Node* temp = head;
		unsigned int _index = 0;
		while (_index != index) {
			temp = temp->next;
			_index++;
		}
		return temp;
	}
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
	Node* temp = head;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (index > nodeCount) {
			throw std::out_of_range("Error: Index is out of range.");
		}
		else {
			if (i == index) {
				return (temp->data);
			}
			else {
				temp = temp->next;
			}
		}
	}
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
	Node* temp = head;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (temp->data == data) {
			return temp;
		}
		else {
			temp = temp->next;
		}
	}
	return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
	Node* temp = head;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (temp->data == data) {
			return temp;
		}
		else {
			temp = temp->next;
		}
	}
	return nullptr;
}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
	Node* temp = head;
	Node* output = nullptr;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (temp->data == value) {
			output = temp;
			outData.push_back(output);
			temp = temp->next;
			output = nullptr;
		}
		else {
			temp = temp->next;
		}
	}
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
	unsigned int ans = 0;
	if (nodeCount == rhs.nodeCount) {
		for (unsigned int i = 0; i < nodeCount; i++) {
			if ((GetNode(i)->data) == rhs.GetNode(i)->data) {
				ans++;
			}
		}
		if (ans == nodeCount) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
	nodeCount++;
	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = node;
	newNode->prev = node->prev;
	node->prev->next = newNode;
	node->prev = newNode;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
	nodeCount++;
	Node* newNode = new Node;
	newNode->data = data;
	newNode->prev = node;
	newNode->next = node->next;
	node->next->prev = newNode;
	node->next = newNode;
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
	if (index > nodeCount) {
		throw out_of_range("Index is out of range.");
	}
	else if (index == nodeCount) {
		AddTail(data);
	}
	else if (index == 0) {
		AddHead(data);
	}
	else {
		nodeCount++;
		Node* newNode = new Node;
		newNode->data = data;
		newNode->prev = GetNode(index)->prev;
		newNode->next = GetNode(index);
		if (GetNode(index)->prev == nullptr) {
			head = newNode;
		}
		else {
			GetNode(index)->prev->next = newNode;
		}
		GetNode(index)->prev = newNode;
	}
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
	unsigned int index = 0;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (GetNode(i) == node) {
			index = i;
			break;
		}
	}
	for (unsigned int j = index; j < nodeCount; j++) {
		cout << GetNode(j)->data << endl;
	}
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
	unsigned int index = 0;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (GetNode(i) == node) {
			index = i;
			break;
		}
	}
	for (unsigned int j = index; j > 0; j--) {
		cout << GetNode(j)->data << endl;
	}
	cout << GetNode(0)->data << endl;
}

template <typename T>
bool LinkedList<T>::RemoveHead() {
	Node* temp = head;
	if (head == nullptr) {
		delete temp;
		return false;
	}
	else if(head->next == nullptr){
		nodeCount--;
		delete temp;
		head = nullptr;
		tail = nullptr;
		return true;
	}
	else {
		nodeCount--;
		head->next->prev = nullptr;
		head = head->next;
		delete temp;
		return true;
	}
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
	Node* temp = tail;
	if (tail == nullptr) {
		delete temp;
		return false;
	}
	else if(tail->prev == nullptr){
		nodeCount--;
		delete temp;
		tail = nullptr;
		head = nullptr;
		return true;
	}
	else {
		nodeCount--;
		tail->prev->next = nullptr;
		tail = tail->prev;
		delete temp;
		return true;
	}
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
	if (index > nodeCount) {
		return false;
	}
	Node* temp = GetNode(index);
	if (temp == nullptr) {
		return false;
	}
	else if (temp->next == nullptr) {
		temp->prev->next = nullptr;
	}
	else if (temp->prev == nullptr) {
		temp->next->prev = nullptr;
	}
	else {
		temp->prev->next = GetNode(index)->next;
		temp->next->prev = GetNode(index)->prev;
	}
	delete temp;
	nodeCount--;
	return true;
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
	int x = -1;
	unsigned int ans = 0;
	Node* temp = head;
	while (temp->next != nullptr) {
		x++;
		if (temp->data == data) {
			ans++;
			temp = temp->next;
			RemoveAt(x);
			x--;
		}
		else {
			temp = temp->next;
		}
	}
	return ans;
}

template <typename T>
void LinkedList<T>::Clear() {
	Node* temp1 = head;
	Node* temp = nullptr;
	while (temp1 != nullptr) {
		temp = temp1->next;
		delete temp1;
		temp1 = temp;
	}
	nodeCount = 0;
	head = nullptr;
	tail = nullptr;
}