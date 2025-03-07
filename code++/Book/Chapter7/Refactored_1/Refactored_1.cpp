#include <string>
#include <vector>

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
    IBus& _bus;

public:
    void SendEmailChangedMessage(int userId, std::string newEmail)
    {
        _bus.Send("Subject: USER; Type: EMAIL CHANGED; Id: {userId}; NewEmail: {newEmail}");
    }
};

class User
{
public:
    int UserId;//{ get; private set; }
    std::string Email;//{ get; private set; }
    UserType Type;//{ get; private set; }

public:
    User(int userId, std::string email, UserType type)
        :
        UserId(userId)
        , Email(email)
        , Type(type)
    {
    }

    User()
        : UserId{ -1 }
        , Type{}
    {
    }

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

class Database
{
public:
    std::vector<std::string> GetUserById(int userId)
    {
        return {};
    }

    User GetUserByEmail(std::string email)
    {
        return User();
    }

    void SaveUser(User user)
    {
    }

    std::vector<std::string> GetCompany()
    {
        return {};
    }

    void SaveCompany(int newNumber)
    {
    }
};



class UserController
{
    Database _database; // = new Database();
    MessageBus _messageBus; // = new MessageBus();

public:
    void ChangeEmail(int userId, std::string newEmail)
    {
        auto data = _database.GetUserById(userId);
        std::string email = (std::string)data[1];
        UserType type = (UserType)atoi(data[2].c_str());
        auto user = User(userId, email, type);

        auto companyData = _database.GetCompany();
        std::string companyDomainName = (std::string)companyData[0];
        int numberOfEmployees = atoi(companyData[1].c_str());

        int newNumberOfEmployees = user.ChangeEmail(
            newEmail, companyDomainName, numberOfEmployees);

        _database.SaveCompany(newNumberOfEmployees);
        _database.SaveUser(user);
        _messageBus.SendEmailChangedMessage(userId, newEmail);
    }
};

