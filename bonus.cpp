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
    helper::println("9- Shrink image");
    helper::println("0- to exit");
}

int menuHandler( int choice ){
    switch ( choice )
    {
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
            return 0;
        case 9:
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