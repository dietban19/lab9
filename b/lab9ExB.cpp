//  ENSF 337 Fall 2020 - Exercise B
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

const int size = 6;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::cerr;
struct City {
    double x, y;
    char name[30];
};

void write_binary_file(City cities[], int size, char* filename);
/* PROMISES: attaches an ofstream object to a binary file named "filename" and
 * writes the content of the array cities into the file.
 */
void print_from_binary(char* filename);
/* PROMISES: attaches an ifstream object to a binary file named "filename" and
 * reads the content of the file (one record at a time and displays it on the
 * screen.
 */

int main() {
    char bin_filename[] = "cities.bin";
    
    City cities[size] = {{100, 50, "Calgary"},
        {100, 150, "Edmonton"},
        {50, 50, "Vancouver"},
        {200, 50, "Regina"},
        {500, 50, "Toronto"},
        {200, 50, "Montreal"}};
    
    write_binary_file(cities, size, bin_filename);
    cout << "\nThe content of the binary file is:" << endl;
    print_from_binary(bin_filename);
    return 0;
}

void write_binary_file(City cities[], int size, char* filename){
    ofstream stream(filename, ios::out | ios::binary);
    if(stream.fail()){
        cerr << "failed to open file: " << filename << endl;
        exit(1);
    }
    
    for(int i =0; i < size; i++)
        stream.write((char*)&cities[i], sizeof(City));
    stream.close();
}

void print_from_binary(char* filename) {
    ifstream is(filename, ios::binary);
    City cityName[6];
    if(is.fail()){
        cerr << "Failed to Open File: " << filename << endl;
        exit(1);
    }
    for(int i = 0; i < size; i++){
        is.read(reinterpret_cast<char*>(&cityName[i]), sizeof(cityName));
        cout << "Name: " << cityName[i].name;
        cout << ", x coordinate: " << cityName[i].x;
        cout << ", y coordinate: " << cityName[i].y << endl;
    }
    is.close();
}



