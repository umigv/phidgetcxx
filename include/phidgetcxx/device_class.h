#ifndef UMIGV_PHIDGETCXX_DEVICE_CLASS_H
#define UMIGV_PHIDGETCXX_DEVICE_CLASS_H

#include <cstddef> // for phidget22.h

#include <phidget22.h>

namespace phidgetcxx {

enum class DeviceClass {
    Accelerometer = PHIDCLASS_ACCELEROMETER,
    AdvancedServo = PHIDCLASS_ADVANCEDSERVO,
    Analog = PHIDCLASS_ANALOG,
    Bridge = PHIDCLASS_BRIDGE,
    Encoder = PHIDCLASS_ENCODER,
    FrequencyCounter = PHIDCLASS_FREQUENCYCOUNTER,
    Gps = PHIDCLASS_GPS,
    Hub = PHIDCLASS_HUB,
    InterfaceKit = PHIDCLASS_INTERFACEKIT,
    Ir = PHIDCLASS_IR,
    Led = PHIDCLASS_LED,
    MeshDongle = PHIDCLASS_MESHDONGLE,
    MotorControl = PHIDCLASS_MOTORCONTROL,
    PhSensor = PHIDCLASS_PHSENSOR,
    Rfid = PHIDCLASS_RFID,
    Servo = PHIDCLASS_SERVO,
    Spatial = PHIDCLASS_SPATIAL,
    Stepper = PHIDCLASS_STEPPER,
    TemperatureSensor = PHIDCLASS_TEMPERATURESENSOR,
    TextLcd = PHIDCLASS_TEXTLCD,
    Vint = PHIDCLASS_VINT,
    Dictionary = PHIDCLASS_DICTIONARY
};

constexpr DeviceClass as_cxx(const Phidget_DeviceClass device_class) noexcept {
    return static_cast<DeviceClass>(device_class);
}

} // namespace phidgetcxx

#endif
