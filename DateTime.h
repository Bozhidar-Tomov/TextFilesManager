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

    bool operator<(const DateTime &rhs) const;
    void print() const;
};