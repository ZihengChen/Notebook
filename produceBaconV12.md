# Produce Bacon Ntuple Version 12

## 1. Setup Bacon V12

```shell
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc491
cmsrel CMSSW_8_0_24_patch1
cd CMSSW_8_0_24_patch1/src
cmsenv

scp -r zichen@lxplus774.cern.ch:/afs/cern.ch/work/k/ksung/public/Production/12/CMSSW_8_0_24_patch1/src/* ./
  
rm -rf Bacon*

git clone https://github.com/ksung25/BaconProd.git
cd BaconProd
git checkout tags/12 -b v12
cd ..

git clone https://github.com/ksung25/BaconAna.git
cd BaconAna/
git checkout 040cb14fc13b261dce3b27cb66d51fbe660ae72a -b v12
cd ..

scram b -j 
```



## 2. Crab Config
Before submit to crab, do a local test first `cmsRun makingBacon_MC_25ns_MINIAOD.py`.
If local test run goes smoothly, you can submit crab

```
voms-proxy-init --voms cms
which grid-proxy-info
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source $VO_CMS_SW_DIR/cmsset_default.sh
source /cvmfs/cms.cern.ch/crab3/crab.sh

crab submit -c crab_TT_powheg.py 
```
You can query the status by `crab status -d <PROJECT/DIR>`

An axample of crab config is like following

```python

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'TT_powheg'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'makingBacon_MC_25ns_MINIAOD.py'
config.JobType.outputFiles = ['Output.root']
config.JobType.allowUndistributedCMSSW = True
config.Data.inputDataset = '/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 20000
config.Data.outLFNDirBase = '/store/user/zichen/'
config.Data.publication = False
config.Data.outputDatasetTag = 'CRAB3'
config.Site.storageSite = 'T2_CH_CERN'
```
