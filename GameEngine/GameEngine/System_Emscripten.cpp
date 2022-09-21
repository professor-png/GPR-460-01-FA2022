#include "System_Emscripten.h"

namespace gpr460
{
	void System::ShutDown()
	{
		//close ErrorFile
		CloseHandle(errorFile);
	}

	void System::ErrorMessage(const string& msg)
	{
		//MessageBox(NULL, msg.c_str(), L"Error", MB_OK | MB_ICONERROR);

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