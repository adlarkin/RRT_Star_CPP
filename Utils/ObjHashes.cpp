//
// Created by adlarkin on 11/1/18.
//

#include "../State/Location.h"

namespace std {
    template<>
    struct hash<Location> {
        size_t operator()(const Location &obj) const {
            size_t h1 = hash<int>()(obj.xID());
            size_t h2 = hash<int>()(obj.yID());
            return h1 ^ (h2 << 1);
        }
    };
}