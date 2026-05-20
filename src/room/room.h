#pragma once
#include <iostream>
#include <vector>

using namespace std;

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

// abstract klasa
class Room {
protected:
    int roomNumber;
    double pricePerNight;
    bool available;

public:
    Room(int number, double price);

    virtual ~Room() {}

    int getRoomNumber() const;
    double getPrice() const;
    bool isAvailable() const;

    void setAvailability(bool status);

    virtual void display_info() const = 0;
};

// 1 room
class SingleRoom : public Room {
public:
    SingleRoom(int number, double price);

    void display_info() const override;
};

// 2 room
class DoubleRoom : public Room {
public:
    DoubleRoom(int number, double price);

    void display_info() const override;
};

// suite
class Suite : public Room {
public:
    Suite(int number, double price);

    void display_info() const override;
};

// room manager
class RoomManager {
private:
    vector<shared_ptr<Room>> rooms;

public:
    void addRoom(shared_ptr<Room> room);

    shared_ptr<Room> findRoom(int roomNumber);

    void listRooms() const;
};

#endif