#pragma once

namespace mce {
    class Color {
    public:
        float r;
        float g;
        float b;
        float a;
        Color()
            : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {};
        Color(float r, float g, float b, float a = 1)
            : r(r), g(g), b(b), a(a) {};
        Color(double r, double g, double b, double a = 1)
            : r((float)r), g((float)g), b((float)b), a((float)a) {};
        Color(int ir, int ig, int ib, int ia = 255)
            : r(ir / 255.0f), g(ig / 255.0f), b(ib / 255.0f), a(ia / 255.0f) {};
    };
}
