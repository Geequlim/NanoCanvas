#ifndef PAINT_HPP
#define PAINT_HPP

namespace NanoCanvas
{
    struct Paint
    {
        enum class Type
        {
            Linear,
            Radial,
            Box,
            ImagePattern,
            None
        } type = Type::None;
        float xx =0.0f, yy =0.0f , aa =0.0f, bb =0.0f, cc =0.0f,dd =0.0f;
        int imageID  = 0;
        Color sColor = Colors::ZeroColor;
        Color eColor = Colors::ZeroColor;
    };
}

#endif // PAINT_HPP
