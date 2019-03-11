
To calculate luminosity for a given data section. First go to `lxplus`
```
ssh zichen@lxplus.cern.ch
```

Setup BRIL tools by adding `brilconda` to path and installing `brilws`.
Skip this step if already set up.

```
export PATH=$HOME/.local/bin:/cvmfs/cms-bril.cern.ch/brilconda/bin:$PATH
pip install --install-option="--prefix=$HOME/.local" brilws
```

Then use `brilcalc` to calculate luminosity
```
brilcalc lumi -b "STABLE BEAMS" --normtag /afs/cern.ch/user/l/lumipro/public/Normtags/normtag_PHYSICS.json -i inputLumis.json -u /fb
```
where `inputLumis.json` files are found in [cms-service-dqm](https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/)
