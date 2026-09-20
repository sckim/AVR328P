
#ifndef _ADXL_345_H_
#define _ADXL_345_H_

//----------------------------------------------------------------------------
#define ADXL345_ADDRESS			0xA6

//----------------------------------------------------------------------------
// ADXL3200 register map
#define ADXL345_DEVID					0x00	// Device ID
#define ADXL345_THRESH_TAP				0x1D	// Tap threshold 
#define ADXL345_OFSX					0x1E	// X-axis offset
#define ADXL345_OFSY					0x1F	// Y-axis offset
#define ADXL345_OFSZ					0x20	// Z-axis offset
#define ADXL345_DUR						0x21	// Tap duration 
#define ADXL345_LATENT					0x22	// Tap latency
#define ADXL345_WINDOW					0x23	// Tap window
#define ADXL345_THRESH_ACT				0x24	// Activity threshold
#define ADXL345_THRESH_INACT			0x25	// Inactivity threshold
#define ADXL345_TIME_INACT				0x26	// Inactivity time
#define ADXL345_ACT_INACT_CTL			0x27	// Axis enable control for activity and inactivity detection
#define ADXL345_THRESH_FF				0x28	// Free-fall threshold 
#define ADXL345_TIME_FF					0x29	// Free-fall time
#define ADXL345_TAP_AXES				0x2A	// Axis control for single tap/double tap
#define ADXL345_ACT_TAP_STATUS			0x2B	// Source of single tap/double tap
#define ADXL345_BW_RATE					0x2C	// Data rate and power mode control 
#define ADXL345_POWER_CTL				0x2D	// Power-saving features control 
#define ADXL345_INT_ENABLE				0x2E	// Interrupt enable control 
#define ADXL345_INT_MAP					0x2F	// Interrupt mapping control
#define ADXL345_INT_SOURCE				0x30	// Source of interrupts 
#define ADXL345_DATA_FORMAT				0x31	// Data format control
#define ADXL345_DATAX0					0x32	// X-Axis Data 0
#define ADXL345_DATAX1					0x33	// X-Axis Data 1
#define ADXL345_DATAY0					0x34	// Y-Axis Data 0
#define ADXL345_DATAY1					0x35	// Y-Axis Data 1
#define ADXL345_DATAZ0					0x36	// Z-Axis Data 0
#define ADXL345_DATAZ1					0x37	// Z-Axis Data 1
#define ADXL345_FIFO_CTL				0x38	// FIFO control
#define ADXL345_FIFO_STATUS				0x39	// FIFO status

// ADXL3200 variables
#define ADXL345_VAR_START				0x08
#define ADXL345_VAR_STOP				0x00

// Register 0x27?ACT_INACT_CTL (Read/Write) 
typedef struct 
{						
	unsigned char	INACT_Zenable:1;		
	unsigned char	INACT_Y_enable:1;			
	unsigned char	INACT_X_enable:1;			
	unsigned char	INACT_acdc:1;			
	unsigned char	ACT_Z_enable:1;			
	unsigned char	ACT_Y_enable:1;			
	unsigned char	ACT_X_enable:1;					
	unsigned char	ACT_acdc:1;		
}_ACT_INACT_CTL;

typedef union 
{
	unsigned char all;
	_ACT_INACT_CTL bit;
}UACT_INACT_CTL;

// Register 0x2A?TAP_AXES (Read/Write)
typedef struct {						
	unsigned char	TAP_Z_enable:1;		
	unsigned char	TAP_Y_enable:1;			
	unsigned char	TAP_X_enable:1;			
	unsigned char	Suppress:1;		
}_TAP_AXES;

typedef union {
	unsigned char all;
	_TAP_AXES bit;
}UTAP_AXES;	

// Register 0x2B?ACT_TAP_STATUS (Read Only)
typedef struct {						
	unsigned char	TAP_Z_source:1;		
	unsigned char	TAP_Y_source:1;			
	unsigned char	TAP_X_source:1;			
	unsigned char	Asleep:1;		
	unsigned char	ACT_Z_source:1;		
	unsigned char	ACT_Y_source:1;			
	unsigned char	ACT_X_source:1;			
}_ACT_TAP_STATUS;

typedef union {
	unsigned char all;
	_ACT_TAP_STATUS bit;
}UACT_TAP_STATUS;	

// Register 0x2C?BW_RATE (Read/Write) 
typedef struct {						
	unsigned char	Rate:4;		
	unsigned char	LOW_POWER:1;				
}_BW_RATE;

typedef union {
	unsigned char all;
	_BW_RATE bit;
}UBW_RATE;	

// Register 0x2D?POWER_CTL (Read/Write) 
typedef struct {						
	unsigned char	Wakeup:2;		
	unsigned char	Sleep:1;			
	unsigned char	Measure:1;			
	unsigned char	AUTO_SLEEP:1;		
	unsigned char	Link:1;			
}_POWER_CTL;

typedef union {
	unsigned char all;
	_POWER_CTL bit;
}UPOWER_CTL;	

// Register 0x2E?INT_ENABLE (Read/Write) 
typedef struct {						
	unsigned char	Overrun:1;		
	unsigned char	Watermark:1;			
	unsigned char	FREE_FALL:1;			
	unsigned char	Inactivity:1;		
	unsigned char	Activity:1;		
	unsigned char	DOUBLE_TAP:1;			
	unsigned char	SINGLE_TAP:1;		
	unsigned char	DATA_READY:1;			
}_INT_ENABLE;

typedef union {
	unsigned char all;
	_INT_ENABLE bit;
} UINT_ENABLE;	

// Register 0x2F?INT_MAP (R/W)
typedef struct {						
	unsigned char	Overrun:1;		
	unsigned char	Watermark:1;			
	unsigned char	FREE_FALL:1;			
	unsigned char	Inactivity:1;		
	unsigned char	Activity:1;		
	unsigned char	DOUBLE_TAP:1;			
	unsigned char	SINGLE_TAP:1;		
	unsigned char	DATA_READY:1;			
}_INT_MAP;

typedef union {
	unsigned char all;
	_INT_MAP bit;
}UINT_MAP;

// Register 0x30?INT_SOURCE (Read Only)
typedef struct {						
	unsigned char	Overrun:1;		
	unsigned char	Watermark:1;			
	unsigned char	FREE_FALL:1;			
	unsigned char	Inactivity:1;		
	unsigned char	Activity:1;		
	unsigned char	DOUBLE_TAP:1;			
	unsigned char	SINGLE_TAP:1;		
	unsigned char	DATA_READY:1;			
} _INT_SOURCE;

typedef union {
	unsigned char all;
	_INT_SOURCE bit;
}UINT_SOURCE;

// Register 0x31?DATA_FORMAT (Read/Write)
typedef struct {						
	unsigned char	Range:2;		
	unsigned char	Justify:1;			
	unsigned char	FULL_RES:1;			
	unsigned char	Zero:1;		
	unsigned char	INT_INVERT:1;		
	unsigned char	SPI:1;			
	unsigned char	SELF_TEST:1;				
}_DATA_FORMAT;

typedef union {
	unsigned char all;
	_DATA_FORMAT bit;
}UDATA_FORMAT;

// Register 0x38?FIFO_CTL (Read/Write)
typedef struct {						
	unsigned char	Samples:5;		
	unsigned char	Trigger:1;			
	unsigned char	FIFO_MODE:2;						
}_FIFO_CTL;

typedef union {
	unsigned char all;
	_FIFO_CTL bit;
}UFIFO_CTL;

// 0x39?FIFO_STATUS (Read Only)
typedef struct {						
	unsigned char	Entries:6;		
	unsigned char	Zero:1;			
	unsigned char	FIFO_TRIG:1;						
}_FIFO_STATUS;

typedef union {
	unsigned char all;
	_FIFO_STATUS bit;
}UFIFO_STATUS;


typedef struct {
	unsigned char			DEVID;	
	unsigned char			THRESH_TAP;
	unsigned char			OFSX;
	unsigned char			OFSY;
	unsigned char			OFSZ;
	unsigned char			DUR;
	unsigned char			Latent;
	unsigned char			Window;
	unsigned char			THRESH_ACT;
	unsigned char			THRESH_INACT;
	unsigned char			TIME_INACT;
	UACT_INACT_CTL			ACT_INACT_CTL;
	unsigned char			THRESH_FF;
	unsigned char			TIME_FF;
	UTAP_AXES				TAP_AXES;
	UACT_TAP_STATUS			ACT_TAP_STATUS;
	UBW_RATE				BW_RATE;
	UPOWER_CTL				POWER_CTL;
	UINT_ENABLE				INT_ENABLE;
	UINT_MAP				INT_MAP;
	UINT_SOURCE				INT_SOURCE;
	UDATA_FORMAT			DATA_FORMAT;
	unsigned char			DATAX0;
	unsigned char			DATAX1;
	unsigned char			DATAY0;
	unsigned char			DATAY1;
	unsigned char			DATAZ0;
	unsigned char			DATAZ1;
	UFIFO_CTL				FIFO_CTL;
	UFIFO_STATUS			FIFO_STATUS;
}_ADXL345_REG;

//----------------------------------------------------------------------------
extern void ADXl345_INIT(void);
extern unsigned char ADXl345_INIT_Flag(void);
extern unsigned char ADXl345_ReadXYZ(int* X, int* Y, int* Z);
extern unsigned char ADXl345_Angle(float* X_ang, float* Y_ang, float* Z_ang);


extern void ADXl345_Write(void);
extern void ADXl345_ReadAll(void);

#endif /* _ADXL_345_H_ */
