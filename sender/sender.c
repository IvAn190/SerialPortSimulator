#include <windows.h>
#include <stdlib.h>
#include "../bib/defines.h"

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
    hSerial = CreateFile(serialPort, (GENERIC_READ | GENERIC_WRITE), 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
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
    OVERLAPPED overlapped = {0};
    DWORD bytesRead, bytesWritten;
    BOOL result;

    const DWORD TIMEOUT_MS = 10000; 
    DWORD startTime = GetTickCount();

    DEBUG_INFO("Sending data ...\n");
    while (ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
        result = WriteFile(hSerial, buffer, bytesRead, &bytesWritten, &overlapped);
        if (!result) {
            DWORD err = GetLastError();
            if (err == ERROR_IO_PENDING) {
                DWORD waitResult = WaitForSingleObject(hSerial, TIMEOUT_MS);
                if (waitResult == WAIT_OBJECT_0) {
                    if (!GetOverlappedResult(hSerial, &overlapped, &bytesWritten, TRUE)) {
                        DWORD waitError = GetLastError();
                        DEBUG_ERROR("Error waiting for the overlapped result. Error code: %lu\n", waitError);
                        goto end;   
                    }
                    startTime = GetTickCount(); 
                } else if (waitResult == WAIT_TIMEOUT) {
                    DEBUG_ERROR("Timeout: No data sent in 10 seconds\n");
                    goto end;
                } else {
                    DWORD waitError = GetLastError();
                    DEBUG_ERROR("Error waiting for the write completion. Error code: %lu\n", waitError);
                    goto end;
                }
            } else {
                DEBUG_ERROR("Error writing to the serial port. Error code: %lu\n", err);
                goto end;
            }
        } else {
            startTime = GetTickCount();
        }

        if (GetTickCount() - startTime >= TIMEOUT_MS) {
            DEBUG_ERROR("Timeout: No data sent in 10 seconds\n");
            goto end;
        }
    }
    DEBUG_OK("All data has been sent!\n");
    ret = EXIT_SUCCESS;

end:
    if (hFile) CloseHandle(hFile);
    if (hSerial) CloseHandle(hSerial);
    return ret;
}
