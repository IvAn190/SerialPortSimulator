import sys

def DEBUG_OK(message, *args):
    """Imprime un mensaje de éxito con formato."""
    sys.stdout.write("[+]" + " " + message % args + "\n")

def DEBUG_ERROR(message, *args):
    """Imprime un mensaje de error con formato."""
    sys.stderr.write("[-]" + " " + message % args + "\n")

def DEBUG_INFO(message, *args):
    """Imprime un mensaje informativo con formato."""
    sys.stdout.write("[*]" + " " + message % args + "\n")

