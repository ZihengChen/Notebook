

#include "eudaq/FileReader.hh"
#include "eudaq/PluginManager.hh"
#include "eudaq/OptionParser.hh"
#include <iostream>
#include <fstream>
#include <cmath>

static const std::string EVENT_TYPE = "VME";

int main(int /*argc*/, const char ** argv) {
  eudaq::OptionParser op("VME File Reader", "1.0", "VME Raw Data File Reader", 1);
  try{
    op.Parse(argv);
    eudaq::FileReader reader(op.GetArg(0));

    std::cout << "Opened file:" << reader.Filename() << std::endl;


    std::string outputPath(argv[2]);
    std::string runnb(argv[3]);
    //CSV file test
    //std::ofstream rawFile;
    //rawFile.open(outputPath + "/VME_run"+runnb+".csv");
    
    std::ofstream rawFile_eventFeatures;
    rawFile_eventFeatures.open(outputPath + "/VME_run"+runnb+"_eventFeatures.csv");
    rawFile_eventFeatures << "event,ch,pulseAmp,pulsePos,pulseFWHM,pulseIntegral,pulseMaxSlope,baseline_mean,baseline_std\n";

    int ievent = 0;
    while (reader.NextEvent()) {
      if (reader.GetDetectorEvent().IsEORE()) {
        std::cout << "End of run detected, total number of events " << ievent << std::endl;
        break;
      }
    
      try {
        const eudaq::RawDataEvent &rev = reader.GetDetectorEvent().GetRawSubEvent(EVENT_TYPE); 
        for (size_t ich=0; ich < rev.NumBlocks(); ich++) {

          std::vector<unsigned char> buffer  = rev.GetBlock(ich);
          // std::cout << "-- event " << ievent <<", channel " << ich << ", buffer size is " << buffer.size() << std::endl;
          int nBaselineSample = 0;
          int pulsePos = 0;

          float baseline_mean=0, baseline_std=0, pulseAmp=buffer[1], pulseAmp_sigmaNoise=0;
          for (int idx=1; idx<buffer.size(); idx++ ){
            unsigned int value_int = (unsigned int) buffer[idx];
            float value = float (value_int);

            if (value < pulseAmp){
              pulseAmp = value;
              pulsePos = idx;
            }

            if (idx<1000){
              baseline_mean += value;
              baseline_std += value*value;
              nBaselineSample ++;
            }
          }

          baseline_mean = baseline_mean/nBaselineSample;
          baseline_std = sqrt(baseline_std/nBaselineSample-baseline_mean*baseline_mean);
          pulseAmp = fabs(pulseAmp - baseline_mean);
          pulseAmp_sigmaNoise = pulseAmp/baseline_std;

          // MARK -- calculate FWHM
          float pulseFWHM=0;
          float FWHMThreshold = -0.5*pulseAmp+baseline_mean;
          // left intersection with FWHMThreshold
          for (int ishift=1; ishift<100; ishift++){
            int idx = pulsePos-ishift;
            if (idx<1 || idx>=buffer.size()-1) continue;
            unsigned int value_int = (unsigned int) buffer[idx];
            float value = float (value_int);
            unsigned int previousValue_int = (unsigned int) buffer[idx+1];
            float previousValue = float (previousValue_int);
            if (value > FWHMThreshold){
              float shift = float(ishift) - fabs(value-FWHMThreshold)/fabs(value-previousValue);
              pulseFWHM += shift;
              break;
            }
          }
          // right intersection with FWHMThreshold
          for (int ishift=1; ishift<100; ishift++){
            int idx = pulsePos+ishift;
            if (idx<1 || idx>=buffer.size()-1) continue;
            unsigned int value_int = (unsigned int) buffer[idx];
            float value = float (value_int);
            unsigned int previousValue_int = (unsigned int) buffer[idx-1];
            float previousValue = float (previousValue_int);
            if (value > FWHMThreshold){
              float shift = float(ishift) - fabs(value-FWHMThreshold)/fabs(value-previousValue);
              pulseFWHM += shift;
              break;
            }
          }

          // MARK -- calculate integral and max slope
          float pulseIntegral=0;
          float pulseMaxSlope=0;
          for (int ishift=-100; ishift<=100; ishift++){
            int idx = pulsePos+ishift;
            if (idx<1 || idx>=buffer.size()-1) continue;
            unsigned int value_int = (unsigned int) buffer[idx];
            unsigned int previousValue_int = (unsigned int) buffer[idx-1];
            float value = float (value_int);
            float previousValue = float (previousValue_int);
            pulseIntegral += -(value-baseline_mean);
            if (fabs(previousValue-value)>pulseMaxSlope) {
              pulseMaxSlope=fabs(previousValue-value);
            }
          }

          // save fulse into csv file
          rawFile_eventFeatures << ievent << "," << ich << "," << pulseAmp << "," << pulsePos << "," << pulseFWHM << "," << pulseIntegral << "," << pulseMaxSlope << "," << baseline_mean << "," << baseline_std << "\n";


          //std::cout << " CHANNEL " << ich << std::endl;
          //std::cout << (unsigned int)rev.GetBlock(ich).size() << std::endl;
          /*
          rawFile << "EV" << ievent <<",CH" << ich;
          for (size_t sample=0; sample < buffer.size(); sample++) {

            rawFile << "," << (unsigned int)buffer.at(sample); 
          }           
          rawFile << "\n";
          */
        }
      }
      catch (const eudaq::Exception &) {
        std::cout << "No " << EVENT_TYPE << " subevent in event " << reader.GetDetectorEvent().GetEventNumber() << std::endl;
      }
      
    ievent++;

    //if (ievent%10000 == 0) std::cout << " -- processing event " << ievent << std::endl;
    
    } 
    //rawFile.close(); 
    rawFile_eventFeatures.close();
  }

  catch (...) {
    return op.HandleMainException();
  }
  return 0;
}
