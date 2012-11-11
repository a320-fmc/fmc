
#include <VG/openvg.h>
#include <VG/vgu.h>
#include <EGL/egl.h>

class VGCoord {
public:
	VGCoord(VGfloat x, VGfloat y);
	VGfloat x;
	VGfloat y;
};

class color_t {
public:
	color_t(VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha = 0xFF);
	int size() const;
	VGuint uint() const;
private:
	VGfloat m_color[4];
};

class paint_t {
public:
	virtual inline VGPaintMode set_paint() const = 0;
protected:
	VGPaint m_paint;
};

class paint_fill_t: public paint_t {
public:
	paint_fill_t(color_t color);
	VGPaintMode inline set_paint() const;
};

class paint_stroke_t: public paint_t {
public:
	paint_stroke_t();
	paint_stroke_t(color_t color, 
			float stroke_width,
			VGCapStyle cap_style=VG_CAP_SQUARE,
			VGJoinStyle joint_style=VG_JOIN_ROUND,
			float miter_limit = 0.0f);

	VGPaintMode inline set_paint() const;
private:
	float m_stroke_width;
	VGCapStyle m_cap_style;
	VGJoinStyle m_joint_style;
	float m_miter_limit;
};

class base_path_t {
public:
	inline virtual void draw() = 0;
protected:
	VGPath m_path;
};


template <class Paint> class path_t: public base_path_t {
public:
	path_t(Paint paint);
	inline virtual void draw();
protected:
	Paint m_paint;
};

class line_t: public path_t<paint_stroke_t>
{
public:
	line_t(VGCoord &from, VGCoord &to, paint_stroke_t &paint);
};

class rect_t: public path_t<paint_fill_t>
{
public:
	rect_t(VGCoord from, VGCoord size, paint_fill_t paint);
};
