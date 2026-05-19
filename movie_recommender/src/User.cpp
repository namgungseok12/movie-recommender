#include "User.h"
#include <iostream>

using namespace std;

// 기본 생성자
User::User() : id(0), name(""), email("")
{
}

// 매개변수 생성자
User::User(int uId, const string &uName, const string &uEmail)
    : id(uId), name(uName), email(uEmail)
{
}

int User::getId() const
{
  return id;
}

string User::getName() const
{
  return name;
}

string User::getEmail() const
{
  return email;
}

void User::setName(const string &uName)
{
  name = uName;
}

void User::setEmail(const string &uEmail)
{
  email = uEmail;
}

bool User::operator==(const User &other) const
{
  return this->id == other.id;
}

bool User::operator!=(const User &other) const
{
  return !(*this == other);
}

ostream &operator<<(ostream &os, const User &user)
{
  os << "사용자 ID: " << user.id << " | 이름: " << user.name << " | 이메일: " << user.email;
  return os;
}