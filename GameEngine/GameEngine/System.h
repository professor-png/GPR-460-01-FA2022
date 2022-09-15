#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <string>

namespace gpr460
{
    typedef std::wstring string;

    class System
    {
    private:
        HANDLE errorFile;

    public:
        ~System();

        void Init();
        void ShutDown();
        void ErrorMessage(const string& msg);
        void LogToErrorFile(const string& msg);

    };
}