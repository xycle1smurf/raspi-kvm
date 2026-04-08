#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define UART_LINE_MAX 128

bool uart_protocol_handle_line(const char *line, char *reply, size_t reply_size);
bool hid_type_ascii(const char *text, char *reply, size_t reply_size);
bool hid_send_keycode(uint8_t keycode, char *reply, size_t reply_size);
void hid_release_all(void);
