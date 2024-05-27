#include"Date.h"


Date::Date() {
    day = 1;
    month = 3;
    year = 2004;
}

void Date::setDay(int Day) {
    day = Day;
}

void Date::setMonth(int Month) {
    month = Month;
}

void Date::setyYear(int y) {
    year = y;
}

Date::Date(int D, int M, int Y) {
    day = D;
    month = M;
    year = Y;
}

Date::~Date() {
//Destructor
}

void Date::Set_Date(int D, int M, int Y) {
    day = D;
    month = M;
    year = Y;
}

void Date::PrintDate() const {
    cout << "(" << day << "/" << month << "/" << year << ")" << endl;
}


int Date::getDay() {
    return day;
}

int Date::getMonth() {
    return month;
}

int Date::getYear() {
    return year;
}

