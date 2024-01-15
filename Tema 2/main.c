#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"

int main(void) {
    TTimezone fus_orar[25];
    snprintf(fus_orar[0].name, sizeof(fus_orar[0].name), "EET");
    fus_orar[0].utc_hour_difference = 0;
    snprintf(fus_orar[1].name, sizeof(fus_orar[1].name), "CET");
    fus_orar[1].utc_hour_difference = 2;
    snprintf(fus_orar[2].name, sizeof(fus_orar[2].name), "EET");
    fus_orar[2].utc_hour_difference = -8;
    TDateTimeTZ dt;
    dt.date = convertUnixTimestampToDateWithoutLeapYears(204269878);
    dt.time.hour = 0;
    dt.time.min = 0;
    dt.time.sec = 0;
    dt.tz = &fus_orar[0];
    printDateTimeTZ(dt);
}
