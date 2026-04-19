#pragma once
#include <iostream>
#include "Enums.h"

using namespace std;

class Seats {
private:
    int rows;
    int cols;
    float prices[10][10];
    bool available_seats[10][10];
    SeatType seatTypes[10][10];

public:
    Seats(int r, int c) {
        rows = r;
        cols = c;

        if (r > 10 || c > 10) {
            cout << "Unavailable: maximum seats is 100" << endl;
            rows = 0;
            cols = 0;
            return;
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                available_seats[i][j] = true;

                if (i < 2) {  
                    prices[i][j] = 150.0;
                    seatTypes[i][j] = SeatType::VIP;
                }
                else if (i < 5) {  
                    prices[i][j] = 100.0;
                    seatTypes[i][j] = SeatType::PREMIUM;
                }
                else {  
                    prices[i][j] = 80.0;
                    seatTypes[i][j] = SeatType::REGULAR;
                }
            }
        }
    }

    bool isSeatAvailable(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            return false;
        }
        return available_seats[row][col];
    }

    float getSeatPrice(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            return 0.0;
        }
        return prices[row][col];
    }

    bool bookSeat(int row, int col) {
        if (!isSeatAvailable(row, col)) {
            return false;
        }
        available_seats[row][col] = false;
        return true;
    }

    void freeSeat(int row, int col) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            available_seats[row][col] = true;
        }
    }

    void displaySeats() const {
        cout << "\nSeating Layout (- = available, X = booked):\n  ";
        
        
        for (int j = 0; j < cols; j++) {
            cout << (j < 9 ? " " : "") << j + 1 << " ";
        }
        cout << endl;

        
        for (int i = 0; i < rows; i++) {
            cout << (i < 9 ? " " : "") << i + 1 << " ";
            for (int j = 0; j < cols; j++) {
                cout << " " << (available_seats[i][j] ? "-" : "X") << " ";
            }
            cout << "  $" << prices[i][0] << endl;
        }

        cout << "\nPricing by row:\n";
        cout << "Rows 1-2:  VIP     - $150\n";
        cout << "Rows 3-5:  PREMIUM - $100\n";
        cout << "Rows 6-10: REGULAR - $80\n";
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }
    SeatType getSeatType(int row, int col) const { return seatTypes[row][col]; }
};

