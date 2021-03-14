import serial

device = 'COM3'  # open serial port
baudrate = 9600 # or whatever you use

arduino_port = serial.Serial (device,
                              baudrate = baudrate,
                              parity   = serial.PARITY_NONE,
                              stopbits = serial.STOPBITS_ONE,
                              bytesize = serial.EIGHTBITS,
                              rtscts   = False,
                              dsrdtr   = False,
                              xonxoff  = False,
                              timeout  = 0)
def RemoveInvalidChars(s):
    s = str(s)
    newstr = ""
    a = "1234567890."
    for char in s:
        if char in a:
            newstr += char
    if(len(newstr) > 0):
        print(newstr)
    return newstr

while True:
    line = arduino_port.readline ()
    RemoveInvalidChars(line)
    #print()
    # whatever you want to do here...
