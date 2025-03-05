//
// Book/Chapter7/CanExecute/CanExecute.cpp
//
#include <string>
#include <stdexcept>
#include <vector>
#include <cstddef>

#include "string_split.h"

enum UserType
{
    Customer = 1,
    Employee = 2,
};

class Precondition
{
public:
    static void Requires(bool precondition, std::string message = "")
    {
        if (precondition == false)
            throw std::runtime_error(message);
    }
};

class Company
{
public:
    std::string DomainName; //{ get; private set; }
    int NumberOfEmployees; //{ get; private set; }

    Company(std::string domainName, int numberOfEmployees)
    {
        DomainName = domainName;
        NumberOfEmployees = numberOfEmployees;
    }

    void ChangeNumberOfEmployees(int delta)
    {
        Precondition::Requires(NumberOfEmployees + delta >= 0);

        NumberOfEmployees += delta;
    }

    bool IsEmailCorporate(std::string email) const
    {
        std::string emailDomain = split_string(email, '@')[1];
        return emailDomain == DomainName;
    }
};

class User
{
public:
    int UserId; //{ get; private set; }
    std::string Email; //{ get; private set; }
    UserType Type; //{ get; private set; }
    bool IsEmailConfirmed; //{ get; private set; }

    User()
    : UserId(-1)
    , IsEmailConfirmed{}
    {}

    User(int userId, std::string email, UserType type, bool isEmailConfirmed)
        : UserId(userId)
        , Email(email)
        , Type(type)
        , IsEmailConfirmed(isEmailConfirmed)
    {
    }

    std::string CanChangeEmail() const
    {
        if (IsEmailConfirmed)
            return "Can't change email after it's confirmed";

        return std::string{};
    }

    void ChangeEmail(std::string newEmail, Company &company)
    {
        Precondition::Requires(!CanChangeEmail().empty());

        if (Email == newEmail)
            return;

        UserType newType = company.IsEmailCorporate(newEmail)
            ? UserType::Employee
            : UserType::Customer;

        if (Type != newType)
        {
            int delta = newType == UserType::Employee ? 1 : -1;
            company.ChangeNumberOfEmployees(delta);
        }

        Email = newEmail;
        Type = newType;
    }
};

class UserFactory
{
public:
    static User Create(std::string data)
    {
        return User();
    }
};

class Database
{
public:
    std::string GetUserById(int userId)
    {
        return std::string{};
    }

public:
    User GetUserByEmail(std::string email)
    {
        return User{};
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
    void SaveCompany(Company company)
    {
    }
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

class CompanyFactory
{
public:
    static Company Create(std::vector<std::string> const &data)
    {
        Precondition::Requires(data.size() >= 2);

        std::string domainName = data[0];
        int numberOfEmployees = atoi(data[1].c_str());

        return Company(domainName, numberOfEmployees);
    }
};

class UserController
{
private:
    Database _database; // = new Database();
    MessageBus _messageBus; // = new MessageBus();

public:
    std::string ChangeEmail(int userId, std::string newEmail)
    {
        std::string userData = _database.GetUserById(userId);
        User user = UserFactory::Create(userData);

        std::string error = user.CanChangeEmail();
        if (!error.empty())
            return error;

        auto companyData = _database.GetCompany();
        Company company = CompanyFactory::Create(companyData);

        user.ChangeEmail(newEmail, company);

        _database.SaveCompany(company);
        _database.SaveUser(user);
        _messageBus.SendEmailChangedMessage(userId, newEmail);

        return "OK";
    }
};

