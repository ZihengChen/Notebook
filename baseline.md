```
cmsrel CMSSW_11_0_X_2019-06-11-2300
cd CMSSW_11_0_X_2019-06-11-2300/src/
cmsenv
git cms-init
git cms-merge-topic 27160
git remote add ziheng https://github.com/ZihengChen/cmssw
git fetch ziheng

git branch --track HGCal_Tiling_GPU remotes/ziheng/HGCal_tiling_10_6_0_pre4_GPU
git branch --track HGCal_Tiling_GPU_V2 remotes/ziheng/HGCal_tiling_10_6_0_pre4_GPU_combinedKernal


git checkout HGCal_Tiling_GPU 
git rebase -m -X theirs from-CMSSW_11_0_X_2019-06-11-2300 
git cms-addpkg HeterogeneousCore
scram b -j


git checkout HGCal_Tiling_GPU_V2 
git rebase -m -X theirs from-CMSSW_11_0_X_2019-06-11-2300 
git cms-addpkg HeterogeneousCore
scram b -j
```
