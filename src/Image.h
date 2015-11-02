#ifndef IMAGE_H
#define IMAGE_H

namespace NanoCanvas
{
    class Canvas;
    class Image
    {
    public:
        enum ImageFlags 
        {
            /// Generate mipmaps during creation of the image.
            GenerateMipmaps     = 1<<0,
            /// Repeat image in X direction.  
            RepeatX             = 1<<1,
            /// Repeat image in Y direction.
            RepeatY             = 1<<2,
            /// Flips (inverses) image in Y direction when rendered.
            FlipY               = 1<<3,
            /// Image data has premultiplied alpha.
            PreMultiplied       = 1<<4,
        } flags;
        
        
        Image() = default;
        Image(Canvas& canvas,const string& filePath, int imageFlags = 0);
        Image(Canvas& canvas,const Memery& memory, int imageFlags = 0);
        Image(Canvas& canvas,int w,int h,const Memery& memory,int imageFlags=0);
        ~Image();
        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;
        inline bool valid()const{ return imageID;}
        bool update(const Memery& memory);
        void size(int& width,int& height);
        int imageID = 0;
    private:
        Canvas * m_canvas = nullptr;
    };
}

#endif // IMAGE_H
