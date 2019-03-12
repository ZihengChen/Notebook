# Calculate Luminosity

## 1. Login and Setup
To calculate luminosity for a given data section. First go to `lxplus`
```shell
ssh zichen@lxplus.cern.ch
```

Then add `brilconda` to path.
```shell
export PATH=$HOME/.local/bin:/cvmfs/cms-bril.cern.ch/brilconda/bin:$PATH
```

Note that for the first time user, pip install `brilws` if brilws is missing.
```shell
pip install --install-option="--prefix=$HOME/.local" brilws
```

## 2. Run brilcalc
Then use `brilcalc` to calculate luminosity

```shell
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i inputLumis.json 
```
where `inputLumis.json` files are found in [cms-service-dqm](https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/) or lxplus `/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/`

inside which 
* `Era` for era-split json file.
* `Final` for era-summed json file.

### 2.1 Example: 2016 ReReco
For 2016 B-H, era-split json are: `/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Era`

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

By running these script, the result from `brilcalc` is listed in the following table.


|       | LHC delivered [/fb] | CMS recorded [/fb] |
|-------|--------------------:|-------------------:|
| 2016B |               5.991 |               5.75 |
| 2016C |               2.685 |              2.573 |
| 2016D |               4.411 |              4.242 |
| 2016E |               4.222 |              4.025 |
| 2016F |               3.303 |              3.105 |
| 2016G |               7.865 |              7.576 |
| 2016H |               8.985 |              8.651 |
| **total** |      **37.462** |         **35.922** |
  

### 2.1 Example: 2017 promptReco
For 2017 A-F, era-split json are: `/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Era/Prompt/`

```shell
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Era/Prompt/Cert_294927-297019_13TeV_PromptReco_Collisions17_JSON_eraA.txt
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Era/Prompt/Cert_297020-299329_13TeV_PromptReco_Collisions17_JSON_eraB.txt
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Era/Prompt/Cert_299337-302029_13TeV_PromptReco_Collisions17_JSON_eraC.txt
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Era/Prompt/Cert_302030-303434_13TeV_PromptReco_Collisions17_JSON_eraD.txt
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Era/Prompt/Cert_303435-304826_13TeV_PromptReco_Collisions17_JSON_eraE.txt
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Era/Prompt/Cert_304911-306462_13TeV_PromptReco_Collisions17_JSON_eraF.txt
```

By running these script, the result from `brilcalc` is listed in the following table.


|       | LHC delivered [/fb] | CMS recorded [/fb] |
|-------|--------------------:|-------------------:|
| 2017B |               5.124 |              4.823 |
| 2017C |              10.589 |              9.664 |
| 2017D |               4.427 |              4.252 |
| 2017E |               9.760 |              9.278 |
| 2017F |              14.303 |             13.540 |
| **total** |      **37.462** |         **35.922** |
