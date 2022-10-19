#include "System_Emscripten.h"


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
		string message = "alert('" + msg + "')\n";
		emscripten_run_script(message.c_str());
	}

	void System::LogToErrorFile(const string& msg)
	{
		printf("%s", msg.c_str());
	}
	
	void System::GameStart()
	{
		
	}
	
	void System::GameEnd()
	{
		
	}
}