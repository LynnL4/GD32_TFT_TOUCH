/**
 * The MIT License (MIT)
 * 
 * title: a Arduino library for XPT2046
 * 
 * Author: Seeed
 * 
 * Copyright (C) 2019  Seeed Technology Co.,Ltd. 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __XPT2046_H
#define	__XPT2046_H

#include "Arduino.h"
/******************************* XPT2046 touch screen parameters ***************************/
//The difference threshold of AD value of touch coordinates when calibrating touch screen 
#define             XPT2046_THRESHOLD_CalDiff                    2               

#define	            XPT2046_CHANNEL_X 	                          0x90 	          //Channel Y+ 
#define	            XPT2046_CHANNEL_Y 	                          0xd0	          //Channel X+ 

/*******************************  XPT2046 data type ***************************/
typedef	struct          //LCD　coordinate  
{		
	/*A negative number indicates no new data*/
   int16_t x;			//Record the latest touch coordinate
   int16_t y; 
	
   /*Record the last touch coordinate during long press*/
   int16_t pre_x;		
   int16_t pre_y;
	
} strType_XPT2046_Coordinate;   

typedef struct         //Calibrate factor structures 
{
	 float An,  		 //ps:sizeof(long double) = 8
		   Bn,     
		   Cn,   
		   Dn,    
		   En,    
		   Fn,     
           Divider;

} strType_XPT2046_Calibration;


typedef struct         //Calibration factor structure (final use)
{
	 float dX_X,  			 
		   dX_Y,
		   dX,
		   dY_X,
		   dY_Y,
		   dY;

} strType_XPT2046_TouchPara;

/******touch state******/
typedef enum
{
	XPT2046_STATE_RELEASE  = 0,	//release
	XPT2046_STATE_WAITING,			//press
	XPT2046_STATE_PRESSED,			//press
}enumTouchState	;

#define TOUCH_PRESSED 				1
#define TOUCH_NOT_PRESSED			0

//Touch the buffering threshold
#define DURIATION_TIME				2

class XPT2046
{
private:
    uint32_t _mosi;
    uint32_t _miso;
    uint32_t _sck;
    uint32_t _cs;
    uint32_t _penIrq;
    uint8_t _touchFlag;

    void writeCMD(uint8_t cmd);
    uint8_t touchDetect(void);
    uint16_t readCMD(void);
    uint16_t readADC(uint8_t channel);

public:
    XPT2046(uint32_t mosi, uint32_t miso, uint32_t sck, uint32_t cs, uint32_t penIrq);
    ~XPT2046();
    void begin();
    void getRaw(int16_t * sX_Ad, int16_t * sY_Ad );
    uint8_t getXY(int16_t * sX_Ad, int16_t * sY_Ad );
    uint8_t Calculate_CalibrationFactor(strType_XPT2046_Coordinate * pDisplayCoordinate, strType_XPT2046_Coordinate * pScreenSample, strType_XPT2046_Calibration * pCalibrationFactor);
    void Touch_Calibrate();
    bool touchDown();
    bool touchUp();
    strType_XPT2046_TouchPara strXPT2046_TouchPara[48];
    
};

#endif /*__XPT2046_H*/
