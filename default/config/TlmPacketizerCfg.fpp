# ======================================================================
# TlmPacketizerCfg.fpp
# Constants for configuring TlmPacketizer Send Logic Levels
# ======================================================================
module Svc {
    @ Configurable enum supporting multiple resampled telemetry sections
    enum TelemetrySection {
        PRIMARY,
        SECONDARY,
        TERTIARY,
        NUM_SECTIONS,     @< Counter, leave as last element.
    }

    @ Greatest packet group
    constant MAX_CONFIGURABLE_TLMPACKETIZER_GROUP = 3;

    constant NUM_CONFIGURABLE_TLMPACKETIZER_GROUPS = MAX_CONFIGURABLE_TLMPACKETIZER_GROUP + 1;
}
