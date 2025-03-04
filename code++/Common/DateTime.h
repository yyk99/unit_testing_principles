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

    DateTime(int yyyy, int mm, int dd)
    {
        std::tm tm{}; // Zero initialise
        tm.tm_year = yyyy - 1900;
        tm.tm_mon = mm - 1;
        tm.tm_mday = dd;
        // tm.tm_hour = 10;
        // tm.tm_min = 15;
        // tm.tm_isdst = 0; // Not daylight saving

        m_current_time = std::mktime(&tm);
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

    bool operator== (DateTime const &right) const
    {
        return m_current_time == right.m_current_time;
    }
};

#endif
