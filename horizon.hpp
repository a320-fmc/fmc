
#include<vector>
#include <memory>

#include "widget.hpp"
#include "path.hpp"

class horizon_mask_t: public base_path_t
{
public:
	horizon_mask_t();
	void apply_mask(uint32_t width, uint32_t height);
	void draw();
};

class horyzon_widget_t: public widget_t
{
typedef std::vector<base_path_t *> BasePaths;

public:
	horyzon_widget_t();

	void create_horizon_bg();
	void create_horizon_mask();
	void create_horizon_overlay();
	void create_bank_marks();
	void create_aircraft_mark();

	virtual void render(uint32_t width, uint32_t height);

	void update_orientation(float pitch, float bank, float slip, float heading, int ra);
	void update_fd(float pitch, float bank, float heading);
	

private:
	BasePaths m_background;
	BasePaths m_background_overlay;
	BasePaths m_overlay;
	//VGMaskLayer m_mask;
	horizon_mask_t m_mask;

	float m_pitch, m_bank, m_slip;
	float m_target_pitch, m_target_bank, m_target_yaw; // Used for FD bars
	float m_heading, m_target_heading;
	int m_ra;

	const float horizon_width_angle;

	color_t m_ground_color;
	color_t m_sky_color;
	color_t m_black_color;
	paint_stroke_t m_white_stroke;
	paint_stroke_t m_yellow_stroke;
};

