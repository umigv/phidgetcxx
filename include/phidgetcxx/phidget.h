#ifndef UMIGV_PHIDGETCXX_PHIDGET_H
#define UMIGV_PHIDGETCXX_PHIDGET_H

#include "phidgetcxx/channel_class.h"
#include "phidgetcxx/channel_subclass.h"
#include "phidgetcxx/exception.h"
#include "phidgetcxx/return_code.h"

#include <chrono>

#include <gsl/gsl>
#include <phidget22.h>

namespace phidgetcxx {

class Phidget;

class ChannelReference {
public:
    friend Phidget;

    ChannelReference& operator=(const ChannelReference &other);

    ChannelReference& operator=(int channel);

    operator int() const;

private:
    constexpr explicit ChannelReference(Phidget &phidget) noexcept
    : phidget_ptr_{ &phidget } { }

    gsl::not_null<Phidget*> phidget_ptr_;
};

class DataIntervalReference {
public:
    friend Phidget;

    DataIntervalReference& operator=(const DataIntervalReference &other);

    DataIntervalReference& operator=(std::chrono::milliseconds interval);

    operator std::chrono::milliseconds() const;

private:
    constexpr explicit DataIntervalReference(Phidget &phidget) noexcept
    : phidget_ptr_{ &phidget } { }

    gsl::not_null<Phidget*> phidget_ptr_;
};

// wrapper around the PhidgetHandle C type
class Phidget {
public:
    friend ChannelReference;
    friend DataIntervalReference;

    Phidget() = default;

    ~Phidget();

    void release();

    void retain();

    bool is_attached() const;

    ChannelReference channel();

    int channel() const;

    ChannelClass channel_class() const;

    gsl::cstring_span<> channel_class_name() const;

    gsl::cstring_span<> channel_name() const;

    ChannelSubclass channel_subclass() const;

    void close();

    DataIntervalReference data_interval();

    std::chrono::milliseconds data_interval() const;

    void open();

    void open_wait_for_attachment(std::chrono::milliseconds timeout);

private:
    int get_channel() const;

    void set_channel(int channel) const;

    std::chrono::milliseconds get_data_interval() const;

    void set_data_interval(std::chrono::milliseconds interval);

    PhidgetHandle handle_;
};

} // namespace phidgetcxx

#endif
