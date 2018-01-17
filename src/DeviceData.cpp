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
    found = new Device[sizeOfBase];
    trash = new Device[sizeOfBase * 2];
    amount = 0;
    amountFound = 0;
    amountTrash = 0;
    current = -1;
    currentFound = -1;
    currentTrash = -1;
    amountOfDataBases = 0;
}
void DeviceData::add(Device device) {
    if(amount<sizeOfBase) {
        tab[amount] = device;
        amount++;
        current=amount-1;
    }
}

Device& DeviceData::getCurrent() {
    if(current >=0) {
        return tab[current];
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

void DeviceData::nextTrash() {
    if(currentTrash<amountTrash-1) {
        currentTrash++;
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

void DeviceData::previousTrash() {
    if(currentTrash>0) {
        currentTrash--;
    }
}

int DeviceData::getAmount() {
    return amount;
}
int DeviceData::getAmountTrash() {
    return amountTrash;
}

void DeviceData::moveToTrash(){
    trash[amountTrash] = tab[current];
    amountTrash++;
    currentTrash = amountTrash-1;
}

void DeviceData::deleteCurrent() {
    if(current>=0 && amount>1) {
        moveToTrash();
        for (int i=current; i<amount-1; i++) {
            tab[i]=tab[i+1];
        }
        amount--;
        if(current == amount){
            current--;
        }
    } else if(amount ==1) {
        moveToTrash();
        current = -1;
        amount=0;
    }
}

char** DeviceData::loadDataBases() {
    FILE *zp;
    zp = fopen("dataBases","rb");
    fread(&amountOfDataBases,sizeof(amountOfDataBases),1,zp);
    char** dataBases = new char*[amountOfDataBases];

    for(int i=0; i<amountOfDataBases; i++) {
        dataBases[i] = new char[MAX_NAME_LENGHT];
        //dataBases[i] = new char;
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
    char *nameofFile = new char[MAX_NAME_LENGHT];
    strcpy(nameofFile,name);
    strcat(nameofFile,suffix);
    return nameofFile;
}

void DeviceData::saveData() {
    FILE *zp;
    char size[] = ".siz";
    char data[] = ".dat";
    char trash[] = ".trash";
    zp = fopen(addSuffixToFileName(size), "wb");

    fwrite(&sizeOfBase, sizeof(sizeOfBase),1,zp);
    fwrite(&amount, sizeof(amount),1,zp);
    fwrite(&amountTrash, sizeof(amountTrash),1,zp);
    fclose(zp);

    zp = fopen(addSuffixToFileName(data), "wb");

    for(int i=0; i<amount; i++) {
        fwrite(&tab[i],sizeof(tab[i]),1,zp);
    }
    fclose(zp);


    zp = fopen(addSuffixToFileName(trash), "wb");

    for(int i=0; i<amountTrash; i++) {
        fwrite(&trash[i],sizeof(trash[i]),1,zp);
    }
    fclose(zp);
}

void DeviceData::loadData() {
    FILE *zp;
    char size[] = ".siz";
    char data[] = ".dat";
    char trash[] = ".trash";
    amount = 0;
    amountTrash = 0;
    zp = fopen(addSuffixToFileName(size), "rb");

    fread(&sizeOfBase, sizeof(sizeOfBase),1,zp);
    fread(&amount, sizeof(amount),1,zp);
    fread(&amountTrash, sizeof(amountTrash),1,zp);
    fclose(zp);

    zp = fopen(addSuffixToFileName(data), "rb");

    for(int i=0; i<amount; i++) {
        fread(&tab[i],sizeof(tab[i]),1,zp);
    }

    fclose(zp);

    if(amount > 0) {
        current = 0;
    }

    zp = fopen(addSuffixToFileName(trash), "rb");

    for(int i=0; i<amountTrash; i++) {
        fread(&trash[i],sizeof(trash[i]),1,zp);
    }

    fclose(zp);

    if(amountTrash > 0) {
        currentTrash = 0;
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

Device DeviceData::getCurrentTrash(){
    if(currentTrash >= 0){
        return trash[currentTrash];
    }

}

void DeviceData::restoreFromTrash(){
    if(currentTrash>=0 && amountTrash>1) {
        add(trash[currentTrash]);
        for (int i=currentTrash; i<amountTrash-1; i++) {
            trash[i]=trash[i+1];
        }
        amountTrash--;
        if(amountTrash == currentTrash){
            currentTrash--;
        }
    } else if(amountTrash ==1) {
        add(trash[currentTrash]);
        currentTrash = -1;
        amountTrash=0;
    }
}

int DeviceData::getCurrentTrashNumber(){
    return currentTrash;
}

int DeviceData::getCurrentNumber(){
    return current;
}

void DeviceData::clearTrash(){
    amountTrash = 0;
    currentTrash = -1;
}

char* DeviceData::getDataBaseName(){
    return name;
}
int DeviceData::getSizeOfBase(){
    return sizeOfBase;
}

void DeviceData::deleteDataBase(char** dataBases, int selectedDataBase){
    FILE *zp;
    char *dataBaseName = new char[MAX_NAME_LENGHT];
    dataBaseName = dataBases[selectedDataBase];
    char trashFileName[MAX_NAME_LENGHT];
    char sizeFileName[MAX_NAME_LENGHT];

    for(int i = selectedDataBase;i<amountOfDataBases - 1;i++){
        dataBases[i]=dataBases[i+1];
    }
    amountOfDataBases--;

    zp = fopen("dataBases", "wb");
    fwrite(&amountOfDataBases,sizeof(amountOfDataBases),1,zp);
    for(int i=0; i<amountOfDataBases; i++) {
        fwrite(dataBases[i],sizeof(dataBases[i]),1,zp);
    }

    fclose(zp);

    strcpy(trashFileName,dataBaseName);
    strcat(trashFileName,".trash");

    strcpy(sizeFileName,dataBaseName);
    strcat(sizeFileName,".siz");

    strcat(dataBaseName,".dat");

    remove(dataBaseName);
    remove(sizeFileName);
    remove(trashFileName);

}
