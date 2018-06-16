#ifndef UMIGV_PHIDGETCXX_DETAIL_GLOBALS_H
#define UMIGV_PHIDGETCXX_DETAIL_GLOBALS_H

#include "locked_ref.hpp"

#include "phidgetcxx/phidget.h"
#include "phidgetcxx/manager.h"

#include <cstddef>
#include <cstdint>

#include <flat_hash_map.hpp>
#include <phidget22.h>

namespace phidgetcxx {
namespace detail {

struct PhidgetHandlers {
    Phidget::AttachHandlerT attach_handler;
    Phidget::DetachHandlerT detach_handler;
    Phidget::ErrorHandlerT error_handler;
    Phidget::PropertyChangeHandlerT property_change_handler;
    std::int64_t num_refs = 0;
};

struct ManagerHandlers {
    Manager::AttachHandlerT attach_handler;
    Manager::DetachHandlerT detach_handler;
    std::int64_t num_refs = 0;
};

using PhidgetMapT = ska::flat_hash_map<PhidgetHandle, PhidgetHandlers>;
using ManagerMapT = ska::flat_hash_map<PhidgetManagerHandle, ManagerHandlers>;

LockedRef<PhidgetMapT> phidget_map();

LockedRef<ManagerMapT> manager_map();

} // namespace detail
} // namespace phidgetcxx

#endif
