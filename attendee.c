#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EVENTS 100
#define MAX_ATTENDEES 500
#define MAX_NAME_LEN 50
#define MAX_EMAIL_LEN 100
#define MAX_DATE_LEN 20

typedef struct {
    int serial_no;
    char name[MAX_NAME_LEN];
    char date[MAX_DATE_LEN];
} Event;

typedef struct {
    char name[MAX_NAME_LEN];
    char email[MAX_EMAIL_LEN];
    char preference[MAX_NAME_LEN];
    int attended; // 1 for true, 0 for false
    int event_serial_no;
} Attendee;

Event events[MAX_EVENTS];
Attendee attendees[MAX_ATTENDEES];
int event_count = 1;
int attendee_count = 0;

void list_events() {
    printf("List of events:\n");
    if (event_count == 1) {
        printf("No events yet.\n");
    } else {
        printf("%-5s %-30s %-15s\n", "S.No", "Event Name", "Event Date");
        for (int i = 0; i < event_count - 1; i++) {
            printf("%-5d %-30s %-15s\n", events[i].serial_no, events[i].name, events[i].date);
        }
    }
}

void add_event() {
    printf("Enter event name: ");
    getchar(); // Clear the newline buffer
    fgets(events[event_count - 1].name, MAX_NAME_LEN, stdin);
    events[event_count - 1].name[strcspn(events[event_count - 1].name, "\n")] = 0; // Remove newline

    printf("Enter event date (DD/MM/YYYY): ");
    fgets(events[event_count - 1].date, MAX_DATE_LEN, stdin);
    events[event_count - 1].date[strcspn(events[event_count - 1].date, "\n")] = 0; // Remove newline

    events[event_count - 1].serial_no = event_count;
    event_count++;
}

void view_event_details(int serial_no) {
    printf("Event selected: %s\n", events[serial_no - 1].name);
}

void view_attendees(int event_serial_no) {
    printf("%-5s %-30s %-30s %-15s %-10s\n", "S.No", "Name", "Email ID", "Preference", "Attended");
    int count = 0;
    for (int i = 0; i < attendee_count; i++) {
        if (attendees[i].event_serial_no == event_serial_no) {
            printf("%-5d %-30s %-30s %-15s %-10s\n", 
                i + 1, attendees[i].name, attendees[i].email, 
                attendees[i].preference, attendees[i].attended ? "Yes" : "No");
            count++;
        }
    }
    if (count == 0) {
        printf("No attendees for this event.\n");
    }
}

void add_attendee(int event_serial_no) {
    printf("Enter Attendee Name: ");
    getchar();
    fgets(attendees[attendee_count].name, MAX_NAME_LEN, stdin);
    attendees[attendee_count].name[strcspn(attendees[attendee_count].name, "\n")] = 0;

    printf("Enter Attendee Email: ");
    fgets(attendees[attendee_count].email, MAX_EMAIL_LEN, stdin);
    attendees[attendee_count].email[strcspn(attendees[attendee_count].email, "\n")] = 0;

    printf("Enter Attendee Preference (Veg/Non-Veg): ");
    fgets(attendees[attendee_count].preference, MAX_NAME_LEN, stdin);
    attendees[attendee_count].preference[strcspn(attendees[attendee_count].preference, "\n")] = 0;

    printf("Is the attendee present (Y/N): ");
    char choice;
    scanf(" %c", &choice);
    attendees[attendee_count].attended = (choice == 'Y' || choice == 'y') ? 1 : 0;

    attendees[attendee_count].event_serial_no = event_serial_no;
    attendee_count++;
}

void mark_attendance(int event_serial_no) {
    printf("List of attendees not present:\n");
    for (int i = 0; i < attendee_count; i++) {
        if (attendees[i].event_serial_no == event_serial_no && !attendees[i].attended) {
            printf("%-5d %-30s\n", i + 1, attendees[i].name);
        }
    }

    while (1) {
        printf("Enter S.No of attendee to mark present (0 to stop): ");
        int serial_no;
        scanf("%d", &serial_no);
        if (serial_no == 0) {
            break;
        } else if (serial_no > 0 && serial_no <= attendee_count) {
            attendees[serial_no - 1].attended = 1;
            printf("Attendance marked for %s\n", attendees[serial_no - 1].name);
        } else {
            printf("Invalid serial number.\n");
        }
    }
}

void search_attendee(int event_serial_no) {
    char search_name[MAX_NAME_LEN];
    printf("Enter the name of the attendee to search: ");
    getchar();
    fgets(search_name, MAX_NAME_LEN, stdin);
    search_name[strcspn(search_name, "\n")] = 0;

    for (int i = 0; i < attendee_count; i++) {
        if (attendees[i].event_serial_no == event_serial_no &&
            strstr(attendees[i].name, search_name) != NULL) {
            printf("Attendee found: %s\n", attendees[i].name);
            return;
        }
    }
    printf("Attendee not found.\n");
}

void event_summary(int event_serial_no) {
    int total = 0, veg = 0, non_veg = 0, present = 0;
    for (int i = 0; i < attendee_count; i++) {
        if (attendees[i].event_serial_no == event_serial_no) {
            total++;
            if (strstr(attendees[i].preference, "Non")) {
                non_veg++;
            } else {
                veg++;
            }
            if (attendees[i].attended) {
                present++;
            }
        }
    }

    printf("Event Summary:\n");
    printf("Total attendees: %d\n", total);
    printf("Veg attendees: %d\n", veg);
    printf("Non-Veg attendees: %d\n", non_veg);
    printf("Attendance percentage: %.2f%%\n", total ? (present / (float)total) * 100 : 0);
}

int main() {
    // Predefined event and attendee
    strcpy(events[0].name, "Python Workshop");
    strcpy(events[0].date, "20/11/2024");
    events[0].serial_no = 1;

    strcpy(attendees[0].name, "Kushagra Chandra");
    strcpy(attendees[0].email, "kc@gmailcom");
    strcpy(attendees[0].preference, "Non-Vegetarian");
    attendees[0].attended = 0;
    attendees[0].event_serial_no = 1;
    attendee_count++;
    event_count++;

    list_events();

    int choice;
    while (1) {
        printf("\n1. List events\n2. Add event\n3. View event details\n");
        printf("4. View attendees\n5. Add attendee\n6. Mark attendance\n");
        printf("7. Search attendee\n8. Event summary\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            list_events();
        } else if (choice == 2) {
            add_event();
        } else if (choice == 3) {
            int serial_no;
            printf("Enter event serial number: ");
            scanf("%d", &serial_no);
            view_event_details(serial_no);
        } else if (choice == 4) {
            int serial_no;
            printf("Enter event serial number: ");
            scanf("%d", &serial_no);
            view_attendees(serial_no);
        } else if (choice == 5) {
            int serial_no;
            printf("Enter event serial number: ");
            scanf("%d", &serial_no);
            add_attendee(serial_no);
        } else if (choice == 6) {
            int serial_no;
            printf("Enter event serial number: ");
            scanf("%d", &serial_no);
            mark_attendance(serial_no);
        } else if (choice == 7) {
            int serial_no;
            printf("Enter event serial number: ");
            scanf("%d", &serial_no);
            search_attendee(serial_no);
        } else if (choice == 8) {
            int serial_no;
            printf("Enter event serial number: ");
            scanf("%d", &serial_no);
            event_summary(serial_no);
        } else if (choice == 9) {
            printf("Thank you for using the program. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}