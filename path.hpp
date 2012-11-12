
#include <algorithm>
#include <vector>

#include <VG/openvg.h>
#include <VG/vgu.h>
#include <EGL/egl.h>

#include "fmc.hpp"

class VGCoord {
public:
	VGCoord(VGfloat x, VGfloat y);
	VGfloat x;
	VGfloat y;
};

class color_t {
public:
	color_t(VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha = 0.f);
	color_t(VGuint color);
	int size() const;
	VGuint uint() const;
private:
	VGfloat m_color[4];
	VGuint m_ucolor;
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
	VGPaintMode set_paint() const;
};

class paint_stroke_t: public paint_t {
public:
	paint_stroke_t();
	paint_stroke_t(color_t color, 
			float stroke_width,
			VGCapStyle cap_style=VG_CAP_SQUARE,
			VGJoinStyle joint_style=VG_JOIN_ROUND,
			float miter_limit = 0.0f);

	VGPaintMode set_paint() const;
private:
	float m_stroke_width;
	VGCapStyle m_cap_style;
	VGJoinStyle m_joint_style;
	float m_miter_limit;
};

class base_path_t {
public:
	virtual void draw() = 0;
protected:
	VGPath m_path;
};


template <class Paint> class path_t: public base_path_t {
public:
	path_t(Paint paint);
	virtual void draw();
protected:
	Paint m_paint;
};

class line_t: public path_t<paint_stroke_t>
{
public:
	line_t(VGCoord from, VGCoord to, paint_stroke_t paint);
};

class rect_t: public path_t<paint_fill_t>
{
public:
	rect_t(VGCoord from, VGCoord size, paint_fill_t paint);
};

template <class Paint>
class circle_t: public path_t<Paint>
{
typedef path_t<Paint> t_path_t;
using t_path_t::m_path;
public:
	circle_t(VGCoord center, VGfloat radius, Paint paint):
		t_path_t(paint)
	{
		VGUErrorCode err;

		m_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
		err = vguEllipse(m_path, center.x, center.y, radius, radius);
		check_vg_error(err);
	}
};

template <class Paint>
class poly_t: public path_t<Paint>
{
typedef path_t<Paint> t_path_t;
using t_path_t::m_path;

public:
	poly_t(std::vector<VGCoord> coords, Paint paint, bool close=true):
		t_path_t(paint)
	{
		std::vector<VGubyte> commands(coords.size(), VG_LINE_TO_ABS);
		commands[0] = VG_MOVE_TO_ABS;
		if (close)
			commands.push_back(VG_CLOSE_PATH);

		std::vector<VGfloat> points;
		std::for_each(coords.begin(), coords.end(),
				[&points](VGCoord c) { 
					points.push_back(c.x);
					points.push_back(c.y);
				}
			);

		m_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
		vgAppendPathData(m_path, coords.size(), &commands[0], &points[0]);
	}
};

typedef poly_t<paint_fill_t> polygon_t;
typedef poly_t<paint_stroke_t> polyline_t;

