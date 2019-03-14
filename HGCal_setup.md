
# 1. Preparation

## 1.1 Login
First log into `vinavx2` computer
```
ssh username@vinavx2
```

add the following lines into your `.bashrc` for the first time.
```
export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh
```



## 1.2 Set CMSSW

Check out `CMSSW_10_6_0_pre2` with the following commands. To check available CMSSW version, use `scram l`

```
cmsrel CMSSW_10_6_0_pre2
cd CMSSW_10_6_0_pre2/src
cmsenv
git cms-addpkg RecoLocalCalo/HGCalRecProducers
git cms-addpkg RecoLocalCalo/HGCalRecAlgos
scram b -j 
```

# 2. Get Production Configurations

To find all relevant workflows, use `runTheMatrix.py -w upgrade -n | grep D35 |grep 1p7`
and will see the following output. Grab the workflow you want.
```
27488.0 SinglePiPt25Eta1p7_2p7_2023D35_GenSimHLBeamSpotFull+DigiFullTrigger_2023D35+RecoFullGlobal_2023D35+HARVESTFullGlobal_2023D35 
27489.0 SingleMuPt15Eta1p7_2p7_2023D35_GenSimHLBeamSpotFull+DigiFullTrigger_2023D35+RecoFullGlobal_2023D35+HARVESTFullGlobal_2023D35 
27490.0 SingleGammaPt25Eta1p7_2p7_2023D35_GenSimHLBeamSpotFull+DigiFullTrigger_2023D35+RecoFullGlobal_2023D35+HARVESTFullGlobal_2023D35 
27491.0 SingleElectronPt15Eta1p7_2p7_2023D35_GenSimHLBeamSpotFull+DigiFullTrigger_2023D35+RecoFullGlobal_2023D35+HARVESTFullGlobal_2023D35 
27688.0 SinglePiPt25Eta1p7_2p7_2023D35PU_GenSimHLBeamSpotFull+DigiFullTriggerPU_2023D35PU+RecoFullGlobalPU_2023D35PU+HARVESTFullGlobalPU_2023D35PU 
27689.0 SingleMuPt15Eta1p7_2p7_2023D35PU_GenSimHLBeamSpotFull+DigiFullTriggerPU_2023D35PU+RecoFullGlobalPU_2023D35PU+HARVESTFullGlobalPU_2023D35PU 
27690.0 SingleGammaPt25Eta1p7_2p7_2023D35PU_GenSimHLBeamSpotFull+DigiFullTriggerPU_2023D35PU+RecoFullGlobalPU_2023D35PU+HARVESTFullGlobalPU_2023D35PU 
27691.0 SingleElectronPt15Eta1p7_2p7_2023D35PU_GenSimHLBeamSpotFull+DigiFullTriggerPU_2023D35PU+RecoFullGlobalPU_2023D35PU+HARVESTFullGlobalPU_2023D35PU 
```

To get the configurations of a certain workflow, use
```
runTheMatrix.py -w upgrade -l 27490.0 -t 4 -j 0
```
where `-t` is number of threads, and `-j` is the number of jobs ( 0 means do not run the config)

# 3. Run Configuration and Produce events

use `cmsRun` to run step 1,2,3.


