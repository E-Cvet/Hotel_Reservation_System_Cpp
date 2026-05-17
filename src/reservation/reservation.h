#pragma once
#include <iostream>
#include <vector>

#include "room.h"
#include "customer.h"
#include "date.h"

/*
    Info to whoever is in charge of Reservation.
    The protected attributes of Reservation can be whatever you want. That is for you to decide.
    Please leave the public methods as they are, as they are needed in other functionalities.
    Why the public functions are needed:

    Reservation(Customer* customer, Room* room, Date check_in, Date check_out) - Constructor,
            this is how the object is created. Every reservation links a customer to a room
            for a given period. The customer and room are passed as pointers so the reservation
            does not own them — do not delete them in the destructor.
    virtual double calculate_total() - Every child Reservation that you create should implement
            this function. It computes the final price the customer pays for the stay.
            The base formula is: room price * number of nights * (1.0 - customer discount).
            Subclasses can modify this, for example by adding a surcharge or an extra discount
            on top. This is the main polymorphic method of this module.
    virtual void display_info() - Every child Reservation that you create should implement
            this function to display information about that specific reservation.
    int get_id() - Returns the unique ID of the reservation. Used in ReservationManager
            to look up and cancel a specific booking.
    bool is_cancelled() - Returns whether this reservation has been cancelled. Used in
            ReservationManager when listing active reservations.
    void cancel() - Marks the reservation as cancelled and sets the room back to available.

    The three subclasses StandardReservation, EarlyBirdReservation and LastMinuteReservation
    are examples of possible reservation types. You are free to change the internal attributes
    and the pricing logic however you like. What you must not change is calculate_total() and
    display_info() — these must be implemented in every subclass as the rest of the system
    depends on them.

    ReservationManager:
    Same goes for here, the private attributes can be changed completely.
    Please do not change the public method signatures, this is why they are needed:
    void book_room(Customer* customer, Room* room, Date check_in, Date check_out) - Creates
            a new reservation and marks the room as unavailable. Used in main.
    void cancel_reservation(int reservation_id) - Finds the reservation by ID, marks it as
            cancelled and sets the room back to available. Used in main.
    void list_all_reservations() - Prints all reservations in the system. Used in main.
*/

class Reservation {
protected:
    int reservation_id;
    Customer* customer;
    Room* room;
    Date check_in;
    Date check_out;
    static int next_id;

public:
    Reservation(Customer* customer, Room* room, Date check_in, Date check_out);

    virtual double calculate_total() = 0;  // pure virtual
    virtual void display_info() = 0;

    int get_id();
    bool is_cancelled();
    void cancel();

    virtual ~Reservation() = default;
};

class StandardReservation : public Reservation {
public:
    StandardReservation(Customer* customer, Room* room, Date check_in, Date check_out);

    double calculate_total() override;  // room price * nights * customer discount
    void display_info() override;
};

class EarlyBirdReservation : public Reservation {
    double early_bird_discount;  // extra discount on top of customer discount
public:
    EarlyBirdReservation(Customer* customer, Room* room, Date check_in, Date check_out);

    double calculate_total() override;  // standard total minus early bird discount
    void display_info() override;
};

class LastMinuteReservation : public Reservation {
    double surcharge;  // booked too close to check-in, costs more
public:
    LastMinuteReservation(Customer* customer, Room* room, Date check_in, Date check_out);

    double calculate_total() override;  // standard total plus surcharge
    void display_info() override;
};


class ReservationManager {
    vector<Reservation*> reservations;
    RoomManager& room_manager;
    CustomerManager& customer_manager;
public:
    ReservationManager(RoomManager& rm, CustomerManager& cm);

    void book_room(Customer* customer, Room* room, Date check_in, Date check_out);
    void cancel_reservation(int reservation_id);
    void list_all_reservations();

    ~ReservationManager();
};