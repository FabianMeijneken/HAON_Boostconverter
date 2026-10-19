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

	// P element
	float p_element = kP * error;

	// I element
	e_sum += error;
	float i_element = kI * e_sum;

	// D element
	float d_element = kD * (de / dt);

	// PID sum
	float PID_out = p_element + i_element + d_element;


	last_error = error;										// Save the last error
	last_PID_runtime = current_time;

	pid_return.p = p_element;
	pid_return.i = i_element;
	pid_return.d = d_element;
	pid_return.e_sum = e_sum;
	pid_return.ret = PID_out;

	return pid_return;
}
