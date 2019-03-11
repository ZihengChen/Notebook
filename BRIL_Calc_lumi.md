# Calculate Luminosity

## 1. Login and Setup
To calculate luminosity for a given data section. First go to `lxplus`
```bash
ssh zichen@lxplus.cern.ch
```

Setup BRIL tools by adding `brilconda` to path and installing `brilws`.
Skip this step if already set up.

```
export PATH=$HOME/.local/bin:/cvmfs/cms-bril.cern.ch/brilconda/bin:$PATH
pip install --install-option="--prefix=$HOME/.local" brilws
```

## 2. Run brilcalc
Then use `brilcalc` to calculate luminosity
```
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -i inputLumis.json -u /fb
```
where `inputLumis.json` files are found in [cms-service-dqm](https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/) or on lxplus `/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification`

For example, for 2016 B-H
* era-split json are: `/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Era`
* era-summed json are:  `/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Final`
