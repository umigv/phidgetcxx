#ifndef UMIGV_PHIDGETCXX_CHANNEL_CLASS_H
#define UMIGV_PHIDGETCXX_CHANNEL_CLASS_H

#include <cstddef> // to fix a compiler error in <phidget22.h>

#include <phidget22.h>

namespace phidgetcxx {

enum class ChannelClass {
    Accelerometer = PHIDCHCLASS_ACCELEROMETER,
    CurrentInput = PHIDCHCLASS_CURRENTINPUT,
    DataAdapter = PHIDCHCLASS_DATAADAPTER,
    DcMotor = PHIDCHCLASS_DCMOTOR,
    DigitalInput = PHIDCHCLASS_DIGITALINPUT,
    DigitalOutput = PHIDCHCLASS_DIGITALOUTPUT,
    DistanceSensor = PHIDCHCLASS_DISTANCESENSOR,
    Encoder = PHIDCHCLASS_ENCODER,
    FrequencyCounter = PHIDCHCLASS_FREQUENCYCOUNTER,
    Gps = PHIDCHCLASS_GPS,
    Lcd = PHIDCHCLASS_LCD,
    Gyroscope = PHIDCHCLASS_GYROSCOPE,
    Hub = PHIDCHCLASS_HUB,
    CapacitiveTouch = PHIDCHCLASS_HUB,
    HumiditySensor = PHIDCHCLASS_HUMIDITYSENSOR,
    Ir = PHIDCHCLASS_IR,
    LightSensor = PHIDCHCLASS_LIGHTSENSOR,
    Magnetometer = PHIDCHCLASS_MAGNETOMETER,
    MeshDongle = PHIDCHCLASS_MESHDONGLE,
    PhSensor = PHIDCHCLASS_PHSENSOR,
    PowerGuard = PHIDCHCLASS_POWERGUARD,
    PressureSensor = PHIDCHCLASS_PRESSURESENSOR,
    RcServo = PHIDCHCLASS_RCSERVO,
    ResistanceInput = PHIDCHCLASS_RESISTANCEINPUT,
    Rfid = PHIDCHCLASS_RFID,
    SoundSensor = PHIDCHCLASS_SOUNDSENSOR,
    Spatial = PHIDCHCLASS_SPATIAL,
    Stepper = PHIDCHCLASS_STEPPER,
    TemperatureSensor = PHIDCHCLASS_TEMPERATURESENSOR,
    VoltageInput = PHIDCHCLASS_VOLTAGEINPUT,
    VoltageOutput = PHIDCHCLASS_VOLTAGEOUTPUT,
    VoltageRatioInput = PHIDCHCLASS_VOLTAGERATIOINPUT,
    MotorPositionController = PHIDCHCLASS_MOTORPOSITIONCONTROLLER,
    BlDcMotor = PHIDCHCLASS_BLDCMOTOR,
    Dictionary = PHIDCHCLASS_DICTIONARY
};

constexpr ChannelClass
as_cxx(const Phidget_ChannelClass channel_class) noexcept {
    return static_cast<ChannelClass>(channel_class);
}

} // namespace phidgetcxx

#endif
