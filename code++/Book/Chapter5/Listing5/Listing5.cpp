#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

class User
{
public:
    std::string Name;

    std::string NormalizeName(std::string name)
    {
        std::string result = name; // TODO: (name ?? "").Trim();

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

        std::string normalizedName = user.NormalizeName(newName);
        user.Name = normalizedName;

        SaveUserToDatabase(user);
    }
private:
    void SaveUserToDatabase(User user)
    {
    }

    User GetUserFromDatabase(int userId)
    {
        return User();
    }
};
