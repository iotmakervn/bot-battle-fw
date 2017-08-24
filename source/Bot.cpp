#include <mbed.h>
#include "Bot.h"
Bot::Bot(PinName led,
         PinName pin_left_dir,
         PinName pin_left_pwm,
         PinName pin_right_dir,
         PinName pin_right_pwm,
         PinName relay_q,
         PinName relay_w):
    _led(new DigitalOut(led)),
    _motor_left_dir(new PwmOut(pin_left_dir)),
    _motor_left_pwm(new PwmOut(pin_left_pwm)),
    _motor_right_pwm(new PwmOut(pin_right_pwm)),
    _motor_right_dir(new PwmOut(pin_right_dir)),
    _relay_q(new DigitalOut(relay_q)),
    _relay_w(new DigitalOut(relay_w)) {
    reverse = 0;
    auto_rotate = 0;
}

Bot::Bot() {
    //p7, p28, p25, p24, p23, p22, p21
    _led = new DigitalOut(p7);
    _motor_left_dir = new PwmOut(p28);
    _motor_left_pwm = new PwmOut(p25);
    _motor_right_pwm = new PwmOut(p24);
    _motor_right_dir = new PwmOut(p23);
    _relay_q = new DigitalOut(p22);
    _relay_w = new DigitalOut(p21);
}

void Bot::process(uint8_t g_cmd)
{
    uint8_t action = g_cmd & 0xF0;
    uint8_t speed = g_cmd & 0x0F;
    uint8_t fw = 0;
    if(action <= 0x40 && reverse) {
        action ^= 0x30;
        //0x00 ^ 0x30 = 0x30
        //0x10 ^ 0x30 = 0x20
        //0x20 ^ 0x30 = 0x10
        //0x30 ^ 0x30 = 0x00
    }
    switch(action) {
        case 0x00: /* forward */
            go_up(speed);
            break;
        case 0x10: /* left */
            go_left(speed);
            break;
        case 0x20: /* right */
            go_right(speed);
            break;
        case 0x30: /* backward */
            go_down(speed);
            break;
        case 0x40:
            auto_rotate = speed;
        case 0x50:
            stop();
            break;
        case 0x60:
            reverse = speed;
            break;
        case 0x70:
            if(speed == 0x00) {
                skill_q();
            } else if(speed == 0x01) {
                skill_w();
            } else if(speed == 0x02) {
                skill_e();
            } else if(speed == 0x03) {
                skill_r();
            }
            break;

            break;
        default:
            if(action & 0x80) {
                if(action & 0x20)
                    fw = 1;
                if(action & 0x10) { /*right motor*/
                    right(fw, convert_speed(speed));
                } else {    /*left motor*/
                    left(fw, convert_speed(speed));
                }
            }
    }


}
void Bot::connect(void)
{
    _led->write(1);
}
void Bot::disconnect(void)
{
    _led->write(0);
    if(auto_rotate) {
        Bot::skill_e();
    }
}
void Bot::go_up(uint8_t speed)
{
    float f = convert_speed(speed);
    left(1, f);
    right(1, f);
}

void Bot::go_down(uint8_t speed)
{
    float f = convert_speed(speed);
    left(0, f);
    right(0, f);
}
void Bot::go_right(uint8_t speed)
{
    float f = convert_speed(speed);
    left(1, f);
    right(0, f);
}
void Bot::go_left(uint8_t speed)
{
    float f = convert_speed(speed);
    left(0, f);
    right(1, f);
}
void Bot::stop(void)
{
    left(1, 0);
    right(1, 0);
}
void Bot::skill_q(void)
{
    _relay_q->write(!_relay_q->read());
}
void Bot::skill_w(void)
{
    _relay_w->write(!_relay_w->read());
}
void Bot::skill_e(void)
{
    go_right(15);
    _relay_q->write(1);
}
void Bot::skill_r(void)
{
    left(0, 15);
    right(0, 15);
}
void Bot::reverse_bot(void)
{
    reverse = !reverse;
}

float Bot::convert_speed(uint8_t speed)
{
    float f = speed * 0.067;
    if(f > 1) {
        f = 1;
    }
    return f;
}

void Bot::left(uint8_t forward, float pwm)
{
    if(pwm == 0) {
        _motor_left_dir->write(0);
        _motor_left_pwm->write(pwm);
    }
    if(forward) {
        _motor_left_dir->write(0);
        _motor_left_pwm->write(pwm);
    } else {
        _motor_left_dir->write(pwm);
        _motor_left_pwm->write(0);
    }
}
void Bot::right(uint8_t forward, float pwm)
{
    if(pwm == 0) {
        _motor_right_dir->write(0);
        _motor_right_pwm->write(pwm);
    }
    if(forward) {
        _motor_right_dir->write(0);
        _motor_right_pwm->write(pwm);
    } else {
        _motor_right_dir->write(pwm);
        _motor_right_pwm->write(0);
    }


}
