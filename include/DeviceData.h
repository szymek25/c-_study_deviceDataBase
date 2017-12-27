#ifndef DEVICEDATA_H
#define DEVICEDATA_H
#include <Device.h>


class DeviceData {
public:
    DeviceData();
    DeviceData(int sizeOfBase);
    void add(Device device);
    save();
    read();
    Device getCurrent();
    void next();
    void previous();
    int getAmount();
    void deleteCurrent();
    char** loadDataBases();
    void addDataBase(char* name);
    int getamountOfDataBases();
    void setName(char* name);

protected:
    Device *tab;
    int sizeOfBase;
    int amount;
    int current;
    char* name;
    int amountOfDataBases;
private:
};

#endif // DEVICEDATA_H
