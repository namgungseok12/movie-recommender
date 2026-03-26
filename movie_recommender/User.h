#pragma once
#include <string>

using namespace std;

class User
{
private:
  int id;       // 사용자 ID
  string name;  // 이름
  string email; // 이메일

public:
  // 기본 생성자
  User();

  // 매개변수 생성자 (이메일 유효성 검사 포함)
  User(int uId, const string &uName, const string &uEmail);

  // Getter (조회용, const 필수)
  int getId() const;
  string getName() const;
  string getEmail() const;

  // Setter (이름과 이메일 수정)
  void setName(const string &uName);
  void setEmail(const string &uEmail);

  // 유효성 검사 로직
  bool isValidEmail(const string &targetEmail) const;

  // 정보 출력
  void display() const;
};