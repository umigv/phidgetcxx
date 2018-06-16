#include "phidgetcxx/phidget.h"

#include "globals.h"
#include "phidgetcxx/common.h"
#include "phidgetcxx/retained_phidget.h"

#include <climits>
#include <cstring>
#include <limits>

namespace phidgetcxx {
namespace detail {

static std::int64_t add_ref(const PhidgetHandle handle) {
    const auto map_ref = detail::phidget_map();
    auto &map = map_ref.get();

    return ++map[handle].num_refs;
}

static std::int64_t remove_ref(const PhidgetHandle handle) {
    const auto map_ref = detail::phidget_map();
    auto &map = map_ref.get();

    return --map[handle].num_refs;
}

} // namespae detail

constexpr std::int32_t SERIAL_NUMBER_ANY = PHIDGET_SERIALNUMBER_ANY;
constexpr int HUB_PORT_ANY = PHIDGET_HUBPORT_ANY;
constexpr int CHANNEL_ANY = PHIDGET_CHANNEL_ANY;
constexpr LabelAnyTag LABEL_ANY{ };
constexpr std::chrono::milliseconds TIMEOUT_INFINITE{ PHIDGET_TIMEOUT_INFINITE };
constexpr std::chrono::milliseconds TIMEOUT_DEFAULT{ PHIDGET_TIMEOUT_DEFAULT };

LabelReference& LabelReference::operator=(const LabelReference &other) {
    set(other.get());

    return *this;
}

LabelReference& LabelReference::operator=(const gsl::czstring_span<> label) {
    set(label);

    return *this;
}

LabelReference& LabelReference::operator=(LabelAnyTag) {
    phidget_ptr_->set_device_label(LabelAnyTag{ });

    return *this;
}

LabelReference::operator gsl::czstring_span<>() const {
    return get();
}

gsl::czstring_span<> LabelReference::get() const {
    return phidget_ptr_->get_device_label();
}

void LabelReference::set(const gsl::czstring_span<> label) {
    phidget_ptr_->set_device_label(label);
}

Phidget::Phidget(const Phidget &other) : handle_{ other.handle_ } {
    detail::add_ref(handle_);
}

Phidget::Phidget(const PhidgetHandle handle) : handle_{ handle } {
    detail::add_ref(handle_);
}

Phidget& Phidget::operator=(const Phidget &other) {
    if (this == &other) {
        return *this;
    }

    detail::remove_ref(handle_);
    handle_ = other.handle_;
    detail::add_ref(handle_);

    return *this;
}

Phidget::~Phidget() {
    if (!detail::remove_ref(handle_)) {
         const auto map_ref = detail::phidget_map();
         auto &map = map_ref.get();

         map.erase(handle_);
    }

    // this is bad style
    if (is_attached()) {
        close();
    }
}

bool Phidget::is_attached() const {
    int is_attached;
    const auto ret = as_cxx(Phidget_getAttached(handle_, &is_attached));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::is_attached", ret };
    }

    return static_cast<bool>(is_attached);
}

Reference<int> Phidget::channel() {
    return { *this, &Phidget::set_channel, &Phidget::get_channel };
}

int Phidget::channel() const {
    return get_channel();
}

ChannelClass Phidget::channel_class() const {
    Phidget_ChannelClass channel_class;
    const auto ret = as_cxx(Phidget_getChannelClass(handle_, &channel_class));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::channel_class", ret };
    }

    return as_cxx(channel_class);
}

gsl::czstring_span<> Phidget::channel_class_name() const {
    gsl::czstring<> name;
    const auto ret = as_cxx(Phidget_getChannelClassName(handle_, &name));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::channel_class_name", ret };
    }

    return as_span(gsl::not_null<gsl::czstring<>>{ name });
}

gsl::czstring_span<> Phidget::channel_name() const {
    gsl::czstring<> name;
    const auto ret = as_cxx(Phidget_getChannelName(handle_, &name));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::channel_name", ret };
    }

    return as_span(gsl::not_null<gsl::czstring<>>{ name });
}

ChannelSubclass Phidget::channel_subclass() const {
    Phidget_ChannelSubclass subclass;
    const auto ret = as_cxx(Phidget_getChannelSubclass(handle_, &subclass));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::channel_subclass", ret };
    }

    return as_cxx(subclass);
}

void Phidget::close() {
    const auto ret = as_cxx(Phidget_close(handle_));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::close", ret };
    }
}

Reference<std::chrono::milliseconds> Phidget::data_interval() {
    return { *this, &Phidget::set_data_interval, &Phidget::get_data_interval };
}

std::chrono::milliseconds Phidget::data_interval() const {
    return get_data_interval();
}

std::uint32_t
Phidget::device_channel_count(const ChannelClass channel_class) const {
    const auto channel_class_c =
        static_cast<Phidget_ChannelClass>(channel_class);
    std::uint32_t channel_count;
    const auto ret =
        as_cxx(Phidget_getDeviceChannelCount(handle_, channel_class_c,
                                             &channel_count));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::device_channel_count", ret };
    }

    return channel_count;
}

DeviceClass Phidget::device_class() const {
    Phidget_DeviceClass class_c;
    const auto ret = as_cxx(Phidget_getDeviceClass(handle_, &class_c));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::device_class", ret };
    }

    return as_cxx(class_c);
}

gsl::czstring_span<> Phidget::device_class_name() const {
    gsl::czstring<> name;
    const auto ret = as_cxx(Phidget_getDeviceClassName(handle_, &name));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::device_class_name", ret };
    }

    return as_span(gsl::not_null<gsl::czstring<>>{ name });
}

DeviceId Phidget::device_id() const {
    Phidget_DeviceID id;
    const auto ret = as_cxx(Phidget_getDeviceID(handle_, &id));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::device_id", ret };
    }

    return as_cxx(id);
}

LabelReference Phidget::device_label() {
    return { *this };
}

gsl::czstring_span<> Phidget::device_label() const {
    gsl::czstring<> label;
    const auto ret = as_cxx(Phidget_getDeviceLabel(handle_, &label));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::device_id", ret };
    }

    return as_span(gsl::not_null<gsl::czstring<>>{ label });
}

gsl::czstring_span<> Phidget::device_name() const {
    gsl::czstring<> name;
    const auto ret = as_cxx(Phidget_getDeviceName(handle_, &name));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::device_name", ret };
    }

    return as_span(gsl::not_null<gsl::czstring<>>{ name });
}

Reference<std::int32_t> Phidget::device_serial_number() {
    return { *this, &Phidget::set_device_serial_number,
             &Phidget::get_device_serial_number };
}

std::int32_t Phidget::device_serial_number() const {
    return get_device_serial_number();
}

gsl::czstring_span<> Phidget::device_sku() const {
    gsl::czstring<> sku;
    const auto ret = as_cxx(Phidget_getDeviceSKU(handle_, &sku));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::device_sku", ret };
    }

    return as_span(gsl::not_null<gsl::czstring<>>{ sku });
}

int Phidget::device_version() const {
    int version;
    const auto ret = as_cxx(Phidget_getDeviceVersion(handle_, &version));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::device_version", ret };
    }

    return version;
}

RetainedPhidget Phidget::hub() const {
    PhidgetHandle hub;
    const auto ret = as_cxx(Phidget_getHub(handle_, &hub));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::hub", ret };
    }

    return RetainedPhidget::from_retained(hub);
}

Reference<int> Phidget::hub_port() {
    return { *this, &Phidget::set_hub_port, &Phidget::get_hub_port };
}

int Phidget::hub_port() const {
    return get_hub_port();
}

int Phidget::hub_port_count() const {
    int count;
    const auto ret = as_cxx(Phidget_getHubPortCount(handle_, &count));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::hub_port_count", ret };
    }

    return count;
}

bool Phidget::is_channel() const {
    int is_channel;
    const auto ret = as_cxx(Phidget_getIsChannel(handle_, &is_channel));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::is_channel", ret };
    }

    return static_cast<bool>(is_channel);
}

bool Phidget::is_local() const {
    return get_is_local();
}

Reference<bool> Phidget::is_remote() {
    return { *this, &Phidget::set_is_remote, &Phidget::get_is_remote };
}

bool Phidget::is_remote() const {
    return get_is_remote();
}

void Phidget::open() {
    const auto ret = as_cxx(Phidget_open(handle_));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::open", ret };
    }
}

void
Phidget::open_wait_for_attachment(const std::chrono::milliseconds timeout) {
    if (timeout.count() > std::numeric_limits<std::uint32_t>::max()
        || timeout.count() < 0) {
        throw std::invalid_argument{
            "phidgetcxx::Phidget::open_wait_for_attachment"
        };
    }

    const auto ms = static_cast<std::uint32_t>(timeout.count());
    const auto ret = as_cxx(Phidget_openWaitForAttachment(handle_, ms));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::open_wait_for_attachment", ret };
    }
}

RetainedPhidget Phidget::parent() const {
    PhidgetHandle handle;
    const auto ret = as_cxx(Phidget_getParent(handle_, &handle));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::parent", ret };
    }

    return RetainedPhidget::from_retained(handle);
}

gsl::czstring_span<> Phidget::server_hostname() const {
    gsl::czstring<> hostname;
    const auto ret = as_cxx(Phidget_getServerHostname(handle_, &hostname));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::server_hostname", ret };
    }

    return as_span(gsl::not_null<gsl::czstring<>>{ hostname });
}

Reference<gsl::czstring_span<>> Phidget::server_name() {
    return { *this, &Phidget::set_server_name, &Phidget::get_server_name };
}

gsl::czstring_span<> Phidget::server_name() const {
    return get_server_name();
}

gsl::czstring_span<> Phidget::server_peer_name() const {
    gsl::czstring<> name;
    const auto ret = as_cxx(Phidget_getServerPeerName(handle_, &name));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::server_peer_name", ret };
    }

    return as_span(gsl::not_null<gsl::czstring<>>{ name });
}

void Phidget::write_device_label(gsl::czstring_span<> device_label) {
    // device label must be no more than 10 UTF-16 code points
    // each code point is 16 bits, as expected
    if (device_label.as_string_span().size() * CHAR_BIT > 160) {
        throw std::invalid_argument{
            "phidgetcxx::Phidget::write_device_label"
        };
    }

    const auto ret =
        as_cxx(Phidget_writeDeviceLabel(handle_, device_label.assume_z()));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::write_device_label", ret };
    }
}

void Phidget::set_attach_handler(AttachHandlerT handler) {
    const auto map_ref = detail::phidget_map();
    auto &map = map_ref.get();

    map[handle_].attach_handler = std::move(handler);
}

void Phidget::set_detach_handler(DetachHandlerT handler) {
    const auto map_ref = detail::phidget_map();
    auto &map = map_ref.get();

    map[handle_].detach_handler = std::move(handler);
}

void Phidget::set_error_handler(ErrorHandlerT handler) {
    const auto map_ref = detail::phidget_map();
    auto &map = map_ref.get();

    map[handle_].error_handler = std::move(handler);
}

void Phidget::set_property_change_handler(PropertyChangeHandlerT handler) {
    const auto map_ref = detail::phidget_map();
    auto &map = map_ref.get();

    map[handle_].property_change_handler = std::move(handler);
}

int Phidget::get_channel() const {
    int channel;
    const auto ret = as_cxx(Phidget_getChannel(handle_, &channel));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::get_channel", ret };
    }

    return channel;
}

void Phidget::set_channel(const int channel) {
    const auto ret = as_cxx(Phidget_setChannel(handle_, channel));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::set_channel", ret };
    }
}

std::chrono::milliseconds Phidget::get_data_interval() const {
    std::uint32_t interval;
    const auto ret = as_cxx(Phidget_getDataInterval(handle_, &interval));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::get_data_interval", ret };
    }

    return std::chrono::duration<std::uint32_t, std::milli>{ interval };
}

void Phidget::set_data_interval(const std::chrono::milliseconds interval) {
    if (interval.count() > std::numeric_limits<std::uint32_t>::max()
        || interval.count() < 0) {
        throw std::invalid_argument{ "phidgetcxx::Phidget::set_data_interval" };
    }

    const auto ms = static_cast<std::uint32_t>(interval.count());
    const auto ret = as_cxx(Phidget_setDataInterval(handle_, ms));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::set_data_interval", ret };
    }
}

gsl::czstring_span<> Phidget::get_device_label() const {
    gsl::czstring<> label;
    const auto ret = as_cxx(Phidget_getDeviceLabel(handle_, &label));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::get_device_label", ret };
    }

    return as_span(gsl::not_null<gsl::czstring<>>{ label });
}

void Phidget::set_device_label(const gsl::czstring_span<> label) {
    const auto ret =
        as_cxx(Phidget_setDeviceLabel(handle_, label.assume_z()));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::set_device_label", ret };
    }
}

void Phidget::set_device_label(LabelAnyTag) {
    const auto ret = as_cxx(Phidget_setDeviceLabel(handle_, PHIDGET_LABEL_ANY));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::set_device_label", ret };
    }
}

std::int32_t Phidget::get_device_serial_number() const {
    std::int32_t serial_number;
    const auto ret =
        as_cxx(Phidget_getDeviceSerialNumber(handle_, &serial_number));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::get_device_serial_number", ret };
    }

    return serial_number;
}

void Phidget::set_device_serial_number(const std::int32_t serial_number) {
    const auto ret =
        as_cxx(Phidget_setDeviceSerialNumber(handle_, serial_number));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::set_device_serial_number", ret };
    }
}

int Phidget::get_hub_port() const {
    int port;
    const auto ret = as_cxx(Phidget_getHubPort(handle_, &port));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::get_hub_port", ret };
    }

    return port;
}

void Phidget::set_hub_port(const int port) {
    const auto ret = as_cxx(Phidget_setHubPort(handle_, port));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::set_hub_port", ret };
    }
}

bool Phidget::get_is_local() const {
    int is_local;
    const auto ret = as_cxx(Phidget_getIsLocal(handle_, &is_local));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::get_is_local", ret };
    }

    return static_cast<bool>(is_local);
}

void Phidget::set_is_local(const bool is_local) {
    const auto ret =
        as_cxx(Phidget_setIsLocal(handle_, static_cast<int>(is_local)));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::set_is_local", ret };
    }
}

bool Phidget::get_is_remote() const {
    int is_remote;
    const auto ret = as_cxx(Phidget_getIsRemote(handle_, &is_remote));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::get_is_remote", ret };
    }

    return static_cast<bool>(is_remote);
}

void Phidget::set_is_remote(const bool is_remote) {
    const auto ret =
        as_cxx(Phidget_setIsRemote(handle_, static_cast<int>(is_remote)));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::set_is_remote", ret };
    }
}

gsl::czstring_span<> Phidget::get_server_name() const {
    gsl::czstring<> name;
    const auto ret = as_cxx(Phidget_getServerName(handle_, &name));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::get_server_name", ret };
    }

    return as_span(gsl::not_null<gsl::czstring<>>{ name });
}

void Phidget::set_server_name(const gsl::czstring_span<> server_name) {
    const auto ret =
        as_cxx(Phidget_setServerName(handle_, server_name.assume_z()));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::set_server_name", ret };
    }
}

void Phidget::attach_glue(PhidgetHandle, void *const self_opaque) {
    auto &self = *reinterpret_cast<Phidget*>(self_opaque);

    self.do_attach_handler();
}

void Phidget::detach_glue(PhidgetHandle, void *const self_opaque) {
    auto &self = *reinterpret_cast<Phidget*>(self_opaque);

    self.do_detach_handler();
}

void Phidget::error_glue(PhidgetHandle, void *const self_opaque,
                         const Phidget_ErrorEventCode code_c,
                         const gsl::czstring<> description_c) {
    auto &self = *reinterpret_cast<Phidget*>(self_opaque);
    const auto code = as_cxx(code_c);
    const gsl::czstring_span<> description{ gsl::ensure_z(description_c) };

    self.do_error_handler(code, description);
}

void Phidget::property_change_glue(PhidgetHandle, void *const self_opaque,
                                   const gsl::czstring<> name_c) {
    auto &self = *reinterpret_cast<Phidget*>(self_opaque);
    const gsl::czstring_span<> name{ gsl::ensure_z(name_c) };

    self.do_property_change_handler(name);
}

void Phidget::do_attach_handler() {
    const auto map_ref = detail::phidget_map();
    auto &map = map_ref.get();
    auto &handler = map[handle_].attach_handler;

    if (handler) {
        handler(*this);
    }
}

void Phidget::do_detach_handler() {
    const auto map_ref = detail::phidget_map();
    auto &map = map_ref.get();
    auto &handler = map[handle_].detach_handler;

    if (handler) {
        handler(*this);
    }
}

void Phidget::do_error_handler(const ErrorEventCode code,
                               const gsl::czstring_span<> description) {
    const auto map_ref = detail::phidget_map();
    auto &map = map_ref.get();
    auto &handler = map[handle_].error_handler;

    if (handler) {
        handler(*this, code, description);
    }
}

void Phidget::do_property_change_handler(const gsl::czstring_span<> name) {
    const auto map_ref = detail::phidget_map();
    auto &map = map_ref.get();
    auto &handler = map[handle_].property_change_handler;

    if (handler) {
        handler(*this, name);
    }
}

} // namespace phidgetcxx
