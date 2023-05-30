#include "WiFiScanner.h"
#include <iostream>

int main() {
    WiFiScanner wifiScanner;

    if (wifiScanner.scanNetworks()) {
        std::vector<WiFiNetwork> networks = wifiScanner.getNetworks();

        for (const auto& network : networks) {
            std::cout << "SSID: " << network.ssid << std::endl;
            std::cout << "Open: " << (network.isOpen ? "Yes" : "No") << std::endl;
            std::cout << std::endl;
        }
    }
    else {
        std::cerr << "Failed to scan Wi-Fi networks." << std::endl;
        return 1;
    }

    return 0;
}
