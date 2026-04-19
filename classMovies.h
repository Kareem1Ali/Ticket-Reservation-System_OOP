#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include "Enums.h"
#include "classSeats.h"

using namespace std;


class Movie {
private:
    string title;
    Genre genre;
    int releaseYear;
    float duration;  
    string* showTimes;  
    int maxShowTimes;   
    int currentShowTimes;
    Seats* seats; 

protected:
    
    void displayGenre() const {
        cout << "Genre: ";
        switch(genre) {
            case Genre::ACTION: cout << "Action"; break;  
            case Genre::COMEDY: cout << "Comedy"; break;  
            case Genre::DRAMA: cout << "Drama"; break;    
            case Genre::HORROR: cout << "Horror"; break;  
            case Genre::SCIFI: cout << "Sci-Fi"; break;   
            default: cout << "Unknown"; break;
        }
        cout << endl;
    }

public:
    
    Movie() : maxShowTimes(4), currentShowTimes(0), seats(nullptr) {
        title = "Untitled";  
        genre = Genre::DRAMA;  
        releaseYear = 2024;    
        duration = 2.0f;       
        seats = new Seats(10, 10);  
        showTimes = new string[maxShowTimes];
        
        addShowTime("10:00");  
        addShowTime("01:00");  
        addShowTime("05:00");  
        addShowTime("09:00");  
    }

    
    Movie(const string& t, Genre g, int year, float dur) 
        : title(t), genre(g), releaseYear(year), duration(dur), 
          maxShowTimes(4), currentShowTimes(0), seats(nullptr) {
        seats = new Seats(10, 10);
        showTimes = new string[maxShowTimes];
        
        addShowTime("10:00");  
        addShowTime("01:00");  
        addShowTime("05:00");  
        addShowTime("09:00");
    }

    virtual ~Movie() {
        delete[] showTimes;
        delete seats;
    }

    Movie(const Movie& other) : maxShowTimes(other.maxShowTimes), currentShowTimes(other.currentShowTimes) {
        title = other.title;
        genre = other.genre;
        releaseYear = other.releaseYear;
        duration = other.duration;
        seats = new Seats(10, 10);
        showTimes = new string[maxShowTimes];
        for(int i = 0; i < currentShowTimes; i++) {
            showTimes[i] = other.showTimes[i];
        }
    }

    

    virtual void displayInfo() const {
        cout << "\nMovie Details:" << endl;
        cout << "Title: " << title << endl;
        displayGenre();
        cout << "Release Year: " << releaseYear << endl;
        cout << "Duration: " << duration << " hours" << endl;
        displayShowTimes();
    }

    void displayShowTimes() const {
        cout << "Show Times: ";
        for(int i = 0; i < currentShowTimes; i++) {
            cout << showTimes[i];
            if (i < currentShowTimes - 1) cout << ", ";
        }
        cout << endl;
    }

    bool addShowTime(const string& time) {
        
        if (currentShowTimes < maxShowTimes) {
            
            showTimes[currentShowTimes++] = time;
            return true;
        }
        return false;
    }

    bool removeShowTime(const string& time) {
        
        for(int i = 0; i < currentShowTimes; i++) {
            if (showTimes[i] == time) {
                
                for(int j = i; j < currentShowTimes - 1; j++) {
                    showTimes[j] = showTimes[j + 1];
                }
                currentShowTimes--;
                return true;
            }
        }
        return false;
    }

    Seats* getSeats() const { return seats; }
    const string& getTitle() const { return title; }
    Genre getGenre() const { return genre; }
    int getReleaseYear() const { return releaseYear; }
    float getDuration() const { return duration; }
    const string* getShowTimes() const { return showTimes; }
    int getShowTimeCount() const { return currentShowTimes; }

    void setTitle(const string& newTitle) { title = newTitle; }
    void setGenre(Genre newGenre) { genre = newGenre; }
    void setReleaseYear(int newYear) { releaseYear = newYear; }
    void setDuration(float newDuration) { duration = newDuration; }
};


class ActionMovie : public Movie {
private:
    string specialEffects;  

public:
    
    ActionMovie(const string& t, int year, float dur, const string& effects) 
        : Movie(t, Genre::ACTION, year, dur), specialEffects(effects) {}

    void displayInfo() const override {
        Movie::displayInfo();
        cout << "Special Effects: " << specialEffects << endl;
    }
};


class ComedyMovie : public Movie {
private:
    string comedyType;  

public:
    
    ComedyMovie(const string& t, int year, float dur, const string& type) 
        : Movie(t, Genre::COMEDY, year, dur), comedyType(type) {}

    void displayInfo() const override {
        Movie::displayInfo();
        cout << "Comedy Type: " << comedyType << endl;
    }
};


class HorrorMovie : public Movie {
private:
    string horrorType;  

public:
   
    HorrorMovie(const string& t, int year, float dur, const string& type) 
        : Movie(t, Genre::HORROR, year, dur), horrorType(type) {}

    void displayInfo() const override {
        Movie::displayInfo();
        cout << "Horror Type: " << horrorType << endl;
    }
};


class SciFiMovie : public Movie {
private:
    string tech;  

public:
    
    SciFiMovie(const string& t, int year, float dur, const string& te) 
        : Movie(t, Genre::SCIFI, year, dur), tech(te) {}

    void displayInfo() const override {
        Movie::displayInfo();
        cout << "Featured Technology: " << tech << endl;
    }
};