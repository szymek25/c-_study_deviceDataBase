#include <iostream>
#include <windows.h>
#include <Device.h>
#include <DeviceData.h>
#include <conio.h>
#include <stdio.h>
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

void gotoxy(int x, int y) {
    COORD c;
    c.X = x-1;
    c.Y = y-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void showMenu() {
    gotoxy(30,11);
    cout <<"1.Add device"<<endl;
    gotoxy(30,12);
    cout <<"2.Show devices"<<endl;
    gotoxy(30,13);
    cout <<"3.Select Data Base"<<endl;
    gotoxy(30,14);
    cout <<"4.Save Current Data Base"<<endl;
    gotoxy(30,15);
    cout <<"5.Load Current Data Base"<<endl;
    gotoxy(30,16);
    cout <<"0.Exit" <<endl;
}

void displayDetailsForDevice(Device device, int x, int y) {
    gotoxy(x,y);
    cout <<"Brand: "<<device.getBrandName()<<endl;
    gotoxy(x,y+1);
    cout <<"Model: "<<device.getModel()<<endl;
    gotoxy(x,y+2);
    cout <<"Screen Size: "<<device.getScreenSize()<<endl;
    gotoxy(x,y+3);
    cout <<"Ram: "<<device.getRam()<<endl;
    gotoxy(x,y+4);
    cout <<"Rom: "<<device.getMemory()<<endl;
    gotoxy(x,y+5);
    cout <<"Price: "<<device.getPrice()<<endl;

}

void searchByPrice(DeviceData deviceData){
    char c;
    float min,max;
    cout << "Input min price: ";
    cin >> min;
    cout <<"Input max price: ";
    cin >> max;

    bool isFound = deviceData.searchPrice(min,max);
    do{
        if(! isFound){
            system("cls");
            cout <<"No devices founded"<< endl;
            cout <<"Press any key to continue ..."<< endl;
            getch();
            break;
        }
        system("cls");
        cout <<"Founded devices by price";
        displayDetailsForDevice(deviceData.getCurrentFound(),10,10);
        gotoxy(5,20);
        cout <<"Previous[\x1b] Next[\x1a]  Back[0] ";

        c = getch();
        switch(c) {
        case KEY_LEFT:
            deviceData.previousFound();
            break;
        case KEY_RIGHT:
            deviceData.nextFound();
            break;
        }
    }while(c != '0');

    system("cls");
}

void showDevices(DeviceData deviceData) {
    char c;

    do {
        if(deviceData.getAmount() <= 0) {
            system("cls");
            cout <<"No devices in data base"<< endl;
            cout <<"Press any key to continue ..."<< endl;
            getch();
            break;
        }
        system("cls");
        displayDetailsForDevice(deviceData.getCurrent(),10,10);
        gotoxy(5,20);
        cout <<"Previous[\x1b] Next[\x1a]  Delete[c] Search by Price[s] Back[0] ";
        c = getch();
        switch(c) {
        case KEY_LEFT:
            deviceData.previous();
            break;
        case KEY_RIGHT:
            deviceData.next();
            break;
        case 'c':
            deviceData.deleteCurrent();
            break;
        case 's':
            system("cls");
            searchByPrice(deviceData);
            break;
        }

    } while(c != '0');
    system("cls");
}


void inputDeviceInfo(DeviceData& deviceData, int x, int y) {
    char brand[20],model[20];
    int ram,memory;
    float price,screenSize;

    gotoxy(x,y);
    cout <<"Brand:             "<<endl;
    gotoxy(x,y+1);
    cout <<"Model:             "<<endl;
    gotoxy(x,y+2);
    cout <<"Screen Size:        "<<endl;
    gotoxy(x,y+3);
    cout <<"Ram:                "<<endl;
    gotoxy(x,y+4);
    cout <<"Rom:                 "<<endl;
    gotoxy(x,y+5);
    cout <<"Price:               "<<endl;

    gotoxy(x+6,y);
    cin >> brand;
    gotoxy(x+6,y+1);
    cin >> model;
    gotoxy(x+12,y+2);
    cin >> screenSize;
    gotoxy(x+4,y+3);
    cin >> ram;
    gotoxy(x+4,y+4);
    cin >> memory;
    gotoxy(x+6,y+5);
    cin >>price;

    Device device(brand,model,ram,memory,price,screenSize);
    deviceData.add(device);

    system("cls");
}

void inputNewDataBaseInfo(DeviceData& deviceData) {
    char dataBaseName[20];
    cin >> dataBaseName;
    deviceData.addDataBase(dataBaseName);
    deviceData.setName(dataBaseName);
}

void selectBaseName(DeviceData& deviceData, char **dataBases) {

    int i,size;
    bool selected = false;
    size = deviceData.getamountOfDataBases();
    do {
        for(int i=0 ; i < size; i++) {
            cout <<"[" << i << "]" << dataBases[i] << endl;
        }
        cin >> i;

        if(i > size) {
            cout <<"Please input correct number" << endl;
        } else {
            deviceData.setName(dataBases[i]);
            selected = true;
            deviceData.loadData();
        }

    } while(!selected);
    system("cls");
}

void chooseDataBase(DeviceData& deviceData) {
    char **dataBases = deviceData.loadDataBases();
    char c;
    if(deviceData.getamountOfDataBases() <= 0) {
        cout <<"There is no any databases, please input name for new data base";
        inputNewDataBaseInfo(deviceData);
        return;
    }
    do {
        gotoxy(30,11);
        cout << "1.Create new data base"<<endl;
        gotoxy(30,12);
        cout << "2.Open exsist data base"<<endl;
        gotoxy(30,13);
        cout << "0.Exit" <<endl;

        c = getch();
        system("cls");
        switch(c) {
        case '1':
            inputNewDataBaseInfo(deviceData);
            c = '0';
            break;
        case '2':
            selectBaseName(deviceData,dataBases);
            c = '0';
            break;
        }
    } while(c!='0');
}
int main() {
    DeviceData dataBase(15);
    char zn;
    gotoxy(30,10);
    cout << "Welcome in device`s data base"<<endl;
    chooseDataBase(dataBase);

    do {
        showMenu();
        zn=getch();
        system("cls");
        switch(zn) {
        case '1':
            inputDeviceInfo(dataBase,30,10);
            break;
        case '2':
            showDevices(dataBase);
            break;
        case '3':
            chooseDataBase(dataBase);
            break;
        case '4':
            dataBase.saveData();
            break;
        case '5':
            dataBase.loadData();
            break;
        }
    } while(zn != '0');
    return 0;
}
