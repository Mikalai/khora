#include "DiscoveryType.h"

const char* ToString(discovery_type evt) {
    switch (evt) {
        case discovery_type::red:
            return "red";
        case discovery_type::blue:
            return "blue";
        case discovery_type::green:
            return "green";
        case discovery_type::epic_red:
            return "epic_red";
        case discovery_type::epic_blue:
            return "epic_blue";
        case discovery_type::epic_green:
            return "epic_green";
        default:
            return "unknown";
    }
}
