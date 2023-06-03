#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Movie {
    int id;
    char title[50];
    char genre[20];
    int duration;
    char cast[100];
    char synopsis[200];
};

struct Showtime {
    int id;
    int movieId;
    char date[20];
    char time[10];
    int availableSeats;
};

struct User {
    int id;
    char username[50];
    char password[50];
};

struct Ticket {
    int id;
    int userId;
    int showtimeId;
    char seatNumber[10];
};

struct Movie movies[10];
int movieCount = 0;
struct Showtime showtimes[20];
int showtimeCount = 0;
struct User users[100];
int userCount = 0;
struct Ticket tickets[100];
int ticketCount = 0;

// Function to add a movie
void addMovie() {
    struct Movie movie;

    printf("Enter movie title: ");
    scanf("%s", movie.title);

    printf("Enter movie genre: ");
    scanf("%s", movie.genre);

    printf("Enter movie duration (in minutes): ");
    scanf("%d", &movie.duration);

    printf("Enter movie cast: ");
    scanf(" %[^\n]s", movie.cast);

    printf("Enter movie synopsis: ");
    scanf(" %[^\n]s", movie.synopsis);

    movie.id = movieCount + 1;
    movies[movieCount++] = movie;

    printf("Movie added successfully!\n");
    // Write movie data to file
    FILE* movieFile = fopen("movies.txt", "a");
    fprintf(movieFile, "%d,%s,%s,%d,%s,%s\n", movie.id, movie.title, movie.genre, movie.duration, movie.cast, movie.synopsis);
    fclose(movieFile);
}

// Function to add a showtime
void addShowtime() {
    int movieId;
    printf("Enter movie ID: ");
    scanf("%d", &movieId);

    struct Showtime showtime;

    showtime.movieId = movieId;

    printf("Enter showtime date (DD/MM/YYYY): ");
    scanf("%s", showtime.date);

    printf("Enter showtime time (HH:MM AM/PM): ");
    scanf("%s", showtime.time);

    printf("Enter number of available seats: ");
    scanf("%d", &showtime.availableSeats);

    showtime.id = showtimeCount + 1;
    showtimes[showtimeCount++] = showtime;

    printf("Showtime added successfully!\n");
    // Write showtime data to file
    FILE* showtimeFile = fopen("showtimes.txt", "a");
    fprintf(showtimeFile, "%d,%d,%s,%s,%d\n", showtime.id, showtime.movieId, showtime.date, showtime.time, showtime.availableSeats);
    fclose(showtimeFile);
}

// Function to register a user
void registerUser() {
    struct User user;

    printf("Enter username: ");
    scanf("%s", user.username);

    printf("Enter password: ");
    scanf("%s", user.password);

    user.id = userCount + 1;
    users[userCount++] = user;

    printf("User registered successfully!\n");
    // Write user data to file
    FILE* userFile = fopen("users.txt", "a");
    fprintf(userFile, "%d,%s,%s\n", user.id, user.username,user.password);
    fclose(userFile);
}

// Function to book a ticket
void bookTicket() {
    int showtimeId;
    printf("Enter showtime ID: ");
    scanf("%d", &showtimeId);
    struct Showtime* showtime = NULL;
    for (int i = 0; i < showtimeCount; i++) {
        if (showtimes[i].id == showtimeId) {
            showtime = &showtimes[i];
            break;
        }
    }

    if (showtime == NULL) {
        printf("Invalid showtime ID!\n");
        return;
    }

    if (showtime->availableSeats == 0) {
        printf("No available seats for this showtime!\n");
        return;
    }

    struct Ticket ticket;
    ticket.showtimeId = showtimeId;

    printf("Enter seat number: ");
    scanf("%s", ticket.seatNumber);

    ticket.userId = -1; // -1 indicates a ticket without an associated user
    ticket.id = ticketCount + 1;
    tickets[ticketCount++] = ticket;

    showtime->availableSeats--;

    printf("Ticket booked successfully!\n");
    // Write ticket data to file
    FILE* ticketFile = fopen("tickets.txt", "a");
    fprintf(ticketFile, "%d,%d,%d,%s\n", ticket.id, ticket.userId, ticket.showtimeId, ticket.seatNumber);
    fclose(ticketFile);
}
// Function to read movie data from file
void readMoviesFromFile() {
    FILE* movieFile = fopen("movies.txt", "r");
    if (movieFile == NULL) {
    return;
    }
    char line[300];
    while (fgets(line, sizeof(line), movieFile) != NULL) {
        struct Movie movie;
        sscanf(line, "%d,%[^,],%[^,],%d,%[^,],%[^\n]", &movie.id, movie.title, movie.genre, &movie.duration, movie.cast, movie.synopsis);
        movies[movieCount++] = movie;
    }

    fclose(movieFile);
}
// Function to read showtime data from file
void readShowtimesFromFile() {
    FILE* showtimeFile = fopen("showtimes.txt", "r");
    if (showtimeFile == NULL) {
    return;
    }
    char line[300];
    while (fgets(line, sizeof(line), showtimeFile) != NULL) {
        struct Showtime showtime;
        sscanf(line, "%d,%d,%[^,],%[^,],%d", &showtime.id, &showtime.movieId, showtime.date, showtime.time, &showtime.availableSeats);
        showtimes[showtimeCount++] = showtime;
    }

    fclose(showtimeFile);
}
// Function to read user data from file
void readUsersFromFile() {
    FILE* userFile = fopen("users.txt", "r");
    if (userFile == NULL) {
    return;
    }
    char line[200];
    while (fgets(line, sizeof(line), userFile) != NULL) {
        struct User user;
        sscanf(line, "%d,%[^,],%[^\n]", &user.id, user.username, user.password);
        users[userCount++] = user;
    }

    fclose(userFile);
}
// Function to read ticket data from file
void readTicketsFromFile(){
    FILE* ticketFile = fopen("tickets.txt", "r");
    if (ticketFile == NULL) {
    return;
    }
    char line[200];
    while (fgets(line, sizeof(line), ticketFile) != NULL) {
        struct Ticket ticket;
        sscanf(line, "%d,%d,%d,%[^,\n]", &ticket.id, &ticket.userId, &ticket.showtimeId, ticket.seatNumber);
        tickets[ticketCount++] = ticket;
    }
    fclose(ticketFile);
}

// Function to display all movies
void displayMovies() {
    printf("Movie ID\tTitle\t\tGenre\t\tDuration\n");
    for (int i = 0; i < movieCount; i++) {
    printf("%d\t\t%s\t\t%s\t\t%d minutes\n", movies[i].id, movies[i].title, movies[i].genre, movies[i].duration);
    }
}

// Function to display all showtimes
void displayShowtimes() {
    printf("Showtime ID\tMovie Title\t\tDate\t\tTime\t\tAvailable Seats\n");
    for (int i = 0; i < showtimeCount; i++) {
        struct Showtime showtime = showtimes[i];
        struct Movie* movie = NULL;
            for (int j = 0; j < movieCount; j++) {
                if (movies[j].id == showtime.movieId) {
                movie = &movies[j];
                break;
            }
        }

        if (movie != NULL) {
            printf("%d\t\t%s\t\t%s\t%s\t%d\n", showtime.id, movie->title, showtime.date, showtime.time, showtime.availableSeats);
        }
    }
}

int main() {
// Read data from files on program startup
    readMoviesFromFile();
    readShowtimesFromFile();
    readUsersFromFile();
    readTicketsFromFile();
    int choice;

    printf("\n==== Movie Ticket Management System ====\n");
    printf("1. Add Movie\n");
    printf("2. Add Showtime\n");
    printf("3. Register User\n");
    printf("4. Book Ticket\n");
    printf("5. Display Movies\n");
    printf("6. Display Showtimes\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    do{
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                addMovie();
                break;
            case 2:
                addShowtime();
                break;
            case 3:
                registerUser();
                break;
            case 4:
                bookTicket();
                break;
            case 5:
                displayMovies();
                break;
            case 6:
                displayShowtimes();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }

    } while (choice != 0);

return 0;
}