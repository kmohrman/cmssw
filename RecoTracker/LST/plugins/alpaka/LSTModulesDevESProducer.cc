#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "HeterogeneousCore/AlpakaCore/interface/alpaka/ESProducer.h"
#include "HeterogeneousCore/AlpakaCore/interface/alpaka/ModuleFactory.h"
#include "HeterogeneousCore/AlpakaInterface/interface/config.h"
#include "HeterogeneousCore/AlpakaInterface/interface/memory.h"

#include "RecoTracker/Record/interface/TrackerRecoGeometryRecord.h"

#include "RecoTracker/LST/interface/alpaka/LSTESData.h"

// LST includes
#include "SDL/Module.h"
#include "SDL/ModuleMethods.h"
#include "SDL/LST.h"

namespace ALPAKA_ACCELERATOR_NAMESPACE {

class LSTModulesDevESProducer : public ESProducer {
public:
  LSTModulesDevESProducer(const edm::ParameterSet &iConfig);

  static void fillDescriptions(edm::ConfigurationDescriptions &descriptions);

  std::shared_ptr<SDL::LSTESData<SDL::Dev>> produce(device::Record<TrackerRecoGeometryRecord> const& iRecord);

};

LSTModulesDevESProducer::LSTModulesDevESProducer(const edm::ParameterSet &iConfig)
  : ESProducer(iConfig)
{
  setWhatProduced(this, iConfig.getParameter<std::string>("ComponentName"));
}

void LSTModulesDevESProducer::fillDescriptions(edm::ConfigurationDescriptions &descriptions) {
  edm::ParameterSetDescription desc;
  desc.add<std::string>("ComponentName", "")->setComment("Product label");
  descriptions.addWithDefaultLabel(desc);
}

  std::shared_ptr<SDL::LSTESData<SDL::Dev>> LSTModulesDevESProducer::produce(device::Record<TrackerRecoGeometryRecord> const& iRecord) {
    SDL::QueueAcc& queue = iRecord.queue();
    SDL::Dev devAcc = alpaka::getDev(queue);

    // Create objects that used to be global
    uint16_t nModules;
    uint16_t nLowerModules;
    std::shared_ptr<SDL::modulesBuffer<SDL::Dev>> modulesBuffers = std::make_shared<SDL::modulesBuffer<SDL::Dev>>(devAcc);
    std::shared_ptr<SDL::pixelMap> pixelMapping = std::make_shared<SDL::pixelMap>();
    std::shared_ptr<SDL::EndcapGeometry<SDL::Dev>> endcapGeometry = std::make_shared<SDL::EndcapGeometry<SDL::Dev>>(devAcc);
    std::shared_ptr<SDL::TiltedGeometry<SDL::Dev>> tiltedGeometry = std::make_shared<SDL::TiltedGeometry<SDL::Dev>>();
    std::shared_ptr<SDL::ModuleConnectionMap<SDL::Dev>> moduleConnectionMap = std::make_shared<SDL::ModuleConnectionMap<SDL::Dev>>();

    SDL::LST<SDL::Acc>::loadAndFillES(queue,
                                      nModules,
                                      nLowerModules,
                                      modulesBuffers,
                                      pixelMapping,
                                      endcapGeometry,
                                      tiltedGeometry,
                                      moduleConnectionMap);
    return std::make_shared<SDL::LSTESData<SDL::Dev>>(nModules,
                                                      nLowerModules,
                                                      modulesBuffers,
                                                      pixelMapping,
                                                      endcapGeometry,
                                                      tiltedGeometry,
                                                      moduleConnectionMap);
}

}  // namespace ALPAKA_ACCELERATOR_NAMESPACE

DEFINE_FWK_EVENTSETUP_ALPAKA_MODULE(LSTModulesDevESProducer);
