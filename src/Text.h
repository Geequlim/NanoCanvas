#ifndef TEXT_H
#define TEXT_H

namespace NanoCanvas
{
    class Canvas;
    
    struct Font
    {
        int face = 0;
        string name = nullstr;
        
        Font() = default;
        Font(Canvas& canvas, const string& fname , const string& ttfPath);
        Font(Canvas& canvas,const string& fname,const Memery& mem,bool invalidateMem);
        inline bool valid()const{ return face >= 0; }
        ~Font(){};
    };
    
    namespace TextAlign
    {
        enum HorizontalAlign
        {
            /// Align text horizontally to left.
            Left      = 1<<0,
            /// Align text horizontally to center.
            Center    = 1<<1,
            /// Align text horizontally to right.  
            Right     = 1<<2,
        };
        
        enum VerticalAlign
        {
            /// Align text vertically to top.
            Top       = 1<<3,
            /// Align text vertically to middle.
            Middle    = 1<<4,
            /// Align text vertically to bottom. 
            Bottom    = 1<<5,
            /// Align text vertically to baseline.
            Baseline  = 1<<6 
        };
    }
    
    
    struct TextStyle
    {
        int face          = 0;
        float size        = 12.0f;
        float lineHeight  = NAN;
        float blur        = NAN;
        float letterSpace = NAN;
        Color color       = Colors::ZeroColor;
        TextAlign::HorizontalAlign hAlign = TextAlign::Left;
        TextAlign::VerticalAlign vAlign   = TextAlign::Baseline;
    };
}

#endif // TEXT_H
