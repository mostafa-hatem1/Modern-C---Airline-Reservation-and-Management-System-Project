#include "Payment.hpp"
#include <iostream>
#include <utility>
#include <iomanip>
using namespace std;
using json = nlohmann::json;

// --- Constructor ---
Payment::Payment(const string& paymentID,
                 const string& method,
                 const string& details,
                 double amount,
                 Status status)
    : paymentID(std::move(paymentID)),
      method(std::move(method)),
      details(std::move(details)),
      amount(amount),
      status(status)
{}

// --- Getters ---
string Payment::getPaymentID() const   { return paymentID; }
string Payment::getMethod() const      { return method; }
string Payment::getDetails() const     { return details; }
double Payment::getAmount() const      { return amount; }
Payment::Status Payment::getStatus() const { return status; }

// --- Setters and Updates ---
void Payment::setStatus(Status newStatus) { status = newStatus; }

// --- Refund Handling ---
bool Payment::processRefund() {
    if (status == Status::Completed) {
        status = Status::Refunded;
        cout << "Refund processed successfully for Payment ID: " << paymentID << "\n";
        return true;
    } else if (status == Status::Refunded) {
        cout << "Refund has already been processed for this payment.\n";
        return false;
    } else {
        cout << "Refund cannot be processed for Payment ID: " << paymentID << " (status: " << statusToString(status) << ")\n";
        return false;
    }
}

// --- Utility ---
string Payment::statusToString(Status s) {
    switch (s) {
        case Status::Pending:   return "Pending";
        case Status::Completed: return "Completed";
        case Status::Refunded:  return "Refunded";
        case Status::Failed:    return "Failed";
        default:                return "Unknown";
    }
}

Payment::Status Payment::stringToStatus(const string& str) {
    if      (str == "Pending")   return Status::Pending;
    else if (str == "Completed") return Status::Completed;
    else if (str == "Refunded")  return Status::Refunded;
    else if (str == "Failed")    return Status::Failed;
    else                         return Status::Pending;
}

void Payment::printPaymentDetails() const {
    cout << fixed << setprecision(2);
    cout << "Payment ID: " << paymentID << "\n"
         << "Method: "    << method     << "\n"
         << "Details: "   << details    << "\n"
         << "Amount: $"   << amount     << "\n"
         << "Status: "    << statusToString(status) << "\n";
}

void Payment::to_json(json& j) const {
    j = json{
        {"paymentID", paymentID},
        {"method", method},
        {"details", details},
        {"amount", amount},
        {"status", statusToString(status)}
    };
}

std::shared_ptr<Payment> Payment::from_json(const json& j) {
    auto p = std::make_shared<Payment>(
                 j.at("paymentID").get<std::string>(),
                 j.at("method").get<std::string>(),
                 j.at("details").get<std::string>(),
                 j.at("amount").get<double>(),
                 stringToStatus(j.at("status").get<std::string>())
             );
    return p;
}
