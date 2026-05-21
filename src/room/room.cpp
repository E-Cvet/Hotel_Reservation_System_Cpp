#include "room.h"

Room::Room(int number, double price)
    : roomNumber(number), pricePerNight(price), available(true) {}

int Room::getRoomNumber()
{
    return roomNumber;
}

double Room::getPrice()
{
    return pricePerNight;
}

bool Room::isAvailable()
{
    return available;
}

void Room::setAvailability(bool status)
{
    available = status;
}

SingleRoom::SingleRoom(int number, double price) : Room(number, price) {}

void SingleRoom::display_info()
{
    cout << "Single Room | Number: " << roomNumber
         << " | Price: $" << pricePerNight
         << " | Available: " << (available ? "Yes" : "No") << endl;
}

DoubleRoom::DoubleRoom(int number, double price) : Room(number, price) {}

void DoubleRoom::display_info()
{
    cout << "Double Room | Number: " << roomNumber
         << " | Price: $" << pricePerNight
         << " | Available: " << (available ? "Yes" : "No") << endl;
}

Suite::Suite(int number, double price) : Room(number, price) {}

void Suite::display_info()
{
    cout << "Suite       | Number: " << roomNumber
         << " | Price: $" << pricePerNight
         << " | Available: " << (available ? "Yes" : "No") << endl;
}

void RoomManager::addRoom(Room *room)
{
    rooms.push_back(room);
}

Room *RoomManager::findRoom(int roomNumber)
{
    for (Room *room : rooms)
    {
        if (room->getRoomNumber() == roomNumber)
            return room;
    }
    return nullptr;
}

void RoomManager::listRooms()
{
    for (Room *room : rooms)
        room->display_info();
}

vector<Room *> RoomManager::getRooms()
{
    return rooms;
}

RoomManager::~RoomManager()
{
    for (Room *room : rooms)
        delete room;
}
