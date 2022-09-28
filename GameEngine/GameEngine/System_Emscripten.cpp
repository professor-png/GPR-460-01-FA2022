#include "System_Emscripten.h"

#ifdef __EMSCRIPTION__
namespace gpr460
{
	void System::Init()
	{

	}
	void System::ShutDown()
	{
		//close ErrorFile
		//CloseHandle(errorFile);
	}

	void System::ErrorMessage(const string& msg)
	{
		alert("Alert!");
	}

	void System::LogToErrorFile(const string& msg)
	{
		printf(msg);
	}
}
#endif