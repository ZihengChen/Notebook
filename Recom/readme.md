# Setup Madgraph5 and Delphes
Make sure you have setup your gcc and root. On LPC, this can be done by enabling a cmssw environemnt `cmsenv`.
This setup instruction follows and updates the original tutorial [here](https://twiki.cern.ch/twiki/bin/view/CMSPublic/MadgraphTutorial#Madgraph_and_Delphes_Tutorial)



## 1. Madgraph5
```
wget http://launchpad.net/madgraph5/2.0/2.7.x/+download/MG5_aMC_v2.7.3.tar.gz
tar -xf MG5_aMC_v2.7.3.tar.gz MG5_aMC_v2_7_3/
cd MG5_aMC_v2_7_3/
./bin/mg5_aMC

# in the mg5_aMC interative command line tool
install pythia-pgs
quit
```

## 2. Delphes

```
wget http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.4.2.tar.gz
tar -xf Delphes-3.4.2.tar.gz
cd Delphes-3.4.2
make
vim input/mg5_configuration.txt
```
In the file input/mg5_configuration.txt, change the delphes_path variable on line 143 from `# delphes_path = ./Delphes` to `delphes_path = ./Delphes-3.2.0`

## 3. Recomv2

```
cd models
wget https://github.com/ZihengChen/Notebook/raw/master/Recom/Recomv2_UFO.zip
unzip Recomv2_UFO.zip
cd ..
wget 
./bin/mg5_aMC Recom_proc_card_mg5.dat
cd Recom


open index.html
./bin/generate_events
