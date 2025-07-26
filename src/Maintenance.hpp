#ifndef MAINTENANCE_HPP
#define MAINTENANCE_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <memory>

class Maintenance {
private:
    std::string maintenanceID;         // Unique identifier for this maintenance event
    std::string aircraftID;            // Reference to the aircraft
    std::string scheduledDate;         // Scheduled date for maintenance (YYYY-MM-DD)
    std::string performedDate;         // Date maintenance was actually performed
    std::vector<std::string> tasks;    // List of maintenance tasks performed
    std::string technicianName;        // Main technician responsible
    std::string notes;                 // Additional notes or parts replaced
    bool completed;

public:
    // --- Constructor ---
    Maintenance(const std::string& maintenanceID,
                const std::string& aircraftID,
                const std::string& scheduledDate);

    // --- Getters ---
    std::string getMaintenanceID() const;
    std::string getAircraftID() const;
    std::string getScheduledDate() const;
    std::string getPerformedDate() const;
    std::vector<std::string> getTasks() const;
    std::string getTechnicianName() const;
    std::string getNotes() const;
    bool isCompleted() const;

    // --- Setters and Updates ---
    void setPerformedDate(const std::string& date);
    void setTechnicianName(const std::string& name);
    void addTask(const std::string& task);
    void setNotes(const std::string& notes);
    void markCompleted();

    // --- Output Utilities ---
    void printMaintenanceLog() const;

    void to_json(nlohmann::json& j) const;
    static std::shared_ptr<Maintenance> from_json(const nlohmann::json& j);
};

#endif // MAINTENANCE_HPP
