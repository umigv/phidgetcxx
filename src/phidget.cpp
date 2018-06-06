#include "phidgetcxx/phidget.h"

#include <cstring>
#include <limits>

namespace phidgetcxx {
namespace detail {

static inline gsl::czstring_span<> as_span(const gsl::czstring<> string) {
    if (!string) {
        throw std::invalid_argument{ "phidgetcxx::detail::as_span" };
    }

    const auto length =
        static_cast<gsl::cstring_span<>::index_type>(std::strlen(string));
    const gsl::cstring_span<> span{ string, length };

    return { span };
}

} // namespace detail

Phidget::~Phidget() {
    if (is_attached()) {
        close();
    }
}

void Phidget::release() {
    const auto ret = as_cxx(Phidget_release(&handle_));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::release", ret };
    }
}

void Phidget::retain() {
    const auto ret = as_cxx(Phidget_retain(handle_));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::retain", ret };
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
    gsl::czstring<> name = nullptr;
    const auto ret = as_cxx(Phidget_getChannelClassName(handle_, &name));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::channel_class_name", ret };
    }

    return detail::as_span(name);
}

gsl::czstring_span<> Phidget::channel_name() const {
    gsl::czstring<> name = nullptr;
    const auto ret = as_cxx(Phidget_getChannelName(handle_, &name));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::channel_name", ret };
    }

    return detail::as_span(name);
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

DeviceClass Phidget::device_class() const;

gsl::cstring_span<> Phidget::device_class_name() const;

DeviceId Phidget::device_id() const;

Reference<gsl::czstring_span<>> Phidget::device_label();

gsl::czstring_span<> Phidget::device_label() const;

gsl::czstring_span<> Phidget::device_name() const;

Reference<std::int32_t> Phidget::device_serial_number();

std::int32_t Phidget::device_serial_number() const;

gsl::czstring_span<> Phidget::device_sku() const;

int Phidget::device_version() const;

bool Phidget::is_channel() const;

bool Phidget::is_local() const;

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

int Phidget::get_channel() const {
    int channel;
    const auto ret = as_cxx(Phidget_getChannel(handle_, &channel));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::get_channel", ret };
    }

    return channel;
}

void Phidget::set_channel(const int &channel) {
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

void Phidget::set_data_interval(const std::chrono::milliseconds &interval) {
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
    gsl::czstring<> label = nullptr;
    const auto ret = as_cxx(Phidget_getDeviceLabel(handle_, &label));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::get_device_label", ret };
    }

    return detail::as_span(label);
}

void Phidget::set_device_label(const gsl::czstring_span<> &label) {
    const auto ret =
        as_cxx(Phidget_setDeviceLabel(handle_, label.ensure_z().data()));

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

void Phidget::set_device_serial_number(const std::int32_t &serial_number) {
    const auto ret =
        as_cxx(Phidget_setDeviceSerialNumber(handle_, serial_number));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::set_device_serial_number", ret };
    }
}

} // namespace phidgetcxx
