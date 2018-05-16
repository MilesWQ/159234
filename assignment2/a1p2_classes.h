// Do not send this file for marking!!!
// File name: a1p2_classes.h
// Read the assignment 1 part 2 specification 
//and make sure you understand how to use this file.

// Ask questions in lectures/tutorials if you 
// have problems with using this file.

#ifndef A1P2_CLASSES_H
#define A1P2_CLASSES_H

#include <iostream>

using namespace std;

class Room;
class Booking;

/**
 * A class representing a room
 */
class Room {
private:
    string name;    ///< name of the room
    string purpose; ///< purpose of the room, can be either "Teaching" or "Meeting"
    int maxMins;    ///< maximum number of minutes allowed to book
    int totalMins;  ///< sum of the minutes requested by all bookings made on this room
public:

    /**
     * Return the name of the room
     * @return value of this->name
     */
    const string &getName() const { return name; }

    /**
     * Set the name of this room
     * @param name_ name to be set to the room
     */
    void setName(const string &name_) { name = name_; }

    /**
     * Return the purpose of the room
     * @return value of this->purpose
     */
    const string &getPurpose() const { return purpose; }

    /**
     * Set the purpose of this room
     * @param purpose_ can be either 'teaching' or 'meeting'
     */
    void setPurpose(const string &purpose_) { purpose = purpose_; }

    /**
     * Return the maximum number of minutes one can book this room for
     * @return value of this->maxMins
     */
    int getMaxMins() const { return maxMins; }

    /**
     * Set the maximum number of minutes this room can be booked for (per booking)
     * @param maxMins_ number of minutes this room can be booked for. Must be non negative
     */
    void setMaxMins(int maxMins_) { maxMins = maxMins_; }

    /**
     * Return the total minutes that have been booked so far
     * @return value of this->totalMins
     */
    int getTotalMins() const { return totalMins; }

    /**
     *  Set the total minutes that have been booked so far
     * @param totalMins_ total minutes that have been booked so far. Must be non negative
     */
    void setTotalMins(int totalMins_) { totalMins = totalMins_; }

    /**
     * Calculate the total minutes requested by all bookings made on this room and store the result in totalMins
     * This function must be called at least one otherwise the field totalMins will stay at 0
     * It is safe to call this function multiple times
     *
     * @param bookings an array of Booking objects
     * @param numBookings the number of objects in bookings
     */
    void calculateTotalBookingMinutes(Booking bookings[], int numBookings);

    /**
     * Print out in the appropriate format all information about this room
     */
    void print();
};

/**
 * A class representing a booking record
 */
class Booking {
private:
    string booker;  ///< name of the person making this booking
    string purpose; ///< purpose of the booking, can be either "teaching" or "meeting"
    string roomName;///< name of the wanted room. If not sure yet put "---"
    int mins;       ///< how long the room is required for, in minutes

public:

    /**
     * Return the name of the person who created this booking
     * @return value of this->booker
     */
    const string &getBooker() const { return booker; }

    /**
     * Set name of the person who created this booking
     * @param booker_ name of the person who created this booking
     */
    void setBooker(const string &booker_) { booker = booker_; }

    /**
     * Return the purpose of this booking
     * @return value of this->purpose
     */
    const string &getPurpose() const { return purpose; }

    /**
     * Set purpose of this booking
     * @param purpose_ purpose of this booking
     */
    void setPurpose(const string &purpose_) { purpose = purpose_; }

    /**
     * Return the name of the room this booking wishes to book
     * @return value of this->roomName
     */
    const string &getRoomName() const { return roomName; }

    /**
     * Set the name of the room this booking wishes to book
     * @param roomName_ name of the room this booking wishes to book, or '---' for "any room is OK"
     */
    void setRoomName(const string &roomName_) { roomName = roomName_; }

    /**
     * Return the number of minutes this booking wishes to book
     * @return value of this->name
     */
    int getMins() const { return mins; }

    /**
     * Set the number of minutes this booking wishes to book
     * @param mins_ number of minutes this booking wishes to book. Must be non negative
     */
    void setMins(int mins_) { mins = mins_; }

    /**
     * Check if this booking has not been assigned a room.
     * Such room will have "---" in the roomName field instead of an actual room name
     * @return true if it does not have an actual room name. false otherwise.
     */
    bool hasNoRoom();

    /**
     * Check if the booking's purpose is the same as the purpose of the room
     * @param rooms an array of Rooms
     * @param numRooms number of Rooms
     * @return false in two cases: 1) if the booking has no room and 2) If it has a room and the purposes don't match
     *         true otherwise
     */
    bool isWrongPurpose(Room *rooms, int numRooms);

    /**
     * Check if the booking requires more time than allowed by the room. If so, reset the required minutes to be the
     * maximum allowance.
     * @param rooms an array of Rooms
     * @param numRooms number of Rooms
     * @return 0 if the requested time is good. Otherwise the required minutes.
     */
    void resetRequestedTime(Room *rooms, int numRooms);

    /**
     * If this booking has not been assigned a room, then search for an appropriate room.
     * That is, a room with the same purpose and has enough available time to accomodate this booking
     * @param rooms an array of Rooms
     * @param numRooms number of Rooms
     * @return true if the assignment is successful. In case there is no available room left, return false
     */
    bool assignAppropriateRoom(Room rooms[], int numRooms);

    /**
     * Print out in the appropriate format all information about this booking
     */
    void print();
};

#endif //A1P2_CLASSES_H