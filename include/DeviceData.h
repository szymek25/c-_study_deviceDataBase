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
    Device& getCurrent();
    void next();
    void nextFound();
    void nextTrash();
    void previous();
    void previousFound();
    void previousTrash();
    int getAmount();
    int getAmountTrash();
    void deleteCurrent();
    char** loadDataBases();
    void addDataBase(char* name);
    int getamountOfDataBases();
    void setName(char* name);
    void saveData();
    void loadData();
    bool searchPrice(float min, float max);
    Device getCurrentFound();
    Device getCurrentTrash();
    void restoreFromTrash();
    int getCurrentTrashNumber();
    int getCurrentNumber();
    void clearTrash();
    char* getDataBaseName();
    int getSizeOfBase();
    void deleteDataBase(char** dataBases, int selectedDataBase);
    bool searchByModel(char *input);
    bool searchByBrand(char *input);
    int getAmountFound();
    int getCurrentFoundNumber();

protected:
    Device *tab;
    Device *found;
    Device *trash;
    int sizeOfBase;
    int amount;
    int amountFound;
    int amountTrash;
    int current;
    int currentFound;
    int currentTrash;
    char* name;
    int amountOfDataBases;
private:
    char* addSuffixToFileName(char* suffix);
    void moveToTrash();
};

#endif // DEVICEDATA_H
