#include "project.h"

Player::Player()
{
	role=0;
	i=0;
	name="";
	x=0;
	y=0;
	set=0;
	team=0;
	mode=0;
	pow=1;
	maxpower=7;
	amount=1;
	maxamount=7;
	kill=0;
	death=0;
	money=0;
	assist=0;
	drown=0;
	dead=0;
	bomb=NULL;
	t=0;
	bomb=new Bomb[maxamount];
	for(int i=0;i<maxamount;i++){
		bomb[i].powerptr(&pow);
	}
}
void Player::teamchoose(int x, int left, int right)
{
	if(x==left){
		team--;
		if(team<0){
			team+=4;
		}
	}
	else if(x==right){
		team++;
		if(team>3){
			team-=4;
		}
	}
}
void Player::rolechoose(int x, int left, int right)
{
	if(x==left){
		role--;
		if(role<0){
			role+=3;
		}
	}
	else if(x==right){
		role++;
		if(role>2){
			role-=3;
		}
	}
	if(role==0){
		pow=1;
		maxpower=7;
		amount=1;
		maxamount=7;
	}
	else if(role==1){
		pow=2;
		maxpower=4;
		amount=1;
		maxamount=5;
	}
	else if(role==2){
		pow=1;
		maxpower=5;
		amount=2;
		maxamount=4;
	}
	bomb=new Bomb[maxamount];
	for(int i=0;i<maxamount;i++){
		bomb[i].powerptr(&pow);
	}
}
void Player::setxy(int i, int j)
{
	x=i;
	y=j;
}
void Player::powerup()
{
	if(pow<maxpower){
		pow++;
	}
}
void Player::amountup()
{
	if(amount<maxamount){
		amount++;
	}
}
void Player::setname(string n)
{
	name=n;
}
bool Player::setted()
{
	return set;
}
void Player::reset()
{
	role=0;
	i=0;
	name="";
	x=0;
	y=0;
	set=0;
	team=0;
	mode=0;
	pow=1;
	maxpower=7;
	amount=1;
	maxamount=7;
	kill=0;
	death=0;
	money=0;
	assist=0;
	drown=0;
	dead=0;
	bomb=NULL;
	t=0;
	bomb=new Bomb[maxamount];
	for(int i=0;i<maxamount;i++){
		bomb[i].powerptr(&pow);
	}
	
}
