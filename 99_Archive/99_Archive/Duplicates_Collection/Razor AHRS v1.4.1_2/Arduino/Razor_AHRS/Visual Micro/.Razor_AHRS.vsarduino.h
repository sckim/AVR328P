/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Pro or Pro Mini (3.3V, 8 MHz) w/ ATmega328, Platform=avr, Package=arduino
*/

#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO 101
#define ARDUINO_MAIN
#define F_CPU 8000000L
#define __AVR__
#define __cplusplus
extern "C" void __cxa_pure_virtual() {;}

void read_sensors();
void reset_sensor_fusion();
void compensate_sensor_errors();
void check_reset_calibration_session();
void turn_output_stream_on();
void turn_output_stream_off();
char readChar();
//
//
void Compass_Heading();
void Normalize(void);
void Drift_correction(void);
void Matrix_update(void);
void Euler_angles(void);
float Vector_Dot_Product(const float v1[3], const float v2[3]);
void Vector_Cross_Product(float out[3], const float v1[3], const float v2[3]);
void Vector_Scale(float out[3], const float v[3], float scale);
void Vector_Add(float out[3], const float v1[3], const float v2[3]);
void Matrix_Multiply(const float a[3][3], const float b[3][3], float out[3][3]);
void Matrix_Vector_Multiply(const float a[3][3], const float b[3], float out[3]);
void init_rotation_matrix(float m[3][3], float yaw, float pitch, float roll);
void output_angles();
void output_calibration(int calibration_sensor);
void output_sensors_text(char raw_or_calibrated);
void output_sensors_binary();
void output_sensors();
void I2C_Init();
void Accel_Init();
void Read_Accel();
void Magn_Init();
void Read_Magn();
void Gyro_Init();
void Read_Gyro();

#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\standard\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\Razor AHRS v1.4.1\Arduino\Razor_AHRS\Razor_AHRS.ino"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\Razor AHRS v1.4.1\Arduino\Razor_AHRS\Compass.ino"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\Razor AHRS v1.4.1\Arduino\Razor_AHRS\DCM.ino"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\Razor AHRS v1.4.1\Arduino\Razor_AHRS\Math.ino"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\Razor AHRS v1.4.1\Arduino\Razor_AHRS\Output.ino"
#include "D:\sckim\6.SampleCode\Arduino\Sketchbook\Razor AHRS v1.4.1\Arduino\Razor_AHRS\Sensors.ino"
