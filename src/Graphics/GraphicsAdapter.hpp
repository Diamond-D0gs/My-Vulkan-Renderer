#pragma once

#include <string>
#include <cstdint>

namespace Oak::Graphics {
    class Instance;

    class Adapter {
    protected:
        Adapter() = default;

    public:
        struct Info {
            std::u8string _name;
            uint64_t _vram;
        } _info;

        virtual ~Adapter() = default;

        friend Instance;
    };
}