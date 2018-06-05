#ifndef UMIGV_PHIDGETCXX_CHANNEL_SUBCLASS_H
#define UMIGV_PHIDGETCXX_CHANNEL_SUBCLASS_H

#include <cstddef>

#include <phidget22.h>

namespace phidgetcxx {

enum class ChannelSubclass {
    None = PHIDCHSUBCLASS_NONE,
    DigitalOutputDutyCycle = PHIDCHSUBCLASS_DIGITALOUTPUT_DUTY_CYCLE,
    DigitalOutputLedDriver = PHIDCHSUBCLASS_DIGITALOUTPUT_LED_DRIVER,
    TemperatureSensorRtd = PHIDCHSUBCLASS_TEMPERATURESENSOR_RTD,
    TemperatureSensorThermocouple =
        PHIDCHSUBCLASS_TEMPERATURESENSOR_THERMOCOUPLE,
    VoltageInputSensorPort = PHIDCHSUBCLASS_VOLTAGEINPUT_SENSOR_PORT,
    VoltageRatioInputSensorPort = PHIDCHSUBCLASS_VOLTAGERATIOINPUT_SENSOR_PORT,
    VoltageRatioInputBridge = PHIDCHSUBCLASS_VOLTAGERATIOINPUT_BRIDGE,
    LcdGraphic = PHIDCHSUBCLASS_LCD_GRAPHIC,
    LcdText = PHIDCHSUBCLASS_LCD_TEXT,
    EncoderModeSettable = PHIDCHSUBCLASS_ENCODER_MODE_SETTABLE,
    RcServoEmbedded = PHIDCHSUBCLASS_RCSERVO_EMBEDDED
};

constexpr ChannelSubclass
as_cxx(Phidget_ChannelSubclass channel_subclass) noexcept {
    return static_cast<ChannelSubclass>(channel_subclass);
}

} // namespace phidgetcxx

#endif
