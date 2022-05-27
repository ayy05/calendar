#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MONTHS 12

enum days { SUN, MON, TUE, WED, THUR, FRI, SAT };
enum months { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char *month_name[] = {"January", "February", "March",     "April",   "May",      "June",
                            "July",    "August",   "September", "October", "November", "December"};

void print_calendar(int year, int columns);
void leap_year(int year);
int get_first_day(int year, int month);

int main(int argc, char *argv[]) {
    if (argc == 3) {
        int year = strtol(argv[1], NULL, 10);
        int columns = strtol(argv[2], NULL, 10);
        if (columns <= 0) {
            printf("Enter valid column number.\n");
            return 1;
        }

        leap_year(year);
        print_calendar(year, columns);

        return 0;
    }

    printf("Needs 2 argument: year, columns\n");
    return 1;
}

void print_calendar(int year, int columns) {
    enum months month = JAN;
    int i, j, k, max_days, last_start = 0, rows;
    int days[NUM_MONTHS];

    /* Zeller's congruence */
    for (i = 0; i <= DEC; i++) {
        days[i] = get_first_day(year, i);
    }

    printf("\n%*d\n", (22 * columns) / 2, year);

    rows = (int) ((12.0 / columns) + 0.9);

    while (rows--) {
        if (month + columns > NUM_MONTHS) {
            columns = NUM_MONTHS - month;
        }

        last_start = month;
        for (i = 0; i < columns; i++) {
            if (days[month + i] > days[last_start] || (days[month + i] >= days[last_start] && month + i - 1 == FEB))
                last_start = month + i;
        }

        for (i = 0; i < columns; i++) {
            printf("%*s%s", (20 - (int) strlen(month_name[month + i])) / 2, " ", month_name[month + i]);
            printf("  ");
            printf("%*s", 20 - (20 - (int) strlen(month_name[month + i])) / 2 - (int) strlen(month_name[month + i]), " ");
        }

        printf("\n");

        for (i = 0; i < columns; i++) {
            printf("%-22s", "Su Mo Tu We Th Fr Sa");
        }

        printf("\n");

        for (i = 0; i < columns; i++) {
            for (k = 0; k < days[month + i]; k++)
                printf("   ");

            k = 1;
            j = days[month + i];
            while (j++ < 7) {
                printf("%2d ", k++);
            }
            days[month + i] = k;

            printf(" ");
        }

        printf("\n");

        while (days[last_start] <= days_in_month[last_start]) {
            for (i = 0; i < columns; i++) {
                max_days = days_in_month[month + i];

                if (days[month + i] != 0) {
                    j = 0;

                    while (j++ < 7)
                        if (days[month + i] <= max_days)
                            printf("%2d ", days[month + i]++);
                        else
                            printf("   ");

                    printf(" ");
                }
            }
            
            printf("\n");
        }

        month += columns;
        printf("\n");
    }
}

void leap_year(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        days_in_month[FEB]++;
}

int get_first_day(int year, int month) {
    if (--month < 1) {
        month += NUM_MONTHS;
        year--;
    }

    return ((26 * month - 2) / 10 + 1 + (year % 100) + ((year % 100) / 4) + ((year / 100) / 4) +
            (5 * (year / 100))) % 7;
}