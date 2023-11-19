//
// Created by lsk on 9/7/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <wayland-client.h>

struct wl_display *display = NULL;
struct wl_seat *seat = NULL;
struct wl_pointer *pointer = NULL;
static void pointer_motion_handler (void *data, struct wl_pointer *ptr, uint32_t time, wl_fixed_t x, wl_fixed_t y) {
    printf("pointer_motion_event: x: %d, y: %d.", wl_fixed_to_int(x), wl_fixed_to_int(y));
}

static const struct wl_pointer_listener pointer_listener = {
        .motion = pointer_motion_handler
};


static void global_registry_handler(void *data, struct wl_registry *registry, uint32_t id, const char *interface, uint32_t version) {
    if (strcmp(interface, "wl_seat") == 0) {
        printf("got registry event for wl_seat\n");
        seat = wl_registry_bind(registry, id, &wl_seat_interface, 1);
        pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(pointer, &pointer_listener, NULL);
    }
}

static const struct wl_registry_listener registry_listener = {
        global_registry_handler,
        NULL
};

static void handle_int(int sig) {
    wl_display_disconnect(display);
    exit(0);
}

int main() {
    display = wl_display_connect(NULL);
    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);
    wl_display_dispatch(display);
    wl_display_roundtrip(display);
    if (seat == NULL) {
        fprintf(stderr, "cant get seat\n");
    }
    /*
	pointer = wl_seat_get_pointer(seat);
	if (pointer == NULL) {
		fprintf(stderr, "cant get pointer\n");
		exit(1);
	}
	wl_pointer_add_listener(pointer, &pointer_listener, NULL);
	*/
    signal(SIGINT, handle_int);
    while (1) {}
    return 0;
}
