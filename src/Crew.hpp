#ifndef CREW_HPP
#define CREW_HPP

#include <string>
#include <vector>

class Crew {
public:
    enum class Role { Pilot, FlightAttendant };

private:
    std::string crewID;
    Role role;
    std::string name;
    int flightHours;                  // For regulatory compliance (max hours)
    bool assigned;                    // Currently assigned to a flight
    std::vector<std::string> assignedFlights; // IDs of flights currently/past assigned

public:
    // --- Constructor ---
    Crew(const std::string& crewID, Role role, const std::string& name);

    // --- Getters ---
    std::string getCrewID() const;
    Role getRole() const;
    std::string getRoleString() const;
    std::string getName() const;
    int getFlightHours() const;
    bool isAssigned() const;
    std::vector<std::string> getAssignedFlights() const;

    // --- Setters and Updates ---
    void setName(const std::string& newName);
    void setRole(Role newRole);
    void addFlightHours(int hours);
    void assignToFlight(const std::string& flightID);
    void unassign();
    void clearFlightAssignments();

    // --- Utilities ---
    void printCrewDetails() const;
    static std::string roleToString(Role r);
    static Role stringToRole(const std::string& str);
};

#endif // CREW_HPP
