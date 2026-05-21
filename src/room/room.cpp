#include "room.h"

// room klasa

Room::Room(int number, double price)
    : roomNumber(number), pricePerNight(price), available(true) {}

int Room::getRoomNumber() const {
    return roomNumber;
}

double Room::getPrice() const {
    return pricePerNight;
}

bool Room::isAvailable() const {
    return available;
}

void Room::setAvailability(bool status) {
    available = status;
}

// 1 room+

SingleRoom::SingleRoom(int number, double price)
    : Room(number, price) {}

void SingleRoom::display_info() const {
    cout << "Single Room | Number: " << roomNumber
         << " | Price: " << pricePerNight
         << " | Available: " << (available ? "Yes" : "No")
         << endl;
}

// 2 room

DoubleRoom::DoubleRoom(int number, double price)
    : Room(number, price) {}

void DoubleRoom::display_info() const {
    cout << "Double Room | Number: " << roomNumber
         << " | Price: " << pricePerNight
         << " | Available: " << (available ? "Yes" : "No")
         << endl;
}

// suite

Suite::Suite(int number, double price)
    : Room(number, price) {}

void Suite::display_info() const {
    cout << "Suite | Number: " << roomNumber
         << " | Price: " << pricePerNight
         << " | Available: " << (available ? "Yes" : "No")
         << endl;
}

// Room manager

void RoomManager::addRoom(shared_ptr<Room> room) {
    rooms.push_back(room);
}

shared_ptr<Room> RoomManager::findRoom(int roomNumber) {
    for (auto room : rooms) {
        if (room->getRoomNumber() == roomNumber) {
            return room;
        }
    }

    return nullptr;
}

void RoomManager::listRooms() const {
    for (const auto& room : rooms) {
        room->display_info();
    }
}