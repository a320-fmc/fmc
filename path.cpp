#include "path.hpp"


color_t::color_t(VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha)
{
	m_color[0] = red;
	m_color[1] = green;
	m_color[2] = blue;
	m_color[3] = alpha;
}

int color_t::size() const
{
	return 4;
}

VGuint color_t::uint() const
{
	VGuint color;
	color += int(m_color[0] * 256) << 24;
	color += int(m_color[1] * 256) << 16;
	color += int(m_color[2] * 256) << 8;
	color += int(m_color[3] * 256);
	return color;
}

paint_fill_t::paint_fill_t(color_t color)
{
	m_paint = vgCreatePaint();
	vgSetParameteri(m_paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetColor(m_paint, color.uint());
}

VGPaintMode paint_fill_t::set_paint() const
{
	vgSetPaint(m_paint, VG_FILL_PATH);
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

	vgSetPaint(m_paint, VG_FILL_PATH);
	return VG_FILL_PATH;
}

line_t::line_t(VGCoord &from, VGCoord &to, paint_stroke_t &paint):
		m_paint(paint)
{
	VGUErrorCode err;
	m_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	err = vguLine(m_path, from.x, from.y, to.x, to.y);
}