#include "User.hpp"
using namespace std;

#include "User.hpp"
#include "Administrator.hpp"
#include "BookingAgent.hpp"
#include "Passenger.hpp"

std::shared_ptr<User> User::from_json(const nlohmann::json& j) {
    if (!j.contains("role")) return nullptr;
    std::string role = j.at("role").get<std::string>();

    if (role == "Administrator") {
        return Administrator::from_json(j);
    } else if (role == "BookingAgent") {
        return BookingAgent::from_json(j);
    } else if (role == "Passenger") {
        return Passenger::from_json(j);
    } else {
        return nullptr; // Unknown role
    }
}
