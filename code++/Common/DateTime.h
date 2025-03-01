#ifndef DATETIME_H
#define DATETIME_H

class DateTime
{
    time_t m_current_time;
public:
    DateTime() 
    {
        time(&m_current_time);
    }

    static DateTime Now() { return DateTime{}; }

    DateTime AddDays(double d) const
    {
        DateTime r = *this;

        r.m_current_time += (time_t)(d * 24 * 3600);
        return r;
    }

    bool operator>=(DateTime const &right) const
    {
        return m_current_time >= right.m_current_time;
    }
};

#endif
