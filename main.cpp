#include <iostream>
#include <limits>
#include <cstring>
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
void loadGrayScaleImage();
void saveNewGrayScaleImage();

void menu();
void menuPrompt();
int getIntInput();
int menuHandler( int choice );
void doFilterToImage();



// Global Variabels 
unsigned char image[256][256];          // image will be stored in 2d matrix

int main() {

    menu();

}

void menu(){

    while( true ){
        helper::println("WELCOME TO BEST IMAGE FILTER IN FCAI");
        // read grayscale image 
        loadGrayScaleImage(); 

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
    helper::println("5- Darken and Lighten Image");
    helper::println("6- Rotate Image");
    helper::println("7- Detect Image Edges");
    helper::println("0- to exit");
}

int menuHandler( int choice ){
    switch ( choice )
    {
        case 1:
            // do filter 1 to image 
            doFilterToImage();
            // save the new image 
            saveNewGrayScaleImage();
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

void loadGrayScaleImage(){
    char imageFileName[200];                        // stores image path

    cout << "ENTER IMAGE FILENAME" << endl;
    cin >> imageFileName;                           // get image path
    strcat(imageFileName, ".bmp");                  // appned .bmp to the path 

    
    // read gray scale image fron the file we chosen to the image array
    int isOk = readGSBMP( imageFileName, image );    

}

void saveNewGrayScaleImage(){
    char imageFileName[200];                        // stores image path

    cout << "ENTER IMAGE NEW FILENAME" << endl;
    cin >> imageFileName;                           // get image path
    strcat(imageFileName, ".bmp");                  // appned .bmp to the path 

    
    // save new grayscale image
    int isOk = writeGSBMP( imageFileName, image );       
}

