//Author: Mark Lim (@peta909)
//Date: 13 Jan 2019
//License: Free for all to use

//Simple C++ Program to show how CreateProcess() is used to create and execute a process with and without arguments.
//Use of WaitForSingleObject() to used to check if the process has terminated.
//Demostrate the use of process handles.

//Kernel Debugging
//Using Kernel Debugger we could track the "life" of the EProcess struct of the child process.
//The EProcess struct of a process is only removed when all handles to the process is closed.

#include "pch.h"//Pre-compiled headers add headers in this file to speed up compilation time
#include <stdio.h> //c header for things like Printf
#include <Windows.h> //Added in order to use windows apis; could also be added to pch.h

//#include <iostream>// default header

int main()

/*
BOOL CreateProcessW(
  LPCWSTR               lpApplicationName,//Must be full path for this argument if not put NULL and use lpCommandLine
  LPWSTR                lpCommandLine,//can be used to place arguments for application
  LPSECURITY_ATTRIBUTES lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes,
  BOOL                  bInheritHandles,
  DWORD                 dwCreationFlags,
  LPVOID                lpEnvironment,
  LPCWSTR               lpCurrentDirectory,
  LPSTARTUPINFOW        lpStartupInfo,
  LPPROCESS_INFORMATION lpProcessInformation
);

DWORD WaitForSingleObject(
  HANDLE hHandle,
  DWORD  dwMilliseconds
);

*/

{
	//different unicode strings to create notepad process
	wchar_t cmd[] = L"notepad.exe";//unicode string as parameters for strings are unicode for CreateProcessW
	//wchar_t cmd[] = L"C:\\Windows\\System32\\notepad.exe";//use full path if lpApplicationName is used

	//ping locale host forever
	//wchar_t cmd[] = L"C:\\Windows\\System32\\ping.exe";
	wchar_t arg[] = L" -t 127.0.0.1";

	STARTUPINFO si = { sizeof(si) };
	//memset(&si, 0, sizeof(si));//These 2 lines are the same as the init done via C style shortcut in the line above
	//si.cb = sizeof(ci)

	PROCESS_INFORMATION pi;
	//BOOL OK = CreateProcessW(cmd, arg, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);	//This is used to execute a process with arguments
	BOOL OK = CreateProcessW(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if (OK)// check if Process is created
	{
		printf("Applicaiton is running\n");
		printf("PID = %d\n", pi.dwProcessId);

		//Wait forever till Process object is signaled (terminated)
		DWORD status = WaitForSingleObject(pi.hProcess, INFINITE);

		if (status == WAIT_OBJECT_0)//The state of the specified object is signaled.

		{
			printf("PID = %d is closed!\n", pi.dwProcessId);
		}

		CloseHandle(pi.hProcess);//Handles must be explicitly closed if not parent process will hold on to it even if child process is terminated.
		CloseHandle(pi.hThread);



	}
	else
	{
		printf("Application NOT running! \t Error code %d", GetLastError());
	}
	//Add breakpoint here to prevent console from automatically closing after debugging is finished

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
