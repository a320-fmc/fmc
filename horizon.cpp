#include <math.h>

#include "horizon.hpp"


horyzon_widget_t::horyzon_widget_t() :
	m_pitch(0), m_bank(0), m_slip(0),
	m_target_pitch(0), m_target_bank(0), m_target_yaw(0),
	m_heading(0), m_target_heading(0), m_ra(0),
	horizon_width_angle(60.f * M_PI / 180)
{

}

void horyzon_widget_t::render()
{


}

