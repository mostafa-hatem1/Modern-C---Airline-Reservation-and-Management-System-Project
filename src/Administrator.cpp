#include "Administrator.hpp"
#include "BookingAgent.hpp"
#include "Passenger.hpp"
#include "Flight.hpp"
#include "Aircraft.hpp"
#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;

// Constructor
Administrator::Administrator(const string& id, const string& uname, const string& pwdHash)
    : User(id, uname, pwdHash) {}

// Role identifier
string Administrator::getRole() const {
    return "Administrator";
}

// Password verification (replace with real hashing in production)
bool Administrator::verifyPassword(const string& password) const {
    return passwordHash == password;
}

// ================== User Management ==================
void Administrator::addBookingAgent(vector<shared_ptr<BookingAgent>>& agents, 
                  const string& id, const string& uname, const string& pwdHash) {
    agents.push_back(make_shared<BookingAgent>(id, uname, pwdHash));
}

void Administrator::removeBookingAgent(vector<shared_ptr<BookingAgent>>& agents, const string& id) {
    agents.erase(remove_if(agents.begin(), agents.end(),
        [&](shared_ptr<BookingAgent>& agent) { return agent->getUserID() == id; }), agents.end());
}

void Administrator::addPassenger(vector<shared_ptr<Passenger>>& passengers, 
                const string& id, const string& uname, const string& pwdHash) {
    passengers.push_back(make_shared<Passenger>(id, uname, pwdHash));
}

void Administrator::removePassenger(vector<shared_ptr<Passenger>>& passengers, const string& id) {
    passengers.erase(remove_if(passengers.begin(), passengers.end(),
        [&](shared_ptr<Passenger>& p) { return p->getUserID() == id; }), passengers.end());
}

// ================== Flight Management ==================
void Administrator::addFlight(vector<shared_ptr<Flight>>& flights, shared_ptr<Flight> flight) {
    flights.push_back(flight);
}

void Administrator::updateFlight(vector<shared_ptr<Flight>>& flights, 
                                 const string& flightNumber, 
                                 shared_ptr<Flight> updatedFlight) {
    for (auto& flight : flights) {
        if (flight->getFlightNumber() == flightNumber) {
            *flight = *updatedFlight;
            break;
        }
    }
}

void Administrator::removeFlight(vector<shared_ptr<Flight>>& flights, const string& flightNumber) {
    flights.erase(remove_if(flights.begin(), flights.end(),
        [&](shared_ptr<Flight>& flight) { return flight->getFlightNumber() == flightNumber; }), flights.end());
}

void Administrator::viewAllFlights(const vector<shared_ptr<Flight>>& flights) const {
    cout << "--- Flight List ---" << endl;
    for (const auto& flight : flights) {
        cout << "Flight Number: " << flight->getFlightNumber() << endl;
        // Print additional flight details as needed
    }
}

// ================== Aircraft Management ==================
void Administrator::addAircraft(vector<shared_ptr<Aircraft>>& aircrafts, shared_ptr<Aircraft> aircraft) {
    aircrafts.push_back(aircraft);
}

void Administrator::removeAircraft(vector<shared_ptr<Aircraft>>& aircrafts, const string& aircraftID) {
    aircrafts.erase(remove_if(aircrafts.begin(), aircrafts.end(),
        [&](shared_ptr<Aircraft>& a) { return a->getAircraftID() == aircraftID; }), aircrafts.end());
}

// ================== Reporting ==================
void Administrator::generateOperationalReport(const vector<shared_ptr<Flight>>& flights) const {
    cout << "Operational Report" << endl;
    cout << "Total Flights: " << flights.size() << endl;
    // Summarize flight status, delays, cancellations, etc.
}

void Administrator::generateMaintenanceReport(const vector<shared_ptr<Aircraft>>& aircrafts) const {
    cout << "Maintenance Report" << endl;
    // Summarize maintenance logs, schedules, etc.
}

void Administrator::generateUserActivityReport(const vector<shared_ptr<User>>& users) const {
    cout << "User Activity Report" << endl;
    // Summarize user logins/bookings/activities
}

std::shared_ptr<Administrator> Administrator::from_json(const nlohmann::json& j) {
    std::string id = j.at("id").get<std::string>();
    std::string uname = j.at("username").get<std::string>();
    std::string pwdHash = j.at("passwordHash").get<std::string>();
    return std::make_shared<Administrator>(id, uname, pwdHash);
}

void Administrator::to_json(nlohmann::json& j) const {
    j = nlohmann::json{
        {"role", "Administrator"},
        {"id", userID},
        {"username", username},
        {"passwordHash", passwordHash}
    };
}

