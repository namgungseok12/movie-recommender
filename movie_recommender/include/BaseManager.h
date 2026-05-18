#pragma once
#include <string>

// 모든 매니저의 공통 파일 입출력 흐름을 제어하는 추상 클래스
class BaseManager
{
public:
    virtual ~BaseManager();

    // 템플릿 메서드 패턴: 파일 로드/저장 공통 프레임워크 함수
    void loadFromFile(const std::string &filename);
    void saveToFile(const std::string &filename) const;

    virtual int size() const = 0;

protected:
    // 자식 클래스들이 구체적으로 구현해야 할 하위 훅(Hook) 함수 규격
    virtual void clear() = 0;
    virtual void parseLine(const std::string &line) = 0;
    virtual void onPostLoad();
    virtual std::string getHeader() const = 0;
    virtual std::string formatLine(int index) const = 0;
};