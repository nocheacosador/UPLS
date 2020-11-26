import sys
from UPLS import *

device_enum = Device()
print(device_enum)

command = Command()
print(command.getCode())

battery = HookInfo.Battery()
print(battery.getVoltage())

upls = UPLS_Controller()
lst_ports = upls.listAvailablePorts()

print('Available ports:')
for port in lst_ports:
	print(port)