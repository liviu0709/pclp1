#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"

int main(void) {
    TTimezone fus_orar[25];
    strcpy(fus_orar[0].name, "UTC");
    fus_orar[0].utc_hour_difference = 0;
    strcpy(fus_orar[1].name, "CET");
    fus_orar[1].utc_hour_difference = 2;
    strcpy(fus_orar[2].name, "EET");
    fus_orar[2].utc_hour_difference = -8;
    TDateTimeTZ dt;
    dt.date.day = 21;
    dt.date.month = 12;
    dt.date.year = 2023;
    dt.time.hour = 15;
    dt.time.min = 38;
    dt.time.sec = 36;
    dt.tz = &fus_orar[1];
    printf("%d\n", convertDateTimeTZToUnixTimestamp(dt));
    printDateTimeTZ(dt);


}