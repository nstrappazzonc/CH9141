
#include "ble.h"

int main() {
	scanDevices();
    listDevices();
	connectToDevice("50:54:7B:69:49:65");
	versionOfDevice();
    discoverServices();
    getActionSlot();
    // writeToDevice();
    disconnectFromDevice();

    return 0;
}
