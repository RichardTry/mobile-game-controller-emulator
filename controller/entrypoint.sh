#!/bin/bash
# Install
sudo /opt/android-sdk/platform-tools/adb devices
sudo /opt/android-sdk/platform-tools/adb uninstall acme.software.mocon
sudo /opt/android-sdk/platform-tools/adb install /home/user/build/android-build//build/outputs/apk/debug/android-build-debug.apk
