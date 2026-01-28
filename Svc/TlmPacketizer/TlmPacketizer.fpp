module Svc {
  port EnableSection (
      section: FwIndexType @< Section to enable (Primary, Secondary, etc...)
      enabled: Fw.Enabled @< Enable / Disable Section
  )
  
  @ A component for storing telemetry
  active component TlmPacketizer {
    enum RateLogic {
      SILENCED,
      EVERY_MAX,
      ON_CHANGE_MIN,
      ON_CHANGE_MIN_OR_EVERY_MAX,
    }

    
    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Packet send port
    output port PktSend: [NUM_CONFIGURABLE_TLMPACKETIZER_SECTIONS * (MAX_CONFIGURABLE_TLMPACKETIZER_GROUP + 1)] Fw.Com

    async input port controlIn: EnableSection

    @ Ping input port
    async input port pingIn: Svc.Ping

    @ Ping output port
    output port pingOut: Svc.Ping

    @ Run port for starting packet send cycle
    async input port Run: Svc.Sched

    @ Telemetry input port
    sync input port TlmRecv: Fw.Tlm

    @ Telemetry getter port
    sync input port TlmGet: Fw.TlmGet

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Command receive
    command recv port cmdIn

    @ Command registration
    command reg port cmdRegOut

    @ Command response
    command resp port cmdResponseOut

    @ Event
    event port eventOut

    @ Telemetry
    telemetry port tlmOut

    @ Text event
    text event port textEventOut

    @ Time get
    time get port timeGetOut

    # ----------------------------------------------------------------------
    # Commands
    # ----------------------------------------------------------------------

    @ Set telemetry send level
    async command SET_LEVEL(
                             level: FwChanIdType @< The I32 command argument
                           ) \
      opcode 0

    @ Force a packet to be sent
    async command SEND_PKT(
                            $id: U32 @< The packet ID
                          ) \
      opcode 1

    @ Enable / disable telemetry of a group on a section
    async command ENABLE_SECTION(
                                section: FwIndexType    @< section grouping to configure
                                enable: Fw.Enabled      @< Active Sending Group
                              ) \
      opcode 2

        @ Enable / disable telemetry of a group on a section
    async command ENABLE_GROUP(
                                section: FwIndexType    @< section grouping to configure
                                tlmGroup: FwChanIdType  @< Group Level
                                enable: Fw.Enabled      @< Active Sending Group
                              ) \
      opcode 3
    
    @ Force telemetering a group on a section, even if disabled
    async command FORCE_GROUP(
                                    section: FwIndexType    @< section grouping
                                    tlmGroup: FwChanIdType  @< Group Level
                                    enable: Fw.Enabled      @< Active Sending Group
                                  ) \
      opcode 4

    @ Set Min and Max Deltas between successive packets
    async command SET_GROUP_DELTAS(
                                    section: FwIndexType    @< section grouping
                                    tlmGroup: FwChanIdType  @< Group Level
                                    rateLogic: RateLogic    @< Rate Logic
                                    minDelta: U32
                                    maxDelta: U32
                                  ) \
      opcode 5

    

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ Telemetry channel is not part of a telemetry packet.
    event NoChan(
                  Id: FwChanIdType @< The telemetry ID
                ) \
      severity warning low \
      id 0 \
      format "Telemetry ID 0x{x} not packetized"

    @ Telemetry send level set
    event LevelSet(
                    $id: FwChanIdType @< The level
                  ) \
      severity activity high \
      id 1 \
      format "Telemetry send level to {}"

    @ Telemetry send level set
    event MaxLevelExceed(
                          level: FwChanIdType @< The level
                          max: FwChanIdType @< The max packet level
                        ) \
      severity warning low \
      id 2 \
      format "Requested send level {} higher than max packet level of {}"

    @ Packet manually sent
    event PacketSent(
                      $id: U32 @< The packet ID
                    ) \
      severity activity low \
      id 3 \
      format "Sent packet ID {}"

    @ Couldn't find the packet to send
    event PacketNotFound(
                          $id: U32 @< The packet ID
                        ) \
      severity warning low \
      id 4 \
      format "Could not find packet ID {}"

    event SectionUnconfigurable(
                                section: FwIndexType @< The Section
                                enable: Fw.Enabled @< Attempted Configuration
                               ) \
      severity warning low \
      id 5 \
      format "Section {} is unconfigurable and cannot be set to {}"
    
    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    @ Telemetry send level
    telemetry SendLevel: FwChanIdType id 0
  }

}
