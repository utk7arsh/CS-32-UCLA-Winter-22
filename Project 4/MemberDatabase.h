#ifndef MemDatabase_
#define MemDatabase_

#include <string>
#include <vector>
#include "RadixTree.h"
#include "PersonProfile.h"
#include <iostream>

class MemberDatabase {
public:
	MemberDatabase();
	~MemberDatabase();
	bool LoadDatabase(std::string filename);
	std::vector<std::string>FindMatchingMembers(const AttValPair& input) const;
	const PersonProfile* GetMemberByEmail(std::string email) const;
private:
	RadixTree<PersonProfile*> rtpp;
	std::vector<PersonProfile*> vdel;
	RadixTree<std::vector<std::string>> rtemail;
};
#endif
