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
void blackAndWhite();
void saveRGBImage( unsigned char imageArray[256][256][3] );



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
            return 0;
        case 3:
            return 0;
        case 4:
            return 0;
        case 5:
            return 0;
        case 6:
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