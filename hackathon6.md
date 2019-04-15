
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


Then checkout the 
```
git cms-merge-topic lecriste:hack5_Leo
git cms-addpkg RecoLocalCalo/HGCalRecProducers
```

```
git add ...
git commit
git push -u my-cmssw HEAD:my_development_branch
```
