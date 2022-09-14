#include "System.h"

namespace gpr460
{
	System::~System()
	{

	}

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

	}

	void System::ErrorMessage(const string& msg)
	{
		MessageBox(NULL, msg.c_str(), L"Error", MB_OK | MB_ICONERROR);
	}

	void System::LogToErrorFile(const string& msg)
	{

	}
}
