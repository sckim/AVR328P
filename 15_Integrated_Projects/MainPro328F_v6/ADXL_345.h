
#ifndef _ADXL_345_H_
#define _ADXL_345_H_

//----------------------------------------------------------------------------
#define ADXL345_W			0xA6
#define ADXL345_R			0xA7

//----------------------------------------------------------------------------
// ADXL3200 register map
#define REG_MEASURE				0x2D
#define VAR_X					0x32
#define VAR_Y					0x34
#define VAR_Z					0x36

// ADXL3200 variables
#define VAR_START				0x08


//----------------------------------------------------------------------------
extern void ADXl345_INIT(void);
extern unsigned char ADXl345_INIT_Flag(void);

#endif /* _ADXL_345_H_ */
