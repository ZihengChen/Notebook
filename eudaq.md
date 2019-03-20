first make sure you install all package 
```bash
sudo yum install root eigen3-devel gsl gsl-devel wget automake gcc-c++ gcc-gfortran subversion java-1.8.0-openjdk-devel libX11-devel libXpm-devel libXft-devel libXext-devel python-devel tar make cmake which devtoolset-6-gcc-c++ rh-git29 qt5-qtbase-devel openssh-server build-essential xterm.x86_64  zlib-devel
sudo yum groupinstall 'Development Tools'
```

setup eudaq v.1.9.1
```bash
git clone -b v1.x-dev https://github.com/eudaq/eudaq.git
cd eudaq/
git checkout v1.9.1 
cd build
cmake3 -L -DBUILD_tlu=ON ..
make install -j 4
cd ..
```

It might be useful to have the following functions in your `.bashrc`

```bash
mk() {
	cd /afs/cern.ch/user/z/zichen/public/BRIL/eudaq/build
	make install
	cd ..
}

run() {
	bash /afs/cern.ch/user/z/zichen/public/BRIL/eudaq/etc/scripts/STARTRUN.$1
}
```
