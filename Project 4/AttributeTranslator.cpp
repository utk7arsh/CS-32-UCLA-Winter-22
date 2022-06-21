#include "AttributeTranslator.h"
#include <fstream>
#include <iostream>
#include <sstream>

AttributeTranslator::AttributeTranslator() {

}

AttributeTranslator::~AttributeTranslator() {
	for (int i = 0; i < dest_vec.size(); i++) {
		delete dest_vec[i];			//dynamically allocated variable vector
	}
}

bool AttributeTranslator::Load(std::string filename) {
	std::string line;
	std::string source;
	std::ifstream infile(filename);
	if (infile) {
		while (getline(infile, line)) {
			AttValPair* atv = nullptr;
			if (!line.empty()) {				//avoids empty lines
				std::string a1; std::string a2;
				std::istringstream iss(line);
				getline(iss, a1, ','); getline(iss, a2, ',');

				source = a1 + ',' + a2;		//source means the first pair in a sentence
				std::vector<AttValPair*>* p = rtat.search(source);
				if (p == nullptr) {
					std::vector<AttValPair*> temp;
					for (;;) {
						std::string a3;
						std::string a4;
						if (!getline(iss, a3, ',')) {
							break;
						}
						getline(iss, a4, ',');
						atv = new AttValPair(a3, a4);
						temp.push_back(atv);		//adding new pair to the temp vector 
						dest_vec.push_back(atv);	//adding to destruct later
					}
					rtat.insert(source, temp);		//finally inserts into radix
				}
				else {								//when that source already exists
					for (;;) {
						std::string a3;
						std::string a4;
						if (!getline(iss, a3, ',')) {
							break;
						}
						getline(iss, a4, ',');
						atv = new AttValPair(a3, a4);
						std::string atv_s = a3 + ',' + a4;	
						p->push_back(atv);
						dest_vec.push_back(atv);
					
					}
					rtat.insert(source, *p);		//finally inserting a pair's all compatibles to Radix
				}
			}
		}
		infile.close();
	}
	else {
		return false;
	}
	return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
	std::string combination = source.attribute + ',' + source.value;
	std::vector<AttValPair> temp;
	std::vector<AttValPair*>* trial = rtat.search(combination);
	if (rtat.search(combination) == nullptr) {
		return temp;		//empty vector
	}
	else {
		for (int i = 0; i < trial->size(); i++) {
			temp.push_back(*((*trial)[i]));
		}
		return temp;
	}
}