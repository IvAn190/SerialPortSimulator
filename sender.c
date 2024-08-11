#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "bib/defines.h"


int main(int argc, char *argv[]) {
    int ret = EXIT_FAILURE;
    if (argc < 3) {
        DEBUG_ERROR("Needs 2 args to work! (port name & data file path)");
        goto end;
    }

    HANDLE hSerial, hFile;

    char* comPort = argv[1];
    char serialPort[20];
    sprintf(serialPort, "\\\\.\\%s", comPort);

    char* filePath = argv[2];

    /* Open serial port */
    hSerial = CreateFile(serialPort, (GENERIC_READ | GENERIC_WRITE), 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        DWORD err = GetLastError();
        DEBUG_ERROR("Error opening serial port %s. Error code: %lu\n", comPort, err);
        goto end;
    } else {
        DEBUG_OK("Serial port %s opened successfully!\n", comPort);
    }

    /* Open file */
    hFile = CreateFile(filePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);  
    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD err = GetLastError();
        DEBUG_ERROR("Error opening file %s. Error code: %lu\n", filePath, err);
        goto end;
    } else {
        DEBUG_OK("File %s opened successfully!\n", filePath);
    }

    BYTE buffer[4096];
    DWORD bytesRead, bytesWritten;

    DEBUG_INFO("Sending data ...\n");
    while (ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
        if (!WriteFile(hSerial, buffer, bytesRead, &bytesWritten, NULL)) {
            DWORD err = GetLastError();
            DEBUG_ERROR("Error writing to the serial port. Error code: %lu\n", err);
            goto end;
        } else {
            DEBUG_OK("%lu bytes written to the serial port\n", bytesWritten);
        }
    }

    ret = EXIT_SUCCESS;
end:
    if (hFile) CloseHandle(hFile);
    if (hSerial) CloseHandle(hSerial);
    return ret;
}
