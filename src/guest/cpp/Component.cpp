#include "wit/utility_cpp.h"

namespace exports::app::utility::info {

wit::string GetMessage(int32_t number) {
    std::string message = "This is C++ function, number = "
        + std::to_string(number);
    return wit::string::from_view(message);
}

} // namespace exports::app::utility::info
