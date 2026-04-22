#include "User.h"
#include <iostream>

using namespace std;

User::User() : id(0), name(""), email("") {}

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
  if (isValidEmail(uEmail))
  {
    email = uEmail;
  }
  else
  {
    cout << "❌ 오류: 잘못된 이메일 형식으로 변경할 수 없습니다." << endl;
  }
}

bool User::isValidEmail(const string &targetEmail)
{
  return targetEmail.find('@') != string::npos;
}

ostream &operator<<(ostream &os, const User &user)
{
  os << "[User " << user.id << "] Name: " << user.name
     << ", Email: " << user.email;
  return os;
}