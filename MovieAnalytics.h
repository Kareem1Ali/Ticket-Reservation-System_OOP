// MovieAnalytics.h
#pragma once
#include <iostream>
#include "Enums.h"
#include "classMovies.h"

using namespace std;

class MovieAnalytics {
private:
    const Movie* movie;
    int standardTickets;
    int premiumTickets;
    int studentTickets;
    float standardRevenue;
    float premiumRevenue;
    float studentRevenue;
public:
    MovieAnalytics() : movie(nullptr), standardTickets(0), premiumTickets(0), 
                      studentTickets(0), standardRevenue(0), premiumRevenue(0), 
                      studentRevenue(0) {}
    
    MovieAnalytics(const Movie* m) : movie(m), standardTickets(0), premiumTickets(0), 
                                    studentTickets(0), standardRevenue(0), 
                                    premiumRevenue(0), studentRevenue(0) {}
    
    void addTicketSale(TicketType type, float price) {
        switch (type) {
            case TicketType::STANDARD:
                standardTickets++;
                standardRevenue += price;
                break;
            case TicketType::PREMIUM:
                premiumTickets++;
                premiumRevenue += price;
                break;
            case TicketType::STUDENT:
                studentTickets++;
                studentRevenue += price;
                break;
        }
    }
    
    int getTotalTickets() const {
        return standardTickets + premiumTickets + studentTickets;
    }
    
    float getTotalRevenue() const {
        return standardRevenue + premiumRevenue + studentRevenue;
    }
    
    const Movie* getMovie() const {
        return movie;
    }
    
    void displayReport() const {
        if (!movie) {
            cout << "No movie data available.\n";
            return;
        }
        
        cout << "\n========= MOVIE ANALYTICS REPORT =========\n";
        cout << "Movie: " << movie->getTitle() << endl;
        
        
        cout << "Genre: ";
        switch (movie->getGenre()) {
            case Genre::ACTION: cout << "Action"; break;
            case Genre::COMEDY: cout << "Comedy"; break;
            case Genre::DRAMA: cout << "Drama"; break;
            case Genre::HORROR: cout << "Horror"; break;
            case Genre::SCIFI: cout << "Sci-Fi"; break;
            default: cout << "Unknown"; break;
        }
        cout << endl;
        
        cout << "\n--- Ticket Sales Breakdown ---\n";
        cout << "Standard Tickets: " << standardTickets 
             << " ($" << standardRevenue << ")\n";
        cout << "Premium Tickets: " << premiumTickets 
             << " ($" << premiumRevenue << ")\n";
        cout << "Student Tickets: " << studentTickets 
             << " ($" << studentRevenue << ")\n";
        
        cout << "\n--- Summary ---\n";
        cout << "Total Tickets Sold: " << getTotalTickets() << endl;
        cout << "Total Revenue: $" << getTotalRevenue() << endl;
        
        
        if (getTotalTickets() > 0) {
            cout << "Most Popular Ticket Type: ";
            if (standardTickets >= premiumTickets && standardTickets >= studentTickets) {
                cout << "Standard";
            } else if (premiumTickets >= standardTickets && premiumTickets >= studentTickets) {
                cout << "Premium";
            } else {
                cout << "Student";
            }
            cout << endl;
        }
        
        cout << "========================================\n";
    }
};