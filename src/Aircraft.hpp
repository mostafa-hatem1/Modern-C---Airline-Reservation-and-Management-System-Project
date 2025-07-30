#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <string>
#include <vector>
#include "json.hpp"
#include <memory>

// Forward-declare MaintenanceLog if you have maintenance tracking as a separate class.
class MaintenanceLog;

class Aircraft {
private:
    std::string aircraftID;
    std::string type;
    int seatCapacity;
    std::string status; // e.g., "Available", "In Maintenance", "Out of Service"
    std::vector<std::string> maintenanceSchedule; // e.g., YYYY-MM-DD
    std::vector<std::string> maintenanceLogs; // Or vector<MaintenanceLog> if implemented

public:
    // --- Constructor ---
    Aircraft(const std::string& id, const std::string& type, int seatCapacity);

    // --- Getters ---
    std::string getAircraftID() const;
    std::string getType() const;
    int getSeatCapacity() const;
    std::string getStatus() const;
    std::vector<std::string> getMaintenanceSchedule() const;
    std::vector<std::string> getMaintenanceLogs() const;

    // --- Setters ---
    void setStatus(const std::string& newStatus);
    void setType(const std::string& newType);

    // --- Maintenance Management ---
    void addMaintenanceDate(const std::string& date);
    void addMaintenanceLog(const std::string& log); // Expandable for logs as objects
    void clearMaintenanceLogs();

    // --- Utilities ---
    bool isAvailable() const;
    void printAircraftDetails() const;

    void to_json(nlohmann::json& j) const;
    static std::shared_ptr<Aircraft> from_json(const nlohmann::json& j);
};

#endif // AIRCRAFT_HPP
