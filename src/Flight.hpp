#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include "json.hpp"
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <memory>

class Aircraft;

class Flight {
public:
    enum class Status { Scheduled, Delayed, Canceled, Completed };

private:
    std::string flightNumber;
    std::string origin;
    std::string destination;
    std::string departureDate; // YYYY-MM-DD
    std::string departureTime; // HH:MM
    std::string arrivalDate;
    std::string arrivalTime;
    std::shared_ptr<Aircraft> aircraft;
    int totalSeats;
    double price; // Price per seat

    Status status;

    // Seat map: key is seat string, value is availability
    std::unordered_map<std::string, bool> seatMap;

    // Crew assignments
    std::string pilotID;
    std::vector<std::string> attendantIDs;

public:
    Flight(const std::string& flightNumber,
           const std::string& origin,
           const std::string& destination,
           const std::string& departureDate,
           const std::string& departureTime,
           const std::string& arrivalDate,
           const std::string& arrivalTime,
           std::shared_ptr<Aircraft> aircraft,
           int totalSeats,
           double price,
           Status status = Status::Scheduled);

    // Getters
    std::string getFlightNumber() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    std::string getDepartureDate() const;
    std::string getDepartureTime() const;
    std::string getArrivalDate() const;
    std::string getArrivalTime() const;
    std::string getAircraftType() const;
    int getTotalSeats() const;
    double getPrice() const;
    Status getStatus() const;

    // Setter for status
    void setStatus(Status newStatus);

    // Crew assignment
    void assignPilot(const std::string& pilotID);
    void assignAttendants(const std::vector<std::string>& attendantIDs);
    std::string getPilotID() const;
    std::vector<std::string> getAttendantIDs() const;

    // Seats
    bool isSeatValid(const std::string& seatNumber) const;
    bool isSeatAvailable(const std::string& seatNumber) const;
    bool reserveSeat(const std::string& seatNumber);
    void freeSeat(const std::string& seatNumber);
    int getAvailableSeatCount() const;
    std::vector<std::string> getAvailableSeats() const;

    // Utility for displaying flight info
    void printFlightInfo() const;

    // For status as string
    static std::string statusToString(Status s);
    static Status stringToStatus(const std::string& str);

    void to_json(nlohmann::json& j) const;
    static std::shared_ptr<Flight> from_json(const nlohmann::json& j);
};

#endif // FLIGHT_HPP
