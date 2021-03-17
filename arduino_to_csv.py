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
    return newstr

while True:
    line = arduino_port.readline()
    strval = RemoveInvalidChars(line)
    # IF WE GET NUMBER 
    if(len(strval) > 0):
        val = float(strval)
        print(val)
