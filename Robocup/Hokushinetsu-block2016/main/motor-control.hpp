#ifndef MOTOR_CONTROL
#define MOTOR_CONTROL

#include "mbed.h"
#include "motor.hpp"
#include "PID.h"
#include "compass.hpp"

class micon;

class MotorControl {
public:
    // constructor
    MotorControl(PinName normal, PinName reverse, PinName pwm, PinName normal2, PinName reverse2, PinName pwm2, PinName normal3, PinName reverse3, PinName pwm3, PinName sda, PinName scl, float pid_intarval_ms = 10);

    // setter
    void set_pid_gain(float Kc, float TauI, float TauD);
    bool set_angular_rate(float angular_rate);
    bool set_acceleration_rate(float acceleration_rate);

    // getter
    float get_p_gain(void);
    float get_i_gain(void);
    float get_d_gain(void);
    float get_angular_rate();
    float get_acceleration_rate();

    //adjust motor power
    void setMotorsLimit(float limit, float left_deviation, float back_deviation, float right_deviation);

    //function for move
    void start_turn(float target_angle, float corrent_angle);
    void stop_turn();
    void move(float power, float move_angle);
    void brake(float power);

private:
    Motor *motor1;
    Motor *motor2;
    Motor *motor3;

    Compass *_compass;

    // instance to realize pid
    PID* pid;
    Ticker pid_interval_ticker;

    // Straight moving system variable
    double power_;
    double move_angle_;

    // Rotating system variable
    float target_angle_;
    float omega;

    float angular_rate_;
    float acceleration_rate_;

    float Kc_;
    float TauI_;
    float TauD_;
    float pid_intarval;

    // private function prototype declaration
    void update_omega();
};

#include "micon.hpp"

/*********************  constructor   *********************/
MotorControl::MotorControl(PinName normal, PinName reverse, PinName pwm, PinName normal2, PinName reverse2, PinName pwm2, PinName normal3, PinName reverse3, PinName pwm3, PinName sda, PinName scl, float pid_intarval_ms) {
    motor1 = new Motor(normal, reverse, pwm);
    motor2 = new Motor(normal2, reverse2, pwm2);
    motor3 = new Motor(normal3, reverse3, pwm3);
    _compass = new Compass(sda, scl);

    // initalize acceleration rate
    angular_rate_ = 0.35;
    acceleration_rate_ = 0.65;

    // inital pid controller
    pid_intarval = pid_intarval_ms / 1000;
    pid = new PID(1, 0, 0, pid_intarval);
    pid->setMode (AUTO_MODE);
    pid->setInputLimits(-180, 180);
    pid->setOutputLimits(-angular_rate_, angular_rate_);
}

/*********************  setter   *********************/

void MotorControl::set_pid_gain(float Kc, float TauI, float TauD) {
    pid->setTunings(Kc, TauI, TauD);
    Kc_ = Kc;
    TauI_ = TauI;
    TauD_ = TauD;
}

bool  MotorControl::set_angular_rate(float angular_rate) {
    if (angular_rate < 0 || angular_rate > 1) return false;
    angular_rate_ = angular_rate;
    acceleration_rate_ = 1 - angular_rate;

    pid->setOutputLimits(-angular_rate_, angular_rate_);

    return true;
}

bool MotorControl::set_acceleration_rate(float acceleration_rate) {
    if (acceleration_rate < 0 || acceleration_rate > 1) return false;
    acceleration_rate_ = acceleration_rate;
    angular_rate_ = 1 - acceleration_rate;

    pid->setOutputLimits(-angular_rate_, angular_rate_);

    return true;
}

/*********************  getter   *********************/

float MotorControl::get_p_gain(void) {
    return Kc_;
}

float MotorControl::get_i_gain(void) {
    return TauI_;
}

float MotorControl::get_d_gain(void) {
    return TauD_;
}

float MotorControl::get_angular_rate() {
    return angular_rate_;
}

float MotorControl::get_acceleration_rate() {
    return acceleration_rate_;
}

/*********************  function for move   *********************/

void MotorControl::move(float power, float move_angle) {
    power_ = power;
    move_angle_ = move_angle;

    double cosine = acceleration_rate_ * power * cos(move_angle * 0.0174533);
    double sine   = acceleration_rate_ * power * sin(move_angle * 0.0174533);

    motor1->run(omega + ( 0.35 * sine - 0.6062177826491071 * cosine));
    motor2->run(omega + (-0.70 * sine));
    motor3->run(omega + ( 0.35 * sine + 0.6062177826491071 * cosine));
}

void MotorControl::start_turn(float target_angle, float corrent_angle) {
    target_angle_ = target_angle;
    pid->setSetPoint(target_angle);
    pid_interval_ticker.attach(this, &MotorControl::update_omega, pid_intarval);
}

void MotorControl::stop_turn() {
    pid_interval_ticker.detach();
    pid->reset();
}

void MotorControl::brake(float power) {
    motor1->brake(power);
    motor2->brake(power);
    motor3->brake(power);
}

/*********************  adjust motor   *********************/

void MotorControl::setMotorsLimit(float limit, float left_deviation, float back_deviation, float right_deviation) {
    motor1->set_limit(limit * left_deviation);
    motor2->set_limit(limit * back_deviation);
    motor3->set_limit(limit * right_deviation);
}

/*********************  private function   *********************/

void MotorControl::update_omega(void) {
    pid->setProcessValue(_compass->measure_angle(target_angle_));
    omega = pid->compute();
    move(power_, move_angle_);
}

#endif /*MOTOR_CONTROL*/
