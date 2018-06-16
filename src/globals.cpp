#include "globals.h"

namespace phidgetcxx {
namespace detail {

LockedRef<PhidgetMapT> phidget_map() {
    static PhidgetMapT map;
    static std::mutex mutex;

    return { map, mutex };
}

LockedRef<ManagerMapT> manager_map() {
    static ManagerMapT map;
    static std::mutex mutex;

    return { map, mutex };
}

} // namespace detail
} // namespace phidgetcxx
