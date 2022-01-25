#include "TimeOfFlight.h"

TimeOfFlight::TimeOfFlight(tof_init_config_s tof_init_config) {
    sensor = Adafruit_VL53L0X();
    distance = 0;
    range_state = TOF_LONG_RANGE;
    for(int i = 0; i < NUM_PREV_DISTANCE; i++){
        prev_distances[i] = i; // dont set all to same value, otherwise check_prev_distances will fail
    }
    init_config = tof_init_config;
    init(tof_init_config);
}

//private
void TimeOfFlight::reset_prev_distances() {
    for(int i = 0; i < NUM_PREV_DISTANCE; i++){
        prev_distances[i] = i; // dont set all to same value, otherwise check_prev_distances will fail
    }
}

void TimeOfFlight::update_prev_distances(float cur_distance) {
    for(int i = 0; i < NUM_PREV_DISTANCE; i++){
        if(i == (NUM_PREV_DISTANCE - 1))
            prev_distances[i] = cur_distance;
        else
            prev_distances[i] = prev_distances[i+1];
    }
}

bool TimeOfFlight::check_prev_distances() {
    int count_same = 0;
    for(int i = 0; i < (NUM_PREV_DISTANCE - 1); i++){
        if(prev_distances[i] == prev_distances[i+1])
            count_same++;
    }
    if(count_same == (NUM_PREV_DISTANCE -1))
        return ULTRASONIC_NOT_OK;
    return ULTRASONIC_OK;
}

bool TimeOfFlight::check_scheduled() {
    schedule_count++;
    if(schedule_count == (schedule_period + 1)){
        return SCHEDULED;
    }
    return NOT_SCHEDULED;
}

bool TimeOfFlight::set_long_range() {
    // need equivalent from arduino libraries of Vcselperiod Pre and Final Range. these are from polulu.
    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);\
    range_state = TOF_LONG_RANGE;
}

bool TimeOfFlight::set_short_range() {
    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 14);
    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 10);
    range_state = TOF_SHORT_RANGE;
}

//public
bool TimeOfFlight::init(tof_init_config_s tof_init_config) {
    if(!enable())
        return TOF_NOT_OK;

    if(!sensor.begin())
        return TOF_NOT_OK;

    set_schedule_period(tof_init_config.schedule_period);

    if(!set_range_state(tof_init_config.range_state))
        return TOF_NOT_OK;

    return TOF_OK;
}

bool TimeOfFlight::reset() {
    shutdown();
    reset_prev_distances();
    if(!init(init_config)){
        if(!init(init_config)){
            return TOF_NOT_OK;
        }
    }
    return TOF_OK;
}

void TimeOfFlight::run10ms() {
    if(check_scheduled() == SCHEDULED){
        sensor.rangingTest(&measure, false);
        if (measure.RangeStatus != 4){
            distance = measure.RangeMilliMeter;
            schedule_count = 0;
        }
        else{
            // make task scheduled next cycle, and set distance to prev distance
            schedule_count--;
            distance = prev_distances[NUM_PREV_DISTANCE - 1];
        }
        update_prev_distances(distance);
    }
}

void TimeOfFlight::set_schedule_period(int period) { // milliseconds/10
    schedule_period = period;
    sensor.setMeasurementTimingBudget(period * 1000) // microseconds
}

bool TimeOfFlight::set_range_state(bool range) {
    if(range == TOF_LONG_RANGE){
        if(!set_long_range())
            return TOF_NOT_OK;
    }
    if(range == TOF_SHORT_RANGE){
        if(!set_short_range())
            return TOF_NOT_OK;
    }
    if (range_state != range){
        return TOF_NOT_OK;
    }
    return TOF_OK;
}

bool TimeOfFlight::get_range_state(bool &range) {
    range = range_state;
    return TOF_OK;
}

bool TimeOfFlight::get_distance(float &value) {
    if (check_prev_distances() == TOF_OK){
        value = distance;
        return TOF_OK;
    }
    value = 0;
    return TOF_NOT_OK;
}

bool TimeOfFlight::shutdown() {
    digitalWrite(init_config.shutdown_pin, LOW);
    delayMs(10);
    return TOF_OK;
}

bool TimeOfFlight::enable() {
    pinMode(init_config.shutdown_pin, INPUT);
    digitalWrite(init_config.shutdown_pin, HIGH);
}

bool TimeOfFlight::set_address(int new_address) {
    if(!sensor.setAddress(new_address))
        return TOF_NOT_OK;
    return TOF_OK;
}