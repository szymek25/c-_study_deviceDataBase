#include <iostream>
#include <windows.h>
#include <Device.h>
#include <DeviceData.h>
#include <conio.h>
#include <stdio.h>
#include <map>
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define MAX_NAME_LENGHT 20
#define TO_MUCH_CHARACTERS "Your name is to long, max character is 20"
#define IS_NOT_DIGIT "Please input number"
#define DATA_BASE_SIZE 15
#define BRAND "brand"
#define MODEL "model"
#define RAM "ram"
#define MEMORY "memory"
#define SCREEN_SIZE "screenSize"

using namespace std;

void gotoxy(int x, int y) {
    COORD c;
    c.X = x-1;
    c.Y = y-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

boolean areYouSure(){
    char i;
    cout <<"Are you sure (y,n)?";
    cin >>i;
    switch(i){
        case 'y':return true;
        break;
        default: return false;
    }
}

void showMenu() {
    gotoxy(30,11);
    cout <<"1.Add device"<<endl;
    gotoxy(30,12);
    cout <<"2.Show devices"<<endl;
    gotoxy(30,13);
    cout <<"3.Manage Databases"<<endl;
    gotoxy(30,14);
    cout <<"4.Save Current Database"<<endl;
    gotoxy(30,15);
    cout <<"5.Load Current Database"<<endl;
    gotoxy(30,16);
    cout <<"6.Trash"<<endl;
    gotoxy(30,17);
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

void displayFounded(DeviceData deviceData,bool isFound){
    char c;
    do {
        if(! isFound) {
            system("cls");
            cout <<"No devices founded"<< endl;
            cout <<"Press any key to continue ..."<< endl;
            getch();
            break;
        }
        system("cls");
        cout <<"Founded devices: "<< deviceData.getCurrentFoundNumber() + 1 << "/" << deviceData.getAmountFound();
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
    } while(c != '0');
}

void searchByBrand(DeviceData deviceData){
    char c;
    char input[MAX_NAME_LENGHT];

    cout <<"Input phrase: ";
    cin >> input;
    bool isFound = deviceData.searchByBrand(input);

    displayFounded(deviceData,isFound);
}

void searchByModel(DeviceData deviceData){
    char c;
    char input[MAX_NAME_LENGHT];

    cout <<"Input phrase: ";
    cin >> input;
    bool isFound = deviceData.searchByModel(input);

    displayFounded(deviceData,isFound);
}

void searchByPrice(DeviceData deviceData) {
    float min,max;
    cout << "Input min price: ";
    cin >> min;
    cout <<"Input max price: ";
    cin >> max;
    if(min>max){
        cout <<"You inputted ridiculous data" << endl;
        cout <<"Press any key to continue ..."<< endl;
        getch();
        return;
    }

    bool isFound = deviceData.searchPrice(min,max);

    displayFounded(deviceData,isFound);

    system("cls");
}

void editDevice(Device& device,int x,int y) {
    char *brand,*model;
    int ram,memory;
    float price,screenSize;
    string brand_str,model_str,screenSize_str,price_str,ram_str,memory_str;

    gotoxy(x,y-2);
    cout <<"If you do not want to edit, leave field blank" <<endl;
    gotoxy(x,y);
    cout <<"Current Brand: " << device.getBrandName()<<endl;
    gotoxy(x,y+1);
    cout <<"New Brand:             "<<endl;
    gotoxy(x,y+2);
    cout <<"Current Model: "<< device.getModel() <<endl;
    gotoxy(x,y+3);
    cout <<"New Model:             "<<endl;
    gotoxy(x,y+4);
    cout << "Current Screen Size: " << device.getScreenSize() <<endl;
    gotoxy(x,y+5);
    cout <<"New Screen Size:        "<<endl;
    gotoxy(x,y+6);
    cout <<"Current Ram Amount: "<< device.getRam() <<endl;
    gotoxy(x,y+7);
    cout <<"New Ram Amount:                "<<endl;
    gotoxy(x,y+8);
    cout <<"Current Rom Amount: " << device.getMemory() <<endl;
    gotoxy(x,y+9);
    cout <<"New Rom Amount:                 "<<endl;
    gotoxy(x,y+10);
    cout <<"Current Price: " << device.getPrice() <<endl;
    gotoxy(x,y+11);
    cout <<"New Price:               "<<endl;


    gotoxy(x+10,y+1);
    cin.ignore();
    getline(cin,brand_str);
    if(!brand_str.empty()) {
        brand = &brand_str[0];
        device.setBrandName(brand);
    }


    gotoxy(x+10,y+3);
    getline(cin,model_str);
    if(!model_str.empty()) {
        model = &model_str[0];
        device.setModel(model);
    }

    gotoxy(x+16,y+5);
    getline(cin,screenSize_str);
    if(!screenSize_str.empty()) {
        screenSize = atof(screenSize_str.c_str());
        device.setScreenSize(screenSize);
    }

    gotoxy(x+15,y+7);
    getline(cin,ram_str);
    if(!ram_str.empty()) {
        ram = atoi(ram_str.c_str());
        device.setRam(ram);
    }

    gotoxy(x+15,y+9);
    getline(cin,memory_str);
    if(!memory_str.empty()) {
        memory = atoi(memory_str.c_str());
        device.setMemory(memory);
    }

    gotoxy(x+10,y+11);
    getline(cin,price_str);
    if(!price_str.empty()) {
        price = atof(price_str.c_str());
        device.setPrice(price);
    }
}

void showDevices(DeviceData& deviceData) {
    char c;

    do {
        if(deviceData.getAmount() <= 0) {
            system("cls");
            cout <<"No devices in database"<< endl;
            cout <<"Press any key to continue ..."<< endl;
            getch();
            break;
        }
        system("cls");
        cout << "Device: "<< deviceData.getCurrentNumber() + 1 << "/" << deviceData.getAmount();
        displayDetailsForDevice(deviceData.getCurrent(),10,10);
        gotoxy(5,20);
        cout <<"Previous[\x1b] Next[\x1a]  Delete[c] Edit[e] Back[0] ";
        gotoxy(5,22);
        cout <<"Search by: Price[s] Model[m] Brand[b]"<<endl;
        c = getch();
        switch(c) {
        case KEY_LEFT:
            deviceData.previous();
            break;
        case KEY_RIGHT:
            deviceData.next();
            break;
        case 'c':
            system("cls");
            if(areYouSure()){
                if(deviceData.getAmountTrash() >= DATA_BASE_SIZE){
                    cout <<"There is no free space in trash"<<endl;
                    cout <<"Press <y> if you want clear trash or <n> if you want cancel"<<endl;
                    c = getch();
                    if(c == 'y'){
                        deviceData.clearTrash();
                    } else{
                        break;
                    }
                }
                deviceData.deleteCurrent();
            }
            break;
        case 's':
            system("cls");
            searchByPrice(deviceData);
            break;
        case 'e':
            system("cls");
            editDevice(deviceData.getCurrent(),30,30);
            break;
        case 'm':
            system("cls");
            searchByModel(deviceData);
            break;
        case 'b':
            system("cls");
            searchByBrand(deviceData);
            break;
        }

    } while(c != '0');
    system("cls");
}

bool validateLenghtOfCharArray(char* array, unsigned int maxLenght) {
    if(strlen(array)>maxLenght) {
        return false;
    }
    return true;
}
void displayNewDeviceForm(int x,int y,map<string,string> values) {
    gotoxy(x,y);
    cout <<"Brand:"<< values[BRAND] <<endl;
    gotoxy(x,y+1);
    cout <<"Model:"<< values[MODEL] <<endl;
    gotoxy(x,y+2);
    cout <<"Screen Size:"<< values[SCREEN_SIZE] <<endl;
    gotoxy(x,y+3);
    cout <<"Ram:"<< values[RAM] <<endl;
    gotoxy(x,y+4);
    cout <<"Rom:"<< values[MEMORY] <<endl;
    gotoxy(x,y+5);
    cout <<"Price:"<<endl;
}

void clearErrorMessageInNewDeviceForm(int x, int y) {
    gotoxy(x,y+7);
    cout <<"                                                   ";
}

void showErrorMessageAndClearInput(int x,int y,string errorMsg,map<string,string> values) {
    system("cls");
    displayNewDeviceForm(x,y,values);
    gotoxy(x,y+7);
    cout <<errorMsg<<endl;
}

void inputDeviceInfo(DeviceData& deviceData, int x, int y) {
    if(deviceData.getAmount() >= DATA_BASE_SIZE){
        system("cls");
        cout <<"Max size of data base has been reached" <<endl;
        cout <<"Press any key to continue ..."<< endl;
        getch();
        system("cls");
        return ;
    }
    char brand[MAX_NAME_LENGHT],model[MAX_NAME_LENGHT];
    int ram,memory;
    float price,screenSize;
    bool isValid = false;

    map<string,string> values;

    displayNewDeviceForm(x,y,values);

    do {
        isValid=false;
        gotoxy(x+6,y);
        cin >> brand;
        isValid = validateLenghtOfCharArray(brand,MAX_NAME_LENGHT);
        if(!isValid) {
            showErrorMessageAndClearInput(x,y,TO_MUCH_CHARACTERS,values);
        }
    } while(!isValid);
    string brand_str(brand);
    values[BRAND] = brand_str;
    clearErrorMessageInNewDeviceForm(x,y);

    do {
        gotoxy(x+6,y+1);
        cin >> model;
        isValid = validateLenghtOfCharArray(model,MAX_NAME_LENGHT);
        if(!isValid) {
            showErrorMessageAndClearInput(x,y,TO_MUCH_CHARACTERS,values);
        }
    } while(!isValid);
    string model_str(model);
    values[MODEL] = model_str;
    clearErrorMessageInNewDeviceForm(x,y);

    do {
        gotoxy(x+12,y+2);
        cin.clear();
        cin.sync();
        cin >> screenSize;

        if(!cin.good()) {
            showErrorMessageAndClearInput(x,y,IS_NOT_DIGIT,values);
        }

    } while(!cin.good());
    clearErrorMessageInNewDeviceForm(x,y);
    values[SCREEN_SIZE] = to_string(screenSize);

    do {
        gotoxy(x+4,y+3);
        cin.clear();
        cin.sync();
        cin >> ram;
        if(!cin.good()) {
            showErrorMessageAndClearInput(x,y,IS_NOT_DIGIT,values);
        }
    } while(!cin.good());
    clearErrorMessageInNewDeviceForm(x,y);
    values[RAM] = to_string(ram);

    do {
        gotoxy(x+4,y+4);
        cin.clear();
        cin.sync();
        cin >> memory;

        if(!cin.good()) {
            showErrorMessageAndClearInput(x,y,IS_NOT_DIGIT,values);
        }

    } while(!cin.good());
    clearErrorMessageInNewDeviceForm(x,y);
    values[MEMORY] = to_string(memory);

    do {
        gotoxy(x+6,y+5);
        cin.clear();
        cin.sync();
        cin >>price;

        if(!cin.good()) {
            showErrorMessageAndClearInput(x,y,IS_NOT_DIGIT,values);
        }

    } while(!cin.good());

    Device device(brand,model,ram,memory,price,screenSize);
    deviceData.add(device);

    system("cls");
}

bool checkIfCurrentLoadedDataBaseStillExsist(DeviceData deviceData, char** dataBases){
    char* dataBaseName = new char[MAX_NAME_LENGHT];
    dataBaseName = deviceData.getDataBaseName();
    int lengthOfArray = deviceData.getamountOfDataBases();
    bool isPresent = false;

    for(int i = 0;i < lengthOfArray;i++){
        if(strcmp(dataBaseName,dataBases[i]) == 0){
            isPresent = true;
            break;
        }
    }

    return isPresent;
}

char* inputNewDataBaseInfo(DeviceData deviceData) {
    char* dataBaseName = new char;
    cout <<"Name:";
    cin >> dataBaseName;
    deviceData.addDataBase(dataBaseName);
    return dataBaseName;
    system("cls");
}

void selectBaseName(DeviceData& deviceData, char **dataBases) {

    int numberOfBase,size;
    bool selected = false;
    size = deviceData.getamountOfDataBases();
    cout <<"Select Database"<<endl;
    do {
        for(int i=0 ; i < size; i++) {
            cout <<"[" << i << "]" << dataBases[i] << endl;
        }
        cin >> numberOfBase;

        if(numberOfBase >= size) {
            cout <<"Please input correct number" << endl;
        } else {
            deviceData.setName(dataBases[numberOfBase]);
            selected = true;
            deviceData.loadData();
        }

    } while(!selected);
    system("cls");
}

void deleteDataBase(DeviceData deviceData){
    char ** dataBases = new char*;
    int numberOfBase,size;
    bool selected = false;
    dataBases = deviceData.loadDataBases();
    size = deviceData.getamountOfDataBases();

     do {
        for(int i=0 ; i < size; i++) {
            cout <<"[" << i << "]" << dataBases[i] << endl;
        }
        cin >> numberOfBase;

        if(numberOfBase >= size) {
            cout <<"Please input correct number" << endl;
        } else {
            selected = true;
            deviceData.deleteDataBase(dataBases,numberOfBase);
        }

    } while(!selected);
    system("cls");
}

void chooseDataBase(DeviceData& deviceData) {
    char **dataBases = new char*;
    dataBases = deviceData.loadDataBases();
    char c;
    char* nameOfBase = new char[MAX_NAME_LENGHT];

    do {

        if(deviceData.getamountOfDataBases() <= 0) {
            cout <<"There is no any databases, please input name for new data base" <<endl;
            nameOfBase = inputNewDataBaseInfo(deviceData);
            deviceData.setName(nameOfBase);
            system("cls");
            return;
        }

        gotoxy(30,11);
        cout << "1.Create new database"<<endl;
        gotoxy(30,12);
        cout << "2.Open exsist database"<<endl;
        gotoxy(30,13);
        cout <<"3.Delete database" <<endl;
        gotoxy(30,14);
        cout << "0.Exit" <<endl;

        c = getch();
        system("cls");
        switch(c) {
        case '1':
            nameOfBase = inputNewDataBaseInfo(deviceData);
            deviceData.setName(nameOfBase);
            deviceData.loadData();
            c = '0';
            break;
        case '2':
            selectBaseName(deviceData,dataBases);
            c = '0';
            break;
        case '3':
            deleteDataBase(deviceData);
            dataBases = deviceData.loadDataBases();
            if(deviceData.getamountOfDataBases() <= 0){
                break;
            }
            if(!checkIfCurrentLoadedDataBaseStillExsist(deviceData,dataBases)){
                selectBaseName(deviceData,dataBases);
                c = '0';
            }
            break;
        }
    } while(c!='0');
}

void showTrash(DeviceData& deviceData) {
    char c;
    do {
        if(deviceData.getAmountTrash() <= 0) {
            system("cls");
            cout <<"No devices in trash"<< endl;
            cout <<"Press any key to continue ..."<< endl;
            getch();
            break;
        }
        system("cls");
        cout <<"Devices in trash: ";
        cout << deviceData.getCurrentTrashNumber() +1 <<"/"<<deviceData.getAmountTrash();
        displayDetailsForDevice(deviceData.getCurrentTrash(),10,10);
        gotoxy(5,20);
        cout <<"Previous[\x1b] Next[\x1a] Restore[r] Clean Trash[d]  Back[0] ";

        c = getch();
        switch(c) {
        case KEY_LEFT:
            deviceData.previousTrash();
            break;
        case KEY_RIGHT:
            deviceData.nextTrash();
            break;
        case 'r':
            if(deviceData.getAmount()>= DATA_BASE_SIZE){
                system("cls");
                cout <<"In a database there is no free memory, if you will try restore this object you will lose it"<<endl;
                cout <<"Do you want continue(y,n)"<<endl;
                c = getch();
                if(c!='y'){
                    break;
                }
            }
            deviceData.restoreFromTrash();
            system("cls");
            break;
        case 'd':
            system ("cls");
            if(areYouSure()){
                deviceData.clearTrash();
            }
            break;
        }
    } while(c != '0');
    system("cls");
}

int main() {
    DeviceData dataBase(DATA_BASE_SIZE);
    char zn;
    gotoxy(30,10);
    cout << "Welcome in device`s database"<<endl;
    chooseDataBase(dataBase);

    do {
        cout <<"Name: "<< dataBase.getDataBaseName()<<endl;
        cout <<"Amount: "<< dataBase.getAmount()<<"/"<<dataBase.getSizeOfBase()<<endl;
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
            if(!dataBase.saveData()){
                cout <<"Something went wrong, try again later"<<endl;
            } else{
                cout <<"Successful"<<endl;
            }
            cout <<"Press any key to continue ..."<< endl;
            getch();
            system("cls");

            break;
        case '5':
            if(!dataBase.loadData()){
                cout <<"Something went wrong, try again later"<<endl;
            } else{
                cout <<"Successful"<<endl;
            }
            cout <<"Press any key to continue ..."<< endl;
            getch();
            system("cls");
            break;
        case '6':
            showTrash(dataBase);
            break;
        }
    } while(zn != '0');
    return 0;
}
