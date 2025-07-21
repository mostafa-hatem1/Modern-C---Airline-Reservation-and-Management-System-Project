#include "PersistenceManager.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

// --- Utility: Save JSON to File ---
static bool saveJsonToFile(const json& j, const string& filename) {
    try {
        fs::create_directories(fs::path(filename).parent_path());
        ofstream ofs(filename);
        if (!ofs) throw runtime_error("Unable to write to " + filename);
        ofs << j.dump(4); // pretty print
        return true;
    } catch (const exception& ex) {
        cerr << "File error writing " << filename << ": " << ex.what() << endl;
        return false;
    }
}

// --- Utility: Load JSON from File ---
static bool loadJsonFromFile(json& j, const string& filename) {
    try {
        ifstream ifs(filename);
        if (!ifs) throw runtime_error("File " + filename + " not found.");
        ifs >> j;
        return true;
    } catch (const exception& ex) {
        cerr << "File error reading " << filename << ": " << ex.what() << endl;
        return false;
    }
}

// --- USERS ---
bool PersistenceManager::saveUsers(const vector<shared_ptr<User>>& users, const string& filename) {
    json jarr = json::array();
    for (const auto& user : users) {
        json j;
        user->to_json(j); // Each user subclass must implement to_json
        jarr.push_back(j);
    }
    return saveJsonToFile(jarr, filename);
}

bool PersistenceManager::loadUsers(vector<shared_ptr<User>>& users, const string& filename) {
    json jarr;
    if (!loadJsonFromFile(jarr, filename)) return false;
    users.clear();
    for (const auto& j : jarr) {
        auto user = User::from_json(j); // Static/factory reconstructs concrete type
        if (user) users.push_back(user);
    }
    return true;
}

// --- FLIGHTS ---
bool PersistenceManager::saveFlights(const vector<shared_ptr<Flight>>& flights, const string& filename) {
    json jarr = json::array();
    for (const auto& flight : flights) {
        json j;
        flight->to_json(j);
        jarr.push_back(j);
    }
    return saveJsonToFile(jarr, filename);
}

bool PersistenceManager::loadFlights(vector<shared_ptr<Flight>>& flights, const string& filename) {
    json jarr;
    if (!loadJsonFromFile(jarr, filename)) return false;
    flights.clear();
    for (const auto& j : jarr) {
        auto flight = Flight::from_json(j);
        if (flight) flights.push_back(flight);
    }
    return true;
}

// --- AIRCRAFT ---
bool PersistenceManager::saveAircraft(const vector<shared_ptr<Aircraft>>& aircrafts, const string& filename) {
    json jarr = json::array();
    for (const auto& aircraft : aircrafts) {
        json j;
        aircraft->to_json(j);
        jarr.push_back(j);
    }
    return saveJsonToFile(jarr, filename);
}

bool PersistenceManager::loadAircraft(vector<shared_ptr<Aircraft>>& aircrafts, const string& filename) {
    json jarr;
    if (!loadJsonFromFile(jarr, filename)) return false;
    aircrafts.clear();
    for (const auto& j : jarr) {
        auto aircraft = Aircraft::from_json(j);
        if (aircraft) aircrafts.push_back(aircraft);
    }
    return true;
}

// --- RESERVATIONS ---
bool PersistenceManager::saveReservations(const vector<shared_ptr<Reservation>>& reservations, const string& filename) {
    json jarr = json::array();
    for (const auto& res : reservations) {
        json j;
        res->to_json(j);
        jarr.push_back(j);
    }
    return saveJsonToFile(jarr, filename);
}

bool PersistenceManager::loadReservations(vector<shared_ptr<Reservation>>& reservations, const string& filename) {
    json jarr;
    if (!loadJsonFromFile(jarr, filename)) return false;
    reservations.clear();
    for (const auto& j : jarr) {
        auto res = Reservation::from_json(j);
        if (res) reservations.push_back(res);
    }
    return true;
}

// --- CREW ---
bool PersistenceManager::saveCrew(const vector<shared_ptr<Crew>>& crew, const string& filename) {
    json jarr = json::array();
    for (const auto& c : crew) {
        json j;
        c->to_json(j);
        jarr.push_back(j);
    }
    return saveJsonToFile(jarr, filename);
}

bool PersistenceManager::loadCrew(vector<shared_ptr<Crew>>& crew, const string& filename) {
    json jarr;
    if (!loadJsonFromFile(jarr, filename)) return false;
    crew.clear();
    for (const auto& j : jarr) {
        auto c = Crew::from_json(j);
        if (c) crew.push_back(c);
    }
    return true;
}

// --- MAINTENANCE ---
bool PersistenceManager::saveMaintenance(const vector<shared_ptr<Maintenance>>& maintenances, const string& filename) {
    json jarr = json::array();
    for (const auto& m : maintenances) {
        json j;
        m->to_json(j);
        jarr.push_back(j);
    }
    return saveJsonToFile(jarr, filename);
}

bool PersistenceManager::loadMaintenance(vector<shared_ptr<Maintenance>>& maintenances, const string& filename) {
    json jarr;
    if (!loadJsonFromFile(jarr, filename)) return false;
    maintenances.clear();
    for (const auto& j : jarr) {
        auto m = Maintenance::from_json(j);
        if (m) maintenances.push_back(m);
    }
    return true;
}

// --- PAYMENTS ---
bool PersistenceManager::savePayments(const vector<shared_ptr<Payment>>& payments, const string& filename) {
    json jarr = json::array();
    for (const auto& p : payments) {
        json j;
        p->to_json(j);
        jarr.push_back(j);
    }
    return saveJsonToFile(jarr, filename);
}

bool PersistenceManager::loadPayments(vector<shared_ptr<Payment>>& payments, const string& filename) {
    json jarr;
    if (!loadJsonFromFile(jarr, filename)) return false;
    payments.clear();
    for (const auto& j : jarr) {
        auto p = Payment::from_json(j);
        if (p) payments.push_back(p);
    }
    return true;
}
