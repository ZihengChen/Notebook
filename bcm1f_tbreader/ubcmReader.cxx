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
  eudaq::OptionParser op("EUDAQ Example File Reader", "1.0",
      "Just an example, modify it to suit your own needs",
      1);
  eudaq::OptionFlag doraw(op, "r", "raw", "Display raw data from events");
  eudaq::OptionFlag docon(op, "c", "converted", "Display converted events");
  try {
    // This will look through the command-line arguments and set the options
    op.Parse(argv);

    // Loop over all filenames
    // for (size_t i = 0; i < op.NumArgs(); ++i) {

      // Create a reader for this file
      eudaq::FileReader reader(op.GetArg(0));

      // Display the actual filename (argument could have been a run number)
      std::cout << "Opened file: " << reader.Filename() << std::endl;

      // The BORE is now accessible in reader.GetDetectorEvent()
      if (docon.IsSet()) {
        // The PluginManager should be initialized with the BORE
        eudaq::PluginManager::Initialize(reader.GetDetectorEvent());
      }
      
      //CSV file test
      //std::ofstream rawFile;
      std::string runnb(argv[3]);
      //rawFile.open("/home/teleuser/eudaq_1.9.1/data/BCM1Ftestbeam/ubcm_run" + runnb + ".csv");
      
      std::ofstream rawFile_eventFeatures;
      rawFile_eventFeatures.open("/home/teleuser/eudaq_1.9.1/data/BCM1Ftestbeam/ubcm_run" + runnb + "_eventFeatures.csv");
      rawFile_eventFeatures << "event,ch,pulseAmp,pulsePos,baseline_mean,baseline_std\n";
      
      // std::ofstream stdevFile;
      // stdevFile.open("stdevtocsv.csv");


      int ievent = 0;

      // Now loop over all events in the file
      while (reader.NextEvent()) {

        if (reader.GetDetectorEvent().IsEORE()) {
          std::cout << "End of run detected" << std::endl;
          // Don't try to process if it is an EORE
          break;
        }

        if (doraw.IsSet()) {


          // Display summary of raw event
          //std::cout << reader.GetDetectorEvent() << std::endl;

          try {
            // Look for a specific RawDataEvent, will throw an exception if not found
            const eudaq::RawDataEvent & rev =
              reader.GetDetectorEvent().GetRawSubEvent(EVENT_TYPE);
            // Display summary of the Example RawDataEvent
            // std::cout << rev << std::endl;

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
              // save fulse into csv file
              rawFile_eventFeatures << ievent << "," << ich << "," << pulseAmp << "," << pulsePos  << "," << baseline_mean << "," << baseline_std << "\n";


              // save std event into csv file
             /*
	      rawFile << "EV" << ievent << ",CH" << ich ;
              for (int idx=0; idx<buffer.size(); idx++ ){
                rawFile << "," << (unsigned int)buffer[idx];
              }
              rawFile << "\n";*/
            }

          } catch (const eudaq::Exception & ) {
            std::cout << "No " << EVENT_TYPE << " subevent in event "
              << reader.GetDetectorEvent().GetEventNumber()
              << std::endl;
          }
        }


        if (docon.IsSet()) {
          // Convert the RawDataEvent into a StandardEvent
          eudaq::StandardEvent sev = eudaq::PluginManager::ConvertToStandard(reader.GetDetectorEvent());
          // Display summary of the Example RawDataEvent
          std::cout << sev << std::endl;

          size_t NumSens = sev.NumPlanes();
          for (size_t ich=0; ich < NumSens; ich++){
            // get the sensor (plane)
            eudaq::StandardPlane sens = sev.GetPlane(ich); 
            // get the length of TotSamples 
            size_t TotSamples = sens.HitPixels(0);
            // print the event
            //std::cout << "-- event " << ievent << ", channel " << ich << ", buffer size is " << TotSamples << std::endl;
            // save std event into csv file
            // stdevFile << ievent << "," << ich ;
            // start from 1, the first element is 0 added artifically.
            // for (size_t sample=1; sample < TotSamples; sample++){
            //   stdevFile << "," << sens.GetPixel(sample,0); 
            // }
            // stdevFile << "\n";
          } 
        }

        // increase ievent
        ievent ++;
      }

      //rawFile.close(); 
      // stdevFile.close();
      rawFile_eventFeatures.close();
    // }

  } catch (...) {
    // This does some basic error handling of common exceptions
    return op.HandleMainException();
  }
  return 0;
}
