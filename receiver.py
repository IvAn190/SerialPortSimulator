import serial

def leer_puerto_serial(puerto='COM9', baudrate=9600, timeout=1):
    try:
        # Abrir el puerto serial
        with serial.Serial(puerto, baudrate, timeout=timeout) as ser:
            print(f"Conectado al puerto {puerto}")
            while True:
                # Leer datos del puerto
                datos = ser.readline().decode('utf-8').strip()
                if datos:
                    print(f"Datos recibidos: {datos}")
    except serial.SerialException as e:
        print(f"Error al conectar con el puerto {puerto}: {e}")
    except KeyboardInterrupt:
        print("Lectura interrumpida por el usuario.")

if __name__ == "__main__":
    leer_puerto_serial()
