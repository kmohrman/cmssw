# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step3 -s RAW2DIGI,RECO:reconstruction_trackingOnly --conditions auto:phase2_realistic_T21 --datatier GEN-SIM-RECO -n 10 --eventcontent RECOSIM --geometry Extended2026D88 --era Phase2C17I13M9 --procModifiers gpu,trackingLST,trackingIters01 --no_exec
import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Phase2C17I13M9_cff import Phase2C17I13M9
from Configuration.ProcessModifiers.gpu_cff import gpu
from Configuration.ProcessModifiers.trackingLST_cff import trackingLST
from Configuration.ProcessModifiers.trackingIters01_cff import trackingIters01

process = cms.Process('RECO',Phase2C17I13M9,gpu,trackingLST,trackingIters01)

#process.FastTimerService = cms.Service( "FastTimerService",
#    dqmPath = cms.untracked.string( "DQM/TimerService" ),
#    dqmModuleTimeRange = cms.untracked.double( 40.0 ),
#    enableDQMbyPath = cms.untracked.bool( True ),
#    writeJSONSummary = cms.untracked.bool( True ),
#    dqmPathMemoryResolution = cms.untracked.double( 5000.0 ),
#    enableDQM = cms.untracked.bool( True ),
#    enableDQMbyModule = cms.untracked.bool( True ),
#    dqmModuleMemoryRange = cms.untracked.double( 100000.0 ),
#    dqmModuleMemoryResolution = cms.untracked.double( 500.0 ),
#    dqmMemoryResolution = cms.untracked.double( 5000.0 ),
#    enableDQMbyLumiSection = cms.untracked.bool( True ),
#    dqmPathTimeResolution = cms.untracked.double( 0.5 ),
#    printEventSummary = cms.untracked.bool( False ),
#    dqmPathTimeRange = cms.untracked.double( 100.0 ),
#    dqmTimeRange = cms.untracked.double( 2000.0 ),
#    enableDQMTransitions = cms.untracked.bool( False ),
#    dqmPathMemoryRange = cms.untracked.double( 1000000.0 ),
#    dqmLumiSectionsRange = cms.untracked.uint32( 2500 ),
#    enableDQMbyProcesses = cms.untracked.bool( True ),
#    dqmMemoryRange = cms.untracked.double( 1000000.0 ),
#    dqmTimeResolution = cms.untracked.double( 5.0 ),
#    printRunSummary = cms.untracked.bool( False ),
#    dqmModuleTimeResolution = cms.untracked.double( 0.2 ),
#    printJobSummary = cms.untracked.bool( True ),
#    jsonFileName = cms.untracked.string(  "time.json" )
#)
#
#process.ThroughputService = cms.Service( "ThroughputService",
#    dqmPath = cms.untracked.string( "HLT/Throughput" ),
#    eventRange = cms.untracked.uint32( 10000 ),
#    timeRange = cms.untracked.double( 60000.0 ),
#    printEventSummary = cms.untracked.bool( True ),
#    eventResolution = cms.untracked.uint32( 100 ),
#    enableDQM = cms.untracked.bool( True ),
#    dqmPathByProcesses = cms.untracked.bool( True ),
#    timeResolution = cms.untracked.double( 5.828 )
#)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2026D88Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.Accelerators_cff')
process.load("HeterogeneousCore.AlpakaCore.ProcessAcceleratorAlpaka_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(300),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet)
)

# Input source
process.source = cms.Source("PoolSource",
    #fileNames = cms.untracked.vstring('file:step3_DIGI2RAW.root'),
    fileNames = cms.untracked.vstring(
        #'file:/depot/cms/users/kmohrman/from_evourlio/step2_21034.1_100Events.root',                                         # From Manos May 29, CMSS_12_* (ttbar)
        #'file:/depot/cms/users/kmohrman/from_evourlio/step2_DIGI_L1TrackTrigger_L1_DIGI2RAW_HLT.root',                       # The one originally specified in the repo (muon gun)
        #'file:/depot/cms/users/kmohrman/from_evourlio/anriosta_LST_samples_CMSSW_14_1_0_pre0/step2_21034.1_100Events.root',  # The 14_* one pointed to in the master readme (ttbar?)

        # Timing study
        'file:/depot/cms/users/kmohrman/from_evourlio/anriosta_LST_samples_CMSSW_14_1_0_pre0/step2_21034.1_100Events_CP01.root',
        'file:/depot/cms/users/kmohrman/from_evourlio/anriosta_LST_samples_CMSSW_14_1_0_pre0/step2_21034.1_100Events_CP02.root',
        'file:/depot/cms/users/kmohrman/from_evourlio/anriosta_LST_samples_CMSSW_14_1_0_pre0/step2_21034.1_100Events_CP03.root',
    ),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    secondaryFileNames = cms.untracked.vstring()
)

###
# SONIC stuff
process.load("HeterogeneousCore.SonicTriton.TritonService_cff")
#process.TritonService.verbose = False
process.TritonService.verbose = True
#process.TritonService.fallback.useDocker = True
#process.TritonService.fallback.verbose = False
process.TritonService.fallback.verbose = True
# uncomment this part if there is one server running at 0.0.0.0 with grpc port 8001
process.TritonService.servers.append(
    cms.PSet(
        name = cms.untracked.string("default"),
        address = cms.untracked.string("0.0.0.0"),
        #address = cms.untracked.string("128.211.148.61"),
        port = cms.untracked.uint32(8011),
    )
)
###

process.options = cms.untracked.PSet(
    IgnoreCompletely = cms.untracked.vstring(),
    Rethrow = cms.untracked.vstring(),
    TryToContinue = cms.untracked.vstring(),
    accelerators = cms.untracked.vstring('*'),
    allowUnscheduled = cms.obsolete.untracked.bool,
    canDeleteEarly = cms.untracked.vstring(),
    deleteNonConsumedUnscheduledModules = cms.untracked.bool(True),
    dumpOptions = cms.untracked.bool(False),
    emptyRunLumiMode = cms.obsolete.untracked.string,
    eventSetup = cms.untracked.PSet(
        forceNumberOfConcurrentIOVs = cms.untracked.PSet(
            allowAnyLabel_=cms.required.untracked.uint32
        ),
        numberOfConcurrentIOVs = cms.untracked.uint32(0)
    ),
    fileMode = cms.untracked.string('FULLMERGE'),
    forceEventSetupCacheClearOnNewRun = cms.untracked.bool(False),
    holdsReferencesToDeleteEarly = cms.untracked.VPSet(),
    makeTriggerResults = cms.obsolete.untracked.bool,
    modulesToCallForTryToContinue = cms.untracked.vstring(),
    modulesToIgnoreForDeleteEarly = cms.untracked.vstring(),
    numberOfConcurrentLuminosityBlocks = cms.untracked.uint32(0),
    numberOfConcurrentRuns = cms.untracked.uint32(1),
    numberOfStreams = cms.untracked.uint32(0),
    numberOfThreads = cms.untracked.uint32(1),
    printDependencies = cms.untracked.bool(False),
    sizeOfStackForThreadsInKB = cms.optional.untracked.uint32,
    throwIfIllegalParameter = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(False)
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step3 nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RECO'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('step3_RAW2DIGI_RECO.root'),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase2_realistic_T21', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstruction_trackingOnly)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.RECOSIMoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)



# Customisation from command line

#Have logErrorHarvester wait for the same EDProducers to finish as those providing data for the OutputModule
from FWCore.Modules.logErrorHarvester_cff import customiseLogErrorHarvesterUsingOutputCommands
process = customiseLogErrorHarvesterUsingOutputCommands(process)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
