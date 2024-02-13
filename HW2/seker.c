#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

void sendCommandToArduino(char command);
char receiveDataFromArduino();

int main() {
    char choice;
    char buffer[100];

    printf("## WELCOME TO GTU ARDUINO LAB ##\n\n");
    printf("## STUDENT NAME: Yunus Seker ##\n\n");

    while (1) {
        printf("## MENU : ##\n\n");
        printf("(1) TURN ON LED ON ARDUINO\n");
        printf("(2) TURN OFF LED ON ARDUINO\n");
        printf("(3) FLASH ARDUINO LED 5 TIMES\n");
        printf("(4) SEND A NUMBER TO ARDUINO TO COMPUTE FACTORIAL BY ARDUINO\n");
        printf("(5) Button press counter\n");
        printf("(6) Turn on external led\n");
        printf("(0) EXIT\n\n");
        printf("PLEASE SELECT: ");

        scanf(" %c", &choice);

        switch (choice) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
                sendCommandToArduino(choice);
                break;
            case '0':
                exit(0);
            default:
                printf("Invalid selection. Please try again.\n");
        }

        // Clear input buffer
        while (getchar() != '\n');

        printf("\nPress any key to continue...");
        getch();
        system("cls");
    }

    return 0;
}

void sendCommandToArduino(char command) {
    HANDLE hSerial;
    DCB dcbSerialParams = { 0 };
    COMMTIMEOUTS timeouts = { 0 };

    hSerial = CreateFile("COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error opening serial port\n");
        exit(1);
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Error getting serial port state\n");
        CloseHandle(hSerial);
        exit(1);
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Error setting serial port state\n");
        CloseHandle(hSerial);
        exit(1);
    }

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        fprintf(stderr, "Error setting timeouts\n");
        CloseHandle(hSerial);
        exit(1);
    }

    char commandString[2] = { command, '\0' };

    DWORD bytes_written, total_bytes_written = 0;
    if (!WriteFile(hSerial, commandString, strlen(commandString), &bytes_written, NULL)) {
        fprintf(stderr, "Error writing to serial port\n");
        CloseHandle(hSerial);
        exit(1);
    }

    CloseHandle(hSerial);
}
