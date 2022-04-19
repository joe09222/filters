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
void doFilterToImage();
void blackAndWhite();
void invertImage();
void MergeImages();
void flip();
void flipH();
void flipV();
void adjustBrightness( bool isDarken );
void drakenAndLighten();
void detectEdges();
void rotate90();
void rotate180();
void rotate270();
void doRotation();

void shrinkImageHalf();
void shrinkImageQuarter();
void shrinkImageThird();
void shrinkImage();


// Global Variabels 
unsigned char image[256][256];          // image will be stored in 2d matrix

int main() {

    menu();

}

void menu(){

    while( true ){
        helper::println("WELCOME TO BEST IMAGE FILTER IN FCAI");
        // read grayscale image 
        loadGrayScaleImage( image ); 

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
            // do filter 1 to image 
            blackAndWhite();
            // save the new image 
            saveNewGrayScaleImage( image );
            return 0;
        case 2:
            invertImage();
            saveNewGrayScaleImage( image );
            return 0;
        case 3:
            MergeImages();
            saveNewGrayScaleImage( image );
            return 0;
        case 4:
            flip();
            saveNewGrayScaleImage( image );
            return 0;
        case 5:
            // we will save the file inside the function 
            doRotation();
            return 0;
        case 6:
            drakenAndLighten();
            saveNewGrayScaleImage( image );
            return 0;
        case 7:
            detectEdges();
            saveNewGrayScaleImage( image );
            return 0;
        case 9:
            shrinkImage();
            return 0;
        default:
            helper::println("something really wrong happened");
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



void doFilterToImage(){
    // do filters here
}

void loadGrayScaleImage( unsigned char imageArray[256][256] = image ){
    char imageFileName[200];                        // stores image path

    cout << "ENTER IMAGE FILENAME" << endl;
    cin >> imageFileName;                           // get image path
    strcat(imageFileName, ".bmp");                  // appned .bmp to the path 

    
    // read gray scale image fron the file we chosen to the image array
    int isOk = readGSBMP( imageFileName, imageArray );    

}

void saveNewGrayScaleImage( unsigned char imageArray[256][256] = image ){
    char imageFileName[200];                        // stores image path

    cout << "ENTER IMAGE NEW FILENAME" << endl;
    cin >> imageFileName;                           // get image path
    strcat(imageFileName, ".bmp");                  // appned .bmp to the path 

    
    // save new grayscale image
    int isOk = writeGSBMP( imageFileName, imageArray );       
}


// filter - 1
void blackAndWhite(){
    // loop over every pixel
    for( int i = 0; i < 256 ; i++) {
        for( int j = 0; j < 256 ; j++) {
            // check if pixel value is less than 127 we make it black else we make it white
            if( image[i][j] < 127 ){
                image[i][j] = 0;
            }else{
                image[i][j] = 255;
            }
        }
    }
}

// filter - 2
void invertImage(){
    // loop over every pixel
    for( int i = 0; i < 256 ; i++) {
        for( int j = 0; j < 256 ; j++) {
            image[i][j] = ~image[i][j];
        }
    }
}

// filter - 3
void MergeImages() {

    // read another image in variable image 2 
    unsigned char image2[256][256];

    cout << "ENTER FILENAME OF IMAGE YOU WANT TO MERGE " << endl;

    loadGrayScaleImage( image2 );

    // loop over every pixel
    for( int i = 0; i < 256 ; i++){
        for( int j = 0; j < 256 ; j++){
            // we assign pixel -> average of corsponding pixel in the two images
            image[i][j] = ( image[i][j]  + image2[i][j]) / 2;
        }
    }

}

// filter - 4 flip 

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
            // swap left and right columns
            // swap  j -> { 0 -> 255 } => { 1 -> 254 } => ....
            int temp = image[i][j];
            image[i][j] = image[i][256 - j];
            image[i][256-j] = temp;
        }
    }
}

void flipV(){
    // we loop over half the rows not all since we swapping 2 values
    for( int i = 0; i < (256 / 2) ; i++){
        for( int j = 0; j < 256 ; j++){
            // swap upper and lower rows
            // swap i-> { 0 -> 255 } => { 1 -> 254 } => ....
            int temp = image[i][j];
            image[i][j]= image[256-i][j];
            image[256-i][j]= temp;
        }
    }
}


// filter - 5

// VERY STUPID IMPLEMENTATION OF ROTATION { YOU CANT USE DYNAMIC ANGELS }

void doRotation(){
    helper::println("Do you want to Rotate image by 90 | 180 | 270");
    helper::println("1- 90");
    helper::println("2- 180");
    helper::println("any num except 1 and 2  - 270");
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

    unsigned char image2[256][256];

    for( int i = 0; i < 256 ; i++) {
        for( int j = 0; j < 256; j++) {
            // we assign the first column in image 2 -> to the first row in image 1  -> and so on
            image2[255 - j ][i] = image[i][j];
        }
    }

    saveNewGrayScaleImage( image2 );

}

void rotate180() {
    unsigned char image2[256][256];

    for( int i = 0; i < 256 ; i++) {
        for( int j = 0; j < 256; j++) {
            // we assign the last row of the new image to the reversed(first row) of image 1 -> and so on 
            image2[255 - i][j] = image[i][255 - j];
        }
    }
    saveNewGrayScaleImage( image2 );
}

void rotate270() {
    unsigned char image2[256][256];

    for( int i = 0; i < 256 ; i++) {
        for( int j = 0; j < 256; j++) {
            // we assign the last column in image 2 -> to the reversed(first row in image 1)  
            image2[255 - j][255 - i] = image[i][255 - j];
        }
    }

    saveNewGrayScaleImage( image2 );
}


// filter - 6 

void adjustBrightness( bool isDarken ){
    // we loop over all the rows
    for( int i = 0; i < 256 ; i++){
        for( int j = 0; j < 256 ; j++){
            // get current pixel value
            int temp = image[i][j];
            int calc;
            // if we want to darken
            if( isDarken )
                // we add current value - half it 
                calc = temp - ( temp * 0.5 );
            // if we want to brighten
            else 
                // we add current value + half it 
                calc = temp + ( temp * 0.5 );
            // truncate value to 0 and 255 [ becuase they are our limits]
            if( calc >= 255 ){
                calc = 255;
            }else if (calc <= 0) {
                calc = 0;
            }
            // assign new value to the current pixel
            image[i][j] = calc;
        }
    }
}

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

// filter - 7
void detectEdges(){
    // we loop over all the rows
    for( int i = 0; i < 256 ; i++){
        for( int j = 0; j < 256 ; j++){
            int gx = 0;
            int gy = 0;

            // get top values 
            for( int k = 0; k < 2 ;k++){
                gx += -1 * image[i - 1][j - 1] ;
                gx += 1 * image[i - 1][j + 1] ;
                
                gy += 1 * image[i - 1][j - 1] ;
                gy += 2 * image[i - 1][j] ;
                gy += 1 * image[i - 1][j + 1] ;
            }
            // current row
            for( int k = 0; k < 2 ;k++){
                gx += -2 * image[i][j - 1] ;
                gx += 2 * image[i][j + 1] ;

            }
            // current row
            for( int k = 0; k < 2 ;k++){
                gx += -1 * image[i + 1][j - 1] ;
                gx += 1 * image[i + 1][j + 1] ;

                gy += -1 * image[i + 1][j - 1] ;
                gy += -2 * image[i + 1][j] ;
                gy += -1 * image[i + 1][j + 1] ;
            }

            int newVal = ceil(sqrt( (gy * gy) + (gx * gx) ));
            
            image[i][j] = newVal;
        }
    }
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
    unsigned char image2[256][256];          // image will be stored in 2d matrix

    int currentRow = 0;
    int currentCol = 0;

    for( int i = 0; i < 256 ; i+= 2){
        currentCol = 0;
        for( int j = 0; j < 256 ; j+= 2){
            image2[currentRow][currentCol] = image[i][j];
            currentCol++;
        }
        currentRow++;
    }


    for( int i = 0; i < 128 ;i++){
        for( int j = 128; j < 256 ; j++){
            image2[i][j] = 255;
        }
    }

    for( int i = 128; i < 256 ;i++){
        for( int j = 0; j < 256 ; j++){
            image2[i][j] = 255;
        }
    }


    saveNewGrayScaleImage( image2 );

}



void shrinkImageQuarter() {
    unsigned char image2[256][256];          // image will be stored in 2d matrix

    int currentRow = 0;
    int currentCol = 0;

    for( int i = 0; i < 256 ; i+= 4){
        currentCol = 0;
        for( int j = 0; j < 256 ; j+= 4){
            image2[currentRow][currentCol] = image[i][j];
            currentCol++;
        }
        currentRow++;
    }


    for( int i = 0; i < 64 ;i++){
        for( int j = 64; j < 256 ; j++){
            image2[i][j] = 255;
        }
    }

    for( int i = 64; i < 256 ;i++){
        for( int j = 0; j < 256 ; j++){
            image2[i][j] = 255;
        }
    }


    saveNewGrayScaleImage( image2 );

}

void shrinkImageThird() {
    unsigned char image2[256][256];          // image will be stored in 2d matrix

    int currentRow = 0;
    int currentCol = 0;

    for( int i = 0; i < 256 ; i+= 3){
        currentCol = 0;
        for( int j = 0; j < 256 ; j+= 3){
            image2[currentRow][currentCol] = image[i][j];
            currentCol++;
        }
        currentRow++;
    }


    for( int i = 0; i < 86 ;i++){
        for( int j = 86; j < 256 ; j++){
            image2[i][j] = 255;
        }
    }

    for( int i = 86; i < 256 ;i++){
        for( int j = 0; j < 256 ; j++){
            image2[i][j] = 255;
        }
    }


    saveNewGrayScaleImage( image2 );

}






