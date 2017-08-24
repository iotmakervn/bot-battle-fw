#include <mbed.h>
#include "Bot.h"
Bot::Bot(PinName led,
         PinName motor_left_a,
         PinName motor_left_b,
         PinName motor_right_a,
         PinName motor_right_b,
         PinName relay_q,
         PinName relay_w):
    _led(new DigitalOut(led)),
    _motor_left_a(new DigitalOut(motor_left_a)),
    _motor_left_b(new PwmOut(motor_left_b)),
    _motor_right_a(new PwmOut(motor_right_a)),
    _motor_right_b(new DigitalOut(motor_right_b)),
    _relay_q(new DigitalOut(relay_q)),
    _relay_w(new DigitalOut(relay_w)) {
    reverse = 0;
    auto_rotate = 0;
}

Bot::Bot() {
    //p7, p28, p25, p24, p23, p22, p21
    _led = new DigitalOut(p7);
    _motor_left_a = new DigitalOut(p28);
    _motor_left_b = new PwmOut(p25);
    _motor_right_a = new PwmOut(p24);
    _motor_right_b = new DigitalOut(p23);
    _relay_q = new DigitalOut(p22);
    _relay_w = new DigitalOut(p21);
}

void Bot::process(uint8_t g_cmd)
{
    uint8_t action = g_cmd & 0xF0;
    uint8_t speed = g_cmd & 0x0F;

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
        case 0x50:
            stop();
            break;
        case 0x80:
            reverse = speed;
            break;
        case 0x90:
            auto_rotate = speed;
            break;
    }


}
void Bot::connect(void)
{
    _led->write(1);
}
void Bot::disconnect(void)
{
    Bot::skill_e();
    _led->write(0);
    if(auto_rotate) {
        go_right(15);
    }
}
void Bot::go_up(uint8_t speed)
{
    float f = convert_speed(speed);
    _motor_left_a->write(0);
    _motor_left_b->write(f);
    _motor_right_a->write(0);
    _motor_right_b->write(f);
}
void Bot::go_down(uint8_t speed)
{
    float f = convert_speed(speed);
    _motor_left_a->write(f);
    _motor_left_b->write(0);
    _motor_right_a->write(f);
    _motor_right_b->write(0);
}
void Bot::go_right(uint8_t speed)
{
    float f = convert_speed(speed);
    _motor_left_a->write(0);
    _motor_left_b->write(f);
    _motor_right_a->write(f);
    _motor_right_b->write(0);
}
void Bot::go_left(uint8_t speed)
{
    float f = convert_speed(speed);
    _motor_left_a->write(f);
    _motor_left_b->write(0);
    _motor_right_a->write(0);
    _motor_right_b->write(f);
}
void Bot::stop(void)
{
    _motor_left_a->write(1);
    _motor_left_b->write(1);
    _motor_right_a->write(1);
    _motor_right_b->write(1);
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
    _motor_left_a->write(0.5);
    _motor_left_b->write(1);
    _motor_right_a->write(0);
    _motor_right_b->write(1);
}
void Bot::reverse_bot(void)
{
    reverse = !reverse;
}

float Bot::convert_speed(uint8_t speed)
{
    float f = speed * 0.06 + 0.1;
    if(f > 1) {
        f = 1;
    }
    return f;
}
