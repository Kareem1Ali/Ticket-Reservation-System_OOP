#pragma once
#include <iostream>
#include <string>
using namespace std;

class Customer {
private:
    string name;
    string email;

public:
    Customer() {
        name = "";
        email = "";
    }

    bool isStringEmpty(const string& str) const {
        return str.length() == 0;
    }

    bool hasValidEmail() const {
        bool hasAtSign = false;
        bool hasDot = false;
        
        for(int i = 0; i < email.length(); i++) {
            if(email[i] == '@') {
                hasAtSign = true;
            }
            if(email[i] == '.') {
                hasDot = true;
            }
        }
        
        return hasAtSign && hasDot;
    }

    void inputName() {
        while (true) {
            cout << "Enter customer name: ";
            getline(cin, name);
            
            if (isStringEmpty(name)) {
                cout << "Error: Name cannot be empty. Please enter a valid name." << endl;
            } else {
                break;
            }
        }
    }

    void inputEmail() {
        while (true) {
            cout << "Enter customer email: ";
            getline(cin, email);
            
            if (isStringEmpty(email)) {
                cout << "Error: Email cannot be empty. Please enter a valid email." << endl;
            } 
            else if (!hasValidEmail()) {
                cout << "Error: Invalid email format. Email must contain '@' and '.' characters." << endl;
            }
            else {
                break;
            }
        }
    }

    void inputAllData() {
        cout << "\n=== Customer Registration ===\n" << endl;
        inputName();
        inputEmail();
        cout << "\nCustomer data successfully registered!" << endl;
    }

    string getName() const {
        return name;
    }

    string getEmail() const {
        return email;
    }

    void setName(const string& customerName) {
        if (isStringEmpty(customerName)) {
            cout << "Error: Customer name cannot be empty" << endl;
            return;
        }
        name = customerName;
    }

    void setEmail(const string& customerEmail) {
        if (isStringEmpty(customerEmail)) {
            cout << "Error: Customer email cannot be empty" << endl;
            return;
        }
        email = customerEmail;
    }

    void display() const {
        cout << "\n=== Customer Information ===\n" << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        
        if (hasValidEmail()) {
            cout << "Email Status: Valid" << endl;
        } else {
            cout << "Email Status: Invalid (missing @ or .)" << endl;
        }
    }
};
