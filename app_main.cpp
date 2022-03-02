#include "app_main.hpp"

namespace main
{
    sensor::ultrasonic_init_config_s ultrasonicFrontInitConfig;
    sensor::ultrasonic_init_config_s ultrasonicSideInitConfig;

    sensor::Ultrasonic UltrasonicFront;
    sensor::Ultrasonic UltrasonicSide;

    sensor::BNO055 bno055_imu;

    sm::sensor_data_s sensor_data;
    sm::sensor_data_s sensor_data_debounced;

    sm::MissionControl path;
    int distances[PATH_LENGTH];
    sm::StateMachine stateMachine;

    debug::Logger logger;

    int time_us;

    wifi_network = "";
    wifi_password = "";
    IPAddress ip = (192, 168, 1, 1);
    WifiServer server(80);

    void run10ms(){
        UltrasonicSide.run10ms();
        UltrasonicFront.run10ms();
    }

    void read_sensor_data(){
         if(!UltrasonicFront.get_distance(&sensor_data.ultrasonic_front))
             return SAR_NOT_OK;

         if(!UltrasonicSide.get_distance(&sensor_data.ultrasonic_side))
             return SAR_NOT_OK;

         if(!bno055_imu.get_angular_position(&sensor_data.imu_theta))
             return SAR_NOT_OK;

         if(!bno055_imu.get_angular_velocity(&sensor_data.imu_theta_dot))
             return SAR_NOT_OK;

         logger.print_float(sensor_data.ultrasonic_front, "ultrasonic_front", time_us);
         logger.print_float(sensor_data.ultrasonic_side, "ultrasonic_side", time_us);


         // TODO: Sensor debounce
    }


    void app_setup(){
        WiFi.begin(wifi_network, wifi_password);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
        }
        if (ip == Wifi.localIP())
            server.begin();

        ultrasonicFrontInitConfig.echoPin = 13;
        ultrasonicFrontInitConfig.trigPin = 12;
        ultrasonicSideInitConfig.echoPin = 11;
        ultrasonicSideInitConfig.trigPin = 10;

        UltrasonicFront.init(ultrasonicFrontInitConfig);
        UltrasonicSide.init(ultrasonicSideInitConfig);

        bno055_imu.init()

        distances = {0,0,0,0,0,0,0,0,0,0,0,0};
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

        WifiClient client = server.accept();
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

        delayMicroseconds(10000 - (micros() - time_us));
    }
}
