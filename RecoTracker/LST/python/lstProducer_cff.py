import FWCore.ParameterSet.Config as cms

#from RecoTracker.LST.lstProducer_cfi import lstProducer
from RecoTracker.LST.lstsonicProducer_cfi import lstsonicProducer as _lstsonicProducer
#from RecoTracker.LST.lstsonicProducer_cfi import lstsonicProducer as lstsonicProducer

lstsonicProducer = _lstsonicProducer.clone(
    Client = dict(
        timeout = 300,
        mode = "Async",
        modelName = "identity_fp32",
        #modelName = "lst",
        modelConfigPath = "RecoTracker/LST/python/config.pbtxt",
        # version "1" is the resolutionTune
        # version "2" is the responeTune
        modelVersion = "1",
    ),
    #pf_src = "packedPFCandidates",
)

#from Configuration.ProcessModifiers.gpu_cff import gpu
#(~gpu).toModify(lstProducer.alpaka, backend = 'serial_sync')
#(~gpu).toModify(lstsonicProducer.alpaka, backend = 'serial_sync')

#from RecoTracker.LST.lstModulesDevESProducer_cfi import lstModulesDevESProducer
#(~gpu).toModify(lstModulesDevESProducer.alpaka, backend = 'serial_sync')
