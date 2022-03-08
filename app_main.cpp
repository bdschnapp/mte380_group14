#include "app_main.hpp"

namespace main
{
    sensor::ultrasonic_init_config_s ultrasonicFrontInitConfig;
    sensor::ultrasonic_init_config_s ultrasonicSideInitConfig;

    sensor::Ultrasonic UltrasonicFront;
    sensor::Ultrasonic UltrasonicSide;

    sensor::BNO055 bno055_imu;

    sensor::Button e_stop;

    sm::sensor_data_s sensor_data;
    sm::sensor_data_s sensor_data_debounced;

    sm::MissionControl path;
    sm::StateMachine stateMachine;

    SoftwareSerial BT(2, 3); // RX | TX

    int time_us;

    void run10ms(){
        e_stop.run10ms();
        UltrasonicSide.run10ms();
        UltrasonicFront.run10ms();
        bno055_imu.run_10ms();
    }

    bool read_sensor_data(){
         if(!UltrasonicFront.get_distance(&sensor_data.ultrasonic_front))
             return SAR_NOT_OK;

         if(!UltrasonicSide.get_distance(&sensor_data.ultrasonic_side))
             return SAR_NOT_OK;

         if(!bno055_imu.get_angular_position(&sensor_data.imu_theta))
             return SAR_NOT_OK;

         if(!bno055_imu.get_angular_velocity(&sensor_data.imu_theta_dot))
             return SAR_NOT_OK;

         if(!e_stop.get_button_press(&sensor_data.button))
             return SAR_NOT_OK;

         // TODO: Sensor debounce
    }


    void app_setup(){
        Serial.begin(9600);
        BT.begin(9600);

        ultrasonicFrontInitConfig.echoPin = USF_ECHO_PIN;
        ultrasonicFrontInitConfig.trigPin = USF_TRIG_PIN;
        ultrasonicSideInitConfig.echoPin = USS_ECHO_PIN;
        ultrasonicSideInitConfig.trigPin = USS_TRIG_PIN;

        UltrasonicFront.init(ultrasonicFrontInitConfig);
        UltrasonicSide.init(ultrasonicSideInitConfig);

        bno055_imu.init()

        e_stop.init(BUTTON_PIN);

        path.init(&distances);
        stateMachine.init();
    }

    void app_loop(){
        time_us = micros();
        run10ms();

        if(!read_sensor_data()){
            stateMachine.transition_to_faulted();
        }

        stateMachine.run10ms(sensor_data_debounced);

        // this should be accurate to 4 us, however only 50 tasks are run per second. (should be 100)
        delayMicroseconds(10000 - (micros() - time_us));
    }
}
