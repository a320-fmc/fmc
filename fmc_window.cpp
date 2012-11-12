#include "fmc_window.hpp"

fmc_window_t::fmc_window_t(uint32_t x, uint32_t y, uint32_t width, uint32_t height) :
			window_t(x,y,width,height)
{ }

fmc_window_t::~fmc_window_t()
{ }

void fmc_window_t::render()
{
	float clearColor[4] = {0.1,0.1,0.1,1};

	eglSwapBuffers(egldisplay, eglsurface); //force EGL to recognize resize

	vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
	vgClear(0, 0, width, height);

	m_horizon.render(width, height);
	
	eglSwapBuffers(egldisplay, eglsurface);
	check_vg_error(vgGetError());

	return;
}
