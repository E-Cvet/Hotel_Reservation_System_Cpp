#include <iostream>
#include "../src/room/room.h"

using namespace std;

int main() {
    RoomManager manager;

    manager.addRoom(make_shared<SingleRoom>(101, 50));
    manager.addRoom(make_shared<DoubleRoom>(201, 80));
    manager.addRoom(make_shared<Suite>(301, 150));

    manager.listRooms();

    return 0;
}