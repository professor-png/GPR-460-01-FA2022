#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <Windows.h>
#include <string>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

namespace gpr460
{
#ifdef _WIN32
    typedef std::wstring string;
#else
    typedef std::string string;
#endif
    

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