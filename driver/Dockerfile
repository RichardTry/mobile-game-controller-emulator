FROM rabits/qt:5.15-desktop   


RUN mkdir build
WORKDIR build
COPY . /home/user/mocon
RUN cp /home/user/mocon/driver/entrypoint.sh .

# Install dependencies
RUN sudo apt-get update
RUN sudo apt-get install -y libqt5gui5
RUN sudo rm -rf /var/lib/apt/lists/*

# Call QMake
RUN qmake ../mocon/mobile-game-controller-emulator.pro -spec linux-g++ CONFIG+=qml_debug CONFIG+=driver

# Build
RUN make

# Run
CMD sh ./entrypoint.sh
