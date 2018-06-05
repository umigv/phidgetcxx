#include "phidgetcxx/phidget.h"

#include <cstring>
#include <limits>

namespace phidgetcxx {

ChannelReference& ChannelReference::operator=(const ChannelReference &other) {
    const int other_channel = other.phidget_ptr_->get_channel();
    phidget_ptr_->set_channel(other_channel);

    return *this;
}

ChannelReference& ChannelReference::operator=(const int channel) {
    phidget_ptr_->set_channel(channel);

    return *this;
}

ChannelReference::operator int() const {
    return phidget_ptr_->get_channel();
}

DataIntervalReference&
DataIntervalReference::operator=(const DataIntervalReference &other) {
    const std::chrono::milliseconds other_interval =
        other.phidget_ptr_->get_data_interval();

    phidget_ptr_->set_data_interval(other_interval);

    return *this;
}

DataIntervalReference&
DataIntervalReference::operator=(const std::chrono::milliseconds interval) {
    phidget_ptr_->set_data_interval(interval);

    return *this;
}

DataIntervalReference::operator std::chrono::milliseconds() const {
    return phidget_ptr_->get_data_interval();
}

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

ChannelReference Phidget::channel() {
    return ChannelReference{ *this };
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

gsl::cstring_span<> Phidget::channel_class_name() const {
    gsl::czstring<> name = nullptr;
    const auto ret = as_cxx(Phidget_getChannelClassName(handle_, &name));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::channel_class_name", ret };
    }

    const auto length =
        static_cast<gsl::cstring_span<>::index_type>(std::strlen(name));

    return { name, length };
}

gsl::cstring_span<> Phidget::channel_name() const {
    gsl::czstring<> name = nullptr;
    const auto ret = as_cxx(Phidget_getChannelName(handle_, &name));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::channel_name", ret };
    }

    const auto length =
        static_cast<gsl::cstring_span<>::index_type>(std::strlen(name));

    return { name, length };
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

DataIntervalReference Phidget::data_interval() {
    return DataIntervalReference{ *this };
}

std::chrono::milliseconds Phidget::data_interval() const {
    return get_data_interval();
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

int Phidget::get_channel() const {
    int channel;
    const auto ret = as_cxx(Phidget_getChannel(handle_, &channel));

    if (!ret) {
        throw Exception{ "phidgetcxx::Phidget::get_channel", ret };
    }

    return channel;
}

void Phidget::set_channel(const int channel) const {
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

} // namespace phidgetcxx
