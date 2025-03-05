//
// Book/Chapter7/DomainEvents/DomainEvents.cpp
//

#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <stdexcept>

#include "string_split.h"

enum UserType
{
    Customer = 1,
    Employee = 2
};

class Precondition
{
public:
    static void Requires(bool precondition, std::string message = "")
    {
        if (!precondition)
            throw std::runtime_error(message);
    }
};

class EmailChangedEvent
{
public:
    int UserId; //{ get; }
    std::string NewEmail; //{ get; }

    EmailChangedEvent(int userId, std::string newEmail)
        : UserId(userId)
        , NewEmail(newEmail)
    {
    }

    bool operator == (EmailChangedEvent const& other) const {
        return other.UserId == this->UserId && other.NewEmail == this->NewEmail;
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

    bool IsEmailCorporate(std::string email)
    {
        std::string emailDomain = split_string(email, '@')[1];
        return emailDomain == DomainName;
    }
};

class CompanyFactory
{
public:
    static Company Create(std::vector<std::string> const& data)
    {
        Precondition::Requires(data.size() >= 2);

        std::string domainName = (std::string)data[0];
        int numberOfEmployees = atoi(data[1].c_str());

        return Company(domainName, numberOfEmployees);
    }
};

class User {
public:
    int UserId{}; //{ get; private set; }
    std::string Email; // { get; private set; }
    UserType Type{}; // { get; private set; }
    bool IsEmailConfirmed{}; // { get; private set; }
    std::vector<EmailChangedEvent> EmailChangedEvents; // { get; private set; }

    User()
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

        return std::string();
    }

    void ChangeEmail(std::string newEmail, Company &company)
    {
        Precondition::Requires(CanChangeEmail().empty());

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
        EmailChangedEvents.push_back(EmailChangedEvent(UserId, newEmail));
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

class UserFactory
{
    public: static User Create(std::vector<std::string> const & data)
    {
        return User();
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
        std::vector<std::string> userData = _database.GetUserById(userId);
        User user = UserFactory::Create(userData);

        std::string error = user.CanChangeEmail();
        if (!error.empty())
            return error;

        std::vector<std::string> companyData = _database.GetCompany();
        Company company = CompanyFactory::Create(companyData);

        user.ChangeEmail(newEmail, company);

        _database.SaveCompany(company);
        _database.SaveUser(user);

        for (EmailChangedEvent &ev : user.EmailChangedEvents)
        {
            _messageBus.SendEmailChangedMessage(ev.UserId, ev.NewEmail);
        }

        return "OK";
    }
};

class Tests : public testing::Test
{
};

// [Fact]
TEST_F(Tests, Changing_email_from_corporate_to_non_corporate)
{
    auto company = Company("mycorp.com", 1);
    auto sut = User(1, "user@mycorp.com", UserType::Employee, false);

    sut.ChangeEmail("new@gmail.com", company);

    ASSERT_EQ(0, company.NumberOfEmployees);

    ASSERT_STREQ("new@gmail.com", sut.Email.c_str());
    ASSERT_EQ(UserType::Customer, sut.Type);
    // sut.EmailChangedEvents.Should().Equal(
    //     new EmailChangedEvent(1, "new@gmail.com"));
};


