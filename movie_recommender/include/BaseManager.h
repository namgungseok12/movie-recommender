#pragma once
#include <string>


class BaseManager
{
public:
  virtual ~BaseManager();

  // 템플릿 메서드 패턴: 전체적인 파일 입출력 흐름(오픈-루프-클로즈)을 부모가 제어
  void loadFromFile(const std::string &filename);
  void saveToFile(const std::string &filename) const;

  // 현재 관리 중인 데이터의 개수를 반환
  virtual int size() const = 0;

protected:
  // 자식 클래스가 구현해야 할 하위 훅(Hook) 함수들
  virtual void clear() = 0;                            // 데이터 초기화
  virtual void parseLine(const std::string &line) = 0; // CSV 한 줄 파싱
  virtual void onPostLoad();                           // 파일 로드 후 ID 갱신
  virtual std::string getHeader() const = 0;           // CSV 파일의 맨 첫 줄 헤더 문자열 반환
  virtual std::string formatLine(int index) const = 0; // 인덱스에 해당하는 객체를 CSV 문자열 포맷으로 변환
};