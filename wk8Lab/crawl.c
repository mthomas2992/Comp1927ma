// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders <vince@kyllikki.org>
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <curl/curl.h>
#include "stack.h"
#include "set.h"
#include "graph.h"
#include "url.h"
#include "url_file.h"
#include "queue.h"


#define BUFSIZE 1024

void setFirstURL(char *, char *);
void normalise(char *, char *, char *, char *, int);
void strlower(char *);

int main(int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char next[BUFSIZE];
	int  maxURLs;

	if (argc > 2) {
		strcpy(baseURL,argv[1]);
		setFirstURL(baseURL,firstURL);
		maxURLs = atoi(argv[2]);
		if (maxURLs < 40) maxURLs = 40;
	}
	else {
		fprintf(stderr, "Usage: %s BaseURL MaxURLs\n",argv[0]);
		exit(1);
	}

	// You need to modify the code below to implement:
	//
	// add firstURL to the ToDo list
	// initialise Graph to hold up to maxURLs
	// initialise set of Seen URLs
	// while (ToDo list not empty and Graph not filled) {
	//    grab Next URL from ToDo list
	//    if (not allowed) continue
	//    foreach line in the opened URL {
	//       foreach URL on that line {
	//          if (Graph not filled or both URLs in Graph)
	//             add an edge from Next to this URL //add vertex to graph rep also
	//          if (this URL not Seen already) {
	//             add it to the Seen set
	//             add it to the ToDo list
	//          }
	//       }
    //    }
	//    close the opened URL
	//    sleep(1)
	// }

	if (!(handle = url_fopen(firstURL, "r"))) {
		fprintf(stderr,"Couldn't open %s\n", next);
		exit(1);
	}
	Graph g;
	Set seenset;
	Queue currentURLconnect;
	Queue ToDo;
	ToDo=newQueue();
	enterQueue(ToDo,argv[1]);//add given url to que or stack
	g=newGraph(maxURLs); //initialise graph
	int q=0; //size of scanned que
	int x=0; //testing
	int test=0;
	seenset=newSet(); //set of seen urls, set doesn't have duplicates
	char currentURL[BUFSIZE];
	while (emptyQueue(ToDo)==0){ //while something in the todo list
		currentURLconnect=newQueue();
		//currentURL=leaveQueue(ToDo); //get current url
		strcpy(currentURL,leaveQueue(ToDo));
		//add if statement here to check for validity

		//get all urls associated with currentURL
		strcpy(baseURL,currentURL);
		setFirstURL(baseURL,firstURL);
		handle = url_fopen(firstURL, "r");
		while((!url_feof(handle))&&(q<maxURLs)) {
			url_fgets(buffer,sizeof(buffer),handle);
			//fputs(buffer,stdout);
			strlower(buffer);
			char *cur, link[BUFSIZE], full_link[BUFSIZE];
			cur = buffer;
			while ((cur = nextURL(cur)) != NULL) {
				getURL(cur, link, BUFSIZE-1);
				normalise(link, next, baseURL, full_link, BUFSIZE-1);
				//printf("Found %s\n",full_link);
				q++;
				enterQueue(currentURLconnect,full_link); //add to set
				cur += strlen(link);
			}
		}
		while(q>0){
			char * newcurrent=leaveQueue(currentURLconnect);
			test=addEdge(g,newcurrent,currentURL);
			if (test==0) break;
			if (isElem(seenset,newcurrent)==0){
				insertInto(seenset,newcurrent);//make seen
				enterQueue(ToDo,newcurrent); //enter todo que
			}
			q--;
		}
		if (test==0) break;
		x++;
		printf("run %d\n",x);
		if (x>10) break;
		showQueue(ToDo);
		disposeQueue(currentURLconnect); //empty out found urls
		sleep(1);
	}
	showGraph(g,1);
	/*
	//this code prints off all the urls it finds on a page
	while(!url_feof(handle)) {
		url_fgets(buffer,sizeof(buffer),handle);
		//fputs(buffer,stdout);
		strlower(buffer);
		char *cur, link[BUFSIZE], full_link[BUFSIZE];
		cur = buffer;
		while ((cur = nextURL(cur)) != NULL) {
			getURL(cur, link, BUFSIZE-1);
			normalise(link, next, baseURL, full_link, BUFSIZE-1);
			printf("Found %s\n",full_link); //perhaps here store all the found links into stack or que?
			cur += strlen(link);
		}
	}
	url_fclose(handle);
	sleep(1);*/
	return 0;


}

// normalise(In,From,Base,Out,N)
// - converts the URL in In into a regularised version in Out
// - uses the base URL to handle URLs like "/..."
// - uses From (the URL used to reach In) to handle "../"
//   - assumes that From has already been normalised
void normalise(char *in, char *from, char *base, char *out, int n)
{
	if (strstr(in, "http") != NULL)
		strcpy(out, in);
	else if (in[0] == '/') {
		strcpy(out, base);
		strcat(out, in);
	}
	else {
		strcpy(out, base);
		strcat(out, "/");
		strcat(out, in);
	}
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
void setFirstURL(char *base, char *first)
{
	char *c;
	if ((c = strstr(base, "/index.html")) != NULL) {
		strcpy(first,base);
		*c = '\0';
	}
	else if (base[strlen(base)-1] == '/') {
		strcpy(first,base);
		strcat(first,"index.html");
		base[strlen(base)-1] = '\0';
	}
	else {
		strcpy(first,base);
		strcat(first,"/index.html");
	}
}

// strlower(Str)
// - set all chars in Str to lower-case
void strlower(char *s)
{
	for ( ; *s != '\0'; s++)
		*s = tolower(*s);
}
