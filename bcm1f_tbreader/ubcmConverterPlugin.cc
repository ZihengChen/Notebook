#include "eudaq/DataConverterPlugin.hh"
#include "eudaq/StandardEvent.hh"
#include "eudaq/Utils.hh"

// All LCIO-specific parts are put in conditional compilation blocks
// so that the other parts may still be used if LCIO is not available.
#if USE_LCIO
#include "IMPL/LCEventImpl.h"
#include "IMPL/TrackerRawDataImpl.h"
#include "IMPL/LCCollectionVec.h"
#include "lcio.h"
#endif

namespace eudaq {

  // The event type for which this converter plugin will be registered
  // Modify this to match your actual event type (from the Producer)
  static const char *EVENT_TYPE = "ubcm";

  // Declare a new class that inherits from DataConverterPlugin
  class ubcmConverterPlugin : public DataConverterPlugin {

  public:
    // This is called once at the beginning of each run.
    // You may extract information from the BORE and/or configuration
    // and store it in member variables to use during the decoding later.
    virtual void Initialize(const Event &bore, const Configuration &cnf) {
      m_ubcmparam = bore.GetTag("ubcm", 0);
#ifndef WIN32 // some linux Stuff //$$change
      (void)cnf; // just to suppress a warning about unused parameter cnf
#endif
    }

    // This should return the trigger ID (as provided by the TLU)
    // if it was read out, otherwise it can either return (unsigned)-1,
    // or be left undefined as there is already a default version.
    virtual unsigned GetTriggerID(const Event &ev) const {
      static const unsigned TRIGGER_OFFSET = 8;
      // Make sure the event is of class RawDataEvent
      if (const RawDataEvent *rev = dynamic_cast<const RawDataEvent *>(&ev)) {
        // This is just an ubcm, modified it to suit your raw data format
        // Make sure we have at least one block of data, and it is large enough
        if (rev->NumBlocks() > 0 &&
            rev->GetBlock(0).size() >= (TRIGGER_OFFSET + sizeof(short))) {
          // Read a little-endian unsigned short from offset TRIGGER_OFFSET
          return getlittleendian<unsigned short>(
              &rev->GetBlock(0)[TRIGGER_OFFSET]);
        }
      }
      // If we are unable to extract the Trigger ID, signal with (unsigned)-1
      return (unsigned)-1;
    }

    // Here, the data from the RawDataEvent is extracted into a StandardEvent.
    // The return value indicates whether the conversion was successful.
    // Again, this is just an ubcm, adapted it for the actual data layout.
    virtual bool GetStandardSubEvent(StandardEvent &sev,
                                     const Event &ev) const {

      if (ev.IsBORE() || ev.IsEORE()){
        // Nothing to do
        return true;
      } 
      
      // If we get here there must be data event
      const RawDataEvent &rev = dynamic_cast<const RawDataEvent &>(ev);

      // If the event type is used for different sensors
      // they can be differentiated here
      std::string sensortype = "ubcm";

      // Create a StandardPlane representing one sensor plane
      for (int ich=0; ich<rev.NumBlocks(); ich++){
        StandardPlane plane(ich, EVENT_TYPE, sensortype);
        // Set the number of pixels
        int width = 1, height = 1;
        plane.SetSizeRaw(width, height);

        std::vector<unsigned char> buffer  = rev.GetBlock(ich);

        
        for (size_t sample=0; sample < buffer.size(); sample++){ 
          plane.PushPixel(width, height, (unsigned int) buffer[sample] );
        }  
        // Set the trigger ID
        plane.SetTLUEvent(GetTriggerID(ev));
        // Add the plane to the StandardEvent
        sev.AddPlane(plane);
        // Indicate that data was successfully converted
      }

        
      return true;
    }

#if USE_LCIO
    // This is where the conversion to LCIO is done
    virtual lcio::LCEvent *GetLCIOEvent(const Event * /*ev*/) const {
      return 0;
    }
#endif

  private:
    // The constructor can be private, only one static instance is created
    // The DataConverterPlugin constructor must be passed the event type
    // in order to register this converter for the corresponding conversions
    // Member variables should also be initialized to default values here.
    ubcmConverterPlugin()
        : DataConverterPlugin(EVENT_TYPE), m_ubcmparam(0) {}

    // Information extracted in Initialize() can be stored here:
    unsigned m_ubcmparam;

    // The single instance of this converter plugin
    static ubcmConverterPlugin m_instance;
  }; // class ubcmConverterPlugin

  // Instantiate the converter plugin instance
  ubcmConverterPlugin ubcmConverterPlugin::m_instance;

} // namespace eudaq
