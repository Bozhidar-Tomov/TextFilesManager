#include <iostream>
#include "DateTime.h"

DateTime::DateTime(unsigned day, unsigned month, unsigned year,
                   unsigned hours, unsigned mins, unsigned secs)
{
    this->date = Date(day, month, year);
    this->time = Time(hours, mins, secs);
}

bool DateTime::operator<(const DateTime &rhs) const
{
    return this->date < rhs.date && this->time < rhs.time;
}

void DateTime::print() const
{
    this->date.print();
    std::cout << ", at ";
    this->time.print(true);
}