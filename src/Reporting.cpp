#include "Reporting.hpp"
#include "Flight.hpp"
#include "Reservation.hpp"
#include "Aircraft.hpp"
#include "Maintenance.hpp"
#include "User.hpp"

#include <iostream>
#include <iomanip>
#include <map>
using namespace std;

// --- Operational Report ---
void Reporting::generateOperationalReport(
    const vector<shared_ptr<Flight>>& flights,
    const vector<shared_ptr<Reservation>>& reservations,
    const string& monthYear)
{
    int totalFlights = 0, completed = 0, delayed = 0, canceled = 0;
    int totalReservations = 0;
    double totalRevenue = 0.0;
    map<string, int> bookingPerFlight;
    map<string, double> revenuePerFlight;

    for (const auto& flight : flights) {
        if (flight->getDepartureDate().substr(5, 2) + "-" + flight->getDepartureDate().substr(0, 4) == monthYear) {
            totalFlights++;
            auto status = Flight::statusToString(flight->getStatus());
            if (status == "Scheduled" || status == "Completed") completed++;
            if (status == "Delayed") delayed++;
            if (status == "Canceled") canceled++;
        }
    }
    for (const auto& res : reservations) {
        if (res->getFlight()->getDepartureDate().substr(5, 2) + "-" + res->getFlight()->getDepartureDate().substr(0, 4) == monthYear) {
            totalReservations++;
            bookingPerFlight[res->getFlight()->getFlightNumber()]++;
            revenuePerFlight[res->getFlight()->getFlightNumber()] += res->getTotalCost();
            totalRevenue += res->getTotalCost();
        }
    }
    cout << fixed << setprecision(2);
    cout << "Report Summary:\n";
    cout << "- Total Flights Scheduled: " << totalFlights << '\n';
    cout << "- Flights Completed: " << completed << '\n';
    cout << "- Flights Delayed: " << delayed << '\n';
    cout << "- Flights Canceled: " << canceled << '\n';
    cout << "- Total Reservations Made: " << totalReservations << '\n';
    cout << "- Total Revenue: $" << totalRevenue << "\n\n";
    cout << "Detailed Flight Performance:\n";
    int idx = 1;
    for (const auto& f : flights) {
        string key = f->getFlightNumber();
        if (bookingPerFlight[key] > 0) {
            cout << idx++ << ". Flight " << key << ": "
                 << Flight::statusToString(f->getStatus())
                 << " (" << bookingPerFlight[key] << " Bookings, $"
                 << revenuePerFlight[key] << ")\n";
        }
    }
}

// --- Maintenance Report ---
void Reporting::generateMaintenanceReport(
    const vector<shared_ptr<Aircraft>>& aircrafts,
    const vector<shared_ptr<Maintenance>>& maintenances,
    const string& monthYear)
{
    cout << "Maintenance Report for " << monthYear << ":\n";
    int scheduled = 0, completed = 0;
    for (const auto& m : maintenances) {
        if (m->getScheduledDate().substr(5, 2) + "-" + m->getScheduledDate().substr(0, 4) == monthYear) {
            scheduled++;
            if (m->isCompleted()) completed++;
            cout << "- Aircraft: " << m->getAircraftID()
                 << ", Scheduled: " << m->getScheduledDate()
                 << ", Performed: " << m->getPerformedDate()
                 << ", Status: " << (m->isCompleted() ? "Completed" : "Pending") << '\n';
        }
    }
    cout << "- Total Maintenance Scheduled: " << scheduled << '\n';
    cout << "- Total Completed: " << completed << '\n';
}

// --- User Activity Report ---
void Reporting::generateUserActivityReport(
    const vector<shared_ptr<User>>& users,
    const vector<shared_ptr<Reservation>>& reservations,
    const string& monthYear)
{
    cout << "User Activity Report for " << monthYear << ":\n";
    map<string, int> reservationsByUser;
    for (const auto& res : reservations) {
        if (res->getFlight()->getDepartureDate().substr(5, 2) + "-" + res->getFlight()->getDepartureDate().substr(0, 4) == monthYear) {
            reservationsByUser[res->getPassenger()->getUserID()]++;
        }
    }
    for (const auto& user : users) {
        cout << "- User: " << user->getUsername() << ", Role: " << user->getRole()
             << ", Bookings Made: " << reservationsByUser[user->getUserID()] << '\n';
    }
}
