# FSO-GnuRadio-Module
A module for simulating free-space optical communication systems using GnuRadio

To compile the module:
- create ./build directory and compile the code:
```
mkdir build
cd Build
cmake ../
make
```

- after compiling, test the module:
```
make test
```

- and finally install the module:
```
sudo make install
sudo ldconfig
```

Check the demo files included in the repository for further information and usage example:

### FSO_Comm_Demo.grc
![Screenshot](FSO_Comm_Sys.png)
![Screenshot](FSO_Comm_Sig.png)

### Channel_Analyser_Demo.grc
![Screenshot](Chan_An_Sys.png)
![Screenshot](Chan_An_Sig.png)
