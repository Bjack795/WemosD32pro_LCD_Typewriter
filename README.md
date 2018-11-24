# WemosD32pro_LCD_Typewriter
This is a rudimental typewriter using Wemos D32 pro, an LCD1602 and a USB host for the keyboard


## Hardware

- Wemos D32 pro (https://wiki.wemos.cc/products:d32:d32_pro)
- 16x02 Alphanumeric LCD (http://wiki.sunfounder.cc/index.php?title=LCD1602_Module)
- Keyboard USB Host (http://www.hobbytronics.co.uk/usb-host-keyboard)
- wires, headers and resistances
- microSD

The schematics of the connections are in the LCD_TYPEWRITER_Connections.pdf file
![lcd_typewriter_connections](https://user-images.githubusercontent.com/42472256/48662719-26aa1c80-ea86-11e8-9ddc-a9b52ef8c79b.jpg)

## Software
All the libraries and files included in TYPEWRITER folder.

Arduino IDE must be used to upload all these files.

**REMEMBER**

Add the Wemos D32 pro from the Board Manager

### WebServer Rights

All the WebServer functions rights belong to G6EJD (https://github.com/G6EJD), a genius to whom goes my gratitude for the help given to this project.
The functions are an implementation of this library https://github.com/Pedroalbuquerque/ESP32WebServer.
## Still a prototype
This is the actual aspect of the project.

In the future the aim is to convert it to Epaper display.
The keyboard will be an assembled mechanical one and the case will be 3d Printed

![scheme](https://user-images.githubusercontent.com/42472256/48662727-4e00e980-ea86-11e8-8cf3-20dca738d891.jpeg)


To improve the project this could be an idea of the embedded keyboard, inventor 3d model of a custom GH60 keyboard:


![gh60_render2](https://user-images.githubusercontent.com/42472256/48973720-c0edff80-f046-11e8-9203-d59c9dd1190e.png)
