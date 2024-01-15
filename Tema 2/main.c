#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"

int main(void) {
    TTimezone fus_orar[25];
    strcpy(fus_orar[0].name, "EET");
    fus_orar[0].utc_hour_difference = 0;
    strcpy(fus_orar[1].name, "CET");
    fus_orar[1].utc_hour_difference = 2;
    strcpy(fus_orar[2].name, "EET");
    fus_orar[2].utc_hour_difference = -8;
    TDateTimeTZ dt;
    /*
    4 5 1992 23 38 41
EET 2
    */
    dt.date = convertUnixTimestampToDateWithoutLeapYears(204269878);
    dt.time.hour = 0;
    dt.time.min = 0;
    dt.time.sec = 0;
    dt.tz = &fus_orar[0];
    printDateTimeTZ(dt);

}