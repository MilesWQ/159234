/**
* @file a2p1_classes.cpp
*
* @brief 159234 assignment 2 part 1
*		 Implement a book class, a journal class and a DVD class to compute the related surcharge and print their information
*
* @details 1. All of three classes are inherited from Item and override getFees(), print() methods to support polymorphism.
*          2. In general, the fees of three types of items are subject to over due days or whether they are lost.
*          3. When books are overdue or lost, borrowers of these books will be charged an extra fee if the books are special.
*          4. There are two auxiliary functions "intToString" and "statusToString" to perform conversion operations for strings.
*          5. Other details please refer to assignment specifications.
*
* @author Wan Qian ID:17326163
*
* @version 1.0
*/

#include "a2p1_classes.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 * Convert an integer to a string
 * @param[in] num an integer to be converted
 * @return the string type of that integer.
 */
string intToString(int num);

/**
 * Convert an enumeration Status type of an item to a string
 * @param[in] status a value of enum Status
 * @return the string type of that Status type.
 */
string statusToString(Status status);

/**
 * Default constructor of base class Item
 * @param[in] callnumber_ the call number
 * @param[in] title_ the title
 * @param[in] status_ lending status
 * @param[in] daysoverdue_ number of days overdue
 */
Item::Item(const string &callnumber_ = "", const string &title_ = "", Status status_ = Status::AVAILABLE,
    int daysoverdue_ = 0) : callNumber(callnumber_), title(title_), status(status_), daysOverDue(daysoverdue_) {}

/**
* Return the fee the borrower currently owes
* @return the accumulated overdue fee or the lost fee if the item is lost
*         0 otherwise
*/
int Item::getFees() const {
    int result = 0;
    if (getStatus() == Status::MISSING) {
        result = LOST_ITEM_FEE;
    }
    if (getStatus() == Status::OVERDUE) {
        result = daysOverDue * OVERDUE_FEE_PER_DAY;
    }
    return result;
}

/**
 * Print the student information
 */
void printStudentInfo() {
    cout << "**************************************************\n* 159.234 Assignment 2 Part 1\n"
        "* Name: Wan Qian\n* ID: 17326163\n**************************************************\n" << endl;
}

/**
 * represents information of a book
 */
class Book :public Item {
public:
    /**
     * Default constructor for book instances
     * param[in] callnumber_ call number of the book
     * param[in] title_ title of the book
     * param[in] author_ author name of the book
     * param[in] pages_  pages number of the book
     * param[in] status_ status of the book
     * param[in] daysoverdue_ overdue days of the book
     *
     */
    Book(const string &callnumber_ = "", const string &title_ = "", const string& author_ = "", int pages_ = 0, Status status_ = Status::AVAILABLE,
        int daysoverdue_ = 0);

    /**
     * Destructor
     */
    virtual ~Book() {};

    /**
     * Get author of the book
     * @return the author name of the book
     */
    string getAuthor() const {
        return mAuthor;
    }

    /**
     * Set the author of the book
     * @param[in] author the author name of the book
     */
    void setAuthor(const string &author) {
        mAuthor = author;
    }

    /**
     * Get the number of pages.
     * @return the number of page of the book
     */
    int getPages() const {
        return mNumPages;
    }

    /**
     * Set the number of pages.
     * @param[in] the number of the pages of the book.
     */
    void setPages(int pages) {
        mNumPages = pages;
    }

    /**
     * Check whether the book is a special book.
     * @return true if the book is special otherwise false
     */
    bool isSpecial() const;

    /**
     * Return the fee the borrower currently owes.
     * @return the accumulated overdue fee or the lost fee if the book is lost
     *         If there's a fee occur and it's a special book, an extra surcharge will be added.
     *         0 otherwise
     */
    int getFees() const;

    /**
     * return the information of the book.
     * @return the formatting information of the book.
     */
    string print() const;
private:
    string mAuthor; ///< author name of the book
    int mNumPages;  ///< number of pages
};

Book::Book(const string &callnumber_, const string &title_, const string& author_, int pages_, Status status_, int daysoverdue_)
    :Item(callnumber_, title_, status_, daysoverdue_), mAuthor(author_), mNumPages(pages_) {}

bool Book::isSpecial() const {
    string callNum = getCallNumber();
    return callNum[0] == 'S';
}

int Book::getFees() const {
    int result = 0;
    result = Item::getFees();
    if (result != 0 && isSpecial()) {
        result += SPECIAL_SURCHARGE;
    }
    return result;
}

string Book::print() const {
    string result = "Book #" + getCallNumber() + ", title: \"" + getTitle() + "\" by " + getAuthor() + ", pages: "
        + intToString(getPages()) + ", status: " + statusToString(getStatus()) + ", overdue fee: " + intToString(getFees());
    return result;
}

/**
 * represents information of a journal.
 */
class Journal :public Item {
public:
    /**
     * Default constructor for journal instances
     * param[in] callnumber_ call number of the journal
     * param[in] title_ title of the journal
     * param[in] volume_ volume of the journal
     * param[in] frequency_  times of annual publication of the journal
     * param[in] status_ status of the journal
     * param[in] daysoverdue_ overdue days of the journal
     */
    Journal(const string &callnumber_ = "", const string &title_ = "", const string& volume_ = "", int frequency_ = 0, Status status_ = Status::AVAILABLE,
        int daysoverdue_ = 0);

    /**
     * Destructor
     */
    virtual ~Journal() {}

    /**
     * Get the volume of the journal.
     * @return the volume of the journal.
     */
    string getVolume() const {
        return mVolume;
    }

    /**
     * Set the volume of the journal.
     * @param[in] volume the volume of the journal
     */
    void setVolume(const string& volume) {
        mVolume = volume;
    }

    /**
     * Get the number of times of annual publication of the journal
     * @return the frequency of the publication each year
     */
    int getFrequency() const {
        return mFrequency;
    }

    /**
     * Set the number of times of annual publication of the journal
     * @param[in] frequency the annual publication frequency of the journal
     */
    void setFrequency(int frequency) {
        mFrequency = frequency;
    }

    /**
    * Return the fee the borrower currently owes
    * @return the accumulated overdue fee or the lost fee if the journal is lost
    *         0 otherwise
    */
    int getFees() const;

    /**
    * return the information of the journal.
    * @return the formatting information of the journal.
    */
    string print() const;
private:
    string mVolume; ///< the volume of the journal
    int mFrequency; ///< the frequency of annual publication 
};

Journal::Journal(const string &callnumber_, const string &title_, const string& volume_, int frequency_, Status status_, int daysoverdue_)
    :Item(callnumber_, title_, status_, daysoverdue_), mVolume(volume_), mFrequency(frequency_) {}

int Journal::getFees() const {
    return Item::getFees();
}

string Journal::print() const {
    string result = "Journal #" + getCallNumber() + ", title: \"" + getTitle() + "\" volume " + getVolume() + ", frequency: "
        + intToString(getFrequency()) + ", status: " + statusToString(getStatus()) + ", overdue fee: " + intToString(getFees());
    return result;
}

/**
 * represents information of a DVD
 */
class DVD :public Item {
public:
    /**
     * Default constructor for DVD instances
     * param[in] callnumber_ call number of the DVD
     * param[in] title_ title of the DVD
     * param[in] producer_ producer of the DVD
     * param[in] status_ status of the DVD
     * param[in] daysoverdue_ overdue days of the DVD
     */
    DVD(const string &callnumber_ = "", const string &title_ = "", const string& producer_ = "", Status status_ = Status::AVAILABLE,
        int daysoverdue_ = 0);

    /**
     * Destructor
     */
    virtual ~DVD() {}

    /**
     * Get the producer of the DVD
     * @return the name of the producer.
     */
    string getProducer() const {
        return mProducer;
    }

    /**
     * Set the producer of the DVD
     * @param[in] producer the name of the producer of the DVD
     */
    void setProducer(const string& producer) {
        mProducer = producer;
    }

    /**
    * Return the fee the borrower currently owes
    * @return the accumulated overdue fee or the lost fee if the journal is lost
    *         0 otherwise
    */
    int getFees() const;

    /**
    * return the information of the DVD.
    * @return the formatting information of the DVD.
    */
    string print() const;
private:
    string mProducer;   ///<the producer name
};

DVD::DVD(const string &callnumber_, const string &title_, const string& producer_, Status status_, int daysoverdue_)
    :Item(callnumber_, title_, status_, daysoverdue_), mProducer(producer_) {}

int DVD::getFees() const {
    return Item::getFees();
}

string DVD::print() const {
    string result = "DVD #" + getCallNumber() + ", title: \"" + getTitle() + "\" produced by " + getProducer()
        + ", status: " + statusToString(getStatus()) + ", overdue fee: " + intToString(getFees());
    return result;
}

string intToString(int num) {
    stringstream converter;
    converter << num;
    return converter.str();
}

string statusToString(Status status) {
    string result;
    switch (status)
    {
    case Status::AVAILABLE:
        result = "Available";
        break;
    case Status::ON_LOAN:
        result = "On loan";
        break;
    case Status::PROCESSED:
        result = "Processed";
        break;
    case Status::MISSING:
        result = "Missing";
        break;
    case Status::OVERDUE:
        result = "Overdue";
        break;
    default:
        result = "undefined status";
    }
    return result;
}
