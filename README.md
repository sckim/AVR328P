# uC_examples
Microcontroller Atmega 328P와 관련된 예제입니다. (현재에는 328P 예제이며, 추후 수정 예정)
강의 자료와 소스 코드는 계속 올리도록 하겠습니다. 회로도는 Proteus ver. 8.x 이상에서 볼 수 있습니다.

## 강의 개요
+ 마이크로컨트롤러
+ Email: sckim@hknu.ac.kr

## 강의 구성 
### 1주차: 마이크로컨트롤러란? 

### 2주차: 개발환경구축
+ AVR Studio ([Ver 7](http://www.microchip.com/mplab/avr-support/atmel-studio-7), [Ver 4.19](https://www.dropbox.com/s/3c2vubam8lwj42c/AvrStudio4Setup.exe?dl=0))
+ Eclipse for AVR ([Neon](https://www.eclipse.org/downloads/packages/release/neon/3/eclipse-ide-cc-developers), [AVR Plugin 설치](https://marketplace.eclipse.org/category/free-tagging/avr))
+ [AVRToolchain](https://www.dropbox.com/s/7j8wxu1b2sp6b6n/AVR-Toolchain_330710.exe?dl=0)
+ [WinAVR](https://sourceforge.net/projects/winavr/files/) - avr gcc compiler
+ [Training Boar Kit](https://docs.google.com/document/d/1z8ZOeDaLLHn7CCoW8pkEYocl6X6kjT0bNDkCtDhy2is/edit#heading=h.ewk21ulbo3a9) - 학교에 있는 실습 키트
+ [필수프로그램](https://www.dropbox.com/s/invxn9zygupyc5h/Core.zip?dl=0) - AVRStudio4.19, AVR-Toolchain, WinAVR, msys-1.0.dll을 한꺼번에 받을 수 있습니다.
+ 개발에 도움이 되는 유틸리티 - [Putty](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html), [ISP-Pololu programmer](https://www.dropbox.com/s/yxbxef388oqb1lm/pololu-usb-avr-programmer-v2-1.0.1-win.msi?dl=0)

### 3주차: 범용 입/출력
+ [GPIO 출력](https://github.com/sckim/AVR328P/blob/master/010_Blink/Blink.c), [회로도](https://github.com/sckim/AVR328P/blob/master/010_Blink/AVR328P_LCD_7Seg_Terminal.DSN)
+ [GPIO 입력](https://github.com/sckim/AVR328P/blob/master/020_Input_LED/Input.c), [회로도](https://github.com/sckim/AVR328P/blob/master/020_Input_LED/AVR328P_Key_7Seg.DSN)
+ Debounce

### 4주차: 범용 입력 
+ [4x3 Keypad 입력](https://github.com/sckim/AVR328P/blob/master/026_Keypad/Keypad.c), [회로도](https://github.com/sckim/AVR328P/blob/master/026_Keypad/Keypad.pdsprj)

### 5주차: 외부 인터럽트 
+ [Interrupter를 사용한 버튼 입력](https://github.com/sckim/AVR328P/blob/master/027_Interrupt/Interrupt.c), [회로도](https://github.com/sckim/AVR328P/blob/master/027_Interrupt/AVR328P_7Seg_decoder.DSN)

### 6주차: 디스플레이장치 (7Segments) 
+ [7Segments 사용하기](https://github.com/sckim/AVR328P/blob/master/015_7Segments/7Segments.c), [회로도](https://github.com/sckim/AVR328P/blob/master/015_7Segments/AVR328P_LCD_7Seg.DSN)

[![](http://img.youtube.com/vi/E7OPkgIjPyo/0.jpg)](http://www.youtube.com/watch?v=E7OPkgIjPyo "7Segments display")

+ [4개의 7Segments 사용하기](https://github.com/sckim/uC_examples/blob/master/48_Four7Segments_itoa/Four7Segments.c), [회로도](https://github.com/sckim/uC_examples/blob/master/48_Four7Segments_itoa/Four7Segments.DSN)

[![](http://img.youtube.com/vi/qo5lWw_W_tg/0.jpg)](http://www.youtube.com/watch?v=qo5lWw_W_tg "4 digits FND")

### 7주차: 디스플레이장치 (LCD) 
+ [LCD 함수 이용해서 제어](https://github.com/sckim/AVR328P/blob/master/032_LibTextLCD/textLCDLib.c), [회로도](https://github.com/sckim/AVR328P/blob/master/050_textLCD/AVR328P_LCD.DSN), [lcd_lib.c](https://github.com/sckim/AVR328P/blob/master/050_textLCD/lcd_lib.c), [lcd_lib.h](https://github.com/sckim/AVR328P/blob/master/050_textLCD/lcd_lib.h)

### 8주차: Analog to Digital 
+ [ADC 값을 부동소수점으로 출력하기](https://github.com/sckim/uC_examples/blob/master/101_ADC_on_LCD/ADC_on_LCD.c), [회로도](https://github.com/sckim/AVR328P/blob/master/035_textLCDADC/AVR328P_LCD.DSN)

### 9주차: Timer
+ [Timer 0 Overflow Flag 활용](https://github.com/sckim/AVR328P/blob/master/040_Timer0Overflow/Timer0_8mSec.c)
+ [Timer 0 Overflow 인터럽트 활용](https://github.com/sckim/AVR328P/blob/master/041_Timer0Overflow_Int/Timer0_8mSec.c)
+ [Timer 0 Ouput match Flag 활용](https://github.com/sckim/AVR328P/blob/master/042_Timer0_CTC/Timer0_8mSec.c)
+ [Timer 0 Ouput match 인터럽트 활용](https://github.com/sckim/AVR328P/blob/master/043_Timer0_CTC_int/Timer0_10mSec.c)
+ Timer 2
+ [회로도](https://github.com/sckim/AVR328P/blob/master/043_Timer0_CTC_int/AVR328P_Key_7Seg.DSN)

### 10주차: Timer (PWM)
+ Timer 1, 3

### 11주차: Serial communicate (UART)
### 12주차: SPI
### 13주차: I2C
### 14주차: 디스플레이장치 (Graphic LCD) 
### 15주차: WatchDog

### 16주차: 키트 직접 만들어보기
+ 부트로더

## 참고자료
+ 즐기면서 익히는 uC (자체자료)
+ AVR328.pdf ([Dropbox](https://www.dropbox.com/s/ql3lzhbfzwl62mv/ATmega328P.pdf?dl=0), [Web](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf))
+ [BerkeleyX: EE40LX Electronic Interfaces](https://courses.edx.org/courses/course-v1:BerkeleyX+EE40LX+2T2015/info)
+ [AVR Programming Tutorial](http://ocw.mit.edu/courses/media-arts-and-sciences/mas-962-special-topics-new-textiles-spring-2010/readings-lectures-tutorials/tut06_avr1/)
+ [Atmega 328 Summary(http://www.ozeki.hu/attachments/473/ATmega-328P_Summary.pdf)
