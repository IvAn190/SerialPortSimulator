#include <windows.h>
#include <stdio.h>
#include "bib/defines.h"

int main() {
    int ret = EXIT_FAILURE;

    HANDLE hComm;
    hComm = CreateFile(TEXT("\\\\.\\COM3"),
                       GENERIC_READ | GENERIC_WRITE,
                       0,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);

    if (hComm == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        DEBUG_ERROR("Could not find resource. Error code: %lu\n", error);
        goto end;
        
    } else {
        DEBUG_INFO("Puerto COM abierto correctamente\n");
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hComm, &dcbSerialParams)) {
        printf("Error al obtener el estado del puerto\n");
        CloseHandle(hComm);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hComm, &dcbSerialParams)) {
        printf("Error al configurar el puerto COM\n");
        CloseHandle(hComm);
        return 1;
    }

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hComm, &timeouts)) {
        printf("Error al configurar los tiempos de espera\n");
        CloseHandle(hComm);
        return 1;
    }

    char szBuff[10] = "Hello";
    DWORD dwBytesWritten = 0;

    if (!WriteFile(hComm, szBuff, sizeof(szBuff), &dwBytesWritten, NULL)) {
        printf("Error al escribir en el puerto COM\n");
        CloseHandle(hComm);
        return 1;
    } else {
        printf("Datos escritos en el puerto COM\n");
    }

    char szReadBuff[10];
    DWORD dwBytesRead = 0;

    if (ReadFile(hComm, szReadBuff, sizeof(szReadBuff), &dwBytesRead, NULL)) {
        printf("Datos leídos del puerto COM: %s\n", szReadBuff);
    } else {
        printf("Error al leer del puerto COM\n");
    }

    ret = EXIT_SUCCESS;
end:
    CloseHandle(hComm);
    return ret;
}
