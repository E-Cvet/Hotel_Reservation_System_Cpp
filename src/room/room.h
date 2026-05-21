#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Room {
protected:
    int roomNumber;
    double pricePerNight;
    bool available;

public:
    Room(int number, double price);

    virtual ~Room() {}

    int getRoomNumber();
    double getPrice();
    bool isAvailable();

    void setAvailability(bool status);

    virtual void display_info() = 0;
};

class SingleRoom : public Room {
public:
    SingleRoom(int number, double price);
    void display_info() override;
};

class DoubleRoom : public Room {
public:
    DoubleRoom(int number, double price);
    void display_info() override;
};

class Suite : public Room {
public:
    Suite(int number, double price);
    void display_info() override;
};

class RoomManager {
private:
    vector<Room *> rooms;

public:
    void addRoom(Room *room);
    Room *findRoom(int roomNumber);
    void listRooms();
    vector<Room *> getRooms();

    ~RoomManager();
};
