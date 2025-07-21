#ifndef REPORTING_HPP
#define REPORTING_HPP

#include <vector>
#include <memory>
#include <string>

// Forward declarations
class Flight;
class Reservation;
class Aircraft;
class Maintenance;
class User;

class Reporting {
public:
    // --- Operational ---
    static void generateOperationalReport(
        const std::vector<std::shared_ptr<Flight>>& flights,
        const std::vector<std::shared_ptr<Reservation>>& reservations,
        const std::string& monthYear // Format: MM-YYYY
    );

    // --- Maintenance ---
    static void generateMaintenanceReport(
        const std::vector<std::shared_ptr<Aircraft>>& aircrafts,
        const std::vector<std::shared_ptr<Maintenance>>& maintenances,
        const std::string& monthYear
    );

    // --- User Activity ---
    static void generateUserActivityReport(
        const std::vector<std::shared_ptr<User>>& users,
        const std::vector<std::shared_ptr<Reservation>>& reservations,
        const std::string& monthYear
    );
};

#endif // REPORTING_HPP
