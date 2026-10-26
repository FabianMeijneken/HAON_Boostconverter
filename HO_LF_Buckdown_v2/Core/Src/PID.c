/*
 * PID.c
 *
 *  Created on: 7 Oct 2026
 *      Author: fmeij
 */
#include <PID.h>


uint32_t last_PID_runtime = 0;
float last_error = 0;
float e_sum = 0;
float last_PID_output = 0;

struct pid_output_type pid_return;

// https://en.wikipedia.org/wiki/PID_controller#/media/File:PID_en.svg
// A function which runs a PID controller with the p, i and d constants defined in PID.h
// @author 	Fabian Meijneken
// @ret		The system returns a struct which contains the p, i and d component, the e_sum and the PID_out. In the final product only PID_out is needed, all other values are for debugging.
struct pid_output_type run_PID(float current_voltage, float setpoint)
{
	float current_time = HAL_GetTick();
	float dt = fmax(current_time - last_PID_runtime, 1);				// delta time
	float error = setpoint - current_voltage;				// current error
	float de	 = error - last_error;							// delta error

	if (fabs(error) < PID_deadzone) {
		pid_return.p = 0;
		pid_return.i = 0;
		pid_return.d = 0;
		pid_return.e_sum = e_sum;
		pid_return.ret = last_PID_output;
		return pid_return;
	}

	bool saturated_upper = (last_PID_output >= MAX_DUTY) && (error > 0);
	bool saturated_lower = (last_PID_output <= 0.0f) && (error < 0);

	if (!saturated_upper && !saturated_lower) {
		e_sum += error;
	}

	// P element
	float p_element = kP * error;

	// I element
//	e_sum += error;
	float i_element = kI * e_sum;

	// D element
	float d_element = kD * (de / dt);

	// PID sum
	float PID_out = p_element + i_element + d_element;

	// clamp PID output between maximum values:
	PID_out = fmax(fmin(PID_out, MAX_DUTY), 0);

	// Save current values as "last"
	last_error = error;
	last_PID_runtime = current_time;
	last_PID_output = PID_out;

	// Format return struct.
	pid_return.p = p_element;
	pid_return.i = i_element;
	pid_return.d = d_element;
	pid_return.e_sum = e_sum;
	pid_return.ret = PID_out;

	return pid_return;
}
