cmsrel CMSSW_11_0_0_pre5
cd CMSSW_11_0_0_pre5/src
cmsenv
scram b

runTheMatrix.py -w upgrade -n | grep D41 | grep TTbar_14TeV
runTheMatrix.py -w upgrade -l 20434.0 -t 4 -j 0

```
git cms-addpkg RecoLocalCalo/HGCalRecProducers
git cms-addpkg HeterogeneousCore

cp -r ../../../HGCal/CMSSW_11_0_0_pre2/src/HeterogeneousCore/CUDAUtilities HeterogeneousCore/
cp ../../../HGCal/CMSSW_11_0_0_pre2/src/RecoLocalCalo/HGCalRecProducers/interface/HGCalLayerTilesGPU.h RecoLocalCalo/HGCalRecProducers/interface/
cp ../../../HGCal/CMSSW_11_0_0_pre2/src/RecoLocalCalo/HGCalRecProducers/interface/HGCalCLUEAlgoGPURunner.h RecoLocalCalo/HGCalRecProducers/interface/
cp ../../../HGCal/CMSSW_11_0_0_pre2/src/RecoLocalCalo/HGCalRecProducers/plugins/HGCalCLUEAlgoGPURunner.cu RecoLocalCalo/HGCalRecProducers/plugins/

cp ../../../HGCal/CMSSW_11_0_0_pre2/src/RecoLocalCalo/HGCalRecProducers/plugins/BuildFile.xml RecoLocalCalo/HGCalRecProducers/plugins/BuildFile.xml 
cp ../../../HGCal/CMSSW_11_0_0_pre2/src/RecoLocalCalo/HGCalRecProducers/BuildFile.xml RecoLocalCalo/HGCalRecProducers/BuildFile.xml
```
