#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"

enum { saizeci = 60, sec_in_ora = 3600, ore_in_zi = 24, zile_in_an_nebisect = 365,
treizeci = 30, treizeci_unu = 31, douazeci_si_opt = 28, an_inceput = 1970,
unu = 1, doi = 2, trei = 3, patru = 4, cinci = 5, sase = 6, sapte = 7, opt = 8,
noua = 9, zece = 10, unsprezece = 11, doisprezece = 12, o_suta = 100, patru_sute = 400 };

// Task 1
TTime convertUnixTimestampToTime(unsigned int timestamp) {
    TTime result;
    result.sec = timestamp % saizeci;
    result.min = (timestamp / saizeci) % saizeci;
    result.hour = (timestamp / sec_in_ora) % ore_in_zi;
    return result;
}

// Task 2
TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp) {
    TDate result;
    unsigned int secunde_in_an = zile_in_an_nebisect * ore_in_zi * sec_in_ora;
    unsigned int secunde_in_zi = ore_in_zi * sec_in_ora;
    unsigned int secunde_30_zile = treizeci * ore_in_zi * sec_in_ora;
    unsigned int secunde_31_zile = treizeci_unu * ore_in_zi * sec_in_ora;
    unsigned int secunde_februarie_nebisect = douazeci_si_opt * ore_in_zi * sec_in_ora;
    result.year = timestamp / secunde_in_an + an_inceput;
    timestamp = timestamp % secunde_in_an;
    unsigned int timestamp_zile = timestamp;
    // Ian
    if ( timestamp < secunde_31_zile ) {
        result.month = unu;
    // Ian + Febr
    } else if ( timestamp < secunde_31_zile + secunde_februarie_nebisect ) {
        timestamp_zile = timestamp - secunde_31_zile;
        result.month = doi;
    // Ian + Febr + Mar
    } else if ( timestamp < secunde_31_zile + secunde_februarie_nebisect + secunde_31_zile ) {
        timestamp_zile = timestamp - secunde_31_zile - secunde_februarie_nebisect;
        result.month = trei;
    // Ian + Febr + Mar + Apr
    } else if ( timestamp < secunde_31_zile + secunde_februarie_nebisect + secunde_31_zile + secunde_30_zile ) {
        timestamp_zile = timestamp - secunde_31_zile - secunde_februarie_nebisect - secunde_31_zile;
        result.month = patru;
    // Ian + Febr + Mar + Apr + Mai
    } else if ( timestamp < secunde_31_zile * 3 + secunde_februarie_nebisect + secunde_30_zile ) {
        timestamp_zile = timestamp - secunde_31_zile * 2 - secunde_februarie_nebisect - secunde_30_zile;
        result.month = cinci;
    // Ian + Febr + Mar + Apr + Mai + Iun
    } else if ( timestamp < secunde_31_zile * 3 + secunde_februarie_nebisect + secunde_30_zile * 2 ) {
        timestamp_zile = timestamp - secunde_31_zile * 3 - secunde_februarie_nebisect - secunde_30_zile;
        result.month = sase;
    // Ian + Febr + Mar + Apr + Mai + Iun + Iul (31d)
    } else if ( timestamp < secunde_31_zile * 4 + secunde_februarie_nebisect + secunde_30_zile * 2 ) {
        timestamp_zile = timestamp - secunde_31_zile * 3 - secunde_februarie_nebisect - secunde_30_zile * 2;
        result.month = sapte;
    // Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug (31d)
    } else if ( timestamp < secunde_31_zile * cinci + secunde_februarie_nebisect + secunde_30_zile * 2 ) {
        timestamp_zile = timestamp - secunde_31_zile * 4 - secunde_februarie_nebisect - secunde_30_zile * 2;
        result.month = opt;
    // Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep (30d)
    } else if ( timestamp < secunde_31_zile * cinci + secunde_februarie_nebisect + secunde_30_zile * 3 ) {
        timestamp_zile = timestamp - secunde_31_zile * cinci - secunde_februarie_nebisect - secunde_30_zile * 2;
        result.month = noua;
    // Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep + Oct (31d)
    } else if ( timestamp < secunde_31_zile * sase + secunde_februarie_nebisect + secunde_30_zile * 3 ) {
        timestamp_zile = timestamp - secunde_31_zile * cinci - secunde_februarie_nebisect - secunde_30_zile * 3;
        result.month = zece;
    // Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep + Oct + Nov (30d)
    } else if ( timestamp < secunde_31_zile * sase + secunde_februarie_nebisect + secunde_30_zile * 4 ) {
        timestamp_zile = timestamp - secunde_31_zile * sase - secunde_februarie_nebisect - secunde_30_zile * 3;
        result.month = unsprezece;
    // Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep + Oct + Nov + Dec (31d)
    } else if ( timestamp < secunde_31_zile * sapte + secunde_februarie_nebisect + secunde_30_zile * 4 ) {
        timestamp_zile = timestamp - secunde_31_zile * sase - secunde_februarie_nebisect - secunde_30_zile * 4;
        result.month = doisprezece;
    } else {
        result.month = 0;
        printf("Ceva nu e bine\n");
    }
    result.day = timestamp_zile / secunde_in_zi + 1;
    return result;
}

// Task 3
TDate convertUnixTimestampToDate(unsigned int timestamp) {
    TDate result;
    result.year = an_inceput;
    int secunde_in_an_nebisect = zile_in_an_nebisect * ore_in_zi * sec_in_ora;
    int secunde_in_an_bisect = (zile_in_an_nebisect + 1) * ore_in_zi * sec_in_ora;
    int secunde_in_zi = ore_in_zi * sec_in_ora;
    int secunde_30_zile = treizeci * ore_in_zi * sec_in_ora;
    int secunde_31_zile = treizeci_unu * ore_in_zi * sec_in_ora;
    int timestamp_an_curent = 0;
    while ( timestamp_an_curent <= timestamp ) {
        if ( (result.year % 4 == 0 && result.year % o_suta != 0) || result.year % patru_sute == 0 ) {
            if ( timestamp_an_curent + secunde_in_an_bisect > timestamp )
                break;
            timestamp_an_curent += secunde_in_an_bisect;
        } else {
            if ( timestamp_an_curent + secunde_in_an_nebisect > timestamp )
                break;
            timestamp_an_curent += secunde_in_an_nebisect;
        }
        result.year++;
    }
    timestamp -= timestamp_an_curent;
    static unsigned int secunde_februarie_an_curent;
    if ( (result.year % 4 == 0 && result.year % o_suta != 0) || result.year % patru_sute == 0)
        secunde_februarie_an_curent = (treizeci - 1) * ore_in_zi * sec_in_ora;
    else
        secunde_februarie_an_curent = (treizeci - 2) * ore_in_zi * sec_in_ora;

    // Aflam luna curenta a anului folosind aceeasi metoda ca la taskul anterior
    static unsigned int timestamp_zile;
    // Ian
    if ( timestamp < secunde_31_zile ) {
        timestamp_zile = timestamp;
        result.month = unu;
    // Ian + Febr
    } else if ( timestamp < secunde_31_zile + secunde_februarie_an_curent ) {
        timestamp_zile = timestamp - secunde_31_zile;
        result.month = doi;
    // Ian + Febr + Mar
    } else if ( timestamp < secunde_31_zile + secunde_februarie_an_curent + secunde_31_zile ) {
        timestamp_zile = timestamp - secunde_31_zile - secunde_februarie_an_curent;
        result.month = trei;
    // Ian + Febr + Mar + Apr
    } else if ( timestamp < secunde_31_zile + secunde_februarie_an_curent + secunde_31_zile + secunde_30_zile ) {
        timestamp_zile = timestamp - secunde_31_zile - secunde_februarie_an_curent - secunde_31_zile;
        result.month = patru;
    // Ian + Febr + Mar + Apr + Mai
    } else if ( timestamp < secunde_31_zile * 3 + secunde_februarie_an_curent + secunde_30_zile ) {
        timestamp_zile = timestamp - secunde_31_zile * 2 - secunde_februarie_an_curent - secunde_30_zile;
        result.month = cinci;
    // Ian + Febr + Mar + Apr + Mai + Iun
    } else if ( timestamp < secunde_31_zile * 3 + secunde_februarie_an_curent+ secunde_30_zile * 2 ) {
        timestamp_zile = timestamp - secunde_31_zile * 3 - secunde_februarie_an_curent - secunde_30_zile;
        result.month = sase;
    // Ian + Febr + Mar + Apr + Mai + Iun + Iul (31d)
    } else if ( timestamp < secunde_31_zile * 4 + secunde_februarie_an_curent + secunde_30_zile * 2 ) {
        timestamp_zile = timestamp - secunde_31_zile * 3 - secunde_februarie_an_curent - secunde_30_zile * 2;
        result.month = sapte;
    // Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug (31d)
    } else if ( timestamp < secunde_31_zile * cinci + secunde_februarie_an_curent + secunde_30_zile * 2 ) {
        timestamp_zile = timestamp - secunde_31_zile * 4 - secunde_februarie_an_curent - secunde_30_zile * 2;
        result.month = opt;
    // Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep (30d)
    } else if ( timestamp < secunde_31_zile * cinci + secunde_februarie_an_curent + secunde_30_zile * 3 ) {
        timestamp_zile = timestamp - secunde_31_zile * cinci - secunde_februarie_an_curent- secunde_30_zile * 2;
        result.month = noua;
    // Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep + Oct (31d)
    } else if ( timestamp < secunde_31_zile * sase + secunde_februarie_an_curent + secunde_30_zile * 3 ) {
        timestamp_zile = timestamp - secunde_31_zile * cinci - secunde_februarie_an_curent - secunde_30_zile * 3;
        result.month = zece;
    // Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep + Oct + Nov (30d)
    } else if ( timestamp < secunde_31_zile * sase + secunde_februarie_an_curent + secunde_30_zile * 4 ) {
        timestamp_zile = timestamp - secunde_31_zile * sase - secunde_februarie_an_curent - secunde_30_zile * 3;
        result.month = unsprezece;
    // Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep + Oct + Nov + Dec (31d)
    } else if ( timestamp < secunde_31_zile * sapte + secunde_februarie_an_curent + secunde_30_zile * 4 ) {
        timestamp_zile = timestamp - secunde_31_zile * sase - secunde_februarie_an_curent - secunde_30_zile * 4;
        result.month = doisprezece;
    } else {
        result.month = 0;
        printf("Ceva nu e bine\n");
    }
    result.day = timestamp_zile / secunde_in_zi + 1;
    return result;
}

// Task 4
TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp, TTimezone *timezones, int timezone_index) {
    TDateTimeTZ result;
    result.time = convertUnixTimestampToTime(timestamp + timezones[timezone_index].utc_hour_difference * sec_in_ora);
    result.date = convertUnixTimestampToDate(timestamp + timezones[timezone_index].utc_hour_difference * sec_in_ora);
    result.tz = &timezones[timezone_index];
    return result;
}

// Task 5
unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ datetimetz) {
    unsigned int sol = 0;

    unsigned int secunde_in_an_nebisect = zile_in_an_nebisect * ore_in_zi * sec_in_ora;
    unsigned int secunde_in_an_bisect = (zile_in_an_nebisect + 1) * ore_in_zi * sec_in_ora;

    sol += (datetimetz).time.sec;
    sol += (datetimetz).time.min * saizeci;
    sol += (datetimetz).time.hour * sec_in_ora;

    for ( int i = an_inceput ; i < (datetimetz).date.year ; i++ ) {
        if ( (i % 4 == 0 && i % o_suta != 0) || i % patru_sute == 0)
            sol += secunde_in_an_bisect;
        else
            sol += secunde_in_an_nebisect;
    }

    unsigned int nr_zile_luni[doisprezece] = {treizeci_unu, douazeci_si_opt, treizeci_unu,
    treizeci, treizeci_unu, treizeci, treizeci_unu, treizeci_unu, treizeci, treizeci_unu, treizeci, treizeci_unu};
    unsigned int an_curent = (datetimetz).date.year;
    if ( (an_curent % 4 == 0 && an_curent % o_suta != 0) || an_curent % patru_sute == 0)
        nr_zile_luni[1] = douazeci_si_opt + 1;

    for ( int i = 0 ; i < (datetimetz).date.month - 1 ; i++ )
        sol += nr_zile_luni[i] * ore_in_zi * sec_in_ora;

    sol += ((datetimetz).date.day - 1) * ore_in_zi * sec_in_ora;

    sol -= ((int)(datetimetz).tz->utc_hour_difference) * sec_in_ora;

    return sol;
}

// Task 6
void printDateTimeTZ(TDateTimeTZ datetimetz) {
    // [data] [luna (cuvânt)] [anul], [ora]:[minutul]:[secunda] [timezone name] (UTC[+/-][timezone utc hour diff])
    char *luni[doisprezece] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie",
        "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
    if ( datetimetz.date.day < zece )
        printf("0");
    printf("%d %s %d, ", datetimetz.date.day, luni[datetimetz.date.month - 1], datetimetz.date.year);
    if ( datetimetz.time.hour < zece )
        printf("0");
    printf("%d:", datetimetz.time.hour);
    if ( datetimetz.time.min < zece )
        printf("0");
    printf("%d:", datetimetz.time.min);
    if ( datetimetz.time.sec < zece )
        printf("0");
    printf("%d ", datetimetz.time.sec);
    printf("%s (UTC", datetimetz.tz->name);
    if ( datetimetz.tz->utc_hour_difference >= 0 )
        printf("+");
    printf("%d)\n", datetimetz.tz->utc_hour_difference);
}
