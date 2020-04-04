#include <iostream>
#include <math.h>
#include <string.h>
#include "types.h"

const int MAX_YEAR = 2100;

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

int day_in_month(int month, int year)
{
    int day = 0;
    switch (month)
    {
    case 1:
        day = 31; 
        break;
    case 3:
        day = 31; 
        break;
    case 5:
        day + 31; 
        break;
    case 7:
        day = 31; 
        break;
    case 8:
        day = 31; 
        break;
    case 10:
        day += 31; 
        break;
    case 12:
        day = 31; 
        break;
    case 4:
        day = 30; 
        break;
    case 6:
        day = 30; 
        break;
    case 9:
        day = 30; 
        break;
    case 11:
        day = 30; 
        break;
    case 2:
        if ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0))
                day = 29;
            else
                day = 28;
    default:
        break;
    }
    return day;
}


class Date
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
public:
    Date(int day, int month, int year)
    {
        if((year < 0) || (year > MAX_YEAR))
        {
            cout << "Wrong format for year!" << endl;
            exit(-1);
        }  
        else
            this->year = (unsigned int)year;

        if ((month < 1) || (month > 12))
        {
            cout << "Wrong format for month!" << endl;
            exit(-1);
        }
        else
        this->month = (unsigned int)month;
        if ((day < 0) || (day > day_in_month(month, year)))
        {
            cout << "Wrong format for day!" << endl;
            exit(-1);
        }
        else
            this->day = (unsigned int)day;
    }
    void set_day(unsigned int day);
    void set_month(unsigned int month);
    void set_year(unsigned int year);
    
    unsigned int get_day();
    unsigned int get_month();
    unsigned int get_year();

    long int full_day();

    friend unsigned long operator-(Date &A, Date &B);

    friend bool operator==(Date &A, Date &B);
    friend bool operator!=(Date &A, Date &B);
    friend bool operator>(Date &A, Date &B);
    friend bool operator<(Date &A, Date &B);
    friend ostream& operator<<(ostream& os, const Date &date);
};

void Date::set_day(unsigned int day)
{
    this->day = day;
}

void Date::set_month(unsigned int month)
{
    this->month = month;
}

void Date::set_year(unsigned int year)
{
    this->year = year;
}

unsigned int Date::get_day()
{
    return day;
}

unsigned int Date::get_month()
{
    return month;
}

unsigned int Date::get_year()
{
    return year;
}

long int Date::full_day()
{
    int bissextile =  ((year - 1) / 4) - ((year - 1) / 100) + ((year - 1) / 400) + 1;
    int d_t_now = 0;
    for (int i = month - 1; i > 0; i--)
    {
        d_t_now += day_in_month(i, year);
    }
    cout << bissextile << " " << d_t_now << " " << day << endl;
    return year * 365 + bissextile + d_t_now + day;
}

unsigned long operator-(Date &A, Date &B)
{
    long int d = A.full_day() - B.full_day();
    if (d >= 0)
        return d;
    return -1;
}

bool operator==(Date &A, Date &B)
{
    if(A.full_day() == B.full_day())
        return true;
    return false;
}

bool operator!=(Date &A, Date &B)
{
    if(A.full_day() != B.full_day())
        return true;
    return false;
}

bool operator<(Date &A, Date &B)
{
    if(A.full_day() < B.full_day())
        return true;
    return false;
}

bool operator>(Date &A, Date &B)
{
    if(A.full_day() > B.full_day())
        return true;
    return false;
}

ostream& operator<<(ostream& os, const Date &date)
{
    if(date.day < 10)
        os << "0";
    os << date.day << ".";
    if(date.month < 10)
        os << "0";
    os << date.month << ".";
    if(date.year < 1000)
        os << "0";
    if(date.year < 100)
        os << "0";
    if(date.year < 10)
        os << "0";
    os << date.year << endl;
    return os;
}

////////////////////////////////////////////////////////////

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
