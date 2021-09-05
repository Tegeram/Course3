#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <numeric>

using namespace std;

template <typename ValueType>
void print(vector<ValueType>& vec) {
	cout << "( ";
	copy(vec.begin(), vec.end(), ostream_iterator<ValueType>{cout, "  "});
	cout << ")";
}

//=====Task 1================================================================================================================

template <typename ValueType>
void insert_sorted(vector<ValueType>& vec, ValueType a) {
	auto it = find_if(vec.begin(), vec.end(), [a](ValueType i) {return (i > a); });
	vec.insert(it, a);
}

//=====Task 2================================================================================================================

void Initialisate(vector<double>& vec) {	
	generate(vec.begin(), vec.end(), []() {return ((rand() % 100) * sin(rand() % 180 - 90)); });
}

void Transform(vector<double>& vec1, vector<double>& vec2) {
	transform(vec1.begin(), vec1.end(), vec2.begin(), [](double i)
		{
			double a,b;
			b =  modf(i, &a);
			if (b > 0.5)
				a += 1;
			return a;
		}
	);
}

double Deviation(vector<double>& vec1, vector<double>& vec2) {
	vector<double> vec3(100);
	for (size_t i = 0; i < vec1.size(); i++)
	{
		vec3[i] = vec1[i] - vec2[i];
	}	
	transform(vec3.begin(), vec3.end(), vec3.begin(), [](double i) { return pow(i, 2); });
	cout << "\n";
	print(vec3);
	
	return accumulate(vec3.begin(), vec3.end(), 0.0);
}

//===========================================================================================================================

int main()
{
	cout << "Task 1" << "\n";
    vector<int> v1{ 1,3,5,7,9 };
	print(v1);
	cout << endl;
	insert_sorted(v1, 4);
	insert_sorted(v1, 10);	
	print(v1);
	vector<char> v2{ 'a','c','e'};
	cout << endl;
	print(v2);
	cout << endl;
	insert_sorted(v2, 'b');
	insert_sorted(v2, 'f');
	print(v2);
	cout << endl;

	//=======================================================================================================================

	cout << "Task 2" << "\n";
	vector<double> v3(100);
	vector<double> v4(100);
	vector<double> v5(100);
	Initialisate(v3);
	Transform(v3, v4);	
	cout << "vector 1: ";
	print(v3);
	cout << "\nvector 2: ";
	print(v4);
	cout << "\n" << "Deviation = " << Deviation(v3, v4);

	return 0;
}
