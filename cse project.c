#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int isLeapYear(int year);
int getDaysInMonth(int month, int year);
int getDayOfWeek(int day, int month, int year);
void printMonth(int month, int year);
void printYear(int year);
void printDayOfWeek(int day, int month, int year);
int dayOfYear(int day, int month, int year);
void dateDifference(int day1, int month1, int year1, int day2, int month2, int year2);
void addDays(int day, int month, int year, int daysToAdd);
void displayMenu();

int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int year;
                printf("Enter year: ");
                scanf("%d", &year);
                printYear(year);
                break;
            }
            case 2: {
                int day, month, year;
                printf("Enter day: ");
                scanf("%d", &day);
                printf("Enter month: ");
                scanf("%d", &month);
                printf("Enter year: ");
                scanf("%d", &year);
                printDayOfWeek(day, month, year);
                break;
            }
            case 3: {
                int day, month, year;
                printf("Enter day: ");
                scanf("%d", &day);
                printf("Enter month: ");
                scanf("%d", &month);
                printf("Enter year: ");
                scanf("%d", &year);
                printf("Day of year: %d\n", dayOfYear(day, month, year));
                break;
            }
            case 4: {
                int day1, month1, year1, day2, month2, year2;
                printf("Enter first date (day month year): ");
                scanf("%d %d %d", &day1, &month1, &year1);
                printf("Enter second date (day month year): ");
                scanf("%d %d %d", &day2, &month2, &year2);
                dateDifference(day1, month1, year1, day2, month2, year2);
                break;
            }
            case 5: {
                int day, month, year, daysToAdd;
                printf("Enter day: ");
                scanf("%d", &day);
                printf("Enter month: ");
                scanf("%d", &month);
                printf("Enter year: ");
                scanf("%d", &year);
                printf("Enter number of days to add: ");
                scanf("%d", &daysToAdd);
                addDays(day, month, year, daysToAdd);
                break;
            }
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Print calendar for a year\n");
    printf("2. Find day of the week for a specific date\n");
    printf("3. Find day number within the year\n");
    printf("4. Calculate difference between two dates\n");
    printf("5. Add days to a date\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

// Function to check if a year is a leap year
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to get the number of days in a month
int getDaysInMonth(int month, int year) {
    switch(month) {
        case 1: return 31;
        case 2: return isLeapYear(year) ? 29 : 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;
    }
}

// Function to get the day of the week for a given date using Sakamoto's method
int getDayOfWeek(int day, int month, int year) {
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    if (month < 3) {
        year -= 1;
    }
    return (year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
}

// Function to print the calendar for a given month and year
void printMonth(int month, int year) {
    char *months[] = { "January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December" };
    int days = getDaysInMonth(month, year);
    int startDay = getDayOfWeek(1, month, year);

    printf("\n  ------------%s-------------\n", months[month - 1]);
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    // Print leading spaces for the first day of the month
    for (int i = 0; i < startDay; i++) {
        printf("     ");
    }

    // Print the days of the month
    for (int day = 1; day <= days; day++) {
        printf("%5d", day); // Print each day with a width of 5 characters
        if ((startDay + day) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

// Function to print the calendar for a given year
void printYear(int year) {
    for (int month = 1; month <= 12; month++) {
        printMonth(month, year);
    }
}

// Function to print the name of the day of the week for a given date
void printDayOfWeek(int day, int month, int year) {
    char *daysOfWeek[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    int dayOfWeek = getDayOfWeek(day, month, year);
    printf("The day of the week for %d-%d-%d is: %s\n", day, month, year, daysOfWeek[dayOfWeek]);
}

// Function to get the day number within the year for a given date
int dayOfYear(int day, int month, int year) {
    int days = day;
    for (int i = 1; i < month; i++) {
        days += getDaysInMonth(i, year);
    }
    return days;
}

// Function to calculate the difference between two dates
void dateDifference(int day1, int month1, int year1, int day2, int month2, int year2) {
    int n1 = year1 * 365 + day1;
    for (int i = 0; i < month1 - 1; i++) {
        n1 += getDaysInMonth(i + 1, year1);
    }
    n1 += year1 / 4 - year1 / 100 + year1 / 400;

    int n2 = year2 * 365 + day2;
    for (int i = 0; i < month2 - 1; i++) {
        n2 += getDaysInMonth(i + 1, year2);
    }
    n2 += year2 / 4 - year2 / 100 + year2 / 400;

    printf("Difference: %d days\n", abs(n2 - n1));
}

// Function to add days to a date and print the new date
void addDays(int day, int month, int year, int daysToAdd) {
    while (daysToAdd > 0) {
        int daysInMonth = getDaysInMonth(month, year);
        if (day + daysToAdd <= daysInMonth) {
            day += daysToAdd;
            daysToAdd = 0;
        } else {
            daysToAdd -= (daysInMonth - day + 1);
            day = 1;
            if (++month > 12) {
                month = 1;
                year++;
            }
        }
    }
    printf("New date: %d-%d-%d\n", day, month, year);
}
