#ifndef Radix
#define Radix

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

template <typename ValueType>
struct RadixNode {
	std::string key;
	ValueType* val;
	bool end;		//denotes end of word
	RadixNode* child[128];		//children
	std::string child_s[128];	//string stored in children
	RadixNode() {
		for (int i = 0; i < 128; i++)
			child[i] = nullptr;
	}
	~RadixNode() {}
};

template<typename ValueType>
void ClearAllNodes(RadixNode<ValueType>* x) {
	if (x == nullptr)
		return;
	for (int i = 0; i < 128; i++) {
		ClearAllNodes(x->child[i]);
	}
	delete x;
	x = nullptr;
}

template <typename ValueType>
class RadixTree {
public:
	RadixTree() {
		root = new RadixNode<ValueType>;
	}

	~RadixTree() {
		ClearAllNodes(root);
		for (int i = 0; i < deletions.size(); i++) {
			delete deletions[i];
		}
	}

	void insert(std::string key, const ValueType& value);
	ValueType* search(std::string key) const;

private:
	RadixNode<ValueType>* root;
	std::vector<ValueType*> deletions;

	void Rad_Ins(RadixNode<ValueType>* rn, std::string s, ValueType& v) {
		if (s.empty()) {
			rn->end = true;
			rn->val = &(v);		//assigned value type at the end of the string
			return;
		}
		int ch = s[0];
		if (rn->child[ch] == nullptr) {
			rn->child[ch] = new RadixNode<ValueType>;
			rn->child[ch]->key = s;
			rn->child_s[ch] = s;
			Rad_Ins(rn->child[ch], "", v);		//in case of a complete new branch of word
			return;
		}
		std::string transit = rn->child_s[ch];
		int matching = 0;
		while (matching < std::min(transit.length(), s.length()) && transit[matching] == s[matching]) {
			matching++;
		}
		if (matching == transit.length()) {
			Rad_Ins(rn->child[ch], s.substr(matching), v); //part of s that matching in multiple strings is taken as one rad_ins
		}
		else if (matching == s.length()) {			//this time entire transition string is matching with s
			RadixNode<ValueType>* rNode = new RadixNode<ValueType>;
			rNode->child[transit[matching]] = rn->child[ch];
			rNode->child_s[transit[matching]] = transit.substr(matching);
			rn->child[ch] = rNode;
			rn->child_s[ch] = s;
			Rad_Ins(rn->child[ch], "", v);
		}
		else {
			RadixNode<ValueType>* Rnode = new RadixNode<ValueType>;
			Rnode->child[transit[matching]] = rn->child[ch];
			Rnode->child_s[transit[matching]] = transit.substr(matching);
			rn->child[ch] = Rnode;									//this covers the case where a word is partially "matching" with existing word in the start 
			rn->child_s[ch] = s.substr(0, matching);				//but branches out towards end of word
			Rad_Ins(rn->child[ch], s.substr(matching), v);
		}
	}

	ValueType* Rad_LookFor(RadixNode<ValueType>* Rn, std::string s) const {
		if (s.empty()) {
			return Rn->val;						//base case of recursion to return value
		}
		int ch = s[0];
		if (Rn->child[ch] == nullptr) {
			return nullptr;						//when the first letter branch doesnt exist
		}

		std::string transit;
		transit = Rn->child_s[ch];
		int min_len = std::min(transit.length(), s.length());
		if (transit.substr(0, min_len) != s.substr(0, min_len)) {
			return  nullptr;				//does not match
		}
		if (transit.length() == min_len) {
			return Rad_LookFor(Rn->child[ch], s.substr(transit.length()));	//word is matched till min_len
		}
		else {
			return nullptr;
		}
	}
};

template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value) {
	ValueType* vall = new ValueType;
	deletions.push_back(vall);
	*vall = value;
	Rad_Ins(root, key, *vall);
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const {
	return Rad_LookFor(root, key);
}

#endif
//
// Fake RADIX IMPLEMENTATION
//#ifndef Radix
//#define Radix
//
//#include <string>
//#include <vector>
//#include <map>
//
//template <typename ValueType>
//class RadixTree {
//public:
//	RadixTree();
//	~RadixTree();
//	void insert(std::string key, const ValueType& value);
//	ValueType* search(std::string key) const;
//
//private:
//	std::map<std::string, ValueType> radmap;
//	std::map<std::string, ValueType>* pmap;
//	/*struct Node {
//		Node() :m_char(' ') {}
//		Node(char ch) : m_char(ch) {}
//		~Node() {}
//		char m_char;
//		vector<ValueType> m_value;
//		vector<Node*> m_children;
//	};
//	Node* root;*/
//	//void deleter(Node* current);
//
//
//};
//
//template <typename ValueType>
//inline
//RadixTree<ValueType>::RadixTree() {
//	pmap = &(radmap);
//}
//
//template <typename ValueType>
//inline
//RadixTree<ValueType>::~RadixTree() {
//
//}
//
//template <typename ValueType>
//inline
//void RadixTree<ValueType>::insert(std::string key, const ValueType& value) {
//	radmap[key] = value;
//}
//
//template <typename ValueType>
//inline
//ValueType* RadixTree<ValueType>::search(std::string key) const {
//	typename std::map<std::string, ValueType>::iterator it;
//	it = pmap->find(key);
//	if (it == pmap->end()) {
//		return nullptr;
//	}
//	return &(it->second);
//}
//
//#endif