#include "scheduler.h"
#include <string>
#include <iostream>
using namespace std;
//Dakshin Rathan
// this is a source file for a scheduling application that makes use of a doubly linked list


bool Scheduler::isAvailable(unsigned start, unsigned duration) const
{
    if (start < 0 || start > 99 || duration < 0)
    {
        return false;
    }
    ScheduleNode *temp = this->head;

    unsigned tempStart = 0;
    unsigned tempEnd = tempStart + temp->length;

    while (tempEnd <= start)
    {
        tempStart = tempStart + temp->length;
        temp = temp->next;
        tempEnd += temp->length;
    }

    if (temp->name == "FREE" && tempEnd >= start + duration)
    {

        return true;
    }
    else
    {
        return false;
    }
}

void Scheduler::schedule(const string &name, unsigned start, unsigned duration)
{
    //invalid check
    if (duration == 0 || duration > 100 || start >= 100)
    {
        //cout << "\ninvalid" << endl;
        return;
    }
    ScheduleNode *mergePtr = this->head;
    ScheduleNode *temp = this->head;
    ScheduleNode *node = new ScheduleNode(name, duration);

    unsigned location = 0;
    unsigned tempStart = location;
    unsigned tempEnd = tempStart + temp->length;

    bool added = false;
    while (!added)
    {
        mergePtr = this->head;
        if (temp->name == "FREE" && start >= tempStart && start + duration <= tempEnd)
        {

            //case 0: replace free period
            if (tempStart == start && temp->length == duration)
            {

                temp->name = node->name;
                if (temp->next == nullptr || temp->prev == nullptr)
                {
                }

                added = true;
            }
            //case 1: Add event at beginning of schedule, (change head pointer)
            else if (start == 0)
            {
                //cout << "\nhere1" << endl;
                node->next = temp;
                temp->prev = node;
                this->head = node;
                temp->length -= duration;

                added = true;
            }
            //case 2a: Add event at beginnign of free preiod
            else if (start == tempStart && start + duration < tempEnd)
            {
                node->next = temp;
                node->prev = temp->prev;
                temp->prev->next = node;
                temp->prev = node;
                temp->length -= duration;
                added = true;
            }

            //case 2b: Add event at end of free period
            else if (start > tempStart && start + duration == tempEnd)
            {
                //cout << "\nhere2b" << endl;

                if (temp->next == nullptr)
                {
                    temp->next = node;
                    node->prev = temp;
                    temp->length -= duration;
                    added = true;
                }
                else if (temp->next != nullptr)
                {
                    node->next = temp->next;
                    node->prev = temp;
                    temp->next->prev = node;
                    temp->next = node;
                    temp->length -= duration;
                    added = true;
                }
            }

            //case 3: add event in the middle of free period
            else if (start > tempStart && start + duration < tempEnd)
            {
                //cout << "\nhere3" << endl;
                int origLength = temp->length;
                ScheduleNode *freeNode = new ScheduleNode("FREE", 1);
                if (temp->next != nullptr)
                {
                    temp->next->prev = freeNode;
                    freeNode->next = temp->next;
                }

                else
                {
                    freeNode->next = nullptr;
                }

                //adjusting length of Free node before desired event
                temp->length = start - tempStart;

                node->prev = temp;
                temp->next = node;
                freeNode->prev = node;
                node->next = freeNode;

                freeNode->length = origLength - (temp->length) - (node->length);

                added = true;
            }

            //check
            //case 5: Filling a free spot in between two events of the same name.
            else if (temp->prev->name == temp->next->name && temp->next->name == node->name && start == tempStart && start + duration == tempEnd)
            {
                //cout << "\nhere5" << endl;
                node->prev = temp->prev;
                node->next = temp->next;
                temp->prev->next = node;
                temp->next->prev = node;
                delete temp;
                node->merge(node->next);
                node->prev->merge(node);

                added = true;
            }

            //case 4: Add event that has the same name before another event (merge)
            else if (temp->next->name == node->name && start + duration == tempEnd)
            {
                //cout << "\nhere4" << endl;

                node->next = temp->next;
                node->prev = temp;
                temp->next = node;
                node->next->prev = node;
                node->merge(node->next);

                added = true;
            }
            //case 6: Add event that has the same name after another event (merge)
            else if (temp->prev->name == node->name && start == tempStart)
            {
                //cout << "\nhere6" << endl;
                node->prev = temp->prev;
                node->next = temp;
                temp->prev->next = node;
                temp->prev = node;
                temp->prev->prev->merge(node);

                added = true;
            }
        }
        if (!added)
        {
            tempStart = tempStart + temp->length;
            temp = temp->next;
            tempEnd += temp->length;
            location += temp->length;
        }
    }
    while (mergePtr->next != nullptr)
    {

        if (mergePtr->length == 100 || mergePtr->next == nullptr)
        {
            // cout << "broke1";
            break;
        }
        while (mergePtr->name == mergePtr->next->name)
        {
            mergePtr->merge(mergePtr->next);
            //cout << "name: " << mergePtr->name << ", length: " << mergePtr->length << endl;
            if (mergePtr->next == nullptr)
            {
                break;
            }
        }

        if (mergePtr->next == nullptr)
        {
            break;
        }

        mergePtr = mergePtr->next;
    }
}

void Scheduler::free(unsigned start)
{
    ScheduleNode *temp = this->head;
    ScheduleNode *mergePtr = this->head;
    unsigned location = 0;
    while (location < start)
    {

        location += temp->length;
        temp = temp->next;
    }

    if (location != start)
    {
        cout << "location != start" << endl;
        return;
    }

    temp->name = FREE;

    while (mergePtr->next != nullptr)
    {

        if (mergePtr->length == 100 || mergePtr->next == nullptr)
        {
            //  cout << "broke";
            break;
        }
        while (mergePtr->name == mergePtr->next->name)
        {
            mergePtr->merge(mergePtr->next);
            //cout << "name: " << mergePtr->name << ", length: " << mergePtr->length << endl;
            if (mergePtr->next == nullptr)
            {
                break;
            }
        }

        if (mergePtr->next == nullptr)
        {
            break;
        }

        mergePtr = mergePtr->next;
    }
}

void Scheduler::printSchedule() const
{
    ScheduleNode *temp = this->head;

    unsigned time = 0;
    while (temp != NULL)
    {
        cout << time << ": " << temp->name << " (" << temp->length << ")" << endl;
        time += temp->length;
        temp = temp->next;
    }
}

//optional
void ScheduleNode::merge(ScheduleNode *other)
{
    //cout << "\nheremerge" << endl;
    if (other->next != nullptr)
    {
        this->next = other->next;
        other->next->prev = other->prev;
    }
    else
    {
        this->next = nullptr;
    }

    this->length = this->length + other->length;

    delete other;
}

Scheduler:: ~Scheduler()
{
    
    while(head->next != nullptr)
    {
        head = head->next;
        delete head->prev;
    }
    delete head;
}