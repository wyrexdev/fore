//
// Created by wyrex on 8/14/25.
//

#include "Color.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

namespace Graphics {

    Color::Color(float _r, float _g, float _b, float _a)
            : r(_r), g(_g), b(_b), a(_a) {}

    Color::Color(const std::string& hex) {
        setHex(hex);
    }

    void Color::set(float _r, float _g, float _b, float _a) {
        r = _r; g = _g; b = _b; a = _a;
    }

    void Color::setHex(const std::string& hex) {
        std::string h = hex;
        if (h[0] == '#') h = h.substr(1);
        if (h.length() != 6 && h.length() != 8) {
            throw std::invalid_argument("Hex string must be 6 or 8 characters");
        }

        unsigned int hexValue;
        std::stringstream ss;
        ss << std::hex << h;
        ss >> hexValue;

        if (h.length() == 6) { // RRGGBB
            r = ((hexValue >> 16) & 0xFF) / 255.0f;
            g = ((hexValue >> 8) & 0xFF) / 255.0f;
            b = (hexValue & 0xFF) / 255.0f;
            a = 1.0f;
        } else { // RRGGBBAA
            r = ((hexValue >> 24) & 0xFF) / 255.0f;
            g = ((hexValue >> 16) & 0xFF) / 255.0f;
            b = ((hexValue >> 8) & 0xFF) / 255.0f;
            a = (hexValue & 0xFF) / 255.0f;
        }
    }

    void Color::print() const {
        std::cout << "RGBA: (" << r << ", " << g << ", " << b << ", " << a << ")\n";
    }

    std::string Color::toHexString() const {
        unsigned int R = static_cast<unsigned int>(r * 255.0f);
        unsigned int G = static_cast<unsigned int>(g * 255.0f);
        unsigned int B = static_cast<unsigned int>(b * 255.0f);
        unsigned int A = static_cast<unsigned int>(a * 255.0f);
        std::stringstream ss;
        ss << "#" << std::hex << std::setw(2) << std::setfill('0') << R
           << std::setw(2) << std::setfill('0') << G
           << std::setw(2) << std::setfill('0') << B
           << std::setw(2) << std::setfill('0') << A;
        return ss.str();
    }

}