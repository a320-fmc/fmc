#include "path.hpp"

VGCoord::VGCoord(VGfloat x, VGfloat y) :
			x(x), y(y)
{ }

color_t::color_t(VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha)
{
	m_color[0] = red;
	m_color[1] = green;
	m_color[2] = blue;
	m_color[3] = alpha;

	m_ucolor += int(m_color[0] * 256) << 24;
	m_ucolor += int(m_color[1] * 256) << 16;
	m_ucolor += int(m_color[2] * 256) << 8;
	m_ucolor += int(m_color[3] * 256);
}

color_t::color_t(VGuint color)
{
	m_color[0] = float(color >> 24) / 256;
	m_color[1] = float(color >> 16) / 256;
	m_color[2] = float(color >> 8) / 256;
	m_color[3] = float(color) / 256;

	m_ucolor = color;
}

int color_t::size() const
{
	return 4;
}

VGuint color_t::uint() const
{
	return m_ucolor;
}

paint_fill_t::paint_fill_t(color_t color)
{
	m_paint = vgCreatePaint();
	vgSetParameteri(m_paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetColor(m_paint, color.uint());
	check_vg_error(vgGetError());
}

VGPaintMode paint_fill_t::set_paint() const
{
	vgSetPaint(m_paint, VG_FILL_PATH);
	check_vg_error(vgGetError());
	return VG_FILL_PATH;
}


paint_stroke_t::paint_stroke_t(color_t color, float stroke_width,
				VGCapStyle cap_style, VGJoinStyle joint_style,
				float miter_limit):
					m_stroke_width(stroke_width),
					m_cap_style(cap_style),
					m_joint_style(joint_style),
					m_miter_limit(miter_limit)
{
	m_paint = vgCreatePaint();
	vgSetParameteri(m_paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetColor(m_paint, color.uint());
}

VGPaintMode paint_stroke_t::set_paint() const
{
	vgSetf(VG_STROKE_LINE_WIDTH, m_stroke_width);
	vgSeti(VG_STROKE_CAP_STYLE, m_cap_style);
	vgSeti(VG_STROKE_JOIN_STYLE, m_joint_style);
	vgSetf(VG_STROKE_MITER_LIMIT, m_miter_limit);

	vgSetPaint(m_paint, VG_STROKE_PATH);
	check_vg_error(vgGetError());
	return VG_STROKE_PATH;
}

template <class Paint>
path_t<Paint>::path_t(Paint paint) : m_paint(paint)
{
}


template <class Paint>
void path_t<Paint>::draw()
{
	VGPaintMode paint_mode;
	paint_mode = m_paint.set_paint();
	vgDrawPath(m_path, paint_mode);
	check_vg_error(vgGetError());
}

line_t::line_t(VGCoord from, VGCoord to, paint_stroke_t paint):
		path_t(paint)
{
	//std::cout << "Creating line" << std::endl;
	VGUErrorCode err;
	m_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	err = vguLine(m_path, from.x, from.y, to.x, to.y);
	check_vg_error(err);
}

rect_t::rect_t(VGCoord from, VGCoord size, paint_fill_t paint):
		path_t(paint)
{
	//std::cout << "Creating rect" << std::endl;
	VGUErrorCode err;
	m_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	err = vguRect(m_path, from.x, from.y, size.x, size.y);
	check_vg_error(err);
}

