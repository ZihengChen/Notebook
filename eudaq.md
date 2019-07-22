first make sure you install prerequisite packages. on `brillab186` these packages are installed.

```bash
sudo yum install root eigen3-devel gsl gsl-devel wget automake gcc-c++ gcc-gfortran subversion java-1.8.0-openjdk-devel libX11-devel libXpm-devel libXft-devel libXext-devel python-devel tar make cmake which devtoolset-6-gcc-c++ rh-git29 qt5-qtbase-devel openssh-server build-essential xterm.x86_64  zlib-devel
sudo yum groupinstall 'Development Tools'
```

### To setup eudaq v.1.9.1
```bash
git clone -b v1.x-dev https://github.com/eudaq/eudaq.git
cd eudaq/
git checkout v1.9.1 
```

### To build eudaq
```
cd build
cmake3 -L ..
make install -j 4
cd ..
```


### To setup the vme,ubcm readers 

at the version used in DESY testbeam 2019/

```
wget https://raw.githubusercontent.com/ZihengChen/Notebook/master/bcm1f_tbreader/VMEReader.cxx -O main/exe/src/VMEReader.cxx
wget https://raw.githubusercontent.com/ZihengChen/Notebook/master/bcm1f_tbreader/ubcmReader.cxx -O main/exe/src/ubcmReader.cxx
wget https://raw.githubusercontent.com/ZihengChen/Notebook/master/bcm1f_tbreader/CMakeLists.txt -O main/exe/CMakeLists.txt
wget https://raw.githubusercontent.com/ZihengChen/Notebook/master/bcm1f_tbreader/ubcmConverterPlugin.cc -O main/lib/plugins/ubcmConverterPlugin.cc
wget https://raw.githubusercontent.com/ZihengChen/Notebook/master/bcm1f_tbreader/VMEConverterPlugin.cc -O main/lib/plugins/VMEConverterPlugin.cc
```
Then build again

### To read raw and make csv
in `eudaq`
```
wget https://raw.githubusercontent.com/ZihengChen/Notebook/master/bcm1f_tbreader/runRawToCsv.py -O runRawToCsv.py
```
The raw file locations are

* **brillab186** `/localdata/TestBeamMay2019/bcm1f_2019/`
* **brilutca3** `/localdata/bcm1f_testbeamDESY2019/`


please edit the output directory in `runRawToCsv.py` and then `python runRawToCsv.py`

