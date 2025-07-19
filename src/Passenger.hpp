#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include "User.hpp"
#include <string>
#include <vector>
#include <memory>

class Reservation;
class Flight;

class Passenger : public User {
    int loyaltyPoints;
    // Additional details (e.g., contact info, passport #) can be added
public:
    Passenger(const std::string& id, const std::string& uname, const std::string& pwdHash);

    std::string getRole() const override;
    bool verifyPassword(const std::string& password) const override;

    // Profile management
    void updateProfile(const std::string& newUsername);
    int getLoyaltyPoints() const;
    void addLoyaltyPoints(int points);
    bool redeemLoyaltyPoints(int points);

    // Reservation and travel
    void viewBookings(const std::vector<std::shared_ptr<Reservation>>& reservations) const;
    void viewBoardingPass(const std::vector<std::shared_ptr<Reservation>>& reservations, const std::string& reservationID) const;

    // Self-service flight search (optional, if allowed)
    void searchFlights(const std::vector<std::shared_ptr<Flight>>& flights,
                      const std::string& origin,
                      const std::string& destination,
                      const std::string& date) const;

    // Online check-in
    bool onlineCheckIn(std::vector<std::shared_ptr<Reservation>>& reservations, const std::string& reservationID);

    // Additional: Cancel a reservation (if permitted)
    bool cancelReservation(std::vector<std::shared_ptr<Reservation>>& reservations, const std::string& reservationID);

    // More profile accessors and mutators as needed
};

#endif // PASSENGER_HPP
