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

void showDevices(DeviceData deviceData) {
    char c;

    do {
        if(deviceData.getAmount() <= 0){
            system("cls");
            cout <<"No devices in data base"<< endl;
            cout <<"Press any key to continue ..."<< endl;
            getch();
            break;
        }
        system("cls");
        displayDetailsForDevice(deviceData.getCurrent(),10,10);
        gotoxy(5,20);
        cout <<"Previous[\x1b] Next[\x1a]  Delete[c]  Back[0] ";
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
int main() {
    DeviceData dataBase(15);
    char zn;
    gotoxy(30,10);
    cout << "Welcome in device`s data base"<<endl;

    do {
        showMenu();
        zn=getch();
        system("CLS");
        switch(zn) {
        case '1':
            inputDeviceInfo(dataBase,30,10);
            break;
        case '2':
            showDevices(dataBase);
            break;
        }
    } while(zn != '0');
    return 0;
}
