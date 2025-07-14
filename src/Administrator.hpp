#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "User.hpp"
#include <string>

class Administrator : public User {
public:
    // Constructor: initializes base User class members
    Administrator(const std::string& id, const std::string& uname, const std::string& pwdHash)
        : User(id, uname, pwdHash) {}

    // Override to return the role of this user
    std::string getRole() const override { return "Administrator"; }

    // Password verification (placeholder: compares stored hash with input password)
    bool verifyPassword(const std::string& password) const override {
        // In a real application, this should compare hashed passwords securely
        return passwordHash == password;
    }

    // Placeholder for admin-specific methods (to be implemented later)
    // void addUser(...);
    // void removeUser(...);
    // void manageFlight(...);
};

#endif // ADMINISTRATOR_H
