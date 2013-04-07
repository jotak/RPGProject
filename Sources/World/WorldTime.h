#ifndef _WORLD_TIME_H
#define _WORLD_TIME_H

#include "../Utils/utils.h"

#define DEFAULT_TIME_COMPRESSION		50.0f

class DateTime
{
public:
    friend ostream& operator<< (ostream& stream, const DateTime& dt) {
    	stream << dt.year << "-" << dt.month+1 << "-" << dt.day+1 << " " << dt.hour << ":" << dt.minute << ":" << dt.second;
    	return stream;
    };
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
    	double deltaWorld = delta * DEFAULT_TIME_COMPRESSION;
    	timeBuffer += deltaWorld;
    	if (timeBuffer >= 1) {
    		int seconds = (int) timeBuffer;
    		timeBuffer -= (double) seconds;
    		dateTime.second += seconds;
    		while (dateTime.second >= 60) {
    			dateTime.second -= 60;
    			dateTime.minute++;
    			while (dateTime.minute >= 60) {
    				dateTime.minute -= 60;
    				dateTime.hour++;
        			while (dateTime.hour >= 24) {
        				dateTime.hour -= 24;
        				dateTime.day++;
            			while (dateTime.day >= 30) {
            				dateTime.day -= 30;
            				dateTime.month++;
                			while (dateTime.month >= 12) {
                				dateTime.month -= 12;
                				dateTime.year++;
                			}
            			}
        			}
    			}
    		}
    	}
    };

private:
	WorldTime() {
		timeBuffer = 0;
		dateTime.year = 0;
		dateTime.month = 0;
		dateTime.day = 0;
		dateTime.hour = 0;
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
