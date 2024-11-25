#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EVENTS 100
#define MAX_ATTENDEES 500
#define MAX_STRING_LEN 100

// Separate arrays for events
int event_ids[MAX_EVENTS];
char event_names[MAX_EVENTS][MAX_STRING_LEN];
char event_dates[MAX_EVENTS][MAX_STRING_LEN];
int event_count = 1; // Counter for events

// Separate arrays for attendees
char attendee_names[MAX_ATTENDEES][MAX_STRING_LEN];
char attendee_emails[MAX_ATTENDEES][MAX_STRING_LEN];
char attendee_preferences[MAX_ATTENDEES][MAX_STRING_LEN];
char attendee_attendance[MAX_ATTENDEES][MAX_STRING_LEN];
char attendee_events[MAX_ATTENDEES][MAX_STRING_LEN];
int attendee_count = 0; // Counter for attendees
// Function to mark attendance
void mark_attendance(char *event_name) {
    printf("\nList of attendees not present:\n");
    printf("------------------------------------\n");
    int absent_count = 0;

    for (int i = 0; i < attendee_count; i++) {
        if (strcmp(attendee_events[i], event_name) == 0 && strcmp(attendee_attendance[i], "False") == 0) {
            printf("S.No: %d\n", i + 1);
            printf("Name: %s\n", attendee_names[i]);
            printf("Email: %s\n", attendee_emails[i]);
            printf("Preference: %s\n", attendee_preferences[i]);
            printf("------------------------------------\n");
            absent_count++;
        }
    }

    if (absent_count == 0) {
        printf("No attendees are marked absent.\n");
    } else {
        int serial_no;
        while (1) {
            printf("\nType Serial No. of the attendee to mark present (0 to exit): ");
            scanf("%d", &serial_no);

            if (serial_no == 0) {
                break;
            } else if (serial_no > 0 && serial_no <= attendee_count) {
                if (strcmp(attendee_events[serial_no - 1], event_name) == 0) {
                    strcpy(attendee_attendance[serial_no - 1], "True");
                    printf("Attendance marked for: %s\n", attendee_names[serial_no - 1]);
                } else {
                    printf("Invalid selection. Please select a valid attendee for this event.\n");
                }
            } else {
                printf("Invalid Serial No.\n");
            }
        }
    }
}

// Function to search for an attendee
void search_attendee(char *event_name) {
    char search_name[MAX_STRING_LEN];
    int found = 0;

    printf("Enter the name of the attendee you want to search: ");
    getchar(); // Clear the input buffer
    fgets(search_name, MAX_STRING_LEN, stdin);
    search_name[strcspn(search_name, "\n")] = 0;

    for (int i = 0; i < attendee_count; i++) {
        if (strcmp(attendee_events[i], event_name) == 0 &&
            strncasecmp(attendee_names[i], search_name, strlen(search_name)) == 0) {
            printf("\nAttendee found: %s\n", attendee_names[i]);
            printf("------------------------------------\n");
            printf("Name: %s\n", attendee_names[i]);
            printf("Email: %s\n", attendee_emails[i]);
            printf("Preference: %s\n", attendee_preferences[i]);
            printf("Attended: %s\n", strcmp(attendee_attendance[i], "True") == 0 ? "Yes" : "No");
            printf("------------------------------------\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No attendee with the name '%s' found for the event '%s'.\n", search_name, event_name);
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

    event_ids[event_count - 1] = event_count;
    strcpy(event_names[event_count - 1], event_name);
    strcpy(event_dates[event_count - 1], event_date);

    event_count++;
}
// Function to list all events
void list_events() {
    printf("\nList of events:\n");
    if (event_count == 1) {
        printf("No events yet\n");
    } else {
        for (int i = 0; i < event_count - 1; i++) {
            printf("S.No: %d\n", event_ids[i]);
            printf("Event Name: %s\n", event_names[i]);
            printf("Event Date: %s\n", event_dates[i]);
            printf("------------------------------------\n");
        }
    }
}

// Function to display attendees for an event
void display_attendees(char *event_name) {
    int count = 0;

    printf("\nAttendees for event: %s\n", event_name);
    printf("------------------------------------\n");

    for (int i = 0; i < attendee_count; i++) {
        if (strcmp(attendee_events[i], event_name) == 0) {
            printf("S.No: %d\n", count + 1);
            printf("Name: %s\n", attendee_names[i]);
            printf("Email: %s\n", attendee_emails[i]);
            printf("Preference: %s\n", attendee_preferences[i]);
            printf("Attended: %s\n", strcmp(attendee_attendance[i], "True") == 0 ? "Yes" : "No");
            printf("------------------------------------\n");
            count++;
        }
    }

    if (count == 0) {
        printf("No attendees in the event\n");
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

    strcpy(attendee_names[attendee_count], name);
    strcpy(attendee_emails[attendee_count], email);
    strcpy(attendee_preferences[attendee_count], preference);
    strcpy(attendee_attendance[attendee_count], (attendance == 'Y' || attendance == 'y') ? "True" : "False");
    strcpy(attendee_events[attendee_count], event_name);

    attendee_count++;
}

// Function to display event summary
void event_summary(char *event_name) {
    int total = 0, veg = 0, non_veg = 0, present = 0;

    for (int i = 0; i < attendee_count; i++) {
        if (strcmp(attendee_events[i], event_name) == 0) {
            total++;
            if (strcmp(attendee_preferences[i], "non veg") == 0) {
                non_veg++;
            } else {
                veg++;
            }
            if (strcmp(attendee_attendance[i], "True") == 0) {
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
    event_ids[0] = 1;
    strcpy(event_names[0], "Python Workshop");
    strcpy(event_dates[0], "20/11/2024");

    // Predefined Attendee
    strcpy(attendee_names[0], "Kushagra Chandra");
    strcpy(attendee_emails[0], "kc@gmailcom");
    strcpy(attendee_preferences[0], "non veg");
    strcpy(attendee_attendance[0], "False");
    strcpy(attendee_events[0], "Python Workshop");
    attendee_count++;
    event_count++;

    int serial_no;
    char event_name[MAX_STRING_LEN];

    // Display and add events
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
    strcpy(event_name, event_names[serial_no - 1]);

    // Event-specific menu
    while (1) {
        int menu_choice;
        printf("\nMenu:\n");
        printf("1. See attendee details\n");
        printf("2. Add attendee\n");
        printf("3. Get event summary\n");
        printf("4. Mark attendance\n");
        printf("5. Search for attendee\n");
        printf("6. Exit\n");
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
                mark_attendance(event_name);
                break;
            case 5:
                search_attendee(event_name);
                break;
            case 6:
                printf("Thank you for using our program\nHave a nice day :)\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}
