#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "HeterogeneousCore/AlpakaCore/interface/alpaka/ESProducer.h"
#include "HeterogeneousCore/AlpakaCore/interface/alpaka/ModuleFactory.h"
#include "HeterogeneousCore/AlpakaInterface/interface/config.h"
#include "HeterogeneousCore/AlpakaInterface/interface/memory.h"

#include "RecoTracker/Record/interface/TrackerRecoGeometryRecord.h"

// LST includes
#include <SDL/Module.h>
#include <SDL/ModuleMethods.h>
#include <SDL/LST.h>

namespace ALPAKA_ACCELERATOR_NAMESPACE {

class LSTModulesDevESProducer : public ESProducer {
public:
  LSTModulesDevESProducer(const edm::ParameterSet &iConfig);

  static void fillDescriptions(edm::ConfigurationDescriptions &descriptions);

  //std::unique_ptr<SDL::LSTESHostData> produceHost(TrackerRecoGeometryRecord const& iRecord);
  std::unique_ptr<SDL::LSTESDeviceData<SDL::Dev>> produceDevice(device::Record<TrackerRecoGeometryRecord> const& iRecord);

  edm::ESGetToken<SDL::LSTESHostData, TrackerRecoGeometryRecord> lstESHostToken_;

};

LSTModulesDevESProducer::LSTModulesDevESProducer(const edm::ParameterSet &iConfig)
  : ESProducer(iConfig)
{
  // setWhatProduced(this, &LSTModulesDevESProducer::produceHost);
  // auto cc = setWhatProduced(this, &LSTModulesDevESProducer::produceTest);
  // lstTestToken_ = cc.consumes();

  setWhatProduced(this, &LSTModulesDevESProducer::produceDevice);
}

void LSTModulesDevESProducer::fillDescriptions(edm::ConfigurationDescriptions &descriptions) {
  edm::ParameterSetDescription desc;
  descriptions.addWithDefaultLabel(desc);
}

// std::unique_ptr<SDL::LSTESHostData> LSTModulesDevESProducer::produceHost(TrackerRecoGeometryRecord const& iRecord) {
//   return SDL::loadAndFillESHost();
// }

std::unique_ptr<SDL::LSTESDeviceData<SDL::Dev>> LSTModulesDevESProducer::produceDevice(device::Record<TrackerRecoGeometryRecord> const& iRecord) {
  //auto const& lstESHostData = iRecord.getData(lstESHostToken_);
  auto lstESHostData = SDL::loadAndFillESHost();  // TODO: get this from the iRecord bypassing the copy that it tries to do
  SDL::QueueAcc& queue = iRecord.queue();
  return SDL::loadAndFillESDevice(queue, lstESHostData.get());
}

}  // namespace ALPAKA_ACCELERATOR_NAMESPACE

DEFINE_FWK_EVENTSETUP_ALPAKA_MODULE(LSTModulesDevESProducer);
