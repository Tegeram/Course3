#include <iostream>
#include <list>
#include <malloc.h>
#include <algorithm>
#include <numeric>
#include <iterator>


using namespace std;

//=====Task 1================================================================================================================

void Print(list<double> list) {
	cout << "( ";
	for (auto i : list) {
		cout << i << " ";
	}
	cout << ")" << endl;
}

void PushBack(list<double>& list) {
	double num = 0;
	for (auto i : list) {
		num += i;
	}
	list.push_back(num / list.size());
}

//=====Task 2================================================================================================================

class Matrix {
private:
	size_t m_size;
	double* ptr;

public:
	Matrix(size_t size) {
		m_size = size;
		ptr = (double*)malloc(m_size * m_size * sizeof(double));//создание        
	}

	~Matrix() {
		free(ptr);
	}

	void InitMatrix() {
		for (size_t i = 0; i < m_size; i++) {
			for (size_t j = 0; j < m_size; j++)
			{
				cout << "Enter number: ";
				cin >> ptr[i * m_size + j];
			}
		}
	}

	void PrintMatrix() {
		for (size_t i = 0; i < m_size; i++) {
			cout << "(";
			for (size_t j = 0; j < m_size; j++)
			{
				cout << " " << ptr[i * m_size + j];

			}
			cout << ")" << "\n";
		}
	}

	double Determinant() {

		double det = 1;
		for (size_t i = 0; i < m_size; ++i)
		{
			double mx = fabs(ptr[i * m_size + i]);
			size_t idx = i;
			for (size_t j = i + 1; j < m_size; ++j)
				if (mx < fabs(ptr[i * m_size + j])) mx = fabs(ptr[i * m_size + (idx = j)]);
			if (idx != i)
			{
				for (size_t j = i; j < m_size; ++j)
				{
					double t = ptr[j * m_size + i];
					ptr[j * m_size + i] = ptr[j * m_size + idx];
					ptr[j * m_size + idx] = t;
				}
				det = -det;
			}
			for (size_t k = i + 1; k < m_size; ++k)
			{
				double t = ptr[k * m_size + i] / ptr[i * m_size + i];

				for (size_t j = i; j < m_size; ++j)
					ptr[k * m_size + j] -= ptr[i * m_size + j] * t;
			}
		}
		for (size_t i = 0; i < m_size; ++i) det *= ptr[i * m_size + i];
		return det;
	}
};


//=====Task 3================================================================================================================

template <typename ValueType>
class OwnIterator : public iterator<input_iterator_tag, ValueType> {
protected:	
	ValueType* p;

private:
	OwnIterator(ValueType* p) : p(p) {};

public:
	friend class OwnContainer;	

	OwnIterator(const OwnIterator& it) : p(it.p) {}

	bool operator!=(OwnIterator const& other) const {
		return p != other.p;
	}

	ValueType& operator* () const {
		return *p;
	}

	OwnIterator& operator++() {
		++p;
		return *this;
	}
};

class OwnContainer {
protected:
	const size_t size;
	unique_ptr<int[]> arr;
public:
	OwnContainer(initializer_list<int> values) : size(values.size()), arr(new int[size]) {
		copy(values.begin(), values.end(), arr.get());
	}

	typedef OwnIterator<int> Myiter;

	Myiter begin() { return Myiter(arr.get()); };
	Myiter end() { return Myiter(arr.get() + size); };
};


//===========================================================================================================================

int main()
{
	cout << "Task 1" << "\n";
	list<double> list1{ 2,5,7,2,3 };
	PushBack(list1);
	Print(list1);
	PushBack(list1);
	PushBack(list1);
	PushBack(list1);
	Print(list1);
	cout << endl;

	//=======================================================================================================================

	cout << "Task 2" << "\n";
	size_t size1;
	cout << "Enter size (n) of matrix[n][n]: ";
	cin >> size1;
	Matrix mat(size1);
	mat.InitMatrix();
	mat.PrintMatrix();
	cout << "Determinant = " << mat.Determinant() << endl << endl;

	//=======================================================================================================================

	cout << "Task 3" << "\n";
	OwnContainer m{ 1,2,3,4,5,6,7,8,9 };
	cout << "( ";
	for (auto x : m) {
		cout << x << " ";
	}
	cout << ")";

	return 0;
}
