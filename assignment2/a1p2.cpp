/**
* @file a1p2.cpp
*
* @brief 159234 assignment 1 part 2.
*		   The program reads room and booking data from related files and reset the unreasonable bookings with valid requirements.
*
* @details The program covers below stories:
*          1.When reading either rooms.txt or bookings.txt encounters problems(e.g. the file name isn't "rooms.txt" or "bookings.txt")
*			    the program exits with 1.
*
*			  2.When the data number(the first line) recorded in either file is 0 the program exits with 1.
*
*          3.In general situation, the program assigns or resets a required room of a booking when 1)the booking doesn't specify a room. 
*            2)the purpose of the booking doesn't match its required room. The assignment process will satisfy the booking's purpose as well
*            as its requested time.There's another case that the required room would be reassigned, referring to point #4.
*
*			  4.In case that all bookings have correct purposes with valid time requests, however some required rooms might be booked exceeding
*            the total time constraint(300 mins),in the meanwhile there're extra rooms are available to serve, then the program reassigns appropriate 
*            rooms for some bookings as to balance the room usage.This is implemented by function "resetBookingsWithOverBookedRoom()".
*
*          5.The program fixes the wrong time request of a booking according to its current required room if the purpose matches.
*
*			  6.After executing the time fixing and room reassignment process,the program prints out the formatted output.
*
*          The program doesn't handle below scenarios:
*          1.The data numbers recorded in the first line of files are not consistent with the actual data numbers
*				 (e.g. room number is 4 but the actual room records are 5).In this case, the program just processes the
*				 data according to the number recorded in the first line.
*
*          2.The time request of a booking exceeds maxMins of all available rooms which could satify the booking's purpose. In addition to that, the 
*            purpose of the booking doesn't comply with its required room(or might be empty"---") either. In that case, the program is unable to either 
*            fix the time request or find an appropriate room for it.Since the purpose of the booking doesn't match the room, it's meaningless to fix the 
*            time request according to this incorrect required room. Also the program can't find a suitable room for it because of the invalid requested time.
*
*          3.There is not enough room resources to feed all booking requirements.
*
*          More details refer to assignment A1P2 specification.
*
* @author Wan Qian ID:17326163
*
* @version 1.0
*/

#include <string>
#include <fstream>
#include <iostream>
#include "a1p2_classes.h"

/**
* The total minutes a room can be booked a day.
*/
const int TOTAL_ROOM_MINS = 300;

/**
* The file name of room data.
*/
const char* ROOM_FILE = "rooms.txt";

/**
* The file name of booking data.
*/
const char* BOOKING_FILE = "bookings.txt";

/**
* Maximum number of room data in a room array.
*/
const int MAX_ROOM = 100;

/**
* Maximum number of booking data in a booking array.
*/
const int MAX_BOOKING = 100;

/**
* Read room data file.When the file was read successfully,store the room data into an array and get the number of room data.
* It stores the prompt in a string as a result if there's a problem in reading the file.
*
* @param[out] rooms An array of Room to store the room data read from the file.
* @param[out] numRooms The number of the room information.It will be assigned the value after file reading.
* @param[out] result Return the program terminating information when file reading had problems.
* @return False if there was a problem in opening the file or the number of data is 0.
*         otherwise true.
*/
bool readFile(Room(&rooms)[MAX_ROOM], int &numRooms, string &result);

/**
* Read booking data file.When the file was read successfully,store the booking data into an array and get the number of booking data.
* It stores the prompt in a string as a result if there's a problem in reading the file.
*
* @param[out] bookings An array of Booking to store the booking data read from the file.
* @param[out] numBookings The number of the booking information.It will be assigned the value after file reading.
* @param[out] result Return the program terminating information when file reading had problems.
* @return False if there was a problem in opening the file or the number of data is 0.
*         otherwise true.
*/
bool readFile(Booking(&bookings)[MAX_BOOKING], int &numBookings, string &result);

/**
* Set the totalMins of each room object in an room array according to current bookings' requested time.
* This function should be called when 1)any requested time in the booking array was changed
* 2)any requested room in the booking array was changed.
*
* @param[in] rooms An array of rooms
* @param[in] bookings An array of bookings
* @param[in] numRooms The number of the rooms
* @param[in] numBookings The number of the bookings
*/
void updateTotalMinForRooms(Room(&rooms)[MAX_ROOM], Booking(&bookings)[MAX_BOOKING], int numRooms, int numBookings);

/**
* Assign appropriate rooms to bookings which either didn't specify a room or the purposes didn't match their required rooms.
* This function can guarantee the totalMins of all rooms conform to the constraint when assigning rooms to bookings.
*
* @param[in] rooms An array of rooms
* @param[in] bookings An array of bookings
* @param[in] numRooms The number of the rooms
* @param[in] numBookings The number of the bookings
*/
void resetBookingsOfWrongPurpose(Room(&rooms)[MAX_ROOM], Booking(&Bookings)[MAX_BOOKING], int numRooms, int numBookings);

/**
* Reset requested time to the maximum allowance for bookings if they exceed the maxMins of requested rooms.
*
* @param[in] rooms An array of rooms
* @param[in] bookings An array of bookings
* @param[in] numRooms The number of the rooms
* @param[in] numBookings The number of the bookings
*/
void correctRequestTimeForBookings(Room(&rooms)[MAX_ROOM], Booking(&bookings)[MAX_BOOKING], int numRooms, int numBookings);

/**
* Check whether totalMins of the required room in each booking exceeds TOTAL_ROOM_MINS or not,
* if so rearrange the required room for the corresponding booking.
* This function should be called after finishing the processes of reassignment for wrong purposes and fixing invalid requested time.
* After executing this function the totalMins of all rooms will be complied with the constraint and up to date.
*
* @param[in] rooms An array of room
* @param[in] bookings An array of booking
* @param[in] numRooms The number of the rooms
* @param[in] numBookings The number of the bookings
*/
void resetBookingsWithOverBookedRoom(Room(&rooms)[MAX_ROOM], Booking(&bookings)[MAX_BOOKING], int numRooms, int numBookings);

/**
* Print out student information as requested format.
*/
void printStudentInfo();

/**
* Print out each room information in the room array in requested format.
* @param[in] rooms An array of rooms
* @param[in] numRooms The number of the rooms
*/
void print(Room(&rooms)[MAX_ROOM], int numRooms);

/**
* Print out each booking information in the booking array in requested format.
* @param[in] bookings An array of bookings
* @param[in] numBookings The number of the bookings
*/
void print(Booking(&bookings)[MAX_BOOKING], int numBookings);

/**
* Program entrance.
*/
int main()
{
    Room rooms[MAX_ROOM]; ///< the room array storing room data
    Booking bookings[MAX_BOOKING]; ///< the booking array storing booking data
    int numBookings = 0; ///< the number of booking recorded in the file.
    int numRooms = 0; ///< the number of room recorded in the file.
    string readFileResult; ///< to receive the prompt after reading file.

    if (!readFile(rooms, numRooms, readFileResult)) {
        printStudentInfo();
        cerr << readFileResult << endl;
        return 1;
    }
    if (!readFile(bookings, numBookings, readFileResult)) {
        printStudentInfo();
        cerr << readFileResult << endl;
        return 1;
    }
    updateTotalMinForRooms(rooms, bookings, numRooms, numBookings);

    printStudentInfo();
    cout << "Initially, staff made the following booking requests:" << endl;
    print(bookings, numBookings);
    cout << "\nNow fixing invalid requests...\n" << endl;
    resetBookingsOfWrongPurpose(rooms, bookings, numRooms, numBookings);
    updateTotalMinForRooms(rooms, bookings, numRooms, numBookings);
    correctRequestTimeForBookings(rooms, bookings, numRooms, numBookings);
    updateTotalMinForRooms(rooms, bookings, numRooms, numBookings);
    resetBookingsWithOverBookedRoom(rooms, bookings, numRooms, numBookings);
    cout << "Final booking arrangement is:" << endl;
    print(bookings, numBookings);
    cout << "\nRoom utilisation is:" << endl;
    print(rooms, numRooms);
    return 0;
}

/**
* Calculate the total minutes requested by all bookings made on this room and store the result in totalMins
* This function must be called at least one otherwise the field totalMins will stay at 0
* It is safe to call this function multiple times
*
* @param bookings an array of Booking objects
* @param numBookings the number of objects in bookings
*/
void Room::calculateTotalBookingMinutes(Booking bookings[], int numBookings) {
    int sumOfMins = 0;
    for (int i = 0; i != numBookings; ++i) {
        if (bookings[i].getRoomName() == getName()) {
            sumOfMins += bookings[i].getMins();
        }
    }
    setTotalMins(sumOfMins);
}

/**
* Print out in the appropriate format all information about this room
*/
void Room::print() {
    cout << "Room: " << getName() << " suitable for " << getPurpose() << " purpose allows maximum "
        << getMaxMins() << " minutes. Total booked time: " << getTotalMins() << " minutes." << endl;
}

/**
* Check if this booking has not been assigned a room.
* Such room will have "---" in the roomName field instead of an actual room name
* @return true if it does not have an actual room name. false otherwise.
*/
bool Booking::hasNoRoom() {
    return getRoomName() == "---";
}

/**
* Check if the booking's purpose is the same as the purpose of the room
* @param rooms an array of Rooms
* @param numRooms number of Rooms
* @return true in two cases: 1) if the booking has no room and 2) If it has a room and the purposes don't match
*         false otherwise
*/
bool Booking::isWrongPurpose(Room rooms[], int numRooms) {
    if (hasNoRoom()) {
        return true;
    }
    for (int i = 0; i != numRooms; ++i) {
        if (getRoomName() == rooms[i].getName() && getPurpose() != rooms[i].getPurpose()) {
            return true;
        }
    }
    return false;
}

/**
* Check if the booking requires more time than allowed by the room. If so, reset the required minutes to be the
* maximum allowance.
* @param rooms an array of Rooms
* @param numRooms number of Rooms
*/
void Booking::resetRequestedTime(Room rooms[], int numRooms) {
    for (int i = 0; i != numRooms; ++i) {
        if (getRoomName() == rooms[i].getName()) {
            if (getMins() > rooms[i].getMaxMins()) {
                setMins(rooms[i].getMaxMins());
            }
            return;
        }
    }
}

/**
* If this booking has not been assigned a room, then search for an appropriate room.
* That is, a room with the same purpose and has enough available time to accommodate this booking
* @param rooms an array of Rooms
* @param numRooms number of Rooms
* @return true if the assignment is successful. In case there is no available room left, return false
*/
bool Booking::assignAppropriateRoom(Room rooms[], int numRooms) {
    for (int i = 0; i != numRooms; ++i) {
        if (getPurpose() == rooms[i].getPurpose() && getMins() <= rooms[i].getMaxMins() &&
            getMins() + rooms[i].getTotalMins() <= TOTAL_ROOM_MINS) {
            setRoomName(rooms[i].getName());
            return true;
        }
    }
    return false;
}

/**
* Print out in the appropriate format all information about this booking
*/
void Booking::print() {
    cout << "Booking: by " << getBooker() << " for " << getPurpose() << " purpose at room " << getRoomName() << " for " << getMins() << " minutes" << endl;
}

bool readFile(Room(&rooms)[MAX_ROOM], int &numRooms, string &result) {
    ifstream file(ROOM_FILE);
    if (!file) {
        result = "Error: file rooms.txt is missing. Program terminates.";
        return false;
    }
    file >> numRooms;
    if (numRooms == 0) {
        result = "The number of room information is 0. Program terminates.";
        file.close();
        return false;
    }
    string name, purpose;
    int maxMins = 0;
    for (int i = 0; i != numRooms; ++i) {
        file >> name >> purpose >> maxMins;
        rooms[i].setName(name);
        rooms[i].setPurpose(purpose);
        rooms[i].setMaxMins(maxMins);
    }
    file.close();
    result = "success";
    return true;
}

bool readFile(Booking(&bookings)[MAX_BOOKING], int &numBookings, string &result) {
    ifstream file(BOOKING_FILE);
    if (!file) {
        result = "Error: file bookings.txt is missing. Program terminates.";
        return false;
    }
    file >> numBookings;
    if (numBookings == 0) {
        result = "The number of booking information is 0. Program terminates.";
        file.close();
        return false;
    }
    string booker, purpose, roomName;
    int requestMins;
    for (int i = 0; i != numBookings; ++i) {
        file >> booker >> purpose >> roomName >> requestMins;
        bookings[i].setBooker(booker);
        bookings[i].setPurpose(purpose);
        bookings[i].setRoomName(roomName);
        bookings[i].setMins(requestMins);
    }
    file.close();
    result = "success";
    return true;
}

void updateTotalMinForRooms(Room(&rooms)[MAX_ROOM], Booking(&bookings)[MAX_BOOKING], int numRooms, int numBooking) {
    for (int i = 0; i != numRooms; ++i) {
        rooms[i].calculateTotalBookingMinutes(bookings, numBooking);
    }
}

void resetBookingsOfWrongPurpose(Room(&rooms)[MAX_ROOM], Booking(&bookings)[MAX_BOOKING], int numRooms, int numBookings) {
    for (int i = 0; i != numBookings; ++i) {
        if (bookings[i].isWrongPurpose(rooms, numRooms)) {
            bookings[i].assignAppropriateRoom(rooms, numRooms);
        }
    }
}

void correctRequestTimeForBookings(Room(&rooms)[MAX_ROOM], Booking(&bookings)[MAX_BOOKING], int numRooms, int numBookings) {
    for (int i = 0; i != numBookings; ++i) {
        bookings[i].resetRequestedTime(rooms, numRooms);
    }
}

void resetBookingsWithOverBookedRoom(Room(&rooms)[MAX_ROOM], Booking(&bookings)[MAX_BOOKING], int numRooms, int numBookings) {
    for (int i = 0; i != numBookings; ++i) {
        for (int j = 0; j != numRooms; ++j) {
            if (bookings[i].getRoomName() == rooms[j].getName()) {
                if (rooms[j].getTotalMins() > TOTAL_ROOM_MINS) {
                    bookings[i].assignAppropriateRoom(rooms, numRooms);
                    updateTotalMinForRooms(rooms, bookings, numRooms, numBookings);
                }
                break;
            }
        }
    }
}

void printStudentInfo() {
    cout << "**************************************************\n* 159.234 Assignment 1 Part 2\n"
        "* Name: Wan Qian\n* ID: 17326163\n**************************************************" << endl;
}

void print(Room(&rooms)[MAX_ROOM], int numRooms) {
    for (int i = 0; i != numRooms; ++i) {
        rooms[i].print();
    }
}

void print(Booking(&bookings)[MAX_BOOKING], int numBookings) {
    for (int i = 0; i != numBookings; ++i) {
        bookings[i].print();
    }
}
