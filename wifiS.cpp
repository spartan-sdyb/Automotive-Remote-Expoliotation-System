#include "WiFiScanner.h"
#include <iwlib.h>

WiFiScanner::WiFiScanner() {}

bool WiFiScanner::scanNetworks() {
    networks.clear();

    // Open a socket for wireless interface
    int socketFD = iw_sockets_open();
    if (socketFD < 0) {
        return false;
    }

    // Get wireless interface name
    char ifName[IFNAMSIZ];
    if (iw_get_kernel_we_version(socketFD, ifName) < 0) {
        iw_sockets_close(socketFD);
        return false;
    }

    // Scan for wireless networks
    iwrange range;
    iw_scan_init(socketFD, ifName, &range);
    char buffer[4096];
    iw_scan(socketFD, ifName, range.we_version_compiled, buffer);

    // Process the scan results
    iw_event event;
    char* currentBuffer = buffer;
    while (1) {
        currentBuffer += iw_process_event(currentBuffer, &event, range.we_version_compiled);
        if (event.cmd != SIOCGIWAP) {
            break;
        }

        WiFiNetwork network;
        network.ssid = event.u.ap_addr.sa_data;
        network.isOpen = (event.u.ap_flags & IW_ENCODE_DISABLED) != 0;
        networks.push_back(network);
    }

    // Close the socket
    iw_sockets_close(socketFD);

    return true;
}

std::vector<WiFiNetwork> WiFiScanner::getNetworks() const {
    return networks;
}
