#include "database.h"
#include <fstream>
#include <sstream>

Database::Database(string data_dir)
{
    rooms_file         = data_dir + "/rooms.dat";
    customers_file     = data_dir + "/customers.dat";
    reservations_file  = data_dir + "/reservations.dat";
}

static Date parse_date(string s)
{
    int d, m, y;
    char slash;
    istringstream iss(s);
    iss >> d >> slash >> m >> slash >> y;
    return Date(d, m, y);
}

void Database::save(RoomManager &rm, CustomerManager &cm, ReservationManager &resm)
{
    // Rooms
    {
        ofstream file(rooms_file);
        for (auto room : rm.getRooms())
        {
            if (dynamic_cast<SingleRoom *>(room))       file << "SINGLE";
            else if (dynamic_cast<DoubleRoom *>(room))  file << "DOUBLE";
            else                                        file << "SUITE";

            file << " " << room->getRoomNumber()
                 << " " << room->getPrice()
                 << " " << room->isAvailable()
                 << "\n";
        }
    }

    // Customers
    {
        ofstream file(customers_file);
        for (Customer *c : cm.getCustomers())
        {
            if (VipCustomer *v = dynamic_cast<VipCustomer *>(c))
            {
                file << c->get_id() << " VIP"
                     << " " << c->get_name()
                     << " " << c->get_surname()
                     << " " << c->get_phone()
                     << " " << v->get_loyalty_points()
                     << "\n";
            }
            else if (CorporateCustomer *corp = dynamic_cast<CorporateCustomer *>(c))
            {
                file << c->get_id() << " CORPORATE"
                     << " " << c->get_name()
                     << " " << c->get_surname()
                     << " " << c->get_phone()
                     << " " << corp->get_company_name()
                     << " " << corp->get_tax_id()
                     << "\n";
            }
            else if (GroupCustomer *g = dynamic_cast<GroupCustomer *>(c))
            {
                file << c->get_id() << " GROUP"
                     << " " << c->get_name()
                     << " " << c->get_phone()
                     << " " << g->get_group_size()
                     << "\n";
            }
        }
    }

    // Reservations
    {
        ofstream file(reservations_file);
        for (Reservation *res : resm.getReservations())
        {
            if (dynamic_cast<StandardReservation *>(res))       file << "STANDARD";
            else if (dynamic_cast<EarlyBirdReservation *>(res)) file << "EARLYBIRD";
            else                                                file << "LASTMINUTE";

            file << " " << res->get_customer_id()
                 << " " << res->get_room_number()
                 << " " << res->get_check_in().to_string()
                 << " " << res->get_check_out().to_string()
                 << " " << res->is_cancelled()
                 << "\n";
        }
    }
}

void Database::load(RoomManager &rm, CustomerManager &cm, ReservationManager &resm)
{
    // Rooms
    {
        ifstream file(rooms_file);
        string type;
        int number, available;
        double price;

        while (file >> type >> number >> price >> available)
        {
            Room *room = nullptr;
            if (type == "SINGLE")
                room = new SingleRoom(number, price);
            else if (type == "DOUBLE")
                room = new DoubleRoom(number, price);
            else
                room = new Suite(number, price);

            room->setAvailability(available);
            rm.addRoom(room);
        }
    }

    // Customers
    {
        ifstream file(customers_file);
        int saved_id;
        string type;

        while (file >> saved_id >> type)
        {
            Customer::set_next_id(saved_id);

            Customer *c = nullptr;
            if (type == "VIP")
            {
                string first, last, phone;
                int points;
                file >> first >> last >> phone >> points;
                c = new VipCustomer(first, last, phone, points);
            }
            else if (type == "CORPORATE")
            {
                string first, last, phone, company, tax;
                file >> first >> last >> phone >> company >> tax;
                c = new CorporateCustomer(first, last, phone, company, tax);
            }
            else if (type == "GROUP")
            {
                string org, phone;
                int size;
                file >> org >> phone >> size;
                c = new GroupCustomer(org, phone, size);
            }

            if (c)
                cm.add_customer(c);
        }
    }

    // Reservations
    {
        ifstream file(reservations_file);
        string type, check_in_str, check_out_str;
        int customer_id, room_number, cancelled_flag;

        while (file >> type >> customer_id >> room_number
                    >> check_in_str >> check_out_str >> cancelled_flag)
        {
            Customer *cust = cm.find_customer(customer_id);
            Room *room = rm.findRoom(room_number);
            if (!cust || !room)
                continue;

            Date check_in  = parse_date(check_in_str);
            Date check_out = parse_date(check_out_str);

            Reservation *res = nullptr;
            if (type == "STANDARD")
                res = new StandardReservation(cust, room, check_in, check_out);
            else if (type == "EARLYBIRD")
                res = new EarlyBirdReservation(cust, room, check_in, check_out);
            else
                res = new LastMinuteReservation(cust, room, check_in, check_out);

            if (cancelled_flag)
                res->mark_cancelled();

            resm.add_reservation(res);
        }
    }
}
