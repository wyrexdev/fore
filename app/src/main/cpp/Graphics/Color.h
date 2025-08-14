//
// Created by wyrex on 8/14/25.
//

#ifndef FORE_COLOR_H
#define FORE_COLOR_H

#pragma once
#include <string>
#include <iostream>

namespace Graphics {

    class Color {
    public:
        float r, g, b, a;

        Color(float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f);
        Color(const std::string& hex);

        void set(float _r, float _g, float _b, float _a = 1.0f);
        void setHex(const std::string& hex);

        void print() const;
        std::string toHexString() const;
    };
}


#endif //FORE_COLOR_H
