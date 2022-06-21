#include "newMap.h"

Map::Map() {
	map_max_size = DEFAULT_MAX_ITEMS;
	map_size = 0;
	m_key = new KeyType[map_max_size];
	m_value = new ValueType[map_max_size];
}


Map::Map(int m) {
	map_max_size = m;
	map_size = 0;
	m_key = new KeyType[map_max_size];
	m_value = new ValueType[map_max_size];
}

Map::Map(const Map& other) {
	map_max_size = other.map_max_size;
	map_size = other.map_size;
	m_key = new KeyType[map_max_size];
	m_value = new ValueType[map_max_size];

	for (int i = 0; i < map_size; i++) {
		m_key[i] = other.m_key[i];
		m_value[i] = other.m_value[i];
	}
}

Map& Map:: operator=(const Map& p) {
	if (this != &p) {
		Map temp(p);
		this->swap(temp);
		/*delete[] m_key;
		delete[] m_value;
		map_max_size = p.map_max_size;
		map_size = p.map_size;

		m_key = new KeyType[map_max_size];
		m_value = new ValueType[map_max_size];

		for (int j = 0; j < map_size; j++) {
			m_key[j] = p.m_key[j];
			m_value[j] = p.m_value[j];
		}*/
	}
	return *this;
}


Map::~Map() {
	delete [] m_key;
	delete [] m_value;
}

bool Map::empty() const {
	return (map_size == 0);
}

int Map::size() const {
	return map_size;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
	if (map_size >= map_max_size)
		return false;

	if (map_size == 0) {
		m_key[0] = key;
		m_value[0] = value;
		map_size++;
		return true;
	}

	for (int i = 0; i < map_size; i++) {
		if (m_key[i] == key) {
			return false;
		}
	}
	m_key[map_size] = key;
	m_value[map_size] = value;
	map_size++;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value) {
	for (int i = 0; i < map_size; i++) {
		if (m_key[i] == key) {
			m_value[i] = value;
			return true;
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {

	if (map_size == 0) {
		m_key[0] = key;
		m_value[0] = value;
		map_size++;
		return false;
	}
	for (int i = 0; i < map_size; i++) {
		if (m_key[i] == key) {
			m_value[i] = value;
			return true;
		}
	}
	if (map_size >= map_max_size)
		return false;

	m_key[map_size] = key;
	m_value[map_size] = value;
	map_size++;
	return false;
}

bool Map::erase(const KeyType& key) {
	for (int i = 0; i < map_size; i++) {
		if (m_key[i] == key) {
			for (int j = i; j < map_size - 1; j++) {
				m_key[j] = m_key[j + 1];
				m_value[j] = m_value[j + 1];
			}
			map_size--;
			return true;
		}
	}
	return false;
}

bool Map::contains(const KeyType& key) const {
	for (int i = 0; i < map_size; i++) {
		if (m_key[i] == key) {
			return true;
		}
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
	for (int i = 0; i < map_size; i++) {
		if (m_key[i] == key) {
			value = m_value[i];
			return true;
		}
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
	if (i < 0 || i >= map_size) {
		return false;
	}

	Map temp = *this;

	KeyType temp1;
	ValueType temp2;

	for (int i = 0; i < map_size - 1; i++) {
		for (int j = 0; j < map_size - i - 1; j++) {
			if (temp.m_key[j] > temp.m_key[j + 1]) {
				temp1 = temp.m_key[j];
				temp.m_key[j] = temp.m_key[j + 1];
				temp.m_key[j + 1] = temp1;

				temp2 = temp.m_value[j];
				temp.m_value[j] = temp.m_value[j + 1];
				temp.m_value[j + 1] = temp2;
			}
		}
	}

	key = temp.m_key[i];
	value = temp.m_value[i];
	return true;
}

void Map::swap(Map& other) {
	KeyType* m_keytemp;
	ValueType* m_valuetemp;
	m_keytemp = m_key;
	m_key = other.m_key;
	other.m_key = m_keytemp;

	m_valuetemp = m_value;
	m_value = other.m_value;
	other.m_value = m_valuetemp;

	int temp_max = map_max_size;
	map_max_size = other.map_max_size;
	other.map_max_size = temp_max;

	int temp_size = map_size;
	map_size = other.map_size;
	other.map_size = temp_size;
}



