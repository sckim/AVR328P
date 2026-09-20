

#ifndef _ITG3200_H_
#define _ITG3200_H_


// ITG3200 Register Defines
#define WHO	0x00
#define	SMPL	0x15
#define DLPF	0x16
#define INT_C	0x17
#define INT_S	0x1A
#define	TMP_H	0x1B
#define	TMP_L	0x1C
#define	GX_H	0x1D
#define	GX_L	0x1E
#define	GY_H	0x1F
#define	GY_L	0x20
#define GZ_H	0x21
#define GZ_L	0x22
#define PWR_M	0x3E


#define FOSC 8000000
#define ITG3200_R 0xD1	// ADD pin is pulled low
#define ITG3200_W 0xD0	// So address is 0x69

#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))

unsigned char buf[50];

void ITG3200_INIT(); 
char ITG3200Read(unsigned char address);
void ITG3200Write(unsigned char address, unsigned char data);
void ITG3200ViewRegisters(void);
int checkInterrupt(void);
void ITG3200BlockRead(unsigned char address);


#endif /* _ITG3200_ */
