//#include <iostream>
//using namespace std;
//#include <string>
//#include <cassert>
//
//bool somePredicate(double x)
//{
//	return x > 0;
//}

// Return true if the somePredicate function returns false for at
	// least one of the array elements, false otherwise.
bool anyFalse(const double a[], int n)
{
	if (n < 1)
		return false;
	if (!somePredicate(*a))
		return true;
	return anyFalse(a + 1, n - 1);
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
	if (n < 1) 
		return 0;
	if (!somePredicate(*a))
		return (1 + countFalse(a + 1, n - 1));
	else
		return countFalse(a + 1, n - 1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
	if (n < 1)
		return -1;
	int count = firstTrue(a + 1, n - 1);

	if (count == -1) {
		if (somePredicate(*a))
			return 0;
		else
			return -1;
	}

	if (somePredicate(*a))
		return 0;
	else
		return 1 + count;
}

// Return the subscript of the largest element in the array (i.e.,
// return the smallest subscript m such that a[m] >= a[k] for all
// k such that k >= 0 and k < n).  If there is no such subscript,
// return -1.
int locateMax(const double a[], int n)
{
	if (n < 1) { return -1; }
	if (n == 1) { return 0; }

	int max1 = locateMax(a, n / 2);
	int max2 = locateMax(a + n/2, n - (n / 2)) + n/2;

	if (a[max1]  >= a[max2])
		return max1;
	else
		return max2;

}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not contain
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool contains(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0) { return true; }
	if (n1 < n2) { return false; }

	if (a1[0] == a2[0]) {
		return(contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1));
	}
	return(contains(a1 + 1, n1 - 1, a2, n2));
}

//int main() {
//	/*double ab[4] = {-100,23,44,55};
//	cout << anyFalse(ab, 4) << endl;
//	cout << countFalse(ab, 4) << endl;
//	cout << firstTrue(ab, 4) << endl;
//	cout << locateMax(ab, 4) << endl;
//
//	const double p[7] = { 10, 50, 40, 20, 50, 40, 30 };
//	const double q[3] = { 50,30,10 };
//	cout << contains(p, 7, q, 3) << endl;*/
//	double a[]{ 1, 1, -1, 1, -1, 1 };
//	assert(anyFalse(a, 6));
//	assert(anyFalse(a, 3));
//	assert(!anyFalse(a, -1));
//	assert(!anyFalse(a, 1));
//	assert(!anyFalse(a, 0));
//
//	assert(countFalse(a, 6) == 2);
//	assert(countFalse(a, 3) == 1);
//	assert(countFalse(a, -3) == 0);
//	assert(countFalse(a, 0) == 0);
//	assert(countFalse(a, 2) == 0);
//
//	double b[]{ -1, -1, 1, -1, 1, -1 };
//	assert(firstTrue(b, 6) == 2);
//	assert(firstTrue(b, -2) == -1);
//	assert(firstTrue(b, 3) == 2);
//	assert(firstTrue(b, 2) == -1);
//
//	double c[]{ 1, 3, -2, -1, 3, 5 };
//	assert(locateMax(c, 6) == 5);
//	assert(locateMax(c, 5) == 1);
//	assert(locateMax(c, 2) == 1);
//	assert(locateMax(c, 3) == 1);
//	assert(locateMax(c, -5) == -1);
//	assert(locateMax(c, 0) == -1);
//	assert(locateMax(c, 1) == 0);
//
//	double a1[]{ 10, 50, 40, 20, 50, 40, 30 };
//	double b1[]{ 50, 20, 30 };
//	double b2[]{ 50, 40, 40 };
//	double b3[]{ 50, 30, 20 };
//	double b4[]{ 10, 20, 20 };
//	assert(contains(a1, 7, b1, 3));
//	assert(contains(a1, 7, b2, 3));
//	assert(!contains(a1, 7, b3, 3));
//	assert(!contains(a1, 7, b4, 3));
//	assert(contains(a1, 7, b1, 0));
//}