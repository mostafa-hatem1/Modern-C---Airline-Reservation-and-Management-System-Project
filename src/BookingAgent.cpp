#include "BookingAgent.hpp"
#include "Passenger.hpp"
#include "Flight.hpp"
#include "Reservation.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

// Constructor
BookingAgent::BookingAgent(const string& id, const string& uname, const string& pwdHash)
    : User(id, uname, pwdHash) {}

// Role identifier
string BookingAgent::getRole() const {
    return "BookingAgent";
}

// Password check (replace with hash logic if needed)
bool BookingAgent::verifyPassword(const string& password) const {
    return passwordHash == password;
}

// 1. Search flights based on criteria
void BookingAgent::searchFlights(
        const vector<shared_ptr<Flight>>& flights,
        const string& origin,
        const string& destination,
        const string& date) const {
    cout << "Available flights from " << origin << " to " << destination << " on " << date << ":\n";
    bool found = false;
    for (const auto& flight : flights) {
        if (flight->getOrigin() == origin &&
            flight->getDestination() == destination &&
            flight->getDepartureDate() == date) {
            cout << "- Flight: " << flight->getFlightNumber() << ", Departs: " 
                 << flight->getDepartureTime() << endl;
            found = true;
        }
    }
    if (!found) cout << "No matching flights found.\n";
}

// 2. Book a flight for a passenger
shared_ptr<Reservation> BookingAgent::bookFlight(
        vector<shared_ptr<Reservation>>& reservations,
        shared_ptr<Passenger> passenger,
        shared_ptr<Flight> flight,
        const string& seatNumber,
        const string& paymentMethod,
        const string& paymentDetails) {
    // Check if seat is available (assuming Flight has isSeatAvailable)
    if (!flight->isSeatAvailable(seatNumber)) {
        cout << "Seat " << seatNumber << " is not available. Booking failed.\n";
        return nullptr;
    }
    // Simulate payment processing (to be expanded)
    bool paymentSuccess = true; // Pretend payment is always successful for now
    if (!paymentSuccess) {
        cout << "Payment failed.\n";
        return nullptr;
    }
    // Reserve seat in flight
    flight->reserveSeat(seatNumber);

    // Create new reservation
    string resID = "R" + to_string(reservations.size() + 1); // Simple reservation ID
    auto reservation = make_shared<Reservation>(resID, passenger, flight, seatNumber, "Confirmed");
    reservations.push_back(reservation);
    cout << "Booking successful. Reservation ID: " << resID << endl;
    return reservation;
}

// 3. Modify reservation (change seat)
bool BookingAgent::modifyReservation(
        vector<shared_ptr<Reservation>>& reservations,
        const string& reservationID,
        const string& newSeatNumber) {
    for (auto& reservation : reservations) {
        if (reservation->getReservationID() == reservationID) {
            auto flight = reservation->getFlight();
            if (!flight->isSeatAvailable(newSeatNumber)) {
                cout << "Seat " << newSeatNumber << " is not available." << endl;
                return false;
            }
            // Free the old seat and reserve the new one
            flight->freeSeat(reservation->getSeatNumber());
            flight->reserveSeat(newSeatNumber);

            reservation->setSeatNumber(newSeatNumber);
            cout << "Reservation updated. New seat: " << newSeatNumber << endl;
            return true;
        }
    }
    cout << "Reservation ID not found.\n";
    return false;
}

// 4. Cancel reservation
bool BookingAgent::cancelReservation(
        vector<shared_ptr<Reservation>>& reservations,
        const string& reservationID) {
    auto it = remove_if(reservations.begin(), reservations.end(),
        [&](const shared_ptr<Reservation>& res) {
            if (res->getReservationID() == reservationID) {
                auto flight = res->getFlight();
                flight->freeSeat(res->getSeatNumber());
                cout << "Reservation cancelled and seat freed.\n";
                return true;
            }
            return false;
        });
    if (it != reservations.end()) {
        reservations.erase(it, reservations.end());
        return true;
    }
    cout << "Reservation ID not found for cancellation.\n";
    return false;
}

// 5. View all reservations for a passenger
void BookingAgent::viewReservations(
        const vector<shared_ptr<Reservation>>& reservations,
        const string& passengerID) const {
    bool found = false;
    for (const auto& res : reservations) {
        if (res->getPassenger()->getUserID() == passengerID) {
            cout << "Reservation ID: " << res->getReservationID()
                 << ", Flight: " << res->getFlight()->getFlightNumber()
                 << ", Seat: " << res->getSeatNumber()
                 << ", Status: " << res->getStatus() << endl;
            found = true;
        }
    }
    if (!found) cout << "No reservations found for this passenger.\n";
}
