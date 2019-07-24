#include "eudaq/FileReader.hh"
#include "eudaq/PluginManager.hh"
#include "eudaq/OptionParser.hh"
#include "eudaq/Event.hh"
#include <fstream>
#include <cmath>



static const std::string EVENT_TYPE = "ubcm";

int main(int /*argc*/, const char ** argv) {
  // You can use the OptionParser to get command-line arguments
  // then they will automatically be described in the help (-h) option
  eudaq::OptionParser op("ubcm File Reader", "1.0", "ubcm Raw Data File Reader", 1);
  try {
    // This will look through the command-line arguments and set the options
    op.Parse(argv);


    // Create a reader for this file
    eudaq::FileReader reader(op.GetArg(0));

    // Display the actual filename (argument could have been a run number)
    std::cout << "Opened file: " << reader.Filename() << std::endl;
    
    std::string outputPath(argv[2]);
    std::string runnb(argv[3]);
    //CSV file test
    //std::ofstream rawFile;
    //rawFile.open(outputPath + "/ubcm_run"+runnb+".csv");
    
    std::ofstream rawFile_eventFeatures;
    rawFile_eventFeatures.open( outputPath + "/ubcm_run"+runnb+"_eventFeatures.csv");
    rawFile_eventFeatures << "event,ch,pulseAmp,pulsePos,pulseFWHM,pulseIntegral,pulseMaxSlope,baseline_mean,baseline_std\n";
    
    int ievent = 0;

    // Now loop over all events in the file
    while (reader.NextEvent()) {

      if (reader.GetDetectorEvent().IsEORE()) {
        std::cout << "End of run detected, total number of events " << ievent << std::endl;
        // Don't try to process if it is an EORE
        break;
      }

      try {
        const eudaq::RawDataEvent & rev = reader.GetDetectorEvent().GetRawSubEvent(EVENT_TYPE);
        for (size_t ich=0; ich < rev.NumBlocks(); ich++){

          std::vector<unsigned char> buffer  = rev.GetBlock(ich);
          // std::cout << "-- event " << ievent <<", channel " << ich << ", buffer size is " << buffer.size() << std::endl;
          int nBaselineSample = 0; 
          int pulsePos = 0;

          float baseline_mean=0;
          float baseline_std=0;
          float pulseAmp=0;
          float pulseAmp_sigmaNoise=0;
    
          for (int idx=1; idx<buffer.size(); idx++ ){
            unsigned int value_int = (unsigned int) buffer[idx];
            float value = float (value_int);

            if (value > pulseAmp){
              pulseAmp = value;
              pulsePos = idx;
            }

            if (idx>1000){
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
          float FWHMThreshold = 0.5*pulseAmp+baseline_mean;
          // left intersection with FWHMThreshold
          for (int ishift=1; ishift<100; ishift++){
            int idx = pulsePos-ishift;
            if (idx<1 || idx>=buffer.size()-1) continue;
            unsigned int value_int = (unsigned int) buffer[idx];
            float value = float (value_int);
            unsigned int previousValue_int = (unsigned int) buffer[idx+1];
            float previousValue = float (previousValue_int);
            if (value < FWHMThreshold){
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
            if (value < FWHMThreshold){
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
            pulseIntegral += (value-baseline_mean);
            if (fabs(previousValue-value)>pulseMaxSlope) {
              pulseMaxSlope=fabs(previousValue-value);
            }
          }

          // save fulse into csv file
          rawFile_eventFeatures << ievent << "," << ich << "," << pulseAmp << "," << pulsePos << "," << pulseFWHM << "," << pulseIntegral << "," << pulseMaxSlope << "," << baseline_mean << "," << baseline_std << "\n";


          // save std event into csv file
          /*
          rawFile << "EV" << ievent << ",CH" << ich ;
          for (int idx=0; idx<buffer.size(); idx++ ){
            rawFile << "," << (unsigned int)buffer[idx];
          }
          rawFile << "\n";
          */
        }

      } catch (const eudaq::Exception & ) {
        std::cout << "No " << EVENT_TYPE << " subevent in event "
          << reader.GetDetectorEvent().GetEventNumber()
          << std::endl;
      }
      // increase ievent
      ievent ++;
      //if (ievent%10000 == 0) std::cout << " -- processing event " << ievent << std::endl;

    }

    //rawFile.close(); 
    rawFile_eventFeatures.close();

  } catch (...) {
    // This does some basic error handling of common exceptions
    return op.HandleMainException();
  }
  return 0;
}
