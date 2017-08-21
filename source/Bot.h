#ifndef __Bot_H__
#define __Bot_H__
class Bot{

	public:
	//	char led1;
	//	DigitalOut led1(p7);
		char a;
		void connection();
		void go_up(void);

};
#endif /* #ifndef __Bot_H__ */

void Bot::connection()
{
	a=10;
}

void Bot::go_up()
{
	a=11;
}
