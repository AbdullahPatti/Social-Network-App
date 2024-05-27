#pragma once
#include <iostream>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date();
    ~Date();
    void Set_Date(int d, int m, int y);
    Date(int d, int m, int y);
    void PrintDate() const;
    int getDay();
    int getMonth();
    int getYear();
    void setDay(int day);
    void setMonth(int month);
    void setyYear(int year);

};