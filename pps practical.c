#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EVENTS 100
#define MAX_ATTENDEES 500
#define MAX_STRING_LEN 100

// Global arrays for storing events and attendees
char events[MAX_EVENTS][3][MAX_STRING_LEN];       // Events: S.No, Event Name, Event Date
char attendees[MAX_ATTENDEES][5][MAX_STRING_LEN]; // Attendees: Name, Email, Preference, Attendance, Event Name
int event_count = 1;                              // Counter for events
int attendee_count = 0;                           // Counter for attendees

// Function to list all events
void list_events() {
    printf("\nList of events:\n");
    if (event_count == 1) {
        printf("No events yet\n");
    } else {
        for (int i = 0; i < event_count - 1; i++) {
            printf("S.No: %s\n", events[i][0]);
            printf("Event Name: %s\n", events[i][1]);
            printf("Event Date: %s\n", events[i][2]);
            printf("------------------------------------\n");
        }
    }
}

// Function to add a new event
void add_event() {
    char event_name[MAX_STRING_LEN], event_date[MAX_STRING_LEN];

    printf("\nEnter event name: ");
    getchar(); // Clear the input buffer
    fgets(event_name, MAX_STRING_LEN, stdin);
    event_name[strcspn(event_name, "\n")] = 0; // Remove newline character

    printf("Enter event date (DD/MM/YYYY): ");
    fgets(event_date, MAX_STRING_LEN, stdin);
    event_date[strcspn(event_date, "\n")] = 0;

    sprintf(events[event_count - 1][0], "%d", event_count);
    strcpy(events[event_count - 1][1], event_name);
    strcpy(events[event_count - 1][2], event_date);

    event_count++;
}

// Function to display event details
void event_details(int serial_no) {
    printf("\nEvent selected: %s\n", events[serial_no - 1][1]);
}

// Function to display attendees for an event
void display_attendees(char *event_name) {
    int count = 0;

    printf("\nAttendees for event: %s\n", event_name);
    printf("------------------------------------\n");

    for (int i = 0; i < attendee_count; i++) {
        if (strcmp(attendees[i][4], event_name) == 0) {
            printf("S.No: %d\n", count + 1);
            printf("Name: %s\n", attendees[i][0]);
            printf("Email: %s\n", attendees[i][1]);
            printf("Preference: %s\n", attendees[i][2]);
            printf("Attended: %s\n", strcmp(attendees[i][3], "True") == 0 ? "Yes" : "No");
            printf("------------------------------------\n");
            count++;
        }
    }

    if (count == 0) {
        printf("No Attendees in the event\n");
    }
}

// Function to add an attendee
void add_attendee(char *event_name) {
    char name[MAX_STRING_LEN], email[MAX_STRING_LEN], preference[MAX_STRING_LEN], attendance;

    printf("\nEnter attendee name: ");
    getchar(); // Clear input buffer
    fgets(name, MAX_STRING_LEN, stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter attendee email: ");
    fgets(email, MAX_STRING_LEN, stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Enter attendee preference (Veg/Non-Veg): ");
    fgets(preference, MAX_STRING_LEN, stdin);
    preference[strcspn(preference, "\n")] = 0;

    printf("Present in event or not (Y/N): ");
    scanf(" %c", &attendance);

    strcpy(attendees[attendee_count][0], name);
    strcpy(attendees[attendee_count][1], email);
    strcpy(attendees[attendee_count][2], preference);
    strcpy(attendees[attendee_count][3], (attendance == 'Y' || attendance == 'y') ? "True" : "False");
    strcpy(attendees[attendee_count][4], event_name);

    attendee_count++;
}

// Function to display event summary
void event_summary(char *event_name) {
    int total = 0, veg = 0, non_veg = 0, present = 0;

    for (int i = 0; i < attendee_count; i++) {
        if (strcmp(attendees[i][4], event_name) == 0) {
            total++;
            if (strcmp(attendees[i][2], "non veg") == 0) {
                non_veg++;
            } else {
                veg++;
            }
            if (strcmp(attendees[i][3], "True") == 0) {
                present++;
            }
        }
    }

    printf("\nEvent Summary for %s\n", event_name);
    printf("------------------------------------\n");
    printf("Total Attendees: %d\n", total);
    printf("Veg Preference: %d\n", veg);
    printf("Non-Veg Preference: %d\n", non_veg);
    if (total > 0) {
        printf("Attendance Percentage: %.2f%%\n", (present / (float)total) * 100);
    } else {
        printf("Attendance Percentage: 0.00%%\n");
    }
}

// Main Function
int main() {
    // Predefined Event
    strcpy(events[0][0], "1");
    strcpy(events[0][1], "Python Workshop");
    strcpy(events[0][2], "20/11/2024");

    // Predefined Attendee
    strcpy(attendees[0][0], "Kushagra Chandra");
    strcpy(attendees[0][1], "kc@gmailcom");
    strcpy(attendees[0][2], "non veg");
    strcpy(attendees[0][3], "False");
    strcpy(attendees[0][4], "Python Workshop");
    attendee_count++;
    event_count++;

    int serial_no;
    char event_name[MAX_STRING_LEN];

    // Separate list and add events
    list_events();
    char choice;
    printf("\nWant to add more events (Y/N): ");
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y') {
        add_event();
        list_events();
    }

    printf("\nEnter S.No of the event you want to see details of: ");
    scanf("%d", &serial_no);
    strcpy(event_name, events[serial_no - 1][1]);
    event_details(serial_no);

    // Event-specific menu
    while (1) {
        int menu_choice;
        printf("\nMenu:\n");
        printf("1. See attendee details\n");
        printf("2. Add attendee\n");
        printf("3. Get event summary\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &menu_choice);

        switch (menu_choice) {
            case 1:
                display_attendees(event_name);
                break;
            case 2:
                add_attendee(event_name);
                break;
            case 3:
                event_summary(event_name);
                break;
            case 4:
                printf("Thank you for using our program\nHave a nice day :)\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}