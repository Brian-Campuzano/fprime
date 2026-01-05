module Svc {
module Ccsds {

    @ Enum representing an error during framing/deframing in the CCSDS protocols
    enum FrameError: U8 {
        SP_INVALID_LENGTH = 0
        TC_INVALID_SCID = 1
        TC_INVALID_LENGTH = 2
        TC_INVALID_VCID = 3
        TC_INVALID_CRC = 4
    }

    # ------------------------------------------------
    # SpacePacket
    # ------------------------------------------------ 
    @ Describes the frame header format for the SpacePacket communications protocol
    struct SpacePacketHeader {
        packetIdentification: U16,   @< 3 bits PVN | 1 bit Pkt type | 1 bit Sec Hdr | 11 bit APID
        packetSequenceControl: U16,  @< 2 bits Sequence flags | 14 bits packet seq count (or name)
        packetDataLength: U16        @< 16 bits length
    }
    @ Masks and Offsets for deserializing individual sub-fields in SpacePacket headers
    module SpacePacketSubfields {
        # packetIdentification sub-fields     |--- 16 bits ---|
        constant PvnMask        = 0xE000  @< 0b1110000000000000
        constant PktTypeMask    = 0x1000  @< 0b0001000000000000
        constant SecHdrMask     = 0x0800  @< 0b0000100000000000
        constant ApidMask       = 0x07FF  @< 0b0000011111111111
        constant PvnOffset      = 13 
        constant PktTypeOffset  = 12 
        constant SecHdrOffset   = 11 
        # packetSequenceControl sub-fields
        constant SeqFlagsMask   = 0xC000  @< 0b1100000000000000
        constant SeqCountMask   = 0x3FFF  @< 0b0011111111111111
        constant SeqFlagsOffset = 14 
        # Widths
        constant ApidWidth      = 11
        constant SeqCountWidth  = 14
    }

    # ------------------------------------------------
    # TC
    # ------------------------------------------------ 
    @ Describes the frame header format for a Telecommand (TC) Transfer Frame header
    struct TCHeader {
        flagsAndScId: U16,    @< 2 bits Frame V. | 1 bit bypass | 1 bit ctrl | 2 bit reserved | 10 bits spacecraft ID
        vcIdAndLength: U16,   @< 6 bits Virtual Channel ID | 10 bits Frame Length
        frameSequenceNum: U8  @< 8 bits Frame Sequence Number
    }
    @ Describes the frame trailer format for a Telecommand (TC) Transfer Frame
    struct TCTrailer {
        fecf: U16             @< 16 bit Frame Error Control Field (CRC16)
    }
    @ Masks and Offsets for deserializing individual sub-fields in TC headers
    module TCSubfields {
        # flagsAndScId sub-fields
        constant FrameVersionMask = 0xC000  @< 0b1100000000000000
        constant BypassFlagMask   = 0x2000  @< 0b0010000000000000
        constant ControlFlagMask  = 0x1000  @< 0b0001000000000000
        constant ReservedMask     = 0x0C00  @< 0b0000110000000000
        constant SpacecraftIdMask = 0x03FF  @< 0b0000001111111111
        constant BypassFlagOffset = 13
        # vcIdAndLength sub-fields
        constant VcIdMask         = 0xFC00  @< 0b1111110000000000
        constant FrameLengthMask  = 0x03FF  @< 0b0000001111111111
        constant VcIdOffset       = 10
    }

    # ------------------------------------------------
    # TM
    # ------------------------------------------------ 
    @ Describes the frame header format for a Telemetry (TM) Transfer Frame header
    struct TMHeader {
        globalVcId: U16,         @< 2 bit Frame Version | 10 bit spacecraft ID | 3 bit virtual channel ID | 1 bit OCF flag
        masterFrameCount: U8,    @< 8 bit Master Channel Frame Count
        virtualFrameCount: U8,   @< 8 bit Virtual Channel Frame Count
        dataFieldStatus: U16     @< 1 bit 2nd Header | 1 bit sync | 1 bit pkt order | 2 bit seg len | 11 bit header ptr
    }
    @ Describes the frame trailer format for a Telemetry (TM) Transfer Frame
    struct TMTrailer {
        fecf: U16             @< 16 bit Frame Error Control Field (CRC16)
    }
    @ Offsets for serializing individual sub-fields in TM headers
    module TMSubfields {
        constant frameVersionOffset = 14
        constant spacecraftIdOffset = 4
        constant virtualChannelIdOffset = 1
        constant segLengthOffset = 11
    }

    # ------------------------------------------------
    # CFDP
    # ------------------------------------------------ 
    enum CfdpStatus {
        SUCCESS @< CFDP operation has been succesfull
        ERROR @< Generic CFDP error return code
        PDU_METADATA_ERROR @< Invalid metadata PDU
        SHORT_PDU_ERROR @< PDU too short
        REC_PDU_FSIZE_MISMATCH_ERROR @< Receive PDU: EOF file size mismatch
        REC_PDU_BAD_EOF_ERROR @< Receive PDU: Invalid EOF packet
        SEND_PDU_NO_BUF_AVAIL_ERROR @< Send PDU: No send buffer available, throttling limit reached
        SEND_PDU_ERROR @< Send PDU: Send failed
    }

    enum CfdpFrozen {
        NOT_FROZEN @< CFDP channel operations are executing nominally
        FROZEN @< CFDP channel operations are frozen
    }

    @ Values for CFDP file transfer class
    @
    @ The CFDP specification prescribes two classes/modes of file
    @ transfer protocol operation - unacknowledged/simple or
    @ acknowledged/reliable.
    @
    @ Defined per section 7.1 of CCSDS 727.0-B-5
    enum CfdpClass {
        CLASS_1 = 0 @< CFDP class 1 - Unreliable transfer
        CLASS_2 = 1 @< CFDP class 2 - Reliable transfer
    }

    @ CFDP queue identifiers
    enum CfdpQueueId {
        PEND = 0, @< first one on this list is active
        TXA = 1
        TXW = 2
        RX = 3
        HIST = 4
        HIST_FREE = 5
        FREE = 6
        NUM = 7
    }

    @ Structure representing base CFDP PDU header
    @ CF_CFDP_PduHeader_t for encoded form
    struct CfdpLogicalPduHeader {
        version: U8 @< Version of the protocol
        pdu_type: U8 @< File Directive (0) or File Data (1)
        direction: U8 @< Toward Receiver (0) or Toward Sender (1)
        txm_mode: U8 @< Acknowledged (0) or Unacknowledged (1)
        crc_flag: U8 @< CRC not present (0) or CRC present (1)
        large_flag: U8 @< Small/32-bit size (0) or Large/64-bit size (1)

        segmentation_control: U8 @< Record boundaries not preserved (0) or preserved (1)
        eid_length: U8 @< Length of encoded entity IDs, in octets (NOT size of logical value)
        segment_meta_flag: U8 @< Segment Metatdata not present (0) or Present (1)
        txn_seq_length: U8 @< Length of encoded sequence number, in octets (NOT size of logical value)

        header_encoded_length: U16 @< Length of the encoded PDU header, in octets (NOT sizeof struct)
        data_encoded_length: U16 @< Length of the encoded PDU data, in octets

        source_eid: CfdpEntityId @< Source entity ID (normalized)
        destination_eid: CfdpEntityId @< Destination entity ID (normalized)
        sequence_num: CfdpTransactionSeq @< Sequence number (normalized)
    }

    @< Structure for configuration parameters for a single CFDP channel
    struct CfdpChannelParams {
        ack_limit: U8 @< number of times to retry ACK (for ex, send FIN and wait for fin-ack)
        nack_limit: U8 @< number of times to retry NAK before giving up (resets on a single response
        ack_timer: U32 @< Acknowledge timer in seconds
        inactivity_timer: U32 @< Inactivity timer in seconds
        dequeue_enabled: Fw.Enabled @< if enabled, then the channel will make pending transactions active
        move_dir: string size CfdpManagerMaxFileSize @< Move directory if not empty
    }

    @< Struture for the configured array of CFDP channels
    array CfdpChannelArrayParams = [CfdpManagerNumChannels] CfdpChannelParams
}
}
