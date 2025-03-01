#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IDatabase
{
public:
    virtual int GetNumberOfUsers() = 0;
    virtual ~IDatabase() {}
};

class IEmailGateway
{
public:
    virtual void SendGreetingsEmail(std::string userEmail) = 0;
    virtual ~IEmailGateway() {}
};

class Report
{
    int m_NumberOfUsers;
public:
    int NumberOfUsers() const { return m_NumberOfUsers; }

    Report(int numberOfUsers)
        : m_NumberOfUsers(numberOfUsers)
    {
    }
};

class Controller
{
protected:
    IEmailGateway *_emailGateway;
    IDatabase *_database;

public:
    Controller(IEmailGateway& emailGateway)
        : _emailGateway(&emailGateway)
        , _database{}
    {
    }


    Controller(IDatabase& database)
        : _emailGateway{}
        , _database(&database)
    {
    }


    void GreetUser(std::string userEmail)
    {
        _emailGateway->SendGreetingsEmail(userEmail);
    }

    Report CreateReport()
    {
        int numberOfUsers = _database->GetNumberOfUsers();
        return Report(numberOfUsers);
    }
};

// class IStoreMock : public IStore
// {
// public:
//     MOCK_METHOD(bool, HasEnoughInventory, (Product product, int quantity), (override));
//     MOCK_METHOD(void, RemoveInventory, (Product product, int quantity), (override));
//     MOCK_METHOD(void, AddInventory, (Product product, int quantity), (override));
//     MOCK_METHOD(int, GetInventory, (Product product), (override));
// };

class Mock_IEmailGateway : public IEmailGateway
{
public:
    //  virtual void SendGreetingsEmail(std::string userEmail) = 0;
    MOCK_METHOD(void, SendGreetingsEmail, (std::string userEmail), (override));
};

class ControllerTests : public testing::Test
{
};

// [Fact]
TEST_F(ControllerTests, Sending_a_greetings_email)
{
    Mock_IEmailGateway emailGatewayMock;
    Controller sut (emailGatewayMock);

    EXPECT_CALL(emailGatewayMock, SendGreetingsEmail("user@email.com"))
        .Times(1);

    sut.GreetUser("user@email.com");
};

class Mock_IDatabase : public IDatabase
{
public:
    //  virtual void SendGreetingsEmail(std::string userEmail) = 0;
    MOCK_METHOD(int, GetNumberOfUsers, (), (override));
};

// [Fact]
TEST_F(ControllerTests, Creating_a_report)
{
    using ::testing::Return;
    using ::testing::AtLeast;

    Mock_IDatabase stub;
    // stub.Setup(x = > x.GetNumberOfUsers()).Returns(10);
    EXPECT_CALL(stub, GetNumberOfUsers ())
    .Times(1).WillRepeatedly(Return(10));

    Controller sut (stub);

    Report report = sut.CreateReport();

    ASSERT_EQ(10, report.NumberOfUsers());
}


