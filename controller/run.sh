#!/bin/bash
docker run --rm -it --privileged --name mocon_controller --network=host --volume="/dev/bus/usb:/dev/bus/usb" mocon_controller
