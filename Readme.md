# Hotel Reservation System
A console-based hotel management system written in C++ demonstrating core OOP principles — inheritance, polymorphism, and encapsulation — across three independently developed modules.

---

## Project structure

```
hotel-reservation/
├── src/
│   ├── date/
│   │   ├── date.h
│   │   └── date.cpp
│   ├── room/
│   │   ├── room.h
│   │   └── room.cpp
│   ├── customer/
│   │   ├── customer.h
│   │   └── customer.cpp
│   └── reservation/
│       ├── reservation.h
│       └── reservation.cpp
├── tests/
│   ├── test_room.cpp
│   ├── test_customer.cpp
│   └── test_reservation.cpp
├── main.cpp
├── Requirements.md
└── README.md
```

---

## Modules

### Date — `src/date/`
A shared utility used by all modules. Provides a simple `Date` struct with day, month, and year fields, and a `days_until()` method used to calculate the number of nights between check-in and check-out.

### Room — `src/room/`
Manages the room hierarchy. `Room` is the abstract base class. Concrete types (`SingleRoom`, `DoubleRoom`, `Suite`) each implement `display_info()`. `RoomManager` holds all rooms in the system and exposes methods to add, find, and list them.

### Customer — `src/customer/`
Manages the customer hierarchy. `Customer` is the abstract base class. Concrete types (`VipCustomer`, `CorporateCustomer`, `GroupCustomer`) each implement `get_discount()` and `display_info()`. `CustomerManager` holds all customers and exposes methods to add, find, and list them.

### Reservation — `src/reservation/`
Manages the reservation hierarchy. `Reservation` is the abstract base class. Concrete types (`StandardReservation`, `EarlyBirdReservation`, `LastMinuteReservation`) each implement `calculate_total()` and `display_info()`. `ReservationManager` links the other two modules together and handles booking and cancellation.

---

## Workflow
Each team member works on their own branch to keep changes isolated and avoid conflicts on `master`.

**1. Clone the repository**
```bash
git clone <repository-url>
cd hotel-reservation
```

**2. Create a branch for your module**
Name your branch after the module you own:
```bash
git checkout -b feature/room
# or
git checkout -b feature/customer
# or
git checkout -b feature/reservation
```

**3. Implement your module**
Work only within your assigned files (see [Module ownership](#module-ownership)). Do not modify another person's module files. If you need a change in a shared file (`src/date/`, `main.cpp`), discuss it with the team first.

**4. Commit and push your changes**
```bash
git add src/room/ tests/test_room.cpp   # adjust paths to your module
git commit -m "feat(room): implement SingleRoom and RoomManager"
git push origin feature/room
```

**5. Open a pull request to `master`**
Go to the repository on GitHub and open a pull request from your feature branch into `master`. In the PR description, briefly describe what you implemented and how to test it. At least one other team member should review and approve before merging.

> Keep your branch up to date with `master` by running `git pull origin master` periodically to catch any shared-file changes early.


---

## Compiling

### Full program
```bash
g++ main.cpp src/date/date.cpp src/room/room.cpp src/customer/customer.cpp src/reservation/reservation.cpp -o hotel
./hotel
```

### Individual module tests
Each module has its own test file with its own `main()`. Compile and run them independently — no conflicts with `main.cpp`.

```bash
# Test rooms
g++ tests/test_room.cpp src/date/date.cpp src/room/room.cpp -o test_room
./test_room

# Test customers
g++ tests/test_customer.cpp src/date/date.cpp src/customer/customer.cpp -o test_customer
./test_customer

# Test reservations
g++ tests/test_reservation.cpp src/date/date.cpp src/room/room.cpp src/customer/customer.cpp src/reservation/reservation.cpp -o test_reservation
./test_reservation
```

---

## Module ownership

| Module      | Files                                      | Owner    |
|-------------|--------------------------------------------|----------|
| Room        | `src/room/`, `tests/test_room.cpp`         | Kiril    |
| Customer    | `src/customer/`, `tests/test_customer.cpp` | Dona     |
| Reservation | `src/reservation/`, `tests/test_reservation.cpp` | Ekaterina |
| Shared      | `src/date/`, `main.cpp`, `README.md`       | Everyone |

> Each person is responsible for their own module folder and test file.  
> Do not edit another person's module files.  
> `main.cpp` should only be edited after agreeing with the whole team.

---

## Features

- Add and list rooms by type (single, double, suite)
- Add and list customers by type (standard, VIP, corporate, group)
- Book a room for a customer with a check-in and check-out date
- Automatically applies customer discount to the total price
- Cancel a reservation and restore room availability
- List all reservations in the system