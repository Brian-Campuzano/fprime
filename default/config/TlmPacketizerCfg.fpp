# ======================================================================
# TlmPacketizerCfg.fpp
# Constants for configuring TlmPacketizer Send Logic Levels
# ======================================================================
module Svc {
    @ The number of sections of ports (Primary = 0, Secondary = 1, etc...)
    constant NUM_CONFIGURABLE_TLMPACKETIZER_SECTIONS = 3;

    @ Greatest packet group
    constant MAX_CONFIGURABLE_TLMPACKETIZER_GROUP = 3;

    constant NUM_CONFIGURABLE_TLMPACKETIZER_GROUPS = MAX_CONFIGURABLE_TLMPACKETIZER_GROUP + 1;
}
