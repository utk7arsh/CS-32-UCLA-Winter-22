#ifndef MatchMaker_
#define MatchMaker_
#include <vector>
#include <iostream>
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "provided.h"

class MatchMaker {
public:
	MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
	~MatchMaker();
	std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
	const MemberDatabase* mdb_mm;
	const AttributeTranslator* at_mm;

};
#endif


