#pragma once
#include <vector>
#include <string>
#include "User.h"

class UserManager
{
private:
  std::vector<User> users;
  int nextUserId;

public:
  UserManager();

  int addUser(const std::string &name, const std::string &email);
  User *findByName(const std::string &name);
  void printAll() const;
};