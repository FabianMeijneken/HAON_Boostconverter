/*
 * PID.h
 *
 *  Created on: 7 Oct 2026
 *      Author: fmeij
 */

#ifndef INC_PID_H_
#define INC_PID_H_



#endif /* INC_PID_H_ */


// Includes
#include "stm32f4xx_hal.h"
#include "main.h"

// Constants
#define kP .01f
#define kI .0f
#define kD .0f

// Functions
struct pid_output_type run_PID(float current_voltage, float setpoint);
