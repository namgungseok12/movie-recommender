#pragma once
#include <string>
#include <iostream>

// 사용자 정보 보관 클래스
class User
{
private:
  int id;            // 사용자 고유 ID
  std::string name;  // 사용자 이름
  std::string email; // 사용자 이메일

public:
  User();
  User(int uId, const std::string &uName, const std::string &uEmail);

  int getId() const;
  std::string getName() const;
  std::string getEmail() const;

  void setName(const std::string &uName);
  void setEmail(const std::string &uEmail);

  // 연산자 오버로딩
  bool operator==(const User &other) const;
  bool operator!=(const User &other) const;
  friend std::ostream &operator<<(std::ostream &os, const User &user);
};