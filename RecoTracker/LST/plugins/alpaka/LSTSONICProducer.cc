//#include <alpaka/alpaka.hpp>

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"
#include "FWCore/Utilities/interface/InputTag.h"

//#include "HeterogeneousCore/AlpakaCore/interface/alpaka/EDGetToken.h"
//#include "HeterogeneousCore/AlpakaCore/interface/alpaka/EDPutToken.h"
//#include "HeterogeneousCore/AlpakaCore/interface/alpaka/Event.h"
//#include "HeterogeneousCore/AlpakaCore/interface/alpaka/EventSetup.h"
//#include "HeterogeneousCore/AlpakaCore/interface/alpaka/stream/SynchronizingEDProducer.h"
//#include "HeterogeneousCore/AlpakaInterface/interface/config.h"

#include "RecoTracker/LST/interface/LSTOutput.h"
#include "RecoTracker/LST/interface/LSTPhase2OTHitsInput.h"
#include "RecoTracker/LST/interface/LSTPixelSeedInput.h"

#include "RecoTracker/Record/interface/TrackerRecoGeometryRecord.h"

//#include "SDL/LST.h"

#include "HeterogeneousCore/SonicTriton/interface/TritonEDProducer.h"
#include "FWCore/Framework/interface/MakerMacros.h"

//namespace ALPAKA_ACCELERATOR_NAMESPACE {
//namespace ALPAKA_ACCELERATOR_NAMESPACE {

  //class LSTProducer : public stream::SynchronizingEDProducer<> {
  class LSTSONICProducer : public TritonEDProducer<> {
  public:
    //LSTProducer(edm::ParameterSet const& config)
        //: lstPixelSeedInputToken_{consumes<LSTPixelSeedInput>(config.getParameter<edm::InputTag>("pixelSeedInput"))},
    LSTSONICProducer(edm::ParameterSet const& config)
          : TritonEDProducer<>(config),
          lstPixelSeedInputToken_{consumes<LSTPixelSeedInput>(config.getParameter<edm::InputTag>("pixelSeedInput"))},
          lstPhase2OTHitsInputToken_{
              consumes<LSTPhase2OTHitsInput>(config.getParameter<edm::InputTag>("phase2OTHitsInput"))},
          //modulesESToken_{esConsumes()},
          verbose_(config.getParameter<int>("verbose")),
          lstOutputToken_{produces()} {}

    //void acquire(device::Event const& event, device::EventSetup const& setup) override {
    //void acquire(device::Event const& iEvent,device::EventSetup const& iSetup, Input& iInput) override {
    void acquire(edm::Event const& iEvent, edm::EventSetup const& iSetup, Input& iInput) override {

      // Inputs
      auto const& pixelSeeds = iEvent.get(lstPixelSeedInputToken_);
      auto const& phase2OTHits = iEvent.get(lstPhase2OTHitsInputToken_);

      /*
      auto const& modulesData = setup.getData(modulesESToken_);
      lst_.run(event.queue(),
               &modulesData,
               verbose_,
               pixelSeeds.px(),
               pixelSeeds.py(),
               pixelSeeds.pz(),
               pixelSeeds.dxy(),
               pixelSeeds.dz(),
               pixelSeeds.ptErr(),
               pixelSeeds.etaErr(),
               pixelSeeds.stateTrajGlbX(),
               pixelSeeds.stateTrajGlbY(),
               pixelSeeds.stateTrajGlbZ(),
               pixelSeeds.stateTrajGlbPx(),
               pixelSeeds.stateTrajGlbPy(),
               pixelSeeds.stateTrajGlbPz(),
               pixelSeeds.q(),
               pixelSeeds.hitIdx(),
               phase2OTHits.detId(),
               phase2OTHits.x(),
               phase2OTHits.y(),
               phase2OTHits.z());
    }
    */

    ////////////////////////////////////////
    auto& input = iInput.at("input");
    auto pixelSeedsdata = input.allocate<float>();
    auto& vpixelSeedsdata = (*pixelSeedsdata)[0];
    //auto& vpixelSeedsdata = pixelSeedsdata->at(0);
    //auto& vpixelSeedsdata = pixelSeedsdata.at(0);
    for (const auto& pixelSeed_px : pixelSeeds.px()) {
      vpixelSeedsdata.push_back(pixelSeed_px);
    }
    for (const auto& pixelSeed_py : pixelSeeds.py()) {
      vpixelSeedsdata.push_back(pixelSeed_py);
    }

    for (const auto& pixelSeed_pz : pixelSeeds.pz()) {
      vpixelSeedsdata.push_back(pixelSeed_pz);
    }

    for (const auto& pixelSeed_dxy : pixelSeeds.dxy()) {
      vpixelSeedsdata.push_back(pixelSeed_dxy);
    }

    for (const auto& pixelSeed_dz : pixelSeeds.dz()) {
      vpixelSeedsdata.push_back(pixelSeed_dz);
    }

    for (const auto& pixelSeed_ptErr : pixelSeeds.ptErr()) {
      vpixelSeedsdata.push_back(pixelSeed_ptErr);
    }

    for (const auto& pixelSeed_etaErr : pixelSeeds.etaErr()) {
      vpixelSeedsdata.push_back(pixelSeed_etaErr);
    }

    for (const auto& pixelSeed_stateTrajGlbX : pixelSeeds.stateTrajGlbX()) {
      vpixelSeedsdata.push_back(pixelSeed_stateTrajGlbX);
    }

    for (const auto& pixelSeed_stateTrajGlbY : pixelSeeds.stateTrajGlbY()) {
      vpixelSeedsdata.push_back(pixelSeed_stateTrajGlbY);
    }

    for (const auto& pixelSeed_stateTrajGlbZ : pixelSeeds.stateTrajGlbZ()) {
      vpixelSeedsdata.push_back(pixelSeed_stateTrajGlbZ);
    }

    for (const auto& pixelSeed_stateTrajGlbPx : pixelSeeds.stateTrajGlbPx()) {
      vpixelSeedsdata.push_back(pixelSeed_stateTrajGlbPx);
    }

    for (const auto& pixelSeed_stateTrajGlbPy : pixelSeeds.stateTrajGlbPy()) {
      vpixelSeedsdata.push_back(pixelSeed_stateTrajGlbPy);
    }

    for (const auto& pixelSeed_stateTrajGlbPz : pixelSeeds.stateTrajGlbPz()) {
      vpixelSeedsdata.push_back(pixelSeed_stateTrajGlbPz);
    }

    for (const auto& pixelSeed_q : pixelSeeds.q()) {
      vpixelSeedsdata.push_back(pixelSeed_q);
    }

    //  member named 'algo'?
    //for (const auto& pixelSeed_algo : pixelSeeds.algo()) {
    //  vpixelSeedsdata.push_back(pixelSeed_algo);
    //}

    // This should have it's own input
    //auto hitIdxdata = input.allocate<std::vector<int>>();
    auto hitIdxdata = input.allocate<int>();
    auto& vhitIdxdata = (*hitIdxdata)[0];
    for (const auto& inputhitIdx_hitIdx_vec : pixelSeeds.hitIdx()) {
        for (const auto& inputhitIdx_hitIdx : inputhitIdx_hitIdx_vec) {
          vhitIdxdata.push_back(inputhitIdx_hitIdx);
        }
    }



    // phase2OTHits
    auto& input_phase2OTHits = iInput.at("input_phase2OTHitsdata");
    auto phase2OTHitsdata = input_phase2OTHits.allocate<float>();
    auto& vphase2OTHitsdata = (*phase2OTHitsdata)[0];
    for (const auto& phase2OTHit_x : phase2OTHits.x()) {
      vphase2OTHitsdata.push_back(phase2OTHit_x);
    }

    for (const auto& phase2OTHit_y : phase2OTHits.y()) {
      vphase2OTHitsdata.push_back(phase2OTHit_y);
    }

    for (const auto& phase2OTHit_z : phase2OTHits.z()) {
      vphase2OTHitsdata.push_back(phase2OTHit_z);
    }

    auto phase2OTHitsdataInt = input.allocate<unsigned int>();
    auto& vphase2OTHitsdataInt = (*phase2OTHitsdataInt)[0];
    for (const auto& phase2OTHit_detId : phase2OTHits.detId()) {
      vphase2OTHitsdataInt.push_back(phase2OTHit_detId);
    }


    input.toServer(pixelSeedsdata);
    input.toServer(phase2OTHitsdata);

    }

    ////////////////////////////////////////


    //void produce(device::Event& event, device::EventSetup const&) override {
    //void produce(device::Event& iEvent, device::EventSetup const& iSetup, Output const& iOutput) override {
    void produce(edm::Event& iEvent, edm::EventSetup const& iSetup, Output const& iOutput) override {

      const auto& output1 = iOutput.begin()->second;
      const auto& outputs = output1.fromServer<float>();

      // Output
      LSTOutput lstOutput;
      //lstOutput.setLSTOutputTraits(lst_.hits(), lst_.len(), lst_.seedIdx(), lst_.trackCandidateType());

      iEvent.emplace(lstOutputToken_, std::move(lstOutput));
    }

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
      edm::ParameterSetDescription desc;
      TritonClient::fillPSetDescription(desc);
      desc.add<edm::InputTag>("pixelSeedInput", edm::InputTag{"lstPixelSeedInputProducer"});
      desc.add<edm::InputTag>("phase2OTHitsInput", edm::InputTag{"lstPhase2OTHitsInputProducer"});
      desc.add<int>("verbose", 0);
      descriptions.addWithDefaultLabel(desc);
    }

  private:
    edm::EDGetTokenT<LSTPixelSeedInput> lstPixelSeedInputToken_;
    edm::EDGetTokenT<LSTPhase2OTHitsInput> lstPhase2OTHitsInputToken_;
    //device::ESGetToken<SDL::modulesBuffer<Device>, TrackerRecoGeometryRecord> modulesESToken_;
    //edm::ESGetToken<SDL::modulesBuffer<Device>, TrackerRecoGeometryRecord> modulesESToken_;
    const int verbose_;
    edm::EDPutTokenT<LSTOutput> lstOutputToken_;

    //SDL::LST lst_;
    //SDL::LST<SDL::Acc> lst_;
  };

//}  // namespace ALPAKA_ACCELERATOR_NAMESPACE
//}  // namespace ALPAKA_ACCELERATOR_NAMESPACE

//#include "HeterogeneousCore/AlpakaCore/interface/alpaka/MakerMacros.h"
//DEFINE_FWK_ALPAKA_MODULE(LSTSONICProducer);
DEFINE_FWK_MODULE(LSTSONICProducer);
//DEFINE_FWK_ALPAKA_MODULE(LSTSONICProducer);
