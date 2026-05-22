# Hotel Reservation System

A console-based hotel management system in C++. Built as a team project to practice OOP — the three main modules (rooms, customers, reservations) were each developed separately on feature branches and merged into master.

---

## What it does

- Add rooms (single, double, suite) with a price per night
- Add customers — VIP (25% discount), Corporate (20%), Group (15%)
- Book a room for a customer with check-in and check-out dates, with three reservation types:
  - **Standard** — base price with customer discount applied
  - **Early Bird** — extra 10% off on top of the customer discount
  - **Last Minute** — 20% surcharge added
- Cancel a reservation and free up the room automatically
- List all rooms, customers, and reservations
- Everything is saved to disk and reloaded on the next run

---

## Project structure

```
hotel-reservation/
├── src/
│   ├── date/           – Date struct, shared across all modules
│   ├── room/           – Room hierarchy + RoomManager
│   ├── customer/       – Customer hierarchy + CustomerManager
│   ├── reservation/    – Reservation hierarchy + ReservationManager
│   └── database/       – Reads and writes the .dat files
├── data/               – rooms.dat, customers.dat, reservations.dat
└── main.cpp
```

---

## Modules

**Date** (`src/date/`) — a simple struct with day, month, year and a `days_until()` method. Used everywhere to calculate number of nights.

**Room** (`src/room/`) — `Room` is the abstract base. `SingleRoom`, `DoubleRoom`, and `Suite` extend it and implement `display_info()`. `RoomManager` stores and looks up rooms.

**Customer** (`src/customer/`) — `Customer` is the abstract base. `VipCustomer`, `CorporateCustomer`, and `GroupCustomer` each override `get_discount()` and `display_info()`. `CustomerManager` stores and looks up customers.

**Reservation** (`src/reservation/`) — `Reservation` is the abstract base. `StandardReservation`, `EarlyBirdReservation`, and `LastMinuteReservation` each implement `calculate_total()` and `display_info()`. `ReservationManager` links rooms and customers together and handles all booking logic.

**Database** (`src/database/`) — a separate class that handles all file I/O. The managers themselves know nothing about files. On startup it reads the three `.dat` files; on exit it writes them back.

---

## Compiling

```bash
g++ main.cpp src/date/date.cpp src/room/room.cpp src/customer/customer.cpp src/reservation/reservation.cpp src/database/database.cpp -o hotel
./hotel
```

---

## Data files

The `data/` folder is created automatically on first run. The three files use a simple space-separated format:

```
# rooms.dat
SINGLE 101 2500 1       ← type, number, price, available (1/0)

# customers.dat
1001 VIP Aleksandar Petrov 070-123-456 750   ← id, type, fields...

# reservations.dat
STANDARD 1001 101 25/05/2026 28/05/2026 0   ← type, customer id, room, check-in, check-out, cancelled
```

You can edit these files directly — useful for seeding test data or fixing a mistake without going through the menu.

---

## Module ownership

| Module      | Files                                | Owner     |
|-------------|--------------------------------------|-----------|
| Room        | `src/room/`                          | Kiril     |
| Customer    | `src/customer/`                      | Dona      |
| Reservation | `src/reservation/`                   | Ekaterina |
| Shared      | `src/date/`, `src/database/`, `main.cpp` | Everyone  |

Stick to your own module. If you need to change something in a shared file, talk to the others first.

---

## Git workflow

We use feature branches — one per module. Don't commit directly to master.

```bash
git checkout -b feature/reservation   # or room, customer
# ... do your work ...
git add src/reservation/
git commit -m "feat: implement EarlyBirdReservation"
git push origin feature/reservation
```

Then open a pull request to master and get at least one other person to review it before merging.
