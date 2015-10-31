#include "NanoCanvas.h"
#include "nanovg.h"

namespace NanoCanvas
{

    NVGcolor nvgColor(const Color& color)
    {
        return nvgRGBA(color.r,color.g,color.b,color.a);
    }

    NVGpaint nvgPaint(NVGcontext* vg,const Paint& paint)
    {
        NVGpaint nvgPaint;
        switch(paint.type)
        {
            case Paint::Type::Linear:
                nvgPaint = nvgLinearGradient(vg,paint.xx,paint.yy,
                                             paint.aa,paint.bb,
                                             nvgColor(paint.sColor),
                                             nvgColor(paint.eColor));
                break;
            case Paint::Type::Box:
                nvgPaint = nvgBoxGradient(vg,paint.xx,paint.yy,
                                          paint.aa,paint.bb,paint.cc,
                                          paint.dd,nvgColor(paint.sColor),
                                          nvgColor(paint.eColor));
                break;
            case Paint::Type::Radial:
                nvgPaint = nvgRadialGradient(vg,paint.xx,paint.yy,
                                             paint.aa,paint.bb,
                                             nvgColor(paint.sColor),
                                             nvgColor(paint.eColor));
                break;
            case Paint::Type::Image:
                // TODO: Image pattern
                break;
            case Paint::Type::None:
            default:
                break;
        }
        return nvgPaint;
    }

/*----------------- Propoties ---------------------*/
    std::function<NVGcontext*(int)> Canvas::nvgContextCreateFunc = nullptr;

    Canvas::Canvas(int flags , float width , float height, float scaleRatio)
    {
        m_nvgCtx = nvgContextCreateFunc(flags);
        m_width = width;
        m_height = height;
        m_scaleRatio = scaleRatio;
        m_xPos  = m_yPos = 0;
        m_alpha = 1.0f;
    }


/*-------------------- Style Control -------------------*/

    Canvas& Canvas::globalAlpha(float alpha)
    {
        m_alpha = alpha;
        nvgGlobalAlpha(m_nvgCtx,m_alpha);
        return *this;
    }

    Canvas& Canvas::lineCap(LineCap cap)
    {
        int nvgCap = NVG_BUTT;
        if ( cap == LineCap::SQUARE )
            nvgCap = NVG_SQUARE;
        else if ( cap == LineCap::ROUND)
            nvgCap = NVG_ROUND;
        nvgLineCap(m_nvgCtx,nvgCap);
        return *this;
    }

    Canvas& Canvas::lineJoin(LineJoin join)
    {
        int nvgJoin = NVG_BEVEL;
        if ( join == LineJoin::ROUND )
            nvgJoin = NVG_ROUND;
        else if ( join == LineJoin::MITER)
            nvgJoin = NVG_MITER;
        nvgLineJoin(m_nvgCtx,nvgJoin);
        return *this;
    }

    Canvas& Canvas::lineWidth(float width)
    {
        nvgStrokeWidth(m_nvgCtx,width);
        return *this;
    }

    Canvas& Canvas::miterLimit(float limit)
    {
        nvgMiterLimit(m_nvgCtx,limit);
        return *this;
    }


    Canvas& Canvas::fillStyle(const Color& color)
    {
        nvgFillColor(m_nvgCtx,nvgRGBA(color.r,color.g,color.b,color.a));
        return *this;
    }

    Canvas& Canvas::fillStyle(const Paint& paint)
    {
        if (paint.type != Paint::Type::None )
        {
            NVGpaint npaint = nvgPaint(m_nvgCtx,paint);
            nvgFillPaint(m_nvgCtx,npaint);
        }
        return *this;
    }

    Canvas& Canvas::strokeStyle(const Paint& paint)
    {
        if (paint.type != Paint::Type::None )
        {
            NVGpaint npaint = nvgPaint(m_nvgCtx,paint);
            nvgStrokePaint(m_nvgCtx,npaint);
        }
    }

    Canvas& Canvas::strokeStyle(const Color& color)
    {
        nvgStrokeColor(m_nvgCtx,nvgRGBA(color.r,color.g,color.b,color.a));
        return *this;
    }

    Paint Canvas::createLinearGradient(float x0,float y0,float x1,float y1,
                                      const Color& scolor , const Color& ecolor)
    {
        Paint gdt;
        gdt.type = Paint::Type::Linear;
        gdt.xx = x0;
        gdt.yy = y0;
        gdt.aa = x1;
        gdt.bb = y1;
        gdt.sColor = scolor;
        gdt.eColor = ecolor;
        return gdt;
    }
    
    Paint Canvas::createRadialGradient(float cx,float cy,float r1,float r2,
                                  const Color& icolor , const Color& ocolor)
    {
        Paint gdt;
        gdt.type = Paint::Type::Radial;
        gdt.xx = cx;
        gdt.yy = cy;
        gdt.aa = r1;
        gdt.bb = r2;
        gdt.sColor = icolor;
        gdt.eColor = ocolor;
        return gdt;
    }

    Paint Canvas::createBoxGradient(float x, float y, float w, float h,
                               float r, float f, Color icol, Color ocol)
    {
        Paint gdt;
        gdt.type = Paint::Type::Box;
        gdt.xx = x;
        gdt.yy = y;
        gdt.aa = w;
        gdt.bb = h;
        gdt.cc = r;
        gdt.dd = f;
        gdt.sColor = icol;
        gdt.eColor = ocol;
        return gdt;
    }

/* ------------------- Basic Path ----------------------*/

    Canvas& Canvas::moveTo(float x,float y)
    {
        local2Global(x,y);
        nvgMoveTo(m_nvgCtx,x,y);
        return *this;
    }

    Canvas& Canvas::lineTo(float x,float y)
    {
        local2Global(x,y);
        nvgLineTo(m_nvgCtx,x,y);
        return *this;
    }

    Canvas& Canvas::arcTo(float x1,float y1,float x2,float y2,float r)
    {
        local2Global(x1,y1);
        local2Global(x2,y2);
        nvgArcTo(m_nvgCtx,x1,y1,x2,y2,r);
        return *this;
    }

    Canvas& Canvas::quadraticCurveTo(float cpx,float cpy,float x, float y)
    {
        local2Global(cpx,cpy);
        local2Global(x,y);
        nvgQuadTo(m_nvgCtx,cpx,cpy,x,y);
        return *this;
    }

    Canvas& Canvas::bezierCurveTo(float cp1x,float cp1y,
                                  float cp2x,float cp2y,
                                  float x, float y)
    {
        local2Global(cp1x,cp1y);
        local2Global(cp2x,cp2y);
        local2Global(x,y);
        nvgBezierTo(m_nvgCtx,cp1x,cp1y,cp2x,cp2y,x,y);
        return *this;
    }

    Canvas& Canvas::arc(float x,float y,float r,
                float sAngle,float eAngle,bool counterclockwise)
    {
        local2Global(x,y);
        int dir = counterclockwise? NVG_CCW : NVG_CW;
        nvgArc(m_nvgCtx,x,y,r,sAngle,eAngle,dir);
        return *this;
    }


    Canvas& Canvas::closePath()
    {
        nvgClosePath(m_nvgCtx);
        return *this;
    }


/* ------------------- Advance Path --------------------*/


    Canvas& Canvas::rect(float x,float y,float w,float h)
    {
        local2Global(x,y);
        nvgRect(m_nvgCtx,x,y,w,h);
        return *this;
    }

    Canvas& Canvas::roundedRect(float x,float y,float w,float h,float r)
    {
        local2Global(x,y);
        nvgRoundedRect(m_nvgCtx,x,y,w,h,r);
        return *this;
    }

    Canvas& Canvas::circle(float cx ,float cy , float r)
    {
        local2Global(cx,cy);
        nvgCircle(m_nvgCtx,cx,cy,r);
        return *this;
    }

    Canvas& Canvas::ellipse(float cx, float cy, float rx, float ry)
    {
        local2Global(cx,cy);
        nvgEllipse(m_nvgCtx,cx,cy,rx,ry);
        return *this;
    }

/* ------------------- Draw Action ---------------------*/

    Canvas& Canvas::fill()
    {
        nvgFill(m_nvgCtx);
        return *this;
    }

    Canvas& Canvas::stroke()
    {
        nvgStroke(m_nvgCtx);
        return *this;
    }

    Canvas& Canvas::fillRect(float x,float y,float w,float h)
    {
        local2Global(x,y);
        nvgBeginPath(m_nvgCtx);
        nvgRect(m_nvgCtx,x,y,w,h);
        nvgFill(m_nvgCtx);
        return *this;
    }

    Canvas& Canvas::strokeRect(float x,float y,float w,float h)
    {
        local2Global(x,y);
        nvgBeginPath(m_nvgCtx);
        nvgRect(m_nvgCtx,x,y,w,h);
        nvgStroke(m_nvgCtx);
        return *this;
    }

    Canvas& Canvas::clearColor(const Color& color)
    {
        nvgSave(m_nvgCtx);

        nvgFillColor(m_nvgCtx,nvgRGBA(color.r,color.g,color.b,color.a));
        nvgBeginPath(m_nvgCtx);
        nvgRect(m_nvgCtx,m_xPos,m_yPos,m_width,m_height);
        nvgFill(m_nvgCtx);

        nvgRestore(m_nvgCtx);
        return *this;
    }


/*------------------- State Handling -----------------*/

    Canvas& Canvas::save()
    {
        nvgSave(m_nvgCtx);
        return *this;
    }

    Canvas& Canvas::restore()
    {
        nvgRestore(m_nvgCtx);
        return *this;
    }

    Canvas& Canvas::reset()
    {
        nvgReset(m_nvgCtx);
        return *this;
    }

/*--------------------- Transformations ----------------*/

    Canvas& Canvas::scale(float scalewidth , float scaleheight)
    {
        nvgScale(m_nvgCtx,scalewidth,scaleheight);
        return *this;
    }

    Canvas& Canvas::rotate(float angle)
    {
        nvgRotate(m_nvgCtx,angle);
        return *this;
    }

    Canvas& Canvas::translate(float x,float y)
    {
        nvgTranslate(m_nvgCtx,x,y);
        return *this;
    }

    Canvas& Canvas::transform(float a, float b, float c,
                              float d, float e, float f)
    {
        nvgTransform(m_nvgCtx,a,b,c,d,e,f);
        return *this;
    }

    Canvas& Canvas::setTransform(float a, float b, float c,
                                 float d, float e, float f)
    {
        nvgResetTransform(m_nvgCtx);
        nvgTransform(m_nvgCtx,a,b,c,d,e,f);
        return *this;
    }

    Canvas& Canvas::restTransform()
    {
        nvgResetTransform(m_nvgCtx);
        return *this;
    }

/*---------------- Canvas Control -----------------*/
    Canvas& Canvas::begineFrame(int windowWidth, int windowHeight)
    {
        nvgBeginFrame(m_nvgCtx,windowWidth,windowHeight,m_scaleRatio);
        // Clip out side area
        nvgScissor(m_nvgCtx,m_xPos,m_yPos,m_width,m_height);

        return *this;
    }

    Canvas& Canvas::cancelFrame()
    {
        nvgCancelFrame(m_nvgCtx);
        return *this;
    }

    void Canvas::endFrame()
    {
        nvgEndFrame(m_nvgCtx);
    }

    Canvas& Canvas::beginPath()
    {
        nvgBeginPath(m_nvgCtx);
        return *this;
    }

    Canvas& Canvas::pathWinding( Winding dir)
    {
        int windingDir = NVG_CW;
        if ( dir == Winding::CCW)
            windingDir = NVG_CCW;
        nvgPathWinding(m_nvgCtx, windingDir);
        return *this;
    }

    Canvas& Canvas::clip(float x,float y,float w,float h)
    {
        local2Global(x,y);
        nvgIntersectScissor(m_nvgCtx,x,y,w,h);
        return *this;
    }

    Canvas& Canvas::resetClip()
    {
        nvgResetScissor(m_nvgCtx);
        return *this;
    }
}
