#ifndef DATE_H
#define DATE_H
#include <iostream>

class Date
{
    private:
    int year;
    int month;
    int day;

    int hour;
    int minute;
    int second;

    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    public:

    void addYears(unsigned int );
    void addMonths(unsigned int );
    void addDays(unsigned int );

    void addHours(unsigned int );
    void addMinutes(unsigned int );
    void addSeconds(unsigned int );
    


    void setYears(unsigned int );
    void setMonths(unsigned int );
    void setDays(unsigned int );

    void setHours(unsigned int );
    void setMinutes(unsigned int );
    void setSeconds(unsigned int );


    bool isLeapYear();

    void propogate();

    Date(int, int, int, int, int, int);
    Date();

    friend std::ostream &operator<<(std::ostream &o, const Date &d);

};



#endif
