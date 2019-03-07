# Get start with BRIL BCM1f uTCA


#### Administration Preparation

* Request a dosimeter. Instructions are [here](https://dosimetry.web.cern.ch/en/dosimeter-obtain). 

* Request access to the CMS BRIL lab `0186-1-f03` in the [ADaMS](http://cern.ch/adams).

## 1. Testbeam DAQ
The ubcm project contains both firmware and low level software tools for uTCA cards operated within BRIL.
Details of usage found in Alex's [wiki](https://gitlab.cern.ch/bril/ubcm/wikis/testbeam)


SSH to PC
```
ssh -X -Y zichen@brillab186
```

For the first time, clone the BCM1f uTCA repository
```
cd /afs/cern.ch/user/z/zichen/public/BRIL/
git clone https://gitlab.cern.ch/bril/ubcm.git]
cd ubcm
git checkout rawdata
```

Configure slow controller and GLIB board.
```
cd /afs/cern.ch/user/z/zichen/public/BRIL/ubcm/sw
. env.sh
make

python scripts/deploy_fw.py -frj lab.amc6 ./placebo 6
cd /home/slow_hub_controller
bin/slow_control_direct AOH 1 M 0x16 3

cd -
python scripts/deploy_fw.py -f lab.amc3 ../fw/fpga/build/bcm1f/bcm1f_0_14_154.mcs 3
```

Run simple DAQ
```
bin/raw_daq -t bcm1f.brillab186.amc3 OUTFILEPREF 10
```




