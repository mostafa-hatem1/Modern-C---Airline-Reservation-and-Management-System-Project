#ifndef PERSISTENCEMANAGER_HPP
#define PERSISTENCEMANAGER_HPP

#include <string>
#include <vector>
#include <memory>

// Forward declarations of key entities
class User;
class Flight;
class Aircraft;
class Reservation;
class Crew;
class Maintenance;
class Payment;

class PersistenceManager {
public:
    // --- Save Methods ---
    static bool saveUsers(const std::vector<std::shared_ptr<User>>& users, const std::string& filename);
    static bool saveFlights(const std::vector<std::shared_ptr<Flight>>& flights, const std::string& filename);
    static bool saveAircraft(const std::vector<std::shared_ptr<Aircraft>>& aircrafts, const std::string& filename);
    static bool saveReservations(const std::vector<std::shared_ptr<Reservation>>& reservations, const std::string& filename);
    static bool saveCrew(const std::vector<std::shared_ptr<Crew>>& crew, const std::string& filename);
    static bool saveMaintenance(const std::vector<std::shared_ptr<Maintenance>>& maintenances, const std::string& filename);
    static bool savePayments(const std::vector<std::shared_ptr<Payment>>& payments, const std::string& filename);

    // --- Load Methods ---
    static bool loadUsers(std::vector<std::shared_ptr<User>>& users, const std::string& filename);
    static bool loadFlights(std::vector<std::shared_ptr<Flight>>& flights, const std::string& filename);
    static bool loadAircraft(std::vector<std::shared_ptr<Aircraft>>& aircrafts, const std::string& filename);
    static bool loadReservations(std::vector<std::shared_ptr<Reservation>>& reservations, const std::string& filename);
    static bool loadCrew(std::vector<std::shared_ptr<Crew>>& crew, const std::string& filename);
    static bool loadMaintenance(std::vector<std::shared_ptr<Maintenance>>& maintenances, const std::string& filename);
    static bool loadPayments(std::vector<std::shared_ptr<Payment>>& payments, const std::string& filename);
};

#endif // PERSISTENCEMANAGER_HPP
