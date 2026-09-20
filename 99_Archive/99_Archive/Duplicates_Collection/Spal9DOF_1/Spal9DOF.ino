/* Hardware version - v13
	
	ATMega328@3.3V w/ external 8MHz resonator
	High Fuse DA
        Low Fuse FF
	
	ADXL345: Accelerometer
	HMC5843: Magnetometer
	ITG3200: Gyrosensor

        Programmer : 3.3v FTDI
*/

#include <Wire.h>

// ADXL345 Sensitivity(from datasheet) => 4mg/LSB   1G => 1000mg/4mg = 256 steps
// Tested value : 256
#define GRAVITY 256  //this equivalent to 1G in the raw data coming from the accelerometer 
#define Accel_Scale(x) x*(GRAVITY/9.81)//Scaling the raw data of the accel to actual acceleration in meters for seconds square

#define ToRad(x) (x*0.01745329252)  // *pi/180
#define ToDeg(x) (x*57.2957795131)  // *180/pi

#define FALSE 0
#define TRUE 1

// LPR530 & LY530 Sensitivity (from datasheet) => (3.3mv at 3v)at 3.3v: 3mV/º/s, 3.22mV/ADC step => 0.93
// Tested values : 0.92
// Should be checked for ITG3200
#define Gyro_Gain_X 0.92 //X axis Gyro gain
#define Gyro_Gain_Y 0.92 //Y axis Gyro gain
#define Gyro_Gain_Z 0.92 //Z axis Gyro gain
#define Gyro_Scaled_X(x) x*ToRad(Gyro_Gain_X) //Return the scaled ADC raw data of the gyro in radians for second
#define Gyro_Scaled_Y(x) x*ToRad(Gyro_Gain_Y) //Return the scaled ADC raw data of the gyro in radians for second
#define Gyro_Scaled_Z(x) x*ToRad(Gyro_Gain_Z) //Return the scaled ADC raw data of the gyro in radians for second

// IGT-3200 Sensitivity (from datasheet) => 14.375 LSBs/º/s
// Tested values : 
#define Gyro_Gain_X   11.000 //X axis Gyro gain
#define Gyro_Gain_Y   11.000 //Y axis Gyro gain
#define Gyro_Gain_Z   11.000 //Z axis Gyro gain

#define Kp_ROLLPITCH 0.0125
#define Ki_ROLLPITCH 0.000008
#define Kp_YAW 1.2
#define Ki_YAW 0.000008

/*For debugging purposes*/
#define OUTPUTMODE 1

#define PRINT_DCM 1     //Will print the whole direction cosine matrix
#define PRINT_ANALOGS 1 //Will print the analog raw data
#define PRINT_EULER 1   //Will print the Euler angles Roll, Pitch and Yaw

#define ADC_WARM_CYCLES 50
#define STATUS_LED 13 

#define PRINT_EULER             0   //Will print the Euler angles Roll, Pitch and Yaw
#define PRINT_SENSOR_DATA       1   //Will print the Corrected Sensor Data
#define PRINT_SENSOR_DATA_RAW   0   //Will print the raw uncorrected Sensor Data
#define PRINT_DCM               0   //Will print the whole direction cosine matrix

int8_t sensors[3] = {1,2,0};  // Map the ADC channels gyro_x, gyro_y, gyro_z
int SENSOR_SIGN[9] = { 1,1,1,1,1,1,1,1,1};  //Correct directions x,y,z - gyros, accels, magnetormeter

float G_Dt=0.02;    // Integration time (DCM algorithm)  We will run the integration loop at 50Hz if possible

long timer=0;   //general purpuse timer
long timer_old;

//Structure for holding offsets and calibration values for the accel, gyro, and magnetom
struct s_sensor_offsets
{
    
    float accel_offset[3];
    float accel_scale[3];
    float gyro_offset[3];
    float magnetom_offset[3];
    float magnetom_XY_Theta;
    float magnetom_XY_Scale;
    float magnetom_YZ_Theta;
    float magnetom_YZ_Scale;
    
};

//structure for holding raw and calibration corrected data from the sensors
struct s_sensor_data
{
    //raw data is uncorrected and corresponds to the
    //true sensor axis, not the redefined platform orientation
    int gyro_x_raw;
    int gyro_y_raw;
    int gyro_z_raw;
    int accel_x_raw;
    int accel_y_raw;
    int accel_z_raw;
    int magnetom_x_raw;
    int magnetom_y_raw;
    int magnetom_z_raw;
  
    //This data has been corrected based on the calibration values
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float accel_x;
    float accel_y;
    float accel_z;
    float magnetom_x;
    float magnetom_y;
    float magnetom_z;
    float magnetom_heading;
    short baro_temp;  
    long baro_pres;
};

s_sensor_offsets sen_offset = {0,0,0,0,0,0,0,0,0,0,0,0};
s_sensor_data sen_data = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

float Accel_Vector[3]= {0,0,0}; //Store the acceleration in a vector
float Gyro_Vector[3]= {0,0,0};//Store the gyros turn rate in a vector
float Omega_Vector[3]= {0,0,0}; //Corrected Gyro_Vector data
float Omega_P[3]= {0,0,0};//Omega Proportional correction
float Omega_I[3]= {0,0,0};//Omega Integrator
float Omega[3]= {0,0,0};

// Euler angles
float roll;
float pitch;
float yaw;

float errorRollPitch[3]= {0,0,0}; 
float errorYaw[3]= {0,0,0};

//These counters allow us to sample some of the sensors at lower rates
unsigned int  Compass_counter=0;

float DCM_Matrix[3][3]       = {{1,0,0},{0,1,0},{0,0,1}}; 
float Update_Matrix[3][3]    = {{0,1,2},{3,4,5},{6,7,8}}; 
float Temporary_Matrix[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

void setup()
{ 
  Serial.begin(57600);
  pinMode (STATUS_LED,OUTPUT);  // Status LED
  
  Serial.println();
  Serial.println("SPAL IMU - 9DOF");
  
  delay(300);
  Wire.begin();    //Init the I2C
  delay(20);
  
  //================================
  // Initialize all the IMU sensors
  //
  Init_Accel();
  Init_Compass();
  Init_Gyro();

  Serial.println("Sparkfun 9DOF Razor AHRS");

  digitalWrite(STATUS_LED,LOW);
  delay(1500);
  
  digitalWrite(STATUS_LED,HIGH);
  timer=millis();

  delay(20);

  //init some counters
  Compass_counter=0;
}

void loop() //Main Loop
{
  if((DIYmillis()-timer)>=20)  // Main loop runs at 50Hz
  {
    Compass_counter++;

        timer_old = timer;
        timer=DIYmillis();
        G_Dt = (timer-timer_old)/1000.0;    // Real time of loop run. We use this on the DCM algorithm (gyro integration time)
        if(G_Dt > 1)  
            G_Dt = 0;  //keeps dt from blowing up, goes to zero to keep gyros from departing
        
        //=================================================================================//
        //=======================  Data adquisition of all sensors ========================//
        
        
        //======================= Read the Gyro and Accelerometer =======================//
        Read_Gyro();      // Read the data from the I2C Gyro
        Read_Accel();     // Read I2C accelerometer
      
      
        //=============================== Read the Compass ===============================//
        Compass_counter=0;
        Read_Compass();    // Read I2C magnetometer     
    
        //=================================================================================//
        //=======================  Calculations for DCM Algorithm  ========================//
        Matrix_update(); 
        Normalize();
        Drift_correction();
        Euler_angles();
        
       
        //=================================================================================//
        //============================= Data Display/User Code ============================//
        // Make sure you don't take too long here!
     
        printdata();
        StatusLEDToggle();
  }  
}
