#ifndef ADMINISTRATOR_HPP
#define ADMINISTRATOR_HPP

#include "User.hpp"
#include <vector>
#include <string>
#include <memory>

// Forward declarations for system entities
class BookingAgent;
class Passenger;
class Flight;
class Aircraft;
class User;

// The Administrator class enables management of users, flights, aircraft, and system reporting.
class Administrator : public User {
public:
    // --- Constructor ---
    Administrator(const std::string& id, const std::string& uname, const std::string& pwdHash);

    // --- Overridden authentication methods ---
    std::string getRole() const override;
    bool verifyPassword(const std::string& password) const override;

    // ================== User Management ==================
    void addBookingAgent(std::vector<std::shared_ptr<BookingAgent>>& agents,
                         const std::string& id, const std::string& uname, const std::string& pwdHash);
    void removeBookingAgent(std::vector<std::shared_ptr<BookingAgent>>& agents, const std::string& id);

    void addPassenger(std::vector<std::shared_ptr<Passenger>>& passengers,
                      const std::string& id, const std::string& uname, const std::string& pwdHash);
    void removePassenger(std::vector<std::shared_ptr<Passenger>>& passengers, const std::string& id);

    // ================== Flight Management ==================
    void addFlight(std::vector<std::shared_ptr<Flight>>& flights, std::shared_ptr<Flight> flight);
    void updateFlight(std::vector<std::shared_ptr<Flight>>& flights,
                      const std::string& flightNumber,
                      std::shared_ptr<Flight> updatedFlight);
    void removeFlight(std::vector<std::shared_ptr<Flight>>& flights, const std::string& flightNumber);
    void viewAllFlights(const std::vector<std::shared_ptr<Flight>>& flights) const;

    // ================== Aircraft Management ==================
    void addAircraft(std::vector<std::shared_ptr<Aircraft>>& aircrafts, std::shared_ptr<Aircraft> aircraft);
    void removeAircraft(std::vector<std::shared_ptr<Aircraft>>& aircrafts, const std::string& aircraftID);

    // ================== Reporting ==================
    void generateOperationalReport(const std::vector<std::shared_ptr<Flight>>& flights) const;
    void generateMaintenanceReport(const std::vector<std::shared_ptr<Aircraft>>& aircrafts) const;
    void generateUserActivityReport(const std::vector<std::shared_ptr<User>>& users) const;

    static std::shared_ptr<Administrator> from_json(const nlohmann::json& j);
    void to_json(nlohmann::json& j) const override;
};

#endif // ADMINISTRATOR_HPP
