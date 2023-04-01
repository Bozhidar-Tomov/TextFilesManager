#include "Date.h"
#include "Time.h"

struct DateTime
{
private:
    Date date;
    Time time;

public:
    DateTime() = default;
    DateTime(unsigned day, unsigned month, unsigned year,
             unsigned hours, unsigned mins, unsigned secs);

    // const Date &getDate() const;
    // const Time &getTime() const;

    void print() const;
};