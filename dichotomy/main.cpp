//
// Created by antosha on 25.05.17.
//

#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::vector;


class mayan_number{
public:
    mayan_number(){};
    mayan_number(const char*);
    mayan_number(int);

    mayan_number operator=(const mayan_number& num);
    mayan_number operator+(const mayan_number& num);
    mayan_number operator-(const mayan_number& num);
    mayan_number operator*(const mayan_number& num);
    mayan_number operator*(int num);
    mayan_number operator/(const mayan_number& num);
    bool operator>(const mayan_number& num);
    bool operator<(const mayan_number& num);
    bool operator==(const mayan_number& num);

    friend ostream& operator<<(ostream& os, const mayan_number& num);
private:
    vector<int> number;
};

ostream& operator<<(ostream& os, const mayan_number& num){
    for (int i = (int)num.number.size() - 1; i > -1; --i) {

        os<<'(';
        for (int j = 0; j < num.number[i]%5; ++j) {
            os<<'.';
        }
        for (int j = 0; j < num.number[i]/5; ++j) {
            os<<'|';
        }
        os<<')';
    }
    return os;
}

mayan_number::mayan_number(const char * str) {
    while(*str != '\0'){
        if(*str != '(') {
            cout<<"Init error";
            number.clear();
            return;
        }
        str++;
        int res = 0;
        int count = 0;
        while(*str == '.'){
            res++;
            str++;
            count++;
        }
        if(count > 4) {
            cout<<"Init error";
            number.clear();
            return;
        }
        count = 0;
        while(*str == '|'){
            res+=5;
            str++;
            count++;
        }
        if(count > 4) {
            cout<<"Init error";
            number.clear();
            return;
        }
        if(*str != ')') {
            cout<<"Init error";
            number.clear();
            return;
        }
        str++;
        if(res > 19) {
            cout<<"Init error";
            number.clear();
            return;
        }
        number.push_back(res);
    }
    std::reverse(number.begin(), number.end());
}

mayan_number mayan_number::operator=(const mayan_number &num) {
    this->number=num.number;
    return *this;
}

mayan_number mayan_number::operator+(const mayan_number &num) {
    mayan_number res;
    int i = 0;
    int mem = 0;
    while (true) {
        int sum = mem;
        if (i < num.number.size())
            sum += num.number[i];
        if (i < number.size())
            sum += number[i];
        mem = sum/20;
        res.number.push_back(sum % 20);
        if (i >= num.number.size() && i >= number.size()) {
            res.number.push_back(mem);
            while(res.number.back() == 0)
                res.number.pop_back();
            break;
        }
        i++;
    }
    return res;
}

mayan_number mayan_number::operator-(const mayan_number &num) {
    mayan_number res;
    int i = 0;
    int mem = 0;
    while (true) {
        int sum = mem;
        if (i < num.number.size())
            sum -= num.number[i];
        if (i < number.size())
            sum += number[i];
        if (sum < 0) {
            mem = -1;
            sum = 20 + sum;
        } else {
            mem = 0;
        }
        res.number.push_back(sum);
        if (i >= num.number.size() && i >= number.size()) {
            if (mem == -1){
                res.number.clear();
                //cout<<"Mayans didn't know negative numbers"<<endl;
                return res;
            }
            while(res.number.back() == 0 && res.number.size() != 1)
                res.number.pop_back();
            break;
        }
        i++;
    }
    return res;
}

mayan_number mayan_number::operator*(const mayan_number &num) {
    mayan_number res("()");
    for (int i = 0; i < number.size(); ++i) {
        mayan_number temp;
        for (int j = 0; j < i; ++j) {
            temp.number.push_back(0);
        }
        int mem = 0;
        for (int k = 0; k < num.number.size(); ++k) {
            int mul = number[i]*num.number[k] + mem;
            mem = mul/20;
            temp.number.push_back(mul%20);
        }

        while (mem != 0) {
            temp.number.push_back(mem%20);
            mem/=20;
        }
        res = res + temp;
    }
    return res;
}

mayan_number mayan_number::operator/(const mayan_number &num) {
    mayan_number num_copy = num;
    if(*this == num) {
        return mayan_number(1);
    }
    if(*this < num) {
        return mayan_number(0);
    }
    mayan_number res;
    mayan_number part;
    int i = 0;
    while (i < number.size()) {
        part.number.clear();
        part.number.push_back(number[i++]);
        while(part < num) {
            part.number.push_back(number[i++]);
            res.number.push_back(0);
        }
        int part_res = 1;
        while( num_copy * part_res < part)
            part_res++;
        res.number.push_back(--part_res);
    }
    std::reverse(res.number.begin(), res.number.end());
    while(res.number.back() == 0 && res.number.size() != 1)
        res.number.pop_back();
    return res;
}

bool mayan_number::operator>(const mayan_number &num) {
    mayan_number temp = *this - num;
    return temp.number.size() != 0 && temp.number[0] != 0;
}

mayan_number::mayan_number(int num) {
    while (num != 0) {
        number.push_back(num%20);
        num /= 20;
    }
}

mayan_number mayan_number::operator*(int num) {
    return mayan_number(num)*(*this);
}

bool mayan_number::operator==(const mayan_number &num) {
    mayan_number temp = *this - num;
    return temp.number.size() == 1 && temp.number[0] == 0;
}

bool mayan_number::operator<(const mayan_number &num) {
    mayan_number temp = *this - num;
    return temp.number.size() == 0;
}

int main() {
    mayan_number a("(.)(..)");


    mayan_number b("(..)(.)");

    mayan_number c (210);
    mayan_number d (210);
    mayan_number q = a;
    cout<<d<<endl;

    return 0;
}