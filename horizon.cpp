#include <math.h>

#include "horizon.hpp"


horyzon_widget_t::horyzon_widget_t() :
	m_pitch(0), m_bank(0), m_slip(0),
	m_target_pitch(0), m_target_bank(0), m_target_yaw(0),
	m_heading(0), m_target_heading(0), m_ra(0),
	horizon_width_angle(60.f * M_PI / 180)
{
	create_horizon_bg();
}

void horyzon_widget_t::create_horizon_bg()
{
	color_t ground_color(0x603311FF);
	color_t sky_color(0x007FFFFF);
	paint_stroke_t white_stroke(color_t(0xFFFFFFFF), 0.1f);

	base_path_t *ground = new rect_t(VGCoord(-20.f, -100.f), VGCoord(40.f, 100.f), ground_color);
	m_paths.push_back(ground);

	base_path_t *sky = new rect_t(VGCoord(-20.f, 0.f), VGCoord(40.f, 100.f), sky_color);
	m_paths.push_back(sky);

	m_paths.push_back(new line_t(VGCoord(-20.f, 0.f), VGCoord(20.f, 0.f), white_stroke));
	//m_paths.push_back(new line_t(VGCoord(-5.f, 10.f), VGCoord(5.f, 10.f), white_stroke));

	float len;
	for (int ang = 1; ang <= 20; ang++)
	{
		switch (ang % 4)
		{
			case 0:
				len = 5.f;
				break;
			case 1:
			case 3:
				len = 1.5f;
				break;
			case 2:
				len = 2.5f;
				break;
		}

		std::cout << "adding line " << 2.5f * ang << " len " << len << std::endl;
		m_paths.push_back(new line_t(VGCoord(-len, 2.5f * ang), VGCoord(len, 2.5f * ang), white_stroke));
		m_paths.push_back(new line_t(VGCoord(-len, -2.5f * ang), VGCoord(len, -2.5f * ang), white_stroke));
	}
}

void horyzon_widget_t::create_horizon_mask()
{


}

void horyzon_widget_t::render(uint32_t width, uint32_t height)
{
	BasePaths::iterator it;
	std::cout << "In horizon render" << m_paths.size() << std::endl;

	m_mask.apply_mask(width, height);
	float scale = float(width) / 50;
	float pitch_scale = float(height) / 100.f;
	vgLoadIdentity();
	vgScale(scale, scale);
	vgTranslate(scale*2, scale);

	int i = 0;
	for (it = m_paths.begin(); it != m_paths.end(); it++)
	{
		std::cout << "Draw path" << i << std::endl;
		(*it)->draw();
		i++;
	}
}

horizon_mask_t::horizon_mask_t()
{
	m_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

	VGubyte aui8PathSegments[5];
	aui8PathSegments[0] = VG_MOVE_TO_ABS;
	aui8PathSegments[1] = VG_LINE_TO_ABS;
	aui8PathSegments[2] = VG_LINE_TO_ABS;
	aui8PathSegments[3] = VG_SCCWARC_TO_ABS;
	aui8PathSegments[4] = VG_CLOSE_PATH;


	VGfloat afPoints[] = {
			-20.f, 0.0f,
			20.f, 0.0f,
			20.f, 30.f,
			30.f, 30.f, 10, -20.f, 30.f,
			};
	vgAppendPathData(m_path, 5, aui8PathSegments, afPoints);
}

void horizon_mask_t::apply_mask(uint32_t width, uint32_t height)
{
	vgSeti(VG_MASKING, VG_TRUE);
	vgMask(VG_INVALID_HANDLE, VG_CLEAR_MASK, 0, 0, width, height);
	check_vg_error(vgGetError());

	vgRenderToMask(m_path, VG_FILL_PATH, VG_SET_MASK);
	check_vg_error(vgGetError());
}

void horizon_mask_t::draw()
{
}
