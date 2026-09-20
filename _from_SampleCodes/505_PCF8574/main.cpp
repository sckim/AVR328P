/*
 * mani.cpp
 *
 *  Created on: 2019. 6. 28.
 *      Author: Soochan Kim
 */

#include <avr/io.h>
#include "PCF8574.h"

PCF8574 PCF_01(0x20);

int main(void){
	PCF_01.begin();
	PCF_01.write(1, 1);
	PCF_01.write(0, 0);

	return 0;
}
