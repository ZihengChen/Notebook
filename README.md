# SetupNewMacOS

## Basic Installation

* bashrc

```bash
wget url/bash_profile.sh ~/.bash_profile
```

* xcode 

download the latest xcode from AppSore and install command-line tool `xcode-select --install`

* anaconda

download anaconda installation

* homebrew and cmake

```bash
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
brew install cmake
```

* root

```bash
sudo mkdir /usr/local/root
cd /usr/local/root
sudo cmake TO/ROOT/SRC 
sudo cmake --build . -- -j4
```
