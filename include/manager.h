#ifndef BAASSISTANT_MANAGER_H
#define BAASSISTANT_MANAGER_H

#include <memory>

#include "control/window.h"

namespace Baa {

class Manager {
    std::unique_ptr<Window> window;

public:
    explicit Manager(Window *window);

    ~Manager() = default;
};

}
#endif  // BAASSISTANT_MANAGER_H
