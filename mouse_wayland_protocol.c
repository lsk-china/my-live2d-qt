/* Generated by wayland-scanner 1.22.0 */

#include <stdlib.h>
#include <stdint.h>
#include "wayland-util.h"

#ifndef __has_attribute
# define __has_attribute(x) 0  /* Compatibility with non-clang compilers. */
#endif

#if (__has_attribute(visibility) || defined(__GNUC__) && __GNUC__ >= 4)
#define WL_PRIVATE __attribute__ ((visibility("hidden")))
#else
#define WL_PRIVATE
#endif

extern const struct wl_interface wl_keyboard_interface;
extern const struct wl_interface wl_pointer_interface;
extern const struct wl_interface wl_touch_interface;

static const struct wl_interface *wayland_types[] = {
	NULL,
	&wl_pointer_interface,
	&wl_keyboard_interface,
	&wl_touch_interface,
};

static const struct wl_message wl_seat_requests[] = {
	{ "get_pointer", "n", wayland_types + 1 },
	{ "get_keyboard", "n", wayland_types + 2 },
	{ "get_touch", "n", wayland_types + 3 },
	{ "release", "5", wayland_types + 0 },
};

static const struct wl_message wl_seat_events[] = {
	{ "capabilities", "u", wayland_types + 0 },
	{ "name", "2s", wayland_types + 0 },
};

WL_PRIVATE const struct wl_interface wl_seat_interface = {
	"wl_seat", 7,
	4, wl_seat_requests,
	2, wl_seat_events,
};

