#ifndef Personprof
#define Personprof

#include "provided.h"
#include "RadixTree.h"
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

class PersonProfile {
public:
	PersonProfile(std::string name, std::string email);
	~PersonProfile();
	std::string GetName() const;
	std::string GetEmail() const;
	void AddAttValPair(const AttValPair& attval);
	int GetNumAttValPairs() const;
	bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
	std::string m_name;
	std::string m_email;
	RadixTree<std::unordered_set<std::string>> rt;
	std::vector<AttValPair> pp;
};

#endif