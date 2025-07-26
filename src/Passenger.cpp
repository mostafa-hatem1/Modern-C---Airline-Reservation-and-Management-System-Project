#include "Passenger.hpp"
#include "Reservation.hpp"
#include "Flight.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

Passenger::Passenger(const string& id, const string& uname, const string& pwdHash)
    : User(id, uname, pwdHash), loyaltyPoints(0) {}

string Passenger::getRole() const {
    return "Passenger";
}

bool Passenger::verifyPassword(const string& password) const {
    return passwordHash == password;
}

// -- Profile Management --

void Passenger::updateProfile(const string& newUsername) {
    username = newUsername;
}

int Passenger::getLoyaltyPoints() const {
    return loyaltyPoints;
}

void Passenger::addLoyaltyPoints(int points) {
    loyaltyPoints += points;
}

bool Passenger::redeemLoyaltyPoints(int points) {
    if (points > loyaltyPoints) return false;
    loyaltyPoints -= points;
    return true;
}

// -- Reservation Viewing --

void Passenger::viewBookings(const vector<shared_ptr<Reservation>>& reservations) const {
    bool found = false;
    for (const auto& res : reservations) {
        if (res->getPassenger()->getUserID() == userID) {
            cout << "Reservation ID: " << res->getReservationID()
                 << ", Flight: " << res->getFlight()->getFlightNumber()
                 << ", Seat: " << res->getSeatNumber()
                 << ", Status: " << Reservation::statusToString(res->getStatus()) << endl;
            found = true;
        }
    }
    if (!found) cout << "No bookings found.\n";
}

void Passenger::viewBoardingPass(const vector<shared_ptr<Reservation>>& reservations, const string& reservationID) const {
    for (const auto& res : reservations) {
        if (res->getReservationID() == reservationID && res->getPassenger()->getUserID() == userID) {
            cout << "=== Boarding Pass ===" << endl;
            cout << "Passenger: " << username << endl;
            cout << "Flight: " << res->getFlight()->getFlightNumber() << endl;
            cout << "Seat: " << res->getSeatNumber() << endl;
            cout << "Status: " << Reservation::statusToString(res->getStatus()) << endl;
            cout << "=====================" << endl;
            return;
        }
    }
    cout << "Reservation not found or does not belong to you.\n";
}

// -- Optional: Search flights (self-service) --

void Passenger::searchFlights(const vector<shared_ptr<Flight>>& flights,
                   const string& origin,
                   const string& destination,
                   const string& date) const {
    cout << "Your search: " << origin << " to " << destination << ", date: " << date << endl;
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
    if (!found) cout << "No flights found matching criteria.\n";
}

// -- Online check-in (marks reservation as checked in) --

bool Passenger::onlineCheckIn(vector<shared_ptr<Reservation>>& reservations, const string& reservationID) {
    for (auto& res : reservations) {
        if (res->getReservationID() == reservationID && res->getPassenger()->getUserID() == userID) {
            if (res->getStatus() == Reservation::Status::CheckedIn) {
                cout << "Already checked in.\n";
                return false;
            }
            res->setStatus(Reservation::Status::CheckedIn);
            cout << "Check-in successful. You are now checked in.\n";
            return true;
        }
    }
    cout << "Reservation not found or not yours.\n";
    return false;
}


// -- Cancel reservation (marks as cancelled and could trigger refund logic) --

bool Passenger::cancelReservation(vector<shared_ptr<Reservation>>& reservations, const string& reservationID) {
    auto it = find_if(reservations.begin(), reservations.end(),
        [&](const shared_ptr<Reservation>& res) {
            return res->getReservationID() == reservationID && res->getPassenger()->getUserID() == userID;
        });
    if (it != reservations.end()) {
        (*it)->setStatus(Reservation::Status::Cancelled);
        cout << "Reservation cancelled successfully.\n";
        // (Optional: trigger refund logic here if needed)
        return true;
    }
    cout << "Reservation not found or not yours.\n";
    return false;
}

std::shared_ptr<Passenger> Passenger::from_json(const nlohmann::json& j) {
    std::string id = j.at("id").get<std::string>();
    std::string uname = j.at("username").get<std::string>();
    std::string pwdHash = j.at("passwordHash").get<std::string>();
    // Optionally handle loyaltyPoints
    auto p = std::make_shared<Passenger>(id, uname, pwdHash);
    if (j.contains("loyaltyPoints")) {
        p->addLoyaltyPoints(j.at("loyaltyPoints").get<int>());
    }
    return p;
}

void Passenger::to_json(nlohmann::json& j) const {
    j = nlohmann::json{
        {"role", "Passenger"},
        {"id", userID},
        {"username", username},
        {"passwordHash", passwordHash},
        {"loyaltyPoints", getLoyaltyPoints()}
    };
}


