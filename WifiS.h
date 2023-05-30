#ifndef WIFI_SCANNER_H
#define WIFI_SCANNER_H

#include <vector>
#include <string>

struct WiFiNetwork {
    std::string ssid;
    bool isOpen;
};

class WiFiScanner {
public:
    WiFiScanner();

    bool scanNetworks();
    std::vector<WiFiNetwork> getNetworks() const;

private:
    std::vector<WiFiNetwork> networks;
};

#endif
