#include "Crew.hpp"
#include <iostream>
using namespace std;

// --- Constructor ---
Crew::Crew(const string& crewID, Role role, const string& name)
    : crewID(crewID), role(role), name(name), flightHours(0), assigned(false) {}

// --- Getters ---
string Crew::getCrewID() const                { return crewID; }
Crew::Role Crew::getRole() const              { return role; }
string Crew::getRoleString() const            { return roleToString(role); }
string Crew::getName() const                  { return name; }
int Crew::getFlightHours() const              { return flightHours; }
bool Crew::isAssigned() const                 { return assigned; }
vector<string> Crew::getAssignedFlights() const { return assignedFlights; }

// --- Setters and Updates ---
void Crew::setName(const string& newName)         { name = newName; }
void Crew::setRole(Role newRole)                  { role = newRole; }
void Crew::addFlightHours(int hours)              { flightHours += hours; }
void Crew::assignToFlight(const string& flightID) {
    assigned = true;
    assignedFlights.push_back(flightID);
}
void Crew::unassign()                             { assigned = false; }
void Crew::clearFlightAssignments()               { assignedFlights.clear(); }

// --- Utilities ---
void Crew::printCrewDetails() const {
    cout << "Crew ID: " << crewID << "\n"
         << "Name: " << name << "\n"
         << "Role: " << roleToString(role) << "\n"
         << "Flight Hours: " << flightHours << "\n"
         << "Currently Assigned: " << (assigned ? "Yes" : "No") << "\n";
    if (!assignedFlights.empty()) {
        cout << "Assigned Flights: ";
        for (const auto& fid : assignedFlights) {
            cout << fid << " ";
        }
        cout << endl;
    }
}

string Crew::roleToString(Role r) {
    switch (r) {
        case Role::Pilot: return "Pilot";
        case Role::FlightAttendant: return "Flight Attendant";
        default: return "Unknown";
    }
}

Crew::Role Crew::stringToRole(const string& str) {
    if (str == "Pilot") return Role::Pilot;
    if (str == "Flight Attendant") return Role::FlightAttendant;
    return Role::Pilot; // Default
}
