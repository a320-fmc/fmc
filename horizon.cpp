#include <math.h>

#include "horizon.hpp"


horyzon_widget_t::horyzon_widget_t() :
	m_pitch(0), m_bank(0), m_slip(0),
	m_target_pitch(0), m_target_bank(0), m_target_yaw(0),
	m_heading(0), m_target_heading(0), m_ra(0),
	horizon_width_angle(60.f * M_PI / 180)
{

}

void horyzon_widget_t::create_horizon_bg()
{
	color_t ground_color(0x60, 0x33, 0x11);
	color_t sky_color(0x00, 0x7F, 0xFF);

	base_path_t *ground = new rect_t(VGCoord(-20.f, -100.f), VGCoord(40.f, 100.f), ground_color);
	m_paths.push_back(ground);

	base_path_t *sky = new rect_t(VGCoord(-20.f, 0.f), VGCoord(40.f, 100.f), sky_color);
	m_paths.push_back(sky);
}

void horyzon_widget_t::render()
{
	BasePaths::iterator it;

	for (it = m_paths.begin(); it != m_paths.end(); it++)
	{
		(*it)->draw();
	}
}

