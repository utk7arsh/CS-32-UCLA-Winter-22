#include "MemberDatabase.h"
#include <fstream>
#include <sstream>


MemberDatabase::MemberDatabase() { }
MemberDatabase::~MemberDatabase() {
    for (int i = 0; i < vdel.size(); i++) {
        delete vdel[i];
    }
}

bool MemberDatabase::LoadDatabase(std::string filename) {
    std::string line;
    std::ifstream infile(filename);
    int check = 0;
    if (infile) {
        std::string email; std::string name;
        PersonProfile* psp = nullptr;
        while (getline(infile, line)) {
            if (!line.empty()) {
                if (check == 0) {
                    name = line;
                    check++;
                }
                else if (check == 1) {
                    email = line;
                    if (rtpp.search(email) != nullptr) {        //stops duplicate emails
                        return false;
                    }
                    check++;
                }
                else if (check == 2) {
                    psp = new PersonProfile(name, email);           
                    rtpp.insert(email, psp);
                    vdel.push_back(psp);                    //this vector needs to be deleted in the destructor
                    check++;
                }
                else {
                    std::string at; std::string vl;
                    std::istringstream iss(line);
                    getline(iss, at, ','); getline(iss, vl, ',');
                    AttValPair attv(at, vl);            //making a attval pair using getline
                    psp->AddAttValPair(attv);

                    std::string attvalstring = at + ',' + vl;
                    std::vector<std::string>* p = rtemail.search(attvalstring);
                    if (p == nullptr) {
                        std::vector<std::string> temp;
                        temp.push_back(email);          
                        rtemail.insert(attvalstring, temp);     //connecting each attvalpair to an email
                    }
                    else {
                        p->push_back(email);
                        rtemail.insert(attvalstring, *p);
                    }
                }
            }
            else {
                PersonProfile* psp = nullptr;
                check = 0;
            }
            //std::cout << line << '\n';
        }
        infile.close();
    }
    return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    std::vector<std::string> temp;
    std::string combination = input.attribute + ',' + input.value;
    std::vector<std::string>* trial = rtemail.search(combination);
    if (rtemail.search(combination) == nullptr) { return temp;} 
    else {
        for (int i = 0; i < trial->size(); i++) {
            temp.push_back((*trial)[i]);            //matching members added to the vector
        }
        return temp;
    }
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {
    if (rtpp.search(email) == nullptr)
        return nullptr;
    return *(rtpp.search(email));
}