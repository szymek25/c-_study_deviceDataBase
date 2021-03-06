#ifndef DEVICE_H
#define DEVICE_H
#define MAX_NAME_LENGHT 20

class Device
{
    public:
        Device();
        Device(char *brand, char *model, int ram, int memory, float price, float screenSize);
        char* getBrandName();
        char* getModel();
        int getRam();
        int getMemory();
        float getPrice();
        float getScreenSize();
        void setBrandName(char *newBrandName);
        void setModel(char *newModel);
        void setScreenSize(float newScreenSize);
        void setPrice(float newPrice);
        void setRam(int newRam);
        void setMemory(int newMemory);

    protected:
        char brand[MAX_NAME_LENGHT];
        char model[MAX_NAME_LENGHT];
        int ram;
        int memory;
        float price;
        float screenSize;

    private:
};

#endif // DEVICE_H
