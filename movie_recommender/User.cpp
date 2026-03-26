#include "User.h"
#include <iostream>
#include <string>

using namespace std;

// 기본 생성자: 초기화 리스트를 사용하여 안전하게 기본값으로 설정
User::User() : id(0), name(""), email("") {}

// 매개변수 생성자: 매개변수 이름을 uId, uName 등으로 하여 멤버 변수와 구분
User::User(int uId, const string &uName, const string &uEmail)
    : id(uId), name(uName)
{

  // 생성 시점에 이메일 유효성을 검사하여 할당
  if (isValidEmail(uEmail))
  {
    email = uEmail;
  }
  else
  {
    cout << "⚠️ 경고: [ID " << uId << "] 유효하지 않은 이메일 형식입니다." << endl;
    email = "unknown@example.com";
  }
}

// Getter 구현: 객체 내부 값을 바꾸지 않으므로 const를 유지
int User::getId() const { return id; }
string User::getName() const { return name; }
string User::getEmail() const { return email; }

// Setter 구현: 이름 수정
void User::setName(const string &uName)
{
  name = uName;
}

// Setter 구현: 이메일 수정 (유효성 검사 포함)
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

// 유효성 검사: '@' 기호가 포함되어 있는지 확인
// string::npos는 찾지 못했을 때의 반환값이므로, 그것과 같지 않아야 '찾음'을 의미함
bool User::isValidEmail(const string &targetEmail) const
{
  return targetEmail.find('@') != string::npos;
}

// 정보 출력 메서드
void User::display() const
{
  cout << "[User " << id << "] Name: " << name
       << ", Email: " << email << endl;
}