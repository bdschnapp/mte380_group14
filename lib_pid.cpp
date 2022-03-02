#include "lib_pid.hpp"

namespace pid {
    PID

        void Compute(double InputVal)
    {
        Input = InputVal;
        unsigned long now = millis();
        int timeChange = (now - lastTime);
        if (timeChange >= SampleTime)
        {
            /*Compute all the working error variables*/
            double error = Setpoint - Input;
            ITerm += (ki * error);
            if (ITerm > outMax) ITerm = outMax;
            else if (ITerm < outMin) ITerm = outMin;
            double dInput = (Input - lastInput);

            /*Compute PID Output*/
            Output = kp * error + ITerm - kd * dInput;
            if (Output > outMax) Output = outMax;
            else if (Output < outMin) Output = outMin;

            /*Remember some variables for next time*/
            lastInput = Input;
            lastTime = now;
        }
        if (error < Tolerance) {
            return 0;
        }
        else{
            return Output;
        }
    }

    void SetTunings(double Kp, double Ki, double Kd)
    {
        if (Kp < 0 || Ki < 0 || Kd < 0) return;

        double SampleTimeInSec = ((double)SampleTime) / 1000;
        kp = Kp;
        ki = Ki * SampleTimeInSec;
        kd = Kd / SampleTimeInSec;

        if (controllerDirection == REVERSE)
        {
            kp = (0 - kp);
            ki = (0 - ki);
            kd = (0 - kd);
        }
    }

    void SetSampleTime(int NewSampleTime)
    {
        if (NewSampleTime > 0)
        {
            double ratio = (double)NewSampleTime
                / (double)SampleTime;
            ki *= ratio;
            kd /= ratio;
            SampleTime = (unsigned long)NewSampleTime;
        }
    }

    void SetOutputLimits(double Min, double Max)
    {
        if (Min > Max) return;
        outMin = Min;
        outMax = Max;

        if (Output > outMax) Output = outMax;
        else if (Output < outMin) Output = outMin;

        if (ITerm > outMax) ITerm = outMax;
        else if (ITerm < outMin) ITerm = outMin;
    }

    void Reset()
    {
        lastInput = Input;
        ITerm = Output;
        if (ITerm > outMax) ITerm = outMax;
        else if (ITerm < outMin) ITerm = outMin;
    }

    void SetControllerDirection(int Direction)
    {
        controllerDirection = Direction;
    }

    void SetTarget(double SetPointVal)
    {
        SetPoint = SetPointVal;
    }

    void SetTolerance(double ToleranceVal)
    {
        Tolerance = ToleranceVal;
    }

} // namespace pid