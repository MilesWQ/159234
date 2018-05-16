// ----Do not send this file for marking!!!----
// ----Do not make any change to this file!!!----
// File name: a2p1_classes.h
// Read the assignment 2 part 1 specification
// and make sure you understand how to use this file.

// Ask questions in lectures/tutorials if you
// have problems with using this file.

#ifndef A2P1_CLASSES_H
#define A2P1_CLASSES_H

#include <iostream>

using namespace std;

const int OVERDUE_FEE_PER_DAY = 5; ///< Fee charged each day it is overdue
const int LOST_ITEM_FEE = 200;     ///< Fee charged for lost item
const int SPECIAL_SURCHARGE = 30;  ///< A surcharge for special books on top of any fee owed

/**
 * Possible values of Status
 */
enum class Status {
    AVAILABLE,
    ON_LOAN,
    PROCESSED,
    MISSING,
    OVERDUE,
};

/**
* An abstract class representing a library item
*/
class Item {
public:

    /**
    * Constructor - to be called by derived classes
    * @param callNumber the call number
    * @param title the title
    * @param status lending status
    * @param daysOverDue number of days overdue
    */
    Item(const string &callNumber, const string &title, Status status,
        int daysOverDue);

    /**
    * Return the lending status
    * @return the lending status
    */
    Status getStatus() const {
        return status;
    }

    /**
    * Return the call number
    * @return the call number
    */
    const string &getCallNumber() const {
        return callNumber;
    }

    /**
    * Return the title
    * @return the title
    */
    const string &getTitle() const {
        return title;
    }

    /**
    * Return a string in the appropriate format containing
    * all information about the object
    * @return the string representation of this object
    */
    virtual string print() const = 0;

    /**
    * Return the fee the borrower currently owes
    *
    * @return the accummulated overdue fee if item is missing
    *         the lost fee if item is lost
    *         0 otherwise
    */
    virtual int getFees() const;
private:
    Status status;                     ///< status of the item
    string title;                      ///< title of the item
    int daysOverDue;                   ///< number of days overdue
    string callNumber;                 ///< call number
};

/**
* Print out your names and IDs
*/
void printStudentInfo();

#endif //A2P1_CLASSES_H