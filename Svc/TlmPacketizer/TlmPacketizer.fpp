module Svc {
  port EnableSection (
      section: FwIndexType @< Section to enable (Primary, Secondary, etc...)
      enabled: Fw.Enabled @< Enable / Disable Section
  )
  @ A component for storing telemetry
  active component TlmPacketizer {
    # ----------------------------------------------------------------------
    # Types
    # ----------------------------------------------------------------------
    
    enum RateLogic {
      SILENCED,
      EVERY_MAX,
      ON_CHANGE_MIN,
      ON_CHANGE_MIN_OR_EVERY_MAX,
    }
    
    struct GroupConfig {
      enabled: Fw.Enabled       @< Enable / Disable Telemetry Output
      forceEnabled: Fw.Enabled  @< Force Enable / Disable Telemetry Output
      rateLogic: RateLogic      @< Rate Logic Configuration
      min: U32                  @< Minimum Sched Ticks 
      max: U32                  @< Maximum Sched Ticks
    } default {
      enabled = Fw.Enabled.ENABLED
      forceEnabled = Fw.Enabled.DISABLED
      rateLogic =  RateLogic.ON_CHANGE_MIN
      min = 0
      max = 0
    }

    array GroupConfigs = [NUM_CONFIGURABLE_TLMPACKETIZER_GROUPS] GroupConfig
    array SectionConfigs = [NUM_CONFIGURABLE_TLMPACKETIZER_SECTIONS] GroupConfigs
    array SectionEnabled = [NUM_CONFIGURABLE_TLMPACKETIZER_SECTIONS] Fw.Enabled default Fw.Enabled.ENABLED

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Packet send port
    output port PktSend: [NUM_CONFIGURABLE_TLMPACKETIZER_SECTIONS * NUM_CONFIGURABLE_TLMPACKETIZER_GROUPS] Fw.Com

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
                            $id: U32              @< The packet ID
                            section: FwIndexType  @< Section to emit packet
                          ) \
      opcode 1

    @ Enable / disable telemetry of a group on a section
    async command ENABLE_SECTION(
                                section: FwIndexType    @< Section grouping to configure
                                enable: Fw.Enabled      @< Section enabled or disabled
                              ) \
      opcode 2

        @ Enable / disable telemetry of a group on a section
    async command ENABLE_GROUP(
                                section: FwIndexType    @< Section grouping to configure
                                tlmGroup: FwChanIdType  @< Group Identifier
                                enable: Fw.Enabled      @< Section enabled or disabled
                              ) \
      opcode 3
    
    @ Force telemetering a group on a section, even if disabled
    async command FORCE_GROUP(
                                    section: FwIndexType    @< Section grouping
                                    tlmGroup: FwChanIdType  @< Group Identifier
                                    enable: Fw.Enabled      @< Section enabled or disabled
                                  ) \
      opcode 4

    @ Set Min and Max Deltas between successive packets
    async command SET_GROUP_DELTAS(
                                    section: FwIndexType    @< Section grouping
                                    tlmGroup: FwChanIdType  @< Group Identifier
                                    rateLogic: RateLogic    @< Rate Logic
                                    minDelta: U32           @< Minimum Sched Ticks to send packets on updates
                                    maxDelta: U32           @< Maximum Sched Ticks to send packets
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
    telemetry GroupConfigs: SectionConfigs id 0
    telemetry SectionEnabled: SectionEnabled id 1

  }

}
