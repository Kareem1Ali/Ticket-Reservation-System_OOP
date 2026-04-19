#include <iostream>
#include <string>
#include <cstring>
#include "Enums.h"
#include "classCustomer.h"
#include "classMovies.h"
#include "classSeats.h"
#include "classReservation.h"
#include "MovieAnalytics.h"
#include "AnalyticsManager.h"

using namespace std;

const int MAX_MOVIES = 5;

void displayMenu() {
    cout << "\n=== Cinema Reservation System Menu ===\n";
    cout << "1. View Available Movies\n";
    cout << "2. View Seating Layout\n";
    cout << "3. Book Seats\n";
    cout << "4. Cancel Specific Seats\n";
    cout << "5. Cancel Entire Reservation\n";
    cout << "6. View Reservation Details\n";
    cout << "7. View Movie Analytics\n";
    cout << "8. View Overall Cinema Analytics\n";
    cout << "9. Exit\n";
    cout << "Enter your choice (1-9): ";
}

void displayMovies(const Movie movies[], int count) {
    cout << "\nAvailable Movies:\n";
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". ";
        movies[i].displayInfo();
    }
}

void selectShowTime(const Movie& movie, string& selectedTime) {
    cout << "\nAvailable Show Times:\n";
    const string* showTimes = movie.getShowTimes();
    int count = movie.getShowTimeCount();
    
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". " << showTimes[i] << endl;
    }

    int choice;
    do {
        cout << "Select show time (1-" << count << "): ";
        cin >> choice;
        cin.ignore();
    } while (choice < 1 || choice > count);

    selectedTime = showTimes[choice - 1];
}

int main() {
    cout << "=== Welcome to Cinema Reservation System ===\n\n";

    Movie movies[MAX_MOVIES] = {
        Movie("The Matrix", Genre::SCIFI, 2024, 2.5f),
        Movie("Comedy Club", Genre::COMEDY, 2024, 1.8f),
        Movie("سيكو سيكو", Genre::COMEDY, 2024, 2.2f),
        Movie("Avengers : Doomsday", Genre::ACTION, 2024, 1.5f),
        Movie("البدلة", Genre::COMEDY, 2024, 2.0f)
    };

    Customer customer;
    customer.inputAllData();
    customer.display();

    Reservation reservation;
    bool hasReservation = false;
    int selectedMovie = -1;
    string selectedTime;
    
    // Create analytics manager
    AnalyticsManager analyticsManager;

    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                displayMovies(movies, MAX_MOVIES);
                break;

            case 2: {
                displayMovies(movies, MAX_MOVIES);
                int movieChoice;
                cout << "\nSelect movie number to view seating layout: ";
                cin >> movieChoice;
                cin.ignore();
                movieChoice--;

                if (movieChoice >= 0 && movieChoice < MAX_MOVIES) {
                    selectShowTime(movies[movieChoice], selectedTime);
                    Seats* seats = movies[movieChoice].getSeats();
                    if (seats) {
                        cout << "\nSeating Layout for " << movies[movieChoice].getTitle() 
                             << " at " << selectedTime << ":\n";
                        seats->displaySeats();
                    }
                } else {
                    cout << "Invalid movie selection.\n";
                }
                break;
            }

            case 3: {
                if (!hasReservation) {
                    displayMovies(movies, MAX_MOVIES);
                    cout << "\nSelect movie number: ";
                    cin >> selectedMovie;
                    cin.ignore();
                    selectedMovie--;

                    if (selectedMovie >= 0 && selectedMovie < MAX_MOVIES) {
                        selectShowTime(movies[selectedMovie], selectedTime);
                        reservation.create(customer, &movies[selectedMovie]);
                        hasReservation = true;
                    } else {
                        cout << "Invalid movie selection.\n";
                        break;
                    }
                }

                Seats* seats = movies[selectedMovie].getSeats();
                if (seats) {
                    cout << "\nCurrent Seating Layout for " << selectedTime << ":\n";
                    seats->displaySeats();
                }

                int row, col, ticketType;
                cout << "\nEnter row number: ";
                cin >> row;
                cout << "Enter column number: ";
                cin >> col;
                cout << "Select ticket type (0: STANDARD, 1: PREMIUM, 2: STUDENT): ";
                cin >> ticketType;
                cin.ignore();

                TicketType type;
                switch (ticketType) {
                    case 1: type = TicketType::PREMIUM; break;
                    case 2: type = TicketType::STUDENT; break;
                    default: type = TicketType::STANDARD; break;
                }

                if (reservation.addSeat(row, col, type)) {
                    // Record the ticket sale in analytics
                    reservation.recordSales(analyticsManager);
                    
                    cout << "Seat booked successfully!\n";
                    cout << "\nUpdated Seating Layout for " << selectedTime << ":\n";
                    seats->displaySeats();
                } else {
                    cout << "Failed to book seat. Please try again.\n";
                }
                break;
            }

            case 4:
                if (hasReservation) {
                    Seats* seats = movies[selectedMovie].getSeats();
                    if (seats) {
                        cout << "\nCurrent Seating Layout for " << selectedTime << ":\n";
                        seats->displaySeats();
                    }

                    int row, col;
                    cout << "\nEnter row number to cancel: ";
                    cin >> row;
                    cout << "Enter column number to cancel: ";
                    cin >> col;
                    cin.ignore();

                    if (reservation.cancelSeat(row, col)) {
                        cout << "Seat cancelled successfully!\n";
                        cout << "\nUpdated Seating Layout for " << selectedTime << ":\n";
                        seats->displaySeats();
                    } else {
                        cout << "Failed to cancel seat. Please check the seat numbers.\n";
                    }
                } else {
                    cout << "No active reservation found.\n";
                }
                break;

            case 5:
                if (hasReservation) {
                    reservation.cancelReservation();
                    hasReservation = false;
                    selectedMovie = -1;
                    selectedTime = "";
                    cout << "Entire reservation cancelled successfully!\n";
                } else {
                    cout << "No active reservation found.\n";
                }
                break;

            case 6:
                if (hasReservation) {
                    cout << "\nShow Time: " << selectedTime << endl;
                    reservation.showReservation();
                    Seats* seats = movies[selectedMovie].getSeats();
                    if (seats) {
                        cout << "\nCurrent Seating Layout for " << selectedTime << ":\n";
                        seats->displaySeats();
                    }
                } else {
                    cout << "No active reservation found.\n";
                }
                break;
                
            case 7: {
                // View movie analytics
                displayMovies(movies, MAX_MOVIES);
                int movieChoice;
                cout << "\nSelect movie number to view analytics: ";
                cin >> movieChoice;
                cin.ignore();
                movieChoice--;

                if (movieChoice >= 0 && movieChoice < MAX_MOVIES) {
                    analyticsManager.displayMovieReport(&movies[movieChoice]);
                } else {
                    cout << "Invalid movie selection.\n";
                }
                break;
            }
                
            case 8:
                // View overall cinema analytics
                analyticsManager.displayAllReports();
                break;

            case 9:
                cout << "Thank you for using our system!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}