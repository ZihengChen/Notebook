dump reco geometry
```
git cms-addpkg Fireworks/Geometry
scram b
cmsRun Fireworks/Geometry/python/dumpRecoGeometry_cfg.py  tag=2023 version=D35
```


Get fireworks on your computer
```
curl http://cmsshow-rels.web.cern.ch/cmsShow-rels/fireworks-mojave-10.3.sparseimage.bz2| bzcat >fireworks-mojave-10.3.sparseimage 
hdiutil attach fireworks-mojave-10.3.sparseimage 
cd /Volumes/Fireworks/bin 
./cmsShow data.root 
```
