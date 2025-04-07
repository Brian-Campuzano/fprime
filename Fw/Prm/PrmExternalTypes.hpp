// ============================================================================
// @file   PrmExternalTypes.hpp
// @author Brian Campuzano
// @brief  Types for delegating parameter serialization and deserialization
// ============================================================================

#ifndef FW_EXTERNAL_PARAM_TYPES_HPP
#define FW_EXTERNAL_PARAM_TYPES_HPP

#include <FpConfig.hpp>
#include <Fw/Prm/ParamValidEnumAc.hpp>
#include "PrmBuffer.hpp"

namespace Fw {

    class ParamExternalDelegate {
        public:
            // TODO Add documentation
            virtual SerializeStatus deserializeParam(const FwPrmIdType id, const ParamValid prmStat, ParamBuffer& buff) = 0;
            virtual SerializeStatus serializeParam(const FwPrmIdType id, ParamBuffer& buff) = 0;
        };

}  // namespace Fw

#endif