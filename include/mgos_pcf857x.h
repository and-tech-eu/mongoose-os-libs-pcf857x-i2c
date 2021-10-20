/*
 * Copyright 2019 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include "mgos.h"
#include "mgos_gpio.h"
#include "mgos_i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mgos_pcf857x;

/*
 * Initialize a PCF857X on the I2C bus `i2c` at address specified in `i2caddr`
 * parameter (default PCF857X is on address 0x20). The device will be polled for
 * validity, upon success a new `struct mgos_pcf857x` is allocated and
 * returned. If the device could not be found, NULL is returned.
 * To install an interrupt handler for the chip, set int_gpio to any valid GPIO
 * pin. Set it to -1 to disable interrupts.
 */
struct mgos_pcf857x *mgos_pcf8574_create(struct mgos_i2c *i2c, uint8_t i2caddr, int int_gpio);
struct mgos_pcf857x *mgos_pcf8575_create(struct mgos_i2c *i2c, uint8_t i2caddr, int int_gpio);

/*
 * Destroy the data structure associated with a PCF857X device. The reference
 * to the pointer of the `struct mgos_pcf857x` has to be provided, and upon
 * successful destruction, its associated memory will be freed and the pointer
 * set to NULL and true will be returned.
 */
bool mgos_pcf857x_destroy(struct mgos_pcf857x **dev);

/* Emit a logline with the pin and io register stat
 */
void mgos_pcf857x_print_state(struct mgos_pcf857x *dev);

/* These follow `mgos_gpio.h` definitions. */
bool mgos_pcf857x_gpio_set_mode(struct mgos_pcf857x *dev, int pin, enum mgos_gpio_mode mode);
bool mgos_pcf857x_gpio_setup_output(struct mgos_pcf857x *dev, int pin, bool level);
bool mgos_pcf857x_gpio_setup_input(struct mgos_pcf857x *dev, int pin, enum mgos_gpio_pull_type pull_type);
bool mgos_pcf857x_gpio_read(struct mgos_pcf857x *dev, int pin);
void mgos_pcf857x_gpio_write(struct mgos_pcf857x *dev, int pin, bool level);
bool mgos_pcf857x_gpio_toggle(struct mgos_pcf857x *dev, int pin);

bool mgos_pcf857x_gpio_set_int_handler(struct mgos_pcf857x *dev, int pin, enum mgos_gpio_int_mode mode, mgos_gpio_int_handler_f cb, void *arg);
bool mgos_pcf857x_gpio_enable_int(struct mgos_pcf857x *dev, int pin);
bool mgos_pcf857x_gpio_disable_int(struct mgos_pcf857x *dev, int pin);
void mgos_pcf857x_gpio_clear_int(struct mgos_pcf857x *dev, int pin);
void mgos_pcf857x_gpio_remove_int_handler(struct mgos_pcf857x *dev, int pin, mgos_gpio_int_handler_f *old_cb, void **old_arg);
bool mgos_pcf857x_gpio_set_button_handler(struct mgos_pcf857x *dev, int pin, enum mgos_gpio_pull_type pull_type, enum mgos_gpio_int_mode int_mode, int debounce_ms, mgos_gpio_int_handler_f cb, void *arg);

/*
 * A utility function that takes care of blinking an LED.
 * Set either on_ms or off_ms to 0 to disable
 */
bool mgos_pcf857x_gpio_blink(struct mgos_pcf857x *dev, int pin, int on_ms, int off_ms);

#ifdef __cplusplus
}
#endif
