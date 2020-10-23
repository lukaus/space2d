#include "date.h"


using namespace std;

void Date::addYears(unsigned int y)
{
    Date::addSeconds(y * 60 * 60 * 24 * 365); 
}

bool Date::isLeapYear()
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if(year % 16 == 0)
                return true;
            else
                return false;
        }
        else 
            return false;
    }
    else
    {
        return false;
    }
}

void Date::addMonths(unsigned int m)
{
    if (month == 11) // Dec
        Date::addSeconds(m * 60 * 60 * 24 * 31);
    else if (month == 1) // Feb
    {
        if (Date::isLeapYear())
            Date::addSeconds(m * 60 * 60 * 24 * 29);
        else
            Date::addSeconds(m * 60 * 60 * 24 * 28);
    }
    else
        Date::addSeconds(m * 60 * 60 * 24 * monthDays[month + 1]);
}

void Date::addDays(unsigned int d)
{

    Date::addSeconds(d * 60 * 60 * 24); 
}

void Date::addHours(unsigned int h)
{

    Date::addSeconds(h * 60 * 60); 
}

void Date::addMinutes(unsigned int m)
{
    Date::addSeconds(m * 60); 
}

void Date::addSeconds(unsigned int s)
{
    second += s;
    Date::propogate();
}
void Date::setYears(unsigned int s)
{
    year = s;
    Date::propogate();
}

void Date::setMonths(unsigned int s)
{
    month = s;
    Date::propogate();
}
void Date::setDays(unsigned int s)
{
    day = s;
    Date::propogate();
}

void Date::setHours(unsigned int s)
{
    hour = s;
    Date::propogate();
}

void Date::setMinutes(unsigned int s)
{
    minute = s;
    Date::propogate();
}

void Date::setSeconds(unsigned int s)
{
    second = s;
    Date::propogate();
}


void Date::propogate()
{
     minute += (second / 60);
     second = second % 60;

     hour += minute / 60;
     minute = minute % 60;

     day += hour / 24;
     hour = hour % 24;

     if ( day > monthDays[(month)])
     {
         if (month == 1)
         {
             if(!isLeapYear())
             {
                 day = 1;
                 month += 1;
             }
             else if (day > 29)
             {
                 day = 1;
                 month += 1;
             }
         }
         else
         {
            day = 1;
            month += 1;
         }
     }
     
     year += month / 12;
     month = month % 12;
}

    Date::Date()
{
    year = 2000;
    month = 0;
    day = 1;
    hour = 0;
    minute = 0;
    second = 0;
}
    Date::Date(int y, int mo, int d, 
            int h, int m, int s)
{
    year = y;
    month = mo-1;
    day = d;

    hour = h;
    minute = m;
    second = s;

}

ostream &operator<<(ostream &o, const Date &d)
{
    o << d.year << "/" << (d.month+1) << "/" << d.day << " " << d.hour << ":" << d.minute << ":" << d.second;
    return o;
}
