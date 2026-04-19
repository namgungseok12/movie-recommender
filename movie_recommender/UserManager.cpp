#include "UserManager.h"

void UserManager::addUser(const User &user)
{
  users.push_back(user);
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
  for (const User &user : users)
  {
    user.display();
  }
}