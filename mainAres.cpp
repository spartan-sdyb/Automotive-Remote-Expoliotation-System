#include "HeliTrack.hpp";
#include "PigTracker";
#include "<iostream>"

bool FlyingPig() {
	std::string aircraftInfo = faAPI.getAircraftInfo("FLIGHT_ID");
	double distance = faAPI.calculateDistance(lat1, lon1, lat2, lon2);


}
int gps() {
    const char* serialPort = "/dev/ttyTHS1"; 

    SIM808_GPS gps(serialPort);

    if (!gps.initialize()) {
        std::cerr << "Failed to initialize SIM808 GPS." << std::endl;
        return 1;
    }

    if (!gps.enableGPS()) {
        std::cerr << "Failed to enable GPS." << std::endl;
        return 1;
    }

    if (!gps.resetGPS()) {
        std::cerr << "Failed to reset GPS." << std::endl;
        return 1;
    }

    if (!gps.requestGPSData()) {
        std::cerr << "Failed to request GPS data." << std::endl;
        return 1;
    }

    gps.readGPSData();

    return 0;


}






int main() {






}