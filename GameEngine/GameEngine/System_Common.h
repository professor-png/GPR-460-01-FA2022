#pragma once

#include <string>

//include windows for error file handle
#ifdef _WIN32
#include <Windows.h>
#endif


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
    const gpr460::string K_MESSAGE = L"Do not press K!!!";
    const gpr460::string K_ERROR = L"Error: User pressed k";
#else
    typedef std::string string;
    const gpr460::string K_MESSAGE = "Do not press K!!!";
    const gpr460::string K_ERROR = "Error: User pressed k";
#endif
    

    class System
    {
    private:
#ifdef _WIN32
        HANDLE errorFile = NULL;
#endif

    public:
        void Init();
        void ShutDown();
        void ErrorMessage(const string& msg);
        void LogToErrorFile(const string& msg);

    };
}