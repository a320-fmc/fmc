#include "window.hpp"

class fmc_window_t : public window_t
{
public:
	fmc_window_t(uint32_t x, uint32_t y, uint32_t width, uint32_t heidht);
	virtual ~fmc_window_t();
	void render();
};
