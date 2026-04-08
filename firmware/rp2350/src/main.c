#include <stdio.h>
#include <string.h>

#include "bsp/board_api.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include "tusb.h"

#include "uart_protocol.h"

#define UART_ID uart0
#define UART_BAUD 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

static char line_buffer[UART_LINE_MAX];
static size_t line_len = 0;

static void uart_init_local(void) {
    uart_init(UART_ID, UART_BAUD);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(UART_ID, true);
}

static void uart_poll_lines(void) {
    while (uart_is_readable(UART_ID)) {
        char ch = (char)uart_getc(UART_ID);
        if (ch == '\r') {
            continue;
        }
        if (ch == '\n') {
            line_buffer[line_len] = '\0';
            if (line_len > 0) {
                char reply[128] = {0};
                bool ok = uart_protocol_handle_line(line_buffer, reply, sizeof(reply));
                if (reply[0] != '\0') {
                    uart_puts(UART_ID, reply);
                    uart_puts(UART_ID, "\r\n");
                } else if (!ok) {
                    uart_puts(UART_ID, "ERR UNKNOWN\r\n");
                }
            }
            line_len = 0;
            continue;
        }
        if (line_len + 1 < sizeof(line_buffer)) {
            line_buffer[line_len++] = ch;
        } else {
            line_len = 0;
            uart_puts(UART_ID, "ERR ARG\r\n");
        }
    }
}

int main(void) {
    board_init();
    stdio_init_all();
    uart_init_local();
    tusb_init();

    while (true) {
        tud_task();
        uart_poll_lines();
        sleep_ms(1);
    }
}
