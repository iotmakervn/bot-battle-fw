#ifndef __Bot_H__
#define __Bot_H__
#include <mbed.h>

/**
*
*This class will process the data to control robot
*
*/
class Bot {
private:
    DigitalOut *_led;
    PwmOut      *_motor_left_dir;
    PwmOut     *_motor_left_pwm;
    PwmOut     *_motor_right_pwm;
    PwmOut     *_motor_right_dir;
    DigitalOut *_relay_q;
    DigitalOut *_relay_w;
    uint8_t reverse;
    uint8_t auto_rotate;
    float convert_speed(uint8_t speed);
public:
    /**
    *contructor to changing pinname
    */
    Bot(PinName led,
        PinName pin_left_dir,
        PinName pin_left_pwm,
        PinName pin_right_pwm,
        PinName pin_right_dir,
        PinName relay_q,
        PinName relay_w);
    Bot();
    /**
    *Rotbot control menthods
    */
    void connect(void);
    void disconnect(void);
    void process(uint8_t g_cmd);
    void go_up(uint8_t speed);
    void go_down(uint8_t speed);
    void go_right(uint8_t speed);
    void go_left(uint8_t speed);
    void left(uint8_t forward, float pwm);
    void right(uint8_t forward, float pwm);
    void skill_q(void);
    void skill_w(void);
    void skill_e(void);
    void skill_r(void);
    void stop(void);
    void reverse_bot(void);


};
#endif /* #ifndef __Bot_H__ */

