// Determine if/how two Places are adjacent

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "Places.h"

int main(int argc, char **argv)
{
	int id1, id2, errs=0;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s Place1 Place2\n", argv[0]);
		exit(1);
	}
	id1 = atoi(argv[1]);
	id2 = atoi(argv[2]);
	// check place validity
	if (id1 < 0 || id1 > 70) {
		errs++;
		fprintf(stderr, "Invalid place num: %d\n", atoi(argv[1]));
	}
	if (id2 < 0 || id1 > 70) {
		errs++;
		fprintf(stderr, "Invalid place num: %d\n", atoi(argv[2]));
	}
	if (errs > 0) exit(1);

	Map europe;
	europe = newMap();

	// check for direct connection
    TransportID t[MAX_TRANSPORT];  int i, n;

//	printf("Between %s and %s ...\n", idToName(id1), idToName(id2));
	n = connections(europe, id1, id2, t);
	if (n > 0) {
		for (i = 0; i < n; i++) {
			printf("%s connects to %s by ", idToName(id1), idToName(id2));
			switch (t[i]) {
			case ROAD: printf("Road\n"); break;
			case RAIL: printf("Rail\n"); break;
			case BOAT: printf("Boat\n"); break;
			default:   printf("Weird connection\n"); break;
			}
		}
	}
	return 0;
}
