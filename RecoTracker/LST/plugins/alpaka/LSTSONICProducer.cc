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

    // Set up the vector in which we'll store all of the pixelSeed info that we will pass as input
    // The vector will be totally flat, so we'll need to also include some shape info
    auto& input_1 = iInput.at("input");
    //auto inputdata = input_1.allocate<float>();
    auto inputdata = input_1.allocate<double>();
    auto& vinputdata = (*inputdata)[0];

    // phase2OTHits size, so we can reconstruct the vectors properly on the server side
    std:: cout << "OT Hits Size: " << phase2OTHits.x().size() << std::endl;
    vinputdata.push_back(phase2OTHits.x().size());

    // phase2OTHits values
    for (const auto& phase2OTHit_detId : phase2OTHits.detId()) {
      std:: cout << "The phase2OTHits_detId:" << phase2OTHit_detId << std::endl;
      vinputdata.push_back(phase2OTHit_detId);
    }
    for (const auto& phase2OTHit_x : phase2OTHits.x()) {
      std:: cout << "The phase2OTHits_x: " << phase2OTHit_x << std::endl;
      vinputdata.push_back(phase2OTHit_x);
    }
    for (const auto& phase2OTHit_y : phase2OTHits.y()) {
      std:: cout << "The phase2OTHits_y: " << phase2OTHit_y << std::endl;
      vinputdata.push_back(phase2OTHit_y);
    }
    for (const auto& phase2OTHit_z : phase2OTHits.z()) {
      std:: cout << "The phase2OTHits_z: " << phase2OTHit_z << std::endl;
      vinputdata.push_back(phase2OTHit_z);
    }


    // pixelSeeds

    // Check the size of pixelSeeds and put it in the input
    // This is to know how many pixelSeeds we have, so that we know how to unpack it on the server side
    std:: cout << "New event! Size: " << pixelSeeds.px().size() << std::endl;
    vinputdata.push_back(pixelSeeds.px().size());

    // Fill up the vector of pixelSeed info that we will pass as input
    for (const auto& pixelSeed_px : pixelSeeds.px()) {
      vinputdata.push_back(pixelSeed_px);
      std:: cout << "The pixelSeeds_px: " << pixelSeed_px << std::endl;
    }

    for (const auto& pixelSeed_py : pixelSeeds.py()) {
      vinputdata.push_back(pixelSeed_py);
      std:: cout << "The pixelSeeds_py: " << pixelSeed_py << std::endl;
    }

    for (const auto& pixelSeed_pz : pixelSeeds.pz()) {
      vinputdata.push_back(pixelSeed_pz);
      std:: cout << "The pixelSeeds_pz: " << pixelSeed_pz << std::endl;
    }

    for (const auto& pixelSeed_dxy : pixelSeeds.dxy()) {
      vinputdata.push_back(pixelSeed_dxy);
      std:: cout << "The pixelSeeds_dxy: " << pixelSeed_dxy  << std::endl;
    }

    for (const auto& pixelSeed_dz : pixelSeeds.dz()) {
      vinputdata.push_back(pixelSeed_dz);
      std:: cout << "The pixelSeeds_dz: " << pixelSeed_dz  << std::endl;
    }

    for (const auto& pixelSeed_ptErr : pixelSeeds.ptErr()) {
      vinputdata.push_back(pixelSeed_ptErr);
      std:: cout << "The pixelSeeds_ptErr: " << pixelSeed_ptErr  << std::endl;
    }

    for (const auto& pixelSeed_etaErr : pixelSeeds.etaErr()) {
      vinputdata.push_back(pixelSeed_etaErr);
      std:: cout << "The pixelSeeds_etaErr: " <<  pixelSeed_etaErr << std::endl;
    }

    for (const auto& pixelSeed_stateTrajGlbX : pixelSeeds.stateTrajGlbX()) {
      vinputdata.push_back(pixelSeed_stateTrajGlbX);
      std:: cout << "The pixelSeeds_stateTrajGlbX: " << pixelSeed_stateTrajGlbX  << std::endl;
    }

    for (const auto& pixelSeed_stateTrajGlbY : pixelSeeds.stateTrajGlbY()) {
      vinputdata.push_back(pixelSeed_stateTrajGlbY);
      std:: cout << "The pixelSeeds_stateTrajGlbY: " << pixelSeed_stateTrajGlbY  << std::endl;
    }

    for (const auto& pixelSeed_stateTrajGlbZ : pixelSeeds.stateTrajGlbZ()) {
      vinputdata.push_back(pixelSeed_stateTrajGlbZ);
      std:: cout << "The pixelSeeds_stateTrajGlbZ: " << pixelSeed_stateTrajGlbZ  << std::endl;
    }

    for (const auto& pixelSeed_stateTrajGlbPx : pixelSeeds.stateTrajGlbPx()) {
      vinputdata.push_back(pixelSeed_stateTrajGlbPx);
      std:: cout << "The pixelSeeds_stateTrajGlbPx: " <<  pixelSeed_stateTrajGlbPx << std::endl;
    }

    for (const auto& pixelSeed_stateTrajGlbPy : pixelSeeds.stateTrajGlbPy()) {
      vinputdata.push_back(pixelSeed_stateTrajGlbPy);
      std:: cout << "The pixelSeeds_stateTrajGlbPy: " << pixelSeed_stateTrajGlbPy  << std::endl;
    }

    for (const auto& pixelSeed_stateTrajGlbPz : pixelSeeds.stateTrajGlbPz()) {
      vinputdata.push_back(pixelSeed_stateTrajGlbPz);
      std:: cout << "The pixelSeeds_stateTrajGlbPz: " << pixelSeed_stateTrajGlbPz  << std::endl;
    }

    for (const auto& pixelSeed_q : pixelSeeds.q()) {
      vinputdata.push_back(pixelSeed_q);
      std:: cout << "The pixelSeeds_q: " << pixelSeed_q  << std::endl;
    }


    // Special case for hitIdx since it has an extra layer of nestedness
    // Get the size of each of the sub arrays, so we know what shape it is
    for (const auto& inputhitIdx_hitIdx_vec : pixelSeeds.hitIdx()) {
        std::cout << "The hitIdxShape: " << inputhitIdx_hitIdx_vec.size() << std::endl;
        vinputdata.push_back(inputhitIdx_hitIdx_vec.size());
    }
    // Now put in all of the values
    for (const auto& inputhitIdx_hitIdx_vec : pixelSeeds.hitIdx()) {
        std::cout << "Starting:" << std::endl;
        for (const auto& inputhitIdx_hitIdx : inputhitIdx_hitIdx_vec) {
          vinputdata.push_back(inputhitIdx_hitIdx);
          std:: cout << "    The hitIdx: " << inputhitIdx_hitIdx << std::endl;
        }
    }


    // Send the input to the server
    input_1.toServer(inputdata);

    }

    ////////////////////////////////////////


    // Get the output
    void produce(edm::Event& iEvent, edm::EventSetup const& iSetup, Output const& iOutput) override {


      ////////// Get the raw output and put it into a vector //////////
      const auto &output1 = iOutput.begin()->second;
      const auto &outputs_from_server = output1.fromServer<int8_t>();
      auto output = (outputs_from_server[0]);

      // Dump the raw output into a vector
      std::vector <int> output_vec;
      int output_len = output.size()/sizeof(int);
      for (int i=0; i<output_len; i++) {
          int tmp = 0;
          std::memcpy(&tmp,&(output.front())+i*sizeof(int),sizeof(int));
          std::cout << "tmp: " << tmp << std::endl;
          output_vec.push_back(tmp);
      };


      ////////// Reconstruct the output objects from the flat vector //////////

      // The vectors we'll be building up
      std::vector<int>                       out_seedIdx;
      std::vector<short>                     out_trackCandidateType;
      std::vector<unsigned int>              out_len;
      std::vector<std::vector<unsigned int>> out_hits;

      // Counters we'll need to uses to keep track as we loop
      int itr_main = 0; // This will be the counter as we loop through the flat vector
      int itr_start = 0; // Use this to keep track of where to start each for loop

      // Get the seedIdx vector
      int seedIdx_len = output_vec[0]; itr_main++;
      std::cout << "seedIdx_len: " << seedIdx_len << std::endl;
      itr_start = itr_main;
      for (int i=itr_start; i<itr_start+seedIdx_len; i++){
          out_seedIdx.push_back(output_vec[i]);
          std::cout << "    " << output_vec[i] << std::endl;
          itr_main++;
      };

      // Get the trackCandidateType vector
      int trackCandidateType_len = output_vec[itr_main]; itr_main++;
      std::cout << "trackCandidateType_len: " << trackCandidateType_len << std::endl;
      itr_start = itr_main;
      for (int i=itr_start; i<itr_start+trackCandidateType_len; i++){
          out_trackCandidateType.push_back(short (output_vec[i]));
          std::cout << "    " << output_vec[i] << std::endl;
          itr_main++;
      };

      // Get the len vector
      int len_len = output_vec[itr_main]; itr_main++;
      std::cout << "len_len: " << len_len << std::endl;
      itr_start = itr_main;
      for (int i=itr_start; i<itr_start+len_len; i++){
          out_len.push_back((unsigned int) output_vec[i]);
          std::cout << "    " << output_vec[i] << std::endl;
          itr_main++;
      };

      // Get the hits vector of vectors (harder, since nested)
      // Get the shape vector
      int hits_len = output_vec[itr_main]; itr_main++;
      std::vector<int> hits_sizes;
      itr_start = itr_main;
      for (int i=itr_start; i<itr_start+hits_len; i++){
          hits_sizes.push_back(output_vec[i]);
          std::cout << "The hits sizes: " << output_vec[i] << std::endl;
          itr_main++;
      }
      // Get the values
      for (const auto& hits_size : hits_sizes){
          std::cout << "hits_size: " << hits_size << std::endl;
          std::vector<unsigned int> tmp_vec;
          itr_start = itr_main;
          for (int i=itr_start; i<itr_start+hits_size; i++){
              tmp_vec.push_back((unsigned int) output_vec[i]);
              std::cout << "    The hit: " << output_vec[i] << std::endl;
              itr_main++;
          }
          out_hits.push_back(tmp_vec);
      }


      // Print what's in the vectors
      std::cout << "out_seedIdx" << std::endl;
      for (const auto& i : out_seedIdx){
        std::cout << "This is: " << i << std::endl;
      }
      std::cout << "out_trackCandidateType" << std::endl;
      for (const auto& i :out_trackCandidateType){
        std::cout << "This is: " << i << std::endl;
      }
      std::cout << "out_len" << std::endl;
      for (const auto& i :out_len){
        std::cout << "This is: " << i << std::endl;
      }
      std::cout << "out_hits" << std::endl;
      for (const auto& i :out_hits){
          for (const auto& ii : i){
            std::cout << "This is: " << ii << std::endl;
          }
      }


      ////////// Construct the LST output object //////////

      LSTOutput lstOutput;
      lstOutput.setLSTOutputTraits(out_hits, out_len, out_seedIdx, out_trackCandidateType);

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
