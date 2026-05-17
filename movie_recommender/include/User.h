#pragma once
#include <string>
#include <iostream>

class User
{
private:
  int id;
  std::string name;
  std::string email;

public:
  User();
  User(int uId, const std::string &uName, const std::string &uEmail);

  int getId() const;
  std::string getName() const;
  std::string getEmail() const;

  void setName(const std::string &uName);
  void setEmail(const std::string &uEmail);

  static bool isValidEmail(const std::string &targetEmail);

  bool operator==(const User &other) const;
  bool operator!=(const User &other) const;

  friend std::ostream &operator<<(std::ostream &os, const User &user);
};