#ifndef _WORLD_TIME_H
#define _WORLD_TIME_H

#include "../Utils/utils.h"

#define TIME_COMPRESSION		1000.0f	// FAST TIME
//#define TIME_COMPRESSION		50.0f
#define SECONDS_PER_MINUTE				60
#define MINUTES_PER_HOUR				60
#define HOURS_PER_DAY					24
#define DAYS_PER_MONTH					30
#define MONTHS_PER_YEAR					12

// hardcode constants to avoid calculations and casts
// remember to update it in case above constants would be modified
#define F_MINUTES_PER_HOUR				60.0f
#define F_SECONDS_PER_HOUR				3600.0f

#define TIME_IN_HOURS(dt)				((double)dt.hour + (double)dt.minute / F_MINUTES_PER_HOUR + (double)dt.second / F_SECONDS_PER_HOUR)

class DateTime
{
public:
    friend ostream& operator<< (ostream& stream, const DateTime& dt) {
    	stream << dt.year << "-" << dt.month+1 << "-" << dt.day+1 << " " << dt.hour << ":" << dt.minute << ":" << dt.second;
    	return stream;
    };

    void add(int seconds) {
		second += seconds;
		while (second >= SECONDS_PER_MINUTE) {
			second -= SECONDS_PER_MINUTE;
			minute++;
			while (minute >= MINUTES_PER_HOUR) {
				minute -= MINUTES_PER_HOUR;
				hour++;
    			while (hour >= HOURS_PER_DAY) {
    				hour -= HOURS_PER_DAY;
    				day++;
        			while (day >= DAYS_PER_MONTH) {
        				day -= DAYS_PER_MONTH;
        				month++;
            			while (month >= MONTHS_PER_YEAR) {
            				month -= MONTHS_PER_YEAR;
            				year++;
            			}
        			}
    			}
			}
		}
    }

    double getHoursBased(bool maskSeconds, bool maskMinutes, bool maskHours, bool maskDays, bool maskMonths, bool maskYears) {
    	double seconds = maskSeconds ? 0 : ((double)second / (double)SECONDS_PER_MINUTE) / (double)MINUTES_PER_HOUR;
    	double minutes = maskMinutes ? 0 : (double)minute / (double)MINUTES_PER_HOUR;
    	double hours = maskHours ? 0 : (double)hour;
    	double days = maskDays ? 0 : (double) (day * HOURS_PER_DAY);
    	double months = maskMonths ? 0 : (double) (month * DAYS_PER_MONTH * HOURS_PER_DAY);
    	double years = maskYears ? 0 : (double) (year * MONTHS_PER_YEAR * DAYS_PER_MONTH * HOURS_PER_DAY);
    	return seconds + minutes + hours + days + months + years;
    }

	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

class WorldTime
{
public:
    static WorldTime * getInstance()
    {
        if (m_pInstance == NULL) m_pInstance = new WorldTime();
        return m_pInstance;
    };

    const DateTime& getTime() {
    	return dateTime;
    }

    void add(double delta) {
    	timeBuffer += delta * TIME_COMPRESSION;
    	if (timeBuffer >= 1) {
    		int seconds = (int) timeBuffer;
    		timeBuffer -= (double) seconds;
    		dateTime.add(seconds);
    	}
    };

private:
	WorldTime() {
		timeBuffer = 0;
		dateTime.year = 0;
		dateTime.month = 0;
		dateTime.day = 0;
		dateTime.hour = 6;
		dateTime.minute = 0;
		dateTime.second = 0;
	};
    static WorldTime * m_pInstance;

    DateTime dateTime;
    double timeBuffer;
};

// Helper alias
#define _time WorldTime::getInstance()

#endif
