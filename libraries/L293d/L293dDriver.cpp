/*
============
 L293D Chip 
============

Library to control the dual-independent motors at the hardware level. This is
a low level library that simply turns the motors forwards or backwards and
controls their speed.

Author: Jason Storey
License: GPLv3

*/

#include "L293DDriver.h"


/*

As this class is just a wrapper around two Motor classes, it isn't super
interesting. One thing to note is that left and right motors must be
initialized separately here. The L293D's `left` and `right` methods are simply
wrappers around each motor's `drive` method

*/
void L293D::setLeft(int enable1, int input1, int input2)
{
	L293D::_left_motor.setPins(enable1, input1, input2);
}

void L293D::setRight(int enable2, int input3, int input4)
{
	L293D::_right_motor.setPins(enable2, input3, input4);
}

void L293D::left(float speed)
{
	L293D::_left_motor.drive(speed);
}

void L293D::right(float speed)
{
	L293D::_right_motor.drive(speed);
}



/*
=========
  Motor
=========
*/


/*

This sets the pins for a motor. It has been purposely restricted to being done
once, to avoid confusion down the track.

*/
void Motor::setPins(int enable, int input1, int input2)
{
	if (Motor::_en == false) {
		pinMode(enable, OUTPUT);
		pinMode(input1, OUTPUT);
		pinMode(input2, OUTPUT);
		Motor::_en = enable;
		Motor::_in1 = input1;
		Motor::_in2 = input2;
	} else {
		printf("Cannot reassign motor pins");
	}
}

/*
 
This is the function that controls the voltages and duty cycle of the input
and enable pins. The enable pin is pulsed on and off rapidly, such that it
effectively slows down the motor. This is called PWM, and it is handled by the
analogWrite() function.

*/
void Motor::drive(float speed)
{
	// Clean up the speed value. The value might be "messy" because
	// the user is using a math function to interpolate speeds.
	speed = constrain(floor(speed), -255, 255);
	
	if (INVERTER) { // Invert the direction incase motors wired backwards
		speed *= -1;
	}

	Motor::_speed = speed;


	if (Motor::_speed > 0) {
		// We define "forward" as in1 high.
		digitalWrite(Motor::_in1, HIGH);
		digitalWrite(Motor::_in2, LOW);
		analogWrite(Motor::_en, abs(Motor::_speed));
	} else if (Motor::_speed < 0) {
		// Note reversed voltages of in1 and in2.
		digitalWrite(Motor::_in1, LOW);
		digitalWrite(Motor::_in2, HIGH);
		analogWrite(Motor::_en, abs(Motor::_speed)); // Make sure written speed is +ve
	} else {
		// If everything is set to low, motor effectively coasts.
		digitalWrite(Motor::_in1, LOW);
		digitalWrite(Motor::_in2, LOW);
		analogWrite(Motor::_en, 0);
	}
}