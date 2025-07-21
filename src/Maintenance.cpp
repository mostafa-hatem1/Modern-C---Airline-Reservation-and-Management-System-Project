#include "Maintenance.hpp"
#include <iostream>
#include <utility>
using namespace std;

// --- Constructor ---
Maintenance::Maintenance(const string& maintenanceID,
                         const string& aircraftID,
                         const string& scheduledDate)
    : maintenanceID(maintenanceID),
      aircraftID(aircraftID),
      scheduledDate(scheduledDate),
      performedDate(""),
      technicianName(""),
      notes(""),
      completed(false) {}

// --- Getters ---
string Maintenance::getMaintenanceID()   const { return maintenanceID; }
string Maintenance::getAircraftID()      const { return aircraftID; }
string Maintenance::getScheduledDate()   const { return scheduledDate; }
string Maintenance::getPerformedDate()   const { return performedDate; }
vector<string> Maintenance::getTasks()   const { return tasks; }
string Maintenance::getTechnicianName()  const { return technicianName; }
string Maintenance::getNotes()           const { return notes; }
bool Maintenance::isCompleted()          const { return completed; }

// --- Setters and Updates ---
void Maintenance::setPerformedDate(const string& date)      { performedDate = date; }
void Maintenance::setTechnicianName(const string& name)     { technicianName = name; }
void Maintenance::addTask(const string& task)               { tasks.push_back(task); }
void Maintenance::setNotes(const string& notes_)            { notes = notes_; }
void Maintenance::markCompleted()                           { completed = true; }

// --- Output Utilities ---
void Maintenance::printMaintenanceLog() const {
    cout << "Maintenance ID: " << maintenanceID << "\n"
         << "Aircraft ID: " << aircraftID << "\n"
         << "Scheduled Date: " << scheduledDate << "\n"
         << "Performed Date: " << (performedDate.empty() ? "N/A" : performedDate) << "\n"
         << "Technician: " << (technicianName.empty() ? "N/A" : technicianName) << "\n"
         << "Status: " << (completed ? "Completed" : "Pending") << "\n"
         << "Tasks:\n";
    if (tasks.empty()) {
        cout << "  - None logged\n";
    } else {
        for (const auto& t : tasks)
            cout << "  - " << t << "\n";
    }
    cout << "Notes: " << (notes.empty() ? "N/A" : notes) << "\n";
}
