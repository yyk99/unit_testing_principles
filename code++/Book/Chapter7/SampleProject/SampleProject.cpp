#include "gtest/gtest.h"

#include <vector>
#include <string>
#include <stdexcept>

#include "string_split.h"

enum UserType
{
    Customer = 1,
    Employee = 2
};

class User;
class Database
{
public:
    static std::vector<std::string> GetUserById(int userId)
    {
        return {};
    }

public:
    static User GetUserByEmail(std::string email);

public:
    static void SaveUser(User& user)
    {
    }

public:
    static std::vector<std::string> GetCompany()
    {
        return {};
    }

public:
    static void SaveCompany(int newNumber)
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
    static IBus& _bus;

public:
    static void SendEmailChangedMessage(int userId, std::string newEmail)
    {
        _bus.Send("Subject: USER; Type: EMAIL CHANGED; Id: {userId}; NewEmail: {newEmail}");
    }
};


class User
{
public:
    int UserId; //{ get; private set; }
public:
    std::string Email; //{ get; private set; }
public:
    UserType Type; //{ get; private set; }

public:
    void ChangeEmail(int userId, std::string newEmail)
    {
        std::vector<std::string> data = Database::GetUserById(userId);
        UserId = userId;
        Email = (std::string)data[1];
        Type = (UserType)(atoi(data[2].c_str()));

        if (Email == newEmail)
            return;

        //bool isEmailTaken = Database.GetUserByEmail(newEmail) != null;
        //if (isEmailTaken)
        //    return "Email is taken";

        std::vector<std::string> companyData = Database::GetCompany();
        std::string companyDomainName = companyData[0];
        int numberOfEmployees = atoi(companyData[1].c_str());

        std::string emailDomain = split_string(newEmail, '@')[1];
        bool isEmailCorporate = emailDomain == companyDomainName;
        UserType newType = isEmailCorporate
            ? UserType::Employee
            : UserType::Customer;

        if (Type != newType)
        {
            int delta = newType == UserType::Employee ? 1 : -1;
            int newNumber = numberOfEmployees + delta;
            Database::SaveCompany(newNumber);
        }

        Email = newEmail;
        Type = newType;

        Database::SaveUser(*this);
        MessageBus::SendEmailChangedMessage(UserId, newEmail);
    }
};

User Database::GetUserByEmail(std::string email)
{
    return {};
}