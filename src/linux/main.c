#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "WCHBLElib/WCHBLElib.h"

#define BLESCAN_TIMEOUT 3
#define BLE_SUCCESS     0
#define BLE_FAILED      1

WCHBLEHANDLE *connection = NULL;

static void BleAdvertisingDeviceInfo(const char* addr, const char* name, int8_t rssi);
static void ConnectionState(WCHBLEHANDLE *connection, int state);
static void DisconnectStateCallBack(void *arg);
static void NotificationCallBack(const uuid_t* uuid, const uint8_t* data, size_t data_length);
static void versionOfDevice();
static void scanDevices();
static void connectToDevice(const char* mac_addr);
static void disconnectFromDevice();
static void discoverServices();
static void writeToDevice();

int main() {
	scanDevices();
	connectToDevice("50:54:7B:69:49:65");
	
	//versionOfDevice();
	
    //discoverServices();
    //writeToDevice();
    disconnectFromDevice();

    return 0;
}

void scanDevices() {
    printf("==> List devices:\n");
    printf("  > Only show devices with OUI: 50:54:7B\n");

    fflush(stdout);
    freopen("/dev/null", "w", stdout);
    fclose(stdout);
    int ret = WCHBle_BLE_Scan(BLESCAN_TIMEOUT, BleAdvertisingDeviceInfo);
    // fclose(fp);
    //fclose(stdout);
    fflush(stdout);

    if (ret == BLE_FAILED) {
        printf("Fail to discover primary services.\n");
        exit(1);
    }
}

void connectToDevice(const char* mac_addr) {
    printf("==> Connecting to device: %s\n", mac_addr);
    connection = WCHBle_Connect(mac_addr, ConnectionState);

    if (connection) {
        WCHBle_register_on_disconnect(connection,DisconnectStateCallBack);
        WCHBle_register_notification(connection, NotificationCallBack);
    }
}

void disconnectFromDevice() {
    if (connection) {
        WCHBle_Disconnect(connection);
    }
}

void BleAdvertisingDeviceInfo(const char *addr, const char *name, int8_t rssi) {
    char OUI[8];

    strncpy(OUI,addr,8);

    if (strcmp("50:54:7B",OUI) == 0) {
        printf("--> MAC: %s Name: %s RSSI: %d dBm\n", addr, name, rssi);
    }
}

void ConnectionState(WCHBLEHANDLE *connection, int state) {
    if (connection)
        printf("==> Connect OK!\n");
    else
        printf("==> Connect failed!\n");
}

void DisconnectStateCallBack(void *arg) {
    if (connection)
        WCHBle_Disconnect(connection);
}

void NotificationCallBack(const uuid_t *uuid, const uint8_t *data, size_t data_length){
	printf("--> ");
    for (size_t i = 0; i < data_length; i++) {
        printf("%c", data[i]);
    }
    printf("\n");
}

void versionOfDevice() {
    const char *VER_ARRAY[] = {"V1.0", "V1.1", "V1.2", "V2.0", "V2.1", "V3.0", "V4.0", "V4.1", "V4.2", "V5.0", "V5.1", "V5.2"};
    int ver = WCHBLEGetBluetoothVer();
    
    if(ver >= 0 && ver < sizeof(VER_ARRAY)/sizeof(VER_ARRAY[0]))
        printf("==> Device version: %s\n", VER_ARRAY[ver]);
    else
	    printf("==> Device code version: %d\n", ver);
}

char* format_to_char(int value) {
    char *buffer = (char *)malloc(5 * sizeof(char));

    if (buffer != NULL) {
        snprintf(buffer, 5, "%04x", value);
    }

    return buffer;
}

void discoverServices() {
    GattPrimaryService services[10] = { 0 };
    int services_count;
    char uuid_str[MAX_LEN_UUID_STR+1];
    int ret;
    ret = WCHBle_Discover_Primary(connection, services, &services_count);
    printf("==> Services: %d\n", services_count);
    
    if (services_count == 0) {
        printf("Services empty.\n");
        exit(1);
    }
    
    if (ret != BLE_SUCCESS) {
        printf("Fail to discover primary services.\n");
        exit(1);
    }

    for (int i = 0; i < services_count; i++) {
            Gatt_UUID_to_Str(&services[i].uuid, uuid_str, sizeof(uuid_str));
            char *handle = format_to_char(services[i].attr_handle_start);
            
            GattCharacteristic characteristics[200] = { 0 };
            int characteristics_count = 0;
            
            ret = WCHBle_Discover_Characteristics(connection, handle, characteristics, &characteristics_count);
     
            printf("==> Characteristics: %d -> %d\n", ret, characteristics_count);
            
            for (int y = 0; y < characteristics_count; y++) {
                    char uuid_str2[MAX_LEN_UUID_STR+1];
                    Gatt_UUID_to_Str(&characteristics[y].uuid, uuid_str2, sizeof(uuid_str2));

					ret = WCHBle_Open_Notification(connection, uuid_str2);
					if (ret != BLE_SUCCESS)
			            printf("Open notification failed.\n");
        			else
                    	printf("----> characteristic[%d] properties:0x%02x handle:0x%04x uuid:%s\n", y, characteristics[y].properties, characteristics[y].handle, uuid_str2);
            }
    }
}

void discoverCharacteristics() {
}

void writeToDevice() {
    for (int i = 0; i < 10; i++) {
        char time_str[21];
        time_t now = time(NULL);
        struct tm *local = localtime(&now);
        snprintf(time_str, sizeof(time_str), "Host time: %02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);

        size_t buf_len = sizeof(time_str);
        WCHBle_Write_Characteristic(connection, "0xfff2", true, time_str, buf_len);
    
        sleep(1);
    }
}
