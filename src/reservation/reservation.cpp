#include "reservation.h"

int Reservation::next_id = 1;

Reservation::Reservation(Customer *customer, Room *room, Date check_in, Date check_out)
{
    this->reservation_id = next_id++;
    this->customer = customer;
    this->room = room;
    this->check_in = check_in;
    this->check_out = check_out;
    this->cancelled = false;
}

int Reservation::get_id()
{
    return reservation_id;
}

bool Reservation::is_cancelled()
{
    return cancelled;
}

void Reservation::cancel()
{
    cancelled = true;
    room->setAvailability(true);
}

void Reservation::mark_cancelled()
{
    cancelled = true;
}

int Reservation::get_customer_id()
{
    return customer->get_id();
}

int Reservation::get_room_number()
{
    return room->getRoomNumber();
}

Date Reservation::get_check_in()
{
    return check_in;
}

Date Reservation::get_check_out()
{
    return check_out;
}

StandardReservation::StandardReservation(Customer *customer, Room *room, Date check_in, Date check_out)
    : Reservation(customer, room, check_in, check_out) {}

double StandardReservation::calculate_total()
{
    int nights = check_in.days_until(check_out);
    double room_price = room->getPrice();
    double discount_percentage = 1.0 - customer->get_discount();

    return room_price * nights * discount_percentage;
}

void StandardReservation::display_info()
{
    int nights = check_in.days_until(check_out);
    cout << "\n  [#" << reservation_id << " | Standard | "
         << (cancelled ? "Cancelled" : "Active") << "]" << endl;
    cout << "  Customer : " << customer->get_name()
         << " (ID " << customer->get_id() << ")" << endl;
    cout << "  Room     : #" << room->getRoomNumber()
         << " at $" << fixed << setprecision(2) << room->getPrice() << " per night" << endl;
    cout << "  Period   : " << check_in.to_string()
         << " -> " << check_out.to_string()
         << " (" << nights << " night" << (nights != 1 ? "s" : "") << ")" << endl;
    cout << "  Discount : " << (customer->get_discount() * 100) << "%" << endl;
    cout << "  Total    : $" << fixed << setprecision(2) << calculate_total() << endl;
}

EarlyBirdReservation::EarlyBirdReservation(Customer *customer, Room *room, Date check_in, Date check_out)
    : Reservation(customer, room, check_in, check_out), early_bird_discount(0.10) {}

double EarlyBirdReservation::calculate_total()
{
    int nights = check_in.days_until(check_out);
    double room_price = room->getPrice();
    double discount_percentage = 1.0 - customer->get_discount();

    double base_price = room_price * nights * discount_percentage;

    double early_bird_discount_percentage = 1.0 - early_bird_discount;

    return base_price * early_bird_discount_percentage;
}

void EarlyBirdReservation::display_info()
{
    int nights = check_in.days_until(check_out);
    cout << "\n  [#" << reservation_id << " | Early Bird | "
         << (cancelled ? "Cancelled" : "Active") << "]" << endl;
    cout << "  Customer : " << customer->get_name()
         << " (ID " << customer->get_id() << ")" << endl;
    cout << "  Room     : #" << room->getRoomNumber()
         << " @ $" << fixed << setprecision(2) << room->getPrice() << "/night" << endl;
    cout << "  Period   : " << check_in.to_string()
         << " -> " << check_out.to_string()
         << " (" << nights << " night" << (nights != 1 ? "s" : "") << ")" << endl;
    cout << "  Discount : " << (customer->get_discount() * 100)
         << "% customer + " << (early_bird_discount * 100) << "% early bird" << endl;
    cout << "  Total    : $" << fixed << setprecision(2) << calculate_total() << endl;
}

LastMinuteReservation::LastMinuteReservation(Customer *customer, Room *room, Date check_in, Date check_out)
    : Reservation(customer, room, check_in, check_out)
{
    this->surcharge = 0.20;
}

double LastMinuteReservation::calculate_total()
{
    int nights = check_in.days_until(check_out);
    double room_price = room->getPrice();
    double discount_percentage = 1.0 - customer->get_discount();

    double base_price = room_price * nights * discount_percentage;

    double last_minute_surcharge_percentage = 1.0 + surcharge;

    return base_price * last_minute_surcharge_percentage;
}

void LastMinuteReservation::display_info()
{
    int nights = check_in.days_until(check_out);
    cout << "\n  [#" << reservation_id << " | Last Minute | "
         << (cancelled ? "Cancelled" : "Active") << "]" << endl;
    cout << "  Customer : " << customer->get_name()
         << " (ID " << customer->get_id() << ")" << endl;
    cout << "  Room     : #" << room->getRoomNumber()
         << " @ $" << fixed << setprecision(2) << room->getPrice() << "/night" << endl;
    cout << "  Period   : " << check_in.to_string()
         << " -> " << check_out.to_string()
         << " (" << nights << " night" << (nights != 1 ? "s" : "") << ")" << endl;
    cout << "  Discount : " << (customer->get_discount() * 100) << "%" << endl;
    cout << "  Surcharge: " << (surcharge * 100) << "%" << endl;
    cout << "  Total    : $" << fixed << setprecision(2) << calculate_total() << endl;
}

ReservationManager::ReservationManager(RoomManager &rm, CustomerManager &cm)
    : room_manager(rm), customer_manager(cm) {}

void ReservationManager::book_room(Customer *customer, Room *room, Date check_in, Date check_out)
{
    if (!room->isAvailable())
    {
        cout << "  Room #" << room->getRoomNumber() << " is not available." << endl;
        return;
    }

    room->setAvailability(false);
    reservations.push_back(new StandardReservation(customer, room, check_in, check_out));
    cout << "  Standard reservation #" << reservations.back()->get_id()
         << " created." << endl;
}

void ReservationManager::book_early_bird(Customer *customer, Room *room, Date check_in, Date check_out)
{
    if (!room->isAvailable())
    {
        cout << "  Room #" << room->getRoomNumber() << " is not available." << endl;
        return;
    }

    room->setAvailability(false);
    reservations.push_back(new EarlyBirdReservation(customer, room, check_in, check_out));
    cout << "  Early bird reservation #" << reservations.back()->get_id()
         << " created." << endl;
}

void ReservationManager::book_last_minute(Customer *customer, Room *room, Date check_in, Date check_out)
{
    if (!room->isAvailable())
    {
        cout << "  Room #" << room->getRoomNumber() << " is not available." << endl;
        return;
    }

    room->setAvailability(false);
    reservations.push_back(new LastMinuteReservation(customer, room, check_in, check_out));
    cout << "  Last minute reservation #" << reservations.back()->get_id()
         << " created." << endl;
}

void ReservationManager::cancel_reservation(int reservation_id)
{
    for (Reservation *reservation : reservations)
    {
        if (reservation->get_id() == reservation_id)
        {
            if (reservation->is_cancelled())
            {
                cout << "  Reservation #" << reservation_id
                     << " is already cancelled." << endl;
                return;
            }
            reservation->cancel();
            cout << "  Reservation #" << reservation_id
                 << " cancelled. Room is now available." << endl;
            return;
        }
    }
    cout << "  Reservation #" << reservation_id << " not found." << endl;
}

void ReservationManager::list_all_reservations()
{
    if (reservations.empty())
    {
        cout << "  No reservations in the system." << endl;
        return;
    }

    for (Reservation *reservation : reservations)
    {
        reservation->display_info();
    }
}

void ReservationManager::add_reservation(Reservation *res)
{
    reservations.push_back(res);
}

vector<Reservation *> ReservationManager::getReservations()
{
    return reservations;
}

ReservationManager::~ReservationManager()
{
    for (Reservation *res : reservations)
    {
        delete res;
    }
}
