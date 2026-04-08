#include "uart_protocol.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tusb.h"

static uint8_t ascii_to_hid_keycode(char c, bool *needs_shift) {
    *needs_shift = false;

    if (c >= 'a' && c <= 'z') {
        return 0x04 + (uint8_t)(c - 'a');
    }
    if (c >= 'A' && c <= 'Z') {
        *needs_shift = true;
        return 0x04 + (uint8_t)(c - 'A');
    }
    if (c >= '1' && c <= '9') {
        return 0x1e + (uint8_t)(c - '1');
    }
    if (c == '0') {
        return 0x27;
    }
    switch (c) {
        case ' ': return 0x2c;
        case '\n': return 0x28;
        case '.': return 0x37;
        case ',': return 0x36;
        case '-': return 0x2d;
        case '/': return 0x38;
        default: return 0;
    }
}

void hid_release_all(void) {
    if (tud_hid_ready()) {
        tud_hid_keyboard_report(0, 0, NULL);
    }
}

bool hid_send_keycode(uint8_t keycode, char *reply, size_t reply_size) {
    if (!tud_hid_ready()) {
        snprintf(reply, reply_size, "ERR BUSY");
        return false;
    }

    uint8_t keycodes[6] = { keycode, 0, 0, 0, 0, 0 };
    tud_hid_keyboard_report(0, 0, keycodes);
    sleep_ms(10);
    hid_release_all();
    snprintf(reply, reply_size, "OK KEY 0x%02x", keycode);
    return true;
}

bool hid_type_ascii(const char *text, char *reply, size_t reply_size) {
    if (!tud_hid_ready()) {
        snprintf(reply, reply_size, "ERR BUSY");
        return false;
    }

    size_t count = 0;
    for (const char *p = text; *p != '\0'; ++p) {
        bool shift = false;
        uint8_t keycode = ascii_to_hid_keycode(*p, &shift);
        if (keycode == 0) {
            continue;
        }
        uint8_t keycodes[6] = { keycode, 0, 0, 0, 0, 0 };
        uint8_t modifier = shift ? KEYBOARD_MODIFIER_LEFTSHIFT : 0;
        tud_hid_keyboard_report(0, modifier, keycodes);
        sleep_ms(10);
        hid_release_all();
        sleep_ms(5);
        ++count;
    }

    snprintf(reply, reply_size, "OK TYPE %u", (unsigned)count);
    return true;
}

bool uart_protocol_handle_line(const char *line, char *reply, size_t reply_size) {
    if (strcmp(line, "PING") == 0) {
        snprintf(reply, reply_size, "PONG");
        return true;
    }
    if (strcmp(line, "INFO") == 0) {
        snprintf(reply, reply_size, "INFO RP2350-HID v0 features=keyboard");
        return true;
    }
    if (strcmp(line, "RELEASE") == 0) {
        hid_release_all();
        snprintf(reply, reply_size, "OK RELEASE");
        return true;
    }
    if (strncmp(line, "TYPE ", 5) == 0) {
        return hid_type_ascii(line + 5, reply, reply_size);
    }
    if (strncmp(line, "KEY ", 4) == 0) {
        char *endptr = NULL;
        unsigned long value = strtoul(line + 4, &endptr, 0);
        if (endptr == line + 4 || value > 0xffUL) {
            snprintf(reply, reply_size, "ERR ARG");
            return false;
        }
        return hid_send_keycode((uint8_t)value, reply, reply_size);
    }

    snprintf(reply, reply_size, "ERR UNKNOWN");
    return false;
}
