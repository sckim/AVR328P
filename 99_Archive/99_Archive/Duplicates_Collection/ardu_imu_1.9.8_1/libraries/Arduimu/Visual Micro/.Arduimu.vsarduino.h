/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Pro or Pro Mini (5V, 16 MHz) w/ ATmega328, Platform=avr, Package=arduino
*/

#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO 101
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define __cplusplus
extern "C" void __cxa_pure_virtual() {;}

//
//
void startup_ground(void);
void startup_air(void);
void debug_print(char string[]);
void debug_handler(byte message);
void Read_adc_raw(void);
float read_adc(int select);
void Analog_Init(void);
void Analog_Reference(uint8_t mode);
void Read_adc_raw();
float read_adc(int select);
void Normalize(void);
void Drift_correction(void);
void Accel_adjust(void);
void Matrix_update(void);
void Euler_angles(void);
bool HMC5883_init();
void HMC5883_set_offset(int offsetx, int offsety, int offsetz);
void HMC5883_read();
void HMC5883_calculate(float roll, float pitch);
byte MPU6000_SPI_read(byte reg);
void MPU6000_SPI_write(byte reg, byte data);
void MPU6000_data_int();
void MPU6000_Init(void);
void MPU6000_Read();
void printdata(void);
void printPerfData(long time);
long convert_to_dec(float x);
float Vector_Dot_Product(float vector1[3],float vector2[3]);
void Vector_Cross_Product(float vectorOut[3], float v1[3],float v2[3]);
void Vector_Scale(float vectorOut[3],float vectorIn[3], float scale2);
void Vector_Add(float vectorOut[3],float vectorIn1[3], float vectorIn2[3]);
void Matrix_Multiply(float a[3][3], float b[3][3],float mat[3][3]);

#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\standard\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\ardu_imu_1.9.8\libraries\Arduimu\Arduimu.ino"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\ardu_imu_1.9.8\libraries\Arduimu\ADC.pde"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\ardu_imu_1.9.8\libraries\Arduimu\DCM.pde"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\ardu_imu_1.9.8\libraries\Arduimu\HMC5883.pde"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\ardu_imu_1.9.8\libraries\Arduimu\MPU6000.h"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\ardu_imu_1.9.8\libraries\Arduimu\MPU6000.pde"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\ardu_imu_1.9.8\libraries\Arduimu\Output.pde"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\ardu_imu_1.9.8\libraries\Arduimu\Vector.pde"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\ardu_imu_1.9.8\libraries\Arduimu\matrix.pde"
