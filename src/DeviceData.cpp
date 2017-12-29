#include "DeviceData.h"
#include <Device.h>
#include <stdio.h>
#include <string.h>
#define MAX_NAME_LENGHT 20
DeviceData::DeviceData() {
    //ctor
}
DeviceData::DeviceData(int sizeOfBase) {
    this -> sizeOfBase = sizeOfBase;
    tab = new Device[sizeOfBase];
    found = new Device;
    amount = 0;
    amountFound = 0;
    current = -1;
    currentFound = -1;
    amountOfDataBases = 0;
}
void DeviceData::add(Device device) {
    if(amount<sizeOfBase) {
        tab[amount] = device;
        amount++;
        current=amount-1;
    }
}

Device DeviceData::getCurrent() {
    if(this -> current >=0) {
        return this -> tab[this -> current];
    }
}

void DeviceData::next() {
    if(current<amount-1) {
        current++;
    }
}

void DeviceData::nextFound() {
    if(currentFound<amountFound-1) {
        currentFound++;
    }
}

void DeviceData::previous() {
    if(current>0) {
        current--;
    }
}

void DeviceData::previousFound() {
    if(currentFound>0) {
        currentFound--;
    }
}

int DeviceData::getAmount() {
    return amount;
}

void DeviceData::deleteCurrent() {
    if(current>=0 && amount>1) {
        for (int i=current; i<amount-1; i++) {
            tab[i]=tab[i+1];
        }
        amount--;
    } else if(amount ==1) {
        current = -1;
        amount=0;
    }
}

char** DeviceData::loadDataBases() {
    FILE *zp;
    zp = fopen("dataBases","rb");
    fread(&amountOfDataBases,sizeof(amountOfDataBases),1,zp);
    char** dataBases = new char*;

    for(int i=0; i<amountOfDataBases; i++) {
        dataBases[i] = new char[MAX_NAME_LENGHT];
        fread(dataBases[i],sizeof(dataBases[i]),1,zp);
    }
    fclose(zp);
    return dataBases;
}

void DeviceData::addDataBase(char* name) {
    char** dataBases = new char*;
    dataBases = loadDataBases();
    dataBases[amountOfDataBases] = name;
    amountOfDataBases++;

    FILE *zp;
    zp = fopen("dataBases", "wb");
    fwrite(&amountOfDataBases,sizeof(amountOfDataBases),1,zp);
    for(int i=0; i<amountOfDataBases; i++) {
        fwrite(dataBases[i],sizeof(dataBases[i]),1,zp);
    }

    fclose(zp);
}

char* DeviceData::addSuffixToFileName(char* suffix) {
    char *nameofFile = new char;
    strcpy(nameofFile,name);
    strcat(nameofFile,suffix);
    return nameofFile;
}

void DeviceData::saveData() {
    FILE *zp;
    zp = fopen(addSuffixToFileName(".siz"), "wb");

    fwrite(&sizeOfBase, sizeof(sizeOfBase),1,zp);
    fwrite(&amount, sizeof(amount),1,zp);
    fclose(zp);

    zp = fopen(addSuffixToFileName(".dat"), "wb");

    for(int i=0; i<amount; i++) {
        fwrite(&tab[i],sizeof(tab[i]),1,zp);
    }
    fclose(zp);
}

void DeviceData::loadData() {
    FILE *zp;
    zp = fopen(addSuffixToFileName(".siz"), "rb");

    fread(&sizeOfBase, sizeof(sizeOfBase),1,zp);
    fread(&amount, sizeof(amount),1,zp);
    fclose(zp);

    zp = fopen(addSuffixToFileName(".dat"), "rb");

    for(int i=0; i<amount; i++) {
        fread(&tab[i],sizeof(tab[i]),1,zp);
    }

    fclose(zp);

    if(amount > 0) {
        current = 0;
    }
}

int DeviceData::getamountOfDataBases() {
    return amountOfDataBases;
}

void DeviceData::setName(char* name) {
    this -> name = name;
}

bool DeviceData::searchPrice(float min, float max){
    amountFound = 0;
    currentFound = -1;
    for (int i=0;i<amount;i++){
        if(tab[i].getPrice()>=min && tab[i].getPrice()<=max){
            found[amountFound]=tab[i];
            amountFound++;
        }
    }
    if(amountFound){
        currentFound=0;
        return 1;
    }else{
        return 0;
    }
}

Device DeviceData::getCurrentFound(){
    if(currentFound >=0) {
        return found[currentFound];
    }
}
