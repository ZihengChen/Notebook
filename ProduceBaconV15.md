## config the Bacon V15
```bash
cmsrel CMSSW_10_2_13
cd CMSSW_10_2_13/src
cmsenv
cd ../..
wget https://raw.githubusercontent.com/NWUHEP/BaconProd/master/scripts/setup_prod.sh
source setup_prod.sh

cd PATH/CMSSW_10_2_13/src
git clone git@github.com:NWUHEP/BaconAna.git
git clone git@github.com:NWUHEP/BaconProd.git

# get multicrab
cd BaconProd/Ntupler/config
cp /uscms/home/zchen/nobackup/CMSSW_10_2_13/src/BaconProd/Ntupler/config/multicrab .
```
 
## sumbit multicrab

```bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
source /cvmfs/cms.cern.ch/crab3/crab.sh
voms-proxy-init --rfc --voms cms

vim ./multicrab # edit this
./multicrab -c submit

# other multicrab
#./multicrab -c status -w MyDir
#./multicrab -c resubmit -w MyDir -o '--maxmemory=5000'
```