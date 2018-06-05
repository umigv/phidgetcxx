#ifndef UMIGV_PHIDGETCXX_RETURN_CODE_H
#define UMIGV_PHIDGETCXX_RETURN_CODE_H

#include <cstddef> // to fix a compiler error in <phidget22.h>

#include <phidget22.h>

namespace phidgetcxx {

enum class ReturnCode {
    Ok = EPHIDGET_OK,
    Perm = EPHIDGET_PERM,
    NoEnt = EPHIDGET_NOENT,
    Timeout = EPHIDGET_TIMEOUT,
    KeepAlive = EPHIDGET_KEEPALIVE,
    Interrupted = EPHIDGET_INTERRUPTED,
    Io = EPHIDGET_IO,
    NoMemory = EPHIDGET_NOMEMORY,
    Access = EPHIDGET_ACCESS,
    Fault = EPHIDGET_FAULT,
    Busy = EPHIDGET_BUSY,
    Exist = EPHIDGET_EXIST,
    NotDir = EPHIDGET_NOTDIR,
    IsDir = EPHIDGET_ISDIR,
    Invalid = EPHIDGET_INVALID,
    NFile = EPHIDGET_NFILE,
    MFile = EPHIDGET_MFILE,
    NoSpc = EPHIDGET_NOSPC,
    FBig = EPHIDGET_FBIG,
    RoFs = EPHIDGET_ROFS,
    Unsupported = EPHIDGET_UNSUPPORTED,
    InvalidArg = EPHIDGET_INVALIDARG,
    Again = EPHIDGET_AGAIN,
    NotEmpty = EPHIDGET_NOTEMPTY,
    Unexpected = EPHIDGET_UNEXPECTED,
    Duplicate = EPHIDGET_DUPLICATE,
    BadPassword = EPHIDGET_BADPASSWORD,
    NetUnavail = EPHIDGET_NETUNAVAIL,
    ConnRef = EPHIDGET_CONNREF,
    ConnReset = EPHIDGET_CONNRESET,
    HostUnreach = EPHIDGET_HOSTUNREACH,
    NoDev = EPHIDGET_NODEV,
    WrongDevice = EPHIDGET_WRONGDEVICE,
    Pipe = EPHIDGET_PIPE,
    Resolv = EPHIDGET_RESOLV,
    UnknownVal = EPHIDGET_UNKNOWNVAL,
    NotAttached = EPHIDGET_NOTATTACHED,
    InvalidPacket = EPHIDGET_INVALIDPACKET,
    TooBig = EPHIDGET_2BIG,
    BadVersion = EPHIDGET_BADVERSION,
    Closed = EPHIDGET_CLOSED,
    NotConfigured = EPHIDGET_NOTCONFIGURED,
    Eof = EPHIDGET_EOF
};

constexpr ReturnCode as_return_code(const PhidgetReturnCode code) noexcept {
    return static_cast<ReturnCode>(code);
}

} // namespace phidgetcxx

#endif
