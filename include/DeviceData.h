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
    void nextFound();
    void previous();
    void previousFound();
    int getAmount();
    void deleteCurrent();
    char** loadDataBases();
    void addDataBase(char* name);
    int getamountOfDataBases();
    void setName(char* name);
    void saveData();
    void loadData();
    bool searchPrice(float min, float max);
    Device getCurrentFound();

protected:
    Device *tab;
    Device *found;
    int sizeOfBase;
    int amount;
    int amountFound;
    int current;
    int currentFound;
    char* name;
    int amountOfDataBases;
private:
    char* addSuffixToFileName(char* suffix);
};

#endif // DEVICEDATA_H
