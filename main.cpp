#include <iostream>
#include <string>
#include <sys/stat.h>
#include "src/reservation/reservation.h"
#include "src/database/database.h"

using namespace std;


int read_int();
double read_double();
void pause();
void section(string title);

void add_room(RoomManager &rm);
void room_menu(RoomManager &rm);

void add_customer(CustomerManager &cm);
void customer_menu(CustomerManager &cm);

void make_reservation(ReservationManager &resm, RoomManager &rm, CustomerManager &cm);
void reservation_menu(ReservationManager &resm, RoomManager &rm, CustomerManager &cm);


int main()
{
    const string data_dir = "data";
    mkdir(data_dir.c_str(), 0755);

    RoomManager rm;
    CustomerManager cm;
    ReservationManager resm(rm, cm);

    Database db(data_dir);
    db.load(rm, cm, resm);

    while (true)
    {
        system("clear");
        cout << "================================" << endl;
        cout << "   Hotel Reservation System" << endl;
        cout << "================================" << endl;
        cout << endl;
        cout << "1. Room Management" << endl;
        cout << "2. Customer Management" << endl;
        cout << "3. Reservation Management" << endl;
        cout << "0. Exit" << endl;

        cout << "Choice: ";
        int choice;
        choice = read_int();

        switch (choice)
        {
            case 0:
                db.save(rm, cm, resm);
                cout << "Goodbye." << endl;
                return 0;
            case 1:
                room_menu(rm);
                break;
            case 2:
                customer_menu(cm);
                break;
            case 3:
                reservation_menu(resm, rm, cm);
                break;
            default:
                cout << "  Invalid choice." << endl;
        }
    }
}


int read_int()
{
    string input;
    while (true)
    {
        cin >> input;
        try
        {
            return stoi(input);
        }
        catch (...)
        {
            cout << "  Please enter a whole number: ";
        }
    }
}

double read_double()
{
    string input;
    while (true)
    {
        cin >> input;
        try
        {
            return stod(input);
        }
        catch (...)
        {
            cout << "  Please enter a number: ";
        }
    }
}

void pause()
{
    cout << endl << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}


void section(string title)
{
    cout << endl;
    cout << "--- " << title << " ---" << endl;
}


void add_room(RoomManager &rm)
{
    system("clear");
    section("Add Room");
    cout << "  1. Single Room" << endl;
    cout << "  2. Double Room" << endl;
    cout << "  3. Suite" << endl;
    cout << "  0. Back" << endl;

    cout << "  Choice: ";
    int type;
    type = read_int();

    if (type == 0)
    {
        return;
    }

    if (type < 1 || type > 3)
    {
        cout << "  Invalid choice." << endl;
        return;
    }

    int number;
    cout << "  Room number: ";
    number = read_int();

    double price;
    cout << "  Price per night: $";
    price = read_double();

    if (rm.findRoom(number))
    {
        cout << "  Room #" << number << " already exists." << endl;
        pause();
        return;
    }

    switch (type) {
        case 1:
            rm.addRoom(new SingleRoom(number, price));
            break;
        case 2:
            rm.addRoom(new DoubleRoom(number, price));
            break;
        case 3:
            rm.addRoom(new Suite(number, price));
            break;
    }
    cout << "  Room #" << number << " added successfully." << endl;
    pause();
}

void room_menu(RoomManager &rm)
{
    while (true)
    {
        system("clear");
        section("Room Management");
        cout << "  1. Add Room" << endl;
        cout << "  2. List All Rooms" << endl;
        cout << "  0. Back" << endl;

        cout << "  Choice: ";
        int choice;
        choice = read_int();

        switch (choice) {
            case 0:
                return;
            case 1:
                add_room(rm);
                break;
            case 2:
                section("All Rooms");
                rm.listRooms();
                pause();
                break;
            default:
                cout << "  Invalid choice." << endl;
                pause();
        }
    }
}


void add_customer(CustomerManager &cm)
{
    system("clear");
    section("Add Customer");
    cout << "  1. VIP Customer       (25% discount)" << endl;
    cout << "  2. Corporate Customer (20% discount)" << endl;
    cout << "  3. Group Customer     (15% discount)" << endl;
    cout << "  0. Back" << endl;

    cout << "  Choice: ";
    int type;
    type = read_int();

    if (type == 0)
    {
        return;
    }

    Customer *c = nullptr;
    switch (type) {
        case 1:
        {
            string first;
            cout << "  First name: ";
            cin >> first;

            string last;
            cout << "  Last name: ";
            cin >> last;

            string phone;
            cout << "  Phone: ";
            cin >> phone;

            int points;
            cout << "  Loyalty points: ";
            points = read_int();

            c = new VipCustomer(first, last, phone, points);
            break;
        }
        case 2:
        {
            string first;
            cout << "  First name: ";
            cin >> first;

            string last;
            cout << "  Last name: ";
            cin >> last;

            string phone;
            cout << "  Phone: ";
            cin >> phone;

            string company;
            cout << "  Company name: ";
            cin >> company;

            string tax;
            cout << "  Tax ID: ";
            cin >> tax;

            c = new CorporateCustomer(first, last, phone, company, tax);
            break;
        }
        case 3:
        {
            string org;
            cout << "  Organization: ";
            cin >> org;

            string phone;
            cout << "  Phone: ";
            cin >> phone;

            int size;
            cout << "  Group size: ";
            size = read_int();

            c = new GroupCustomer(org, phone, size);
            break;
        }
        default:
            cout << "  Invalid choice." << endl;
            pause();
            return;
    }
    cm.add_customer(c);
    cout << "  Customer added successfully. ID: " << c->get_id() << endl;
    pause();
}

void customer_menu(CustomerManager &cm)
{
    while (true)
    {
        system("clear");
        section("Customer Management");
        cout << "  1. Add Customer" << endl;
        cout << "  2. Find Customer by ID" << endl;
        cout << "  3. List All Customers" << endl;
        cout << "  0. Back" << endl;

        cout << "  Choice: ";
        int choice;
        choice = read_int();

        switch (choice) {
            case 0:
                return;
            case 1:
                add_customer(cm);
                break;
            case 2:
            {
                int id;
                cout << "  Customer ID: ";
                id = read_int();

                Customer *c = cm.find_customer(id);
                if (c)
                {
                    c->display_info();
                    pause();
                }
                else
                {
                    cout << "  Customer #" << id << " not found." << endl;
                    pause();
                }

                break;
            }
            case 3:
                cm.list_all_customers();
                pause();
                break;
            default:
                cout << "  Invalid choice." << endl;
                pause();
        }
    }
}


void make_reservation(ReservationManager &resm, RoomManager &rm, CustomerManager &cm)
{
    system("clear");
    section("Make Reservation");
    cout << "  1. Standard    (base price)" << endl;
    cout << "  2. Early Bird  (extra 10% off)" << endl;
    cout << "  3. Last Minute (20% surcharge)" << endl;
    cout << "  0. Back" << endl;

    int type;
    cout << "  Reservation type: ";
    type = read_int();

    if (type == 0)
    {
        return;
    }

    if (type < 1 || type > 3)
    {
        cout << "  Invalid choice." << endl;
        return;
    }

    int cust_id;
    cout << "  Customer ID: ";
    cust_id = read_int();

    Customer *cust = cm.find_customer(cust_id);
    if (!cust)
    {
        cout << "  Customer #" << cust_id << " not found." << endl;
        pause();
        return;
    }

    int room_num;
    cout << "  Room number: ";
    room_num = read_int();

    Room *room = rm.findRoom(room_num);
    if (!room)
    {
        cout << "  Room #" << room_num << " not found." << endl;
        pause();
        return;
    }

    cin.ignore();
    Date check_in  = Date::read_from_input("  Check-in");
    Date check_out = Date::read_from_input("  Check-out");

    if (check_in.days_until(check_out) <= 0)
    {
        cout << "  Check-out must be after check-in." << endl;
        pause();
        return;
    }

    switch (type) {
        case 1:
            resm.book_room(cust, room, check_in, check_out);
            break;
        case 2:
            resm.book_early_bird(cust, room, check_in, check_out);
            break;
        case 3:
            resm.book_last_minute(cust, room, check_in, check_out);
            break;
    }
    pause();
}

void reservation_menu(ReservationManager &resm, RoomManager &rm, CustomerManager &cm)
{
    while (true)
    {
        system("clear");
        section("Reservation Management");
        cout << "  1. Book a Room" << endl;
        cout << "  2. Cancel Reservation" << endl;
        cout << "  3. List All Reservations" << endl;
        cout << "  0. Back" << endl;

        cout << "  Choice: ";
        int choice;
        choice = read_int();

        switch (choice) {
            case 0:
                return;
            case 1:
                make_reservation(resm, rm, cm);
                break;
            case 2:
            {
                int id;
                cout << "  Reservation ID: ";
                id = read_int();
                resm.cancel_reservation(id);
                pause();
                break;
            }
            case 3:
                section("All Reservations");
                resm.list_all_reservations();
                pause();
                break;
            default:
                cout << "  Invalid choice." << endl;
                pause();
        }
    }
}
