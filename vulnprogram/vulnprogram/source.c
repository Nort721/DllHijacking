#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

typedef BOOL (*IsServiceRunning)(const wchar_t* serviceName);
typedef BOOL (*StopService)(const wchar_t* serviceName);

int main(int argc, char** argv)
{
	HINSTANCE hmod = LoadLibraryA("ServiceLib.dll");
	if (hmod == NULL) {
		printf("Failed loading library %lu.\n", GetLastError());
		return 1;
	}

	IsServiceRunning is_service_running = (IsServiceRunning)GetProcAddress(hmod, "IsServiceRunning");
	if (is_service_running == NULL) {
		printf("IsServiceRunning address is invalid %lu.\n", GetLastError());
		FreeLibrary(hmod);
		return 1;
	}

	StopService stop_service = (StopService)GetProcAddress(hmod, "StopService");
	if (stop_service == NULL) {
		printf("StopService address is invalid %lu.\n", GetLastError());
		FreeLibrary(hmod);
		return 1;
	}

	const wchar_t* serviceName = L"XblGameSave";

	printf("StopServiceReturn: %d\n", stop_service(serviceName));
	printf("IsServiceRunningO: %d\n", is_service_running(serviceName));

	FreeLibrary(hmod);

	return 0;
}