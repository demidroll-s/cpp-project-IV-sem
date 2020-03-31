#include <iostream>
#include <math.h>
#include <string.h>
#include "example.h"

using namespace std;

class Money
{
protected:
    int dollar;
    int cent;
public:
    //constructors
    Money(int dollar, int cent)
    {
        long int x = dollar * 100 + cent;
        this->dollar = x / 100;
        this->cent = x % 100;
    }
    Money()
    {
        this->dollar = 0;
        this->cent = 0;
    }
    Money(int cent)
    {
        this->dollar = cent / 100;
        this->cent = cent % 100;
    }

    //methods
    void set_dollar(int dollar);
    void set_cent(int cent);
    int get_dollar();
    int get_cent();
    long int full_cent();
    
    //functions
    friend void refresh(Money &money);

    //operators
    friend Money operator+(Money &A, Money &B);
    friend Money operator-(Money &A, Money &B);
    friend Money operator*(Money &A, int l);
    friend Money operator+=(Money &A, Money &B);
    friend Money operator-=(Money &A, Money &B);
    friend Money operator*=(Money &A, int l);

    friend bool operator==(Money &A, Money &B);
    friend bool operator!=(Money &A, Money &B);
    friend bool operator>(Money &A, Money &B);
    friend bool operator<(Money &A, Money &B);

    friend ostream& operator<<(ostream& os, const Money &money);
};

void Money::set_dollar(int dollar)
{
    this->dollar = dollar;
}

void Money::set_cent(int cent)
{
    this->cent = cent;
}

int Money::get_dollar()
{
    return dollar;
}

int Money::get_cent()
{
    return cent;
}

long int Money::full_cent()
{
    return dollar * 100 + cent;
}

//Money methods

void refresh(Money &money)
{
    long int x = money.full_cent();
    money.dollar = x / 100;
    money.cent = x % 100;
}

Money operator+(Money &A, Money &B)
{
    Money C(A.dollar + B.dollar, A.cent + B.cent);
    refresh(C);
    return C;
}

Money operator-(Money &A, Money &B)
{
    Money C(A.dollar - B.dollar, A.cent - B.cent);
    refresh(C);
    return C;
}

Money operator*(Money &A, int l)
{
    Money C(A.dollar * l, A.cent * l);
    refresh(C);
    return C;
}

Money operator+=(Money &A, Money &B)
{
    A = A + B;
    return A;
}

Money operator-=(Money &A, Money &B)
{
    A = A - B;
    return A;
}

Money operator*=(Money &A, int l)
{
    A = A * l;
    return A;
}

bool operator==(Money &A, Money &B)
{
    refresh(A);
    refresh(B);
    if(A.dollar == B.dollar && A.cent == B.cent)
        return true;
    return false;
}

bool operator!=(Money &A, Money &B)
{
    refresh(A);
    refresh(B);
    if(A == B)
        return false;
    return true;
}

bool operator>(Money &A, Money &B)
{
    long int ax = A.full_cent();
    long int bx = B.full_cent();
    if (ax > bx)
        return true;
    return false;
}

bool operator<(Money &A, Money &B)
{
    long int ax = A.full_cent();
    long int bx = B.full_cent();
    if (ax < bx)
        return true;
    return false;
}

ostream& operator<<(ostream& os, const Money &money)
{
    os << money.dollar << " dollars, " << money.cent << " pennies" << endl;
    os << "//////////////////////////" << endl;
    return os;
}

/////////////////////////////////////////////////////////////

class IEH
{
    int IEH_type;
    int limitation;
};

class Capital
{
    int capital_type;
    Money capital_value;
};

class Work
{
    int work_type;
    Money salary;
    work_healthy_t type;
};

class Healthy
{
    bool smoke;
    bool alchocol;
};

class Client
{
protected:
    std::string name;
    std::string surname;
    int age;
    ////////
    int n_IEH; //insu
    IEH *list;
    //////////
    Money base;
public:
    Client(std::string name, std::string surname, int age, IEH *list, Money base)
    {
        this->name = name;
        this->surname = surname;
        this->age = age;
        this->list = list;
        this->base = base;
    }
public:
    friend ostream& operator<<(ostream& os, const Client &client);
};

ostream& operator<<(ostream& os, const Client &client)
{
    os << "Name: " << client.name << endl;
    os << "Surname: " << client.surname << endl;
    os << "Age: " << client.age << endl;
    os << "Base capital: " << client.base << endl;

}
