
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



