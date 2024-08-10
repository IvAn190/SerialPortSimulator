#include <windows.h>
#include "bib/defines.h"

#define SERIAL "\\\\.\\COM3"

int main(int argc, char *argv) {
    int ret = EXIT_FAILURE;

    HANDLE hSerial;
    hSerial =  CreateFile(SERIAL, (GENERIC_READ | GENERIC_WRITE), 0, NULL, OPEN_EXISTING, 0, NULL);
    

    /* Open the serial port */
    if (hSerial == NULL || hSerial == INVALID_HANDLE_VALUE) {
        DWORD err = GetLastError();
        DEBUG_ERROR("Error opening Serial port. Error: %lu\n", err);
        goto end;
    } else {
        DEBUG_INFO("Serial port open!\n");
    }


    ret = EXIT_SUCCESS;
end:
    CloseHandle(hSerial);
    return ret;
}