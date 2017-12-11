#include "DeviceData.h"
#include <Device.h>
#include <stdio.h>
#define MAX_NAME_LENGHT 20
DeviceData::DeviceData() {
    //ctor
}
DeviceData::DeviceData(int sizeOfBase){
    this -> sizeOfBase = sizeOfBase;
    tab = new Device[sizeOfBase];
	amount = 0;
	current = -1;
	size = 0;
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

char** DeviceData::loadDataBases(){
    FILE *zp;
    zp = fopen("dataBases","rb");
    fread(&size,sizeof(size),1,zp);
    char** dataBases = new char*;

    for(int i=0; i<size;i++)
    {
        dataBases[i] = new char[MAX_NAME_LENGHT];
        fread(dataBases[i],sizeof(dataBases[i]),1,zp);
    }
    fclose(zp);
    return dataBases;
}

void DeviceData::addDataBase(char* name){
    char** dataBases = new char*;
    dataBases = loadDataBases();
    dataBases[size] = name;
    size++;

    FILE *zp;
    zp = fopen("dataBases", "wb");
    fwrite(&size,sizeof(size),1,zp);
    for(int i=0; i<size;i++)
    {
        fwrite(dataBases[i],sizeof(dataBases[i]),1,zp);
    }

    fclose(zp);
}

int DeviceData::getSize(){
    return size;
}
