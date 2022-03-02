#ifndef __LIB_PID_HPP__
#define __LIB_PID_HPP__

#define DIRECT 0
#define REVERSE 1

#include "Arduino.h"

namespace pid {
	
	class PID {
	public:

		//empty constructor, use SetTunings and SetTarget methods to assign values.
		PID();
		~PID();

		//Calculates PID values, should be ran every 10ms, but supports other timings
		double Compute(double InputVal);

		//Setter function for kp, ki and kd
		void SetTunings(double kp, double ki, double kd);

		//sets the default minimum sample time, currently defaults to 9ms. 
		void SetSampleTime(int NewSampleTime);

		//set minimum and maximum output values, defaults to 0, 1
		void SetOutputLimits(double Min, double Max);

		//rests values, based on current input, and zeros accumulated error
		void Reset();

		//set direction to direct or reverse, default is direct
		void SetControlDirection(int Direction);

		//sets the controllers target value
		void SetTarget(double SetPointVal);

		//sets a tolerance where the controller will return zero is error is less
		void SetTolerance(double ToleranceVal);

	private:
		unsigned long lastTime;
		double Input, Output, Setpoint;
		double ITerm, lastInput;
		double kp, ki, kd;
		int SampleTime = 9; //10ms
		double outMin = 0;
		double outMax = 1.0;
		int controllerDirection = DIRECT;
		double tolerance = 0;
	};


} // namespace pid