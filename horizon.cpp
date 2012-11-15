#include <math.h>

#include "horizon.hpp"


horyzon_widget_t::horyzon_widget_t() :
	horizon_radius(20.f / sin(deg_to_rad(60.f))),
	m_mask(horizon_radius),
	m_pitch(10), m_bank(10), m_slip(0),
	m_target_pitch(0), m_target_bank(0), m_target_yaw(0),
	m_heading(0), m_target_heading(0), m_ra(0),
	m_ground_color(0x603311FF),
	m_sky_color(0x007FFFFF),
	m_black_color(0x000000FF),
	m_white_stroke(0xFFFFFFFF, 0.2f),
	m_yellow_stroke(color_t(0xFFFF00FF), 0.2f)
{
	create_horizon_bg();
	create_horizon_overlay();
}

void horyzon_widget_t::create_horizon_bg()
{
	color_t ground_color(0x603311FF);
	color_t sky_color(0x007FFFFF);
	paint_stroke_t white_stroke(color_t(0xFFFFFFFF), 0.2f);

	base_path_t *ground = new rect_t(VGCoord(-30.f, -100.f), VGCoord(60.f, 100.f), ground_color);
	m_background.push_back(ground);

	base_path_t *sky = new rect_t(VGCoord(-30.f, 0.f), VGCoord(60.f, 100.f), sky_color);
	m_background.push_back(sky);

	m_background.push_back(new line_t(VGCoord(-30.f, 0.f), VGCoord(30.f, 0.f), white_stroke));

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

		//std::cout << "adding line " << 2.5f * ang << " len " << len << std::endl;
		m_background.push_back(new line_t(VGCoord(-len, 2.5f * ang), VGCoord(len, 2.5f * ang), white_stroke));
		m_background.push_back(new line_t(VGCoord(-len, -2.5f * ang), VGCoord(len, -2.5f * ang), white_stroke));
	}

	m_background_overlay.push_back(new rect_t(VGCoord(-30.f, 18.f), VGCoord(60.f, 82.f), sky_color));
	m_background_overlay.push_back(new line_t(VGCoord(-30.f, 18.f), VGCoord(30.f, 18.f), white_stroke));

	m_background_overlay.push_back(new rect_t(VGCoord(-30.f, -100.f), VGCoord(60.f, 82.f), ground_color));
	m_background_overlay.push_back(new line_t(VGCoord(-30.f, -18.f), VGCoord(30.f, -18.f), white_stroke));
}

void horyzon_widget_t::create_horizon_mask()
{
	//m_background.push_back(new line_t(VGCoord(-20.f, 0.f), VGCoord(20.f, 0.f), white_stroke));
}

void horyzon_widget_t::create_horizon_overlay()
{
	color_t ground_color(0x603311FF);
	color_t sky_color(0x007FFFFF);
	color_t black_color(0x000000FF);
	paint_stroke_t yellow_stroke(color_t(0xFFFF00FF), 0.2f);

	std::vector<VGCoord> coords;

	coords.push_back(VGCoord(-20.f, 0.7f));
	coords.push_back(VGCoord(-10.f, 0.7f));
	coords.push_back(VGCoord(-10.f, -2.3f));
	coords.push_back(VGCoord(-11.4f, -2.3f));
	coords.push_back(VGCoord(-11.4f, -0.7f));
	coords.push_back(VGCoord(-20.f, -0.7f));
	//coords.push_back(VGCoord(-20.f, 0.5f));

	m_overlay.push_back(new polygon_t(coords, black_color));
	m_overlay.push_back(new polyline_t(coords, yellow_stroke, false));

	std::vector<VGCoord> rcoords;
	std::for_each(coords.begin(), coords.end(),
				[&rcoords](VGCoord c) {
					rcoords.push_back(VGCoord(-c.x, c.y));
				}
			);
	
	m_overlay.push_back(new polygon_t(rcoords, black_color));
	m_overlay.push_back(new polyline_t(rcoords, yellow_stroke, false));

	m_overlay.push_back(new circle_t<paint_fill_t>(VGCoord(0, 0), 1.4f, black_color));
	m_overlay.push_back(new circle_t<paint_stroke_t>(VGCoord(0, 0), 1.4f, yellow_stroke));
}

void horyzon_widget_t::render(uint32_t width, uint32_t height)
{
	//BasePaths::iterator it;
	//std::cout << "In horizon render" << m_background.size() << std::endl;

	float scale = float(width) / 100;
	float pitch_scale = float(height) / 100.f;

	vgLoadIdentity();
	vgScale(scale, scale);
	vgTranslate(50, 50);
	vgRotate(-m_bank);
	vgTranslate(0, -m_pitch);

	int i = 0;
	for (auto it = m_background.begin(); it != m_background.end(); it++)
	{
		//std::cout << "Draw path" << i << std::endl;
		(*it)->draw();
		i++;
	}

	vgLoadIdentity();
	vgScale(scale, scale);
	vgTranslate(50, 50);
	vgRotate(-m_bank);
	i = 0;
	std::for_each(m_background_overlay.begin(), m_background_overlay.end(),
				[&i](base_path_t* it) {
					//std::cout << "Draw bg overlay" << i++ << std::endl;
					it->draw();
				}
			);

	vgLoadIdentity();
	vgScale(scale, scale);
	vgTranslate(50, 50);

	i = 0;
	for (auto it = m_overlay.begin(); it != m_overlay.end(); it++)
	{
		//std::cout << "Draw overlay" << i << std::endl;
		(*it)->draw();
		i++;
	}
		
	m_mask.apply_mask(width, height);
}

horizon_mask_t::horizon_mask_t(float horizon_radius)
{
	m_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

	VGubyte aui8PathSegments[5];
	aui8PathSegments[0] = VG_MOVE_TO_ABS;
	aui8PathSegments[1] = VG_SCCWARC_TO_ABS;
	aui8PathSegments[2] = VG_LINE_TO_ABS;
	aui8PathSegments[3] = VG_SCCWARC_TO_ABS;
	aui8PathSegments[4] = VG_CLOSE_PATH;

	float vertical = horizon_radius*cos(deg_to_rad(60));

	VGfloat afPoints[] = {
			-20.f, -vertical,
			horizon_radius, horizon_radius, 10, 20.f, -vertical,
			20.f, vertical,
			horizon_radius, horizon_radius, 10, -20.f, vertical,
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
