#pragma once
#include <iostream>

class Map
{
private:
    int height_;
    int width_;
    char **map_;
public:
    Map(int height, int width){
        height_ = height;
        width_ = width;
        mapInit();
        
       
    };
    ~Map() {
    }
    void mapInit() {
        map_ = new char *[height_];
        for (int count = 0; count < height_; count++)
        {
            map_[count] = new char[width_];
        }
        for (int i = 0; i < height_; i++)
        {
            for (int j = 0; j < width_; j++)
            {
                char a = ' ';
                map_[i][j] = a;
            }
        }
    }
   int getHeight();
   int getWidth();
    void displayMap();

    char **&getMap();

};
