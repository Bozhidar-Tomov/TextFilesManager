#include <iostream>
#include "DateTime.h"

DateTime::DateTime(unsigned day, unsigned month, unsigned year,
                   unsigned hours, unsigned mins, unsigned secs)
{
    this->date = Date(day, month, year);
    this->time = Time(hours, mins, secs);
}

// const Date &DateTime::getDate() const
// {
//     return this->date;
// }
// const Time &DateTime::getTime() const
// {
//     return this->time;
// }

void DateTime::print() const
{
    this->date.print();
    std::cout << ", at ";
    this->time.print(true);
}