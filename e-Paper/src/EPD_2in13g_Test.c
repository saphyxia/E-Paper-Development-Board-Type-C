/*****************************************************************************
* | File      	:   EPD_2IN13G_test.c
* | Author      :   Waveshare team
* | Function    :   2.13inch e-paper (G) test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2023-05-24
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_2in13g_test.h"
#include "EPD_2in13g.h"

int EPD_test(void)
{
    if(DEV_Module_Init()!=0){
        return -1;
    }

    EPD_2IN13G_Init();
    EPD_2IN13G_Clear(EPD_2IN13G_WHITE);
    DEV_Delay_ms(2000);

    //Create a new image cache
    UBYTE *BlackImage,*BlackImage1;
    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    UWORD Imagesize = ((EPD_2IN13G_WIDTH % 4 == 0)? (EPD_2IN13G_WIDTH / 4 ): (EPD_2IN13G_WIDTH / 4 + 1)) * EPD_2IN13G_HEIGHT;
		
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        return -1;
    }
    if((BlackImage1 = (UBYTE *)malloc(Imagesize)) == NULL) {
        return -1;
    }
    Paint_NewImage(BlackImage, EPD_2IN13G_WIDTH, EPD_2IN13G_HEIGHT, 90, EPD_2IN13G_WHITE);
    Paint_SetScale(4);
		Paint_NewImage(BlackImage1, EPD_2IN13G_WIDTH, EPD_2IN13G_HEIGHT, 0, EPD_2IN13G_WHITE);
    Paint_SetScale(4);

#if 1   // show image for array
    Paint_SelectImage(BlackImage);
    Paint_Clear(EPD_2IN13G_WHITE);
    Paint_DrawBitMap(gImage_2in13g);
		EPD_2IN13G_Display(BlackImage);
    DEV_Delay_ms(2000);
#endif        

#if 1   // Drawing on the image
    //1.Select Image
    Paint_SelectImage(BlackImage);
    Paint_Clear(EPD_2IN13G_WHITE);

    // 2.Drawing on the image
    Paint_DrawPoint(10, 80, EPD_2IN13G_RED, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 90, EPD_2IN13G_YELLOW, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, EPD_2IN13G_BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 70, 120, EPD_2IN13G_RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 70, 20, 120, EPD_2IN13G_RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawRectangle(20, 70, 70, 120, EPD_2IN13G_YELLOW, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(80, 70, 130, 120, EPD_2IN13G_YELLOW, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(45, 95, 20, EPD_2IN13G_BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(105, 95, 20, EPD_2IN13G_BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawLine(85, 95, 125, 95, EPD_2IN13G_RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(105, 75, 105, 115, EPD_2IN13G_YELLOW, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawString_EN(10, 0, "Red, yellow, white and black", &Font16, EPD_2IN13G_RED, EPD_2IN13G_YELLOW);
    Paint_DrawString_EN(10, 35, "Four color e-Paper", &Font12, EPD_2IN13G_YELLOW, EPD_2IN13G_BLACK);
    Paint_DrawString_CN(10, 125, "΢ѩ����", &Font24CN, EPD_2IN13G_RED, EPD_2IN13G_WHITE);
    Paint_DrawNum(10, 50, 123456, &Font12, EPD_2IN13G_RED, EPD_2IN13G_WHITE);

    EPD_2IN13G_Display(BlackImage);
    DEV_Delay_ms(3000);
#endif

#if 1   // Drawing on the image
    //1.Select Image
    Paint_SelectImage(BlackImage);
    Paint_Clear(EPD_2IN13G_WHITE);

    // 2.Drawing on the image
    Paint_DrawRectangle(1, 1, 168, 55, EPD_2IN13G_RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(1, 112, 167, 167, EPD_2IN13G_YELLOW, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(59, 1, 109, 167, EPD_2IN13G_BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    EPD_2IN13G_Display(BlackImage);
    DEV_Delay_ms(3000);
#endif

#if 1   // Drawing on the image
    //1.Select Image
    Paint_SelectImage(BlackImage);
    Paint_Clear(EPD_2IN13G_WHITE);

    int hNumber, hWidth, vNumber, vWidth;
    hNumber = 8;
	hWidth = EPD_2IN13G_HEIGHT/hNumber; // 168/16=21
    vNumber = 8;
	vWidth = EPD_2IN13G_WIDTH/vNumber; // 168/16=21

    // 2.Drawing on the image
	for(int i=0; i<hNumber; i++) {  // horizontal
		Paint_DrawRectangle(1, 1+i*hWidth, EPD_2IN13G_WIDTH, hWidth*(1+i), EPD_2IN13G_BLACK + (i % 2), DOT_PIXEL_1X1, DRAW_FILL_FULL);
	}
	for(int i=0; i<vNumber; i++) {  // vertical
        if(i%2) {
            Paint_DrawRectangle(1+i*vWidth, 1, vWidth*(i+1), EPD_2IN13G_HEIGHT, EPD_2IN13G_YELLOW + (i/2%2), DOT_PIXEL_1X1, DRAW_FILL_FULL);
        }
	}

    EPD_2IN13G_Display(BlackImage);
    DEV_Delay_ms(3000);
#endif

    EPD_2IN13G_Clear(EPD_2IN13G_WHITE);

    EPD_2IN13G_Sleep();
    free(BlackImage);
    BlackImage = NULL;
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    DEV_Module_Exit();
    
    return 0;
}
