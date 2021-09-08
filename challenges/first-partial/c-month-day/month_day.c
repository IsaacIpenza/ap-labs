#include <stdio.h>
#include <stdlib.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

void month_day(int year, int yearday, int *pmonth, int *pday){

    if (year < 1){
        printf("Invalid number of year\n");
        return;
    }

    int leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if(yearday < 1 || (leap == 0 && yearday > 365) || (leap == 1 && yearday > 366)){
        printf("Invalid number of yearday\n");
        return;
    }

    int totalMonths = 12;
    int dayTmp = 0;

    for(int i = 0; i <= totalMonths; i++){
        dayTmp += daytab[leap][i];


        if(dayTmp >= yearday){
            dayTmp -= daytab[leap][i];

            *pday = yearday - dayTmp;
            *pmonth = i;
            return;
        }
    }
}

char *month_name(int n) {

   static char *name[] = {
       "Illegal month",
       "January", "February", "March",
       "April", "May", "June",
       "July", "August", "September",
       "October", "November", "December"
   };

   return (n < 1 || n > 12) ? name[0] : name[n];
}


int main(int argc, char **argv) {
    
    if(argc < 3){
        printf("Invalid number of arguments\n");
        return 0;
    }

    int month = 0;
    int day = 0;

    month_day(atoi(argv[1]), atoi(argv[2]), &month, &day);

    if(month == 0 && day == 0){
        printf("Change your arguments\n");
    }else{
        printf("%s %d, %d\n", month_name(month), day, atoi(argv[1]));
    }
    
    return 0;
}
