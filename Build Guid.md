__This is a guid on how to build your own Key Bob__
Estimated build time: 3-5 hours
Estimated shipping time: 1-3 weeks

__TOOLS/ Materials Needed__
-------------------
1) Soldering iron
2) Solder __or__ rosin core
3) Flux (if using regular solder)
4) Fume extractor (good practice for health)
5) Small length of wire (~1ft)
6) Cutter/ wire stripper
7) Arduino IDE coding software
8) USB A to USB C connector (connects ESP32 to PC)
9) Laptop __or__ PC needed for uploading code

   If you __don't__ have any of these please borrow them, __or__ buy them from a supplier like AliExpress or Amazon.

-------------------------------------------------------------------------------------------------------------

#1) Purchase Parts
-----------------------
  1) Go to my BOM.csv file, copy and paste the links into a web browser of the parts you need.
     (You can use other parts sources if you wish)

-------------------------------------------------------------------------------------------------------------

#2) Order PCB
--------------------
  1) You will find the link in BOM.csv that brings you to the JLCPCB website where you will order the PCB.
  2) Download the PCB Production.zip file in my Key Bob PCB file..
  3) Go back to JLCPCB and import the zip file into where it says (Add gerber file).
  4) Set the PCB thickness to 1.2mm.
  5) Feel free to select any PCB color.
  6) Add it to your cart and select the type of shipping you want, then buy.

-------------------------------------------------------------------------------------------------------------

#3) PCB Schematic
------------------------
This is the wiring diagram of the PCB, this will be handy for when you solder everything together.

You can accses this schematic and the PCB through the Key Bob PCB folder and insert the file into Kicad(free software)

Link to Kicad(free): https://www.kicad.org/

<img width="951" height="697" alt="image" src="https://github.com/user-attachments/assets/6c4993d5-a555-4e35-8134-987e7078a849" />


#4) Code   - once you have the esp32 -
----------------------------------------
1) Open arduino ide software, or visual studio code with platformIO installed
2) __If you don't have arduino ide,__ download here and select your OS system: https://www.arduino.cc/en/software/
3) Download the code from Code.zip file.
4) Extract the file by right clicking the file.
5) Import the Get MAC Address code first to obtain the MAC address of your ESP32.
6) Make sure you have these libraries installed: Adafruit BusIO, Adafruit GFX Library, Adafruit SSD 1306.
7) Flash the code to your ESP32, make sure it's plugged in and the right serial port is selected.
8) Write down the MAC address somewhere, you need it for the main code.
9) Open the main code file.
10) Write your MAC address in the labled code once, somewhere near the top.
11) Flash the code to your ESP32.

    video on how to flash, __skip to 2:50__ : https://www.youtube.com/watch?v=V9I9koQ0AeA&t=230s

  If you're curious how the ESP now function works: https://www.youtube.com/watch?v=qxwXwNS3Avw
     
  If you want a more in depth how to code with ESP now function: https://www.youtube.com/watch?v=bEKjCDDUPaU&t=1354s
  
-------------------------------------------------------------------------------------------------------------

  #5) Solder
  ------------------
  1) Overview the provided schematic above.
  2) __DO NOT__ short the battery wires as this will cause possible damage to the battery.
     When cutting the wires for the battery make sure to do one at a time, not posative and negative as it will short circuit.
  4) __If__ you're using flux, apply a very very thin layer on the parts to allow the solder to flow better.
  5) Make sure when placing the ESP32 you have the USB-C face where the silkscreen on the board shows USB-C in a box.
  6) Double check polarity of components before soldering all the pins. (only the resistor has no polarity)
  7) Put the LED in the specified location on the schematic, and put the short leg (negative/ cathode) in the square hole.
  8) To solder on the ESP32 you can have someone hold it, or pre-tin one pad then apply heat while positioning it.

     __If you don't know how to solder,__ watch this: https://www.youtube.com/watch?v=Qps9woUGkvI

-------------------------------------------------------------------------------------------------------------

#6) Micro SD Card
-------------------
1) Format the Micro SD card to FAT32 on your laptop or PC. (You need a micro SD card to usb-A adapter)
2) Download the file named mp3 from my repository
3) Transfer the mp3 files to the SD card
4) Insert the SD card into the DFPlayer (there is only one way it goes in, don't force it)

   If you don't know how, watch this video: https://www.youtube.com/watch?v=MYjFO_QGdrY
