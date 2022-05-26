#include <stdio.h>
#include <stdlib.h>

enum days { SUN, MON, TUE, WED, THUR, FRI, SAT };
enum months { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char *month_name[] = {"January", "February", "March", "April", "May", "June", "July", 
                      "August", "September", "October", "November", "December"};

void print_calendar(int year);
void leap_year(int year);

int main(int argc, char *argv[]) {
    if(argc == 2) {
        int year = strtol(argv[1], NULL, 10);

        leap_year(year);
        print_calendar(year);

        return 0;
    }
    
    printf("Needs 1 argument: year\n");
    return 1;
}

void print_calendar(int year) {
    enum days first_day;
    enum months month = JAN;
    int i, j, max_days;

    year--;
    /* Zeller's congruence */
    first_day = ((26 * 11 - 2)/10 + 1 + (year % 100) + ((year % 100) / 4) + ((year / 100) / 4) + (5 * (year / 100))) % 7;
    
    while (month <= DEC) {
        max_days = days_in_month[month];

        printf("\n%s:\n", month_name[month++]); 

        if (first_day != 0) {
            for(i = 0; i < first_day; i++)
                printf("   ");

            i = 1;
            j = first_day;
            while (j++ <= 6) {
                printf("%2d ", i++);
            }
        } else {
            i = 1;
        }

        while(i <= max_days) {
            if((i + first_day - 1) % 7 == 0)
                printf("\n");
            
            printf("%2d ", i++);
        }
        
        first_day = (i + first_day - 1) % 7;

        printf("\n");
    }
}

void leap_year(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400))
            days_in_month[1]++;
}

