#ifndef _ITG_3200_H_
#define _ITG_3200_H_

//----------------------------------------------------
#define ITG3200_R 0xD1	
#define ITG3200_W 0xD0	

//----------------------------------------------------------------------------
// ITG3200 register map
#define REG_WHO		0x00
#define	REG_SMPL	0x15
#define REG_DLPF	0x16
#define REG_INT_C	0x17
#define REG_INT_S	0x1A
#define	REG_TMP_H	0x1B
#define	REG_TMP_L	0x1C
#define	REG_GX_H	0x1D
#define	REG_GX_L	0x1E
#define	REG_GY_H	0x1F
#define	REG_GY_L	0x20
#define REG_GZ_H	0x21
#define REG_GZ_L	0x22
#define REG_PWR_M	0x3E

// ITG3200 variables
#define VAR_RESET	0x80
#define VAR_SMLPRT	0x00
#define VAR_DLPF	0x18
#define VAR_INT		0x05
#define VAR_PWON	0x00

//----------------------------------------------------
extern void ITG3200_INIT(); 
extern unsigned char ITG3200_INIT_Flag(void);

#endif /* _ITG3200_ */
