
# 1. Preparation

## 1.1 Login
First log into `vinavx2` (or the machine where to work) 
```
ssh username@vinavx2
```

add the following lines into your `.bashrc`.
```
export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh
```

and run `source .bashrc` the first time (unless you logout and login back the machine).


## 1.2 Set CMSSW

Check out `CMSSW_10_6_0_pre2` with the following commands. To check available CMSSW version, use `scram l`

```
cmsrel CMSSW_10_6_0_pre2
cd CMSSW_10_6_0_pre2/src
cmsenv
git cms-addpkg RecoLocalCalo/HGCalRecProducers
git cms-addpkg RecoLocalCalo/HGCalRecAlgos
scram b -j 
```

# 2. Get Production Configurations

To find all relevant workflows, go outside the CMS release folder and use `runTheMatrix.py -w upgrade -n | grep D35 |grep 1p7`
(D35 for the geometry, 1p7 for minEta) and will see the following output. Grab the workflow you want to use.
```
27488.0 SinglePiPt25Eta1p7_2p7_2023D35_GenSimHLBeamSpotFull+DigiFullTrigger_2023D35+RecoFullGlobal_2023D35+HARVESTFullGlobal_2023D35 
27489.0 SingleMuPt15Eta1p7_2p7_2023D35_GenSimHLBeamSpotFull+DigiFullTrigger_2023D35+RecoFullGlobal_2023D35+HARVESTFullGlobal_2023D35 
27490.0 SingleGammaPt25Eta1p7_2p7_2023D35_GenSimHLBeamSpotFull+DigiFullTrigger_2023D35+RecoFullGlobal_2023D35+HARVESTFullGlobal_2023D35 
27491.0 SingleElectronPt15Eta1p7_2p7_2023D35_GenSimHLBeamSpotFull+DigiFullTrigger_2023D35+RecoFullGlobal_2023D35+HARVESTFullGlobal_2023D35 
27688.0 SinglePiPt25Eta1p7_2p7_2023D35PU_GenSimHLBeamSpotFull+DigiFullTriggerPU_2023D35PU+RecoFullGlobalPU_2023D35PU+HARVESTFullGlobalPU_2023D35PU 
27689.0 SingleMuPt15Eta1p7_2p7_2023D35PU_GenSimHLBeamSpotFull+DigiFullTriggerPU_2023D35PU+RecoFullGlobalPU_2023D35PU+HARVESTFullGlobalPU_2023D35PU 
27690.0 SingleGammaPt25Eta1p7_2p7_2023D35PU_GenSimHLBeamSpotFull+DigiFullTriggerPU_2023D35PU+RecoFullGlobalPU_2023D35PU+HARVESTFullGlobalPU_2023D35PU 
27691.0 SingleElectronPt15Eta1p7_2p7_2023D35PU_GenSimHLBeamSpotFull+DigiFullTriggerPU_2023D35PU+RecoFullGlobalPU_2023D35PU+HARVESTFullGlobalPU_2023D35PU 
```

To get the configuration files of a given workflow (i.e. SingleGamma without pile-up), use
```
runTheMatrix.py -w upgrade -l 27490.0 -t 4 -j 0
```
where `27490.0` is the workflow ID, `-t` is number of threads, and `-j` is the number of jobs (`-j 0` won't run the configuration)


# 3. Run Configuration and Produce events

use `cmsRun` to run step1, step2 and step3. 

As step4, clone the repository for NTUPLES in `CMSSW_10_6_0_pre2/src/` and compile

```
git clone https://github.com/CMS-HGCAL/reco-ntuples.git RecoNtuples
scram b -j
```

Then create the following configuration file (`step4_NTUPLE.py`) in the step configuration folder and run it with `cmsRun`:

```
import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras

process = cms.Process("Demo")
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('Configuration.Geometry.GeometryExtended2023D35Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.EventContent.EventContent_cff')
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
try:
    process.load('RecoLocalCalo.HGCalRecProducers.HGCalLocalRecoSequence_cff')
except Exception: # ConfigFileReadError in case config does not exist                                                                                                                                                                                                                         
    process.load('SimCalorimetry.HGCalSimProducers.hgcalDigitizer_cfi')
    process.load('RecoLocalCalo.HGCalRecProducers.hgcalLayerClusters_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase2_realistic', '')
from FastSimulation.Event.ParticleFilter_cfi import *
from RecoLocalCalo.HGCalRecProducers.HGCalRecHit_cfi import dEdX

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use                                                                                                                                                                                                                              
    fileNames = cms.untracked.vstring(
        'file:step3.root'
    ),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
)


process.ana = cms.EDAnalyzer('HGCalAnalysis',
                             detector = cms.string("all"),
                             inputTag_HGCalMultiCluster = cms.string("hgcalMultiClusters"),
                             rawRecHits = cms.bool(False),
                             readCaloParticles = cms.bool(False),
                             storeGenParticleOrigin = cms.bool(True),
                             storeGenParticleExtrapolation = cms.bool(True),
                             storePCAvariables = cms.bool(False),
                             storeElectrons = cms.bool(False),
                             storePFCandidates = cms.bool(False),
                             readGenParticles = cms.bool(True),
                             recomputePCA = cms.bool(False),
                             includeHaloPCA = cms.bool(False),
                             dEdXWeights = dEdX.weights,
                             layerClusterPtThreshold = cms.double(-1),  # All LayerCluster belonging to a multicluster are saved; this Pt threshold applied to the others                                                                                                                     
                             TestParticleFilter = ParticleFilterBlock.ParticleFilter
)

process.ana.TestParticleFilter.protonEMin = cms.double(100000)
process.ana.TestParticleFilter.etaMax = cms.double(3.1)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("file:step4_Ntuple.root")

                                   )

reRunClustering = False

if reRunClustering:
    #process.hgcalLayerClusters.minClusters = cms.uint32(0)                                                                                                                                                                                                                                   
    #process.hgcalLayerClusters.realSpaceCone = cms.bool(True)                                                                                                                                                                                                                                
    #process.hgcalLayerClusters.multiclusterRadius = cms.double(2.)  # in cm if realSpaceCone is true                                                                                                                                                                                         
    #process.hgcalLayerClusters.dependSensor = cms.bool(True)                                                                                                                                                                                                                                 
    #process.hgcalLayerClusters.ecut = cms.double(3.)  # multiple of sigma noise if dependSensor is true                                                                                                                                                                                      
    #process.hgcalLayerClusters.kappa = cms.double(9.)  # multiple of sigma noise if dependSensor is true                                                                                                                                                                                     
    #process.hgcalLayerClusters.deltac = cms.vdouble(2.,3.,5.) #specify delta c for each subdetector separately                                                                                                                                                                               
    process.p = cms.Path(process.hgcalLayerClusters+process.ana)
else:
    process.p = cms.Path(process.ana)
```
