#pragma once
#include <iostream>
#include <cstring>
#include "Enums.h"
#include "classCustomer.h"
#include "classMovies.h"
#include "classSeats.h"
#include "MovieAnalytics.h"
#include "AnalyticsManager.h"

using namespace std;

class Reservation {
private:
    static const int MAX_SEATS = 10;
    static const int MAX_SHOWTIME_LENGTH = 10;

    const Customer* customer;
    const Movie* movie;
    char showTime[MAX_SHOWTIME_LENGTH];
    int* bookedRows;
    int* bookedCols;
    TicketType* ticketTypes;
    int seatCount;
    int maxSeats;
    Seats* movieSeats;

public:
    Reservation() : customer(nullptr), movie(nullptr), seatCount(0), maxSeats(MAX_SEATS), movieSeats(nullptr) {
        showTime[0] = '\0';
        bookedRows = new int[maxSeats];
        bookedCols = new int[maxSeats];
        ticketTypes = new TicketType[maxSeats];
    }
    
    void create(const Customer& cust, const Movie* mov) {
        customer = &cust;
        movie = mov;
        seatCount = 0;
        movieSeats = mov->getSeats();
    }
    
    ~Reservation() {
        delete[] bookedRows;
        delete[] bookedCols;
        delete[] ticketTypes;
    }

    bool addSeat(int row, int col, TicketType type) {
        if (seatCount >= maxSeats) {
            cout << "Error: Maximum seats reached for this reservation." << endl;
            return false;
        }
        
        row--;
        col--;
        
        if (!movie || !movieSeats) {
            cout << "Error: Invalid movie or seats." << endl;
            return false;
        }

        if (row >= 0 && row < movieSeats->getRows() && 
            col >= 0 && col < movieSeats->getCols()) {
            
            if (movieSeats->bookSeat(row, col)) {
                bookedRows[seatCount] = row;
                bookedCols[seatCount] = col;
                ticketTypes[seatCount] = type;
                seatCount++;
                return true;
            } else {
                cout << "Error: Seat is already booked." << endl;
            }
        } else {
            cout << "Error: Invalid seat selection." << endl;
        }
        return false;
    }

    bool cancelSeat(int row, int col) {
        row--;
        col--;
        
        for (int i = 0; i < seatCount; i++) {
            if (bookedRows[i] == row && bookedCols[i] == col) {
                movieSeats->freeSeat(row, col);
                
                for (int j = i; j < seatCount - 1; j++) {
                    bookedRows[j] = bookedRows[j + 1];
                    bookedCols[j] = bookedCols[j + 1];
                    ticketTypes[j] = ticketTypes[j + 1];
                }
                seatCount--;
                return true;
            }
        }
        return false;
    }

    void cancelReservation() {
        if (movie && movieSeats) {
            for (int i = 0; i < seatCount; i++) {
                movieSeats->freeSeat(bookedRows[i], bookedCols[i]);
            }
        }
        seatCount = 0;
    }

    float calculateTotal() const {
        float total = 0.0;
        if (!movie || !movieSeats) return total;

        for (int i = 0; i < seatCount; i++) {
            float basePrice = movieSeats->getSeatPrice(bookedRows[i], bookedCols[i]);
            
            switch (ticketTypes[i]) {
                case TicketType::PREMIUM:
                    total += basePrice * 1.5;
                    break;
                case TicketType::STUDENT:
                    total += basePrice * 0.7;
                    break;
                default:
                    total += basePrice;
                    break;
            }
        }
        return total;
    }

    void showReservation() const {
        if (!customer || !movie) {
            cout << "Error: Invalid reservation" << endl;
            return;
        }

        cout << "\n=== Reservation Details ===\n";
        cout << "Customer: " << customer->getName() << endl;
        movie->displayInfo();
        if (showTime[0] != '\0') {
            cout << "Show Time: " << showTime << endl;
        }
        cout << "Number of Seats: " << seatCount << endl;
        
        if (seatCount > 0) {
            cout << "Seats:\n";
            for (int i = 0; i < seatCount; i++) {
                cout << "Row: " << (bookedRows[i] + 1) << ", Col: " << (bookedCols[i] + 1);
                cout << " (";
                switch (ticketTypes[i]) {
                    case TicketType::PREMIUM:
                        cout << "Premium";
                        break;
                    case TicketType::STUDENT:
                        cout << "Student";
                        break;
                    default:
                        cout << "Standard";
                        break;
                }
                cout << ")\n";
            }
            cout << "Total Cost: $" << calculateTotal() << endl;
        }
    }

public:
    
    void recordSales(AnalyticsManager& analyticsManager) const {
        if (!movie || !movieSeats) return;
        
        for (int i = 0; i < seatCount; i++) {
            float basePrice = movieSeats->getSeatPrice(bookedRows[i], bookedCols[i]);
            float finalPrice = basePrice;
            
            switch (ticketTypes[i]) {
                case TicketType::PREMIUM:
                    finalPrice = basePrice * 1.5;
                    break;
                case TicketType::STUDENT:
                    finalPrice = basePrice * 0.7;
                    break;
                default:
                    break;
            }
            
            analyticsManager.recordTicketSale(movie, ticketTypes[i], finalPrice);
        }
    }
};