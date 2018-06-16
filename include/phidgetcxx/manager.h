#ifndef UMIGV_PHIDGETCXX_MANAGER_H
#define UMIGV_PHIDGETCXX_MANAGER_H

#include "phidgetcxx/phidget.h"

#include <functional>

namespace phidgetcxx {

class Manager;

class Manager {
public:
    using AttachHandlerT = std::function<void(Manager&, const Phidget&)>;
    using DetachHandlerT = std::function<void(Manager&, const Phidget&)>;

    explicit Manager(PhidgetManagerHandle handle);

    AttachHandlerT& attach_handler() noexcept;

    DetachHandlerT& detach_handler() noexcept;

private:
    static void attach_glue(PhidgetManagerHandle handle, void *self,
                            PhidgetHandle phidget);

    static void detach_glue(PhidgetManagerHandle handle, void *self,
                            PhidgetHandle phidget);

    void do_attach(const Phidget &phidget);

    void do_detach(const Phidget &phidget);

    PhidgetManagerHandle handle_;
    AttachHandlerT attach_handler_;
    DetachHandlerT detach_handler_;
};

} // namespace phidgetcxx

#endif
