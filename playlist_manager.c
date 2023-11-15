#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a songN  N
struct Song {
    char title[100];
    char artist[100];
    struct Song* next;
};

// Function to create a new song node
struct Song* createSong(const char* title, const char* artist) {
    struct Song* newSong = (struct Song*)malloc(sizeof(struct Song));
    if (newSong == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        exit(1);
    }
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    newSong->next = NULL;
    return newSong;
}

// Function to add a song to the playlist
void addSong(struct Song** playlist, const char* title, const char* artist) {
    struct Song* newSong = createSong(title, artist);
    newSong->next = *playlist;
    *playlist = newSong;
    printf("Song '%s' by %s added to the playlist.\n", title, artist);
}

// Function to view the playlist
void viewPlaylist(struct Song* playlist) {
    if (playlist == NULL) {
        printf("The playlist is empty.\n");
    } else {
        printf("Playlist:\n");
        int i = 1;
        while (playlist != NULL) {
            printf("%d. '%s' by %s\n", i, playlist->title, playlist->artist);
            playlist = playlist->next;
            i++;
        }
    }
}

// Function to remove a song from the playlist
void removeSong(struct Song** playlist, int songIndex) {
    if (songIndex <= 0) {
        printf("Invalid song index.\n");
        return;
    }

    if (songIndex == 1) {
        struct Song* temp = *playlist;
        *playlist = (*playlist)->next;
        printf("Song '%s' by %s removed from the playlist.\n", temp->title, temp->artist);
        free(temp);
    } else {
        int i = 1;
        struct Song* current = *playlist;
        while (i < songIndex - 1 && current != NULL) {
            current = current->next;
            i++;
        }

        if (current == NULL || current->next == NULL) {
            printf("Invalid song index.\n");
        } else {
            struct Song* temp = current->next;
            current->next = temp->next;
            printf("Song '%s' by %s removed from the playlist.\n", temp->title, temp->artist);
            free(temp);
        }
    }
}

// Function to play a song
void playSong(struct Song* playlist, int songIndex) {
    if (songIndex <= 0) {
        printf("Invalid song index.\n");
        return;
    }

    int i = 1;
    while (i < songIndex && playlist != NULL) {
        playlist = playlist->next;
        i++;
    }

    if (playlist == NULL) {
        printf("Invalid song index.\n");
    } else {
        printf("Now playing: '%s' by %s\n", playlist->title, playlist->artist);
    }
}

int main() {
    struct Song* playlist = NULL;

    while (1) {
        printf("\nPlaylist Manager Menu:\n");
        printf("1. Add Song\n");
        printf("2. View Playlist\n");
        printf("3. Remove Song\n");
        printf("4. Play Song\n");
        printf("5. Quit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                {
                    char title[100], artist[100];
                    printf("Enter the title of the song: ");
                    scanf(" %[^\n]", title);
                    printf("Enter the artist: ");
                    scanf(" %[^\n]", artist);
                    addSong(&playlist, title, artist);
                    break;
                }
            case 2:
                viewPlaylist(playlist);
                break;
            case 3:
                {
                    viewPlaylist(playlist);
                    int songIndex;
                    printf("Enter the index of the song to remove: ");
                    scanf("%d", &songIndex);
                    removeSong(&playlist, songIndex);
                    break;
                }
            case 4:
                {
                    viewPlaylist(playlist);
                    int songIndex;
                    printf("Enter the index of the song to play: ");
                    scanf("%d", &songIndex);
                    playSong(playlist, songIndex);
                    break;
                }
            case 5:
                printf("Exiting the Playlist Manager.\n");
                exit(0);
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }

    return 0;
}
