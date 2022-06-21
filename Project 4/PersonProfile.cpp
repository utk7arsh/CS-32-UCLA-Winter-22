#include "PersonProfile.h"


PersonProfile::PersonProfile(std::string name, std::string email) {
	m_name = name;
	m_email = email;
}

PersonProfile::~PersonProfile() {}

std::string PersonProfile::GetName() const {
	return m_name;
}

std::string PersonProfile::GetEmail() const {
	return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval) {
	std::unordered_set<std::string>* p = rt.search(attval.attribute);
	if (p != nullptr) {				//attribute exists
		if (p->find(attval.value) == p->end()) {
			p->insert(attval.value);
			pp.push_back(attval);
			return;
		}
		else
			return;					//means an identical attval is attempted to insert
	}
	std::unordered_set<std::string> trial;
	trial.insert(attval.value);
	rt.insert(attval.attribute, trial);	
	pp.push_back(attval);
}

int PersonProfile::GetNumAttValPairs() const {
	return pp.size();			//vector of all attval pairs return the correct size
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
	if (attribute_num < 0 || attribute_num >= GetNumAttValPairs())
		return false;
	attval = pp[attribute_num];	//shallow copy
	return true;
}
