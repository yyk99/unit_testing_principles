
#include <vector>
#include <string>
#include <stdexcept>

#include "string_split.h"

enum UserType
{
    Customer = 1,
    Employee = 2
};

class IBus
{
public:
    virtual void Send(std::string message) = 0;
};

class MessageBus
{
private:
    IBus& _bus;

public:
    void SendEmailChangedMessage(int userId, std::string newEmail)
    {
        _bus.Send("Subject: USER; Type: EMAIL CHANGED; Id: {userId}; NewEmail: {newEmail}");
    }
};

class Precondition
{
public:
    static void Requires(bool precondition, std::string message = {})
    {
        if (precondition == false)
            throw std::runtime_error(message);
    }
};

class User
{
public:
    int UserId{}; //{ get; private set; }
    std::string Email; //{ get; private set; }
    UserType Type; //{ get; private set; }

    User(int userId, std::string email, UserType type)
    {
        UserId = userId;
        Email = email;
        Type = type;
    }

    User() = default;

public:
    int ChangeEmail(std::string newEmail,
        std::string companyDomainName, int numberOfEmployees)
    {
        if (Email == newEmail)
            return numberOfEmployees;

        std::string emailDomain = split_string(newEmail, '@')[1];
        bool isEmailCorporate = emailDomain == companyDomainName;
        UserType newType = isEmailCorporate
            ? UserType::Employee
            : UserType::Customer;

        if (Type != newType)
        {
            int delta = newType == UserType::Employee ? 1 : -1;
            int newNumber = numberOfEmployees + delta;
            numberOfEmployees = newNumber;
        }

        Email = newEmail;
        Type = newType;

        return numberOfEmployees;
    }
};

class UserFactory
{
public:
    static User Create(std::vector<std::string> data)
    {
        Precondition::Requires(data.size() >= 3);

        int id = atoi(data[0].c_str());
        std::string email = (std::string)data[1];
        UserType type = (UserType)atoi(data[2].c_str());

        return User(id, email, type);
    }
};

class Database
{
public:
    std::vector<std::string> GetUserById(int userId)
    {
        return {};
    }

public:
    User GetUserByEmail(std::string email)
    {
        return User();
    }

public:
    void SaveUser(User user)
    {
    }

public:
    std::vector<std::string> GetCompany()
    {
        return {};
    }

public:
    void SaveCompany(int newNumber)
    {
    }
};

class UserController
{
private:
    Database &_database;
    MessageBus &_messageBus;

public:
    void ChangeEmail(int userId, std::string newEmail)
    {
        std::vector<std::string> userData = _database.GetUserById(userId);
        User user = UserFactory::Create(userData);

        std::vector<std::string> companyData = _database.GetCompany();
        std::string companyDomainName = (std::string)companyData[0];
        int numberOfEmployees = atoi(companyData[1].c_str());

        int newNumberOfEmployees = user.ChangeEmail(
            newEmail, companyDomainName, numberOfEmployees);

        _database.SaveCompany(newNumberOfEmployees);
        _database.SaveUser(user);
        _messageBus.SendEmailChangedMessage(userId, newEmail);
    }
};


