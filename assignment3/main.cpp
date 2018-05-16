#include "a2p1_classes.cpp"

/**
* Total number of items
*/
const int NUM_ITEMS = 12;
int main() {
    printStudentInfo();
    Item * items[NUM_ITEMS] = {
        new Book("S529.030MAR", "The adventures of Tom Sawyer", "Mark Twain", 500,
        Status::MISSING, 0),
        new Book("S759.010BEN", "Bullies", "Ben Shapiro", 336, Status::OVERDUE, 2),
        new Book("123.010MIL", "Dangrous", "Milo Yiannopolous", 288, Status::MISSING, 10),
        new Book("S205.682CON", "Sherlock Holmes", "Conan Doyle", 68, Status::ON_LOAN, 3),
        new Journal("123.456SCI", "Scientific American", "XXI", 4, Status::MISSING, 10),
        new Journal("382.150ORN", "Ornothologist", "XIV", 1, Status::AVAILABLE, 0),
        new Journal("842.003NAT", "National Geographic", "XXIX", 2, Status::OVERDUE, 8),
        new Journal("153.227NAT", "Computational Biology", "VII", 4, Status::AVAILABLE, 8),
        new DVD("235.707HAY", "Spirited Away", "Hayao Miyazaki", Status::AVAILABLE, 0),
        new DVD("987.654SHI", "Your Name", "Shinkai Mikoto", Status::OVERDUE, 6),
        new DVD("258.147SHO", "Koe No Katachi", "Shochiku", Status::ON_LOAN, 0),
        new DVD("S963.159TIM", "Big Fish", "Tim Burton", Status::OVERDUE, 7)
    };
    int totalFees = 0;
    for (int i = 0; i < NUM_ITEMS; i++) {
        Item * item = items[i];
        cout << item->print() << endl;
        totalFees += item->getFees();
    }
    cout << "Total fees: " << totalFees << endl;
}