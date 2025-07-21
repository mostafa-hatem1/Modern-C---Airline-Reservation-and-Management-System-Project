#include "Aircraft.hpp"
#include <iostream>
#include <utility>
using namespace std;

// --- Constructor ---
Aircraft::Aircraft(const string& id, const string& type, int seatCapacity)
    : aircraftID(id), type(type), seatCapacity(seatCapacity), status("Available") {}

// --- Getters ---
string Aircraft::getAircraftID() const           { return aircraftID; }
string Aircraft::getType() const                 { return type; }
int Aircraft::getSeatCapacity() const            { return seatCapacity; }
string Aircraft::getStatus() const               { return status; }
vector<string> Aircraft::getMaintenanceSchedule() const { return maintenanceSchedule; }
vector<string> Aircraft::getMaintenanceLogs() const     { return maintenanceLogs; }

// --- Setters ---
void Aircraft::setStatus(const string& newStatus) { status = newStatus; }
void Aircraft::setType(const string& newType)     { type = newType; }

// --- Maintenance Management ---
void Aircraft::addMaintenanceDate(const string& date)      { maintenanceSchedule.push_back(date); }
void Aircraft::addMaintenanceLog(const string& log)        { maintenanceLogs.push_back(log); }
void Aircraft::clearMaintenanceLogs()                      { maintenanceLogs.clear(); }

// --- Utilities ---
bool Aircraft::isAvailable() const                         { return status == "Available"; }
void Aircraft::printAircraftDetails() const {
    cout << "Aircraft ID: " << aircraftID << "\n"
         << "Type: " << type << "\n"
         << "Seat Capacity: " << seatCapacity << "\n"
         << "Status: " << status << "\n"
         << "Scheduled Maintenance: ";
    if (maintenanceSchedule.empty()) {
        cout << "None\n";
    } else {
        for (const auto& date : maintenanceSchedule) {
            cout << date << " ";
        }
        cout << "\n";
    }
    if (!maintenanceLogs.empty()) {
        cout << "Maintenance Logs:\n";
        for (const auto& log : maintenanceLogs) {
            cout << "- " << log << "\n";
        }
    }
}
