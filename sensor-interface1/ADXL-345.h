
#ifndef _ADXL_345_H_
#define _ADXL_345_H_


/* ADXL345 */
#define ADXL345_W	0xA6
#define ADXL345_R	0xA7


void ADXl345_INIT(void);
int16_t read_adxl345(char reg_adr);

#endif /* _ADXL_345_H_ */
