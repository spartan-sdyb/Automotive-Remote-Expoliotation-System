#include "SIM808_GPS.h"

SIM808_GPS::SIM808_GPS(const char* serialPort) : serialPort(serialPort) {
    serialFD = -1;
}

bool SIM808_GPS::openSerialPort() {
    serialFD = open(serialPort, O_RDWR | O_NOCTTY | O_NDELAY);
    return (serialFD != -1);
}

bool SIM808_GPS::configureSerialPort() {
    struct termios tty;
    tcgetattr(serialFD, &tty);

    tty.c_cflag = B9600;
    tty.c_cflag |= CS8;
    tty.c_cflag |= CLOCAL;
    tty.c_cflag |= CREAD;

    return (tcsetattr(serialFD, TCSANOW, &tty) != -1);
}

bool SIM808_GPS::initialize() {
    if (!openSerialPort()) {
        std::cerr << "Failed to open serial port." << std::endl;
        return false;
    }

    if (!configureSerialPort()) {
        std::cerr << "Failed to configure serial port." << std::endl;
        return false;
    }

    const char* atCommands[] = {
        "AT\r\n", // Check module response
        "AT+CGPSPWR=1\r\n", // Enable GPS
        "AT+CGPSRST=0\r\n", // Reset GPS
        "AT+CGPSINF=32\r\n" // Request GPS information
    };

    for (const char* cmd : atCommands) {
        write(serialFD, cmd, strlen(cmd));
        usleep(1000000); // Wait for module response
    }

    return true;
}

bool SIM808_GPS::enableGPS() {
    const char* cmd = "AT+CGPSPWR=1\r\n";
    write(serialFD, cmd, strlen(cmd));
    usleep(1000000); // Wait for module response

    // Check if GPS is enabled
    // ...

    return true;
}

bool SIM808_GPS::resetGPS() {
    const char* cmd = "AT+CGPSRST=0\r\n";
    write(serialFD, cmd, strlen(cmd));
    usleep(1000000); // Wait for module response

    // Check if GPS is reset
    // ...

    return true;
}

bool SIM808_GPS::requestGPSData() {
    const char* cmd = "AT+CGPSINF=32\r\n";
    write(serialFD, cmd, strlen(cmd));
    usleep(1000000); // Wait for module response

    // Check if GPS data is requested
    // ...

    return true;
}

bool SIM808_GPS::readGPSData() {
    char buffer[256];
    ssize_t bytesRead;

    while (true) {
        bytesRead = read(serialFD, buffer, sizeof(buffer));

        if (bytesRead > 0) {
            for (int i = 0; i < bytesRead; ++i) {
                std::cout << buffer[i];
            }
        }
    }

    return true;
}
