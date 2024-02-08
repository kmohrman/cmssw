//#include <alpaka/alpaka.hpp>

//#include "DataFormats/Portable/interface/Product.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
//#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/StreamID.h"
//#include "HeterogeneousCore/AlpakaCore/interface/ScopedContext.h"
//#include "HeterogeneousCore/AlpakaInterface/interface/config.h"

#include "RecoTracker/LST/interface/LSTPixelSeedInput.h"
#include "RecoTracker/LST/interface/LSTPhase2OTHitsInput.h"
#include "RecoTracker/LST/interface/LSTOutput.h"

#include "HeterogeneousCore/SonicTriton/interface/TritonEDProducer.h"

#include "FWCore/Framework/interface/MakerMacros.h"

#ifdef ALPAKA_ACC_GPU_CUDA_ENABLED
#include "SDL/LST.h"
#endif  // ALPAKA_ACC_GPU_CUDA_ENABLED

//namespace ALPAKA_ACCELERATOR_NAMESPACE {

  class LSTSONICProducer : public TritonEDProducer<> {
  public:
    //LSTProducer(edm::ParameterSet& config)
    //explicit LSTSONICProducer(edm::ParameterSet const& config)
    LSTSONICProducer(edm::ParameterSet const& config)
    //LSTProducer(const edm::ParameterSet& config)
        : TritonEDProducer<>(config),
          lstPixelSeedInputToken_{consumes<LSTPixelSeedInput>(config.getParameter<edm::InputTag>("pixelSeedInput"))},
          lstPhase2OTHitsInputToken_{
              consumes<LSTPhase2OTHitsInput>(config.getParameter<edm::InputTag>("phase2OTHitsInput"))},
          verbose_(config.getParameter<int>("verbose")),
          lstOutputToken_{produces<LSTOutput>()} {};

    //void acquire(edm::Event const& event, edm::EventSetup const& setup, edm::WaitingTaskWithArenaHolder task) override {
    void acquire(edm::Event const& iEvent, edm::EventSetup const& iSetup, Input& iInput) override {
      // create a context based on the EDM stream number
      //cms::alpakatools::ScopedContextAcquire<Queue> ctx{iEvent.streamID(), std::move(task)};
      //cms::alpakatools::ScopedContextAcquire<Queue> ctx{iEvent.streamID() };

      // Inputs
      auto const& pixelSeeds = iEvent.get(lstPixelSeedInputToken_);
      auto const& phase2OTHits = iEvent.get(lstPhase2OTHitsInputToken_);


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



//#ifdef ALPAKA_ACC_GPU_CUDA_ENABLED
//      lst_.eventSetup();
//      lst_.run(ctx.queue().getNativeHandle(),
//               verbose_,
//               pixelSeeds.px(),
//               pixelSeeds.py(),
//               pixelSeeds.pz(),
//               pixelSeeds.dxy(),
//               pixelSeeds.dz(),
//               pixelSeeds.ptErr(),
//               pixelSeeds.etaErr(),
//               pixelSeeds.stateTrajGlbX(),
//               pixelSeeds.stateTrajGlbY(),
//               pixelSeeds.stateTrajGlbZ(),
//               pixelSeeds.stateTrajGlbPx(),
//               pixelSeeds.stateTrajGlbPy(),
//               pixelSeeds.stateTrajGlbPz(),
//               pixelSeeds.q(),
//               pixelSeeds.hitIdx(),
//               phase2OTHits.detId(),
//               phase2OTHits.x(),
//               phase2OTHits.y(),
//               phase2OTHits.z());
//#endif  // ALPAKA_ACC_GPU_CUDA_ENABLED
    }

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
      desc.add<edm::InputTag>("pixelSeedInput", edm::InputTag{"lstPixelSeedInputProducer"});
      desc.add<edm::InputTag>("phase2OTHitsInput", edm::InputTag{"lstPhase2OTHitsInputProducer"});
      desc.add<int>("verbose", 0);
      descriptions.addWithDefaultLabel(desc);
    }

  private:
    edm::EDGetTokenT<LSTPixelSeedInput> lstPixelSeedInputToken_;
    edm::EDGetTokenT<LSTPhase2OTHitsInput> lstPhase2OTHitsInputToken_;
    const int verbose_;
    edm::EDPutTokenT<LSTOutput> lstOutputToken_;

#ifdef ALPAKA_ACC_GPU_CUDA_ENABLED
    SDL::LST lst_;
#endif  // ALPAKA_ACC_GPU_CUDA_ENABLED
  };

//}  // namespace ALPAKA_ACCELERATOR_NAMESPACE

//#include "HeterogeneousCore/AlpakaCore/interface/MakerMacros.h"
//DEFINE_FWK_ALPAKA_MODULE(LSTProducer);
DEFINE_FWK_MODULE(LSTSONICProducer);
