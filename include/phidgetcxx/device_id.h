#ifndef UMIGV_PHIDGETCXX_DEVICE_ID_H
#define UMIGV_PHIDGETCXX_DEVICE_ID_H

#include <cstddef>

#include <phidget22.h>

namespace phidgetcxx {

// TODO: the rest of the id's
enum class DeviceId {
    Nothing = PHIDID_NOTHING,
    InterfaceKit_4_8_8 = PHIDID_INTERFACEKIT_4_8_8,
    N1000 = PHIDID_1000,
    N1001 = PHIDID_1001,
    N1002 = PHIDID_1002,
    N1008 = PHIDID_1008,
    N1041 = PHIDID_1041,
    N1042 = PHIDID_1042,
    N1043 = PHIDID_1043,
    N1044 = PHIDID_1044,
    N1047 = PHIDID_1047,
    N1057 = PHIDID_1057,
    Enc_1000 = PHIDID_ENC1000,
    Hub_0000 = PHIDID_HUB0000,
    Hub_0004 = PHIDID_HUB0004,
    Mot_1100 = PHIDID_MOT1100,
    Mot_1101 = PHIDID_MOT1101,
};

constexpr DeviceId as_cxx(const Phidget_DeviceID id) noexcept {
    return static_cast<DeviceId>(id);
}

} // namespace phidgetcxx

#endif
