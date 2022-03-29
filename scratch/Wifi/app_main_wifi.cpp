#include "../../app_main.hpp"

namespace main_wifi
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

    debug::Logger logger;

    int time_us;

    std::string wifi_network = "";
    std::string wifi_password = "";
    IPAddress ip = (192, 168, 1, 1);
    WiFiServer server(80);

    void run10ms(){
        e_stop.run10ms();
        UltrasonicSide.run10ms();
        UltrasonicFront.run10ms();
        bno055_imu.run_10ms();
        logger.run10ms();
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

         logger.print_float(sensor_data.ultrasonic_front, "ultrasonic_front", time_us);
         logger.print_float(sensor_data.ultrasonic_side, "ultrasonic_side", time_us);
         logger.print_float(sensor_data.imu_theta, "imu_theta", time_us);
         logger.print_float(sensor_data.imu_theta_dot, "imu_theta_dot", time_us);
         logger.print_float(sensor_data.button, "button", time_us);


         // TODO: Sensor debounce
    }


    void app_setup(){
        WiFi.begin(wifi_network, wifi_password);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
        }
        if (ip == WiFi.localIP())
            server.begin();

        ultrasonicFrontInitConfig.echoPin = USF_ECHO_PIN;
        ultrasonicFrontInitConfig.trigPin = USF_TRIG_PIN;
        ultrasonicSideInitConfig.echoPin = USS_ECHO_PIN;
        ultrasonicSideInitConfig.trigPin = USS_TRIG_PIN;

        UltrasonicFront.init(ultrasonicFrontInitConfig);
        UltrasonicSide.init(ultrasonicSideInitConfig);

        bno055_imu.init()

        e_stop.init(BUTTON_PIN);

        path.init(&distances);
        logger.init();
        stateMachine.init();
    }

    void app_loop(){
        time_us = micros();
        run10ms();

        if(!read_sensor_data()){
            stateMachine.transition_to_faulted();
        }

        stateMachine.run10ms(sensor_data_debounced);

        WifiClient client = server.available();

        // only do stuff if there is an incoming request from a client
        if(client){
            while (client.connected()) {
                interface(
                        client,
                        logger.ping, F("ping: Echo a value. @data: Value. @return: Value of data."),
                        logger.get_data, F("get_data: returns a vector of all the stored sensor data. "));

            }
            // Wait for data transmission to complete.
            client.flush();
            client.stop();
        }

        // this should be accurate to 4 us, however only 50 tasks are run per second. (should be 100)
        delayMicroseconds(10000 - (micros() - time_us));
    }
}
