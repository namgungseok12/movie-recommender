#pragma once
#include "BaseManager.h"
#include "User.h"
#include <vector>
#include <string>

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

  int size() const override;

protected:
  void clear() override;
  void parseLine(const std::string &line) override;
  void onPostLoad() override;
  std::string getHeader() const override;
  std::string formatLine(int index) const override;
};