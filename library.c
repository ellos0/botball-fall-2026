/*** 
     Team "No Name"'s Botball Library 2025
     This is for a 4 omnidirectional wheel robot.
***/

// includes
#include <kipr/wombat.h>
#include <stdio.h>

// constants

#define BL 2
#define BR 1
#define FL 3
#define FR 0

#define ARM 2
#define HAND 3

#define ARM_UP 1024
#define ARM_MAX 2047
#define ARM_MIN 300
#define ARM_BOTGUY 1700
#define ARM_CUBE 1800
#define ARM_FLOOR 2047

#define HAND_OPEN 2047
#define HAND_MAX 2047
#define HAND_MIN 0
#define HAND_BOTGUY_OPEN 700
#define HAND_BOTGUY 190
#define HAND_CUBE 450


#define RANGE 0
#define TOPHAT 1

#define LINE_FOLLOW_DEFAULT -1
// -1 for left, 1 for right
#define LINE_FOLLOW_BIG_TURN 100
#define LINE_FOLLOW_SMALL_TURN -100

// move forward with percentile p
void go(int p) {
	motor(BL,p);
  motor(BR,p);
  motor(FL,p);
  motor(FR,p);
}

void left() {
	motor(BR,100);
  motor(FR,100);
  motor(BL,-100);
  motor(FL,-100);
}

void right() {
	motor(BL,100);
  motor(FL,100);
  motor(BR,-100);
  motor(FR,-100);
}

void enable_servos() {
	set_servo_enabled(ARM, 1);
  set_servo_enabled(HAND, 1);
}

void disable_servos() {
	set_servo_enabled(ARM, 0);
  set_servo_enabled(HAND,0);
}

void un_death_grip() {
	set_servo_position(HAND, HAND_BOTGUY_OPEN);
  msleep(1000);
}

void compact_claw() {
  un_death_grip();
	set_servo_position(ARM, ARM_MIN);
  set_servo_position(HAND, HAND_MIN);
  msleep(1000);
}

void set_hand(int p) {
	set_servo_position(HAND, p);
}

void set_arm(int p) {
	set_servo_position(ARM, p);
}

void go_right(int p) {
	motor(BR, p);
  motor(FL, p);
  motor(FR,-p);
  motor(BL,-p);
}

int claw_needs_compact() {
	return !(get_servo_position(ARM) == ARM_MIN && get_servo_position(HAND) == HAND_MIN);
}

void go_left(int p) {
	motor(BL, p);
  motor(FR, p);
  motor(BR,-p);
  motor(FL,-p);
}

void move_servo_with_speed(int port, float speed, int pos) {
	int counter = get_servo_position(port);
  int orig = counter;
    
  while (counter < pos) {
    counter += (pos-orig)/speed;
    set_servo_position(port, counter);
    msleep(100);
  }
}

int main()
{
  wait_for_light(0);
  shut_down_in(120);
    
  enable_servos();
  	
  compact_claw();
    
  //turn right and move right to pick up botguy
  right(100);
  msleep(1500);
  go_right(100);
  msleep(800);
    
  //align
  right(100);
  msleep(300);
  go(-100);
  msleep(100);
	
  //wiggle
  go(100);
  msleep(100);
  go(0);
  msleep(1000);
    
  //move hand to botguy
  go(0);
  set_hand(HAND_BOTGUY_OPEN);
  msleep(500);
  set_arm(ARM_BOTGUY);
  msleep(1000);
    
  //pick up botguy
  set_hand(HAND_BOTGUY);
  msleep(500);
    
  //turn and drop botguy in lower storage
  set_arm(ARM_UP);
  right(100);
  msleep(2300);
  go(0);
  set_arm(ARM_FLOOR);
  msleep(1000);
  set_hand(HAND_OPEN);
  msleep(500);
  go(0);
  set_arm(ARM_BOTGUY);
  msleep(1000);
    
  //pick up big cubes
  set_hand(HAND_OPEN);
  set_arm(ARM_UP);
  msleep(1000);
  right(100);
  msleep(2100);
  go(-100);
  msleep(200);
  go(0);
  set_hand(HAND_BOTGUY_OPEN);
  msleep(500);
  set_arm(ARM_CUBE);
  msleep(1000);
  set_hand(HAND_CUBE);
  msleep(500);
  set_arm(ARM_UP);
  msleep(1000);
    
  //place cube on pallet
  right(100);
  msleep(800);
  go(-100);
  msleep(200);
  go(0);
  set_arm(ARM_BOTGUY);
  msleep(1000);
  set_hand(HAND_BOTGUY_OPEN);
  msleep(1000);
  set_arm(ARM_UP);
  msleep(1000);
    
  disable_servos();
  return 0;
}
