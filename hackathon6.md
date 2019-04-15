
Setup CMSSW_10_6_0_pre2 following [Simple recipe for developing with Patatrack](https://patatrack.web.cern.ch/patatrack//wiki/PatatrackDevelopment.html)

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


Then chekcout Leo's branch. And get HGCalRecProducers to ntuplize Reco file into flat ntuple.
```
git cms-merge-topic lecriste:hack5_Leo
git cms-addpkg RecoLocalCalo/HGCalRecProducers
```


when merging `lecriste:hack5_Leo`, there might be a small merge confict issue. In this case, you will at the branch `merge-attempt`. To solve this confliction, one just needs to modify *RecoLocalCalo/HGCalRecAlgos/interface/HGCalImagingAlgo.h*. Then commit and merge again to your branch.

```
git checkout hack_zichen
git merge merge-attempt
```



In the end, make your modificationa and add,commit and push to your cmssw fork.
```
git add ...
git commit
git push -u my-cmssw HEAD:hack_zichen
```
