7.3 Slave Mode
Step1. Set the basic parameters, baud rate, working mode, etc. The chip restarts, the UART will work according to the set parameters, and the relevant setting information parameters of the device mode can be set.
Step2. Enter the AT mode to query the connection status, or directly perform the transparent transmission. When not connected, the transmitted data will be directly discarded;
Step3. Use software or the host to connect to the chip for transparent data transmission. During the transparent transmission period, AT configuration will cause that data received by BLE is directly discarded.

baud rate
working mode
restart

# Working mode, 2 slave.
AT+BLEMODE?
AT+BLEMODE=2

# MAC Address
AT+CCADD?
AT+CCADD=05:DF:39:4C:99:B1
# Chip name
AT+NAME?
AT+NAME=nicola

# Device name
AT+PNAME?
AT+PNAME=nicola

# System ID
AT+SYSID?

# chip name of device info
AT+MODNAME?
AT+MODNAME=nicola

# Serial num
AT+SERINUM?

AT+MANUNAME?
