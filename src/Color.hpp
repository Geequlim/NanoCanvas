#ifndef __NanoCanvas_Color_H__
#define __NanoCanvas_Color_H__

namespace NanoCanvas
{
    
    using  Byte = unsigned char;
    
    struct Color
    {
        union
        {
            struct
            {
                /// Red value
                Byte r;
                /// Green value
                Byte g;
                /// Blue value
                Byte b;
                /// Alpha value
                Byte a;
            };
            Byte mem[4];
        };
        
        
        Color(){ r = g = b = a = 0; }
        
        /**
         * @brief Construct a color with an unsigned integer value
         * @param color The color code value
         */
        Color(const unsigned int color) 
        { 
            set(color);
        }
        
        /**
          * @brief Construct color with it's components value in the range [0,255]
          * @param _r The red component value
          * @param _g The green component value
          * @param _b The blue component value
          * @param _a The alpha component value
         */
        Color(Byte _r, Byte _g, Byte _b, Byte _a)
        {
            set(_r,_g,_b,_a);
        }
        
        Color(int _r, int _g, int _b, int _a)
        {
            set(_r,_g,_b,_a);
        }
        
        Color(unsigned _r, unsigned _g, unsigned _b, unsigned _a)
        {
            set(_r,_g,_b,_a);
        }
        
         /**
          * @brief Construct color with it's components value in the range [0,1]
          * @param _r The red component value
          * @param _g The green component value
          * @param _b The blue component value
          * @param _a The alpha component value
          */
        Color(float _r, float _g, float _b, float _a)
        {
            set(_r,_g,_b,_a);
        }
        
        
        inline operator unsigned int() const { return code(); }
        
        inline Byte& operator[](int index){ return mem[index]; }
        inline const Byte operator[](int index) const { return mem[index]; }
        
        inline bool operator==(const Color& color){  return code() == color.code(); }
        inline bool operator<(const Color& color){ return code() < color.code(); }
        
        inline Color& operator = (const unsigned int color){ return set(color); }
    
        Color& operator += (const Color& color)
        {
            r = clamp<Byte>( r + color.r, 0, UCHAR_MAX);
            g = clamp<Byte>( g + color.g, 0, UCHAR_MAX);
            b = clamp<Byte>( b + color.b, 0, UCHAR_MAX);
            a = clamp<Byte>( a + color.a, 0, UCHAR_MAX);
            return *this;
        }
        
        Color& operator -= (const Color& color)
        {
            using std::max;
            r = clamp<Byte>( r - color.r, 0, UCHAR_MAX);
            g = clamp<Byte>( g - color.g, 0, UCHAR_MAX);
            b = clamp<Byte>( b - color.b, 0, UCHAR_MAX);
            a = clamp<Byte>( a - color.a, 0, UCHAR_MAX);
            return *this;
        }
        
        Color& operator *= (const Color& color)
        {
            r = clamp<Byte>( r + (color.r * color.a/UCHAR_MAX), 0, UCHAR_MAX);
            g = clamp<Byte>( g + (color.g * color.a/UCHAR_MAX), 0, UCHAR_MAX);
            b = clamp<Byte>( b + (color.b * color.a/UCHAR_MAX), 0, UCHAR_MAX);
            return *this;
        }
        
        Color operator + (const Color& color)
        {
            Color ret(*this);
            ret += color;
            return ret;
        }
        
        Color operator - (const Color& color)
        {
            Color ret(*this);
            ret -= color;
            return ret;
        }
        
        Color operator * (const Color& color)
        {
            Color ret(*this);
            ret *= color;
            return ret;
        }
        
        inline Color& set(unsigned int color)
        {
            r = (Byte) color >> 24U;
            g = (Byte)(color >> 16U) & 0x00ffU;
            b = (Byte)(color >> 8U) & 0x0000ffU;
            a = (Byte) color % 0x100U;
            return *this;
        }
        
        inline Color& set(float _r, float _g , float _b,float _a)
        {
            r =  clamp<Byte>( (Byte)(_r * UCHAR_MAX), 0, UCHAR_MAX);
            g =  clamp<Byte>( (Byte)(_g * UCHAR_MAX), 0, UCHAR_MAX);
            b =  clamp<Byte>( (Byte)(_b * UCHAR_MAX), 0, UCHAR_MAX);
            a =  clamp<Byte>( (Byte)(_a * UCHAR_MAX), 0, UCHAR_MAX);
            return *this;
        }
        
        inline Color& set(Byte _r, Byte _g, Byte _b, Byte _a)
        {
             r = _r; g = _g; b = _b; a = _a;
             return *this;
        }
        
        inline Color& set(unsigned _r, unsigned _g, unsigned _b, unsigned _a)
        {
            r = (Byte)_r; g = (Byte)_g; b = (Byte)_b; a = (Byte)_a;
        }
        
        inline Color& set(int _r, int _g, int _b, int _a)
        {
            r = (Byte)_r; g = (Byte)_g; b = (Byte)_b; a = (Byte)_a;
        }
        
        inline unsigned int code()const
        {
            unsigned int color = 0U;
            color |= ( r   << 24U );
            color |= ( g << 16U );
            color |= ( b << 8U );
            color |= a;
            return color;
        }
        
        inline float redf()const{ return   r/255.0f; }
        inline float greenf()const{ return g/255.0f; }
        inline float bluef()const{ return  b/255.0f; }
        inline float alphaf()const{ return a/255.0f; }        
    };
    
    namespace Colors
    {
        static Color zeroColor = 0U;
        static Color red = 0xff0000ff;
        static Color green = 0x00ff00ff;
        static Color blue = 0x0000ffff;
        static Color wihte = 0xffffffff;
        static Color black = 0x000000ff;
    }
    
    /** @brief Get hex code string from color */
    string to_string(const Color& color);
}

#endif //__NanoCanvas_Color_H__