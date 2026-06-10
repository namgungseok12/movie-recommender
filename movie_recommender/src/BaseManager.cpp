#include "BaseManager.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

namespace
{
    bool isBlankLine(const string &line)
    {
        return line.find_first_not_of(" \t\r\n") == string::npos;
    }
}

BaseManager::~BaseManager()
{
}

// 공통 로딩 템플릿 구현
void BaseManager::loadFromFile(const string &filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        throw runtime_error("파일을 열 수 없습니다: " + filename);
    }

    clear();

    string line;
    int lineNum = 0;

    // CSV 헤더라인 스킵
    if (getline(file, line))
    {
        lineNum++;
    }

    while (getline(file, line))
    {
        lineNum++;

        if (isBlankLine(line))
        {
            continue;
        }

        try
        {
            parseLine(line);
        }
        catch (const invalid_argument &e)
        {
            cerr << "[CSV 오류] " << filename << " " << lineNum
                 << "번 줄 건너뜀: " << e.what() << endl;
        }
        catch (const out_of_range &e)
        {
            cerr << "[CSV 오류] " << filename << " " << lineNum
                 << "번 줄 건너뜀: 숫자 범위 초과 - " << e.what() << endl;
        }
    }

    onPostLoad();
}

// 공통 저장 템플릿 구현
void BaseManager::saveToFile(const string &filename) const
{
    ofstream file(filename);

    if (!file.is_open())
    {
        throw runtime_error("파일을 저장할 수 없습니다: " + filename);
    }

    file << getHeader() << endl;

    for (int i = 0; i < size(); ++i)
    {
        file << formatLine(i) << endl;
    }

    if (!file)
    {
        throw runtime_error("파일 저장 중 오류가 발생했습니다: " + filename);
    }
}

void BaseManager::onPostLoad()
{
    // 자식에서 추가 동작이 필요 없는 경우를 대비한 가상 기본 구현
}