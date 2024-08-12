# Serial Port Simulator

## Overview

A tool to send data with a COM port. Using com0com library.

## Requirements

- com0com library ([link](https://sourceforge.net/projects/com0com/)). 

## Compile

Compile the script using this command:
```bash
gcc .\sender.c -o sender
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

The ```runner.py``` opens the ports COM8 & COM9 for a correct use. User must install com0com first. This tool aims to be implemented in the [uNavTools](https://github.com/IvAn190/uNavTools) repo. 

> [!NOTE]
> Nevermind where the com0com library is installed because there is a script that finds the correct path to execute the program properly. 