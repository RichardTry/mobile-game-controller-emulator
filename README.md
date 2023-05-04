# MOCON: Mobile Game Controller Emulator
A controller emulating gamepad on mobile devices, and connecting to computers via udp. Written in C++ using the Qt framework. Currently only implemented for android (controller emulattion) and linux (driver emulation). Only tested on ubuntu 20 and an android pie 9 phone.


## Initial Screen
![screenshot](doc/screenshot2.png){width=180 height=360}

## Sending Input
![screenshot](doc/screenshot.png){width=360 height=180}


Here's a [video](https://youtu.be/MWMWvk8R2r0) example of how it works on a laptop with ubuntu 20 and an android phone. 

## Build
Install docker on your machine (with proper permissions, i.e. shoudldn't require sudo) then follow the steps below for controller and driver.
### The Controller APK
The run script will attempt to install the apk on your phone. If instead you want to copy the apk to your host machine you can deploy a container and drop a shell into it. Then run docker cp from the host in a seperate tab.
```
git clone https://bitbucket.org/MuhammetFevziBayiroglu/mobile-game-controller-emulator.git
cd mobile-game-controller-emulator/controller
./build.sh
./run.sh
```

### The Driver
```
# Skip the clone if you've already done it
git clone https://bitbucket.org/MuhammetFevziBayiroglu/mobile-game-controller-emulator.git
cd mobile-game-controller-emulator/driver
./build.sh
./run.sh
```

## Modifying the Controller Layout
You can move around and resize the elements in `resources/controller-layout.svg` to get the exact controller layout you want. You can use any svg editor you like (e.g Inkscape), just don't change the labels of the elements because that's how the svg elements are mapped to layout elements in the code.

## Credit
I'd like to thank [Marek Kraus](https://blog.marekkraus.sk) for putting together this awesome [example](https://blog.marekkraus.sk/c/linuxs-uinput-usage-tutorial-virtual-gamepad/) and making it publicly available. Using the linux documentation alone would have taken me much longer to write the driver side. Thanks to Marek it was a piece of cake.
