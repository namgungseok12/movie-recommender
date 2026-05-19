#pragma once
#include "BaseManager.h"
#include "User.h"
#include <vector>
#include <string>

// BaseManager 추상 클래스를 상속받아 사용자 데이터를 관리
class UserManager : public BaseManager
{
private:
  std::vector<User> users;
  int nextUserId;

public:
  UserManager();

  // 새로운 사용자를 추가
  int addUser(const std::string &name, const std::string &email);

  // 이름 검색 및 ID 검색
  const User *findByName(const std::string &name) const;
  const User *findById(int id) const;

  // 등록된 전체 사용자 목록 출력
  void printAll() const;

  int size() const override;

protected:
  void clear() override;
  void parseLine(const std::string &line) override;
  void onPostLoad() override;
  std::string getHeader() const override;
  std::string formatLine(int index) const override;
};