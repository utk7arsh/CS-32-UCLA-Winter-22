#include "MatchMaker.h"
#include <unordered_set>
#include "RadixTree.h"
#include <vector>
#include <map>
#include <algorithm>


MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at){
	mdb_mm = &mdb;
	at_mm = &at;
}

MatchMaker::~MatchMaker() {
}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
	const PersonProfile* tempman = mdb_mm->GetMemberByEmail(email);

	std::vector<EmailCount> output_vector;			//output
	std::vector<AttValPair> compatiblepairs;		//final vector with compatibles
	std::map<std::string, int> emailcounts;			//all emails with their counters

	for (int i = 0; i < tempman->GetNumAttValPairs(); i++) {
		AttValPair atv;
		tempman->GetAttVal(i, atv);
		std::vector<AttValPair> compatibleAttvals = at_mm->FindCompatibleAttValPairs(atv);
		for (auto j = compatibleAttvals.begin(); j != compatibleAttvals.end(); j++) {
			if(std::find(compatiblepairs.begin(), compatiblepairs.end(), *j) == compatiblepairs.end())
			compatiblepairs.push_back(*j);					//stores all the attval pairs of the input person
		}
	}
	
	for (int k = 0; k < compatiblepairs.size(); k++) {
		std::vector<std::string> temp_compatibleperson = mdb_mm->FindMatchingMembers(compatiblepairs[k]);	//findingmatchingmembers returns a vector of email addresses of all the people with the matching attval pair
		for (int j = 0; j < temp_compatibleperson.size(); j++) {											//vector with compatible email ids which we get from mdb
			std::map<std::string, int>::iterator it;
			it = emailcounts.find(temp_compatibleperson[j]);
			if (it == emailcounts.end()) {
				emailcounts[temp_compatibleperson[j]] = 1;			//inserting a new compatible person
			}	
			else {
				it->second++;										//person already exists so we increment counter
			}	
		}
	}

	struct sorter
	{
		inline bool operator() (const EmailCount& first, const EmailCount& second)
		{
			if (first.count > second.count) //first sort on the basis of num_matches
				return true;
			if (first.count < second.count)
				return false;
			return first.email < second.email; //then sort on the basis of num_emails
		}
	} Sorter;

	std::map<std::string, int>::iterator it;
	for (it = emailcounts.begin(); it != emailcounts.end(); it++) {
		EmailCount ec(it->first, it->second);
		if (it->second >= threshold && it->first != tempman->GetEmail())
			output_vector.push_back(ec);
	}
	std::sort(output_vector.begin(), output_vector.end(), Sorter);		//sorting using a self created algorithm
	return output_vector;
}