#include "ArmControl.h"
#include "ARDVARC_UTIL.h"

/*
	Setting Variables
*/
void ArmControl::setServoPins(int base, int grip) {
	if (base == grip) {
		if (F_DEBUG && Serial) Serial.println("WARNING: Base and grip servos on same pin");
		return;
	}
	s_base.attach(base);
	s_grip.attach(grip);
}

void ArmControl::setServoSpeed(float speed){
	_servo_speed = constrain(speed, 0, 1);
}

/*
	Individual Servos
*/

// Main function (universal)
// Min_true will be the real servo's angle (something like BASE_MIN)
// Where min_map will be what can be passed in

void ArmControl::moveServo(Servo servo, int angle, int min_map, int max_map, int min_true, int max_true) {
	int current_angle = servo.read();
	angle = constrain(angle, min_map, max_map);
	int desired_angle = map(angle, min_map, max_map, min_true, max_true);

	if (F_DEBUG && Serial) Serial.println("Setting servo to: " + String(desired_angle));

	int direction; // Director for stepping, so we close the gap.
	if (current_angle - desired_angle < 0) { // Desired angle is larger, to need to add
		direction = 1;
	} else if (current_angle - desired_angle == 0) {
		return; // Well, that was easy
	} else { // Desired angle is smaller, so need to subtract
		direction = -1;
	}

	int step = 2; // Step of degrees each time we iterate
	int thresh = 2; // Move to within this many degrees of accuracy
	int delay_step = mapf(_servo_speed, 0, 1, MAX_STEP, MIN_STEP);
	for (int L = current_angle; abs(L - desired_angle) > thresh; L += direction * step) {
		servo.write(L);
		delay(delay_step);
	}
}

void ArmControl::setAngle(int angle){
	moveServo(s_base, angle, 0, 180, BASE_MIN, BASE_MAX);
} 

int ArmControl::getAngle(){
	return s_base.read();
}  

void ArmControl::setGrip(int angle){
	moveServo(s_grip, angle, 0, 90, GRIP_MAX, GRIP_MIN);
}  

int ArmControl::getGrip(){
	return s_grip.read();
}   


/*
	Predefined actions
*/
void ArmControl::collectTarget(){
	// Hopefully this is redundant, because we are in rest position already
	readyPosition();
	delay(500);

	setGrip(0); // Grip enough to grab something
	delay(100);
	setAngle(0); // Move over dump bin
	delay(100);
	setGrip(50); // Open claw
	delay(100);
	setGrip(0);  // Close claw again
} 

void ArmControl::restPosition(){
	setAngle(0);
	setGrip(0);
} 

void ArmControl::readyPosition(){
	// Order is important!
	setGrip(60); // Not too wide, enough to catch a target
	setAngle(180); // Fully down, ready
}