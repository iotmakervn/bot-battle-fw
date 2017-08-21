#ifndef __Bot_H__
#define __Bot_H__
class Bot{
private:
	DigitalOut	_motor_left_a;
	DigitalOut	_motor_left_b;
	DigitalOut 	_motor_right_a;
	DigitalOut	_motor_right_b;
	DigitalOut	_skill_q_a;
	DigitalOut	_skill_q_b;
	DigitalOut	_skill_w;


	public:
		Bot(PinName motor_left_a, PinName motor_left_b, PinName motor_right_a, PinName motor_right_b,
			PinName skill_q_a, PinName skill_q_b, PinName skill_w):
		_motor_left_a(motor_left_a), _motor_left_b(motor_left_b), _motor_right_a(motor_right_a), _motor_right_b(motor_right_b),
		_skill_q_a(skill_q_a), _skill_q_b(skill_q_b), _skill_w(skill_w) {}
		void connection(void);
		void go_up(void);

};
#endif /* #ifndef __Bot_H__ */
void Bot::connection(void)
{
	_motor_left_a = 1;
}

void Bot::go_up(void)
{
	
}