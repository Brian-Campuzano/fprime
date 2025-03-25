// ============================================================================
// @file   PrmExternalTypes.hpp
// @author Brian Campuzano
// @brief  Types for delegating parameter serialization and deserialization
// ============================================================================

#ifndef FW_EXTERNAL_PARAM_TYPES_HPP
#define FW_EXTERNAL_PARAM_TYPES_HPP

namespace Fw {

    // TODO fix these types with Havard
    // TODO Why isn't spell check running?
    using ParamSerizationFunc = auto (const FwPrmIdType id, ParamBuffer& buff) -> void;
    // Do we need/want this?
    using ParamSerizationFuncPtr = ParamSerization (*);
    using ParamDeserizationPtr = SerializeStatus (*) (const FwPrmIdType id, ParamBuffer& buff);

}  // namespace Fw

#endif
