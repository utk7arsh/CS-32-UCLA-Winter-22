#ifndef AttrTranslate
#define AttrTranslate
#include <string>
#include <vector>
#include "RadixTree.h"
#include "provided.h"

class AttributeTranslator {
public:
	AttributeTranslator();
	~AttributeTranslator();
	bool Load(std::string filename);
	std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
	RadixTree<std::vector<AttValPair*>> rtat;
	std::vector<AttValPair*> dest_vec;
};
#endif