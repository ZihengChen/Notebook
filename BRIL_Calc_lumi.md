# Calculate Luminosity

## 1. Login and Setup
To calculate luminosity for a given data section. First go to `lxplus`
```shell
ssh zichen@lxplus.cern.ch
```

Setup BRIL tools by adding `brilconda` to path and installing `brilws`.
Skip this step if already set up.

```shell
export PATH=$HOME/.local/bin:/cvmfs/cms-bril.cern.ch/brilconda/bin:$PATH
pip install --install-option="--prefix=$HOME/.local" brilws
```

## 2. Run brilcalc
Then use `brilcalc` to calculate luminosity

```shell
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i inputLumis.json 
```
where `inputLumis.json` files are found in [cms-service-dqm](https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/) or lxplus `/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification`

For example, for 2016 B-H
* era-split json are: `/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Era`
* era-summed json are:  `/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Final`

To run over era-split json for 2016 B-H
```shell
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Era/ReReco/Cert_272007-275376_13TeV_23Sep2016ReReco_Collisions16_JSON_eraB.txt
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Era/ReReco/Cert_275657-276283_13TeV_23Sep2016ReReco_Collisions16_JSON_eraC.txt
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Era/ReReco/Cert_276315-276811_13TeV_23Sep2016ReReco_Collisions16_JSON_eraD.txt
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Era/ReReco/Cert_276831-277420_13TeV_23Sep2016ReReco_Collisions16_JSON_eraE.txt  
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Era/ReReco/Cert_277772-278808_13TeV_23Sep2016ReReco_Collisions16_JSON_eraF.txt
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Era/ReReco/Cert_278820-280385_13TeV_23Sep2016ReReco_Collisions16_JSON_eraG.txt
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Era/ReReco/Cert_280919-284044_13TeV_PromptReco_Collisions16_JSON_eraH.txt
```
