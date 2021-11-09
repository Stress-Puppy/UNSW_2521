
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "FlightDb.h"
#include "AVLTree.h"

struct flightDb {
	// TODO: Add to this struct
	Tree byDepartureAirportDay;
	Tree byFlightNumber;
    Tree betweenTimes;
};

////////////////////////////////////////////////////////////////////////
// Comparison functions

/**
 * Compares two records by FlightNumber only and returns:
 * - A negative number if the first record is less than the second
 * - Zero if the records are equal
 * - A positive number if the first record is greater than the second

 * according to flight number, departure airport, day, hour  and  minute.
 */
int compareByFlightNumber(Record r1, Record r2) {

	int compare = strcmp(RecordGetFlightNumber(r1), RecordGetFlightNumber(r2));
    if (compare == 0) {
        compare = RecordGetDepartureDay(r1) - RecordGetDepartureDay(r2);
    }
    if (compare == 0) {
        compare = RecordGetDepartureHour(r1) - RecordGetDepartureHour(r2);
    }
    if (compare == 0) {
        compare = RecordGetDepartureMinute(r1) - RecordGetDepartureMinute(r2);
    }

    return compare;
}

/**
 * Compares two records by Airport first, day second, and then by
 * FlightNumber if the Airport and the day are equal, and returns:
 * - A negative number if the first record is less than the second
 * - Zero if the records are equal
 * - A positive number if the first record is greater than the second

 * according to the given departure airport and day of week (0 to 6), in increasing order  of
 * (hour, min, flight number)

 */

int compareByDepartureAirportDay(Record r1, Record r2) {
    
	int compare = strcmp(RecordGetDepartureAirport(r1), RecordGetDepartureAirport(r2));

    if (compare == 0) {
        compare = RecordGetDepartureDay(r1) - RecordGetDepartureDay(r2);
    }
    if (compare == 0) {
        compare = RecordGetDepartureHour(r1) - RecordGetDepartureHour(r2);
    }
    if (compare == 0) {
        compare = RecordGetDepartureMinute(r1) - RecordGetDepartureMinute(r2);
    }
    if (compare == 0) {
        compare = compareByFlightNumber(r1, r2);
    }

    return compare;
}

/**
 * Compares two records by time first, and then by
 * FlightNumber if the time are equal, and returns:
 * - A negative number if the first record is less than the second
 * - Zero if the records are equal
 * - A positive number if the first record is greater than the second

 * between  (day1, hour1, min1)  and (day2, hour2, min2), in increasing  order  of
 * (day, hour, min, flight number).

 */

int compareBetweenTimes(Record r1, Record r2) {
    
	int compare = RecordGetDepartureDay(r1) - RecordGetDepartureDay(r2);

    if (compare == 0) {
        compare = RecordGetDepartureHour(r1) - RecordGetDepartureHour(r2);
    }
    if (compare == 0) {
        compare = RecordGetDepartureMinute(r1) - RecordGetDepartureMinute(r2);
    }
    if (compare == 0) {
        compare = strcmp(RecordGetFlightNumber(r1), RecordGetFlightNumber(r2));
    }

    return compare;
}

////////////////////////////////////////////////////////////////////////

/**
 * Creates a new flight DB. 
 * You MUST use the AVLTree ADT (from Task 1) in your implementation.
 */
FlightDb DbNew(void) {
	// TODO: Complete this function
	FlightDb db = malloc(sizeof(*db));
    if (db == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    db->byFlightNumber = TreeNew(compareByFlightNumber);
	db->byDepartureAirportDay = TreeNew(compareByDepartureAirportDay);
    db->betweenTimes = TreeNew(compareBetweenTimes);
    return db;
}

/**
 * Frees all memory allocated to the given flight DB
 */
void     DbFree(FlightDb db) {
	// TODO: Complete this function
	TreeFree(db->byFlightNumber, false);
    TreeFree(db->byDepartureAirportDay, false);
    TreeFree(db->betweenTimes, true);
    free(db);
}

/**
 * Inserts  a  flight  record  into the given DB if there is not already
 * record with the same flight number, departure airport, day, hour  and
 * minute.
 * If  inserted successfully, this function takes ownership of the given 
 * record (so the caller should not modify or free it). 
 * Returns true if the record was successfully inserted,  and  false  if
 * the  DB  already  contained  a  record  with  the same flight number,
 * departure airport, day, hour and minute.
 * The time complexity of this function must be O(log n).
 * You MUST use the AVLTree ADT (from Task 1) in your implementation.
 */
bool     DbInsertRecord(FlightDb db, Record r) {
	// TODO: Complete this function
	if (TreeInsert(db->byFlightNumber, r) && TreeInsert(db->byDepartureAirportDay, r) && TreeInsert(db->betweenTimes, r)) {
        return true;
    } 
    else {
        return false;
    }
}

/**
 * Searches  for  all  records with the given flight number, and returns
 * them all in a list in increasing order of  (day, hour, min).  Returns
 * an empty list if there are no such records. 
 * The  records  in the returned list should not be freed, but it is the
 * caller's responsibility to free the list itself.
 * The time complexity of this function must be O(log n + m), where m is
 * the length of the returned list.
 * You MUST use the AVLTree ADT (from Task 1) in your implementation.
 */
List     DbFindByFlightNumber(FlightDb db, char *flightNumber) {
	// TODO: Complete this function

	Record first = RecordNew(flightNumber, "", "", 0, 0, 0, 0);
	Record second = RecordNew(flightNumber, "zzzzzzzz", "zzzzzzzz", 6, 23, 59, 1200);  // 1200 = 20 hour, the longest flight in the world is 17 hour

    List l = ListNew();
    l = TreeSearchBetween(db->byFlightNumber, first, second);
    RecordFree(first);
    RecordFree(second);

    return l;
}

/**
 * Searches  for all records with the given departure airport and day of
 * week (0 to 6), and returns them all in a list in increasing order  of
 * (hour, min, flight number).
 * Returns an empty list if there are no such records.
 * The  records  in the returned list should not be freed, but it is the
 * caller's responsibility to free the list itself.
 * The time complexity of this function must be O(log n + m), where m is
 * the length of the returned list.
 * You MUST use the AVLTree ADT (from Task 1) in your implementation.
 */
List     DbFindByDepartureAirportDay(FlightDb db, char *departureAirport,
                                     int day) {
	// TODO: Complete this function
	
    Record first = RecordNew("", departureAirport, "", day, 0, 0, 0);
	Record second = RecordNew("zzzzzzzz", departureAirport, "zzzzzzzz", day, 23, 59, 1200);
    
    List l = ListNew();
    l = TreeSearchBetween(db->byDepartureAirportDay, first, second);
    RecordFree(first);
    RecordFree(second);

    return l;

}


/**
 * Searches  for  all  records  between  (day1, hour1, min1)  and (day2,
 * hour2, min2), and returns them all in a list in increasing  order  of
 * (day, hour, min, flight number).
 * Returns an empty list if there are no such records.
 * The  records  in the returned list should not be freed, but it is the
 * caller's responsibility to free the list itself.
 * The time complexity of this function must be O(log n + m), where m is
 * the length of the returned list.
 * You MUST use the AVLTree ADT (from Task 1) in your implementation.
 */
List     DbFindBetweenTimes(FlightDb db, 
                            int day1, int hour1, int min1, 
                            int day2, int hour2, int min2) {
	// TODO: Complete this function

	Record first = RecordNew("", "", "", day1, hour1, min1, 0);
	Record second = RecordNew("zzzzzzzz", "zzzzzzzz", "zzzzzzzz", day2, hour2, min2, 1200);
    
    List l = ListNew();
    l = TreeSearchBetween(db->betweenTimes, first, second);
    RecordFree(first);
    RecordFree(second);

    return l;

}

/**
 * Searches  for  and  returns  the  earliest next flight from the given
 * departure airport, on or after the given (day, hour, min), or NULL if
 * there is no such flight.
 * The returned record must not be freed or modified. 
 * The time complexity of this function must be O(log n).
 * You MUST use the AVLTree ADT (from Task 1) in your implementation.
 */
Record   DbFindNextFlight(FlightDb db, char *departureAirport, 
                          int day, int hour, int min) {
	// TODO: Complete this function
	
    Record r = RecordNew("", departureAirport, "", day, hour, min, 0);
	Record next = TreeNext(db->byDepartureAirportDay, r);
    
    // return the first flight if no next flight
    if (next == NULL) {
        Record temp = RecordNew("", RecordGetDepartureAirport(r), "", 0, 0, 0, 0);
        next = TreeNext(db->byDepartureAirportDay, temp);
        RecordFree(temp);
    }

    RecordFree(r);
    return next;
}



// Finding first available flight at SYD from Sunday 1400
// No flights found
// Record   DbFindNextFlight(FlightDb db, char *departureAirport, 
//                           int day, int hour, int min) {
// 	// TODO: Complete this function
	
//     Record r = RecordNew("", departureAirport, "", day, hour, min, 0);
//     return TreeNext(db->byDepartureAirportDay, r);
// }
