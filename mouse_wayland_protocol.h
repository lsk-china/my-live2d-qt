/* Generated by wayland-scanner 1.22.0 */

#ifndef WAYLAND_CLIENT_PROTOCOL_H
#define WAYLAND_CLIENT_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-client.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @page page_wayland The wayland protocol
 * @section page_ifaces_wayland Interfaces
 * - @subpage page_iface_wl_seat - 
 */
struct wl_keyboard;
struct wl_pointer;
struct wl_seat;
struct wl_touch;

#ifndef WL_SEAT_INTERFACE
#define WL_SEAT_INTERFACE
/**
 * @page page_iface_wl_seat wl_seat
 * @section page_iface_wl_seat_api API
 * See @ref iface_wl_seat.
 */
/**
 * @defgroup iface_wl_seat The wl_seat interface
 */
extern const struct wl_interface wl_seat_interface;
#endif

#ifndef WL_SEAT_CAPABILITY_ENUM
#define WL_SEAT_CAPABILITY_ENUM
enum wl_seat_capability {
	WL_SEAT_CAPABILITY_POINTER = 1,
	WL_SEAT_CAPABILITY_KEYBOARD = 2,
	WL_SEAT_CAPABILITY_TOUCH = 4,
};
#endif /* WL_SEAT_CAPABILITY_ENUM */

/**
 * @ingroup iface_wl_seat
 * @struct wl_seat_listener
 */
struct wl_seat_listener {
	/**
	 */
	void (*capabilities)(void *data,
			     struct wl_seat *wl_seat,
			     uint32_t capabilities);
	/**
	 * @since 2
	 */
	void (*name)(void *data,
		     struct wl_seat *wl_seat,
		     const char *name);
};

/**
 * @ingroup iface_wl_seat
 */
static inline int
wl_seat_add_listener(struct wl_seat *wl_seat,
		     const struct wl_seat_listener *listener, void *data)
{
	return wl_proxy_add_listener((struct wl_proxy *) wl_seat,
				     (void (**)(void)) listener, data);
}

#define WL_SEAT_GET_POINTER 0
#define WL_SEAT_GET_KEYBOARD 1
#define WL_SEAT_GET_TOUCH 2
#define WL_SEAT_RELEASE 3

/**
 * @ingroup iface_wl_seat
 */
#define WL_SEAT_CAPABILITIES_SINCE_VERSION 1
/**
 * @ingroup iface_wl_seat
 */
#define WL_SEAT_NAME_SINCE_VERSION 2

/**
 * @ingroup iface_wl_seat
 */
#define WL_SEAT_GET_POINTER_SINCE_VERSION 1
/**
 * @ingroup iface_wl_seat
 */
#define WL_SEAT_GET_KEYBOARD_SINCE_VERSION 1
/**
 * @ingroup iface_wl_seat
 */
#define WL_SEAT_GET_TOUCH_SINCE_VERSION 1
/**
 * @ingroup iface_wl_seat
 */
#define WL_SEAT_RELEASE_SINCE_VERSION 5

/** @ingroup iface_wl_seat */
static inline void
wl_seat_set_user_data(struct wl_seat *wl_seat, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) wl_seat, user_data);
}

/** @ingroup iface_wl_seat */
static inline void *
wl_seat_get_user_data(struct wl_seat *wl_seat)
{
	return wl_proxy_get_user_data((struct wl_proxy *) wl_seat);
}

static inline uint32_t
wl_seat_get_version(struct wl_seat *wl_seat)
{
	return wl_proxy_get_version((struct wl_proxy *) wl_seat);
}

/** @ingroup iface_wl_seat */
static inline void
wl_seat_destroy(struct wl_seat *wl_seat)
{
	wl_proxy_destroy((struct wl_proxy *) wl_seat);
}

/**
 * @ingroup iface_wl_seat
 */
static inline struct wl_pointer *
wl_seat_get_pointer(struct wl_seat *wl_seat)
{
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_seat,
			 WL_SEAT_GET_POINTER, &wl_pointer_interface, wl_proxy_get_version((struct wl_proxy *) wl_seat), 0, NULL);

	return (struct wl_pointer *) id;
}

/**
 * @ingroup iface_wl_seat
 */
static inline struct wl_keyboard *
wl_seat_get_keyboard(struct wl_seat *wl_seat)
{
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_seat,
			 WL_SEAT_GET_KEYBOARD, &wl_keyboard_interface, wl_proxy_get_version((struct wl_proxy *) wl_seat), 0, NULL);

	return (struct wl_keyboard *) id;
}

/**
 * @ingroup iface_wl_seat
 */
static inline struct wl_touch *
wl_seat_get_touch(struct wl_seat *wl_seat)
{
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_seat,
			 WL_SEAT_GET_TOUCH, &wl_touch_interface, wl_proxy_get_version((struct wl_proxy *) wl_seat), 0, NULL);

	return (struct wl_touch *) id;
}

/**
 * @ingroup iface_wl_seat
 */
static inline void
wl_seat_release(struct wl_seat *wl_seat)
{
	wl_proxy_marshal_flags((struct wl_proxy *) wl_seat,
			 WL_SEAT_RELEASE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_seat), WL_MARSHAL_FLAG_DESTROY);
}

#ifdef  __cplusplus
}
#endif

#endif