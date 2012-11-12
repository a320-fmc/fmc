
#include <bcm_host.h>

#include <VG/openvg.h>
#include <VG/vgu.h>
#include <EGL/egl.h>




class window_t {
public:
	window_t(uint32_t x, uint32_t y, uint32_t width, uint32_t heidht);
	virtual ~window_t();

	virtual void render() = 0;
protected:
	int32_t		x, y;
	int32_t		width, height;

	EGL_DISPMANX_WINDOW_T nativewindow;
	EGLDisplay	egldisplay;
	EGLConfig	eglconfig;
	EGLSurface	eglsurface;
	EGLContext	eglcontext;
};
