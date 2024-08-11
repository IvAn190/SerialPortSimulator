import serial
import subprocess

def start_sender():
    subprocess.Popen(['exec/sender.exe', 'COM8', 'D:/Programacion/SerialPortSimulator/README.md'])

def read_serial_port(port='COM9', baudrate=115200, timeout=1):
    try:
        start_sender()

        with serial.Serial(port, baudrate, timeout=timeout) as ser:
            print(f"Connected to port {port}")
            while True:
                data = ser.readline().decode('utf-8').strip()
                if data:
                    print(f"Received data: {data}")
    except serial.SerialException as e:
        print(f"Error connecting to port {port}: {e}")
    except KeyboardInterrupt:
        print("Reading interrupted by the user.")

if __name__ == "__main__":
    read_serial_port()
