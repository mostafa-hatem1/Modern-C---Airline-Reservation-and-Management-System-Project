#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <string>
#include <memory>
#include <nlohmann/json.hpp>

class Passenger;
class Flight;
class Payment;

class Reservation {
public:
    enum class Status { Confirmed, Cancelled, CheckedIn };

private:
    std::string reservationID;
    std::shared_ptr<Passenger> passenger;
    std::shared_ptr<Flight> flight;
    std::string seatNumber;
    Status status;
    double totalCost;
    std::string paymentMethod;   // e.g., "Credit Card", "Cash", "PayPal"
    std::string paymentDetails;  // e.g., card number, PayPal address
    bool refundProcessed;

public:
    Reservation(const std::string& reservationID,
                std::shared_ptr<Passenger> passenger,
                std::shared_ptr<Flight> flight,
                const std::string& seatNumber,
                double totalCost,
                const std::string& paymentMethod,
                const std::string& paymentDetails);

    // Getters
    std::string getReservationID() const;
    std::shared_ptr<Passenger> getPassenger() const;
    std::shared_ptr<Flight> getFlight() const;
    std::string getSeatNumber() const;
    Status getStatus() const;
    double getTotalCost() const;
    std::string getPaymentMethod() const;
    std::string getPaymentDetails() const;

    // Setters and actions
    void setStatus(Status newStatus);
    void setSeatNumber(const std::string& newSeatNumber);

    // refund flag
    void markRefundProcessed();

    // Util
    static std::string statusToString(Status s);
    static Status stringToStatus(const std::string& str);

    // Present to user (for check-in, etc.)
    void printReservationDetails() const;
    void printBoardingPass(const std::string& gate = "TBD", const std::string& boardingTime = "TBD") const;

    void to_json(nlohmann::json& j) const;
    static std::shared_ptr<Reservation> from_json(const nlohmann::json& j);
};

 

#endif // RESERVATION_HPP
