/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 * Copyright (c) 2017 Victor Perez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

// Pin number of unattached pins
#define NOT_ATTACHED (-1)
#define INVALID_SERVO 255

#ifndef MAX_SERVOS
#define MAX_SERVOS 3
#endif

#define SERVO_DEFAULT_MIN_PW 544
#define SERVO_DEFAULT_MAX_PW 2400
#define SERVO_DEFAULT_MIN_ANGLE 0
#define SERVO_DEFAULT_MAX_ANGLE 180

#define HAL_SERVO_LIB H32Servo

#if defined(TARGET_HC32F46x) && NUM_SERVOS > 1
#error "HC32F46x only supports one servo"
#endif

class H32Servo
{
public:
  H32Servo();
  bool attach(const int32_t pin, const int32_t minAngle = SERVO_DEFAULT_MIN_ANGLE, const int32_t maxAngle = SERVO_DEFAULT_MAX_ANGLE);
  bool attached() const { return pin != NOT_ATTACHED; }
  bool detach();
  void move(const int32_t value);
  int32_t read() const;

private:
  void servoWrite(uint8_t pin, const uint16_t duty_cycle);

  uint8_t servoIndex; // index into the channel data for this servo
  int32_t pin = NOT_ATTACHED;
  int32_t minAngle;
  int32_t maxAngle;
  int32_t angle;

  bool setupSoftPWM(const int32_t pin);
  void pauseSoftPWM();
  void pwmSetDuty(const uint16_t duty_cycle);
};
