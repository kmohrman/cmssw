#include <memory>

// LST includes
#include "SDL/Constants.h"
#include "SDL/Module.h"
#include "SDL/PixelMap.h"
#include "SDL/EndcapGeometry.h"
#include "SDL/TiltedGeometry.h"
#include "SDL/ModuleConnectionMap.h"

namespace SDL {

  template <typename TDev>
  struct LSTESData {
    uint16_t nModules;
    uint16_t nLowerModules;
    std::shared_ptr<SDL::modulesBuffer<TDev>> modulesBuffers;
    std::shared_ptr<SDL::pixelMap> pixelMapping;
    std::shared_ptr<SDL::EndcapGeometry<TDev>> endcapGeometry;
    std::shared_ptr<SDL::TiltedGeometry<TDev>> tiltedGeometry;
    std::shared_ptr<SDL::ModuleConnectionMap<TDev>> moduleConnectionMap;

    LSTESData(uint16_t nModulesIn,
              uint16_t nLowerModulesIn,
              std::shared_ptr<SDL::modulesBuffer<TDev>> modulesBuffersIn,
              std::shared_ptr<SDL::pixelMap> pixelMappingIn,
              std::shared_ptr<SDL::EndcapGeometry<TDev>> endcapGeometryIn,
              std::shared_ptr<SDL::TiltedGeometry<TDev>> tiltedGeometryIn,
              std::shared_ptr<SDL::ModuleConnectionMap<TDev>> moduleConnectionMapIn)
            : nModules(nModulesIn),
              nLowerModules(nLowerModulesIn),
              modulesBuffers(modulesBuffersIn),
              pixelMapping(pixelMappingIn),
              endcapGeometry(endcapGeometryIn),
              tiltedGeometry(tiltedGeometryIn),
              moduleConnectionMap(moduleConnectionMapIn) {}
  };

} // namespace SDL
