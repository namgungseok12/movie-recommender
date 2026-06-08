#include "UserManager.h"
#include <iostream>
#include <sstream>

using namespace std;

UserManager::UserManager() : nextUserId(1)
{
}

int UserManager::addUser(const string &name, const string &email)
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

const User *UserManager::findByName(const string &name) const
{
  for (const User &user : users)
  {
    if (user.getName() == name)
    {
      return &user;
    }
  }
  return nullptr;
}

const User *UserManager::findById(int id) const
{
  for (const auto &user : users)
  {
    if (user.getId() == id)
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

int UserManager::size() const
{
  return static_cast<int>(users.size());
}

void UserManager::clear()
{
  users.clear();
}

void UserManager::parseLine(const string &line)
{
  stringstream ss(line);
  string token;

  getline(ss, token, ',');
  int id = stoi(token);
  getline(ss, token, ',');
  string name = token;
  getline(ss, token, ',');
  string email = token;

  users.push_back(User(id, name, email));
}

void UserManager::onPostLoad()
{
  int maxId = 0;
  for (const auto &user : users)
  {
    if (user.getId() > maxId)
    {
      maxId = user.getId();
    }
  }
  nextUserId = maxId + 1;
}

string UserManager::getHeader() const
{
  return "id,name,email";
}

string UserManager::formatLine(int index) const
{
  const auto &u = users[index];
  return to_string(u.getId()) + "," + u.getName() + "," + u.getEmail();
}