#include <kipr/wombat.h>

int hand = 3;
int arm = 1;
int br = 3;
int bl = 2;
int fr = 1;
int fl = 0;
int armdown = 2047;
int armup = 1365;
int armreset = 2047;
int handclose = 0;
int handopen = 2047;


void go(int p) {
    motor(br,p);
	motor(bl,p);
    motor(fr,p);
    motor(fl,p);
}

void openHand() {
	set_servo_position(hand,handopen);
    msleep(1000);
}
void closeHand() {
	set_servo_position(hand, handclose);
    msleep(1000);
}

void wave() {
	openHand();
    closeHand();
    openHand();
    closeHand();
}

int main()
{
    
    go(100);
    msleep(1000);
    go(-100);
    msleep(1000);
    go(0);
    msleep(1000);
    
    set_servo_enabled(arm,1);
    set_servo_enabled(hand,1);
    
    set_servo_position(arm,armreset);
    set_servo_position(hand,handclose);
    msleep(1500);
    set_servo_position(arm,armup);
    wave();
    
    set_servo_enabled(arm,0);
    set_servo_enabled(hand,0);
    
    return 0;
}
