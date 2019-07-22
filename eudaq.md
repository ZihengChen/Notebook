first make sure you install all package 
```bash
sudo yum install root eigen3-devel gsl gsl-devel wget automake gcc-c++ gcc-gfortran subversion java-1.8.0-openjdk-devel libX11-devel libXpm-devel libXft-devel libXext-devel python-devel tar make cmake which devtoolset-6-gcc-c++ rh-git29 qt5-qtbase-devel openssh-server build-essential xterm.x86_64  zlib-devel
sudo yum groupinstall 'Development Tools'
```

### setup eudaq v.1.9.1
```bash
git clone -b v1.x-dev https://github.com/eudaq/eudaq.git
cd eudaq/
git checkout v1.9.1 
```

### to build eudaq
```
cd build
cmake3 -L ..
make install -j 4
cd ..
```


### To Setup the vme,ubcm readers 

at the version used in DESY testbeam 2019/

```
wget https://raw.githubusercontent.com/ZihengChen/Notebook/master/bcm1f_tbreader/VMEReader.cxx -O main/exe/src/VMEReader.cxx
wget https://raw.githubusercontent.com/ZihengChen/Notebook/master/bcm1f_tbreader/ubcmReader.cxx -O main/exe/src/ubcmReader.cxx
wget https://raw.githubusercontent.com/ZihengChen/Notebook/master/bcm1f_tbreader/CMakeLists.txt -O main/exe/CMakeLists.txt
wget https://raw.githubusercontent.com/ZihengChen/Notebook/master/bcm1f_tbreader/ubcmConverterPlugin.cc main/lib/plugins/ubcmConverterPlugin.cc
wget https://raw.githubusercontent.com/ZihengChen/Notebook/master/bcm1f_tbreader/VMEConverterPlugin.cc main/lib/plugins/VMEConverterPlugin.cc
```
Then build again

