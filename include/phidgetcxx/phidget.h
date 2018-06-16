#ifndef UMIGV_PHIDGETCXX_PHIDGET_H
#define UMIGV_PHIDGETCXX_PHIDGET_H

#include "phidgetcxx/channel_class.h"
#include "phidgetcxx/channel_subclass.h"
#include "phidgetcxx/device_class.h"
#include "phidgetcxx/device_id.h"
#include "phidgetcxx/error_event_code.h"
#include "phidgetcxx/exception.h"
#include "phidgetcxx/phidget_fwd.h"
#include "phidgetcxx/retained_phidget_fwd.h"
#include "phidgetcxx/return_code.h"

#include <cstdint>
#include <chrono>
#include <functional>

#include <gsl/gsl>
#include <phidget22.h>

namespace phidgetcxx {

using AttachHandlerT = std::function<void(Phidget&)>;
using DetachHandlerT = std::function<void(Phidget&)>;
using ErrorHandlerT = std::function<void(Phidget&, ErrorEventCode,
                                         gsl::czstring_span<>)>;
using PropertyChangeHandlerT = std::function<void(Phidget&,
                                                  gsl::czstring_span<>)>;

struct LabelAnyTag { };

extern const std::int32_t SERIAL_NUMBER_ANY;
extern const int HUB_PORT_ANY;
extern const int CHANNEL_ANY;
extern const LabelAnyTag LABEL_ANY;
extern const std::chrono::milliseconds TIMEOUT_INFINITE;
extern const std::chrono::milliseconds TIMEOUT_DEFAULT;

template <typename T>
class Reference {
public:
    friend Phidget;

    Reference& operator=(const Reference &other) {
        set(other.get());

        return *this;
    }

    Reference& operator=(const T value) {
        set(value);

        return *this;
    }

    operator T() const {
        return get();
    }

private:
    using SetPtrT = void (Phidget::*)(T);
    using GetPtrT = T (Phidget::*)() const;

    constexpr Reference(Phidget &phidget, const SetPtrT set_ptr,
                        const GetPtrT get_ptr) noexcept
    : phidget_ptr_{ &phidget }, set_ptr_{ set_ptr }, get_ptr_{ get_ptr } { }

    T get() const {
        return ((*phidget_ptr_).*get_ptr_)();
    }

    void set(const T value) {
        return ((*phidget_ptr_).*set_ptr_)(value);
    }

    gsl::not_null<Phidget*> phidget_ptr_;
    SetPtrT set_ptr_;
    GetPtrT get_ptr_;
};

class LabelReference {
public:
    friend Phidget;

    LabelReference& operator=(const LabelReference &other);

    LabelReference& operator=(gsl::czstring_span<> label);

    LabelReference& operator=(LabelAnyTag);

    operator gsl::czstring_span<>() const;

private:
    constexpr LabelReference(Phidget &phidget) noexcept
    : phidget_ptr_{ &phidget } { }

    gsl::czstring_span<> get() const;

    void set(gsl::czstring_span<> label);

    gsl::not_null<Phidget*> phidget_ptr_;
};

// wrapper around the PhidgetHandle C type
class Phidget {
public:
    template <typename T>
    friend class Reference;
    friend LabelReference;
    friend RetainedPhidget;

    // gsl::not_null will throw if !handle
    explicit Phidget(PhidgetHandle handle);

    Phidget(std::nullptr_t) = delete;

    ~Phidget();

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

    LabelReference device_label();

    gsl::czstring_span<> device_label() const;

    gsl::czstring_span<> device_name() const;

    Reference<std::int32_t> device_serial_number();

    std::int32_t device_serial_number() const;

    gsl::czstring_span<> device_sku() const;

    int device_version() const;

    RetainedPhidget hub() const;

    Reference<int> hub_port();

    int hub_port() const;

    int hub_port_count() const;

    bool is_channel() const;

    Reference<bool> is_local();

    bool is_local() const;

    Reference<bool> is_remote();

    bool is_remote() const;

    void open();

    void open_wait_for_attachment(std::chrono::milliseconds timeout);

    RetainedPhidget parent() const;

    gsl::czstring_span<> server_hostname() const;

    Reference<gsl::czstring_span<>> server_name();

    gsl::czstring_span<> server_name() const;

    gsl::czstring_span<> server_peer_name() const;

    void write_device_label(gsl::czstring_span<> device_label);

    AttachHandlerT attach_handler;
    DetachHandlerT detach_handler;
    ErrorHandlerT error_handler;
    PropertyChangeHandlerT property_change_handler;

private:
    int get_channel() const;

    void set_channel(int channel);

    std::chrono::milliseconds get_data_interval() const;

    void set_data_interval(std::chrono::milliseconds interval);

    gsl::czstring_span<> get_device_label() const;

    void set_device_label(gsl::czstring_span<> label);

    void set_device_label(LabelAnyTag);

    std::int32_t get_device_serial_number() const;

    void set_device_serial_number(std::int32_t serial_number);

    int get_hub_port() const;

    void set_hub_port(int port);

    bool get_is_local() const;

    void set_is_local(bool is_local);

    bool get_is_remote() const;

    void set_is_remote(bool is_remote);

    gsl::czstring_span<> get_server_name() const;

    void set_server_name(gsl::czstring_span<> server_name);

    static void attach_glue(PhidgetHandle, void *self);

    static void detach_glue(PhidgetHandle, void *self);

    static void error_glue(PhidgetHandle, void *self,
                           Phidget_ErrorEventCode code,
                           gsl::czstring<> description);

    static void property_change_glue(PhidgetHandle, void *self,
                                     gsl::czstring<> name);

    void do_attach_handler();

    void do_detach_handler();

    void do_error_handler(ErrorEventCode code,
                          gsl::czstring_span<> description);

    void do_property_change_handler(gsl::czstring_span<> name);

    gsl::not_null<PhidgetHandle> handle_;
};

} // namespace phidgetcxx

#endif
