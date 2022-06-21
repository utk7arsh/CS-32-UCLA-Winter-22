#ifndef MAP_
#define MAP_
#include <string>


using KeyType = std::string;
using ValueType = double;
class Map
{
public:
    Map();
    ~Map();
    Map(const Map& other);
    Map& operator=(const Map& rhs);


    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    void dump();

private:
    struct Node {
        KeyType m_key;
        ValueType m_value;
        Node* next;
        Node* prev;
    };

    int map_size;
    Node* head;
    Node* tail;
};

bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);
#endif