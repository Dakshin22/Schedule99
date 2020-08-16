# Overview
Scheduling application with functionality Add, Delete, Merge, and Replace Events using a Doubly Linked List (DLL).

## A Schedule Template
![](img/ListExample.png)
Above is what the general layout of a schedule looks like. Each node of the DLL represents 1 event and has a name and duration. The next node represents the event after the current node. For this project, the duration has arbriatrary units of time and the entire schedule has a duration limit of 100.

# How to use

Upon running the program, a default schedule will be stored with a single node with name "FREE" and duration 100 (shown below). Whenever the user adds events, the parts of the schedule that are not taken up by events will be replaced by nodes with name FREE and with duration of the unoccupied time.

![](img/free.png)

## Basics

Users can add an event by specifiying a name (EVENT), start time (START_TIME) and end time (END_TIME) and by typing the following command:

add EVENT from START_TIME to END_TIME

(e.g. add WORK from 2 to 30)

Users can also cancel an event by specifying a time (TIME) and by typing the following command:

cancel TIME

(e.g. cancel 2)

After each modification the new schedule will print.

## Merging an Event
Any time a new event is added of the same name as an adjacent event, those two nodes will merge into one node. If the user's current schedule has two of the same event on either side of a FREE block, and adds an event of the same name in place of that FREE block, all three nodes will merge into one node.

## Replacing an Event
The user can replace an event by cancelling the event and adding another event at the same time.

# Challenges

There were many cases that I did not anticipate when starting this project. For example, adding an event in the beggining, middle, and end of a free period all require different ways of rearrange the DLL in terms of the number of and locations of new nodes. Also, adding an event of the same name in the beginning, end or in between two events all require rearranging the DLL differently.
