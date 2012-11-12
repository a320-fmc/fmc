

#include <VG/openvg.h>
#include <VG/vgu.h>
#include <EGL/egl.h>

#include "fmc.hpp"

class widget_t {
public:
	virtual void render(uint32_t width, uint32_t height) = 0;
};
