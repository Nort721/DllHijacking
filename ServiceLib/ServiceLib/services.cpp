#include "services.h"

SERVICES_DLL_API BOOL IsServiceRunning(const wchar_t* serviceName) {
    SC_HANDLE scManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (scManager == NULL) {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        return FALSE;
    }

    SC_HANDLE service = OpenService(scManager, serviceName, SERVICE_QUERY_STATUS);
    if (service == NULL) {
        printf("OpenService failed (%d)\n", GetLastError());
        CloseServiceHandle(scManager);
        return FALSE;
    }

    SERVICE_STATUS_PROCESS serviceStatus;
    DWORD bytesNeeded;
    if (!QueryServiceStatusEx(service, SC_STATUS_PROCESS_INFO, (LPBYTE)&serviceStatus, sizeof(SERVICE_STATUS_PROCESS), &bytesNeeded)) {
        printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
        CloseServiceHandle(service);
        CloseServiceHandle(scManager);
        return FALSE;
    }

    CloseServiceHandle(service);
    CloseServiceHandle(scManager);
    return serviceStatus.dwCurrentState == SERVICE_RUNNING;
}

SERVICES_DLL_API BOOL StopService(const wchar_t* serviceName) {
    SC_HANDLE scManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (scManager == NULL) {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        return FALSE;
    }

    SC_HANDLE service = OpenService(scManager, serviceName, SERVICE_STOP | SERVICE_QUERY_STATUS);
    if (service == NULL) {
        printf("OpenService failed (%d)\n", GetLastError());
        CloseServiceHandle(scManager);
        return FALSE;
    }

    SERVICE_STATUS serviceStatus;
    if (!ControlService(service, SERVICE_CONTROL_STOP, &serviceStatus)) {
        printf("ControlService failed (%d)\n", GetLastError());
        CloseServiceHandle(service);
        CloseServiceHandle(scManager);
        return FALSE;
    }

    CloseServiceHandle(service);
    CloseServiceHandle(scManager);
    return TRUE;
}