#ifndef CANVAS_H
#define CANVAS_H

#include <functional>
class NVGcontext;

namespace NanoCanvas
{
    class Canvas
    {
        friend class Gradient;
    public:
        /// The function to create NanoVG context
        static std::function<NVGcontext*(int)> nvgContextCreateFunc;
        
        enum CreateFlags
        {
            /// Flag indicating if geometry based anti-aliasing is used (may not be needed when using MSAA).
            CVS_ANTIALIAS       = 1<<0,
            /// Flag indicating if strokes should be drawn using stencil buffer. The rendering will be a little
            /// slower, but path overlaps (i.e. self-intersecting or sharp turns) will be drawn just once.
            CVS_STENCIL_STROKES = 1<<1,
            /// Flag indicating that additional debug checks are done.
            CVS_DEBUG           = 1<<2,
        };
        
        enum class Winding 
        {
            /// Counter clock wise
            CCW = 1,
            /// Clock wise
            CW = 2,
        };
        
        enum class LineCap 
        {
            ///  A flat edge is added to each end of the line
            BUTT,
            /// A rounded end cap is added to each end of the line
            ROUND,
            /// A square end cap is added to each end of the line
            SQUARE
            
        };
        
        enum class LineJoin
        {
            /// Creates a beveled corner
            BEVEL,
            /// Creates a rounded corner
            ROUND,
            /// Creates a sharp corner
            MITER
        };
        
        
        /**
         * @brief Initialize Canvas with the function to create NanoVG context
         */
        static void init(const std::function<NVGcontext*(int)>& func)
        {
            nvgContextCreateFunc = func;
        }
        
        /**
         * @brief Construct a Canvas
         * @param flags Canvas flags in CreateFlags
         * @param width The width of the canvas, in pixels
         * @param height The height of the canvas, in pixels
         * @param scaleRatio The device pixel ration 
         * @return 
         */
        Canvas(int flags , float width , float height , float scaleRatio =1.0f);
        
        
    /* ------------------- Basic Path ----------------------*/
    
        /**
         * @brief Moves the path to the specified point in the canvas, without creating a line
         * 
         * The moveTo() method moves the path to the specified point in the canvas, without creating a line.
         *
         * @param x The x-coordinate of where to move the path to
         * @param y The y-coordinate of where to move the path to
         * @return The Canvas to operate with
         */
        Canvas& moveTo(float x,float y);
        
        /**
         * @brief Adds a new point and creates a line from that point to the last specified point in the canvas
         * 
         * The lineTo() method adds a new point and creates a line from that point to the last specified point in the canvas (this method does not draw the line).
         * 
         * @param x The x-coordinate of where to create the line to
         * @param y The y-coordinate of where to create the line to
         * @return The Canvas to operate with
         */
        Canvas& lineTo(float x,float y);
        
        /**
         * @brief Creates an arc/curve between two tangents on the canvas.
         * @param x1 The x-coordinate of the first tangent
         * @param y1 The y-coordinate of the first tangent
         * @param x2 The x-coordinate of the second tangent
         * @param y2 The y-coordinate of the second tangent
         * @param r  The radius of the arc
         * @return The Canvas to operate with
         */
        Canvas& arcTo(float x1,float y1,float x2,float y2,float r);
        
        /**
         * @brief Creates a quadratic Bézier curve
         * 
         * The quadraticCurveTo() method adds a point to the current path by using the specified control points that represent a quadratic Bézier curve.@n
         * A quadratic Bézier curve requires two points. 
         * The first point is a control point that is used in the quadratic Bézier calculation and the second point is the ending point for the curve. 
         * The starting point for the curve is the last point in the current path. If a path does not exist, use the beginPath() and moveTo() methods to define a starting point.
         * 
         * @param cpx The x-coordinate of the Bézier control point
         * @param cpy The y-coordinate of the Bézier control point
         * @param x The x-coordinate of the ending point
         * @param y The y-coordinate of the ending point
         * @return The Canvas to operate with
         */
        Canvas& quadraticCurveTo(float cpx,float cpy,float x, float y);
        
        /**
         * @brief Creates a cubic Bézier curve
         * 
         * The bezierCurveTo() method adds a point to the current path by using the specified control points that represent a cubic Bézier curve.
         * @n
         * A cubic bezier curve requires three points. 
         * The first two points are control points that are used in the cubic Bézier calculation and the last point is the ending point for the curve.  
         * The starting point for the curve is the last point in the current path. If a path does not exist, use the beginPath() and moveTo() methods to define a starting point.
         * 
         * @param cp1x The x-coordinate of the first Bézier control point
         * @param cp1y The y-coordinate of the first Bézier control point
         * @param cp2x The x-coordinate of the second Bézier control point
         * @param cp2y The y-coordinate of the second Bézier control point
         * @param x The x-coordinate of the ending point
         * @param y The y-coordinate of the ending point
         * @return The Canvas to operate with
         */
        Canvas& bezierCurveTo(float cp1x,float cp1y,
                              float cp2x,float cp2y,
                              float x, float y);
        
        /**
         * @brief Creates an arc/curve (used to create circles, or parts of circles)
         * The arc() method creates an arc/curve (used to create circles, or parts of circles).
         * @note Tip: To create a circle with arc(): Set start angle to 0 and end angle to 2*π.
         * @param x The x-coordinate of the center of the circle
         * @param y The y-coordinate of the center of the circle
         * @param r The radius of the circle
         * @param sAngle The starting angle, in radians (0 is at the 3 o'clock position of the arc's circle)
         * @param eAngle The ending angle, in radians
         * @param counterclockwise Optional. Specifies whether the drawing should be counterclockwise or clockwise. False is default, and indicates clockwise, while true indicates counter-clockwise.
         * @return 
         */
        Canvas& arc(float x,float y,float r,
                    float sAngle,float eAngle,bool counterclockwise = false);
        
        /**
         * @brief Close current path with a line segment
         * @return The canvas to operate with 
         */
        Canvas& closePath();
    
    
    /* ------------------- Advance Path --------------------*/
    
        /**
         * @brief Creates a rectangle
         * 
         * The rect() method creates a rectangle.
         * 
         * @param x The x-coordinate of the upper-left corner of the rectangle
         * @param y The y-coordinate of the upper-left corner of the rectangle
         * @param w The width of the rectangle, in pixels
         * @param h The height of the rectangle, in pixels
         * @return The canvas which the path be added to
         */
        Canvas& rect(float x,float y,float w,float h);
        
        /**
         * @brief Creates a  rounded rectangle
         * @param x The x-coordinate of the upper-left corner of the rectangle
         * @param y The y-coordinate of the upper-left corner of the rectangle
         * @param w The width of the rectangle, in pixels
         * @param h The height of the rectangle, in pixels
         * @param r The radius of the circle formed by 4 corners of the rounded rectangle
         * @return The canvas to create path
         */
        Canvas& roundedRect(float x,float y,float w,float h,float r);
        
        /**
         * @brief Creates a circle
         * @param cx The x-coordinate of center point for the circle
         * @param cy The y-coordinate of center point for the circle
         * @param r The radius of the circle
         * @return The canvas to create path
         */
        Canvas& circle(float cx ,float cy , float r);
        
        /**
         * @brief Creates an ellipse
         * @param cx The x-coordinate of center point for the ellipse
         * @param cy The x-coordinate of center point for the ellipse
         * @param rx The radius of the ellipse in horizentoal
         * @param ry The radius of the ellipse in vertical
         * @return The canvas to create path
         */
        Canvas& ellipse(float cx, float cy, float rx, float ry);
        
    /* ------------------- Draw Action ---------------------*/
        
        /**
         * @brief Fills the current drawing (path)
         * 
         * The fill() method fills the current drawing (path). The default color is black.
         *
         * @note If the path is not closed, the fill() method will add a line from the last point to the startpoint of the path to close the path (like closePath()), and then fill the path.
         * @return The canvas to fill
         */
        Canvas& fill();
        
        /**
         * @brief Actually draws the path you have defined
         * 
         * The stroke() method actually draws the path you have defined with all those moveTo() and lineTo() methods. The default color is black.
         * 
         * @return The canvas to stroke
         */
        Canvas& stroke();
        
        /**
         * @brief Draws a "filled" rectangle
         * 
         * The fillRect() method draws a "filled" rectangle. The default color of the fill is black.
         * 
         * @param x The x-coordinate of the upper-left corner of the rectangle
         * @param y The y-coordinate of the upper-left corner of the rectangle
         * @param w The width of the rectangle, in pixels
         * @param h The height of the rectangle, in pixels
         * @return The canvas to draw
         */
        Canvas& fillRect(float x,float y,float w,float h);
        
        /**
         * @brief Draws a rectangle (no fill)
         * 
         * The strokeRect() method draws a rectangle (no fill). The default color of the stroke is black.
         * 
         * @param x The x-coordinate of the upper-left corner of the rectangle
         * @param y The y-coordinate of the upper-left corner of the rectangle
         * @param w The width of the rectangle, in pixels
         * @param h The height of the rectangle, in pixels
         * @return The canvas to draw
         */
        Canvas& strokeRect(float x,float y,float w,float h);
        
        /**
         * @brief Clear the canvas with color
         * @param color The color to fill the hole canvas
         * @return The canvas to operate with
         */
        Canvas& clearColor(const Color& color);
        
    /*-------------------- Style Control -------------------*/
    
        /**
         * @brief Set the style of the end caps for a line
         * 
         * @param cap The line cap style
         * @return The canvas to operate with
         */
        Canvas& lineCap(LineCap cap);
        
        /**
         * @brief Set the type of corner created, when two lines meet
         * @param join The line join style
         * @return The canvas to operate with
         */
        Canvas& lineJoin(LineJoin join);
        
        /**
         * @brief Set the current line width
         * @param width The current line width, in pixels
         * @return The canvas to operate with
         */
        Canvas& lineWidth(float width);
        
        /**
         * @brief Sets the maximum miter length
         * 
         * The miter length is the distance between the inner corner and the outer corner where two lines meet.
         * @n
         * The miter length grows bigger as the angle of the corner gets smaller.
         * 
         * @note The miterLimit property works only if the lineJoin attribute is "miter".
         * @param limit A positive number that specifies the maximum miter length. If the current miter length exceeds the miterLimit, the corner will display as lineJoin "bevel"
         * @return The canvas to operate with
         */
        Canvas& miterLimit(float limit);
//        
//        /**
//         * @brief Get the current alpha or transparency value of the drawing
//         * @return The alpha vlaue of canvas
//         */
//        inline float globalAlpha()const
//        {
//            return m_alpha;
//        }
//        
        /**
         * @brief Sets the current alpha or transparency value of the drawing.
         * @param alpha new alpha vlaue of canvas
         * @return The canvas to operate with
         */
        Canvas& globalAlpha(float alpha);
        
        
        /**
         * @brief Sets the color to fill the drawing
         * @param color The color to fill with
         * @return The canvas to operate with
         */
        Canvas& fillStyle(const Color& color);
        
        /**
         * @brief  Set the color used for strokes.
         * @param color Stroke color
         * @return The canvas to operate with
         */
        Canvas& strokeStyle(const Color& color);
        
    /*--------------------- Canvas Control -----------------*/
        /**
         * @brief Begin drawing a new frame
         * 
         * Calls to Canvas drawing API should be wrapped in begineFrame() & endFrame()
         * begineFrame() defines the size of the window to render to in relation currently
         * set viewport (i.e. glViewport on GL backends). 
         * 
         * @param windowWidth Width of your window
         * @param windowHeight Height of your window
         * @return The canvas to begine frame with
         */
        Canvas& begineFrame(int windowWidth, int windowHeight);
        
        /**
         * @brief Cancels drawing the current frame.
         * @return The canvas to cancle draw
         */
        Canvas& cancelFrame();
        
        /** @brief Ends drawing flushing remaining render state. */
        void endFrame();
        
        /**
         * @brief Begins a path, or resets the current path
         * @return The canvas to create path
         */
        Canvas& beginPath();
        
        /**
         * @brief Sets the current path winding
         * @param dir CVS_CW or CVS_CW
         * @return The canvas to operate with
         */
        Canvas& pathWinding( Winding dir);
        

        /**
         * @brief Clip of a rectangular region
         * @param x The x-coordinate of the upper-left corner of the clip region
         * @param y The y-coordinate of the upper-left corner of the clip region
         * @param w The width of the clip region, in pixels
         * @param h The width of the clip region, in pixels
         * @return The canvas to clip with
         */
        Canvas& clip(float x,float y,float w,float h);
        
        /**
         * @brief Reset clip state ,remove all clip region
         * @return The canvas to reset
         */
        Canvas& resetClip();
        
        
        
    /* --------------------- State NanoVG Handling -------------------
     * 
     * 
     * NanoVG contains state which represents how paths will be rendered.
     * The state contains transform, fill and stroke styles, text and font styles,and scissor clipping.
     * 
     *-----------------------------------------------------------------/
        
        /**
         * @brief Pushe and save the current render state into a state stack.
         * @note  A matching restore() must be used to restore the state.
         * @return The canvas to save state
         */
        Canvas& save();
        
        /**
         * @brief Pop and restore current render state.
         * @return The canvas to restore state
         */
        Canvas& restore();
        
        /**
         * @brief Resets current render state to default values. Does not affect the render state stack.
         * @return The canvas to reset state
         */
        Canvas& reset();
        
        
    /*------------------ Canvas propoties ---------------------*/
    
        /**
         * @brief Check is the context avaliable
         * @return Is the context avaliable
         */
        inline bool valid()const { return m_nvgCtx; }
        
        /**
         * @brief Set canvas size
         * @param width  The width of the canvas, in pixels
         * @param height The height of the canvas, in pixels
         * @return The canvas to resize
         */
        inline Canvas& setSize(float width,float height)
        {
            m_width  = width;
            m_height = height;
            return *this;
        }
        
        /**
         * @brief Set position of the canvas 
         * @param x The x-coordinate of the upper-left corner of the rectangle
         * @param y The y-coordinate of the upper-left corner of the rectangle
         * @return The canvas to change position
         */
        inline Canvas& setPosition(float x , float y)
        {
            m_xPos = x;
            m_yPos = y;
            return *this;
        }
        
        /**
         * @brief Set scale ration of the canvas
         * 
         * Device pixel ration allows to control the rendering on Hi-DPI devices.
         * For example, GLFW returns two dimension for an opened window: window size and
         * frame buffer size. In that case you would set windowWidth/Height to the window size
         * devicePixelRatio to: frameBufferWidth / windowWidth.
         * 
         * @param ratio The device pixel ration
         * @return The canvas to set scale ration with
         */
        inline Canvas& setScaleRatio(float ratio)
        {
            m_scaleRatio = ratio;
            return *this;
        }
        
        /**
         * @brief Convert coordinates in canvas to coordinates in windows 
         * @param x [inout] The x-coordinate to convert
         * @param y [inout] The x-coordinate to convert
         */
        inline void local2Global(float& x,float& y)
        {
            x = m_xPos + x;
            y = m_yPos + y;
        }
        
        /** 
         * @brief Convert coordinates in windows to coordinates in canvas 
         * @param x [inout] The x-coordinate to convert
         * @param y [inout] The x-coordinate to convert
         */
        inline void global2Local(float& x,float& y)
        {
            x = x - m_xPos;
            y = y - m_yPos;
        }
        
        NVGcontext* nvgContext(){ return m_nvgCtx; }
        
    protected:
        NVGcontext * m_nvgCtx;
        float m_width;
        float m_height;
        float m_scaleRatio;
        float m_xPos;
        float m_yPos;
        float m_alpha;
    };
}

#endif // CANVAS_H
