```
cmsrel CMSSW_11_0_0_pre7 
cd CMSSW_11_0_0_pre7/src/
cmsenv
git cms-init
git remote add tony https://github.com/tonydp03/cmssw.git
git fetch tony
git checkout -b newTracksters_forML tony/newTracksters_forML
git cms-addpkg $(git diff $CMSSW_VERSION --name-only | cut -d/ -f-2 | sort -u)
cmsenv
scram b
```


```
cp -r /afs/cern.ch/user/z/zichen/public/HGCal/Workflow Workflow
cd Workflow
cmsRun step1.py
cmsRun step2.py
cmsRun step3.py
cmsRun step4.py
```
