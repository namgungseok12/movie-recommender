#pragma once
#include <string>

class BaseManager
{
public:
    // 상속 관계에서 안전한 메모리 해제를 보장하는 가상 소멸자
    virtual ~BaseManager() {}

    // 자식 클래스들이 반드시 구현해야 하는 순수 가상 함수들
    virtual void loadFromFile(const std::string &filename) = 0;
    virtual void saveToFile(const std::string &filename) const = 0;
    virtual int size() const = 0;
};