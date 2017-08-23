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
    DigitalOut  *_led;
    DigitalOut  *_motor_left_a;
    PwmOut  *_motor_left_b;
    PwmOut  *_motor_right_a;
    DigitalOut  *_motor_right_b;
    DigitalOut  *_relay_q;
    DigitalOut  *_relay_w;
    uint8_t reverse;

public:
    /**
    *contructor to changing pinname
    */
    Bot(PinName led,
        PinName motor_left_a,
        PinName motor_left_b,
        PinName motor_right_a,
        PinName motor_right_b,
        PinName relay_q,
        PinName relay_w);
    Bot();
    /**
    *Rotbot control menthods
    */
    void connection(void);
    void disconnection(void);
    void process(uint8_t g_cmd);
    void go_up(void);
    void go_down(void);
    void go_right(void);
    void go_left(void);
    void skill_q(void);
    void skill_w(void);
    void skill_e(void);
    void skill_r(void);
    void stop(void);
    void reverse_bot(void);


};
#endif /* #ifndef __Bot_H__ */

