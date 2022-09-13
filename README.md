# Arduino-device
utilize the lcd 1602 for display, dht11 for the temperature and humidity sensor, a precise clock module DS3231 for time display and precise timing, a touch pad and a rotational rod for the handy control of the device

the main microprocessor is the **arduino mega board**

the hardware connection:

1.the liquid crystal display 1602, use the SPI interface protocol
 A  PWM2
 K  GND      the back light are connected so that it can blink ^_^
 rs  dig23
 en  dig27
 d4  dig31
 d5  dig35
 d6  dig39
 d7  dig27
 rw  GND
 v0  the middle point of the potential divider (read out the voltage)
 vss  GND
 vdd  5V

2.the DHT11 temperature and humidity sensor
 with the gnd and vcc properly connected
 the signal pin is connected to the digital 49 pin on the arduino mega board
 
3. the clock module DS3231 module 
 SCL  SCL
 SDA  SDA
 GND  GND
 VCC  VCC (just connect them sequentially, but do remember that when writing, don't connect the SCL and SDA)
 
4. the rotate rod
 with the vcc and gnd are properly connected
 X  analogin A4
 y  analogin A2
 press analogin A3  (when the button is unpressed there are potential and considerable noise, add a pull down resistor to deduce the noise. quite essential!)
 
5. the touch pad
 with the gnd and vcc properly connected
 the signal pin is connected to analogin A5
 
