
To setup working directory CMSSW_10_6_0_pre4.

```
cmsrel CMSSW_10_6_0_pre4
cd CMSSW_10_6_0_pre4/src
cmsenv
git cms-init


git remote add tony https://github.com/tonydp03/cmssw.git
git fetch tony
git checkout --track tony/ClueAlgorithm_GPU
git cms-addpkg $(git diff $CMSSW_VERSION --name-only | cut -d/ -f-2 | sort -u)
git cms-checkdeps -a

scram b -j 8
```

Then use `runTheMatrix.py -w upgrade -l 27434.0 -t 4 -j 0` to get GEN-SIM-DIGIRECO configurations.


When Tony setup `ClueAlgorithm_GPU`, he did the following updates

>1) Usual setting, just get CMSSW_10_6_0_pre4 release
>2) Use git cms-merge-topic 26295 to get Marco's pull request with TICL
>3) Get HeterogeneousCore package with git cms-addpkg Heterogeneous core and then add
>'HeterogeneousCore/CUDAUtilities/interface/GPUVecArray.h' from the Patatrack release
>4) add 'BinnerGPU.h' and 'GPUHist2D.h' from 'RecoLocalCalo/HGCalRecAlgos/interface/' to 'RecoLocalCalo/HGCalRecProducers/interface/' and modify the 'include GPUVecArray' statement in 'BinnerGPU.h' properly
>5) add 'BinnerGPU.cu' from 'RecoLocalCalo/HGCalRecAlgos/src/' to RecoLocalCalo/HGCalRecProducers/plugins/' and modify the include statements to get 'BinnerGPU.h' and 'GPUHist2D.h' from the correct path (RecProducers, not RecAlgos)
>6) Produce events: runTheMatrix.py -w upgrade -l 27434.0 -t 4 -j 0 (the old files won't work with this release)
>7) Add changes from our 'HGCalImagingAlgo.h' to 'HGCalCLUEAlgo.h' and from 'HGCalImagingAlgo.cc' to 'HGCalCLUEAlgo.cc'
>8) Copy the BuildFile.xml from 'HeterogeneousCore/CUDAUtilities/' in the Patatrack release and paste it in the new one
>9) Add this line in the BuildFile.xml in 'RecoLocalCalo/HGCalRecProducers/' of the new release: <use   name="HeterogeneousCore/CUDAUtilities"/>
>10) Compile! :D



