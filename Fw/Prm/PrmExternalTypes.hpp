// ============================================================================
// @file   PrmExternalTypes.hpp
// @author Brian Campuzano
// @brief  Types for delegating parameter serialization and deserialization
// ============================================================================

#ifndef FW_EXTERNAL_PARAM_TYPES_HPP
#define FW_EXTERNAL_PARAM_TYPES_HPP

#include <FpConfig.hpp>
#include "PrmBuffer.hpp"

namespace Fw {

    class ParamExternalDelegate {
        public:
            // TODO fix these types with Havard
            virtual SerializeStatus serializeParam(const FwPrmIdType id, ParamBuffer& buff) = 0;
            virtual SerializeStatus deserializeParam(const FwPrmIdType id, ParamBuffer& buff) = 0;
        };

}  // namespace Fw

#endif