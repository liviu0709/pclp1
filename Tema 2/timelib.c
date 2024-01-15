#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"

// TODO Task 1
TTime convertUnixTimestampToTime(unsigned int timestamp) {
	TTime result;
	result.sec = timestamp % 60;
	result.min = (timestamp / 60) % 60;
	result.hour = (timestamp / 3600) % 24;
	return result;
}

// TODO Task 2
TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp) {
	TDate result;
	int secunde_in_an = 365 * 24 * 3600;
	int secunde_in_zi = 24 * 3600;
	int secunde_30_zile = 30 * 24 * 3600;
	int secunde_31_zile = 31 * 24 * 3600;
	int secunde_februarie_nebisect = 28 * 24 * 3600;
	result.year = timestamp / secunde_in_an + 1970;
	timestamp = timestamp % secunde_in_an;
	int timestamp_zile = timestamp;
	// Ian
	if ( timestamp < secunde_31_zile ) {
		result.month = 1;
	// Ian + Febr
	} else if ( timestamp < secunde_31_zile + secunde_februarie_nebisect ) {
		timestamp_zile = timestamp - secunde_31_zile;
		result.month = 2;
	// Ian + Febr + Mar
	} else if ( timestamp < secunde_31_zile + secunde_februarie_nebisect + secunde_31_zile ) {
		timestamp_zile = timestamp - secunde_31_zile - secunde_februarie_nebisect;
		result.month = 3;
	// Ian + Febr + Mar + Apr
	} else if ( timestamp < secunde_31_zile + secunde_februarie_nebisect + secunde_31_zile + secunde_30_zile ) {
		timestamp_zile = timestamp - secunde_31_zile - secunde_februarie_nebisect - secunde_31_zile;
		result.month = 4;
	// Ian + Febr + Mar + Apr + Mai
	} else if ( timestamp < secunde_31_zile * 3 + secunde_februarie_nebisect + secunde_30_zile ) {
		timestamp_zile = timestamp - secunde_31_zile * 2 - secunde_februarie_nebisect - secunde_30_zile;
		result.month = 5;
	// Ian + Febr + Mar + Apr + Mai + Iun
	} else if ( timestamp < secunde_31_zile * 3 + secunde_februarie_nebisect + secunde_30_zile * 2 ) {
		timestamp_zile = timestamp - secunde_31_zile * 3 - secunde_februarie_nebisect - secunde_30_zile;
		result.month = 6;
	// Ian + Febr + Mar + Apr + Mai + Iun + Iul (31d)
	} else if ( timestamp < secunde_31_zile * 4 + secunde_februarie_nebisect + secunde_30_zile * 2 ) {
		timestamp_zile = timestamp - secunde_31_zile * 3 - secunde_februarie_nebisect - secunde_30_zile * 2;
		result.month = 7;
	// Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug (31d)
	} else if ( timestamp < secunde_31_zile * 5 + secunde_februarie_nebisect + secunde_30_zile * 2 ) {
		timestamp_zile = timestamp - secunde_31_zile * 4 - secunde_februarie_nebisect - secunde_30_zile * 2;
		result.month = 8;
	// Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep (30d)
	} else if ( timestamp < secunde_31_zile * 5 + secunde_februarie_nebisect + secunde_30_zile * 3 ) {
		timestamp_zile = timestamp - secunde_31_zile * 5 - secunde_februarie_nebisect - secunde_30_zile * 2;
		result.month = 9;
	// Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep + Oct (31d)
	} else if ( timestamp < secunde_31_zile * 6 + secunde_februarie_nebisect + secunde_30_zile * 3 ) {
		timestamp_zile = timestamp - secunde_31_zile * 5 - secunde_februarie_nebisect - secunde_30_zile * 3;
		result.month = 10;
	// Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep + Oct + Nov (30d)
	} else if ( timestamp < secunde_31_zile * 6 + secunde_februarie_nebisect + secunde_30_zile * 4 ) {
		timestamp_zile = timestamp - secunde_31_zile * 6 - secunde_februarie_nebisect - secunde_30_zile * 3;
		result.month = 11;
	// Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep + Oct + Nov + Dec (31d)
	} else if ( timestamp < secunde_31_zile * 7 + secunde_februarie_nebisect + secunde_30_zile * 4 ) {
		timestamp_zile = timestamp - secunde_31_zile * 6 - secunde_februarie_nebisect - secunde_30_zile * 4;
		result.month = 12;
	} else{
		result.month = 0;
		printf("Ceva nu e bine\n");
	}
	result.day = timestamp_zile / secunde_in_zi + 1;
	return result;
}

// TODO Task 3
TDate convertUnixTimestampToDate(unsigned int timestamp) {
	TDate result;
	result.year = 1970;
	int secunde_in_an_nebisect = 365 * 24 * 3600;
	int secunde_in_an_bisect = 366 * 24 * 3600;
	int secunde_in_zi = 24 * 3600;
	int secunde_30_zile = 30 * 24 * 3600;
	int secunde_31_zile = 31 * 24 * 3600;
	int timestamp_an_curent = 0;
	while ( timestamp_an_curent <= timestamp ) {
		if ( (result.year % 4 == 0 && result.year % 100 != 0) || result.year % 400 == 0) {
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
	int secunde_februarie_an_curent;
	if ( (result.year % 4 == 0 && result.year % 100 != 0) || result.year % 400 == 0)
		secunde_februarie_an_curent = 29 * 24 * 3600;
	else
		secunde_februarie_an_curent = 28 * 24 * 3600;

	// Aflam luna curenta a anului folosind aceeasi metoda ca la taskul anterior
	int timestamp_zile;
	// Ian
	if ( timestamp < secunde_31_zile ) {
		timestamp_zile = timestamp;
		result.month = 1;
	// Ian + Febr
	} else if ( timestamp < secunde_31_zile + secunde_februarie_an_curent ) {
		timestamp_zile = timestamp - secunde_31_zile;
		result.month = 2;
	// Ian + Febr + Mar
	} else if ( timestamp < secunde_31_zile + secunde_februarie_an_curent + secunde_31_zile ) {
		timestamp_zile = timestamp - secunde_31_zile - secunde_februarie_an_curent;
		result.month = 3;
	// Ian + Febr + Mar + Apr
	} else if ( timestamp < secunde_31_zile + secunde_februarie_an_curent + secunde_31_zile + secunde_30_zile ) {
		timestamp_zile = timestamp - secunde_31_zile - secunde_februarie_an_curent - secunde_31_zile;
		result.month = 4;
	// Ian + Febr + Mar + Apr + Mai
	} else if ( timestamp < secunde_31_zile * 3 + secunde_februarie_an_curent + secunde_30_zile ) {
		timestamp_zile = timestamp - secunde_31_zile * 2 - secunde_februarie_an_curent - secunde_30_zile;
		result.month = 5;
	// Ian + Febr + Mar + Apr + Mai + Iun
	} else if ( timestamp < secunde_31_zile * 3 + secunde_februarie_an_curent+ secunde_30_zile * 2 ) {
		timestamp_zile = timestamp - secunde_31_zile * 3 - secunde_februarie_an_curent - secunde_30_zile;
		result.month = 6;
	// Ian + Febr + Mar + Apr + Mai + Iun + Iul (31d)
	} else if ( timestamp < secunde_31_zile * 4 + secunde_februarie_an_curent + secunde_30_zile * 2 ) {
		timestamp_zile = timestamp - secunde_31_zile * 3 - secunde_februarie_an_curent - secunde_30_zile * 2;
		result.month = 7;
	// Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug (31d)
	} else if ( timestamp < secunde_31_zile * 5 + secunde_februarie_an_curent + secunde_30_zile * 2 ) {
		timestamp_zile = timestamp - secunde_31_zile * 4 - secunde_februarie_an_curent - secunde_30_zile * 2;
		result.month = 8;
	// Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep (30d)
	} else if ( timestamp < secunde_31_zile * 5 + secunde_februarie_an_curent + secunde_30_zile * 3 ) {
		timestamp_zile = timestamp - secunde_31_zile * 5 - secunde_februarie_an_curent- secunde_30_zile * 2;
		result.month = 9;
	// Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep + Oct (31d)
	} else if ( timestamp < secunde_31_zile * 6 + secunde_februarie_an_curent + secunde_30_zile * 3 ) {
		timestamp_zile = timestamp - secunde_31_zile * 5 - secunde_februarie_an_curent - secunde_30_zile * 3;
		result.month = 10;
	// Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep + Oct + Nov (30d)
	} else if ( timestamp < secunde_31_zile * 6 + secunde_februarie_an_curent + secunde_30_zile * 4 ) {
		timestamp_zile = timestamp - secunde_31_zile * 6 - secunde_februarie_an_curent - secunde_30_zile * 3;
		result.month = 11;
	// Ian + Febr + Mar + Apr + Mai + Iun + Iul + Aug + Sep + Oct + Nov + Dec (31d)
	} else if ( timestamp < secunde_31_zile * 7 + secunde_februarie_an_curent + secunde_30_zile * 4 ) {
		timestamp_zile = timestamp - secunde_31_zile * 6 - secunde_februarie_an_curent - secunde_30_zile * 4;
		result.month = 12;
	} else{
		result.month = 0;
		printf("Ceva nu e bine\n");
	}
	result.day = timestamp_zile / secunde_in_zi + 1;
	return result;
}

// TODO Task 4
TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp, TTimezone *timezones, int timezone_index) {
	TDateTimeTZ result;
	result.time = convertUnixTimestampToTime(timestamp + timezones[timezone_index].utc_hour_difference * 3600);
	result.date = convertUnixTimestampToDate(timestamp + timezones[timezone_index].utc_hour_difference * 3600);
	result.tz = &timezones[timezone_index];
	return result;
}

// TODO Task 5
unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ datetimetz) {
	unsigned int sol = 0;

	int secunde_in_an_nebisect = 365 * 24 * 3600;
	int secunde_in_an_bisect = 366 * 24 * 3600;

	sol += (datetimetz).time.sec;
	sol += (datetimetz).time.min * 60;
	sol += (datetimetz).time.hour * 3600;

	for ( int i = 1970 ; i < (datetimetz).date.year ; i++ ) {
		if ( (i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
			sol += secunde_in_an_bisect;
		else
			sol += secunde_in_an_nebisect;
	}

	int nr_zile_luni[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int an_curent = (datetimetz).date.year;
	if ( (an_curent % 4 == 0 && an_curent % 100 != 0) || an_curent % 400 == 0)
		nr_zile_luni[1] = 29;

	for ( int i = 0 ; i < (datetimetz).date.month - 1 ; i++ )
		sol += nr_zile_luni[i] * 24 * 3600;

	sol += ((datetimetz).date.day - 1) * 24 * 3600;

	sol -= ((int)(datetimetz).tz->utc_hour_difference) * 3600;

	return sol;
}

// TODO Task 6
void printDateTimeTZ(TDateTimeTZ datetimetz) {
	// [data] [luna (cuvânt)] [anul], [ora]:[minutul]:[secunda] [timezone name] (UTC[+/-][timezone utc hour diff])
	char *luni[12] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie",
		"iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
	if ( datetimetz.date.day < 10 )
		printf("0");
	printf("%d %s %d, ", datetimetz.date.day, luni[datetimetz.date.month - 1], datetimetz.date.year);
	if ( datetimetz.time.hour < 10 )
		printf("0");
	printf("%d:", datetimetz.time.hour);
	if ( datetimetz.time.min < 10 )
		printf("0");
	printf("%d:", datetimetz.time.min);	
	if ( datetimetz.time.sec < 10 )
		printf("0");
	printf("%d ", datetimetz.time.sec);
	printf("%s (UTC", datetimetz.tz->name);
	if ( datetimetz.tz->utc_hour_difference >= 0 )
		printf("+");
	printf("%d)\n", datetimetz.tz->utc_hour_difference);
}
