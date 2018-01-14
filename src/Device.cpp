#include "Device.h"
#include <string.h>

Device::Device() {
    strcpy(this -> brand," ");
    strcpy(this -> model," ");
    this -> memory = 0;
    this -> price = 0;
    this -> ram = 0;
    this -> screenSize = 0;
}

Device::Device(char *brand, char *model, int ram, int memory, float price, float screenSize) {
    strcpy(this -> brand,brand);
    strcpy(this -> model,model);
    this -> memory = memory;
    this -> price = price;
    this -> ram = ram;
    this -> screenSize = screenSize;
}

char* Device::getBrandName() {
    return brand;
}
char* Device::getModel() {
    return model;
}

int Device::getRam() {
    return ram;
}

int Device::getMemory() {
    return memory;
}

float Device::getScreenSize() {
    return screenSize;
}

float Device::getPrice() {
    return price;
}

void Device::setBrandName(char *newBrandName){
    strcpy(brand,newBrandName);
}

void Device::setModel(char *newModel){
    strcpy(model,newModel);
}

void Device::setScreenSize(float newScreenSize){
    screenSize = newScreenSize;
}

void Device::setPrice(float newPrice){
    price = newPrice;
}

void Device::setRam(int newRam){
    ram = newRam;
}

void Device::setMemory(int newMemory){
    memory = newMemory;
}
