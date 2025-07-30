#include "Reservation.hpp"
#include "Passenger.hpp"
#include "Flight.hpp"

#include <iostream>
#include <iomanip>
#include <utility>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

// --- Constructor ---
Reservation::Reservation(const string& reservationID,
                         shared_ptr<Passenger> passenger,
                         shared_ptr<Flight> flight,
                         const string& seatNumber,
                         double totalCost,
                         const string& paymentMethod,
                         const string& paymentDetails)
    : reservationID(reservationID),
      passenger(std::move(passenger)),
      flight(std::move(flight)),
      seatNumber(seatNumber),
      status(Status::Confirmed),
      totalCost(totalCost),
      paymentMethod(paymentMethod),
      paymentDetails(paymentDetails),
      refundProcessed(false)
{}

// --- Getters ---
string Reservation::getReservationID() const { return reservationID; }
shared_ptr<Passenger> Reservation::getPassenger() const { return passenger; }
shared_ptr<Flight> Reservation::getFlight() const { return flight; }
string Reservation::getSeatNumber() const { return seatNumber; }
Reservation::Status Reservation::getStatus() const { return status; }
double Reservation::getTotalCost() const { return totalCost; }
string Reservation::getPaymentMethod() const { return paymentMethod; }
string Reservation::getPaymentDetails() const { return paymentDetails; }

// --- Setters and State Updates ---
void Reservation::setStatus(Status newStatus) { status = newStatus; }
void Reservation::setSeatNumber(const string& newSeatNumber) { seatNumber = newSeatNumber; }
void Reservation::markRefundProcessed() { refundProcessed = true; }

// --- Status Utilities ---
string Reservation::statusToString(Status s) {
    switch (s) {
        case Status::Confirmed:  return "Confirmed";
        case Status::Cancelled:  return "Cancelled";
        case Status::CheckedIn:  return "Checked-in";
        default:                 return "Unknown";
    }
}

Reservation::Status Reservation::stringToStatus(const string& str) {
    if (str == "Confirmed")  return Status::Confirmed;
    if (str == "Cancelled")  return Status::Cancelled;
    if (str == "Checked-in") return Status::CheckedIn;
    return Status::Confirmed; // Default fallback
}

// --- Presentation Helpers ---
void Reservation::printReservationDetails() const {
    cout << "Reservation ID: " << reservationID << '\n'
         << "Passenger: " << passenger->getUsername() << '\n'
         << "Flight: " << flight->getFlightNumber()
         << " from " << flight->getOrigin()
         << " to "   << flight->getDestination() << '\n'
         << "Seat: " << seatNumber << '\n'
         << "Status: " << statusToString(status) << '\n'
         << fixed << setprecision(2)
         << "Total Cost: $" << totalCost << '\n'
         << "Payment Method: " << paymentMethod << '\n'
         << "Payment Details: " << paymentDetails << "\n";
}

void Reservation::printBoardingPass(const string& gate, const string& boardingTime) const {
    cout << "-----------------------------\n"
         << "Reservation ID: " << reservationID << '\n'
         << "Passenger: " << passenger->getUsername() << '\n'
         << "Flight: " << flight->getFlightNumber() << '\n'
         << "Origin: " << flight->getOrigin() << '\n'
         << "Destination: " << flight->getDestination() << '\n'
         << "Departure: " << flight->getDepartureDate()
         << " " << flight->getDepartureTime() << '\n'
         << "Seat: " << seatNumber << '\n'
         << "Gate: " << gate << '\n'
         << "Boarding Time: " << boardingTime << '\n'
         << "-----------------------------" << endl;
}

// --- JSON Serialization ---
void Reservation::to_json(json& j) const {
    j = json{
        {"reservationID", reservationID},
        {"passengerID", passenger->getUserID()},
        {"flightNumber", flight->getFlightNumber()},
        {"seatNumber", seatNumber},
        {"status", statusToString(status)},
        {"totalCost", totalCost},
        {"paymentMethod", paymentMethod},
        {"paymentDetails", paymentDetails},
        {"refundProcessed", refundProcessed}
    };
}

shared_ptr<Reservation> Reservation::from_json(const json& j) {
    // Passenger and Flight pointers to link after all are loaded, here set nullptr placeholders
    auto reservation = make_shared<Reservation>(
                           j.at("reservationID").get<string>(),
                           nullptr,  // Will be linked later using passengerID
                           nullptr,  // Will be linked later using flightNumber
                           j.at("seatNumber").get<string>(),
                           j.at("totalCost").get<double>(),
                           j.at("paymentMethod").get<string>(),
                           j.at("paymentDetails").get<string>()
                       );
    reservation->setStatus(stringToStatus(j.at("status").get<string>()));
    reservation->refundProcessed = j.value("refundProcessed", false);
    return reservation;
}
