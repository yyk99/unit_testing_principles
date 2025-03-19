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

class Precondition
{
public:
    static void Requires(bool precondition, std::string message = std::string())
    {
        if (!precondition)
            throw std::runtime_error(message);
    }
};

class Company
{
public:
    std::string DomainName; //{ get; private set; }
    int NumberOfEmployees; //{ get; private set; }

public:
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

        std::string domainName = data[0];
        int numberOfEmployees = atoi(data[1].c_str());

        return Company(domainName, numberOfEmployees);
    }
};


class User
{
public:
    int UserId; //{ get; private set; }
    std::string Email; //{ get; private set; }
    UserType Type; //{ get; private set; }

public:
    User() 
        : UserId{}
    {
    }

    User(int userId, std::string email, UserType type)
    {
        UserId = userId;
        Email = email;
        Type = type;
    }

    void ChangeEmail(std::string newEmail, Company& company)
    {
        if (Email == newEmail)
            return;

        UserType newType = company.IsEmailCorporate(newEmail)
            ? Employee
            : Customer;

        if (Type != newType)
        {
            int delta = newType == Employee ? 1 : -1;
            company.ChangeNumberOfEmployees(delta);
        }

        Email = newEmail;
        Type = newType;
    }
};

class UserFactory
{
public:
    static User Create(std::vector<std::string> const& data)
    {
        Precondition::Requires(data.size() >= 3);

        int id = atoi(data[0].c_str());
        std::string email = data[1];
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
    };


    User GetUserByEmail(std::string email)
    {
        return {};
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
    IBus* _bus;

public:
    void SendEmailChangedMessage(int userId, std::string newEmail)
    {
        _bus->Send("Subject: USER; Type: EMAIL CHANGED; Id: {userId}; NewEmail: {newEmail}");
    }
};


class UserController
{
private:
    Database _database; // = new Database();
    MessageBus _messageBus; // = new MessageBus();

public:
    void ChangeEmail(int userId, std::string newEmail)
    {
        auto userData = _database.GetUserById(userId);
        User user = UserFactory::Create(userData);

        auto companyData = _database.GetCompany();
        Company company = CompanyFactory::Create(companyData);

        user.ChangeEmail(newEmail, company);

        _database.SaveCompany(company);
        _database.SaveUser(user);
        _messageBus.SendEmailChangedMessage(userId, newEmail);
    }
};

class Tests : public testing::Test
{
};

//[Fact]
TEST_F(Tests, Changing_email_without_changing_user_type)
{
    auto company = Company("mycorp.com", 1);
    auto sut = User(1, "user@mycorp.com", UserType::Employee);

    sut.ChangeEmail("new@mycorp.com", company);

    ASSERT_EQ(1, company.NumberOfEmployees);
    ASSERT_EQ("new@mycorp.com", sut.Email);
    ASSERT_EQ(UserType::Employee, sut.Type);
};

//[Fact]
TEST_F(Tests, Changing_email_from_corporate_to_non_corporate)
{
    auto company = Company("mycorp.com", 1);
    auto sut = User(1, "user@mycorp.com", UserType::Employee);

    sut.ChangeEmail("new@gmail.com", company);

    ASSERT_EQ(0, company.NumberOfEmployees);
    ASSERT_EQ("new@gmail.com", sut.Email);
    ASSERT_EQ(UserType::Customer, sut.Type);
}

//[Fact]
TEST_F(Tests, Changing_email_from_non_corporate_to_corporate)
{
    auto company = Company("mycorp.com", 1);
    auto sut = User(1, "user@gmail.com", UserType::Customer);

    sut.ChangeEmail("new@mycorp.com", company);

    ASSERT_EQ(2, company.NumberOfEmployees);
    ASSERT_EQ("new@mycorp.com", sut.Email);
    ASSERT_EQ(UserType::Employee, sut.Type);
}

//[Fact]
TEST_F(Tests, Changing_email_to_the_same_one)
{
    auto company = Company("mycorp.com", 1);
    auto sut = User(1, "user@gmail.com", UserType::Customer);

    sut.ChangeEmail("user@gmail.com", company);

    ASSERT_EQ(1, company.NumberOfEmployees);
    ASSERT_EQ("user@gmail.com", sut.Email);
    ASSERT_EQ(Customer, sut.Type);
}

// [InlineData("mycorp.com", "email@mycorp.com", true)]
// [InlineData("mycorp.com", "email@gmail.com", false)]
// [Theory]
// TEST_F(Tests, Differentiates_a_corporate_email_from_non_corporate(
//     std::string domain, std::string email, bool expectedResult)
// {
//     var sut = new Company(domain, 0);

//     bool isEmailCorporate = sut.IsEmailCorporate(email);

//     ASSERT_EQ(expectedResult, isEmailCorporate);
// };
