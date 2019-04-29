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

To run over era-split json for 2016 B-H, with single electron trigger "HLT_Ele27_WPTight_Gsf_v*"
```shell
export CERTDIR=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Era/ReReco/

brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i $CERTDIR/Cert_272007-275376_13TeV_23Sep2016ReReco_Collisions16_JSON_eraB.txt --hltpath "HLT_Ele27_WPTight_Gsf_v*" --without-checkjson 
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i $CERTDIRo/Cert_275657-276283_13TeV_23Sep2016ReReco_Collisions16_JSON_eraC.txt --hltpath "HLT_Ele27_WPTight_Gsf_v*" --without-checkjson 
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i $CERTDIR/Cert_276315-276811_13TeV_23Sep2016ReReco_Collisions16_JSON_eraD.txt --hltpath "HLT_Ele27_WPTight_Gsf_v*" --without-checkjson 
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i $CERTDIR/Cert_276831-277420_13TeV_23Sep2016ReReco_Collisions16_JSON_eraE.txt --hltpath "HLT_Ele27_WPTight_Gsf_v*" --without-checkjson 
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i $CERTDIR/Cert_277772-278808_13TeV_23Sep2016ReReco_Collisions16_JSON_eraF.txt --hltpath "HLT_Ele27_WPTight_Gsf_v*" --without-checkjson 
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i $CERTDIR/Cert_278820-280385_13TeV_23Sep2016ReReco_Collisions16_JSON_eraG.txt --hltpath "HLT_Ele27_WPTight_Gsf_v*" --without-checkjson 
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb -i $CERTDIR/Cert_280919-284044_13TeV_PromptReco_Collisions16_JSON_eraH.txt --hltpath "HLT_Ele27_WPTight_Gsf_v*" --without-checkjson 
```

And the reduce single electron lumi mask is [here](https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopTrigger#Summary_for_2016_Run2016B_H_25_n)
which is stored on lxplus at `/afs/cern.ch/user/j/jfernan/public/TOPtriggerJSONS2016/5Dic/ReducedJSONS_from_FullReRecoCertFile/`
run the following commend to get reduced lumi B-H

```
export certfile=LSforPath_HLT_Ele27_WPTight_Gsf_withLowestSeed_L1_SingleIsoEG26_OR_L1_SingleIsoEG28.json
export certdir=/afs/cern.ch/user/j/jfernan/public/TOPtriggerJSONS2016/5Dic/ReducedJSONS_from_FullReRecoCertFile/

brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb  -i $certdir$certfile --without-checkjson --begin 272007 --end 275376
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb  -i $certdir$certfile --without-checkjson --begin 275657 --end 276283
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb  -i $certdir$certfile --without-checkjson --begin 276315 --end 276811
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb  -i $certdir$certfile --without-checkjson --begin 276831 --end 277420
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb  -i $certdir$certfile --without-checkjson --begin 277772 --end 278808
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb  -i $certdir$certfile --without-checkjson --begin 278820 --end 280385
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -u /fb  -i $certdir$certfile --without-checkjson --begin 280919 --end 284044

```

|                          | 2016B | 2016C | 2016D | 2016E | 2016F | 2016G | 2016H | Total[1/fb]|
|--------------------------|-------|-------|-------|-------|-------|-------|-------|------------|
| NormTag                  | 5.75  | 2.573 | 4.242 | 4.025 | 3.105 | 7.576 | 8.651 | **35.922** |
| HLT_Iso(Tk)Mu24_v*       | 5.747 | 2.573 | 4.242 | 4.025 | 3.105 | 7.576 | 8.651 | **35.919** |
| HLT_Ele27_WPTight_Gsf_v* | 5.747 | 2.573 | 4.242 | 4.025 | 3.105 | 7.576 | 8.651 | **35.919** |
| reduced Ele27_WPTight    | 5.747 | 2.573 | 4.242 | 3.633 | 2.905 | 6.156 | 6.094 | **31.351** |

By running these script, the result from `brilcalc` is listed in the following table.

|       |  run number   | LHC delivered [/fb] | CMS recorded [/fb] |
|-------|---------------|--------------------:|-------------------:|
| 2016B | 272007-275376 |               5.991 |               5.75 |
| 2016C | 275657-276283 |               2.685 |              2.573 |
| 2016D | 276315-276811 |               4.411 |              4.242 |
| 2016E | 276831-277420 |               4.222 |              4.025 |
| 2016F | 277772-278808 |               3.303 |              3.105 |
| 2016G | 278820-280385 |               7.865 |              7.576 |
| 2016H | 280919-284044 |               8.985 |              8.651 |
| **total** |      **37.462** |         **35.922** |



This is the same as hn [post](https://hypernews.cern.ch/HyperNews/CMS/get/luminosity/688.html) about LUM-17-001.

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
| **total** |      **44.203** |         **41.557** |
