/** Mode 13 (110x88x256) by Spinal, video streaming concept */

#include "Pokitto.h"
#include "SDFileSystem.h"
#include "HWSound.h"

Pokitto::Core game;
int myDelay;
unsigned short pal[256]; // assign a 256 entry array to hold the palette
struct VIDEO_HEADER
{
  uint8_t   ID[3];
  uint8_t   format;
  uint8_t   width;
  uint8_t   height;
  uint16_t  sampleSize;
  uint32_t  frameCount;
  uint8_t   FPS;
  uint32_t  frameSize;
  uint32_t   frameOffset;
} vidhead;

DigitalOut myAmp(P1_17);

template<typename T>
uint16_t fileReadBytes(T & object)
{
	return fileReadBytes(reinterpret_cast<uint8_t *>(&object), sizeof(T));
}

template<typename T>
void fileWriteBytes(T & object)
{
	fileWriteBytes(reinterpret_cast<uint8_t *>(&object), sizeof(T));
}

template<typename T, size_t size>
uint16_t fileReadBytes(T (&objects)[size])
{
	return fileReadBytes(reinterpret_cast<uint8_t *>(&objects[0]), sizeof(T) * size);
}

template<typename T, size_t size>
void fileWriteBytes(T (&objects)[size])
{
	fileWriteBytes(reinterpret_cast<uint8_t *>(&objects[0]), sizeof(T) * size);
}

template<typename T, size_t size>
uint16_t fileReadBytes(T (&objects)[size], size_t itemCount)
{
	(void)size; // Preempt possible compiler warning
	return fileReadBytes(reinterpret_cast<uint8_t *>(&objects[0]), sizeof(T) * itemCount);
}

template<typename T, size_t size>
void fileWriteBytes(T (&objects)[size], size_t itemCount)
{
	(void)size; // Preempt possible compiler warning
	fileWriteBytes(reinterpret_cast<uint8_t *>(&objects[0]), sizeof(T) * itemCount);
}




void PFFS_Video() { // Petit Fat File System

    uint32_t myFile = fileOpen("movie2.dat", FILE_MODE_READONLY);
    if( !myFile ){
        fileReadBytes(vidhead.ID); // should be P,O,K
        fileReadBytes(vidhead.format); // should be 1
        fileReadBytes(vidhead.width); // should be 110
        fileReadBytes(vidhead.height); // should be 88

        vidhead.frameSize = vidhead.width * vidhead.height;
        vidhead.frameOffset = ((88-vidhead.height)/2)*110;

        uint8_t temp1[4];

        fileReadBytes(&temp1[0], 2); // should be ??
        vidhead.sampleSize = (temp1[1] << 8) + temp1[0];
        fileReadBytes(&temp1[0], 4); // should be ??
        vidhead.frameCount = (temp1[3] << 24)+(temp1[2] << 16)+(temp1[1] << 8)+temp1[0];

        fileReadBytes(&vidhead.FPS, 1); // should be 1

        myDelay = 1000/vidhead.FPS;

        unsigned char col[3];
        for(int temp=0; temp<256; temp++){
            fileReadBytes(&col[0], 3);
            pal[temp] = (col[0]>>3) | ((col[1] >> 2) << 5) | ((col[2] >> 3) << 11);
        }
        game.display.load565Palette(&pal[0]); // load a palette the same way as any other palette in any other screen mode
        int sCount=0;

        pokPlayStream();
        int point=0;
        //uint8_t tempSound[vidhead.sampleSize];

        bool stillGoing=1;
        uint32_t tempTime  = game.getTime();

        uint8_t tempRead[vidhead.sampleSize+vidhead.frameSize];

        while(stillGoing==1){

            uint32_t elapsed = game.getTime()-tempTime;
            if(elapsed > myDelay){
                tempTime = game.getTime() - (elapsed-myDelay);
                if(game.update()){

                    // the sample buffer fromthe file is a different size to the pokitto
                    //game.sound.ampEnable(false);
//                    myAmp=0;
//                    if(!fileReadBytes(&tempSound[0], vidhead.sampleSize))stillGoing=0;

                    if(!fileReadBytes(&tempRead[0], vidhead.sampleSize+vidhead.frameSize))stillGoing=0;
                    point = soundbufindex;
                    for(int t=0; t<vidhead.sampleSize; t++){
                        if(point >= SBUFSIZE){point=0;}
                        soundbuf[point++]=tempRead[t];
                    }
                    for(int t=0; t<vidhead.frameSize; t++){
                        game.display.screenbuffer[vidhead.frameOffset+t]=tempRead[t+vidhead.sampleSize];
                    }

//                    if(!fileReadBytes(&game.display.screenbuffer[vidhead.frameOffset], vidhead.frameSize))stillGoing=0;
//                    myAmp=1;
                    //game.sound.ampEnable(true);

/*
                    if(game.rightBtn()){
                        pokPauseStream();
                        for(int t=0; t<SBUFSIZE; t++){
                            soundbuf[point]=0;
                        }
                        point = soundbufindex;
                        fileSeekRelative((vidhead.frameSize+vidhead.sampleSize)*150);
                        pokPlayStream();
                    }
*/
                } // update
            } // timer
        } // stillgoing
        fileClose();


    } // if myFile
}

void FATFS_video(){

    FILE *myFile = fopen("/sd/movie.dat", "rb");
    if (myFile){

        // read header
        fread(&vidhead.ID[0], sizeof(char),3, myFile);
        fread(&vidhead.format, sizeof(char),1, myFile);
        fread(&vidhead.width, sizeof(char),1, myFile);
        fread(&vidhead.height, sizeof(char),1, myFile);

        vidhead.frameSize = vidhead.width * vidhead.height;
        vidhead.frameOffset = ((88-vidhead.height)/2)*110;

        uint8_t temp1[4];
        fread(&temp1[0], sizeof(char),2, myFile);
        vidhead.sampleSize = (temp1[1] << 8) + temp1[0];
        fread(&temp1[0], sizeof(char),4, myFile);
        vidhead.frameCount = (temp1[3] << 24)+(temp1[2] << 16)+(temp1[1] << 8)+temp1[0];
        fread(&vidhead.FPS, sizeof(char),1, myFile);

        myDelay = 1000/vidhead.FPS;

        unsigned char col[3];
        for(int temp=0; temp<256; temp++){
            fread(&col[0], sizeof(char),3, myFile);
            pal[temp] = (col[0]>>3) | ((col[1] >> 2) << 5) | ((col[2] >> 3) << 11);
        }
        game.display.load565Palette(&pal[0]); // load a palette the same way as any other palette in any other screen mode
        int sCount=0;

        pokPlayStream();
        int point=0;
        uint8_t tempSound[vidhead.sampleSize];
        bool stillGoing=1;
        uint32_t tempTime  = game.getTime();

        while(stillGoing==1){
            // delay, 15fps
            uint32_t elapsed = game.getTime()-tempTime;
            if(elapsed > myDelay){
                tempTime = game.getTime() - (elapsed-myDelay);
                if(game.update()){

                    // the sample buffer fromthe file is a different size to the pokitto
                    if(!fread(&tempSound[0], sizeof(char),vidhead.sampleSize, myFile))stillGoing=0;
                    point = soundbufindex;
                    for(int t=0; t<vidhead.sampleSize; t++){
                        soundbuf[point]=tempSound[t];
                        if(point++ > SBUFSIZE){point=0;}
                    }
                    if(!fread(&game.display.screenbuffer[vidhead.frameOffset], sizeof(char),vidhead.frameSize, myFile))stillGoing=0;

                    if(game.rightBtn()){
                        pokPauseStream();
                        for(int t=0; t<SBUFSIZE; t++){
                            soundbuf[point]=0;
                        }
                        point = soundbufindex;
                        fseek(myFile, (vidhead.frameSize+vidhead.sampleSize)*150, SEEK_CUR);
                        pokPlayStream();
                    }

                } // update
            } // timer
        } // stillgoing
        fclose(myFile);
    } // myFile

}



int main(){
    game.begin();
    game.display.persistence=1;
    game.setFrameRate(999);

    int temp;
    SDFileSystem sd(/*MOSI*/P0_9, /*MISO*/P0_8, /*SCK*/P0_6, /*CS*/P0_7, /*Mountpoint*/"sd");
    pokInitSD(); // Call init always.

    game.display.print("A for PFFS");
    game.display.print("B for FATFS");

    while (game.isRunning()) {

        if(game.update()){
            if(game.aBtn()){PFFS_Video();}
            if(game.bBtn()){FATFS_video();}
        }
    }

return 1;
}
