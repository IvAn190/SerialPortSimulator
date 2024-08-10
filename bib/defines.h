#ifndef DEFINES_H
#define DEFINES_H

#include <stdio.h>

const char* k = "[+]";
const char* e = "[-]";
const char* i = "[*]";

// Definición de macros que aceptan múltiples argumentos
#define DEBUG_OK(...) printf("[+] " __VA_ARGS__)
#define DEBUG_ERROR(...) printf("[-] " __VA_ARGS__)
#define DEBUG_INFO(...) printf("[*] " __VA_ARGS__)

#endif // DEFINES_H
