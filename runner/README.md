# Runner - com0com Port Management Tool

This `runner` tool is a C program designed to manage virtual COM ports using the `com0com` utility on Windows. It allows the user to list currently open ports, remove specific ports, and open new ones. The tool is particularly useful in scenarios where automated port management is required for testing or development purposes.

## Features

- **Registry Access**: The program retrieves the installation directory of `com0com` directly from the Windows Registry.
- **Port Listing**: Lists all currently open virtual COM ports using the `setupc.exe list` command.
- **Port Removal**: Attempts to remove an existing port (e.g., `CNC3`) before opening new ports to avoid conflicts.
- **Port Creation**: Opens a specified pair of virtual COM ports (`COM8` and `COM9` by default).
- **User Interaction**: The program waits for the user to press any key before exiting, allowing time to review the output.

## Requirements

- **Windows OS**: The program relies on Windows-specific APIs and the `com0com` utility.
- **com0com**: Ensure `com0com` is installed and properly configured.

## How It Works

1. **Registry Query**: The program first queries the Windows Registry to find the installation directory of `com0com`.
2. **Port Management**:
   - **List Ports**: It lists all currently open ports to provide the user with an overview of the current state.
   - **Remove Ports**: The program attempts to remove the `CNC3` port using the `setupc.exe` utility.
   - **Open Ports**: It then opens a new pair of ports (`COM8` and `COM9`), ensuring they are correctly set up.
3. **User Prompt**: Before exiting, the program prompts the user to press any key, ensuring they have time to view the output.

## Usage

### Compilation

Ensure you have a C compiler installed. Compile the code using the following command:

```sh
make
```

### Execution

Run the compiled `runner.exe` with administrator privileges:

```sh
Start-Process "runner.exe" -Verb runAs
```

### Notes and Warnings
> [!WARNING]
> - **Administrator Privileges Required**: The program modifies system settings related to COM ports, so it must be run with administrator privileges. Failing to do so may result in errors or the inability to modify the ports.
> - **Registry Access**: The program reads from the Windows Registry to find the installation directory of `com0com`. Ensure that `com0com` is properly installed and configured on your system.
