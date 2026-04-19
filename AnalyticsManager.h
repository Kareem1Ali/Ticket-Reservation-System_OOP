// AnalyticsManager.h
#pragma once
#include "MovieAnalytics.h"

class AnalyticsManager {
private:
    static const int MAX_MOVIES = 10;
    MovieAnalytics* analytics[MAX_MOVIES];
    int count;
    
public:
    AnalyticsManager() : count(0) {
        for (int i = 0; i < MAX_MOVIES; i++) {
            analytics[i] = nullptr;
        }
    }
    
    ~AnalyticsManager() {
        for (int i = 0; i < count; i++) {
            delete analytics[i];
        }
    }
    
    MovieAnalytics* getOrCreateAnalytics(const Movie* movie) {
        
        for (int i = 0; i < count; i++) {
            if (analytics[i]->getMovie() == movie) {
                return analytics[i];
            }
        }
        
        
        if (count < MAX_MOVIES) {
            analytics[count] = new MovieAnalytics(movie);
            return analytics[count++];
        }
        
        return nullptr; 
    }
    
    void recordTicketSale(const Movie* movie, TicketType type, float price) {
        MovieAnalytics* movieAnalytics = getOrCreateAnalytics(movie);
        if (movieAnalytics) {
            movieAnalytics->addTicketSale(type, price);
        }
    }
    
    void displayAllReports() const {
        cout << "\n************ CINEMA REVENUE ANALYSIS ************\n";
        float totalRevenue = 0.0f;
        int totalTickets = 0;
        
        for (int i = 0; i < count; i++) {
            analytics[i]->displayReport();
            totalRevenue += analytics[i]->getTotalRevenue();
            totalTickets += analytics[i]->getTotalTickets();
        }
        
        cout << "\n************ SUMMARY ************\n";
        cout << "Total Movies: " << count << endl;
        cout << "Total Tickets Sold: " << totalTickets << endl;
        cout << "Total Revenue: $" << totalRevenue << endl;
        
        
        if (count > 0) {
            int mostProfitableIndex = 0;
            for (int i = 1; i < count; i++) {
                if (analytics[i]->getTotalRevenue() > analytics[mostProfitableIndex]->getTotalRevenue()) {
                    mostProfitableIndex = i;
                }
            }
            
            cout << "Most Profitable Movie: " 
                 << analytics[mostProfitableIndex]->getMovie()->getTitle()
                 << " ($" << analytics[mostProfitableIndex]->getTotalRevenue() << ")\n";
        }
        
        cout << "*********************************\n";
    }
    
    void displayMovieReport(const Movie* movie) const {
        for (int i = 0; i < count; i++) {
            if (analytics[i]->getMovie() == movie) {
                analytics[i]->displayReport();
                return;
            }
        }
        
        cout << "No analytics available for the selected movie.\n";
    }
};