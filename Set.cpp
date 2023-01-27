//
// Created by algo on 07/04/2021.
//

#include "include/Set.h"
/**
 * Constructor for the Data Struct, purpose to to create Data Object faster.
 * @param key the key value
 * @param data data value(represents data a structure of multiple values)
 */
Data::Data(const string &key, double data) : data(data), next(nullptr) {
    this->key = key;
}

/**
 * Private function handles the repetition of code
 * @param key that is Set somewhere
 * @return the Object that contains the value of the key, if that object exists in the Set.
 */
Data* Set::searchKeyComponent(const string& key) const{
    for (Data* thisSetComponent = this->head; thisSetComponent != nullptr; thisSetComponent = thisSetComponent->next)
        if (thisSetComponent->key == key)
            return thisSetComponent;
    return nullptr;
}

/**
 * Builds Set, Which holds Components in Nodes
 */
Set::Set() : head(nullptr){}

/**
 * Goes through the whole Set even if it's empty will still check.
 */
Set::~Set() {
    for (Data* setComponent; head != nullptr;){
        setComponent = head->next; // Holds on the next Node to delete it next.
        delete head;
        head = setComponent;
    }
}
/**
 * @param toCopySet getting copied to create Another Set that is identical.
 */
Set::Set(const Set &toCopySet) {
    Data* this_set_node_ptr;
    this_set_node_ptr = this->head = new Data(toCopySet.head->key, toCopySet.head->data);
    for (Data* otherSetComponent = toCopySet.head->next;
            otherSetComponent != nullptr;
            otherSetComponent = otherSetComponent->next)
        this_set_node_ptr = this_set_node_ptr->next = new Data(otherSetComponent->key, otherSetComponent->data);
}

/**
 * @param key string unique to object
 * @param data related to the Key
 * @return true if the object with the same key exists, false if it doesn't exist
 */
bool Set::isInSet(const string &key, double &data) const{
    Data * found_node = searchKeyComponent(key);
    if (found_node){
        found_node->data = data;
        return true;
    }
    return false;
}

/**
 * Creates new Object if the key doesn't exist in the Set.
 * @param key String unique to the Set
 * @param data related to the key of the Object
 * @return 1 if the new Object been created and added to the Set,
 * 0 if the key already exists and only modifies the data of that key.
 */
int Set::add(const string &key, double data) {
    Data *newComponent = new Data(key, data);
    if (isInSet(key, data))
        return 0;
    newComponent->next = this->head;
    this->head = newComponent;
    return 1;
}

/**
 * @param key searches through the Set if Object with the same Key exists.
 * @return 1 if the Object exists and successfully been removed, 0 if there was no Object with the same key.
 */
int Set::remove(const string &key) {
    Data * ptr_of_deleted_object = nullptr; // A Node that hold next ptr to the Node that we are going to delete.
    Data * deleted_object = this->head; // A Node that we going to remove from Set(delete it)
    //loop that goes through all the Nodes
    for (;deleted_object != nullptr; ptr_of_deleted_object = deleted_object, deleted_object = deleted_object->next)
    {
        if (deleted_object->key == key)
        {
            if (ptr_of_deleted_object != nullptr)
                ptr_of_deleted_object->next = deleted_object->next;
            else
                this->head = deleted_object->next;
            delete deleted_object;
            return 1;
        }
    }
    return 0;
}

/**
 * @return sum of all data values of the Set.
 */
double Set::sumSet() const{
    double sum_of_all_data = 0;
    for (Data* thisSetComponent = this->head; thisSetComponent != nullptr; thisSetComponent = thisSetComponent->next)
        sum_of_all_data += thisSetComponent->data;
    return sum_of_all_data;
}

/**
 * @param key the string we sum for Hash
 * @return The Hash code of the String Key
 */
int Set::myHashFunction(const string &key) {
    int hash = 0;
    for (char stringIndex : key)
        hash += stringIndex;
    return hash;
}

/**
 * @return sums all the Hash code of the Set together.
 */
int Set::totWeight() const{
    int hashSum = 0;
    for (Data* thisSetComponent = this->head; thisSetComponent != nullptr; thisSetComponent = thisSetComponent->next)
        hashSum += myHashFunction(thisSetComponent->key);
    return hashSum;
}

/**
 * Method only sorts the values of the object and NOT the objects themselves.
 * It prints the Items inside the set each and if it's empty it will print "EMPTY".
 */
void Set::printSet() const {
    if (this->head != nullptr) {
        Set sortedSet(*this);
        //Use of bubble sort
        //i and j are both Data pointer of the sortedSet
        for (Data *i = sortedSet.head; i != nullptr; i = i->next) {
            for (Data *j = i; j != nullptr; j = j->next) {
                if (myHashFunction(i->key) > myHashFunction(j->key)) {
                    Data swappingComponentHelper(i->key, i->data);
                    i->key = j->key;
                    i->data = j->data;
                    j->key = swappingComponentHelper.key;
                    j->data = swappingComponentHelper.data;
                }
            }
            cout << i->key << "," << i->data << endl;
        }
    } else {
        cout << "EMPTY" << endl;
    }
}

/**
 * @param otherSet to compare against this Set
 * @return true if this Set is smaller than the other Set, false otherwise.
 */
bool Set::operator<(const Set &otherSet) const {
    return this->totWeight() < otherSet.totWeight();
}

/**
 * @param otherSet to compare against this Set
 * @return true if this Set is bigger than the other Set, false otherwise.
 */
bool Set::operator>(const Set &otherSet) const {
    return this->totWeight() > otherSet.totWeight();
}

/**
 * @param otherSet to compare against this Set
 * @return true if this Set is equal than the other Set, false otherwise.
 */
bool Set::operator==(const Set &otherSet) const {
    return this->totWeight() == otherSet.totWeight();
}

/**
 *
 * @param otherSet to subtract components that exists in
 * @return A new Set that contains the components that been removed that exists in the otherSet.
 */
Set Set::operator-(const Set &otherSet) const {
    Set resultSet = *this;
    for (Data *otherSetComponent = otherSet.head; otherSetComponent != nullptr; otherSetComponent = otherSetComponent->next)
        resultSet.remove(otherSetComponent->key);
    return resultSet;
}

/**
 * Does the Union operation "This OR that together"
 * @param otherSet Set that we add the components that don't exists in THIS Set
 * @return NEW Set that contains all the components that both THIS and OTHER Sets united but no duplicates.
 */
Set Set::operator|(const Set &otherSet) const {
    Set resultSet = *this;
    for (Data *otherSetComponent = otherSet.head; otherSetComponent != nullptr; otherSetComponent = otherSetComponent->next)
        resultSet.add(otherSetComponent->key, otherSetComponent->data);
    return resultSet;
}

/**
 * Does the Intersection operation "This AND that"
 * @param otherSet's components that must be in THIS set as well
 * @return NEW Set that only contains the components that both THIS and OTHER Sets have.
 */
Set Set::operator&(const Set &otherSet) const {
    Set resultSet(*this);
    for (Data *thisSetComponent = resultSet.head; thisSetComponent != nullptr; thisSetComponent = thisSetComponent->next)
        if (!otherSet.searchKeyComponent(thisSetComponent->key))
            resultSet.remove(thisSetComponent->key);
    return resultSet;
}

/**
 * @param toCopySet The Set that we Assign to THIS Set
 * @return The newly assigned Set that been copied.
 */
Set& Set::operator=(const Set &toCopySet) {
    this->~Set();
    Set *newAssignedSet = new Set(toCopySet);
    this->head = newAssignedSet->head;
    return *this;
}


