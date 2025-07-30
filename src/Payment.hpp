#ifndef PAYMENT_HPP
#define PAYMENT_HPP

#include <string>
#include "json.hpp"
#include <memory>


class Payment {
public:
    enum class Status { Pending, Completed, Refunded, Failed };

private:
    std::string paymentID;
    std::string method;         // "Credit Card", "Cash", "PayPal"
    std::string details;        // e.g., card number, PayPal email
    double amount;
    Status status;

public:
    // --- Constructor ---
    Payment(const std::string& paymentID,
            const std::string& method,
            const std::string& details,
            double amount,
            Status status = Status::Pending);

    // --- Getters ---
    std::string getPaymentID() const;
    std::string getMethod() const;
    std::string getDetails() const;
    double getAmount() const;
    Status getStatus() const;

    // --- Setters and Updates ---
    void setStatus(Status newStatus);

    // --- Refund Handling ---
    bool processRefund();

    // --- Utility ---
    static std::string statusToString(Status s);
    static Status stringToStatus(const std::string& str);
    void printPaymentDetails() const;

    void to_json(nlohmann::json& j) const;
    static std::shared_ptr<Payment> from_json(const nlohmann::json& j);
};

#endif // PAYMENT_HPP
