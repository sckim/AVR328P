#ifndef _ITG_3200_H_
#define _ITG_3200_H_

//----------------------------------------------------
#define ITG3200_ADDRESS		0xD0	

#define ITG3200_NUMOFSAMPLE			10
#define ITG3200_MAXCNT				1000
//----------------------------------------------------------------------------
// ITG3200 register map
#define ITG3200_REG_WHO		0x00
#define	ITG3200_REG_SMPL	0x15
#define ITG3200_REG_DLPF	0x16
#define ITG3200_REG_INT_C	0x17
#define ITG3200_REG_INT_S	0x1A
#define	ITG3200_REG_TMP_H	0x1B
#define	ITG3200_REG_TMP_L	0x1C
#define	ITG3200_REG_GX_H	0x1D
#define	ITG3200_REG_GX_L	0x1E
#define	ITG3200_REG_GY_H	0x1F
#define	ITG3200_REG_GY_L	0x20
#define ITG3200_REG_GZ_H	0x21
#define ITG3200_REG_GZ_L	0x22
#define ITG3200_REG_PWR_M	0x3E

// ITG3200 variables
#define ITG3200_VAR_RESET	0x80
#define ITG3200_VAR_SMLPRT	0x00
#define ITG3200_VAR_DLPF	0x18
#define ITG3200_VAR_INT		0x05
#define ITG3200_VAR_PWON	0x00

//----------------------------------------------------
extern void ITG3200_INIT(); 
extern unsigned char ITG3200_INIT_Flag(void);
extern unsigned char ITG3200_ReadXYZ(int* X, int* Y, int* Z);

#endif /* _ITG3200_ */
