#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include "User.hpp"
#include <string>
#include <vector>
#include <memory>

class Reservation;
class Flight;

class Passenger : public User {
private:
    int loyaltyPoints;

public:
    Passenger(const std::string& id, const std::string& uname, const std::string& pwdHash);

    // User role and authentication
    std::string getRole() const override;
    bool verifyPassword(const std::string& password) const override;

    // Profile management
    void updateProfile(const std::string& newUsername);
    int getLoyaltyPoints() const;
    void addLoyaltyPoints(int points);
    bool redeemLoyaltyPoints(int points);

    // Reservation related
    void viewBookings(const std::vector<std::shared_ptr<Reservation>>& reservations) const;
    void viewBoardingPass(const std::vector<std::shared_ptr<Reservation>>& reservations, const std::string& reservationID) const;

    // Flight search
    void searchFlights(const std::vector<std::shared_ptr<Flight>>& flights,
                       const std::string& origin,
                       const std::string& destination,
                       const std::string& date) const;

    // Online check-in
    bool onlineCheckIn(std::vector<std::shared_ptr<Reservation>>& reservations, const std::string& reservationID);

    // Cancel reservation
    bool cancelReservation(std::vector<std::shared_ptr<Reservation>>& reservations, const std::string& reservationID);

    // Serialization
    void to_json(nlohmann::json& j) const override;
    static std::shared_ptr<Passenger> from_json(const nlohmann::json& j);
};

#endif // PASSENGER_HPP
