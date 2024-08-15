# Serial Port Simulator

## Overview

A tool to send data with a COM port. Using com0com library.

## Requirements

- com0com library ([link](https://sourceforge.net/projects/com0com/)). 

## Compile

Compile the script using this command:
```bash
make
```

## How does it works ? 

```bash
.\sender.exe COMx path/to/file
```

Where the user must input two parameters:
1. COM port.
2. Path to the input file.

### Example
```bash
.\sender.exe COM8 D:/Programacion/SerialPortSimulator/data.ubx
```

> [!WARNING] 
> Before starting, we need to start com0com application and configure both ports, receiver and sender. Due to Windows permissions, we cannot use one port with multiple programs/applications. Because of that, we must configure two ports in the com0com application (sender & receiver). 

## Test

To test out that all is working correctly, run the receiver.py file, changing (inside the file, manually), the port and path file. 

## Runner

The `runner.py` script is designed to manage and interact with virtual serial ports created using the `com0com` utility on Windows. Its primary purpose is to check the status of specific COM ports (in this case, `COM8` and `COM9`), ensure they are available, and if they are not, to open them. This script also requires administrator privileges to execute certain commands, such as modifying the virtual serial ports.

### What It Does:
- **Administrator Check**: The script begins by checking if it is running with administrator privileges. If not, it prompts the user to rerun the script with elevated permissions.
- **Installation Directory Retrieval**: It locates the installation directory of `com0com` using the Windows Registry.
- **Port Management**: The script lists the current virtual serial ports, checks if `COM8` and `COM9` are already open, and opens them if they are not.
- **Debug Information**: Throughout the process, the script provides detailed debug information, such as the status of the ports and any actions taken.

> [!WARNING]
> - **Administrator Privileges**: The script requires administrator privileges to modify virtual serial ports. Ensure that the script is run with the necessary permissions, or it will prompt you to restart with elevated rights.
> - **System-Specific**: This script is specifically designed for Windows systems with `com0com` installed. It will not function on Unix-based systems or without `com0com`.

> [!NOTE]
> - **Error Handling**: The script includes basic error handling to manage potential issues during the execution of commands. However, users should verify the output and logs to ensure that all operations complete successfully.
> - **Customization**: The script currently focuses on `COM8` and `COM9`. If different ports are needed, the script can be easily modified to check and manage other COM ports.

This script is a helpful tool for automating the setup and management of virtual serial ports, especially in environments where these ports are frequently used and need to be consistently available.
