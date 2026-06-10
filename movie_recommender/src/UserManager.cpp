#include "UserManager.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace
{
  string trim(const string &str)
  {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == string::npos)
    {
      return "";
    }

    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
  }

  int parseIntStrict(const string &value, const string &fieldName)
  {
    string trimmed = trim(value);

    if (trimmed.empty())
    {
      throw invalid_argument(fieldName + " 값이 비어 있습니다.");
    }

    size_t pos = 0;
    int result = 0;

    try
    {
      result = stoi(trimmed, &pos);
    }
    catch (const exception &)
    {
      throw invalid_argument(fieldName + " 값은 정수여야 합니다.");
    }

    if (pos != trimmed.size())
    {
      throw invalid_argument(fieldName + " 값에 숫자가 아닌 문자가 포함되어 있습니다.");
    }

    return result;
  }
}

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
  string idToken, name, email, extra;

  if (!getline(ss, idToken, ',') ||
      !getline(ss, name, ',') ||
      !getline(ss, email, ','))
  {
    throw invalid_argument("사용자 CSV 컬럼 수가 부족합니다.");
  }

  if (getline(ss, extra, ','))
  {
    throw invalid_argument("사용자 CSV 컬럼 수가 너무 많습니다.");
  }

  int id = parseIntStrict(idToken, "사용자 ID");

  name = trim(name);
  email = trim(email);

  if (id <= 0)
  {
    throw invalid_argument("사용자 ID는 1 이상이어야 합니다.");
  }

  if (name.empty())
  {
    throw invalid_argument("사용자 이름이 비어 있습니다.");
  }

  if (email.empty())
  {
    throw invalid_argument("이메일이 비어 있습니다.");
  }

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