/*
 * CurrentTime.h
 *
 *  Created on: 23 Nov 2017
 *      Author: betran
 */

#ifndef CURRENTTIME_H_
#define CURRENTTIME_H_


// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string get_current_date_time() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

#endif /* CURRENTTIME_H_ */
