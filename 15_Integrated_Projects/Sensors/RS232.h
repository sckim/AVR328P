#ifndef _RS232_H_
#define _RS232_H_

	void UART0_INIT(unsigned int ubrr);
	unsigned char UART0_GetChar(void);
	void UART0_PutChar(unsigned char TX_data);
	void USART0_PutStr(char *tx_str);

#endif /* _RS232_H_ */
