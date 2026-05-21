#pragma once
#include <string>
#include "../reservation/reservation.h"

using namespace std;

class Database {
    string rooms_file;
    string customers_file;
    string reservations_file;

public:
    Database(string data_dir);

    void load(RoomManager &rm, CustomerManager &cm, ReservationManager &resm);
    void save(RoomManager &rm, CustomerManager &cm, ReservationManager &resm);
};
