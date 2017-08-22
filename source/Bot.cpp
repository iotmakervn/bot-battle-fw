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
		_motor_left_b(new DigitalOut(motor_left_b)), 
		_motor_right_a(new DigitalOut(motor_right_a)), 
		_motor_right_b(new DigitalOut(motor_right_b)),
		_relay_q(new DigitalOut(relay_q)),
		_relay_w(new DigitalOut(relay_w)) {}
Bot::Bot() {}
void Bot::process(uint8_t g_cmd)
{
	if(g_cmd == 1)
	{
		if(reverse == 0)
		Bot::go_up();
		Bot::go_down();
	}
	else if(g_cmd == 2)
	{
		if(reverse == 0)
		Bot::go_left();
		Bot::go_right();
	}
	else if(g_cmd == 3)
	{
		if(reverse == 0)
		Bot::go_down();
		Bot::go_up();
	}
	else if(g_cmd == 4)
	{
		if(reverse == 0)
		Bot::go_right();
		Bot::go_left();
	}
	else if(g_cmd == 5)
		Bot::stop();
	else if(g_cmd == 7)
		Bot::skill_q();
	else if(g_cmd == 9)
		Bot::skill_w();
	else if(g_cmd == 12)
		Bot::skill_e();
	else if(g_cmd == 16)
		Bot::skill_r();
	else if(g_cmd == 18)
		Bot::reverse_bot();
	g_cmd=0;
	
}
void Bot::connection(void)
{
	_led->write(1);
}
void Bot::disconnection(void)
{
	Bot::skill_e();
	_led->write(0);
}
void Bot::go_up(void)
{
	_motor_left_a->write(0);
	_motor_left_b->write(1);
	_motor_right_a->write(0);
	_motor_right_b->write(1);
}
void Bot::go_down(void)
{
	_motor_left_a->write(1);
	_motor_left_b->write(0);
	_motor_right_a->write(1);
	_motor_right_b->write(0);
}
void Bot::go_right(void)
{
	_motor_left_a->write(0);
	_motor_left_b->write(1);
	_motor_right_a->write(1);
	_motor_right_b->write(0);
}
void Bot::go_left(void)
{
	_motor_left_a->write(1);
	_motor_left_b->write(0);
	_motor_right_a->write(0);
	_motor_right_b->write(1);
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
	_relay_w->write(!_relay_q->read());
}
void Bot::skill_e(void)
{
	Bot::go_right();
	_relay_q->write(1);
}
void Bot::skill_r(void)
{
//	Bot::go_up();
//	wait_ms(500);
//	Bot::go_down();
//	wait_ms(500);
}
void Bot::reverse_bot(void)
{
	reverse = !reverse;
}

