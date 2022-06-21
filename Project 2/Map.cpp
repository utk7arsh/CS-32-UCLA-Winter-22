#include "Map.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Map::Map() {
	map_size = 0;				//default constructor
	head = nullptr;
	tail = nullptr;
}

Map::~Map() {
	if (head == nullptr)
		return;					//in case the linked list is empty

	Node* p = head;	
	Node* next_del;				//this pointer will point to the element to be deleted

	while (p != nullptr) {
		next_del = p->next;		//moves to the next element
		delete p;				//deleting the pointer to the previous element
		p = next_del;			//now p points to the next element
	}
	p = nullptr;
}

Map::Map(const Map& other) {
	map_size = 0;	//changing the size of map

	if (other.head == nullptr) {
		head = nullptr;
		tail = nullptr;
		map_size = 0;		//if other is empty
	}
	else {
		/*head = new Node;
		tail = new Node;*/
		head = nullptr;
		tail = nullptr;
		for (int i = 0; i < other.size(); i++) {
			KeyType k1;
			ValueType v1;
			other.get(i, k1, v1);		//get the pair from other
			insert(k1, v1);			//insert the key/value pair
		}
	}
}

Map& Map::operator=(const Map& rhs) {
	if (this != &rhs) {
		Map temp(rhs);	
		this->swap(temp);				//this swaps the temp and this while making no changes to rhs
	}
	return*this;
}


bool Map::empty() const {
	return (map_size == 0);				//map_size private member stores this return value
}

int Map::size() const {
	return map_size;					//indicating size of the list
}

bool Map::insert(const KeyType& key, const ValueType& value) {
	if (contains(key)) {			//if already contains return false
		return false;
	}

	Node* newNode = new Node;		//dynamically allocating the key/value to a new node
	newNode->m_key = key;
	newNode->m_value = value;

	if (map_size == 0) {			
		newNode->m_key = key;
		newNode->m_value = value;
		newNode->next = nullptr;	//when size is zero we add the first pair by
		newNode->prev = nullptr;	//setting its prev and next to null

		head = newNode;				//now both head and tail point to the first pair
		tail = newNode;

		map_size++;
		return true;
	}

	for (Node* p = head; p != nullptr; p = p->next) {	//traversing through each element to find the position to place the new pair
														//insert is presorting the data
		if (p != nullptr && p->m_key > newNode->m_key) { //this means that new item can be added in the front
			newNode->next = p;							//first pair assigned to the next of NEW first pair
			head = newNode;								//head points to the NEW first pair
			newNode->prev = nullptr;					//prev to first pair is null
			newNode->next->prev = newNode;				//p(old first pair)'s prev pointer now points to the NEW first pair
			map_size++;
			return true;
		}
		else if (p!= nullptr && p->m_key < newNode->m_key) {			//belongs after p
			if (p->next != nullptr && p->next->m_key > newNode->m_key) {//and before p->next
				newNode->next = p->next;		//newmode coming in between p and p->next
				p->next = newNode;				
				newNode->prev = p;
				newNode->next->prev = newNode;//p's next should be newnode and p's next's previous should be newnode
				map_size++;
				return true;
			}
			else if (p->next == nullptr) {		//in case the loop reaches the last pair
				p->next = newNode;				//newnode coming after p
				newNode->prev = p;
				newNode->next = nullptr;		//last pair so next to it should be null
				tail = newNode;					//new point of pointing for tail
				map_size++;
				return true;
			}
		}
	}
	return true;
}

void Map::dump() {
	Node* p;
	p = head;
	while (p != nullptr) {				//classic style of printing all the pairs of linked lists
		cerr << "Key " << p->m_key << " Value: " << p->m_value << endl;
		cerr << "Previous: " << p->prev << " Next: " << p->next << endl;
		cerr << "---------------------" << endl;
		p = p->next;
	}
}


bool Map::update(const KeyType& key, const ValueType& value) {
	for (Node* p = head; p != nullptr; p = p->next) {
		if (p!= nullptr && p->m_key == key) {
			p->m_value = value;
			return true;
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
	Node* newNode = new Node;		//dynamically allocating the key/value to a new node
	newNode->m_key = key;
	newNode->m_value = value;

	if (map_size == 0) {
		newNode->m_key = key;
		newNode->m_value = value;
		newNode->next = nullptr;	//when size is zero we add the first pair by
		newNode->prev = nullptr;	//setting its prev and next to null

		head = newNode;				//now both head and tail point to the first pair
		tail = newNode;

		map_size++;
		return true;
	}

	for (Node* p = head; p != nullptr; p = p->next) {
		if (p != nullptr && p->m_key == key) {
			p->m_value = value;
			return true;
		}
	}

	for (Node* p = head; p != nullptr; p = p->next) {
		if (p != nullptr && p->m_key > newNode->m_key) {
			newNode->next = p;
			head = newNode;
			newNode->prev = nullptr;
			newNode->next->prev = newNode;
			map_size++;
			return true;
		}
		else if (p != nullptr && p->m_key < newNode->m_key) {
			if (p->next != nullptr && p->next->m_key > newNode->m_key) {
				newNode->next = p->next;
				p->next = newNode;
				newNode->prev = p;
				newNode->next->prev = newNode;//p's next should be newnode and p's next's previous should be newnode
				map_size++;
				return true;
			}
			else if (p->next == nullptr) {
				p->next = newNode;
				newNode->prev = p;
				newNode->next = nullptr;
				tail = newNode;
				map_size++;
				return true;
			}
		}
	}
	return true;
}

bool Map::erase(const KeyType& key) {
	if (!contains(key)) {
		return false;
	}

	if (head == nullptr) return false; //nothing can be deleted so return false

	if (head->m_key == key) {		//if the first key matches the key that needs to be deleted
		Node* killme = head;
		head = killme->next;		//head now points to the second key/value pair
		delete killme;				//deleting first element
		map_size--;
		return true;
	}

	Node* p = head;
	for (; p != nullptr; p = p->next) {
		if (p!= nullptr && p->m_key == key) {		//traversing through list to find the occurance 
			break;									//key and pointing p to that pair
		}
	}
	if (p != nullptr) {
		if (p->next == nullptr) {					//if it the last pair of the list
			p->prev->next = nullptr;				//p's prev will be last pair and its next would be null
			tail = p->prev;							// tail now points to p->prev
			delete p;
			map_size--;
			return true;				//revise once again
		}
		else {					//its somewhere in the middle
			Node* killme = p;
			p->prev->next = killme->next;	//p's prev's next would now point to p's next
			p->next->prev = killme->prev;	//same for the reverse logic
			delete killme;					//finally delete that pair
			map_size--;
			return true;
		}
	}
	return true;
}

bool Map::contains(const KeyType& key) const {
	for (Node* p = head; p != nullptr; p = p->next) {
		if (p != nullptr && p->m_key == key) {		//if key matches while traversing the list 
			return true;						//key found
		}
	}
	return false;								//key not found
}

bool Map::get(const KeyType& key, ValueType& value) const {

	for (Node* p = head; p != nullptr; p = p->next) {
		if (p != nullptr && p->m_key == key) {
			value = p->m_value;			//same logic as contains if found the same key
			return true;				//on this occasion, change the value
		}
	}
	return false;					//if key not found in the list
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
	if (i < 0 || i >= map_size) {			//insuring i is in the legal range
		return false;
	}
	int counter = 0;		//this represents the position of the pair in the list (starting from 0)
	for (Node* p = head; p != nullptr; p = p->next) {
		if (counter == i) {			//pair to be matched found
			key = p->m_key;
			value = p->m_value;
			return true;
		}
		counter++;					//incrementing to check the entire list
	}
	return true;
}

void Map::swap(Map& other) {	//logic in this function is to exchange the heads and tails so that entire content of this can be
								//approached by other and vice versa.
	int temp_size = map_size;		//exchanging the map_size
	map_size = other.map_size;
	other.map_size = temp_size;

	Node* temp_head = head;			//exchanging the head
	head = other.head;
	other.head = temp_head;

	Node* temp_tail = tail;			//exchanging the tail
	tail = other.tail;
	other.tail = temp_tail;
}

bool merge(const Map& m1, const Map& m2, Map& result) {
	bool retValue = true;
	result = m1;		//m1 is the foundation for the result

	for (int i = 0; i < m2.size(); i++) {
		KeyType ins_k;
		ValueType ins_v;
		m2.get(i, ins_k, ins_v);		//access each pair of m2
		if (result.insert(ins_k, ins_v) == 0) {			//if ins_k is already in result/m1, in case its true it is safely inserted in result
			ValueType check_v;							//check if the Value is different
			result.get(ins_k, check_v);					//store the Value in result of that Key into a new variable
			if (ins_v != check_v) {						//if result Value and the m2 Value are not the same erase it from result
				result.erase(ins_k);
				retValue = false;		//false is only to be returned when clash of same key, different values occurs
			}
		}
	}
	return retValue;
}

void reassign(const Map& m, Map& result) {		//the function in this algorithm is to transfer all the values to the next
	result = m;									//key and pass the last value to the first key (that ensures all values are changed)

	KeyType k_ini;
	ValueType v_ini;
	m.get(0, k_ini, v_ini);						//taking the first key/value pair
	ValueType assignment = v_ini;				//assigment will hold the value that would replace the value in the subsequent keys
												//first pair is done seperately as its value needs to replaced by value of the last pair which cannot be 
												//possible according to the loop given below
	for (int i = 1; i < m.size(); i++) {
		KeyType k1;
		ValueType v1;
		m.get(i, k1, v1);					//starting from pair 2, key/value will be accessed
		result.update(k1, assignment);		//the key will take the value of previous key's value
		assignment = v1;					//assignement will take new key's value which later would replace next pair's value
	}
	result.update(k_ini, assignment);		//finally first key will take last value of assigment tht is the value of the last pair
}