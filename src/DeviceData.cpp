#include "DeviceData.h"
#include <Device.h>
DeviceData::DeviceData() {
    //ctor
}
DeviceData::DeviceData(int sizeOfBase){
    this -> sizeOfBase = sizeOfBase;
    tab = new Device[sizeOfBase];
	amount = 0;
	current = -1;
}
void DeviceData::add(Device device) {
    if(amount<sizeOfBase){
        tab[amount] = device;
        amount++;
        current=amount-1;
    }
}

Device DeviceData::getCurrent(){
    if(this -> current >=0){
        return this -> tab[this -> current];
    }
}

void DeviceData::next(){
    if(current<amount-1){
        current++;
    }
}

void DeviceData::previous(){
    if(current>0){
        current--;
    }
}

int DeviceData::getAmount(){
    return amount;
}

void DeviceData::deleteCurrent(){
    if(current>=0 && amount>1){
        for (int i=current;i<amount-1;i++){
            tab[i]=tab[i+1];
        }
        amount--;
    }else if(amount ==1){
        current = -1;
        amount=0;
    }
}
