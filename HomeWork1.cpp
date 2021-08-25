#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <optional>
#include <string>
//#include <functional>

using namespace std;

struct Person {
    string familyName;
    string firstName;
    string secondName;

    friend ostream& operator<< (ostream& os, const Person& p) {
        os << p.familyName << " " << p.firstName << " " << p.secondName << "   ";
        return os;
    }

    friend bool operator<(const Person& p1, const Person& p2) {
        return tie(p1.familyName, p1.firstName, p1.secondName) < tie(p2.familyName, p2.firstName, p2.secondName);
    }

    friend bool operator==(const Person& p1, const Person& p2) {
        return tie(p1.familyName, p1.firstName, p1.secondName) == tie(p2.familyName, p2.firstName, p2.secondName);
    }
};

struct PhoneNumber {
    int countryNum;
    int cityNum;
    string Number;
    optional<int> extNum;

    

    friend ostream& operator<< (ostream& os, const PhoneNumber& p) {
        if (p.extNum.has_value()) os << "+" << p.countryNum << "(" << p.cityNum << ")" << p.Number << " " << p.extNum.value();        
        else os << "+" << p.countryNum << "(" << p.cityNum << ")" << p.Number << " "; 
        return os;
    }

    friend bool operator<(const PhoneNumber& p1, const PhoneNumber& p2) {
        return tie(p1.countryNum, p1.cityNum, p1.Number, p1.extNum) < tie(p2.countryNum, p2.cityNum, p2.Number, p2.extNum);
    }

    friend bool operator==(const PhoneNumber& p1, const PhoneNumber& p2) {
        return tie(p1.countryNum, p1.cityNum, p1.Number, p1.extNum) == tie(p2.countryNum, p2.cityNum, p2.Number, p2.extNum);
    }
};

ostream& operator<< (ostream& os, const pair<Person, PhoneNumber>& ph) {
    os << ph.first << ph.second;
    return os;
}

bool sortbysec(const pair<Person, PhoneNumber>& p1, const pair<Person, PhoneNumber>& p2)
{
    return (p1.second < p2.second);
}

class PhoneBook {
protected:
    vector<pair<Person, PhoneNumber>> PerPhon;
public:
    friend ostream& operator<< (ostream& os, const PhoneBook& ph) {
        for (const auto& p : ph.PerPhon) {
            os << p.first << p.second << "\n";
        }
        return os;
    }

    PhoneBook(ifstream& file) {       
        if (file) {
            while (true) {
                string str;
                pair<Person, PhoneNumber> input;            
                getline(file, input.first.familyName, ' ');
                getline(file, input.first.firstName, ' ');
                getline(file, input.first.secondName, '+');
                getline(file, str, '(');
                if (!str.empty()) input.second.countryNum = stoi(str);
                getline(file, str, ')');
                if (!str.empty()) input.second.cityNum = stoi(str);
                getline(file, input.second.Number, ' ');
                getline(file, str, '\n');
                if(!str.empty()) input.second.extNum = stoi(str);
                
                if (file.eof()) {
                    break;
                }                
                
                PerPhon.push_back(input);
            }
        }
        else cout << "Error";
    }

    void SortByName() {
        sort(PerPhon.begin(), PerPhon.end());
    }

    void SortByPhone() {
        sort(PerPhon.begin(), PerPhon.end(), sortbysec);
    }

    pair<string, PhoneNumber> GetPhoneNumber(string familyName) {
        int count = 0;
        string nfound = "not found";
        pair<Person, PhoneNumber> pb;
        for (const auto& ph : PerPhon) {
            if (ph.first.familyName == familyName)
            {
                count += 1;
                pb = ph;
            }
        }
        if (count == 1)  return { "",pb.second };
        else if (count > 1) return { "found more than 1",pb.second };
        else return { "not found",pb.second };
    }

    void ChangePhoneNumber(Person p, PhoneNumber ph) {
        vector<pair<Person, PhoneNumber>>::iterator it;
        find_if(it = PerPhon.begin(), PerPhon.end(),
            [&p](const pair<Person, PhoneNumber>& book)
            {return book.first == p; });
        it->second = ph;        
    }
};

int main()
{
    ifstream file("PhoneBook.txt"); // путь к файлу PhoneBook.txt
    PhoneBook book(file);
    cout << book;
     
    cout << "------SortByPhone-------" << endl;
    book.SortByPhone();
    cout << book;

    cout << "------SortByName--------" << endl;
    book.SortByName();
    cout << book;

    cout << "-----GetPhoneNumber-----" << endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона этого человека, либо строку с ошибкой
    auto print_phone_number = [&book](const string& surname) {
        cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
            cout << get<1>(answer);
        else
            cout << get<0>(answer);
        cout << endl;
    };

    //// вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");

    cout << "----ChangePhoneNumber----" << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", nullopt });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
    cout << book;

    return 0;
}
