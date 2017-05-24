#include <iostream>
#include <string>
#include <stdlib.h>
#include <set>
#include <cstring>

using namespace std;

class Word : public string {

    unsigned long nbk;

    unsigned long count();

    void sort();

public:
    Word();

    Word(string &);

    Word(char *);

    Word(char);

    Word *operator=(string);

    Word *operator=(const char *);

    Word *operator=(char);

    Word &operator*(int);

    Word &operator!();

    Word &operator/(int);

    Word &operator-(Word &);

    void instead(Word &, Word &);

    unsigned long getLet();
};

Word::Word() {
    nbk = 0;
};

Word::Word(string &a) : string(a) {
    nbk = count();
};

Word::Word(char *str) : string(str) {
    nbk = count();
};

Word::Word(char str) {
    *(std::string *) this = str;
    nbk = count();
};

unsigned long Word::getLet() {
    return nbk;
};

unsigned long Word::count() {
    return ((std::string *) this)->length();
};

Word *Word::operator=(string a) {
    *(std::string *) this = string::operator=(a);
    nbk = count();
    return this;
};

Word *Word::operator=(const char *a) {
    *(std::string *) this = string::operator=(a);
    nbk = count();
    return this;
};

Word *Word::operator=(char a) {
    *(std::string *) this = string::operator=(a);
    nbk = 1;
    return this;
};

int cmp(const void *a, const void *b) {
    return *(char *) a - *(char *) b;
};

// пример сортировки
void Word::sort() {
    qsort((void *) (*(std::string *) this).data(), (*(std::string *) this).length(), sizeof(char), cmp);
};

Word &Word::operator!() {
    cout<<(((std::string *) this)->size());
    /*for (int i = 0; i < ((std::string *) this)->length() / 2 - 1; ++i) {
        char temp = (*this)[i];
        (*this)[i] = (*this)[((std::string *) this)->length() - i];
        (*this)[((std::string *) this)->length() - i - 1] = temp;
    }*/
};

Word &Word::operator*(int times) {
    const char *data = c_str();
    char *new_data = new char(times * ((std::string *) this)->length());
    for (int i = 0; i < times * ((std::string *) this)->length(); ++i) {
        new_data[i] = data[i%((std::string *) this)->length()];
    }
    clear();
    Word *res = new Word();
    *res = new_data;
    return *res;
};

//Word &operator/(int) {
//};

int main() {
    std::string a = "12345";
    a = 'a';
    Word b = a;
    cout << !b << endl;
    cout << b*3 << endl;

    return 0;
}