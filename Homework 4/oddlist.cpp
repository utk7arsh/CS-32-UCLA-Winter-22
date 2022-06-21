void removeOdd(list<int>& li)
{
	for (list<int>::iterator it = li.begin(); it != li.end();) {
		if (*it % 2 == 1) {
			it = li.erase(it);
		}
		else
			it++;
	}

}