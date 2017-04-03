import serial

serial = serial.Serial("/dev/tty.Repleo-CH341-000013FA")
serial.baudrate = 115200

print("Opening serial connection on:\n\t" + serial.name)
print("\tbaudrate: " + str(serial.baudrate))

#serial.write(b"G28\n")
serial.write(b"G0 X2 Y2\n")
