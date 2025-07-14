#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string userID;
    std::string username;
    std::string passwordHash;
public:
    User(const std::string& id, const std::string& uname, const std::string& pwdHash)
        : userID(id), username(uname), passwordHash(pwdHash) {}

    virtual ~User() = default;

    // Pure virtual function to enforce role identification
    virtual std::string getRole() const = 0;

    // Accessors
    std::string getUserID() const { return userID; }
    std::string getUsername() const { return username; }
    std::string getPasswordHash() const { return passwordHash; }

    // Mutators
    void setUsername(const std::string& uname) { username = uname; }
    void setPasswordHash(const std::string& pwdHash) { passwordHash = pwdHash; }

    // Utility: verify password (to be implemented in derived classes)
    virtual bool verifyPassword(const std::string& password) const = 0;
};

#endif // USER_H
