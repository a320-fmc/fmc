
#include<vector>

#include "widget.hpp"
#include "path.hpp"


class horyzon_widget_t: public widget_t
{
public:
	horyzon_widget_t();

	void create_horizon_bg();
	void create_horizon_mask();
	void create_horizon_overlay();
	void create_bank_marks();
	void create_aircraft_mark();

	virtual void render();

	void update_orientation(float pitch, float bank, float slip, float heading, int ra);
	void update_fd(float pitch, float bank, float heading);
	

private:
	std::vector<path_t> m_paths;
	VGMaskLayer m_mask;

	float m_pitch, m_bank, m_slip;
	float m_target_pitch, m_target_bank, m_target_yaw; // Used for FD bars
	float m_heading, m_target_heading;
	int m_ra;

	const float horizon_width_angle;
};
