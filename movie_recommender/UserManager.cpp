#include "UserManager.h"
#include <iostream>

using namespace std;

UserManager::UserManager() : nextUserId(1)
{
}

int UserManager::addUser(const std::string &name, const std::string &email)
{
  if (findByName(name) != nullptr)
  {
    cout << "이미 같은 이름의 사용자가 존재합니다. 사용자가 추가되지 않았습니다." << endl;
    return -1;
  }

  User user(nextUserId, name, email);
  users.push_back(user);

  int createdId = nextUserId;
  nextUserId++;
  return createdId;
}

const User *UserManager::findByName(const std::string &name) const
{
  User target(0, name, "");

  // 내부에서 읽기만 하므로 const User &로 순회
  for (const User &user : users)
  {
    if (user == target)
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