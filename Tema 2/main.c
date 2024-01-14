#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"

int main(void) {
    TTimezone fus_orar[25];
    strcpy(fus_orar[0].name, "UTC");
    fus_orar[0].utc_hour_difference = -8;
    strcpy(fus_orar[1].name, "CET");
    fus_orar[1].utc_hour_difference = 2;
    strcpy(fus_orar[2].name, "EET");
    fus_orar[2].utc_hour_difference = -8;
    TDateTimeTZ dt;
    /*
    18 2 2010 17 27 8
PST -8
    */
    dt.date.day = 18;
    dt.date.month = 2;
    dt.date.year = 2010;
    dt.time.hour = 17;
    dt.time.min = 27;
    dt.time.sec = 8;
    dt.tz = &fus_orar[0];
    printDateTimeTZ(dt);


}