/**
 * @file a1p1.cpp
 *
 * @brief 159234 assignment 1 part 1. The program reads rooms.txt and bookings.txt files and checks
 *         consistencies between booking requests and room information.After rules checking, the result will be printed.
 *
 * @details The program covers below scenarios:
 *				1.When reading either rooms.txt or bookings.txt occurs problems(e.g. the file name isn't "rooms.txt" or "bookings.txt") 
 *				the program exits with EXIT_FAILURE.
 *				2.When the data number(the first line) recorded in either rooms.txt or bookings.txt is 0 the program exits with EXIT_FAILURE.
 *
 *          The program doesn't handle below cases:
 *				1.The data numbers recorded in the first line of files are not consistent with the actual data numbers
 *				(e.g. room number is 4 but the actual room records are 5).In this case, the program just process the 
 *				consistency check according to the number recorded in the first line.
 *				To complement this, the end of loops in below functions should change to MAX_ROOM or MAX_BOOKING:
 *				printRoomNotBooked, printBookingWithoutRoom, printBookingWithWrongPurpose, printBookingWithInvalidTimeRequest.
 *				2.The number of data exceeds 100.
 *          
 *         A possible improvement for this program:
 *				The below functions use nested loop to search the string which lack efficiency.
 *				printRoomNotBooked, printBookingWithWrongPurpose ,printBookingWithInvalidTimeRequest
 *          It could be better if we can sort the arrays then use binary search or use functions from STL <algorithm> directly.
 *
 * @author Qian Wan ID:17326163
 *
 * @version 1.0
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/**
 * Maximum number of room data in a room array.
 */
const size_t MAX_ROOM = 100;

/**
 * Maximum number of booking data in a booking array.
 */
const size_t MAX_BOOKING = 100;

/**
 * a room structure storing the information of a room
 */
struct Room {
	string mRoomName; /**< room name */
	string mPurpose; /**< purpose that the room can be used,two possible values:teaching,meeting */
	int mTimeLimit; /**< maximum time a booking can request for this room */
};

/**
 * a booking structure represent booking requests
 */
struct Booking {
	string mStaffName; /**< name of the person who submitted the booking */
	string mPurpose; /**< purpose of the room request,two possible value:teaching,meeting*/
	string mRoomName; /**< the room name of the request*/
	int mTimeRequest; /**< time requirement in a booking*/
};

/**
 * Read rooms.txt file.When the file was read successfully,store the room data into an array and get the number of room data.
 *
 * @param[out] rooms An array of Room to store the room data read from the file.
 * @param[out] roomNum The number of the room information.It will be assigned the value after file reading.
 * @param[out] result Return the program terminating information when file reading had problems.
 * @return true if the file is read successfully,false if there's a problem in opening the file.
 */
bool readFile(Room(&rooms)[MAX_ROOM], int &roomNum, string &result);

/**
 * Read bookings.txt file.When the file was read successfully,store the booking data into an array and get the number of booking data.
 *
 * @param[out] bookings An array of Booking to store the booking data read from the file.
 * @param[out] bkgNum The number of the booking information.It will be assigned the value after file reading.
 * @param[out] result Return the program terminating information when file reading had problems.
 * @return true if the file is read successfully,false if there's a problem in opening the file.
 */
bool readFile(Booking(&bookings)[MAX_BOOKING], int &bkgNum, string &result);

/**
 * Print the room information line by line when their names weren't found in the booking list.
 * If all rooms can be found in the booking list,nothing will be printed.

 * @param[in] rooms An array of Room.
 * @param[in] bookings An array of Booking.
 * @param[in] roomNum The number of the rooms.
 * @param[in] bkgNum The number of the bookings.
 */
void printRoomNotBooked(const Room(&rooms)[MAX_ROOM], const Booking(&bookings)[MAX_BOOKING], int roomNum, int bkgNum);

/**
 * Search booking array with room name "---" and print the booking info when their room names are "---"
 * If all bookings have room requests,nothing will be printed.
 *
 * @param[in] bookings An array of Booking.
 * @param[in] bkgNum The number of the bookings.
 */
void printBookingWithoutRoom(const Booking(&bookings)[MAX_BOOKING], int bkgNum);

/**
 * Print out the booking info line by line when their purposes differ from corresponding room info.
 * If all bookings have correct purposes,nothing will be printed.
 *
 * @param[in] rooms An array of Room.
 * @param[in] bookings An array of Booking.
 * @param[in] roomNum The number of the rooms.
 * @param[in] bkgNum The number of the bookings.
 */
void printBookingWithWrongPurpose(const Room(&rooms)[MAX_ROOM], const Booking(&bookings)[MAX_BOOKING], int roomNum, int bkgNum);

/**
 * Print out the booking info line by line when their time requests exceed corresponding rooms' time limit.
 * If there's no room's time request over the limit,nothing will be printed.
 *
 * @param[in] rooms An array of Room.
 * @param[in] bookings An array of Booking.
 * @param[in] roomNum The number of the rooms.
 * @param[in] bkgNum The number of the bookings.
 */
void printBookingWithInvalidTimeRequest(const Room(&rooms)[MAX_ROOM], const Booking(&bookings)[MAX_BOOKING], int roomNum, int bkgNum);

/**
 * Run read file and data validation functions then do consistency rule process.Print the result with formatting output.
 * If any read file process failed, exit immediately.
 *
 * @param[out] rooms The room array to be handled.It will be modified after file reading.
 * @param[out] bookings The booking array to be handled.It will be modified after file reading.
 * @param[out] roomNum  Number of the rooms.It will be modified after file reading.
 * @param[out] bkgNum Number of the bookings.It will be modified after file reading.
 * @return false when reading file occurs problems otherwise return true.
 */
bool run(Room(&rooms)[MAX_ROOM], Booking(&bookings)[MAX_BOOKING], int &roomNum, int &bkgNum);

/**
 * The program entrance.
 */
int main()
{
	Room rooms[MAX_ROOM];
	Booking bookings[MAX_BOOKING];
	int roomNum = 0; //room number will be read from file
	int bkgNum = 0; //booking number will be read from file
	if (!run(rooms, bookings, roomNum, bkgNum)) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

bool readFile(Room(&rooms)[MAX_ROOM], int &roomNum, string &result) {
	ifstream file("rooms.txt");
	if (!file) {
		result = "Error: file rooms.txt is missing. Program terminates.";
		return false;
	}
	file >> roomNum;
	if (roomNum == 0) {
		result = "The number of room information is 0. Program terminates.";
		file.close();
		return false;
	}
	for (int i = 0; i != roomNum; ++i) {
		file >> rooms[i].mRoomName >> rooms[i].mPurpose >> rooms[i].mTimeLimit;
	}
	file.close();
	result = "success";
	return true;
}

bool readFile(Booking(&bookings)[MAX_BOOKING], int &bkgNum, string &result) {
	ifstream file("bookings.txt");
	if (!file) {
		result = "Error: file bookings.txt is missing. Program terminates.";
		return false;
	}
	file >> bkgNum;
	if (bkgNum == 0) {
		result = "The number of booking information is 0. Program terminates.";
		file.close();
		return false;
	}
	for (int i = 0; i != bkgNum; ++i) {
		file >> bookings[i].mStaffName >> bookings[i].mPurpose >> bookings[i].mRoomName >> bookings[i].mTimeRequest;
	}
	file.close();
	result = "success";
	return true;
}

void printRoomNotBooked(const Room(&rooms)[MAX_ROOM], const Booking(&bookings)[MAX_BOOKING], int roomNum, int bkgNum) {
	for (int i = 0; i != roomNum; ++i) {
		int bkgFinder; //Subscript that tracks the booking info if its room name matches the searching.
		for (bkgFinder = 0; bkgFinder != bkgNum; ++bkgFinder) {
			if (rooms[i].mRoomName == bookings[bkgFinder].mRoomName) {
				break;
			}
		}
		//When the subscript reach the end of booking array,the room name can't be found in that array.
		if (bkgFinder == bkgNum) {
			cout << "Room: " << rooms[i].mRoomName << " suitable for " << rooms[i].mPurpose
				<< " purpose allows maximum " << rooms[i].mTimeLimit << " minutes" << endl;
		}
	}
}

void printBookingWithoutRoom(const Booking(&bookings)[MAX_BOOKING], int bkgNum) {
	for (int i = 0; i != bkgNum; ++i) {
		if (bookings[i].mRoomName == "---") {
			cout << "Booking: by " << bookings[i].mStaffName << " for " << bookings[i].mPurpose
				<< " purpose at room --- for " << bookings[i].mTimeRequest << " minutes" << endl;
		}
	}
}

void printBookingWithWrongPurpose(const Room(&rooms)[MAX_ROOM], const Booking(&bookings)[MAX_BOOKING], int roomNum, int bkgNum) {
	for (int i = 0; i != bkgNum; ++i) {
		for (int j = 0; j != roomNum; ++j) {
			if (bookings[i].mRoomName == rooms[j].mRoomName && bookings[i].mPurpose != rooms[j].mPurpose) {
				cout << "Booking: by " << bookings[i].mStaffName << " for " << bookings[i].mPurpose << " purpose at room "
					<< bookings[i].mRoomName << " for " << bookings[i].mTimeRequest << " minutes" << endl;
			}
		}
	}
}

void printBookingWithInvalidTimeRequest(const Room(&rooms)[MAX_ROOM], const Booking(&bookings)[MAX_BOOKING], int roomNum, int bkgNum) {
	for (int i = 0; i != bkgNum; ++i) {
		for (int j = 0; j != roomNum; ++j) {
			if (bookings[i].mRoomName == rooms[j].mRoomName && bookings[i].mTimeRequest > rooms[j].mTimeLimit) {
				cout << "Booking: by " << bookings[i].mStaffName << " for " << bookings[i].mPurpose << " purpose at room "
					<< bookings[i].mRoomName << " for " << bookings[i].mTimeRequest << " minutes" << endl;
			}
		}
	}
}

bool run(Room(&rooms)[MAX_ROOM], Booking(&bookings)[MAX_BOOKING], int &roomNum, int &bkgNum) {
	string header = "**************************************************\n* 159.234 Assignment 1 Part 1\n"
		"* Name: Qian Wan\n* ID: 17326163\n**************************************************\n";
	string readResult;
	if (!readFile(rooms, roomNum, readResult)) {
		header += readResult;
		cout << header << endl;
		return false;
	}
	if (!readFile(bookings, bkgNum, readResult)) {
		header += readResult;
		cout << header << endl;
		return false;
	}

	cout << header << "The following rooms have not been booked by anyone:" << endl;
	printRoomNotBooked(rooms, bookings, roomNum, bkgNum); cout << endl;
	cout << "The following booking requests do not specify a room:" << endl;
	printBookingWithoutRoom(bookings, bkgNum); cout << endl;
	cout << "The following booking requests have the wrong purposes:" << endl;
	printBookingWithWrongPurpose(rooms, bookings, roomNum, bkgNum); cout << endl;
	cout << "The following booking requests are over the time limit:" << endl;
	printBookingWithInvalidTimeRequest(rooms, bookings, roomNum, bkgNum); cout << endl;
	return true;
}
