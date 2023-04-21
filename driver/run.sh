docker run --rm -it --privileged --name mocon_driver --network=host --volume="$HOME/.Xauthority:/home/user/.Xauthority:ro" --volume="/dev/uinput:/dev/uinput:rw" --env "DISPLAY=$DISPLAY" --env "QT_DEBUG_PLUGINS=1" mocon_driver

