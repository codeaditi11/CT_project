#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants for maximum data
#define MAX_BUSES 3
#define MAX_USERS 5

// Arrays to store user information
char usernames[MAX_USERS][50] = {"user1", "user2", "user3", "user4", "user5"};
char passwords[MAX_USERS][50] = {"pass1", "pass2", "pass3", "pass4", "pass5"};

// Arrays to store bus information
int busIds[MAX_BUSES] = {101, 102, 103};
char from[MAX_BUSES][50] = {"City A", "City C", "City E"};
char to[MAX_BUSES][50] = {"City B", "City D", "City F"};
int total[MAX_BUSES] = {50, 40, 30};
int available[MAX_BUSES] = {50, 40, 30};
float cost[MAX_BUSES] = {500.0, 400.0, 300.0};

// Function prototypes
void showMain();
void showUserMenu();
int login(int i, char uname[], char pass[]);
void book(int i);
void cancel(int i);
void checkBus(int i);
void navigateMain(int loggedIn);
void navigateUser(int loggedIn);

// Function to display the main menu
void showMain() {
    printf("\n=== Welcome ===\n");
    printf("1. Log in\n");
    printf("2. Quit\n");
    printf("Pick an option: ");
}

// Function to display the user menu
void showUserMenu() {
    printf("\n-- User Options --\n");
    printf("1. Reserve Seats\n");
    printf("2. Cancel Booking\n");
    printf("3. View Bus Details\n");
    printf("4. Exit to Main\n");
    printf("Your option please: ");
}

// Recursive function to log in
int login(int i, char uname[], char pass[]) {
    if (i >= MAX_USERS) {
        return -1; // Login failed
    }
    if (strcmp(usernames[i], uname) == 0 && strcmp(passwords[i], pass) == 0) {
        return i; // Login successful
    }
    return login(i + 1, uname, pass); // Try the next user
}

// Recursive function to book tickets
void book(int i) {
    if (i >= MAX_BUSES) {
        printf("No bus found with that ID.\n");
        return;
    }

    printf("\nProvide Bus ID: ");
    int busNum;
    scanf("%d", &busNum);

    if (busIds[i] == busNum) {
        printf("How many seats? ");
        int seats;
        scanf("%d", &seats);

        if (seats > 0 && seats <= available[i]) {
            available[i] -= seats;
            printf("Booking successful! Seats left: %d\n", available[i]);
        } else {
            printf("Insufficient seats available!\n");
        }
        return;
    }
    book(i + 1); // Check next bus
}

// Recursive function to cancel tickets
void cancel(int i) {
    if (i >= MAX_BUSES) {
        printf("No bus found with that ID.\n");
        return;
    }

    printf("\nProvide Bus ID: ");
    int busNum;
    scanf("%d", &busNum);

    if (busIds[i] == busNum) {
        printf("How many seats to cancel? ");
        int seats;
        scanf("%d", &seats);

        if (seats > 0 && (available[i] + seats) <= total[i]) {
            available[i] += seats;
            printf("Cancellation successful! Seats left: %d\n", available[i]);
        } else {
            printf("Invalid seat count!\n");
        }
        return;
    }
    cancel(i + 1); // Check next bus
}

// Function to view bus details
void checkBus(int i) {
    if (i >= MAX_BUSES) {
        return;
    }

    printf("\nBus ID: %d\nFrom: %s\nTo: %s\nSeats Available: %d\nCost: %.2f\n",
           busIds[i], from[i], to[i], available[i], cost[i]);
    checkBus(i + 1); // Recursively display next bus
}

// Navigate between menus
void navigateMain(int loggedIn) {
    int choice;
    do {
        showMain();
        scanf("%d", &choice);

        if (choice == 1) {
            char uname[50], pass[50];
            printf("\nUsername: ");
            scanf("%s", uname);
            printf("Password: ");
            scanf("%s", pass);

            loggedIn = login(0, uname, pass);
            if (loggedIn >= 0) {
                printf("\nWelcome, %s!\n", usernames[loggedIn]);
                navigateUser(loggedIn);
            } else {
                printf("\nInvalid credentials. Try again.\n");
            }
        }
    } while (choice != 2);
}

void navigateUser(int loggedIn) {
    int choice;
    do {
        showUserMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                book(0);
                break;
            case 2:
                cancel(0);
                break;
            case 3:
                checkBus(0);
                break;
            case 4:
                return;
            default:
                printf("Invalid option. Try again.\n");
        }
    } while (choice != 4);
}

// Main function
int main() {
    navigateMain(-1);
    printf("\nGoodbye!\n");
    return 0;
}
