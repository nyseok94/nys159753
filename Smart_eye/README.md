# Smart Eye

##  1. Crowd Moving-Human Face Detection

## Fusion-Sensor + Signal Processing + Embedded System(High perfomance SW) + Control(motor)

## Purpose

![15_Smart_Eye_Purpose](../(2018-10-19)_Pylepton_Overlay/01_figs/15_Smart_Eye_Purpose.png)



### 1 . Operation of each Sensor

#### PIXY Vision Sensor(CMUcam6) & Pan/Tilt Mechanism kit

I use PIXY Vision Sensor(CMUcam6) with Pan/Tilt Mechanism kit

How to make is.. [http://www.cmucam.org/projects/cmucam5/wiki/Building_The_PanTilt_1](http://www.cmucam.org/projects/cmucam5/wiki/Building_The_PanTilt_1)

![16_Pixy_sensor](../(2018-10-19)_Pylepton_Overlay/01_figs/16_Pixy_sensor.png)

Then connet to Raspberry Pi

![17_pixy_connect_pi](../(2018-10-19)_Pylepton_Overlay/01_figs/17_pixy_connect_pi.png)

When the connection is complete, several steps are required.

```shell
$ sudo apt-get install libusb-1.0-0.dev
$ sudo apt-get install libboost-all-dev
$ sudo apt-get install cmake
$ git clone https://github.com/charmedlabs/pixy.git
$ cd pixy/scripts
$ ./build_libpixyusb.sh
$ ./build_hello_pixy.sh
$ ./build_pantilt_c_demo.sh
$ sudo ./install_libpixyusb.sh
$ cd ../build/hello_pixy
$ sudo ./hello_pixy
$ sudo ./pantilt_c
```

Then you can see output like below.

![05_pantilt](01_figs/05_pantilt.png)

But, to see these results, you have to learn pixy.



First, you have to download 'PixyMon' for your OS.

[pixymon]: http://cmucam.org/projects/cmucam5/wiki/Latest_release

then, run PixyMon. Here is initial screen.

![06_pixymon_initial_screen](01_figs/06_pixymon_initial_screen.png)

Let`s Set signature green color.

![07_set_sig](01_figs/07_set_sig.png)

if you success you can see like below.

![08_green_set](01_figs/08_green_set.png)

And then, run Pan/Tilt demo..

![09_2color](01_figs/09_2color.png)

you can see 2color signatures!



Pixy changes the LED color according to which color it recognizes

![03_Orange](01_figs/03_Orange.png)

![04_green](01_figs/04_green.png)





#############여기서부터 다시 정리##########

학습시키기 링크 : https://blog.naver.com/roboholic84/220569046780

http://www.cmucam.org/projects/cmucam5/wiki/Teach_Pixy_an_object



#### Pylepton - FLIR



#### Ultrasonic Wave Sensor



#### PIR(Passive Infrared)



### 2. Sensor-Communication(SPI, I2C, UART..)



### 3. Signal-Process & Motor Control



### 4. System Implementation

