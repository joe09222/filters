#include <iostream>
#include <limits>
#include <cstring>
#include <cmath>
#include "bmplib.h"


using namespace std;

// namespaces 
// you need helper::func_name() to acess them
namespace helper {
    // print function like python 
    template <typename T>
    void println( T data ){
        cout << data << endl;
    }
    // print in the same line
    template <typename T>
    void print( T data ){
        cout << data ;
    }

}


// Function declerations 
void loadGrayScaleImage( unsigned char imageArray[256][256]);
void saveNewGrayScaleImage( unsigned char imageArray[256][256] );

void menu(); 
void menuPrompt();
int getIntInput();
int menuHandler( int choice );
void loadRGBImage( unsigned char imageArray[256][256][3]);
void saveRGBImage( unsigned char imageArray[256][256][3] );
void blackAndWhite();
void invertImage();
void MergeImages();
void flip();
void flipH();
void flipV();
void doRotation();
void rotate90();
void rotate180();
void rotate270();
void drakenAndLighten();
void adjustBrightness( bool isDarken );
void detectEdges();
void adjustSize();
void enlargeImage( int startingRow, int startingCloumn );
void shrinkImage();
void shrinkImageHalf();
void shrinkImageQuarter();
void shrinkImageThird();

void mirrorImage();
void mirrorLeftHalf();
void mirrorRightHalf();
void mirrorUpperHalf();
void mirrorLowerHalf();

void shuffleImage();
void fillQuarter( unsigned char newQuarter[128][128][3], int quarter );

void blurImage();


// Global Variabels 
unsigned char image[256][256][3];          // image will be stored in 2d matrix

int main() {

    menu();

}

void menu(){

    while( true ){
        helper::println("WELCOME TO BEST IMAGE FILTER IN FCAI");
        // read grayscale image 
        loadRGBImage( image ); 


        // get menu choice 
        int menuChoice = -1;
        while( (menuChoice < 0 || menuChoice > 14) ){
            menuPrompt();
            menuChoice = getIntInput();
        }

        int handlerVlaue = menuHandler(menuChoice);

        if(  handlerVlaue == -1){
            // exit prgoram
            break;
        }else{
            // check if user wants to use progoram again
            helper::println("Wanna use it again?");
            helper::println("1- to use it");
            int newChoice = getIntInput();
            if( newChoice != 1)
                break;
        }

    }



}

void menuPrompt(){
    helper::println("Please select a filter to apply or 0 to exit:");
    // print choices to user 
    helper::println("1- Black & White Filter");
    helper::println("2- Invert Filter");
    helper::println("3- Merge Filter");
    helper::println("4- Flip Image");
    helper::println("5- Rotate Image");
    helper::println("6- Darken and Lighten Image");
    helper::println("7- Detect Image Edges");
    helper::println("8- Enlarge Image");
    helper::println("9- Shrink image");
    helper::println("10- Mirror image");
    helper::println("11- Shuffle image");
    helper::println("12- Blur image");
    helper::println("0- to exit");
}

int menuHandler( int choice ){
    switch ( choice )
    {
        case 0:
            return -1;
        case 1:
            blackAndWhite();
            saveRGBImage( image );
            return 0;
        case 2:
            invertImage();
            saveRGBImage( image );
            return 0;
        case 3:
            MergeImages();
            saveRGBImage( image );
            return 0;
        case 4:
            flip();
            saveRGBImage( image );
            return 0;
        case 5:
            doRotation();
            return 0;
        case 6:
            drakenAndLighten();
            saveRGBImage( image );
            return 0;
        case 7:
            detectEdges();
            return 0;
        case 8:
            adjustSize();
            return 0;
        case 9:
            shrinkImage();
            return 0;
        case 10:
            mirrorImage();
            return 0;
        case 11:
            shuffleImage();
            return 0;
        case 12:
            blurImage();
            return 0;
        default:
            return -1;
    }
}


int getIntInput(){
    int userInput;                          // variable that stores the user input

    while(!(cin >> userInput)){                // we make a loop that will work if the usre doesnt enter a value suitable to our variable
        // clear console buffer 
        cin.clear();            
        // ignore the whole line                
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // display a message to the user to tell him to enter 
        cout << "Enter a number dumbass" << endl;
    }
    
    return userInput;
}


void loadRGBImage( unsigned char imageArray[256][256][3]){
    char imageFileName[200];                        // stores image path

    cout << "ENTER IMAGE FILENAME" << endl;
    cin >> imageFileName;                           // get image path
    strcat(imageFileName, ".bmp");                  // appned .bmp to the path 

    
    // read gray scale image fron the file we chosen to the image array
    int isOk = readRGBBMP( imageFileName, imageArray );    

}

void saveRGBImage( unsigned char imageArray[256][256][3] ){
   char imageFileName[200];                        // stores image path

    cout << "ENTER IMAGE FILENAME TO SAVE" << endl;
    cin >> imageFileName;                           // get image path
    strcat(imageFileName, ".bmp");                  // appned .bmp to the path 

    
    // read gray scale image fron the file we chosen to the image array
    int isOk = writeRGBBMP( imageFileName, imageArray );    
}


void saveNewGrayScaleImage( unsigned char imageArray[256][256] ){
    char imageFileName[200];                        // stores image path

    cout << "ENTER IMAGE NEW FILENAME" << endl;
    cin >> imageFileName;                           // get image path
    strcat(imageFileName, ".bmp");                  // appned .bmp to the path 

    
    // save new grayscale image
    int isOk = writeGSBMP( imageFileName, imageArray );       
}



// filter - 1 
void blackAndWhite() {
    for( int i = 0; i < 256 ;i++) {
        for( int j = 0; j < 256 ; j++) {
            // stores the average of 3 colors 
            int pixelIntensity = 0;            
            // add 3 colors intensity 
            for( int k = 0; k < 3 ;k++){
                pixelIntensity += image[i][j][k];
            }
            // get their average 
            pixelIntensity = pixelIntensity / 3;
            // decide to make it black or white 
            if( pixelIntensity < 128 )
                pixelIntensity = 0;
            else
                pixelIntensity = 255;
            
            // assign new values
            for( int k = 0; k < 3 ;k++){
                image[i][j][k] = pixelIntensity ;
            }

        }
    }
}


// filter - 2 
void invertImage() {
    for( int i = 0; i < 256 ;i++){
        for( int j = 0; j < 256 ; j++) {
            // invert every color intensity
            for( int k = 0; k < 3 ; k++){
                image[i][j][k] = ~image[i][j][k];
            }
        }
    }
}

// filter - 3

void MergeImages() {

    // read another image in variable image 2 
    unsigned char image2[256][256][3];

    cout << "ENTER FILENAME OF IMAGE YOU WANT TO MERGE " << endl;

    loadRGBImage( image2 );

    // loop over every pixel
    for( int i = 0; i < 256 ; i++){
        for( int j = 0; j < 256 ; j++){
            // assign every color intesnity the average of the 2 images colors
            for( int k = 0; k < 3 ;k++){
                image[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
            }
        }
    }

}

// filter - 4

void flip(){
    helper::println("Do you want to flip horizontal or vertical ");
    helper::println("0- horizlontal");
    helper::println("any- verical");
    int userChoice;
    userChoice = getIntInput();
    
    if( userChoice == 0){
        flipH();
    }else{
        flipV();
    }
}

void flipH(){
    for( int i = 0; i < 256 ; i++){
        // we loop over half the columns not all since we swapping 2 values
        for( int j = 0; j < (256 / 2) ; j++){
            // swap firs col with las col intensity -> 2nd col with las - 1 intesnity -> ...
            for( int k = 0; k < 3 ; k++){
                int temp = image[i][j][k];
                image[i][j][k] = image[i][256 - j][k];
                image[i][256-j][k] = temp;
            }
        }
    }
}

void flipV() {
    // we loop over half the rows not all since we swapping 2 values
    for( int i = 0; i < (256 / 2) ; i++){
        for( int j = 0; j < 256 ; j++){
            // swap upper and lower rows
            for( int k = 0; k < 3 ;k++){
                int temp = image[i][j][k];
                image[i][j][k]= image[256-i][j][k];
                image[256-i][j][k]= temp;
            }
        }
    }
}


// filter - 5

void doRotation(){
    helper::println("Do you want to Rotate image by 90 | 180 | 270");
    helper::println("1- 90");
    helper::println("2- 180");
    helper::println("any num except 1&2 - 270");
    int userChoice;
    userChoice = getIntInput();
    
    if( userChoice == 1){
        rotate90();
    }else if (userChoice == 2) {
        rotate180();
    }  
    else {
        rotate270();
    }
}
void rotate90() {

    unsigned char image2[256][256][3];

    for( int i = 0; i < 256 ; i++) {
        for( int j = 0; j < 256; j++) {
            // we assign the first column in image 2 -> to the first row in image 1  -> and so on
            for( int k = 0; k < 3 ; k++){
                image2[255 - j ][i][k] = image[i][j][k];
            }
        }
    }

    saveRGBImage( image2 );

}

void rotate180() {
    unsigned char image2[256][256][3];

    for( int i = 0; i < 256 ; i++) {
        for( int j = 0; j < 256; j++) {
            // we assign the last row of the new image to the reversed(first row) of image 1 -> and so on 
            for( int k = 0; k < 3; k++){
                image2[255 - i][j][k] = image[i][255 - j][k];
            }
        }
    }
    saveRGBImage( image2 );
}

void rotate270() {
    unsigned char image2[256][256][3];

    for( int i = 0; i < 256 ; i++) {
        for( int j = 0; j < 256; j++) {
            // we assign the last column in image 2 -> to the reversed(first row in image 1)  
            for( int k = 0; k < 3 ; k++){
                image2[255 - j][255 - i][k] = image[i][255 - j][k];
            }
        }
    }

    saveRGBImage( image2 );
}


// filter - 6
void drakenAndLighten(){
    helper::println("Do you want to Draken or Brighten");
    helper::println("0- Darken");
    helper::println("any- Brighten");
    int userChoice;
    userChoice = getIntInput();
    
    if( userChoice == 0){
        adjustBrightness( true );
    }else{
        adjustBrightness( false );
    }
}


void adjustBrightness( bool isDarken ){
    // we loop over all the rows
    for( int i = 0; i < 256 ; i++){
        for( int j = 0; j < 256 ; j++){
            // if we want to darken
            // subtract from every component of color half it 
            if( isDarken ){
                for( int k = 0; k < 3 ;k++){
                    image[i][j][k] = image[i][j][k] - (image[i][j][k] * 0.5);
                    if( image[i][j][k] < 0)
                        image[i][j][k] = 0;
                    
                }
            }
            // add from every component of color half it 
            else {
                for( int k = 0; k < 3 ;k++){
                    image[i][j][k] = image[i][j][k] + (image[i][j][k] * 0.5);
                    if( image[i][j][k] > 255)
                        image[i][j][k] = 255;
                    
                }
            }
        }
    }
}



// filter - 7 
void detectEdges(){
    unsigned char grayScaleImage[256][256];

    // convert rgb image to grayscale image
    for( int i = 0; i < 256 ; i++){
        for( int j = 0; j < 256 ; j++) {
            // algorthim:  0.299 * R + 0.587 * G + 0.114 * B
            int grayScalePixel =  0.299 * image[i][j][0] + 0.587 * image[i][j][1] + 0.114 * image[i][j][2];
            grayScaleImage[i][j] = grayScalePixel;
        }
    }

    // use normal edge detetction algorthim for grayscale image
    // we loop over all the rows
    for( int i = 0; i < 256 ; i++){
        for( int j = 0; j < 256 ; j++){
            int gx = 0;
            int gy = 0;

            // upper row pixels
            gx += -1 * grayScaleImage[i - 1][j - 1] ;
            gx += 1 * grayScaleImage[i - 1][j + 1] ;
            
            gy += 1 * grayScaleImage[i - 1][j - 1] ;
            gy += 2 * grayScaleImage[i - 1][j] ;
            gy += 1 * grayScaleImage[i - 1][j + 1] ;

            // current row pixels 
            gx += -2 * grayScaleImage[i][j - 1] ;
            gx += 2 * grayScaleImage[i][j + 1] ;

            // below row pixels
            gx += -1 * grayScaleImage[i + 1][j - 1] ;
            gx += 1 * grayScaleImage[i + 1][j + 1] ;

            gy += -1 * grayScaleImage[i + 1][j - 1] ;
            gy += -2 * grayScaleImage[i + 1][j] ;
            gy += -1 * grayScaleImage[i + 1][j + 1] ;

            int newPixelVal = floor(sqrt( (gy * gy) + (gx * gx) ));
            
            if (newPixelVal > 255)
                newPixelVal = 0;
            else
                newPixelVal = 255;

            grayScaleImage[i][j] = newPixelVal;  
        }
    }
    saveNewGrayScaleImage( grayScaleImage );


}

// filter - 8 


void adjustSize() {
    helper::println("Do you want to Enlarge image");
    helper::println("0- first quarter");
    helper::println("1- second quarter");
    helper::println("2- third quarter");
    helper::println("any- forth quarter");
    int userChoice;
    userChoice = getIntInput();
    
    if( userChoice == 0){
        enlargeImage(0,0);
    }else if ( userChoice == 1){
        enlargeImage(0,128);
    }else if ( userChoice == 2){
        enlargeImage(128,0);
    }else {
        enlargeImage(128,128);
    }

}
void enlargeImage( int startingRow, int startingCloumn ){
    unsigned char image2[256][256][3];          // image will be stored in 3d matrix
    
    
    int currentRow = (startingRow - 1 );
    int currentColumn;

    for( int i = 0; i < 256 ; i++){
        if(i % 2 == 0)
            currentRow += 1;
        
        currentColumn = (startingCloumn - 1);
            
        for( int j = 0; j < 256 ; j++){
            if( j % 2 == 0){
                currentColumn += 1;
            }
            
            for( int k = 0; k < 3 ; k++){
                image2[i][j][k] = image[currentRow][currentColumn][k];
            }
 
        }
    }

    saveRGBImage( image2 );

}


// filter 9 

void shrinkImage() {
    helper::println("Do you want to shrink image");
    helper::println("0- half the size");
    helper::println("1- third the size");
    helper::println("any- quarter the size");
    int userChoice;
    userChoice = getIntInput();
    
    if( userChoice == 0){
        shrinkImageHalf();
    }else if ( userChoice == 1){
        shrinkImageThird();
    }else {
        shrinkImageQuarter();
    }
}

void shrinkImageHalf() {
    unsigned char image2[256][256][3];          // image will be stored in 2d matrix

    int currentRow = 0;
    int currentCol = 0;

    for( int i = 0; i < 256 ; i+= 2){
        currentCol = 0;
        for( int j = 0; j < 256 ; j+= 2){
            for( int k = 0; k < 3 ;k++){
                image2[currentRow][currentCol][k] = image[i][j][k];
            }
            currentCol++;
        }
        currentRow++;
    }


    for( int i = 0; i < 128 ;i++){
        for( int j = 128; j < 256 ; j++){
            for( int k = 0; k < 3 ;k++){
                image2[i][j][k] = 255;
            }
        }
    }

    for( int i = 128; i < 256 ;i++){
        for( int j = 0; j < 256 ; j++){
            for( int k = 0; k < 3 ;k++){
                image2[i][j][k] = 255;
            }
        }
    }


    saveRGBImage( image2 );

}



void shrinkImageQuarter() {
    unsigned char image2[256][256][3];          // image will be stored in 2d matrix

    int currentRow = 0;
    int currentCol = 0;

    for( int i = 0; i < 256 ; i+= 4){
        currentCol = 0;
        for( int j = 0; j < 256 ; j+= 4){
            for( int k = 0; k < 3 ;k++){
                image2[currentRow][currentCol][k] = image[i][j][k];
            }
            currentCol++;
        }
        currentRow++;
    }


    for( int i = 0; i < 64 ;i++){
        for( int j = 64; j < 256 ; j++){
            for( int k = 0; k < 3 ;k++){
                image2[i][j][k] = 255;
            }
        }
    }

    for( int i = 64; i < 256 ;i++){
        for( int j = 0; j < 256 ; j++){
            for( int k = 0; k < 3 ;k++){
                image2[i][j][k] = 255;
            }
        }
    }


    saveRGBImage( image2 );

}

void shrinkImageThird() {
    unsigned char image2[256][256][3];          // image will be stored in 2d matrix

    int currentRow = 0;
    int currentCol = 0;

    for( int i = 0; i < 256 ; i+= 3){
        currentCol = 0;
        for( int j = 0; j < 256 ; j+= 3){
            for( int k = 0; k < 3 ;k++){
                image2[currentRow][currentCol][k] = image[i][j][k];
            }
            currentCol++;
        }
        currentRow++;
    }


    for( int i = 0; i < 86 ;i++){
        for( int j = 86; j < 256 ; j++){
            for( int k = 0; k < 3 ;k++){
                image2[i][j][k] = 255;
            }
        }
    }

    for( int i = 86; i < 256 ;i++){
        for( int j = 0; j < 256 ; j++){
            for( int k = 0; k < 3 ;k++){
                image2[i][j][k] = 255;
            }
        }
    }


    saveRGBImage( image2 );

}


// filter - 10 

void mirrorImage(){
    helper::println("Do you want to Mirror image");
    helper::println("0- Left 1/2");
    helper::println("1- Right 1/2");
    helper::println("2- Upper 1/2");
    helper::println("any- Lower 1/2");
    int userChoice;
    userChoice = getIntInput();
    
    if( userChoice == 0){
        mirrorLeftHalf();
    }else if ( userChoice == 1){
        mirrorRightHalf();
    }else if ( userChoice == 2){
        mirrorUpperHalf();
    }else {
        mirrorLowerHalf();
    }
}


void mirrorLeftHalf(){
    unsigned char image2[256][256][3];          // image will be stored in 2d matrix
    // fill first half 
    for( int i = 0; i < 256 ; i++){
        for( int j = 0; j < 128 ; j++) {
            for( int k = 0; k < 3 ;k++){
                image2[i][j][k] = image[i][j][k];
            }
        }
    }
    // Miror first half in reverse
    for( int i = 0; i < 256 ; i++){
        for( int j = 255; j >= 128 ; j--) {
            for( int k = 0; k < 3 ;k++){
                image2[i][j][k] = image[i][255 - j][k];
            }
        }
    }

    saveRGBImage( image2 );
}


void mirrorRightHalf(){
    unsigned char image2[256][256][3];          // image will be stored in 2d matrix
    // fill first half 
    for( int i = 0; i < 256 ; i++){
        for( int j = 128; j < 256 ; j++) {
            for( int k = 0; k < 3 ;k++){
                image2[i][j][k] = image[i][j][k];
            }
        }
    }
    // Miror first half in reverse
    for( int i = 0; i < 256 ; i++){
        for( int j = 256; j >= 128 ; j--) {
            for( int k = 0; k < 3 ;k++){
            image2[i][256 - j][k] = image[i][j][k];
            }
        }
    }

    saveRGBImage( image2 );
}

void mirrorUpperHalf(){
    unsigned char image2[256][256][3];          // image will be stored in 2d matrix
    // fill first half 
    for( int i = 0; i < 128 ; i++){
        for( int j = 0; j < 256 ; j++) {
            for( int k = 0; k < 3 ;k++){
                image2[i][j][k] = image[i][j][k];
            }
        }
    }

    // fill second half 
    for( int i = 255; i >= 128 ; i--) {
        for( int j = 0; j < 256 ; j++) { 
            for( int k = 0; k < 3 ;k++){
                image2[i][j][k] = image[255 - i][j][k];
            }
        }
    }

    saveRGBImage( image2 );
}

void mirrorLowerHalf() {
    unsigned char image2[256][256][3];          // image will be stored in 2d matrix
    // fill first half 
    for( int i = 128; i < 256 ; i++){
        for( int j = 0; j < 256 ; j++) {
            for( int k = 0; k < 3 ;k++){
                image2[i][j][k] = image[i][j][k];
            }
        }
    }

    // fill second half 
    for( int i = 0; i < 128 ; i++) {
        for( int j = 0; j < 256 ; j++) { 
            for( int k = 0; k < 3 ;k++){
                image2[i][j][k] = image[255 - i][j][k];
            }
        }
    }

    saveRGBImage( image2 );
}




// filter - 11 
void shuffleImage(){

    helper::println("Enter order of shuffle");
    int ch1,ch2,ch3,ch4;
    ch1 = getIntInput();
    ch2 = getIntInput();
    ch3 = getIntInput();
    ch4 = getIntInput();

    unsigned char image2[256][256][3];
    unsigned char q1[128][128][3];
    unsigned char q2[128][128][3];
    unsigned char q3[128][128][3];
    unsigned char q4[128][128][3];

  

    fillQuarter(q1,ch1);
    fillQuarter(q2,ch2);
    fillQuarter(q3,ch3);
    fillQuarter(q4,ch4);

    // fill first quarter 
    for( int i = 0; i < 128 ; i++){
        for( int j = 0; j < 128 ;j++){
            for( int k = 0; k < 3 ; k++){
                image2[i][j][k] = q1[i][j][k];
            }
        }
    }

    // fill second quarter 
    for( int i = 0; i < 128 ; i++){
        for( int j = 128; j < 256 ;j++){
            for( int k = 0; k < 3 ; k++){
                image2[i][j][k] = q2[i][j - 128][k];
            }
        }
    }

    // fill third quarter 
    for( int i = 128; i < 256 ; i++){
        for( int j = 0; j < 128 ;j++){
            for( int k = 0; k < 3 ; k++){
                image2[i][j][k] = q3[i - 128][j][k];
            }
        }
    }

    // fill forth quarter 
    for( int i = 128; i < 256 ; i++){
        for( int j = 128; j < 256 ;j++){
            for( int k = 0; k < 3 ; k++){
                image2[i][j][k] = q4[i - 128 ][j - 128][k];
            }
        }
    }
    saveRGBImage( image2 );

}

void fillQuarter( unsigned char newQuarter[128][128][3], int quarter ){

    int rowIncrementArr[4] = {0,0,128,128};
    int columnIncrementArr[4] = {0,128,0,128};

    int rowInc = rowIncrementArr[quarter - 1];
    int columnInc = columnIncrementArr[quarter - 1];

    for( int i = 0; i < 128 ; i++){
        for( int j = 0; j < 128 ;j++){
            for( int k = 0; k < 3 ;k++){
                newQuarter[i][j][k] = image[i + rowInc][j + columnInc][k];
            }
        }
    }
}



// filter - 12 
// guassian blur
void blurImage() {
    unsigned char image2[256][256][3];          // image will be stored in 2d matrix

    // 3x3 kernel
    float kernel[3][3] = {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };

    // get kernel sum
    float kernelSum = 0;
    for( int i = 0; i < 3 ;i++){
        for( int j = 0; j < 3 ;j++){
            kernelSum += kernel[i][j];
        }
    }

    for( int i = 0; i < 256 ;i++) {
        for( int j = 0; j < 256 ; j++) {
            // 3 x 3 kernel apply it to every pixel
            for( int k = 0; k < 3 ; k++){
                int topKernel = image[i-1][j - 1][k] * kernel[0][0] + image[i-1][j][k]  * kernel[0][1] + image[i-1][j+1][k]  * kernel[0][2];
                int middleKernel = image[i][j - 1][k]  * kernel[1][0] + image[i][j][k]  * kernel[1][1] + image[i][j+1][k]  * kernel[1][2];
                int lowerKernel = image[i+1][j - 1][k] * kernel[2][0] + image[i+1][j][k] * kernel[2][1] + image[i+1][j+1][k] * kernel[2][2];
                int newPixelValue = ( (topKernel + middleKernel + lowerKernel) / kernelSum);
                image2[i][j][k] = newPixelValue;
            }
        }
    }

    saveRGBImage( image2 );
}




