#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

//=====Task 1============================================================================================================

template<typename T1>
void Swap(T1* ptrA, T1* ptrB) {
    T1 ptrC = *ptrA; 
    *ptrA = *ptrB;
    *ptrB = ptrC;    
}

//=====Task 2============================================================================================================

template<typename T>
void Print(vector<T*>& v) {
    auto it = v.begin();
    for (it; it != v.end(); ++it)
        cout << **it << " ";
    cout << endl;
}

template<typename T2>
void SortPointers(vector<T2*>& v) {
    sort(v.begin(), v.end(), [](T2* a, T2* b) {
        return *a < *b;}
    );
}

//=====Task 3============================================================================================================

class Timer {
private:
    using clock_t = chrono::high_resolution_clock;
    using second_t = chrono::duration<double, ratio<1>>;

    string m_name;
    chrono::time_point<clock_t> m_beg;
    double elapsed() const {
        return chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }

public:
    Timer() : m_beg(clock_t::now()) {}
    Timer(string name) : m_name(name), m_beg(clock_t::now()){}

    void start(string name) {
        m_name = name;
        m_beg = clock_t::now();
    }
    void print() const {
        cout << m_name << ":\t" << elapsed() * 1000 << " ms" << '\n';
    }
};

int Counting1(ifstream& file) {
    Timer timer("Count_if and Find");
    string str = "AEIOUaeiou";
    int count = 0;
    if (file)
    {   
        count = count_if(istream_iterator<char>(file), istream_iterator<char>(), [=](char x) { return str.find(x) != string::npos; });
        timer.print();
        return count;        
    }
}

int Counting2(ifstream& file) {
    Timer timer("Count_if and For");
    string str = "AEIOUaeiou";
    int count = 0;
    if (file)
    {        
        char t;
        for (file >> t; !file.eof(); file >> t) {
            count += count_if(str.begin(), str.end(), [=](char x) { return x == t; });
        }
        timer.print();
        return count;
    }    
}

int Counting3(ifstream& file) {
    Timer timer("For and Find");
    string str = "AEIOUaeiou";
    int count = 0;
    if (file)
    {
        char t;        
        for (file >> t; !file.eof(); file >> t) {
            if (str.find(t) != string::npos) {
                count++;
            }
        }
        timer.print();
        return count;
    }    
}

int Counting4(ifstream& file) {
    Timer timer("2 For");
    char str[] = { 'A','E','I','O','U','a','e','i','o','u' };
    char t;
    int count = 0;
    if (file)
    {        
        for (file >> t; !file.eof(); file >> t) {
            for (size_t j = 0; j < 10 ; j++) {
                if (str[j] == t) {
                    count++;
                }
            }
        }
        timer.print();
        return count;
    }    
}

//=======================================================================================================================

int main()
{    
    cout << "Task 1" << endl;
    int* ptrA = new int(5); 
    int* ptrB = new int(10);
    cout << *ptrA << " " << *ptrB << endl;
    Swap(&ptrA, &ptrB);
    cout << *ptrA << " " << *ptrB << endl;
    delete ptrA;
    delete ptrB;
 //=======================================================================================================================
  
    cout << endl << "Task 2" << endl;
    int a = 4, b = 2, c = 8, d = 1, e = 3;
    vector<int*> v1;
    v1.push_back(&a);
    v1.push_back(&b);
    v1.push_back(&c);
    v1.push_back(&d);
    v1.push_back(&e);

    Print(v1);
    SortPointers(v1);    
    Print(v1);       

//=======================================================================================================================

    cout << endl << "Task 3" << endl;
    ifstream file("Tolstoy Leo. War and Peace.txt");
    cout << "Count_if and Find: " << Counting1(file) << endl;
    file.close();
    
    ifstream file2("Tolstoy Leo. War and Peace.txt");
    cout << "Count_if and For: " << Counting2(file2) << endl;
    file2.close();
    
    ifstream file3("Tolstoy Leo. War and Peace.txt");
    cout << "For and Find: " << Counting3(file3) << endl;
    file3.close();
    
    ifstream file4("Tolstoy Leo. War and Peace.txt");
    cout << "2 For: " << Counting4(file4) << endl;
    file4.close();
    
    return 0;
}
