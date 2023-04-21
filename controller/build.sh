#!/bin/bash
docker rmi mocon_controller 2>/dev/null
docker build .. --force-rm -t mocon_controller --file=./Dockerfile
