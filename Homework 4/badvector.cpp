void removeBad(vector<Movie*>& v)
{
	vector<Movie*>::iterator it;
	for (it = v.begin(); it != v.end();) {
		if ((*it)->rating() < 50) {
			delete* it;
			v.erase(it);
		}
		else
			it++;
	}
}