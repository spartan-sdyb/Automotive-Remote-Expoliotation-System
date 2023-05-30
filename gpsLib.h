#ifndef SIM808_GPS_H
#define SIM808_GPS_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

class SIM808_GPS {
public:
    SIM808_GPS(const char* serialPort);
    bool initialize();
    bool enableGPS();
    bool resetGPS();
    bool requestGPSData();
    bool readGPSData();

private:
    const char* serialPort;
    int serialFD;

    bool openSerialPort();
    bool configureSerialPort();
};

#endif
