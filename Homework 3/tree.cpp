//#include <iostream>
//#include <cassert>
//using namespace std;

// Return the number of ways that all n2 elements of a2 appear in
	// the n1 element array a1 in the same order (though not necessarily
	// consecutively).  The empty sequence (i.e. one where n2 is 0)
	// appears in a sequence of length n1 in 1 way, even if n1 is 0.
	// For example, if a1 is the 7 element array
	//        10 50 40 20 50 40 30
	// then for this value of a2     the function must return
	//        10 20 40                        1
	//        10 40 30                        2
	//        20 10 40                        0
	//        50 40 30                        3
int countContains(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0) { return 1; }
	if (n1 <= 0) { return 0; }
	if (n1 < n2) { return 0; }

	if (a1[0] == a2[0]) {
		return (countContains(a1 + 1, n1 - 1, a2 + 1, n2 - 1) + countContains(a1 + 1, n1 - 1, a2, n2));
	}
	else
		return (countContains(a1 + 1, n1 - 1, a2, n2));
}

// Exchange two doubles
void exchange(double& x, double& y)
{
	double t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > separator come before all the other elements,
// and all the elements whose value is < separator come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= separator, or n if there is no such element, and firstLess is
// set to the index of the first element that is < separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > separator
//   * for firstNotGreater <= i < firstLess, a[i] == separator
//   * for firstLess <= i < n, a[i] < separator
// All the elements > separator end up in no particular order.
// All the elements < separator end up in no particular order.
void separate(double a[], int n, double separator,
	int& firstNotGreater, int& firstLess)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
	//  Every element earlier than position firstNotGreater is > separator
	//  Every element from position firstNotGreater to firstUnknown-1 is
	//    == separator
	//  Every element from firstUnknown to firstLess-1 is not known yet
	//  Every element at position firstLess or later is < separator

	firstNotGreater = 0;
	firstLess = n;
	int firstUnknown = 0;
	while (firstUnknown < firstLess)
	{
		if (a[firstUnknown] < separator)
		{
			firstLess--;
			exchange(a[firstUnknown], a[firstLess]);
		}
		else
		{
			if (a[firstUnknown] > separator)
			{
				exchange(a[firstNotGreater], a[firstUnknown]);
				firstNotGreater++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
	if (n <= 1)
		return;
	int firstnotgreater, firstless;
	separate(a, n, a[n / 2], firstnotgreater, firstless);
	order(a, firstnotgreater);
	order(a + firstless, n - firstless);
	return;
}


//int main() {
//	double p[7] = { 10, 50, 40, 20, 50, 40, 30 };
//	const double q[3] = { 10,60 };
//
//	assert(countContains(p, 7, q, 3) == 0);
//	assert(countContains(p, 1, q, 1) == 1);
//	assert(countContains(p, 2, q, 1) == 1);
//	assert(countContains(p, 2, q, 2) == 0);
//	assert(countContains(p, 2, q, 0) == 1);
//	assert(countContains(p, 1, q, 2) == 0);
//	order(p, 7);
//	assert(p[0] == 50 && p[2] == 40 && p[3] == 40);
//
//	double l[5] = { 9,4,4,5,3 };
//	double m[3] = { 4,5,3 };
//	assert(countContains(l, 5, m, 3) == 2);
//	assert(countContains(l, 5, m, 1) == 2);
//	assert(countContains(l, 2, m, 2) == 0);
//	order(l, 5);
//	order(m, 3);
//	assert(l[1] == m[0] && l[2] == m[1]);
//}