#include "Reservation.hpp"
#include "Passenger.hpp"
#include "Flight.hpp"
#include <iostream>
#include <iomanip>
#include <utility>
using namespace std;

// --- Constructor ---
Reservation::Reservation(
    std::string reservationID,
    std::shared_ptr<Passenger> passenger,
    std::shared_ptr<Flight> flight,
    std::string seatNumber,
    double totalCost,
    std::string paymentMethod,
    std::string paymentDetails)
    : reservationID(std::move(reservationID)),
      passenger(std::move(passenger)),
      flight(std::move(flight)),
      seatNumber(std::move(seatNumber)),
      status(Status::Confirmed),
      totalCost(totalCost),
      paymentMethod(std::move(paymentMethod)),
      paymentDetails(std::move(paymentDetails)),
      refundProcessed(false)
{}

// --- Getters ---
std::string Reservation::getReservationID() const            { return reservationID; }
std::shared_ptr<Passenger> Reservation::getPassenger() const { return passenger; }
std::shared_ptr<Flight> Reservation::getFlight()  const      { return flight; }
std::string Reservation::getSeatNumber()          const      { return seatNumber; }
double Reservation::getTotalCost()                const      { return totalCost; }
Reservation::Status Reservation::getStatus()      const      { return status; }
std::string Reservation::getPaymentMethod()       const      { return paymentMethod; }
std::string Reservation::getPaymentDetails()      const      { return paymentDetails; }

// --- Setters and State Updates ---
void Reservation::setStatus(Status newStatus)             { status = newStatus; }
void Reservation::setSeatNumber(const std::string& newSeatNumber) { seatNumber = newSeatNumber; }
void Reservation::markRefundProcessed()                   { refundProcessed = true; }

// --- Status Utilities ---
std::string Reservation::statusToString(Status s) {
    switch (s) {
        case Status::Confirmed:  return "Confirmed";
        case Status::Cancelled:  return "Cancelled";
        case Status::CheckedIn:  return "Checked-in";
        default:                 return "Unknown";
    }
}
Reservation::Status Reservation::stringToStatus(const std::string& str) {
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

void Reservation::printBoardingPass(const std::string& gate, const std::string& boardingTime) const {
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
