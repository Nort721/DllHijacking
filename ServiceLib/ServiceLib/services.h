#ifndef SERVICES_H_EXPORTS
#define SERVICES_DLL_API __declspec(dllexport)
#else
#define SERVICES_DLL_API __declspec(dllexport)
#endif

#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>

extern "C" {
	SERVICES_DLL_API BOOL IsServiceRunning(const wchar_t* serviceName);
	SERVICES_DLL_API BOOL StopService(const wchar_t* serviceName);
}