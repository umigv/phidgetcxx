#ifndef UMIGV_PHIDGETCXX_PHIDGET_H
#define UMIGV_PHIDGETCXX_PHIDGET_H

#include "phidgetcxx/channel_class.h"
#include "phidgetcxx/channel_subclass.h"
#include "phidgetcxx/device_class.h"
#include "phidgetcxx/device_id.h"
#include "phidgetcxx/exception.h"
#include "phidgetcxx/return_code.h"

#include <cstdint>
#include <chrono>

#include <gsl/gsl>
#include <phidget22.h>

namespace phidgetcxx {

class Phidget;

template <typename T>
class Reference {
public:
    friend Phidget;

    Reference& operator=(const Reference &other) {
        set(other.get());

        return *this;
    }

    Reference& operator=(const T &value) {
        set(value);

        return *this;
    }

    operator T() const {
        return get();
    }

private:
    using SetPtrT = void (Phidget::*)(const T&);
    using GetPtrT = T (Phidget::*)() const;

    constexpr Reference(Phidget &phidget, const SetPtrT set_ptr,
                        const GetPtrT get_ptr) noexcept
    : phidget_ptr_{ &phidget }, set_ptr_{ set_ptr }, get_ptr_{ get_ptr } { }

    T get() const {
        return ((*phidget_ptr_).*get_ptr_)();
    }

    void set(const T &value) {
        return ((*phidget_ptr_).*set_ptr_)(value);
    }

    gsl::not_null<Phidget*> phidget_ptr_;
    SetPtrT set_ptr_;
    GetPtrT get_ptr_;
};

// wrapper around the PhidgetHandle C type
class Phidget {
public:
    template <typename T>
    friend class Reference;

    Phidget() = default;

    ~Phidget();

    void release();

    void retain();

    bool is_attached() const;

    Reference<int> channel();

    int channel() const;

    ChannelClass channel_class() const;

    gsl::czstring_span<> channel_class_name() const;

    gsl::czstring_span<> channel_name() const;

    ChannelSubclass channel_subclass() const;

    void close();

    Reference<std::chrono::milliseconds> data_interval();

    std::chrono::milliseconds data_interval() const;

    std::uint32_t device_channel_count(ChannelClass channel_class) const;

    DeviceClass device_class() const;

    gsl::czstring_span<> device_class_name() const;

    DeviceId device_id() const;

    Reference<gsl::czstring_span<>> device_label();

    gsl::czstring_span<> device_label() const;

    gsl::czstring_span<> device_name() const;

    Reference<std::int32_t> device_serial_number();

    std::int32_t device_serial_number() const;

    gsl::czstring_span<> device_sku() const;

    int device_version() const;

    bool is_channel() const;

    bool is_local() const;

    void open();

    void open_wait_for_attachment(std::chrono::milliseconds timeout);

private:
    int get_channel() const;

    void set_channel(const int &channel);

    std::chrono::milliseconds get_data_interval() const;

    void set_data_interval(const std::chrono::milliseconds &interval);

    gsl::czstring_span<> get_device_label() const;

    void set_device_label(const gsl::czstring_span<> &label);

    std::int32_t get_device_serial_number() const;

    void set_device_serial_number(const std::int32_t &serial_number);

    PhidgetHandle handle_;
};

} // namespace phidgetcxx

#endif
