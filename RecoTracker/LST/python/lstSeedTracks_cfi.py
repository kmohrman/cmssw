import FWCore.ParameterSet.Config as cms

initialStepSeedTracks = cms.EDProducer(
    "TrackFromSeedProducer",
    src = cms.InputTag("initialStepSeeds"),
    beamSpot = cms.InputTag("offlineBeamSpot"),
    TTRHBuilder = cms.string("WithoutRefit")
)

highPtTripletStepSeedTracks = cms.EDProducer(
    "TrackFromSeedProducer",
    src = cms.InputTag("highPtTripletStepSeeds"),
    beamSpot = cms.InputTag("offlineBeamSpot"),
    TTRHBuilder = cms.string("WithoutRefit")
)
