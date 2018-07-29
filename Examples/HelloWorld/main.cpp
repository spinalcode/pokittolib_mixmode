#include "Pokitto.h"
#include "SDFileSystem.h"
#include "HWSound.h"

SDFileSystem sd(/*MOSI*/P0_9, /*MISO*/P0_8, /*SCK*/P0_6, /*CS*/P0_7, /*Mountpoint*/"sd");

Pokitto::Core mygame;

unsigned short pal[256]; // assign a 256 entry array to hold the palette
struct VIDEO_HEADER
{
  uint8_t   format;
  uint8_t   width;
  uint8_t   height;
  uint16_t  sampleSize;
  uint32_t  frameCount;
} vidhead;


int main () {
    mygame.begin();
    mygame.display.persistence=1;

    pokInitSD(); // Call init always.
    int temp=0;
    uint32_t myDelay = 1000/17;
    uint32_t tempTime  = mygame.getTime();

    while (mygame.isRunning()) {

    uint32_t myFile = fileOpen("movie.dat", FILE_MODE_READONLY);
    if( !myFile ){
        // read header
        fileReadBytes(&vidhead.format, 1); // should be 1
        fileReadBytes(&vidhead.width, 1); // should be 110
        fileReadBytes(&vidhead.height, 1); // should be 88

        uint8_t temp1[4];
        fileReadBytes(&temp1[0], 2); // should be ??
        vidhead.sampleSize = (temp1[1] << 8) + temp1[0];
        fileReadBytes(&temp1[0], 4); // should be ??
        vidhead.frameCount = (temp1[3] << 24)+(temp1[2] << 16)+(temp1[1] << 8)+temp1[0];

        unsigned char col[3];
        for(temp=0; temp<256; temp++){
            fileReadBytes(&col[0], 3);
            pal[temp] = (col[0]>>3) | ((col[1] >> 2) << 5) | ((col[2] >> 3) << 11);
        }
        mygame.display.load565Palette(&pal[0]); // load a palette the same way as any other palette in any other screen mode
        bool stillGoing=1;
        int sCount=0;

        pokPlayStream();
        int point=0;
        uint8_t tempSound[vidhead.sampleSize];

        while(stillGoing==1){
            // delay, yes I know it's not the correct way...
            if(mygame.getTime()-tempTime >= myDelay){
                tempTime = mygame.getTime();

                if(mygame.update()){

                    // the sample buffer fromthe file is a different size to the pokitto
                    fileReadBytes(&tempSound[0], vidhead.sampleSize);
                    for(int t=0; t<vidhead.sampleSize; t++){
                        soundbuf[point]=tempSound[t];
                        if(point++ > SBUFSIZE){point=0;}
                    }
                    if(!fileReadBytes(&mygame.display.screenbuffer[0], 9680))stillGoing=0;

                } // update
            } // timer
        } // stillgoing
        fileClose();
  } // file open


    }

}
