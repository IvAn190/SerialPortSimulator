import subprocess
from pathlib import Path
import re
import winreg

from bib.defines import *

def get_com0com_install_directory():
    """Fetches and returns the installation directory of com0com."""
    with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, 
                        R'SOFTWARE\WOW6432Node\com0com') as key:
        return Path(winreg.QueryValueEx(key, 'Install_Dir')[0])

com0com_dir = get_com0com_install_directory()

def get_ports(results):
    """Extracts the port numbers and their identifiers CNCAx and CNCBx from the given output.
    
    Args:
        results (str): The output from `setupc.exe list`.

    Returns:
        list: List of used port numbers.
    """
    # Search for all CNCAx and CNCBx port numbers
    ports = re.findall(r'CNCA(\d+)', results)
    return ports

def list_ports():
    """Lists all current ports."""
    command = [str(com0com_dir / 'setupc.exe'), 'list']
    try:
        result = subprocess.run(command, cwd=com0com_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        DEBUG_INFO("Listing all open ports:")
        print(result.stdout)
        if result.stderr:
            print("Errors:\n", result.stderr)
        return result.stdout
    except Exception as e:
        print(f"Error executing command: {e}")

def close_all_ports():
    """Closes all active com0com ports."""
    results = list_ports()
    
    if results is None:
        return
    
    # Extract the real port numbers
    port_numbers = get_ports(results)

    DEBUG_INFO("Ports detected for closing: %s", ', '.join(port_numbers))

    # Close all active ports
    for port_number in port_numbers:
        command_remove = [str(com0com_dir / 'setupc.exe'), 'remove', port_number]
        try:
            subprocess.run(command_remove, cwd=com0com_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, check=True)
            print(f"Port CNCA{port_number} and CNCB{port_number} successfully closed.")
        except subprocess.CalledProcessError as e:
            print(f"[-] Error closing ports CNCA{port_number} and CNCB{port_number}: {e.stdout} - {e.stderr}")

def open_ports(port_a='COM8', port_b='COM9'):
    """Opens two new virtual ports with the specified names."""
    command_install = [
        str(com0com_dir / 'setupc.exe'), 'install', 
        f'PortName={port_a}', f'PortName={port_b}'
    ]
    
    try:
        result = subprocess.run(command_install, cwd=com0com_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.stderr:
            print("Errors:\n", result.stderr)
            return
        
        print(f"[+] Ports {port_a} and {port_b} have been successfully opened.")
    except Exception as e:
        print(f"[-] Error opening the ports: {e}")

if __name__ == "__main__":
    print("\n")
    results = list_ports()

    # Check if COM8 and COM9 are present in the list
    if 'COM8' in results and 'COM9' in results:
        DEBUG_INFO("Ports COM8 and COM9 are already open.")
        DEBUG_OK("Ports COM8 and COM9 are ready for use.")
    else:
        DEBUG_INFO("Ports COM8 and COM9 are not open. Opening now...")
        open_ports('COM8', 'COM9')
    print("\n")