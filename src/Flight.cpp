#include "Flight.hpp"
#include "Aircraft.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

// -- Constructors

Flight::Flight(const string& flightNumber,
               const string& origin,
               const string& destination,
               const string& departureDate,
               const string& departureTime,
               const string& arrivalDate,
               const string& arrivalTime,
               shared_ptr<Aircraft> aircraft,
               int totalSeats,
               double price,
               Status status)
    : flightNumber(flightNumber),
      origin(origin),
      destination(destination),
      departureDate(departureDate),
      departureTime(departureTime),
      arrivalDate(arrivalDate),
      arrivalTime(arrivalTime),
      aircraft(aircraft),
      totalSeats(totalSeats),
      price(price),
      status(status) {
    // Example: Seat numbers A-F, 1-totalSeats/6 per row.
    char cols[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int rows = totalSeats / 6;
    for (int i = 1; i <= rows; ++i) {
        for (char c : cols) {
            string seat = to_string(i) + c;
            seatMap[seat] = true;
        }
    }
}

// -- Getters

string Flight::getFlightNumber() const { return flightNumber; }
string Flight::getOrigin() const { return origin; }
string Flight::getDestination() const { return destination; }
string Flight::getDepartureDate() const { return departureDate; }
string Flight::getDepartureTime() const { return departureTime; }
string Flight::getArrivalDate() const { return arrivalDate; }
string Flight::getArrivalTime() const { return arrivalTime; }
string Flight::getAircraftType() const { return aircraft ? aircraft->getType() : "Unknown"; }
int Flight::getTotalSeats() const { return totalSeats; }
double Flight::getPrice() const { return price; }
Flight::Status Flight::getStatus() const { return status; }

// -- Setters

void Flight::setStatus(Status newStatus) { status = newStatus; }

// -- Crew Assignment

void Flight::assignPilot(const string& pid) { pilotID = pid; }
void Flight::assignAttendants(const vector<string>& ids) { attendantIDs = ids; }
string Flight::getPilotID() const { return pilotID; }
vector<string> Flight::getAttendantIDs() const { return attendantIDs; }

// -- Seat Management

bool Flight::isSeatValid(const string& seatNumber) const {
    return seatMap.find(seatNumber) != seatMap.end();
}

bool Flight::isSeatAvailable(const string& seatNumber) const {
    auto it = seatMap.find(seatNumber);
    return (it != seatMap.end()) && it->second;
}

bool Flight::reserveSeat(const string& seatNumber) {
    if (isSeatAvailable(seatNumber)) {
        seatMap[seatNumber] = false;
        return true;
    }
    return false;
}

void Flight::freeSeat(const string& seatNumber) {
    if (isSeatValid(seatNumber)) {
        seatMap[seatNumber] = true;
    }
}

int Flight::getAvailableSeatCount() const {
    int count = 0;
    for (const auto& s : seatMap) {
        if (s.second) ++count;
    }
    return count;
}

vector<string> Flight::getAvailableSeats() const {
    vector<string> seats;
    for (const auto& s : seatMap) {
        if (s.second) seats.push_back(s.first);
    }
    return seats;
}

// -- Info Utilities

void Flight::printFlightInfo() const {
    cout << "Flight: " << flightNumber << " | " << origin << " -> " << destination << endl;
    cout << "Departure: " << departureDate << " " << departureTime
         << " | Arrival: " << arrivalDate << " " << arrivalTime << endl;
    cout << "Aircraft: " << getAircraftType() << " | Available Seats: " << getAvailableSeatCount() << "/" << totalSeats << endl;
    cout << "Status: " << statusToString(status) << " | Price: $" << price << endl;
}

// -- Status Utilities

string Flight::statusToString(Status s) {
    switch (s) {
        case Status::Scheduled: return "Scheduled";
        case Status::Delayed: return "Delayed";
        case Status::Canceled: return "Canceled";
        case Status::Completed: return "Completed";
    }
    return "Unknown";
}

Flight::Status Flight::stringToStatus(const string& str) {
    if (str == "Scheduled") return Status::Scheduled;
    if (str == "Delayed") return Status::Delayed;
    if (str == "Canceled") return Status::Canceled;
    if (str == "Completed") return Status::Completed;
    return Status::Scheduled; // default
}
