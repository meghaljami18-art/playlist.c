#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ─────────────────────────────────────────
// STRUCTURE
// ─────────────────────────────────────────
struct song {
    int trackNum;
    char title[50];
    char artist[50];
    float duration;
    struct song *next;
};

// Global pointers
struct song *head = NULL;
struct song *tail = NULL;
int totalSongs = 0;

// ─────────────────────────────────────────
// HELPER: Clear input buffer
// ─────────────────────────────────────────
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ─────────────────────────────────────────
// HELPER: Renumber tracks after delete
// ─────────────────────────────────────────
void renumberTracks() {
    struct song *temp = head;
    int i = 1;
    while (temp != NULL) {
        temp->trackNum = i++;
        temp = temp->next;
    }
}

// ─────────────────────────────────────────
// HELPER: Total playlist duration
// ─────────────────────────────────────────
float totalDuration() {
    struct song *temp = head;
    float total = 0;
    while (temp != NULL) {
        total += temp->duration;
        temp = temp->next;
    }
    return total;
}

// ─────────────────────────────────────────
// FREE PLAYLIST (on exit)
// ─────────────────────────────────────────
void freePlaylist() {
    struct song *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
    totalSongs = 0;
}

// ─────────────────────────────────────────
// INSERT AT END
// ─────────────────────────────────────────
void insertEnd() {
    // FIX 1: Check malloc failure
    struct song *newnode = (struct song *)malloc(sizeof(struct song));
    if (newnode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // FIX 2: Multi-word input with scanf %[^\n]
    printf("Enter title: ");
    clearBuffer();
    scanf("%49[^\n]", newnode->title);

    printf("Enter artist: ");
    clearBuffer();
    scanf("%49[^\n]", newnode->artist);

    // FIX 3: Validate duration
    do {
        printf("Enter duration (in minutes, e.g. 3.45): ");
        scanf("%f", &newnode->duration);
        if (newnode->duration <= 0)
            printf("Duration must be greater than 0!\n");
    } while (newnode->duration <= 0);

    newnode->next = NULL;
    totalSongs++;
    newnode->trackNum = totalSongs;

    if (head == NULL) {
        head = tail = newnode;
    } else {
        tail->next = newnode;
        tail = newnode;
    }

    printf("Song added successfully! (Track %d)\n", newnode->trackNum);
}

// ─────────────────────────────────────────
// DISPLAY
// ─────────────────────────────────────────
void display() {
    struct song *temp = head;

    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    printf("\n============================================\n");
    printf("  🎵 PLAYLIST (%d songs | %.2f mins total)\n", totalSongs, totalDuration());
    printf("============================================\n");

    while (temp != NULL) {
        printf("#%-3d %-25s %-20s %.2f min\n",
               temp->trackNum, temp->title, temp->artist, temp->duration);
        temp = temp->next;
    }

    printf("============================================\n");
}

// ─────────────────────────────────────────
// SEARCH
// ─────────────────────────────────────────
void searchSong() {
    char title[50];
    struct song *temp = head;

    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    // FIX 4: Multi-word search input
    printf("Enter title to search: ");
    clearBuffer();
    scanf("%49[^\n]", title);

    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            printf("\n--- Song Found ---\n");
            printf("Track  : #%d\n", temp->trackNum);
            printf("Title  : %s\n", temp->title);
            printf("Artist : %s\n", temp->artist);
            printf("Duration: %.2f min\n", temp->duration);
            return;
        }
        temp = temp->next;
    }

    printf("Song \"%s\" not found!\n", title);
}

// ─────────────────────────────────────────
// DELETE
// ─────────────────────────────────────────
void deleteSong() {
    char title[50];
    struct song *temp = head;
    struct song *prev = NULL;

    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    // FIX 5: Multi-word delete input
    printf("Enter title to delete: ");
    clearBuffer();
    scanf("%49[^\n]", title);

    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0)
            break;
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Song \"%s\" not found!\n", title);
        return;
    }

    if (prev == NULL) {
        head = temp->next;
        if (head == NULL)
            tail = NULL;
    } else {
        prev->next = temp->next;
        if (temp == tail)
            tail = prev;
    }

    printf("Song \"%s\" deleted successfully!\n", temp->title);
    free(temp);
    totalSongs--;

    // FIX 6: Renumber after delete
    renumberTracks();
}

// ─────────────────────────────────────────
// REVERSE
// ─────────────────────────────────────────
void reverse() {
    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    struct song *current = head;
    struct song *prev = NULL;
    struct song *next = NULL;

    tail = head;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;

    // FIX 7: Renumber after reverse
    renumberTracks();
    printf("Playlist reversed successfully!\n");
}

// ─────────────────────────────────────────
// INSERT AT POSITION
// ─────────────────────────────────────────
void insertAtPosition() {
    int pos;

    printf("Enter position (1 to %d): ", totalSongs + 1);
    scanf("%d", &pos);

    if (pos < 1 || pos > totalSongs + 1) {
        printf("Invalid position!\n");
        return;
    }

    // Insert at end
    if (pos == totalSongs + 1) {
        insertEnd();
        return;
    }

    struct song *newnode = (struct song *)malloc(sizeof(struct song));
    if (newnode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter title: ");
    clearBuffer();
    scanf("%49[^\n]", newnode->title);

    printf("Enter artist: ");
    clearBuffer();
    scanf("%49[^\n]", newnode->artist);

    do {
        printf("Enter duration (in minutes): ");
        scanf("%f", &newnode->duration);
        if (newnode->duration <= 0)
            printf("Duration must be greater than 0!\n");
    } while (newnode->duration <= 0);

    // Insert at head
    if (pos == 1) {
        newnode->next = head;
        head = newnode;
    } else {
        struct song *temp = head;
        for (int i = 1; i < pos - 1; i++)
            temp = temp->next;

        newnode->next = temp->next;
        temp->next = newnode;

        if (newnode->next == NULL)
            tail = newnode;
    }

    totalSongs++;
    renumberTracks();
    printf("Song added at position %d successfully!\n", pos);
}

// ─────────────────────────────────────────
// MAIN MENU
// ─────────────────────────────────────────
int main() {
    int choice;

    do {
        printf("\n====== 🎵 PLAYLIST MENU ======\n");
        printf("1. Add Song (at end)\n");
        printf("2. Add Song (at position)\n");
        printf("3. Display Playlist\n");
        printf("4. Search Song\n");
        printf("5. Delete Song\n");
        printf("6. Reverse Playlist\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insertEnd();         break;
            case 2: insertAtPosition();  break;
            case 3: display();           break;
            case 4: searchSong();        break;
            case 5: deleteSong();        break;
            case 6: reverse();           break;
            case 7:
                // FIX 8: Free all memory on exit
                freePlaylist();
                printf("Goodbye! 🎵\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 7);

    return 0;
}
