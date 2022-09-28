#include "System.h"

namespace gpr460
{
	void System::Init()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

		// make console window
		if (!AllocConsole())
		{
			ErrorMessage(L"Failed To open Console Window!");
			ExitProcess(1);
		}

		freopen("CONOUT$", "w", stdout);
	}

	void System::ShutDown()
	{
		//close ErrorFile
		if (errorFile != NULL)
			CloseHandle(errorFile);
	}

	void System::ErrorMessage(const string& msg)
	{
		MessageBox(NULL, msg.c_str(), L"Error", MB_OK | MB_ICONERROR);
	}

	void System::LogToErrorFile(const string& msg)
	{
		DWORD bytesWritten = 0;

		if (errorFile == NULL)
			errorFile = CreateFileW(L"ErrorFile.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		/*errorFile = CreateFileW(L"ErrorFile.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

		if (GetLastError() == ERROR_FILE_EXISTS)
		{
			errorFile = CreateFileW(L"ErrorFile.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		}*/

		WriteFile(errorFile, (msg + L"\n").c_str(), sizeof(gpr460::string::value_type) * (msg + L"\n").size(), &bytesWritten, NULL);
	}
}
