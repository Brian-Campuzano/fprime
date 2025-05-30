/*
 * PrmBuffer.hpp
 *
 *  Created on: Sep 10, 2012
 *      Author: ppandian
 */

/*
 * Description:
 * This object contains the ParamBuffer type, used for storing parameters
 */
#ifndef FW_PRM_BUFFER_HPP
#define FW_PRM_BUFFER_HPP

#include <Fw/FPrimeBasicTypes.hpp>
#include <Fw/Types/Serializable.hpp>
#include <Fw/Types/SerIds.hpp>

#include "Fw/Types/StringBase.hpp"


namespace Fw {

    static_assert(FW_PARAM_BUFFER_MAX_SIZE >= StringBase::BUFFER_SIZE(FW_PARAM_STRING_MAX_SIZE),
                  "param string must fit into param buffer");

    class ParamBuffer final : public SerializeBufferBase {
        public:

            enum {
                SERIALIZED_TYPE_ID = FW_TYPEID_PRM_BUFF,
                SERIALIZED_SIZE = FW_PARAM_BUFFER_MAX_SIZE + sizeof(FwBuffSizeType)
            };

            ParamBuffer(const U8 *args, FwSizeType size);
            ParamBuffer();
            ParamBuffer(const ParamBuffer& other);
            virtual ~ParamBuffer();
            ParamBuffer& operator=(const ParamBuffer& other);

            FwSizeType getBuffCapacity() const; // !< returns capacity, not current size, of buffer
            U8* getBuffAddr();
            const U8* getBuffAddr() const;

        private:
            U8 m_bufferData[FW_PARAM_BUFFER_MAX_SIZE]; // command argument buffer
    };

}

#endif
