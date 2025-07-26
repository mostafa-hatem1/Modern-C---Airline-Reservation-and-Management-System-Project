#ifndef BOOKINGAGENT_HPP
#define BOOKINGAGENT_HPP

#include "User.hpp"
#include <string>
#include <vector>
#include <memory>

// Forward declarations
class Passenger;
class Flight;
class Reservation;

class BookingAgent : public User {
public:
    BookingAgent(const std::string& id, const std::string& uname, const std::string& pwdHash);

    std::string getRole() const override;
    bool verifyPassword(const std::string& password) const override;

    // 1. Search flights
    void searchFlights(const std::vector<std::shared_ptr<Flight>>& flights,
                      const std::string& origin,
                      const std::string& destination,
                      const std::string& date) const;

    // 2. Book a flight for a passenger
    std::shared_ptr<Reservation> bookFlight(
        std::vector<std::shared_ptr<Reservation>>& reservations,
        std::shared_ptr<Passenger> passenger,
        std::shared_ptr<Flight> flight,
        const std::string& seatNumber,
        const std::string& paymentMethod,
        const std::string& paymentDetails);

    // 3. Modify a reservation (change seat)
    bool modifyReservation(
        std::vector<std::shared_ptr<Reservation>>& reservations,
        const std::string& reservationID,
        const std::string& newSeatNumber);

    // 4. Cancel a reservation
    bool cancelReservation(
        std::vector<std::shared_ptr<Reservation>>& reservations,
        const std::string& reservationID);

    // 5. View all reservations by passenger
    void viewReservations(const std::vector<std::shared_ptr<Reservation>>& reservations,
                          const std::string& passengerID) const;
                          
    static std::shared_ptr<BookingAgent> from_json(const nlohmann::json& j);
    void to_json(nlohmann::json& j) const override;
};

#endif // BOOKINGAGENT_HPP
