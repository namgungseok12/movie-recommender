#include "BaseManager.h"
#include <fstream>

BaseManager::~BaseManager()
{
}

// 공통 로딩 템플릿 구현
void BaseManager::loadFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    clear();
    std::string line;
    if (std::getline(file, line)) {} // CSV 헤더라인 스킵

    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        parseLine(line);
    }
    file.close();
    onPostLoad();
}

// 공통 저장 템플릿 구현
void BaseManager::saveToFile(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << getHeader() << std::endl;
    for (int i = 0; i < size(); ++i)
    {
        file << formatLine(i) << std::endl;
    }
    file.close();
}

void BaseManager::onPostLoad()
{
    // 자식에서 추가 동작이 필요 없는 경우를 대비한 가상 기본 구현
}