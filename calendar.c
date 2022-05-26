#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

        leap_year(year);
        print_calendar(year, columns);

        return 0;
    }

    printf("Needs 2 argument: year, columns\n");
    return 1;
}

void print_calendar(int year, int columns) {
    enum months month = JAN;
    int i, j, k, max_days;
    int f_days[3], c_days[3] = {0, 0, 0};

    printf("\n%d\n", year);

    while (month + 2 <= DEC) {
        /* Zeller's congruence */
        f_days[0] = get_first_day(year, month);
        f_days[1] = get_first_day(year, month + 1);
        f_days[2] = get_first_day(year, month + 2);

        for (k = 0; k < 3; k++) {
            printf("%-22s", month_name[month + k]);
        }

        printf("\n");

        for (k = 0; k < 3; k++) {
            printf("%-22s", "Su Mo Tu We Th Fr Sa");
        }

        printf("\n");

        for (k = 0; k < 3; k++) {
            for (i = 0; i < f_days[k]; i++)
                printf("   ");

            i = 1;
            j = f_days[k];
            while (j++ <= 6) {
                printf("%2d ", i++);
            }
            c_days[k] = i;

            printf(" ");
        }

        printf("\n");

        while (c_days[0] < days_in_month[month] || c_days[1] < days_in_month[month + 1] ||
               c_days[2] < days_in_month[month + 2]) {
            for (k = 0; k < 3; k++) {
                max_days = days_in_month[month + k];
                if (c_days[k] != 0) {
                    j = 0;
                    while (j++ < 7)
                        if (c_days[k] <= max_days)
                            printf("%2d ", c_days[k]++);
                        else
                            printf("   ");
                    printf(" ");
                }
            }
            printf("\n");
        }

        month += 3;
        printf("\n");
    }
}

void leap_year(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        days_in_month[FEB]++;
}

int get_first_day(int year, int month) {
    month--;
    if (month < 1) {
        month += 12;
        year--;
    }

    return ((26 * month - 2) / 10 + 1 + (year % 100) + ((year % 100) / 4) + ((year / 100) / 4) +
            (5 * (year / 100))) % 7;
}