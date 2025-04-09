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

    //! Fw::ParamExternalDelegate is used for parameters that are stored and managed
    //! externally to the owning F' component.
    //!
    //! Fw::ParamExternalDelegate is an abstract base class that defines the interfaces
    //! needed by the F' component to interact with the externally managed parameter(s)
    class ParamExternalDelegate {
        public:

            //! Deserialize a parameter from a parameter buffer
            //!
            //! \param id: Parameter ID of the parameter being deserialized
            //! \param prmStat: The parameter status of the parameter being deserialized
            //! \param buff: The buffer contained the serialized parameter
            //!
            //! \return: The status of the deserialize operation
            virtual SerializeStatus deserializeParam(
                const FwPrmIdType id,
                const ParamValid prmStat,
                ParamBuffer& buff) = 0;

            //! Serialize a parameter into a parameter buffer
            //!
            //! \param id: Parameter ID of the parameter to serialized
            //! \param buff: The buffer to serialize the parameter into
            //!
            //! \return: The status of the serialize operation
            virtual SerializeStatus serializeParam(
                const FwPrmIdType id,
                ParamBuffer& buff) const = 0;
        };

}  // namespace Fw

#endif