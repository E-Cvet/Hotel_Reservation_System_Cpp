#pragma once
#include <iostream>
#include <vector>

using namespace std;

/*
    Info to whoever is in charge of the Rooms.

    The proected attributes of Rooms can be whatever you want. That is for you to decide. 
    Please leave the public methods of rooms these as they are needed in the other functionalities.

    Why the public functions are needed:
        Room (string number, double price) - Constructor, this is how the object is created, every room should have
                a room number by which it will be identified in the system and the price per night that is worth.

        virtual void display_info() - Every child Room that you create should implement this function to display
                information about that specific room.

        double get_price() - The price of that type of room per night.

        bool get_avaibalitiy() - If the room is available or not.

        void set_availability() - Make it available or not.


    Room Manager:
        Same goes for here, the private attributes can be changed compltely

    Please do not change the public attribute signatures, this is why they are needed:

    This functioanlity will be used in the Reservation.
    Room* find_room(string room_number) - Checks if a room is in the system

    These functionalities are used in main:
    void add_room(Room* room) - Adds a room in the system

    void list_all_rooms() - prints all the rooms in the system 

    void list_available_rooms() - prints only the available rooms in the system


    Furthermore, go wild with any implenetation of any child classes.
*/

/* Abstract base class — all room types must have this. This implementation is concrete.*/
class Room {
protected:
    string room_number;
    double price_per_night;
    bool isAvailable;

public:
    Room(string number, double price);

    virtual void display_info() = 0;

    string get_room_number();
    double get_price();
    bool get_availability();
    void set_availability(bool status);
};


/* Examples for rooms that can be created. These are not concrete: */
class SingleRoom : public Room {
public:
    SingleRoom(int number);
    void display_info() override;
};

class DoubleRoom : public Room {
public:
    DoubleRoom(int number);
    void display_info() override;
};

class Suite : public Room {
    bool has_jacuzzi;  

public:
    Suite(int number, bool jacuzzi = false);
    void display_info() override;
};

// Manages the collection of all rooms
class RoomManager {
private:
    vector<Room*> rooms;  // owns the pointers

public:
    void add_room(Room* room);
    Room* find_room(string room_number);
    void list_all_rooms();
    void list_available_rooms();
    ~RoomManager();  // cleans up Room* pointers
};