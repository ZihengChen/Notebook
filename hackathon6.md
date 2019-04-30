## Setup up for NVIDIA Hachathon


```
export SCRAM_ARCH=slc7_amd64_gcc700
source /data/cmssw/cmsset_default.sh

scram list CMSSW_10_6_0_pre2
cmsrel CMSSW_10_6_0_pre2_Patatrack
cd CMSSW_10_6_0_pre2_Patatrack/src
cmsenv

git cms-init 
git fetch my-cmssw
git branch --track my-cmssw/milestone

git cms-addpkg $(git diff $CMSSW_VERSION --name-only | cut -d/ -f-2 | sort -u)
git cms-checkdeps -a
scram b -j
```


1. Setup CMSSW_10_6_0_pre2 following [Simple recipe for developing with Patatrack](https://patatrack.web.cern.ch/patatrack//wiki/PatatrackDevelopment.html)

```
export SCRAM_ARCH=slc7_amd64_gcc700
source /data/cmssw/cmsset_default.sh

scram list CMSSW_10_6_0_pre2
cmsrel CMSSW_10_6_0_pre2_Patatrack
cd CMSSW_10_6_0_pre2_Patatrack/src
cmsenv

git cms-init -x cms-patatrack
git branch CMSSW_10_6_X_Patatrack --track cms-patatrack/CMSSW_10_6_X_Patatrack

git checkout cms-patatrack/CMSSW_10_6_X_Patatrack -b hack_zichen
git cms-addpkg $(git diff $CMSSW_VERSION --name-only | cut -d/ -f-2 | sort -u)
git cms-checkdeps -a
scram b -j
```


2. Then chekcout Leo's branch. And get HGCalRecProducers to ntuplize Reco file into flat ntuple.
```
git cms-merge-topic lecriste:hack5_Leo
git cms-addpkg RecoLocalCalo/HGCalRecProducers
```

> **[Note]** when merging `lecriste:hack5_Leo`, there might be a small merge confict issue. In this case, you will at the branch `merge-attempt`. To solve this confliction, one just needs to modify *RecoLocalCalo/HGCalRecAlgos/interface/HGCalImagingAlgo.h*. Then commit and merge again to your branch.

```
git checkout hack_zichen
git merge merge-attempt
```



3. In the end, make your modificationa and add,commit and push to your cmssw fork.
```
git add ...
git commit
git push -u my-cmssw HEAD:hack_zichen
```
## Run Clustering on GPU

Get cmsRun configurations with 
```
runTheMatrix.py -w upgrade -l 27434.0 -t 4 -j 0
```

Then do cmsRun step1-3.py to run the reconstruction.

> **[Note]** if the step3.py gots segementation violation, quick fix is to comment out line 145-155 in *RecoLocalCalo/HGCalRecAlgos/src/HGCalImagingAlgo.cc*

```c++
std::vector<size_t> rs = sorted_indices(points_[i]);
std::vector<size_t> rsGPU = sorted_indices(recHitsGPU[i]);
for(size_t zz = 0; zz < 10; ++zz){
  std::cout << "\npoint \n" <<
  points_[i][rs[zz]].data.delta << ", " <<
  points_[i][rs[zz]].data.nearestHigher << std::endl;

  std::cout << "recHit \n" <<
  recHitsGPU[i][rsGPU[zz]].delta << ", " <<
  recHitsGPU[i][rsGPU[zz]].nearestHigher << std::endl;
}
```

