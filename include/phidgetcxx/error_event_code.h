#ifndef UMIGV_PHIDGETCXX_ERROR_EVENT_CODE_H
#define UMIGV_PHIDGETCXX_ERROR_EVENT_CODE_H

#include <cstddef>

#include <phidget22.h>

namespace phidgetcxx {

enum class ErrorEventCode {
    BadVersion = EEPHIDGET_BADVERSION,
    Busy = EEPHIDGET_BUSY,
    Network = EEPHIDGET_NETWORK,
    Dispatch = EEPHIDGET_DISPATCH,
    Failure = EEPHIDGET_FAILURE,
    Ok = EEPHIDGET_OK,
    Overrun = EEPHIDGET_OVERRUN,
    PacketLost = EEPHIDGET_PACKETLOST,
    Wrap = EEPHIDGET_WRAP,
    OverTemp = EEPHIDGET_OVERTEMP,
    OverCurrent = EEPHIDGET_OVERCURRENT,
    OutOfRange = EEPHIDGET_OUTOFRANGE,
    BadPower = EEPHIDGET_BADPOWER,
    Saturation = EEPHIDGET_SATURATION,
    OverVoltage = EEPHIDGET_OVERVOLTAGE,
    Failsafe = EEPHIDGET_FAILSAFE,
    VoltageError = EEPHIDGET_VOLTAGEERROR,
    EnergyDump = EEPHIDGET_ENERGYDUMP,
    MotorStall = EEPHIDGET_MOTORSTALL
};

constexpr ErrorEventCode as_cxx(const Phidget_ErrorEventCode code) noexcept {
    return static_cast<ErrorEventCode>(code);
}

} // namespace phidgetcxx

#endif
