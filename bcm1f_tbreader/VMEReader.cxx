#include "eudaq/FileReader.hh"
#include "eudaq/PluginManager.hh"
#include "eudaq/OptionParser.hh"
#include <iostream>
#include <fstream>
#include <cmath>

static const std::string EVENT_TYPE = "VME";

int main(int /*argc*/, const char ** argv) {
  eudaq::OptionParser op("VME File Reader", "1.0", "VME Raw Data File Reader", 1);
  eudaq::OptionFlag doraw(op, "r", "raw", "Display raw data from events");
  eudaq::OptionFlag docon(op, "c", "converted", "Display converted events");
  try{
    op.Parse(argv);
    //for (size_t i=0; i<op.NumArgs(); i++) {
      eudaq::FileReader reader(op.GetArg(0));

      std::cout << "Opened file:" << reader.Filename() << std::endl;

      if (docon.IsSet()) {
        eudaq::PluginManager::Initialize(reader.GetDetectorEvent());
      }
      std::string runnb(argv[3]); 
      //CSV file test
      //std::ofstream rawFile;
      //rawFile.open("/home/teleuser/eudaq_1.9.1/data/BCM1Ftestbeam/VME_run"+runnb+".csv");
      
      std::ofstream rawFile_eventFeatures;
      rawFile_eventFeatures.open("/home/teleuser/eudaq_1.9.1/data/BCM1Ftestbeam/VME_run" + runnb + "_eventFeatures.csv");
      rawFile_eventFeatures << "event,ch,pulseAmp,pulsePos,baseline_mean,baseline_std\n";

      //std::ofstream stdevFile;
      //rawFile.open("/home/teleuser/eudaq_1.9.1/data/BCM1Ftestbeam/VME_run"+runnb+".csv");
      int ievent = 0;
      while (reader.NextEvent()) {
        if (reader.GetDetectorEvent().IsEORE()) {
          std::cout << "End of run detected" << std::endl;
          break;
        }
      
        if (doraw.IsSet()) {
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
              // save fulse into csv file
              rawFile_eventFeatures << ievent << "," << ich << "," << pulseAmp << "," << pulsePos  << "," << baseline_mean << "," << baseline_std << "\n";    


              //std::cout << " CHANNEL " << ich << std::endl;
              //std::cout << (unsigned int)rev.GetBlock(ich).size() << std::endl;
              /*
	      rawFile << "EV" << ievent <<",CH" << ich;
              for (size_t sample=0; sample < buffer.size(); sample++) {
		
                rawFile << "," << (unsigned int)buffer.at(sample); 
              }           
              rawFile << "\n";*/
            }
            //std::cout << rev << std::endl;
          }
          catch (const eudaq::Exception &) {
            std::cout << "No " << EVENT_TYPE << " subevent in event " << reader.GetDetectorEvent().GetEventNumber() << std::endl;
          }
        }
        if (docon.IsSet()) {
          eudaq::StandardEvent sev = eudaq::PluginManager::ConvertToStandard(reader.GetDetectorEvent());
          size_t NumSens = sev.NumPlanes();
          for (size_t ich=0; ich < NumSens; ich++){
            eudaq::StandardPlane sens = sev.GetPlane(ich); 
            //std::cout << "CHANNEL " << ich << std::endl;
            size_t TotSamples = sens.HitPixels(0);

            //stdevFile << "CH" << ich << ",";
            for (size_t sample=1; sample < TotSamples; sample++){// start from 2 because 2 first samples = 0 
              //std::cout << sens.GetPixel(sample, 0) << std::endl;
              //stdevFile << sens.GetPixel(sample,0) << ","; 
            }
           // stdevFile << "\n";
          } 

          //std::cout << sev << std::endl;
        }
	ievent++;
      } 
     //rawFile.close(); 
     //stdevFile.close(); 
     rawFile_eventFeatures.close();
    }
  //}
  catch (...) {
    return op.HandleMainException();
  }
  return 0;
}
