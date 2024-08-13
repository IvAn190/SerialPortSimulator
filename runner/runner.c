#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include <winreg.h>

#include "../bib/defines.h"

// Run as admin: Start-Process "runner.exe" -Verb runAs

/* Function to get com0com installation directory from the Windows Registry */
char* get_com0com_install_directory() {
    HKEY hKey;
    static char installDir[MAX_PATH];
    DWORD bufLen = MAX_PATH;
    
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
                     "SOFTWARE\\WOW6432Node\\com0com", 
                     0, 
                     KEY_QUERY_VALUE, 
                     &hKey) == ERROR_SUCCESS) {
        RegQueryValueEx(hKey, "Install_Dir", NULL, NULL, (LPBYTE)installDir, &bufLen);
        RegCloseKey(hKey);
        return installDir;
    } else {
        DEBUG_ERROR("Could not open registry key for com0com.\n");
        return NULL;
    }
}

/* Function to execute a command and capture the output */
int exec_command(char* cmd, char* output, int output_size) {
    if (cmd == NULL || output == NULL) {
        DEBUG_ERROR("NULL pointers! \n");
        return EXIT_FAILURE;
    }
    
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) return -1;
    fgets(output, output_size, pipe);
    _pclose(pipe);

    return EXIT_SUCCESS;
}

/* Function to list all the open ports */
void list_ports(char* install_dir) {
    char command[512];
    int exit;

    DEBUG_INFO("Ports list:\n");
    snprintf(command, sizeof(command), "\"%s\\setupc.exe\" list", install_dir);

    exit = system(command);
    if (exit != 0) {
        DEBUG_ERROR("Error listing ports. Error code: %u", exit);
    }
}

// Function to check if ports COM8 and COM9 are open
int check_ports_open(char* result) {
    return (strstr(result, "COM8") != NULL && strstr(result, "COM9") != NULL);
}

/* Function to open ports COM8 and COM9 */
void open_ports(char* install_dir, char* port_a, char* port_b) {
    char command[512];
    SetCurrentDirectory(install_dir);

    DEBUG_INFO("Removing CNC3 ports.");
    snprintf(command, sizeof(command), "\"%s\\setupc.exe\" --silent remove 3", install_dir);
    if (system(command) == 0) {
        DEBUG_OK("CNC3 removed correctly.\n");
    } else {
        DEBUG_INFO("CNC3 not removed. Maybe not opened yet.\n");
    }
    
    snprintf(command, sizeof(command), "\"%s\\setupc.exe\" install 3 PortName=%s PortName=%s", install_dir, port_a, port_b);    
    if (system(command) == 0) {
        DEBUG_OK("Ports %s and %s have been successfully opened.\n", port_a, port_b);
        list_ports(install_dir);
    } else {
        DEBUG_ERROR("Error opening the ports.\n");
        return;
    }
}

int main(void) {
    int ret = EXIT_FAILURE;

    char* install_dir = get_com0com_install_directory();
    if (!install_dir) {
        DEBUG_ERROR("Failed to retrieve com0com installation directory.\n");
        goto end;
    }

    list_ports(install_dir);
    open_ports(install_dir, "COM8", "COM9");
    
    printf("\nPress any key to continue...\n");
    getchar();

    ret = EXIT_SUCCESS;
end:
    return ret;
}
