#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

#include "../room/room.h"
#include "../customer/customer.h"
#include "../date/date.h"

using namespace std;

class Reservation {
protected:
    int reservation_id;
    Customer *customer;
    Room *room;
    Date check_in;
    Date check_out;
    bool cancelled;
    static int next_id;

public:
    Reservation(Customer *customer, Room *room, Date check_in, Date check_out);

    virtual double calculate_total() = 0;
    virtual void display_info() = 0;

    int get_id();
    bool is_cancelled();
    void cancel();
    void mark_cancelled();  // sets flag only, does not touch room — used when loading

    int get_customer_id();
    int get_room_number();
    Date get_check_in();
    Date get_check_out();

    virtual ~Reservation() = default;
};

class StandardReservation : public Reservation {
public:
    StandardReservation(Customer *customer, Room *room, Date check_in, Date check_out);

    double calculate_total() override;  // price * nights * (1 - customer_discount)
    void display_info() override;
};

class EarlyBirdReservation : public Reservation {
    double early_bird_discount;  // extra 10% off on top of customer discount
public:
    EarlyBirdReservation(Customer *customer, Room *room, Date check_in, Date check_out);

    double calculate_total() override;  // standard total * (1 - early_bird_discount)
    void display_info() override;
};

class LastMinuteReservation : public Reservation {
    double surcharge;  // 20% extra for booking close to check-in
public:
    LastMinuteReservation(Customer *customer, Room *room, Date check_in, Date check_out);

    double calculate_total() override;  // standard total * (1 + surcharge)
    void display_info() override;
};


class ReservationManager {
    vector<Reservation *> reservations;
    RoomManager &room_manager;
    CustomerManager &customer_manager;

public:
    ReservationManager(RoomManager &rm, CustomerManager &cm);

    void book_room(Customer *customer, Room *room, Date check_in, Date check_out);
    void book_early_bird(Customer *customer, Room *room, Date check_in, Date check_out);
    void book_last_minute(Customer *customer, Room *room, Date check_in, Date check_out);
    void cancel_reservation(int reservation_id);
    void list_all_reservations();

    void add_reservation(Reservation *res);
    vector<Reservation *> getReservations();

    ~ReservationManager();
};
