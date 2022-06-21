#include "Map.h"

Map::Map() {
	map_size = 0;
}

bool Map::empty() const {
	return (map_size == 0);
}

int Map::size() const {
	return map_size;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
	if (map_size >= DEFAULT_MAX_ITEMS)
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
	if (map_size >= DEFAULT_MAX_ITEMS)
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

	Map temp;
	temp.map_size = map_size;

	for (int i = 0; i < map_size; i++) {
		temp.m_key[i] = m_key[i];
		temp.m_value[i] = m_value[i];
	}

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
	Map temp;

	for (int i = 0; i < this->size(); i++) {	//copying this to temp
		temp.m_key[i] = this->m_key[i];
		temp.m_value[i] = this->m_value[i];
		temp.map_size = this->map_size;
	}

	for (int i = 0; i < other.size(); i++) {
		this->m_key[i] = other.m_key[i];
		this->m_value[i] = other.m_value[i];
		this->map_size = other.map_size;
	}

	for (int i = 0; i < temp.size(); i++) {
		other.m_key[i] = temp.m_key[i];
		other.m_value[i] = temp.m_value[i];
		other.map_size = temp.map_size;
	}
}



