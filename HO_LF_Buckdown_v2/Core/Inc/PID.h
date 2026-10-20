/*
 * PID.h
 *
 *  Created on: 7 Oct 2026
 *      Author: fmeij
 */

#ifndef INC_PID_H_
#define INC_PID_H_

// Includes
#include "stm32f4xx_hal.h"
#include "main.h"

// Constants
#define kP .05f
#define kI .005f		// 0.005
#define kD .02f
#define PID_deadzone .05f		// in Volts

// Functions
struct pid_output_type run_PID(float current_voltage, float setpoint);
extern float last_error;

#endif /* INC_PID_H_ */
