#!/bin/bash
docker pull rabits/qt:5.15-desktop

docker rmi --force mocon_driver 2>/dev/null
docker build .. --file ./Dockerfile --force-rm -t mocon_driver
