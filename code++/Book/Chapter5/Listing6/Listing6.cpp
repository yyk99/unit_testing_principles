#include "gtest/gtest.h"

#include "string_trim.h"

class User
{
private:
    std::string _name;
    
public:
    std::string Name() const { return _name; }

    void Name(std::string const& value) {
        _name = NormalizeName(value);
    }

private:
    std::string NormalizeName(std::string const& name)
    {
        std::string result = trim_copy(name);

        if (result.size() > 50)
            return result.substr(0, 50);

        return result;
    }
};

class UserController
{
public:
    void RenameUser(int userId, std::string newName)
    {
        User user = GetUserFromDatabase(userId);
        user.Name(newName);
        SaveUserToDatabase(user);
    }

private:
    void SaveUserToDatabase(User user)
    {
    }

private:
    User GetUserFromDatabase(int userId)
    {
        return User{};
    }
};
