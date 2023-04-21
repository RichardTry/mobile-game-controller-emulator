FROM rabits/qt:5.15-android   

RUN mkdir build
WORKDIR build
COPY . /home/user/mocon
RUN cp /home/user/mocon/controller/entrypoint.sh .

# Call QMake
RUN qmake ../mocon/mobile-game-controller-emulator.pro -spec android-clang CONFIG+=release CONFIG+=controller ANDROID_ABIS="armeabi-v7a arm64-v8a"

# Build
RUN sudo $ANDROID_NDK_ROOT/prebuilt/linux-x86_64/bin/make apk

# Run
CMD sh ./entrypoint.sh
