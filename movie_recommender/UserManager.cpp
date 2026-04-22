#include "UserManager.h"
#include <iostream>

using namespace std;

UserManager::UserManager() : nextUserId(1)
{
}

int UserManager::addUser(const std::string &name, const std::string &email)
{
    User user(nextUserId, name, email);
    users.push_back(user);

    int createdId = nextUserId;
    nextUserId++;
    return createdId;
}

User *UserManager::findByName(const std::string &name)
{
    for (User &user : users)
    {
        if (user.getName() == name)
        {
            return &user;
        }
    }

    return nullptr;
}

void UserManager::printAll() const
{
    if (users.empty())
    {
        cout << "등록된 사용자가 없습니다." << endl;
        return;
    }

    for (const User &user : users)
    {
        cout << user << endl;
    }
}