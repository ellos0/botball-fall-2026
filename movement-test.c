#include <kipr/wombat.h>

int br = 3;
int bl = 2;
int fr = 0;
int fl = 1;

void go(int p) {
	motor(br,p);
    motor(bl,p);
    motor(fr,p);
    motor(fl,p);
}

void left() {
	motor(fr,100);
    motor(fl,100);
    motor(br,-100);
    motor(bl,-100);
}

int main()
{
    left();
    msleep(1000);
    return 0;
}

