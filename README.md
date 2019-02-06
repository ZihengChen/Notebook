
# Setup a New MacOS
This setup is tested on MacOS 10.14.0. A new MacOS 10.14.0 with basic setup are backup in timemachine on Feb 06, 2019. It is recommended to restore from this backup as a starting point.


* bashrc

```bash
curl https://raw.githubusercontent.com/ZihengChen/SetupNewMacOS/master/bash_profile.sh ~/.bash_profile
```

* xcode 

download the latest xcode from AppSore and install command-line tool `xcode-select --install`

* anaconda

download anaconda distribution, choose [latest](https://www.anaconda.com/distribution/) or [previous](https://repo.continuum.io/archive/) version. It has been tested that `Anaconda3 4.4.0 installer` can be understood by root v6.14 and v6.16.

* homebrew and cmake

```bash
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
brew install cmake
```

* root
download root v6.14.00 or later from [here](https://root.cern.ch/downloading-root)
```bash
sudo mkdir /usr/local/root
cd /usr/local/root
sudo cmake TO/ROOT/SRC 
sudo cmake --build . -- -j4
```
