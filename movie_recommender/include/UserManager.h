#pragma once
#include <vector>
#include <string>
#include "BaseManager.h"
#include "User.h"

class UserManager : public BaseManager
{
private:
  std::vector<User> users;
  int nextUserId;

public:
  UserManager();

  int addUser(const std::string &name, const std::string &email);
  const User *findByName(const std::string &name) const;
  const User *findById(int id) const; 
  void printAll() const;

  // BaseManager 인터페이스 구현 
  void loadFromFile(const std::string &filename) override;
  void saveToFile(const std::string &filename) const override;
  int size() const override;
};