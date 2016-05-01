/*

  
	MasterLibrary 4 written by Jared Bruni
	www.LostSideDead.com
	
	  herers over 17,000 lines of code in C and C++ for Visual C++ 6.0
	  
		"Open Source, Open Mind"
		
		  
			" creative freedom " 




  "some say life will beat you down
  break your heart, steal your crown
  so it started forgot knows where
  I guess ill know, when I get there " - tom petty

			
			  
				how to use,
				this library has quite a few different codes I have put together
				some object oriented, and some structured
				the reason all this is in one source file
				is so that its easily accessable and I only
				have to include one file
				what you do is decide what library aspect
				you wish to use
				and use the right #define 
				before you include the header file
				then #include masterlibrary2.h
				and the preproccescor will only add the right
				parts of the code into the EXE so that you dont
				add meaningless stuff
				
				  I hope this helps anyone who wants to learn any of this
				  I code this for practice
				  the more I code the more I learn
				  
					defines
					
					  #define MASTER_FILE_STRING_H - use the c compiler ( give dirver .c extension)
					  #define MASTERXSDK - C++/DirectX 
					  #define MASTERLIB - C++ 
					  #define MASTERIO - use the microsoft C compiler ( give driver source .c extension)
					  #define MASTER_STREAM - use the C++ compiler ( .cpp extension)
					  #define MASTER_STRING2 - use the C++ compiler (.cpp  extension)
					  #define MASTEROGL - use the C++ compiler (.cpp extension)
					  #define MASASM - Master Assembly Script/MasterString2 (.cpp extension)
					  #define MASTER_LIST List Templaite (.cpp extension)

  if you try to use C features with the C++ compiler you will get errors like
c:\masterlibrary2\masterlibrary2.h(305) : error C2440: '=' : cannot convert from 'void *' to 'char *'
thats becuase theres differences between C and C++ they are fairly small so make sure
to read all the directions to know how to use which defines for which languages ! 
if you get linking errors, remember to link to the right librarys, inside the 
header file it explains what librarys to  link to !
					  
						
*/

// use the #define MASTER_FILE_STRING directive to include this into your source
// if you wish to use these algorithms
// it is C, and should so use .C
// does not require  a special entry point
// since it is a collection of structures/functions to aid you in string
// and file manipulation 
#ifdef MASTER_FILE_STRING
#ifndef MASTER_FILE_STRING_H
#define MASTER_FILE_STRING_H

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include <string.h>
#include <ctype.h>
#define NULLPOS -1
#define FAIL -1



#define SEPKEY "{mx-sep!}"

#define FDISPLAY // for debugging


// datablock structure
struct Master_block 
{
	char* data;
	char filename[100];
	
	unsigned long size_t;
	int size_f;
};
// wr file table
struct Master_table
{
	struct Master_block* blocks;
	unsigned long block_num;
};


// function prototypes


int findstr(const char *string, const char *search);// find string
int bfindstr(const char *string, const char *search);// backwards find string
int ifindstr(int start, const char *string, const char *search, unsigned long size_t);// in find string
int ibfindstr(int start, const char *string, const char *search);// in backwards find string
void leftcopy(const char *in, char *out, int pos);// left copy
void rightcopy(const char *in, char *out, int pos);// right copy
void midcopy(const char *in, char *out, int start, int stop);// mid copy
void killspace(char *str);// kill space
int  findoccourance( const char *str, char c);// find occourance
int  findstroc( const char *str, const char *x, unsigned long size_t);
BOOL ishexc(char c);// is this a hex character?
BOOL ishex(char *data);// does this string only contain hex digits?
unsigned long hextointc(char c); // translate this character, into its integer equilvanet
unsigned long  hextoint(char *data); // translate this string of hex characters, into a integer
BOOL iop(char *data); // do illegal characters exisit within this string
BOOL iopc(char c); // illegal character?
BOOL isnumeric(char *numeric); // is this a numeric string?
int  quotesearch(int start, const char* source, const char search);// do a propper quote search (not looking at values with " " around them)
int  linebypos(const char* code, int pos);
void killfilepath(char* str);
// load a file into a datablock
void loadblock(char* filename, struct Master_block* block);
void freeblock(struct Master_block* block);
unsigned long flen(const char* filename);
BOOL isfile(char* filename);
void readfile(const char* filename,char* data);
void savetable(char* table_name, struct Master_table* table);
void loadtable(char* table_name, struct Master_table* table);
void writeblock(FILE* file, struct Master_block* block);
void table_init(struct Master_table* table, unsigned long count);
void table_free(struct Master_table* table);
void table_addfile(struct Master_table* table, char* filename);
void table_extract(struct Master_table* table);
void table_extractblock (struct Master_block* block);



// left copy
void leftcopy(const char *string, char *out, int pos)
{
	int len = strlen(string);
	int i,p = 0;
	
	for(i = 0; i < pos; i++)
	{
		out[p] = string[i];
		p++;
	}
	
	out[p] = 0;
}

// right copy
void rightcopy(const char *string, char *out, int pos)
{
	int len = strlen(string);
	int i;
	int p = 0;
	
	for(i = pos; i < len; i++)
	{
		out[p] = string[i];
		p++;
	}
	
	out[p] = 0;
}

// mid copy
void midcopy(const char *string, char *out, int start, int stop)
{
	int i;
	int p = 0;
	
	for(i = start; i < stop; i++)
	{
		out[p] = string[i];
		p++;
	}
	
	out[p] =0;
	
}


// find the position of a string, within a string
int findstr(const char *string, const char *search)
{
	int i = 0,p = 0,len = strlen(string),len2 = strlen(search);
	
	for(i = 0; i < len; i++)
	{
		if( string[i] == search[0] )
		{
			BOOL add = TRUE;
			for(p = 0; p < len2; p++)
			{
				if( string[i+p] != search[p] )
				{
					add = FALSE;
				}
			}
			
			if(add == TRUE)
			{
				return i;
			}
			
		}
	}
	
	
	return NULLPOS;
}

// backwards string search

// find the position of a string, within a string
int bfindstr(const char *string, const char *search)
{
	int i = 0,p = 0,len = strlen(string),len2 = strlen(search);
	
	for(i = len; i > 0; i--)
	{
		if( string[i] == search[0] )
		{
			BOOL add = TRUE;
			for(p = 0; p < len2; p++)
			{
				if( string[i+p] != search[p] )
				{
					add = FALSE;
				}
			}
			
			if(add == TRUE)
			{
				return i;
			}
			
		}
	}
	
	
	return NULLPOS;
}


// find string, starting from 
int ifindstr( int start, const char *string, const char *search, unsigned long size_t)
{
	int i = 0,p = 0,len = strlen(string),len2 = strlen(search);
	
	for(i = start; i < (int) size_t; i++)
	{
		if( string[i] == search[0] )
		{
			BOOL add = TRUE;
			for(p = 0; p < len2; p++)
			{
				if( string[i+p] != search[p] )
				{
					add = FALSE;
				}
			}
			
			if(add == TRUE)
			{
				return i;
			}
			
		}
	}
	
	
	return NULLPOS;
}

// find string, starting from 
int ibfindstr( int start, const char *string, const char *search)
{
	int i = 0,p = 0,len = strlen(string),len2 = strlen(search);
	
	for(i = start; i > 0; i--)
	{
		if( string[i] == search[0] )
		{
			BOOL add = TRUE;
			for(p = 0; p < len2; p++)
			{
				if( string[i+p] != search[p] )
				{
					add = FALSE;
				}
			}
			
			if(add == TRUE)
			{
				return i;
			}
			
		}
	}
	
	return NULLPOS;
}

// kill all space in this string
void killspace(char *string)
{
	int len = strlen(string);
	char *temp;
	int pos = 0,i;
	
	temp = malloc(len + 1);
	
	for(i = 0; i < len; i++)
	{
		if(string[i] != ' ')
		{
			temp[pos] = string[i];
			pos++;
		}
	}
	
	temp[pos] = 0;
	
	strcpy(string,temp);
	
	free(temp);
}

// find the occourace of a specific character within a string
int findoccourance(const char *str, char c)
{
	int cpos = 0,len = strlen(str),found = 0;
	
	for(cpos = 0; cpos < len; cpos++)
	{
		if(str[cpos] == c)
		{
			found++;
		}			
	}
	
	return found;
}

// is this a hex character?
BOOL ishexc(char c)
{
	c = tolower(c);
	switch (c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		return TRUE;
		break;
	default:
		return FALSE;
		break;
	}
	
	return TRUE;
}

// is this string only contain hex digits?
BOOL ishex(char *data)
{
	int i,len = strlen(data);
	for(i = 0; i < len; i++)
	{
		if(ishexc(data[i]) == FALSE)
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

// hex to int character 
unsigned long hextointc(char c)
{
	c = tolower(c);
	switch(c)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	case 'a':
		return 10;
		break;
	case 'b':
		return 12;
		break;
	case 'c':
		return 13;
		break;
	case 'e':
		return 14;
		break;
	case 'f':
		return 15;
		break;
	}
	
	return FAIL;
}

// translate this string into hex digits
unsigned long hextoint( char *buff)
{
	int len = strlen(buff);
	unsigned long* hexval;
	int hexvali = 0,i,z,index; 
	unsigned long rt = 0;
	
	if(ishex(buff) == FALSE)
	{
		return FAIL;
	}
	
	hexval = malloc ((len+1) * sizeof(unsigned long));
	
	for(i = 0; i < len; i++)
	{
		hexval[hexvali] = hextointc(buff[i]);
		hexvali++;
	}
	
    index = 0;
	for(z = hexvali-1; z >= 0; z--)
	{
		int cur;
		if(index == 0)
		{
			cur = hexval[z];
			index = 16;
		}
		else
		{
			cur = hexval[z] * index;
			index = index * 16;
		}
		
		rt = rt + cur;
	}
	
	free(hexval);
	
	return rt;
}

// is this character a illegal character?
BOOL iopc(char c)
{
	switch(c)
	{
	case '~':
	case '`':
	case '!':
	case '@':
		//	case '#': for float
	case '^':
	case '*':
	case '(':
	case ')':
	case '-':
	case '+':
	case '/':
	case '\\':
	case '<':
	case '>':
	case '.':
	case ',':
	case '?':
		return TRUE;
		break;
	}
	
	return FALSE;
}


// do illegal characters exisit within this string?
BOOL iop(char *string)
{
	
	int i, len = strlen(string);
	
	for(i = 0; i < len; i++)
	{
		if(iopc(string[i]) == TRUE)
		{
			return TRUE;
		}
	}
	
	
	return FALSE;
}

// is this a numeric string?
BOOL isnumeric(char *str)
{
/*
int val;

  val = hextoint(str);
  
	if(val == -1)
	{
	return FALSE;
}*/
	
	int i, len = strlen(str);
	
	for(i = 0; i < len; i++)
	{
		switch(str[i])
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case '.':
			break;
		default:
			return FALSE;
			break;
		}
		
	}
	
	return TRUE;
}
// search for symbols, disregarding data inside of  " "
int quotesearch(int start, const char* source, const char search)
{
	int i, len = strlen(source);
	BOOL igo = TRUE;
	
	for(i = start; i < len; i++)
	{
		
		if(source[i] == '\"')
		{
			if(igo == TRUE) { igo = FALSE; } else { igo = TRUE; }
		}
		
		if(igo == TRUE)
		{
			if(source[i] == search)
			{
				return i;
			}
		}
	}
	
	return FAIL;
}

// get how many \n characters (lines) there are before the pos
int linebypos(const char* source, int pos)
{
	int i, linecount = 0, len = strlen(source);
	
	for(i = 0; i < pos; i++)
	{
		if(source[i] == '\n')
		{
			linecount++;
		}
	}
	
	return linecount;
}


// 

int findstroc(const char *search, const char* str, unsigned long size_t)
{
	int pos;
	int amt = 0;
	pos = findstr( search, str );
	if( pos == -1 ) { return -1; } // failure
	amt ++;
	
	while(1)
	{
		pos = ifindstr(pos+1,search,str,size_t);
		
		if(pos == -1)
		{
			break;
		}
		else
		{
			amt++;
		}
	}
	
	
	return amt;
}

// kill the path from a file name
void killfilepath(char* str)
{
	int lpos;
	
	lpos = bfindstr( str, "\\");
	if( lpos != -1) {
		
		char* temp = malloc ( strlen (str) + 1 );
		
		rightcopy ( str, temp, lpos + 1);
		strcpy( str, temp );
		
		free( temp );
		
	}
}


// return the length of this file
unsigned long flen(const char *filename)
{
	FILE* sfile;
	unsigned long count = 0;
	
	sfile = fopen(filename,"rb+");
	
	while (1)
	{
		char c;
		c = fgetc( sfile );
#ifdef FDISPLAY 
		printf("%c",c);
#endif
		if(feof(sfile))
		{
			break;
		}
		else
		{
			count++;
		}
	}
	
	return count;
}

// does this file exisit? if yes, then return true
BOOL isfile(char *filename)
{
	HANDLE hSearch;
	WIN32_FIND_DATA p;
	hSearch = FindFirstFile(filename,&p);
	if(hSearch!=INVALID_HANDLE_VALUE)
		return TRUE;
	else
		return FALSE;
}

// read in the file
void readfile(const char *filename, char* data)
{
	int pos;
	FILE* ofile;
	
	pos = 0;
	
	ofile = fopen(filename,"rb+");
	
	while (1)
	{
		char c;
		c = fgetc( ofile );
		if(feof(ofile))
		{
			break;
		}
		
		data[pos] = c;
		pos++;
		
	}
	
	data[pos] = 0;
	fclose(ofile);
}

// load information from disk into a block of data
void loadblock(char* filename, struct Master_block* block)
{
	block->data = NULL;
	
	if(isfile(filename))
	{
		block->size_t = flen(filename)+1;
		block->data = malloc(flen(filename)+5);
		strcpy(block->filename,filename);
		block->size_f = strlen(filename) + 1;
		readfile(filename,(char*)block->data);
		
	}
}

// free the block
void freeblock(struct Master_block* block)
{
	if(block->data != NULL)
	{
		
		free(block->data);
		free(block);
		
	}
}

/* hehe -> vb(); */
/* hehe -> master(); //  ok ok // ok ok */


// Masterite the block to a already opened file
void Masteriteblock(FILE* file, struct Master_block* block)
{
	unsigned int i;
	
	fprintf(file,"%s%s;%i:",SEPKEY,block->filename,block->size_t);
	
	for(i = 0; i < block->size_t; i++)
	{
		fputc(block->data[i],file);
	}
}

// load a table from file
void loadtable(char* table_name, struct Master_table* table)
{
	
	int amt = 0; // amount of seperation keys
	char* tdat;
	int file_len = flen( table_name );
	int start_offset = -1;
	
	
	
	
	tdat = malloc ( file_len + 1);
	
	readfile(table_name, tdat);
	
	amt = findstroc( tdat, SEPKEY, file_len );
	
	table_init( table, amt );
	
	
	while (1)
	{
		char tinfo[200];
		char tsize[0xFF];
		int open_pos = 0, close_pos = 0,end_pos = 0;
		long read_size = 0;
		long start_pos = 0;
		int addoff = 0;
		
		
		
		open_pos = ifindstr( start_offset + 1, tdat, SEPKEY, file_len );
		
		if(open_pos == -1) { break; }// no more seperation keys
		close_pos = ifindstr( open_pos, tdat, ";", file_len );
		end_pos = ifindstr( close_pos, tdat, ":", file_len );
		
		midcopy (tdat, tinfo, open_pos + strlen(SEPKEY),close_pos);
		midcopy (tdat, tsize, close_pos + 1, end_pos );
		
		
		/*	printf(" filename: %s size: %s", tinfo, tsize);
		
		system("pause"); */
		strcpy ( table->blocks[table->block_num].filename, tinfo);
		
		read_size = atol ( tsize );
		
		// now allocate the correct amount in the data buffer
		table->blocks[table->block_num].data = malloc ( read_size + 1 );
		table->blocks[table->block_num].size_t = read_size;
		
		for( start_pos = end_pos + 1; start_pos < end_pos + 1 + read_size; start_pos ++ )
		{
			table->blocks[table->block_num].data [ addoff ] = tdat [ start_pos ];
			addoff++;
		}
		
		table->blocks[table->block_num].size_t = read_size;
		
		
		// read in the data, proccess it into the table for a extract 
		
		table->block_num++;
		// set th enew offset
		
		start_offset = open_pos + 1;
		
		
	}
	
	free(tdat);
	
	
}

// save a table to file
void savetable(char* table_name, struct Master_table* table)
{
	// save the table to a binary file, to be read back
	unsigned long i;
	FILE* tfile;
	
	tfile = fopen(table_name,"w");
	
	for (i = 0; i < table->block_num; i++)
	{
		Masteriteblock(tfile,&table->blocks[i]);
	}
	
	fclose(tfile);
}

//
void table_init(struct Master_table* table, unsigned long count)
{
	table->block_num = 0;
	table->blocks = malloc ( sizeof( struct Master_block ) *  count );
}

void table_free(struct Master_table* table)
{
	unsigned long i ;
	for( i = 0; i < table->block_num; i++)
	{
		free( table->blocks[i].data );
		
	}
	free(table->blocks);
}

void table_addfile(struct Master_table* table,char* filename)
{
	loadblock(filename,&table->blocks[table->block_num]);
	killfilepath(table->blocks[table->block_num].filename);
	table->block_num++;
}


void table_extract(struct Master_table* table) 
{
	unsigned long i;
	
	for( i = 0; i < table->block_num; i++)
	{
		table_extractblock ( &table->blocks[i] );
	}
}

// extract this block
void table_extractblock (struct Master_block* block)
{
	FILE* sfile;
	unsigned long pos = 0;
	
    sfile = fopen(block->filename,"w");
	
	for(pos = 0; pos < block->size_t; pos++)
	{
		fputc( block->data [ pos ] , sfile );
	}
	
	
	fclose (sfile);
	
}

#endif
#endif


// use the
// #define MASTER_IOSTREAM
// before you include masterlibrary.h
// to produce a MasterConsole application
// make sure you make it a win32 application
// try not to use these with the structured techniques
// keep them seperate :)
// also remember to use the
// int mastermain(char* argument)
// {
// return(0);
// }
// entry point !
#ifdef MASTER_IOSTREAM
#ifndef MASTERSTREAM
#define MASTERSTREAM

#include <windows.h>
#include <fstream.h>
#include <stdio.h>

#define endl "\n"
#define MASTER_IN WM_USER + 5
#define MASTER_OUT WM_USER + 6
#define MASTER_DONE WM_USER + 7
#define MASTER_INIT WM_USER + 8
#define MASTER_CLEAR WM_USER + 9
#define MASTER_PAUSE WM_USER + 10



int mastermain(char*);
LRESULT APIENTRY WndProc( HWND hwnd , UINT msg, WPARAM wParam, LPARAM lParam );
inline void init();
void readfile(const char *filename, char* data);
int flen(const char *filename);

HWND hwnd;
HWND hconsole;
HWND hpipe;
bool in_go = false;
bool pause_go = false;
char* the_line = NULL;

class masterconsole
{
	void concat(char* buffer);
	void input( char* buffer );
	
public:
	
	masterconsole& operator<<(char*);
	masterconsole& operator<<(char);
	masterconsole& operator<<(int);
	masterconsole& operator<<(short);
	masterconsole& operator<<(long);
	masterconsole& operator<<(double);
	masterconsole& operator>>(char*);
	masterconsole& operator>>(int&);
	masterconsole& operator>>(short&);
	masterconsole& operator>>(long&);
	masterconsole& operator>>(double&);
	
	void pause();
	void clear();
	void printf(const char *, ... );
	
};

void masterconsole::printf(const char * str, ...)
{
	va_list list; 
	char string[5000];
	va_start(list, str); 
	vsprintf((char*)string,str,list);
	va_end(list); 
	concat(string);
}

void masterconsole::concat(char* buffer)
{
	SendMessage(hpipe,WM_SETTEXT,strlen(buffer)+1,(LPARAM)(LPCSTR)buffer);
	SendMessage(hconsole,MASTER_OUT,0,0);	
}

// stream the data
masterconsole& masterconsole::operator <<(char* buffer)
{
	concat(buffer);
	return (*this);
}

masterconsole& masterconsole::operator <<(char c)
{
	char pc[1];
	pc[0] = c;
	pc[1] = 0;
	concat(pc);
	return (*this);
}

masterconsole& masterconsole::operator<<(int num)
{
	char cnum[25];
	itoa(num,cnum,10);
	concat(cnum);
	return(*this);
}

masterconsole& masterconsole::operator <<(short num)
{
	char cnum[25];
	itoa((int)num,cnum,10);
	concat(cnum);
	return(*this);
}

masterconsole& masterconsole::operator <<(long num)
{
	char cnum[50];
	ltoa(num,cnum,10);
	concat(cnum);
	return(*this);
}

masterconsole& masterconsole::operator << (double num )
{
	char cnum[50];
	gcvt(num,10,cnum);
	concat(cnum);
	return(*this);
}

void masterconsole::input(char* buffer)
{
	// send the signal to do input
	// wait in a do events loop
	in_go = true;
	SendMessage(hconsole, MASTER_IN, 0,0);
	
	// lets wait until, its time to read in the dat
	while( in_go == true )
	{
		MSG msg;
		int t = PeekMessage(0,0,0,0,PM_NOREMOVE);
		if(t == WM_QUIT) { break; }
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}
	
	
	SendMessage(hpipe,WM_GETTEXT,5000,(LPARAM)(LPCSTR)buffer);
}

// input stream
masterconsole& masterconsole::operator>>(char* buffer)
{
	// send the signal to do input
	char i[5000];
	input(i);
	strcpy(buffer,i);
	return (*this);
	
}

masterconsole& masterconsole::operator>>(int& num)
{
	char* buffer;
	buffer = new char [ 5000 ];
	input(buffer);
	num = atoi(buffer);
	delete [] buffer;
	buffer = NULL;
	
	return (*this);
}

masterconsole& masterconsole::operator>>(short& num)
{
	char* buffer;
	buffer = new char [ 5000 ];
	input(buffer);
	num  = atoi(buffer);
	delete [] buffer;
	buffer = NULL;
	
	
	return (*this);
}

masterconsole& masterconsole::operator>>(long& num)
{
	char* buffer;
	buffer = new char [ 5000 ];
	input(buffer);
	num = atol(buffer);
	delete [] buffer;
	buffer = NULL;
	
	return (*this);
}

masterconsole& masterconsole::operator>>(double& num)
{
	char* buffer;
	buffer = new char [ 5000 ];
	input(buffer);
	num = atof(buffer);
	delete [] buffer;
	buffer = NULL;
	
	return (*this);
}

// flush out the buffer
void masterconsole::clear()
{
	SendMessage(hconsole,MASTER_CLEAR,0,0);
}
// press any key to continue
void masterconsole::pause()
{
	SendMessage(hconsole,MASTER_PAUSE,0,0);
	
	pause_go = true;
	
	while(pause_go == true)
	{
		MSG msg;
		int t = PeekMessage(0,0,0,0,PM_NOREMOVE);
		if(t == WM_QUIT) { break; }
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}
}

extern masterconsole console;
masterconsole console;


int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	the_line = line;
	hconsole = FindWindow("MasterConsole",NULL);
	if( hconsole == NULL )
	{
zerror:
	MessageBox(0,"Error!\nThis application must be ran from the MasterConsole command line"," Runtime Error", 
		
		MB_ICONERROR );
	return (0);
	}
	hpipe = FindWindowEx(hconsole,0,"Static",0);
	if(hpipe == NULL)
	{
		goto zerror;
	}
	
	
	init();
	return (0);
}

inline void init()
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = NULL;
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "master_console_app";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&wc);
	
	hwnd = CreateWindow("master_console_app","",WS_OVERLAPPED,0,0,0,0,0,0,GetModuleHandle(NULL),0);
	
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
}


LRESULT APIENTRY WndProc( HWND hwnd , UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch (msg)
	{
	case WM_DESTROY:
		SendMessage(hconsole,MASTER_DONE,0,0);
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			
			SendMessage(hconsole,MASTER_INIT,0,0);
			mastermain(the_line);
			SendMessage(hwnd,WM_CLOSE,0,0);
		}
		break;
	case MASTER_IN:
		{
			in_go = false;
		}
		break;
	case MASTER_PAUSE:
		{
			pause_go = false;
		}
		break;
		
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	
	return (0);
}


// return the length of this file
int flen(const char *filename)
{
	FILE* sfile;
	int count = 0;
	
	sfile = fopen(filename,"rb+");
	
	if( sfile == NULL )
	{
		return -1;
	}
	
	while (1)
	{
		char c;
		c = fgetc( sfile );
		if(c == EOF)
		{
			break;
		}
		else
		{
			count++;
		}
	}
	
	return count;
}

// read in the file
void readfile(const char *filename, char* data)
{
	int pos;
	FILE* ofile;
	
	pos = 0;
	
	ofile = fopen(filename,"rb+");
	
	if( ofile == NULL )
	{
		strcpy(data,"�");
		return;
	}
	
	while (1)
	{
		char c;
		c = fgetc( ofile );
		if(c == EOF)
		{
			break;
		}
		
		data[pos] = c;
		pos++;
		
	}
	
	data[pos] = 0;
	fclose(ofile);
}


#endif
#endif


// for making master console applications with C
// using this library 
// remember not to ues it with the collection of functions
// also remember to use the mastermain entry point as follows in your driver !
// int mastermain(char* argument)
// {
// return(0);
// }
#ifdef MASTERIO
#ifndef _MASTERIO_H_
#define _MASTERIO_H_
#define MASTER_IN WM_USER + 5
#define MASTER_OUT WM_USER + 6
#define MASTER_DONE WM_USER + 7
#define MASTER_INIT WM_USER + 8
#define MASTER_CLEAR WM_USER + 9
#define MASTER_PAUSE WM_USER + 10
#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#define true 1
#define false 0
#define bool int


/* function prototypes */
LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void Init();
void mprintf( const char *str, ... );
void mscanf(const char *str, ...);
void concat( const char *str );
void input(char* );
void mflush();
void mclear();
void mpause();
int  miint();
long milong();
double midouble();


/* global variables */
HWND hwnd;
HWND hconsole;
HWND hpipe;
char* the_line;
int mastermain(char* argument);
bool in_go;
bool pause_go;


int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	MSG msg;
	the_line = line;
	hconsole = FindWindow("MasterConsole",NULL);
	
	if( hconsole == NULL )
	{
zerror:
	MessageBox(0,"Error!\nThis application must be ran from the MasterConsole command line"," Runtime Error", 
		
		MB_ICONERROR );
	return (0);
	}
	hpipe = FindWindowEx(hconsole,0,"Static",0);
	if(hpipe == NULL)
	{
		goto zerror;
	}
	
	Init();
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (0);
}


void Init()
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = NULL;
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "master_console_app";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&wc);
	
	hwnd = CreateWindow("master_console_app","",WS_OVERLAPPED,0,0,0,0,0,0,GetModuleHandle(NULL),0);
	
	
}


LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch ( msg )
	{
		
	case WM_DESTROY:
		SendMessage(hconsole,MASTER_DONE,0,0);
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			// init
			SendMessage(hconsole,MASTER_INIT,0,0);
			mastermain(the_line);
			SendMessage(hwnd,WM_CLOSE,0,0);
		}
		break;
	case MASTER_IN:
		{
			in_go = false;
		}
		break;
	case MASTER_PAUSE:
		{
			pause_go = false;
		}
		break;
		
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
		
	}
	
	return (0);
}


/* print formated text */
void mprintf( const char *str, ... )
{
	va_list list; 
	char string[5000];
	va_start(list, str); 
	vsprintf((char*)string,str,list);
	va_end(list); 	
	concat(string);
}

/* scan for input strings */
void mscanf(const char *str, ...)
{
	va_list list;
	
	
	va_start(list, str);
	while( *str )
	{
		switch(*str++)
		{
		case 's':// string
			{
				char* pcharacter;
				pcharacter = va_arg(list,char*);
				input(pcharacter);				
			}
			break;
		}
	}
	
	va_end(list);
}

/* concatinate data to the buffer */
void concat(const char *buffer)
{
	SendMessage(hpipe,WM_SETTEXT,strlen(buffer)+1,(LPARAM)(LPCSTR)buffer);
	SendMessage(hconsole,MASTER_OUT,0,0);	
}

// input from the buffer
void input(char* buffer)
{
	/* send the signal to do input */
	/* wait in a do events loop */
	in_go = true;
	SendMessage(hconsole, MASTER_IN, 0,0);
	
	/* lets wait until, its time to read in the dat */
	while( in_go == true )
	{
		MSG msg;
		int t = PeekMessage(0,0,0,0,PM_NOREMOVE);
		if(t == WM_QUIT) { break; }
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}
	
	
	SendMessage(hpipe,WM_GETTEXT,5000,(LPARAM)(LPCSTR)buffer);
}

void mflush()
{
	SendMessage(hconsole,MASTER_CLEAR,0,0);
}

void mclear()
{
	mflush();
}

void mpause()
{
	SendMessage(hconsole,MASTER_PAUSE,0,0);
	
	pause_go = true;
	
	while(pause_go == true)
	{
		MSG msg;
		int t = PeekMessage(0,0,0,0,PM_NOREMOVE);
		if(t == WM_QUIT) { break; }
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}
}

int  miint()
{
	char input_buffer[255];
	mscanf("%s",input_buffer);
	return (atoi(input_buffer));
}

long milong()
{
	char input_buffer[255];
	mscanf("%s",input_buffer);
	return (atol(input_buffer));
}

double midouble()
{
	char input_buffer[255];
	mscanf("%s",input_buffer);
	return (atof(input_buffer));
}



#endif
#endif

#ifdef MASTERXSDK
/* MasterX Software Devlopment Kit (SDK) 1.9.1
DirectX/Win32 Encapsulation For easy game programming.
Written by Jared Bruni
Email Me: JaredBruni@lostsidedead.com 
www.lostsidedead.com

  
	now contains MasterX Media ( Mp3 Class ) 
	written by Lee Trager ( newest member of lostsidedead.com )
	
	  
		for MasterX SDK documentation check out
		www.lostsidedead.com/gameprog/
		
		  I really am a video game programming fan
		  
			note required librarys within your project link settings
			
			  dxguid.lib ddraw.lib dsound.lib dinput.lib  wsock32.lib winmm.lib
			  
*/

// remember to use the MasterMain entry point,and link !
// example
// int _stdcall MasterMain(HINSTANCE hInst,LPSTR line)
// {
// return(0);
// }


#ifndef MASTERX
#define MASTERX


#define DIRECTINPUT_VERSION 0x700


#include <ddraw.h>
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#include <winsock.h>
#include <stdio.h>
#include<stdarg.h> 


// the default port ID for mastersocket(when it sees -1 it changes it to 7)
#define DEFAULT_PORT -1
// for register based calling convention rather then stack based (speed)
#define FAST __fastcall
// for std based calling convention
#define XSTD __stdcall 
#define MXENTRY __stdcall
// for pascal based calling convention
#define XPAS __pascal
// joydead zone
#define JOY_DEADZONE 20 

// Helper typedef's
typedef int MASTERSCREEN;
typedef int MASTERMSG;
typedef long MXRESULT;
typedef unsigned long WindowHandle;



enum DisplayColor { COLOR_8, COLOR_16,COLOR_24,COLOR_32,COLOR_DEFAULT };

// ADT game object
class MasterGameObject 
{
public:
	virtual void load() = 0;
	virtual void update() = 0;
};

// the masterscreen structure, holds the pointers to the directX com objects interfaces
struct MasterScreen
{
	LPDIRECTDRAW lpDD;
	LPDIRECTDRAWSURFACE lpBack;
	LPDIRECTDRAWSURFACE lpFront;
	~MasterScreen();
};

// text output object, which exisits inside the MasterXHWND object
class MasterText
{
public:
	MasterScreen*  scr;
	HFONT font;
	HFONT underfont;
	
	COLORREF bk;
	COLORREF text;
	void init(MasterScreen*);
	void setfont(HFONT);
	void setunderfont(HFONT);
	void setbkcolor(COLORREF);
	void settextcolor(COLORREF);
	void FAST printtext(char*,int x,int y);
	void FAST sprinttext(int x, int y,char* str, ...);
	void FAST printtextunderline(char*, int x, int y);
	void FAST printtextrect(char*, int x, int y, int w, int h);
	void FAST printtextrectf(int x, int y, int x2, int y2, char* str, ...);
	
	
	void setdefaultfont();
};

// graphic object, - displays bitmaps, and peices of bitmaps, supports color keys
typedef class MasterGraphic
{
	MasterScreen* scr;
	LPDIRECTDRAWSURFACE surf;
	char  filename[50];
	bool ckey;
public:
	int w;
	int h;
	void init(MasterScreen* scr);
	bool LoadGraphic(char* filename);
	bool LoadGraphic(char* filename,MasterScreen* scr);
	void ReLoadGraphic();
	void SetColorKey(COLORREF r);
	void DisplayGraphic(int x, int y);
	void DisplayGraphicEx(int bx, int by, int bw, int bh,int image_x, int image_y);
	~MasterGraphic();
	MasterGraphic();
	void Release();
}MasterSprite;

// mastersound object ,  - sound object, plays imbeded wave files
class MasterSound
{
public:
	IDirectSoundBuffer *pSound;
	bool LoadSound(IDirectSound* pds,LPCTSTR name);
	void Play();
	bool PlayStatus();
	void Release();
	
	MasterSound();
	~MasterSound();
};

// Painting Functions
class MasterPaint
{
	MasterScreen* scr;
public:
	
	void init(MasterScreen* xscr);
	void FAST mxdrawrect(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline);
	void FAST mxdrawroundrect(int x, int y, int x2, int y2,int cw, int ch, COLORREF fill,COLORREF outline);
	void FAST mxdrawpie(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2,COLORREF fill, COLORREF outline);
	void FAST mxdrawchord(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2, COLORREF fill, COLORREF 
		
		outline);
	void FAST mxdrawellipse(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline);
	void FAST mxsetpixel(int x, int y, COLORREF rgbval);
	COLORREF FAST mxgetpixel(int x, int y);
	void FAST mxarc(int x1,int x2, int x3, int x4, int x5, int x6, int x7, int x8,COLORREF fill,COLORREF outline);
	void FAST mxpolygon(CONST POINT* point,int n_points,COLORREF fill,COLORREF outline);
	void FAST mxlineto(int x, int y,COLORREF fill,COLORREF outline);
	void FAST mxanglearc(int x, int y, long radius,float startangle, float sweepangle,COLORREF outline);
	void FAST mxhorizontalline(int x, int x2, int y,COLORREF color);
	void FAST mxverticalline(int y1,int y2,int x,COLORREF color);
	void FAST mxline(int start_x, int start_y, int stop_x, int stop_y,COLORREF color);// draw diagnoal lines
};

// MasterMedia class, written by Lee Trager ( age : 13 years old )
// you can contact Lee, his screen name on AIM is nukem996
// if you find any problems with his code, or want to
// help him work on it, go ahead and message him
class MasterMedia {
	
private:
	
	//gets error number
	long a;
	//for getshortpath
	char finname[1000];
	//to put string together
	char todo[2000];
	
	//error code
	void error(long what){
		mciGetErrorString(what, err, 128);
	}
	
public:
	
	char cfile[255];
	//this is where the error is stored
	char err[10000];
	//this is the alias name of the file ex. mpeg
	char alias[100];
	//tells u the status of a file
	TCHAR statuss[40];
	//tells u the position number(millisec)
	TCHAR p[40];
	//tells u the lenght number(millisec)
	TCHAR l[40];
	
	//opens files and dose not put them in a window
	void open(char file[1000]){
		if(GetShortPathName(file, finname, 1000) != 0){
			strcpy(cfile,file);
			fopen(finname);
		}
	}
	
	// get a pointer to the name of the currently opened file
	char* openedfile()
	{
		return (char*) cfile;
	}
	
	
	// open mp3
	void openmp3(char file[1000])
	{ 
		strcpy(alias,"mpeg");
		open(file);
	}
	
	/*if you have the short path name call to this
	by doing this the file will load faster
	opens files and dose not put them in a window*/
	void fopen(char file[1000]){
		close();
		sprintf(todo, "open %s type mpegvideo Alias %s", file, alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
    }
	
	//open files and puts them in a parent space
	void vidopen(char file[1000], HWND parent){
		if(GetShortPathName(file, finname, 1000) != 0){
			fvidopen(finname, parent);
		}
	}
	
	/*if you have the short path name call to this
	by doing this the file will load faster
	open files and puts them in a parent space*/
	void fvidopen(char file[1000], HWND parent){
		close();
		sprintf(todo, "open %s type mpegvideo Alias %s parent %s Style 1073741824", file, alias, parent);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
	}
	
	//play file
	void play(){
		sprintf(todo, "Play %s from 0", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
    }
	
	//stop file
    void stop(){
		sprintf(todo, "Stop %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
    }
	
	//pause file
	void pause(){
		sprintf(todo, "Pause %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
    }
	
	//resume file
    void resume(){
		sprintf(todo, "Resume %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
    }
	
	//close file
    void close(){
		sprintf(todo, "Close %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}
	
	/*for poistion and lenght error code will now work winmm.dll returns too big of a char
	to ask for the error code it has to be an int but since we cannt use a int we cannt use
	error code here*/
	//get the poistion of a file
	
	unsigned long poistion(){
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString (todo, 0 ,0, 0);
		sprintf(todo, "status %s position", alias);
		mciSendString (todo, p, 40, 0);
		
		return ( unsigned long ) atol(p);
	}
	
	//gets the length of a file
	unsigned long length(){
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString (todo, 0, 0, 0);
		sprintf(todo, "status %s length", alias);
		mciSendString (todo, l, 40, 0);
		return ( unsigned long ) atol (p);
	}
	
	//changes volume sp = speaker vol = what the volume should be set at
	void volume(char sp[6], long vol){
		vol = vol * 10;
		sprintf(todo, "setaudio %s %s Volume to %d", alias, sp, vol);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}
	
	//resize the video
	void resizevid(int left, int top, int width, int height){
		sprintf(todo, "put %s window at %i %i %i %i", alias, left, top, width, height);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}
	
	//seek somewhere with in the file
	void seekto(int where){
		where = where * 1000;
		sprintf(todo, "set %s time format milliseconds", alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
		sprintf(todo, "play %s from %i", alias, where);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
	}
	
	//finds out the status of whats being played
	void status(){
		sprintf(todo, "status %s mode", alias);
		a = mciSendString(todo, statuss, 40, 0);
	}
	
	//set the speed of a file 1000 = normal below 1000 = slower above 1000 = faster
	//changes speed will make audio only come out the frount 2 speakers
	void speed(int spe){
		sprintf(todo, "set %s speed %i", alias, spe);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}
	
	//auto repeat the file repeat [t] = true then repeat file false it wont or will stop
	void repeat(bool repeatt){
		if (repeatt == true){
			sprintf(todo, "play %s notify repeat", alias);
			a = mciSendString(todo, 0, 0, 0);
			error(a);
		}
		else{
			sprintf(todo, "play %s", alias);
			a = mciSendString(todo, 0, 0, 0);
			error(a);
		}
	}
};
// end of lee's media class
// back to jareds codes :)


// the MasterXHWND object, thie is the host object
class MasterXHWND
{
	MASTERSCREEN mscr;
	DDBLTFX ddbltfx;
	
	int pre_time;
    int timer_count;
	
	bool time_flag;
	
	void Destroy();
    bool setprimarysurface();
	bool initSound();
	void initInput();
	
public:
	HWND hwnd;
	MasterScreen scr;
	MasterText   text;
	MasterPaint  paint;
	MasterMedia  media;
	bool alive;
	UINT activeapp;
	IDirectInput		*pDI;
    IDirectInputDevice	*pKeyboard;
    IDirectSound	*pDS;
	
	
	void (* update) (MASTERSCREEN xscr);
	bool CreateMasterX(char* mytitle,int width,int height,DisplayColor color,WNDPROC proc,HINSTANCE hInst,HICON 
		
		icon,HCURSOR cursor);
	WPARAM InitLoop( void (* update) (MASTERSCREEN xscr));
	void Kill();
	MASTERSCREEN  GetScreen();
	void SetScreen(MASTERSCREEN xmscr);
	LRESULT SendMasterMessage(UINT msg,WPARAM wParam,LPARAM lParam);
	void clear();
	void mx_update();
	bool LoadGraphic(MasterGraphic* g, char* filename);
	bool LoadSound(MasterSound* s,LPCSTR resourceID);
    bool KeyCheck(int key);
	bool AsyncKeyCheck(int key);
	void InitTimer(int id, int interval);
	void DestroyTimer(int id);
	void GetMousePosWin(long& x, long& y);
	HFONT CreateMasterFont(char* font_name,int size);
	void HideCursor();
	void RestoreCursor();
	bool TimeChange();
	void ChangeTime();
	void SetTimeFlag();
	bool SyncChange();
};


//******************************** DirectDraw/DirectSound Helper Functions.. from ddutil
IDirectDrawSurface* DDLoadBitmap(IDirectDraw* pdd, LPCSTR szBitmap);
IDirectDrawSurface* CreateOffScreenSurface(IDirectDraw* pdd, int dx, int dy); // Creating the Surface
HRESULT DDCopyBitmap(IDirectDrawSurface* pdds, HBITMAP hbm, int dx, int dy); // Copy Bitmap
///////////////////////////////////////////////////////////////////////////////
IDirectSoundBuffer *DSLoadSoundBuffer(IDirectSound *pDS, LPCTSTR lpName);
BOOL DSReloadSoundBuffer(IDirectSoundBuffer *pDSB, LPCTSTR lpName);
BOOL DSGetWaveResource(HMODULE hModule, LPCTSTR lpName,
					   WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, DWORD *pdwWaveSize);
BOOL DSFillSoundBuffer(IDirectSoundBuffer *pDSB, BYTE *pbWaveData, DWORD dwWaveSize);
BOOL DSParseWaveResource(void *pvRes, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, 
						 DWORD *pdwWaveSize);
HRESULT
DDSetColorKey(IDirectDrawSurface * pdds, COLORREF rgb);
DWORD
DDColorMatch(IDirectDrawSurface * pdds, COLORREF rgb);

HRESULT
DDCopyBitmap2(IDirectDrawSurface * pdds, HBITMAP hbm, int x, int y,
			  int dx, int dy);
HRESULT
DDReLoadBitmap(IDirectDrawSurface * pdds, LPCSTR szBitmap);
//********************************************************************************************
// make a font
HFONT MakeFont(char* ftype, int size);
int APIENTRY MasterMain(HINSTANCE hInst,LPSTR line);// mastermain entry point
// mxbitmap structure, for a surfaces information
struct mxbitmap
{
	int w;
	int h;
	IDirectDrawSurface* surf;
};

static int MXWIDTH;
static int MXHEIGHT;
static bool sound_ok;

// base screen object, inhert this object if you wish for it to have access to MasterXHWND object from a remote location
// it is good for if you want to make sections of the game in differnt areas of the code.
struct ScreenObject
{
	MASTERSCREEN sub_screen;
	MasterXHWND* mxhwnd;
	
	inline Init(MasterXHWND* mxhwndx)
	{
		mxhwnd = mxhwndx;
	}
	
	inline MASTERSCREEN getscreen()
	{
		return sub_screen;
	}
	
	inline void setscreen(MASTERSCREEN xscreen)
	{
		sub_screen = xscreen;
	}
};

//******************* mastersocket

// initilize and kill winsock
void initwinsock();
void killwinsock();

// structure to automaticly initlize and kill winsock
struct AutoWinSockHandle
{
	inline AutoWinSockHandle()
	{
		initwinsock();
	}
	
	inline ~AutoWinSockHandle()
	{
		killwinsock();
	}
};

static AutoWinSockHandle sock_handle; // automaticly construct, and deconstruct
// winsock with this static structure

struct MasterSocket
{
	SOCKET socketx; // the socket structure
	HWND  hwnd; // handle of the window the socket is attached to
	UINT  SOCKET_ID; // socket ID
	void CreateSocket(HWND hwndx,UINT SOCKET_IDx);// create the socket
	void Listen(UINT port);// listen on the socket
	void Connect(char* ipaddress,UINT port);// connect with the socket
	void Send(char* buff, int len); // send data with a connected socket
	int Recive(char* buff,int len);// recive data
	void Accept(); // accept a incomin socket
	const UINT GetID();// get the ID of this socket
	void Close();// close the socket
};

// MasterJoyStick for joysticks


struct MasterJoyStick
{
	JOYINFOEX joystickInfoEx ;// information about are joystick
	JOYCAPS   joystickCaps; // caps structure
	bool joystickPresent;
	bool joystickHasThrottle;
	bool joystickActive;
	unsigned int joystickDeadXMin,joystickDeadXMax,joystickDeadYMin,joystickDeadYMax;
	unsigned int GetJoysticks(); // returns the number of joysticks the drivers support
	bool         JoyExisit(); // does a joystick exisit
	bool         SetupJoystick(); // setup the default joystick
	bool         GetJoystickCoords(JOYINFOEX* info); // get joystick coords structure
	bool         JoyStop();
	bool         JoyForward();
	bool         JoyBackward();
	bool         JoyRight();
	bool         JoyLeft();
	int          GetButtonPressed(JOYINFOEX*);
	int          JoyButtonDown();
	
	inline ~MasterJoyStick()
	{
		ZeroMemory(&joystickInfoEx,sizeof(joystickInfoEx));
	} 
};


/********** MasterScreen Object ******************/

MasterScreen::~MasterScreen()
{
	if(lpBack)
	{
		lpBack->Release();
		lpBack = NULL;
	}
	
	if(lpFront)
	{
		lpFront->Release();
		lpFront = NULL;
	}
	
	if(lpDD)
	{
		lpDD->Release();
		lpDD = NULL;
	}
}

// ****************** MasterXHWND Object 

// Create and initilze MasterX
bool MasterXHWND::CreateMasterX(char* mytitle,int width, int height,DisplayColor color,WNDPROC proc,HINSTANCE hInst,HICON 
								
								icon,HCURSOR cursor)
{
	
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = icon;
	wc.hCursor = cursor;
	wc.lpfnWndProc = (WNDPROC) proc;
	wc.lpszClassName = mytitle;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&wc);
	
	hwnd = CreateWindow(mytitle,mytitle,WS_POPUPWINDOW,0,0,width,height,0,0,hInst,0);
	
	if(hwnd == 0)
	{
		return false;
	}
	
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	
	int bpp;
	
	
	switch(color)
	{
	case COLOR_DEFAULT:
		HDC hdc;
		// retrieves device-specific information about 
		// the specified device. 
		
		// Get the windows device context
		hdc = GetDC(NULL);
		// Get the number of adjacent color bits for each pixel.
		bpp = GetDeviceCaps(hdc, BITSPIXEL);
		// Release the Device Context
		ReleaseDC(NULL, hdc);
		break;
		
	case COLOR_8:
		bpp = 8;
		break;
	case COLOR_16:
		bpp = 16;
		break;
	case COLOR_24:
		bpp = 24;
		break;
	case COLOR_32:
		bpp = 32;
		break;
	}
	
	
	HRESULT ddrval;
	
	// create main dd object
	
	ddrval = DirectDrawCreate(NULL, &scr.lpDD,NULL);
	
	if(ddrval != DD_OK)
	{
		MessageBox(NULL,"Couldnt Create DirectX Object! Error: Terminating!","Error!!!",MB_ICONERROR);
		Kill();
		return false;
	}
	
	ddrval = scr.lpDD->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT );
	
	
	
	if(ddrval != DD_OK)
	{
		scr.lpDD->Release();
		MessageBox(0,"Couldnt Set Cooperative Level, Fatal Error Aborting","Error",MB_ICONERROR);		
	}
	
	ddrval = scr.lpDD->SetDisplayMode(width,height,bpp);
	
	if(ddrval != DD_OK)
	{
		MessageBox(0,"Error Setting Display Mode",0,MB_ICONERROR);
		scr.lpDD->Release();
		return false;
		
	}
	
	if(setprimarysurface())
	{
		sound_ok = initSound();
	}
	else
	{
		MessageBox(0,"Couldnt Set Surfaces! Fatal Error! DirectX is jacked Man","Broken Software :(",MB_ICONERROR);
		return false;
	}
	
	initInput();
	text.init((MasterScreen*)&scr);
	paint.init(&scr);
	
	alive = true;
	
	return true;
}

// initilize Message Processing Loop
WPARAM MasterXHWND::InitLoop(void(* update)(MASTERSCREEN xscr))
{
	
	MSG msg;
	
	while(1)
    {
		
        int t = PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);
        if (t)
        {
            if (!GetMessage (& msg, NULL, 0, 0))
				return msg.wParam;
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
        
        else if (activeapp)// this is important here
		{	
			clear();
			update(mscr);
			mx_update();
		}
        else if (!activeapp)
		{
			WaitMessage();
		}
    }
	
	
	Destroy();
	return msg.wParam;
	
}

// release and destroy Objects 
void MasterXHWND::Destroy()
{
	// Kill Sound Handler
	// Kill Graphic Handler
	
	pKeyboard->Unacquire();
	pKeyboard->Release();
	pDI->Release();
	pDI = NULL;
	
	if(pDS)
	{
		pDS->Release();
	}
	
	
}
// Break the Loop and kill this Program
void MasterXHWND::Kill()
{
	alive = false;
	SendMessage(hwnd,WM_CLOSE,0,0);
}


// Get Current Screen
MASTERSCREEN MasterXHWND::GetScreen()
{
	return mscr;
}
// Set the Screen
void MasterXHWND::SetScreen(MASTERSCREEN xmscr)
{
	mscr = xmscr;
}

// Send a Message to the HWND current iniilized
LRESULT MasterXHWND::SendMasterMessage(UINT msg,WPARAM wParam,LPARAM lParam)
{
	
	return SendMessage(hwnd,msg,wParam,lParam);
}
// Master Clear Screen
void MasterXHWND::clear()
{
	ZeroMemory(&ddbltfx,sizeof(ddbltfx));
	ddbltfx.dwSize = sizeof(ddbltfx);
	ddbltfx.dwFillColor = 0;
	scr.lpBack->Blt(NULL,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&ddbltfx);
}

// Manual MasterX Update (Buffer Flip)
void MasterXHWND::mx_update()
{
	
	HRESULT ddrval;
	ddrval = scr.lpFront->Flip(NULL, DDFLIP_WAIT);
	
	if(ddrval == DD_OK)
	{
	}
	else
	{
		scr.lpFront->Restore();
	}
}
// initilize Input
void MasterXHWND::initInput()
{
	DirectInputCreate(GetModuleHandle(NULL),DIRECTINPUT_VERSION,(struct IDirectInputA**)&pDI,NULL);
	
	pDI->CreateDevice(GUID_SysKeyboard,&pKeyboard,NULL);
	pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	
	// Set the cooperative level 
	pKeyboard->SetCooperativeLevel(hwnd, 
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
	pKeyboard->Acquire();
}

// set primary surfaces
bool MasterXHWND::setprimarysurface()
{
	
	DDSURFACEDESC ddsd;
	DDSCAPS ddscaps;
	HRESULT ddrval;
	
	memset(&ddsd,0,sizeof(ddsd)); // ok were filling out a surface description
	ddsd.dwSize = sizeof(ddsd); // then using createsurface
	// to attach it to the global surface
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	ddsd.dwBackBufferCount = 1;
	
	ddrval = scr.lpDD->CreateSurface(&ddsd,&scr.lpFront,NULL);
	if(ddrval != DD_OK)
	{
        scr.lpDD->Release();
		return false;
	}
	
	// Set the description for backbuffer
	
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	ddrval = scr.lpFront->GetAttachedSurface(&ddscaps, &scr.lpBack);
	if(ddrval != DD_OK)
	{
		
		scr.lpFront->Release();
		scr.lpDD->Release();
		return false;
	}
	
	return true;
}

// init sound
bool MasterXHWND::initSound()
{
	HRESULT h;
	
	h = DirectSoundCreate(NULL, &pDS, NULL);
	if (h != DS_OK)
		return FALSE;
	
	HWND hWnd = GetForegroundWindow();
	if (hWnd == NULL)
		hWnd = GetDesktopWindow();
	
	h = pDS->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);
	if (h != DS_OK)
	{	pDS->Release();
	pDS = NULL;
	return FALSE;
	}
	
	IDirectSoundBuffer *lpDsb;
	DSBUFFERDESC		dsbdesc;
	
	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;
	
	if (pDS->CreateSoundBuffer(&dsbdesc, &lpDsb, NULL) != DS_OK)
	{	pDS->Release();
	pDS = NULL;
	return FALSE;
	}
	lpDsb->Play(0, 0, DSBPLAY_LOOPING);
	
	return TRUE;
}
// Load a Graphic 
bool MasterXHWND::LoadGraphic(MasterGraphic* g,char* filename)
{
	return g->LoadGraphic(filename,&scr);
}
// load 

// Load a Sound
bool MasterXHWND::LoadSound(MasterSound* s,LPCSTR resourceID)
{
	return s->LoadSound(pDS,resourceID);
}
// Check a keystate via DirectInput
bool MasterXHWND::KeyCheck(int key)
{
	BYTE	state[256];
	pKeyboard->GetDeviceState(sizeof(state), &state);
	
	if(state[key] & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// get mouse pos through windows api
void MasterXHWND::GetMousePosWin(long& x, long& y)
{
	POINT point;
	GetCursorPos(&point);
	x = point.x;
	y = point.y;
}

// Check a keystate via Windows
bool MasterXHWND::AsyncKeyCheck(int key)
{
	if(GetAsyncKeyState(key))
	{
		return true;
	}
	else
	{
		return false;
	}
}
// create a font, to use with the text object
HFONT MasterXHWND::CreateMasterFont(char* font_name,int size)
{
	// make a font
	return 
		
		CreateFont(size,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,font_name);
}
// create timer by, id and interval
void MasterXHWND::InitTimer(int id, int interval)
{
	SetTimer(hwnd,id,interval,NULL);
}
// destroy the timer by id
void MasterXHWND::DestroyTimer(int id)
{
	KillTimer(hwnd,id);
}
// hide the cursor
void MasterXHWND::HideCursor()
{
	ShowCursor(false);
}
// show the cursor
void MasterXHWND::RestoreCursor()
{
	ShowCursor(true);
}
// has time changed?
bool MasterXHWND::TimeChange()
{
	if(pre_time == timer_count)
	{
		return false;
	}
	else
	{
		pre_time = timer_count;
		return true;
	}
}
// change the time
void MasterXHWND::ChangeTime()
{
	timer_count++;
	
	if(timer_count > 100)
	{
		timer_count = 0;
	}
}
// auto set time change
void MasterXHWND::SetTimeFlag()
{
	time_flag = TimeChange();
}
// insync update
bool MasterXHWND::SyncChange()
{
	return time_flag;
}


/***** Master Text Object *****************************************/
// set the default font back agian & shit
// set the default font
void MasterText::setdefaultfont()
{
	font = CreateFont(13,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Arial");
}


//init master text object
void MasterText::init(MasterScreen* x)
{
	
	scr = (MasterScreen*)x;
	font = CreateFont(13,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Arial"); //  Create a Stupid Font
	
	underfont = CreateFont(13,
        0, 0, 0, FW_NORMAL, FALSE, TRUE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Arial"); //  Create a Stupid Font
	
	bk = TRANSPARENT;
	text = RGB(255,0,0);
	
}
// set the font
void MasterText::setfont(HFONT f)
{
    font = f;
	
}
// set ud
void MasterText::setunderfont(HFONT f)
{
	underfont = f;
}
// set the bg color (RGB)
void MasterText::setbkcolor(COLORREF f)
{
	
	bk = f;
	
}
// set the textcolor
void MasterText::settextcolor(COLORREF f)
{
	
	text = f;
	
}
// print text
void FAST MasterText::printtext(char* strtext, int x, int y)
{
	
	HDC dc;
    scr->lpBack->GetDC(&dc);
	
	SetTextColor(dc,text);
	SetBkColor(dc,bk);
	
	if(font != NULL)
	{
		SelectObject(dc, font);
	}
	
	TextOut(dc,x,y,strtext,strlen(strtext));
	
	scr->lpBack->ReleaseDC(dc);
	
	
	
}

void FAST MasterText::sprinttext(int x, int y, char* str, ...)
{
	va_list list; 
	char string[5000];
	va_start(list, str); 
	vsprintf((char*)string,str,list);
	va_end(list); 
	printtext(string,x,y);
	
}

// printtextrect stream
void FAST MasterText::printtextrectf(int x, int y, int x2, int y2, char* str, ...)
{
	va_list list; 
	char string[5000];
	va_start(list, str); 
	vsprintf((char*)string,str,list);
	va_end(list); 
	printtextrect(string,x,y,x2,y2);
}

// print formated text within a rectangle
void FAST MasterText::printtextrect(char* strtext, int x, int y, int w, int h)
{
	RECT rt;
	SetRect(&rt,x,y,w,h);
	
	HDC dc;
    scr->lpBack->GetDC(&dc);
	
	SetTextColor(dc,text);
	SetBkColor(dc,bk);
	
	if(font != NULL)
	{
		SelectObject(dc, font);
	}
	
	DrawText(dc,strtext,strlen(strtext),&rt,DT_EDITCONTROL);
	
	scr->lpBack->ReleaseDC(dc);
	
	
	
}
// print text with a underline
void FAST MasterText::printtextunderline(char* strtext, int x, int y)
{
	HDC dc;
    scr->lpBack->GetDC(&dc);
	
	SetTextColor(dc,text);
	SetBkColor(dc,bk);
	
	if(underfont != NULL)
	{
		SelectObject(dc, underfont);
	}
	
	TextOut(dc,x,y,strtext,strlen(strtext));
	
	scr->lpBack->ReleaseDC(dc);
	
}


//************************************* GRAPHIC OBJECT ***************************************/

MasterGraphic::~MasterGraphic()
{
	if(surf != NULL)
	{
		surf->Release();
		surf = NULL;
	}
}

MasterGraphic::MasterGraphic()
{
	ckey = false;
	surf = NULL;
	scr  = NULL;
}
// Release a exisiting MasterX Graphic
void MasterGraphic::Release()
{
	if(surf)
	{
		surf->Release();
	}
}
// Display Graphic ex (display a area of the bitmap)
void MasterGraphic::DisplayGraphicEx(int bx, int by, int bw, int bh,int image_x, int image_y)
{
	HRESULT ddrval;
	RECT     rcRect;
	
	SetRect(&rcRect,bx,by,bw,bh);
	
	if(surf)
	{
		
		if(ckey)
		{
			ddrval= scr->lpBack->BltFast(image_x, image_y, surf,&rcRect, DDBLTFAST_SRCCOLORKEY);
			
			if(ddrval != DD_OK)
			{
				ReLoadGraphic();
			}
		}
		else
		{
			ddrval = scr->lpBack->BltFast(image_x,image_y,surf,&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
			if(ddrval != DD_OK)
			{
				ReLoadGraphic();
			}
		}
	}
}


// Display a exisiting MasterX Graphic
void MasterGraphic::DisplayGraphic(int x, int y)
{
	HRESULT ddrval;
	RECT     rcRect;
	
	SetRect(&rcRect,0,0,w,h);
	
	if(surf)
	{
		
		if(ckey)
		{
			ddrval= scr->lpBack->BltFast(x, y, surf,&rcRect, DDBLTFAST_SRCCOLORKEY);
			
			if(ddrval != DD_OK)
			{
				ReLoadGraphic();
			}
		}
		else
		{
			
			ddrval = scr->lpBack->BltFast(x,y,surf,&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
			if(ddrval != DD_OK)
			{
				ReLoadGraphic();
			}
		}
	}
}
// initilize the Screen Data structure
void MasterGraphic::init(MasterScreen* xscr)
{
	scr = xscr;
}
// Load MasterX Graphic
bool MasterGraphic::LoadGraphic(char* filenamex, MasterScreen* scrx)
{
	scr = scrx;
	strcpy(filename,filenamex);
	return LoadGraphic(filename);
}
// Reload the Graphic when Destroyed
void MasterGraphic::ReLoadGraphic()
{
	DDReLoadBitmap(surf,filename);
}
// Load the Graphic, if you already initilized a screen
bool MasterGraphic::LoadGraphic(char* filenamex)
{
	strcpy(filename,filenamex);
	if(scr != NULL)
	{
		surf = DDLoadBitmap(scr->lpDD,filename);
		if(surf) 
		{
			w = MXWIDTH; // from static global
			h = MXHEIGHT; // from static global
			
			return true;
			
		}
		else
		{
			return false;
		}
	} else
	{
		return false;// no screen initilized
	}
}


// Set a Color key to this graphic
void MasterGraphic::SetColorKey(COLORREF r)
{
	if(surf)
	{
		
		DDSetColorKey(surf,r);
		ckey = true;
		
	}
}

/***************************** THE PAITNING OBJECT ******************************************/
// initlize the MasterPaint
void MasterPaint::init(MasterScreen* xscr)
{
	scr = xscr;
}
// set a pixel
void FAST MasterPaint::mxsetpixel(int x, int y, COLORREF rgbval)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	SetPixel(dc, x, y, rgbval);  
	scr->lpBack->ReleaseDC(dc);
}
// draw a vertical line
void FAST MasterPaint::mxverticalline(int y1,int y2,int x,COLORREF color)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	for(int i = y1; i <=y2; i++)
	{
		
		SetPixel(dc, x, i, color);
		
	}
	scr->lpBack->ReleaseDC(dc);
}
// draw a horizontal line
void FAST MasterPaint::mxhorizontalline(int x1, int x2, int y,COLORREF color)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	for(int i = x2; i>=x1; i--)
	{
		
		SetPixel(dc, i, y, color);
		
	}
	scr->lpBack->ReleaseDC(dc);
}
// draw a line from any 2 points, algorithm orignaly written by
// Bresenham, in 1950
void FAST MasterPaint::mxline(int start_x,int start_y,int stop_x, int stop_y,COLORREF color)
{
	int y_unit,x_unit;
	int ydiff = stop_y-start_y;
	if(ydiff<0)
	{
		ydiff = ydiff;
		y_unit=-1;
	}
	else
	{
		y_unit =1;
	}
	int xdiff=stop_x-start_x;
	if(xdiff<0)
	{
		xdiff=-xdiff;
		x_unit = -1;
	}
	else
	{
		x_unit = 1;
	}
	
	// drawing
	
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
	
	int error_term=0;
	if(xdiff>ydiff)
	{
		int length=xdiff+1;
		for(int i = 0; i <length; i++)
		{
			SetPixel(dc,start_x,start_y,color);
			start_x += x_unit;
			error_term+=ydiff;
			if(error_term>xdiff)
			{
				error_term-=xdiff;
				start_y+=y_unit;
			}
		}
	}
	else
	{
		int length = ydiff+1;
		for(int i = 0; i < length; i++)
		{
			SetPixel(dc,start_x,start_y,color);
			start_y += y_unit;
			error_term+=xdiff;
			if(error_term>0)
			{
				error_term-=ydiff;
				start_x += x_unit;
			}
			
		}
	}
	
	scr->lpBack->ReleaseDC(dc);
}

// get the color of a pixel
COLORREF FAST MasterPaint::mxgetpixel(int x, int y)
{
	COLORREF rgbval;
	HDC dc;
	scr->lpBack->GetDC(&dc);
	rgbval = GetPixel(dc, x, y);     // Save current pixel value
	scr->lpBack->ReleaseDC(dc);
	return rgbval;
}

// draw an arc
void FAST MasterPaint::mxarc(int x1, int x2, int x3, int x4,int x5, int x6,int x7, int x8,COLORREF fill,COLORREF outline)
{
	
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
	   HBRUSH hNewBrush,hOldBrush;
	   HPEN hNewPen,hOldPen; 
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill);
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   Arc(dc,x1,x2,x3,x4,x5,x6,x7,x8);
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); 
	   DeleteObject(hNewPen); 
	   scr->lpBack->ReleaseDC(dc);
}

// draw a line
void FAST MasterPaint::mxlineto(int x, int y,COLORREF fill,COLORREF outline)
{
	
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
    HBRUSH hNewBrush,hOldBrush;
    HPEN hNewPen,hOldPen; 
	   
    hNewBrush = (HBRUSH)CreateSolidBrush(fill);
    hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
    hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
    hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	LineTo(dc,x,y);
	   
	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);
	
	DeleteObject(hNewBrush); 
	DeleteObject(hNewPen); 
	scr->lpBack->ReleaseDC(dc);
}

// draw a angle arc
void FAST MasterPaint::mxanglearc(int x, int y, long radius, float startangle,float sweepangle,COLORREF outline)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
    HBRUSH hNewBrush,hOldBrush;
    HPEN hNewPen,hOldPen; 
	COLORREF fill = RGB(0,0,0); // null colored brush
    hNewBrush = (HBRUSH)CreateSolidBrush(fill);
    hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
    hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
    hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	AngleArc(dc,x,y,radius,startangle,sweepangle);
	   
	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);
	
	DeleteObject(hNewBrush); 
	DeleteObject(hNewPen); 
	scr->lpBack->ReleaseDC(dc);
}

// draw a polygon
void FAST MasterPaint::mxpolygon(CONST POINT* point,int n_points,COLORREF fill,COLORREF outline)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
	   HBRUSH hNewBrush,hOldBrush;
	   HPEN hNewPen,hOldPen; 
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill);
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   Polygon(dc,point,n_points);
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); 
	   DeleteObject(hNewPen); 
	   scr->lpBack->ReleaseDC(dc);
}


// Draw a Rectangle
void FAST MasterPaint::mxdrawrect(int x, int y, int xx, int yy, COLORREF fill, COLORREF outline)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
	   HBRUSH hNewBrush,hOldBrush;
	   HPEN hNewPen,hOldPen; 
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill);
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   Rectangle(dc,x,y,xx,yy); // Draw a rectangle
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); 
	   DeleteObject(hNewPen); 
	   scr->lpBack->ReleaseDC(dc);
}
// Draw a rectangle
void FAST MasterPaint::mxdrawroundrect(int x, int y, int x2, int y2, int cw, int ch, COLORREF fill,COLORREF outline)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
	HBRUSH hNewBrush,hOldBrush;// new Brush to paint with and one thats current (so we can restore)
	   HPEN hNewPen,hOldPen; // New pen to paint with and the current (so we can restore)
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill); // create this brush
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   
	   RoundRect(dc,x,y,x2,y2,cw,ch);
	   
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush);
	   DeleteObject(hNewPen); // i dont need this sso lets KILL It
	   scr->lpBack->ReleaseDC(dc);
}
// draw a circle (pie)
void FAST MasterPaint::mxdrawpie(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2, COLORREF fill,COLORREF 
								 
								 outline)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
	HBRUSH hNewBrush,hOldBrush;// new Brush to paint with and one thats current (so we can restore)
	   HPEN hNewPen,hOldPen; // New pen to paint with and the current (so we can restore)
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill); // create this brush
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   
	   Pie(dc,x,y,x2,y2,nx,ny,nx2,ny2);
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); 
	   DeleteObject(hNewPen); 
	   scr->lpBack->ReleaseDC(dc);
}
// draw chord
void FAST MasterPaint::mxdrawchord(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2,COLORREF fill,COLORREF 
								   
								   outline)
{
	   HDC dc;
	   scr->lpBack->GetDC(&dc);
	   
       HBRUSH hNewBrush,hOldBrush;// new Brush to paint with and one thats current (so we can restore)
	   HPEN hNewPen,hOldPen; // New pen to paint with and the current (so we can restore)
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill); // create this brush
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   Chord(dc,x,y,x2,y2,nx,ny,nx2,ny2);
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); 
	   DeleteObject(hNewPen);
	   scr->lpBack->ReleaseDC(dc);
}
// draw ellipse
void FAST MasterPaint::mxdrawellipse(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline)
{
	   HDC dc;
	   scr->lpBack->GetDC(&dc);
	   
       HBRUSH hNewBrush,hOldBrush;// new Brush to paint with and one thats current (so we can restore)
	   HPEN hNewPen,hOldPen; // New pen to paint with and the current (so we can restore)
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill); // create this brush
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   Ellipse(dc,x,y,x2,y2);
	   
	   
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); 
	   DeleteObject(hNewPen); 
	   scr->lpBack->ReleaseDC(dc);
}

//*********************** MASTER SOUND OBJECT ***********************************************/

MasterSound::MasterSound()
{
	pSound = NULL;
}

MasterSound::~MasterSound()
{
	if(sound_ok)
	{
		
		if(pSound)
		{
			pSound->Release();
		}
		
	}
}

// Load a Sound
bool MasterSound::LoadSound(IDirectSound *pds,LPCSTR name)
{
	if(sound_ok)
	{
		
		
		pSound = DSLoadSoundBuffer(pds,name);
		
		if(pSound)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}
	
	return false;
}
// Play the Sound
void MasterSound::Play()
{
	if(sound_ok)
	{
		
		
		if(pSound)
		{
			pSound->Play(0,0,0);
		}
		
	}
}
// Play status of Sound (is it Playing?)
bool MasterSound::PlayStatus()
{
	if(sound_ok) {
		DWORD status;
		pSound->GetStatus(&status);
		
		if(status & DSBSTATUS_PLAYING)
		{ 
			return true;
		} 
		else 
		{
			return false;
		}
		
		return false;
		
	}
	
	else {
		
		
		return false;
	}
}

void MasterSound::Release()
{
	if(pSound)
	{
		pSound->Release();
	}
}


//************** NON CLASS RELATED FUNCTION **************************************************/
// DirectDraw Load Bitmap (to surface)
IDirectDrawSurface* DDLoadBitmap(IDirectDraw* pdd, LPCSTR szBitmap)
{
	
	HBITMAP hbm;
	BITMAP bm;
	IDirectDrawSurface *pdds;
	
	// Load Image for loading from Disk
	
	hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	
	
	if(hbm == NULL) { return NULL; }
	
	GetObject(hbm, sizeof(bm), &bm); // size
	
	
	// Create Surface for this Bitmap
	
	int cw = bm.bmWidth;
	int ch = bm.bmHeight;
	
	MXWIDTH = cw;
	MXHEIGHT = ch;
	
	
	pdds = CreateOffScreenSurface(pdd, bm.bmWidth,bm.bmHeight);
	
	if(pdds)
	{
		
		DDCopyBitmap(pdds, hbm, bm.bmWidth,bm.bmHeight);
	}
	
	
	DeleteObject(hbm);
	
	return pdds;
	
}

mxbitmap DDLoadBitmapX(IDirectDraw* pdd, LPCSTR szBitmap)
{
	
	HBITMAP hbm;
	BITMAP bm;
	IDirectDrawSurface *pdds;
	
	// Load Image for loading from Disk
	
	hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	mxbitmap xbm;
	
	
	
	if(hbm == NULL) { xbm.surf = NULL; return xbm; }
	
	GetObject(hbm, sizeof(bm), &bm); // size
	
	
	// Create Surface for this Bitmap
	
	int cw = bm.bmWidth;
	int ch = bm.bmHeight;
	
	pdds = CreateOffScreenSurface(pdd, bm.bmWidth,bm.bmHeight);
	
	if(pdds)
	{
		
		DDCopyBitmap(pdds, hbm, bm.bmWidth,bm.bmHeight);
	}
	
	
	DeleteObject(hbm);
	
	xbm.surf = pdds;
	xbm.w = cw;
	xbm.h = ch;
	
	return xbm;
	
}
// this is a surface when can be cliped 
IDirectDrawSurface* CreateOffScreenSurface(IDirectDraw* pdd, int dx, int dy)
{
	
	DDSURFACEDESC ddsd;
	IDirectDrawSurface* pdds;
	
	// Create Surface for this bitmap
	
	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth = dx;
	ddsd.dwHeight = dy;
	
	if(pdd->CreateSurface(&ddsd, &pdds,NULL) != DD_OK)
	{
		return NULL;
		
	} else {
		
		return pdds;
		
	}
	
}
// Copy Bitmap
HRESULT DDCopyBitmap(IDirectDrawSurface* pdds, HBITMAP hbm, int dx, int dy)
{
	
	HDC hdcImage;
	HDC hdc;
	HRESULT hr;
	HBITMAP hbmOld;
	
	// Select Bitmap into a MemoryDC 
	
	hdcImage = CreateCompatibleDC(NULL);
	hbmOld = (HBITMAP)SelectObject(hdcImage, hbm);
	
	if((hr = pdds->GetDC(&hdc)) == DD_OK)
	{
		
		BitBlt(hdc,0,0,dx,dy,hdcImage,0,0,SRCCOPY);
		pdds->ReleaseDC(hdc);
	}
	
	SelectObject(hdcImage, hbmOld);
	DeleteDC(hdcImage);
	
	return hr;
	
}

// Wav Data
static const TCHAR c_szWAV[] = {"WAVE"};

///////////////////////////////////////////////////////////////////////////////
//
// DSLoadSoundBuffer
//
///////////////////////////////////////////////////////////////////////////////

IDirectSoundBuffer *DSLoadSoundBuffer(IDirectSound *pDS, LPCTSTR lpName)
{
	IDirectSoundBuffer *pDSB = NULL;
	DSBUFFERDESC dsBD = {0};
	BYTE *pbWaveData;
	
	if (DSGetWaveResource(NULL, lpName, &dsBD.lpwfxFormat, &pbWaveData, &dsBD.dwBufferBytes))
	{
		dsBD.dwSize = sizeof(dsBD);
		dsBD.dwFlags = DSBCAPS_STATIC | DSBCAPS_GETCURRENTPOSITION2;
		
		if (SUCCEEDED(pDS->CreateSoundBuffer(&dsBD, &pDSB, NULL)))
		{
			if (!DSFillSoundBuffer(pDSB, pbWaveData, dsBD.dwBufferBytes))
			{
				pDSB->Release();
				pDSB = NULL;
			}
		}
		else
		{
			pDSB = NULL;
		}
	}
	
	return pDSB;
}

///////////////////////////////////////////////////////////////////////////////
//
// DSReloadSoundBuffer
//
///////////////////////////////////////////////////////////////////////////////

BOOL DSReloadSoundBuffer(IDirectSoundBuffer *pDSB, LPCTSTR lpName)
{
	BOOL result=FALSE;
	BYTE *pbWaveData;
	DWORD cbWaveSize;
	
	if (DSGetWaveResource(NULL, lpName, NULL, &pbWaveData, &cbWaveSize))
	{
		if (SUCCEEDED(pDSB->Restore()) &&
			DSFillSoundBuffer(pDSB, pbWaveData, cbWaveSize))
		{
			result = TRUE;
		}
	}
	
	return result;
}

///////////////////////////////////////////////////////////////////////////////
//
// DSGetWaveResource
//
///////////////////////////////////////////////////////////////////////////////

BOOL DSGetWaveResource(HMODULE hModule, LPCTSTR lpName,
					   WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, DWORD *pcbWaveSize)
{
	HRSRC hResInfo;
	HGLOBAL hResData;
	void *pvRes;
	
	if (((hResInfo = FindResource(hModule, lpName, c_szWAV)) != NULL) &&
		((hResData = LoadResource(hModule, hResInfo)) != NULL) &&
		((pvRes = LockResource(hResData)) != NULL) &&
		DSParseWaveResource(pvRes, ppWaveHeader, ppbWaveData, pcbWaveSize))
	{
		return TRUE;
	}
	
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BOOL DSFillSoundBuffer(IDirectSoundBuffer *pDSB, BYTE *pbWaveData, DWORD cbWaveSize)
{
	if (pDSB && pbWaveData && cbWaveSize)
	{
		LPVOID pMem1, pMem2;
		DWORD dwSize1, dwSize2;
		
		if (SUCCEEDED(pDSB->Lock(0, cbWaveSize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0)))
		{
			CopyMemory(pMem1, pbWaveData, dwSize1);
			
			if ( 0 != dwSize2 )
				CopyMemory(pMem2, pbWaveData+dwSize1, dwSize2);
			
			pDSB->Unlock(pMem1, dwSize1, pMem2, dwSize2);
			return TRUE;
		}
	}
	
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BOOL DSParseWaveResource(void *pvRes, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData,DWORD *pcbWaveSize)
{
	DWORD *pdw;
	DWORD *pdwEnd;
	DWORD dwRiff;
	DWORD dwType;
	DWORD dwLength;
	
	if (ppWaveHeader)
		*ppWaveHeader = NULL;
	
	if (ppbWaveData)
		*ppbWaveData = NULL;
	
	if (pcbWaveSize)
		*pcbWaveSize = 0;
	
	pdw = (DWORD *)pvRes;
	dwRiff = *pdw++;
	dwLength = *pdw++;
	dwType = *pdw++;
	
	if (dwRiff != mmioFOURCC('R', 'I', 'F', 'F'))
		goto exit;		// not even RIFF
	
	if (dwType != mmioFOURCC('W', 'A', 'V', 'E'))
		goto exit;		// not a WAV
	
	pdwEnd = (DWORD *)((BYTE *)pdw + dwLength-4);
	
	while (pdw < pdwEnd)
	{
		dwType = *pdw++;
		dwLength = *pdw++;
		
		switch (dwType)
		{
		case mmioFOURCC('f', 'm', 't', ' '):
			if (ppWaveHeader && !*ppWaveHeader)
			{
				if (dwLength < sizeof(WAVEFORMAT))
					goto exit;		// not a WAV
				
				*ppWaveHeader = (WAVEFORMATEX *)pdw;
				
				if ((!ppbWaveData || *ppbWaveData) &&
					(!pcbWaveSize || *pcbWaveSize))
				{
					return TRUE;
				}
			}
			break;
			
		case mmioFOURCC('d', 'a', 't', 'a'):
			if ((ppbWaveData && !*ppbWaveData) ||
				(pcbWaveSize && !*pcbWaveSize))
			{
				if (ppbWaveData)
					*ppbWaveData = (LPBYTE)pdw;
				
				if (pcbWaveSize)
					*pcbWaveSize = dwLength;
				
				if (!ppWaveHeader || *ppWaveHeader)
					return TRUE;
			}
			break;
		}
		
		pdw = (DWORD *)((BYTE *)pdw + ((dwLength+1)&~1));
	}
	
exit:
	return FALSE;
}

HRESULT
DDSetColorKey(IDirectDrawSurface * pdds, COLORREF rgb)
{
    DDCOLORKEY              ddck;
	
    ddck.dwColorSpaceLowValue = DDColorMatch(pdds, rgb);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}


DWORD
DDColorMatch(IDirectDrawSurface * pdds, COLORREF rgb)
{
    COLORREF                rgbT;
    HDC                     hdc;
    DWORD                   dw = CLR_INVALID;
    DDSURFACEDESC          ddsd;
    HRESULT                 hres;
	
    //
    //  Use GDI SetPixel to color match for us
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        rgbT = GetPixel(hdc, 0, 0);     // Save current pixel value
        SetPixel(hdc, 0, 0, rgb);       // Set our value
        pdds->ReleaseDC(hdc);
    }
    //
    // Now lock the surface so we can read back the converted color
    //
    ddsd.dwSize = sizeof(ddsd);
    while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING)
        ;
    if (hres == DD_OK)
    {
        dw = *(DWORD *) ddsd.lpSurface;                 // Get DWORD
        if (ddsd.ddpfPixelFormat.dwRGBBitCount < 32)
            dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount) - 1;  // Mask it to bpp
        pdds->Unlock(NULL);
    }
    //
    //  Now put the color that was there back.
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        SetPixel(hdc, 0, 0, rgbT);
        pdds->ReleaseDC(hdc);
    }
    return dw;
}

HRESULT
DDReLoadBitmap(IDirectDrawSurface * pdds, LPCSTR szBitmap)
{
    HBITMAP                 hbm;
    HRESULT                 hr;
	
    //
    //  Try to load the bitmap as a resource, if that fails, try it as a file
    //
    hbm = (HBITMAP) LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, 0,
		0, LR_CREATEDIBSECTION);
    if (hbm == NULL)
        hbm = (HBITMAP) LoadImage(NULL, szBitmap, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (hbm == NULL)
    {
        OutputDebugString("handle is null\n");
        return E_FAIL;
    }
	
	hr = DDCopyBitmap2(pdds, hbm, 0, 0, 0, 0);
	
	
	if (hr != DD_OK)
    {
        OutputDebugString("ddcopybitmap failed\n");
    }
    DeleteObject(hbm);
    return hr;
}

HRESULT
DDCopyBitmap2(IDirectDrawSurface * pdds, HBITMAP hbm, int x, int y,
			  int dx, int dy)
{
    HDC                     hdcImage;
    HDC                     hdc;
    BITMAP                  bm;
    DDSURFACEDESC          ddsd;
    HRESULT                 hr;
	
    if (hbm == NULL || pdds == NULL)
        return E_FAIL;
    //
    // Make sure this surface is restored.
    //
    pdds->Restore();
    //
    // Select bitmap into a memoryDC so we can use it.
    //
    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)
        OutputDebugString("createcompatible dc failed\n");
    SelectObject(hdcImage, hbm);
    //
    // Get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);
    dx = dx == 0 ? bm.bmWidth : dx;     // Use the passed size, unless zero
    dy = dy == 0 ? bm.bmHeight : dy;
    //
    // Get size of surface.
    //
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    pdds->GetSurfaceDesc(&ddsd);
	
    if ((hr = pdds->GetDC(&hdc)) == DD_OK)
    {
        StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y,
			dx, dy, SRCCOPY);
        pdds->ReleaseDC(hdc);
    }
    DeleteDC(hdcImage);
    return hr;
}

// ****** misc

HFONT MakeFont(char* ftype, int size)
{
	return 
		
		CreateFont(size,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,ftype);
}

//*********

// ************************************* MASTERSOCKET

// initilze windows sockets
void initwinsock()
{
	
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 1, 1 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		MessageBox(0,"Error Couldnt Init Winsock!","Aborting",MB_ICONINFORMATION);
		PostQuitMessage(0);
		return;
	}
	
	
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 ) {
		WSACleanup( );
		return;   
		
	}
}

// killwinsock, on lcose
void killwinsock()
{
	WSACleanup();
}

// the master socket data structure
void MasterSocket::CreateSocket(HWND hwndx, UINT SOCKET_IDx)
{
	hwnd = hwndx;
	SOCKET_ID = SOCKET_IDx;
	socketx = socket(AF_INET,SOCK_STREAM,0);
	WSAAsyncSelect(socketx,hwnd,SOCKET_ID,FD_CONNECT|FD_READ|FD_CLOSE|FD_ACCEPT);
}

// begin listening
void MasterSocket::Listen(UINT port)
{
	if(port == DEFAULT_PORT) { port = 7; }
	struct sockaddr_in addy;
	// begin watching on port 7
	addy.sin_family = AF_INET;
	addy.sin_port = htons(port);
	addy.sin_addr.s_addr = INADDR_ANY; //inet_addr("172.129.243.252");
   	bind(socketx,(struct sockaddr*)&addy,sizeof(addy));
	listen(socketx,5);
}
// connect to a remote socket
void MasterSocket::Connect(char* ipaddress,UINT port)
{
	struct sockaddr_in addy2;
	if(port == DEFAULT_PORT) { port = 7; }
	
	addy2.sin_family = AF_INET;
	addy2.sin_port = htons(port);
	addy2.sin_addr.s_addr = inet_addr(ipaddress);
	connect(socketx,(struct sockaddr*)&addy2,sizeof(addy2));
}
// accept a request from remote socket
void MasterSocket::Accept()
{
	struct sockaddr cli_addr;
    int clilen;
	clilen = sizeof(cli_addr);
	socketx = accept(socketx,(struct sockaddr*)&cli_addr,&clilen);
}

// send data once socket is connected
void MasterSocket::Send(char* buff, int len)
{
	send(socketx,buff,len,0);
}
// recive data from a connected socket
int MasterSocket::Recive(char* buff,int len)
{
	return recv(socketx,buff,len,0);
}
// get the ID of a given socket, for the wndproc callback
const UINT MasterSocket::GetID()
{
	return (const UINT)SOCKET_ID;
}
// close an open socket
void MasterSocket::Close()
{
	closesocket(socketx);
}
//***********
// MasterJoyStick

// return how many joysticks there are
unsigned int MasterJoyStick::GetJoysticks()
{
	return joyGetNumDevs();
}
// does joysticks exisit
bool MasterJoyStick::JoyExisit()
{
	joystickInfoEx.dwSize = sizeof(JOYINFOEX);
	joystickPresent = (joyGetPosEx(JOYSTICKID1,&joystickInfoEx) == JOYERR_NOERROR);
	if(!joystickPresent)
	{
		return false;
	}
	
	return true;
}
// setup this joystick
bool MasterJoyStick::SetupJoystick()
{
	if(JoyExisit() == false)
	{
		return false;
	}
	
	joyGetDevCaps(JOYSTICKID1,&joystickCaps,sizeof(joystickCaps));
	joystickHasThrottle = (joystickCaps.wCaps & JOYCAPS_HASZ);
	int joystickDeadSize = (joystickCaps.wXmax - joystickCaps.wXmin) * JOY_DEADZONE / 100;
	joystickDeadXMax = (joystickCaps.wXmax - joystickCaps.wYmin) / 2 + (joystickDeadSize / 2);
	joystickDeadXMin = joystickDeadXMax - joystickDeadSize;
	joystickDeadSize = (joystickCaps.wYmax - joystickCaps.wYmin) * JOY_DEADZONE / 100;
	joystickDeadYMax = (joystickCaps.wYmax - joystickCaps.wYmin) / 2 + (joystickDeadSize / 2);
	joystickDeadYMin = joystickDeadYMax - joystickDeadSize;
	return true;
}
// get joystick cordinates
bool MasterJoyStick::GetJoystickCoords(JOYINFOEX* info)
{
	if(!joystickPresent) return false;
	info->dwSize  = sizeof(JOYINFOEX);
	info->dwFlags = JOY_RETURNX | JOY_RETURNY;
	return (!joyGetPosEx(JOYSTICKID1,info));
}
// is the joystick still
bool MasterJoyStick::JoyStop()
{
	if(!GetJoystickCoords(&joystickInfoEx)) return false;
	return (( joystickInfoEx.dwYpos > joystickDeadYMin) && (joystickInfoEx.dwYpos < joystickDeadYMax) &&
		(joystickInfoEx.dwXpos > joystickDeadXMin) &&
		(joystickInfoEx.dwXpos < joystickDeadXMax));
}

// is the joystick being pressed forward (UP)
bool MasterJoyStick::JoyForward()
{
	if(!GetJoystickCoords(&joystickInfoEx)) return false;
	return (joystickInfoEx.dwYpos < joystickDeadYMin);
}
// is the joystick being pressed backwards (DOWN)
bool MasterJoyStick::JoyBackward()
{
	if(!GetJoystickCoords(&joystickInfoEx)) return false;
	return(joystickInfoEx.dwYpos > joystickDeadYMax);
}
// is the joystick being pressed left 
bool MasterJoyStick::JoyLeft()
{
	if(!GetJoystickCoords(&joystickInfoEx)) return false;
	return(joystickInfoEx.dwXpos < joystickDeadXMin);
}
// is the joystick being pressed right
bool MasterJoyStick::JoyRight()
{
	if(!GetJoystickCoords(&joystickInfoEx)) return false;
	return (joystickInfoEx.dwXpos > joystickDeadXMax);
}
// get the currently pressed button
int MasterJoyStick::GetButtonPressed(JOYINFOEX* info)
{
	if(!joystickPresent) { return 0; }
	
	info->dwSize = sizeof(joystickInfoEx);
	info->dwFlags =  JOY_RETURNBUTTONS;
	joyGetPosEx(JOYSTICKID1,info);
	int x = info->dwButtonNumber;	
	return x;
}

// get the pressed button
int MasterJoyStick::JoyButtonDown()
{
	return GetButtonPressed(&joystickInfoEx);
}

//**********************************************************************************


// ENTRY
int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR l,int CmdShow)
{
	return MasterMain(hInst,l);
}


#endif
#endif

// MasterLib not compatible with newer library of functions
// it includes MasterString, and the AOLCPP for simple AOL 3-5 manipulation
// enjoy !
// requires no special entry point


#ifdef MASTERLIB

#include <windows.h>
#include <string.h>
#include <fstream.h>
#include <iostream.h>
#include <ctime>

// enumerated constants 

enum AOLVER { NOAOL = 0, AOL2, AOL3, AOL4, AOL5, AOL6 };
enum AOLTYPE {ICON, LISTBOX, TREE, VIEW, RICHCNTL, STATIC,GLYPH, IMAGE, CHECKBOX};

// Important Functions
void cppDoEvents();
HWND FindWindowLike_Class(HWND Parent, char* Class); // Just Class
HWND FindWindowLike_Title(HWND Parent, char* Title); // Just Title
#define NOTFOUND -1
#define INULL    -1
#define NOPREV   -1
#define NULLI    -1
#define STRBEGIN -1
#define MRANGE_HI 1
#define MRANGE_LO 0
#define NULLPOS  -1

// string algorithims
void stringcopy(char* dest,char* from); // string copy
void stringattach(char* dest,char* from); // string attach
void leftcopy(char* from,char* dest,int pos);// left copy (leftstr)
void rightcopy(char* from,char* dest,int pos);// right copy (rightstr)
void midcopy(char* from,char* dest,int start_pos,int stop_pos);// middle copy (midstr)
void trimspace(char* buff);// trim space characters
int findstr(char* buffer,char* search);// find string search
int ifindstr(int i,char* buffer,char* search);// find string search from position
int findstrb(char* buffer,char* search); // backwards search
int ifindstrb(int i,char* buffer,char* search); // inside backwards search
int fsearchstr(int start,int stop,char* buff,char* search);// fully controled range search (forward)
int bsearchstr(int start,int stop,char* buff,char* search);// fully controled range search (backward)
void removestr(char* buff,char* str);// remove instances of str in buff
int getlen(char* buff);// get length of the string
void lcase(char* buff);// lower case string
void ucase(char* buff);// upper case string
int  lcasel(int c);// lower case letter
int  ucasel(int c);// upper case letter
int  findoccurance(char* buff,char* search);// find occourances of a specific string
void convertinteger(int integer,char* buff,int base); // convert integer to string
int  convertstring(char* buff); // convert string to integer
bool ishexc(char c);// is this character a hexidecimal digit?
bool ishex(char* buff);// is this string a hexidecimal value?
int  hextointc(char c);// hexidecimal digit to integer value
int  hextoint(char* buff); // hexidecimal digits to integer value
int findoccourance(char* buff,char* search);// find the numeric of times a string occours
void tripcharup(char* buff,int upby);// bump the digits up X times
void tripchardown(char* buff,int downby);// dump the digits down  X times
void replacechar(char* string,char findchr,char replace);// replace single character, through out all instances
void replacestr(char* string,char* findstr,char* rep,char* output);// replace string inside string
void rmvinst(char* buff,char* findstr,char* replace,char* output); // remove single instance of string
char randomchar(int max);// produce a random character
char randomchar(int max,int up);// produce a random character, and then make it + up
void randomstr(char* buff,int char_max,int char_size);// random string
void removechar(char* input,char* output,char c); // remove characters from buffer
int  findchar(char* str,char c);// find single char (forward)
int  ifindchar(int start,char* str,char c); // inside find single char (forward)
int  findcharb(char* str,char c);// find single char (backward)
int  ifindcharb(int start,char* str,char c); // find single char backward ex
int  findcharcf(char* str,int start,int stop,char c);// find single char controled forward
int  findcharcb(char* str,int start,int stop,char c);// find single char controled backward
void removestr(char* input,char* output,char* string); // remove instance of string
void rmvstrx(char* buff,char* output,char* string); // remove single instance of string
void strsavefile(char* filename,char* string);// save the string as a text file
int  getfilestringlength(char* filename);// get the string length of a text file
bool strloadfile(char* filename,char* output);// load a string from a text file
void reversestring(char* input,char* output); // reverse sring
bool isstrvalid(char* string); // checks to see if the string is valid or not (is null terminated)
// string compares
bool mstrcmp(char* buff1,char* buff2); // case sensitive compare
bool mstrcmpx(char* buff1,char* buff2);// not case sensitive compare
bool insidestr(char* buff1,char* buff2); // am i inside this string?
bool insidestrx(char* buff1,char* buff2);// am i inside this string lowercased ?
void strsep(char* str, char* sleft, int go_left, char* sright, int go_right);// seperate into 2 seperate strings from 2 

seperate points
void strsetnull(char* str,int pos); // reset the 0's position
void rmvnullset(char* str); // remove the 0 to end the string
int  getnullpos(char* str); // get the position of the null
void trimcom(char* buff, char* output, char startstr,char stopstr); 
void asmtrim(char* input,char* output);
int  countlines(char* buffer); // counts how many \n characters exisit
int  getfirstletter(char* buffer); // get first letter thats not a space

// static

static char g_sn[200];
static char g_msg[200];

// the structures


// api helper structure
struct APIHELP
{
	// Click a Window
	inline void Click(HWND hwnd)
	{
		SendMessage(hwnd,WM_LBUTTONDOWN,0,0);
		SendMessage(hwnd,WM_LBUTTONUP,0,0);
	}
	// Double Click a Window
	inline void DoubleClick(HWND hwnd)
	{
		SendMessage(hwnd,WM_LBUTTONDBLCLK,0,0);
	}
	// Send a KeyDown to a Window
	inline void KeyDown(HWND hwnd,char c)
	{
		SendMessage(hwnd,WM_KEYDOWN,c,0);
	}
	// Send a Key Up to a Window
	inline void KeyUp(HWND hwnd,char c)
	{
		SendMessage(hwnd,WM_KEYUP,c,0);
	}
	// Send a Key Press to a Window
	inline void KeyPress(HWND hwnd,char c)
	{
		KeyDown(hwnd,c);
		KeyUp(hwnd,c);
	}
	// Send a Close Message to a window
	inline void Close(HWND hwnd)
	{
		SendMessage(hwnd,WM_CLOSE,0,0);
	}
	// Send a SetText Message to a window
	inline void SetText(HWND hwnd,char* buff)
	{
		SendMessage(hwnd,WM_SETTEXT,strlen(buff),(LPARAM)(LPCSTR)buff);
	}
	// Send a GetText Message to a Window
	inline void GetText(HWND hwnd,char* buff)
	{
		int len;
		len = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
		SendMessage(hwnd,WM_GETTEXT,len+1,(LPARAM)(LPCSTR)buff);
	}
	// Send a Get List Item message to a list box
	inline void GetListText(HWND hwnd,int index,char* buff)
	{
		SendMessage(hwnd,LB_GETTEXT,index,(LPARAM)(LPCSTR)buff);
	}
	// Send a Get list Count message
	inline int  GetListCount(HWND hwnd)
	{
		return SendMessage(hwnd,LB_GETCOUNT,0,0);
	}
	// Send a Get List Current Sel message
	inline int  GetListCurSel(HWND hwnd)
	{
		return SendMessage(hwnd,LB_GETCURSEL,0,0);
	}
	// Send a Get List Cur Sel Message
	inline void SetListCurSel(HWND hwnd, int x)
	{
		SendMessage(hwnd,LB_SETCURSEL,x,0);
	}
	// Send a Add Item to List Box Message
	inline void  AddList(HWND hwnd,char* buff)
	{
		SendMessage(hwnd,LB_ADDSTRING,strlen(buff),(LPARAM)(LPCSTR)buff);
	}
	// Send a Rmv Item From listBox Message
	inline void RmvList(HWND hwnd,int x)
	{
		SendMessage(hwnd,LB_DELETESTRING,x,0);
	}
	// pause the application (doesnt freeze) :)
	inline void Pause(double breaktime)
	{
		double wTime = time(NULL) + breaktime;
        while (time(NULL) <= wTime){ cppDoEvents(); }
	}
	// click a button
	inline void ButtonClick(HWND hwnd)
	{
		SendMessage(hwnd, WM_KEYDOWN, VK_SPACE, NULL);
		SendMessage(hwnd, WM_KEYUP, VK_SPACE, NULL);
	}
	// for this window to appear
	inline void WaitForWindow(char* window_class,char* window_title)
	{
		while(FindWindow(window_class,window_title) == 0)
		{
			cppDoEvents();
		}
	}
	// wait for this window to appear ex
	inline void WaitForWindowEx(HWND hwnd,HWND hwnd2,LPCSTR l1,LPCSTR l2)
	{
		while(FindWindowEx(hwnd,hwnd2,l1,l2) == 0)
		{
			cppDoEvents();
		}
	}
	// wait for a window like this to appear
	inline void WaitForWindowLike_Title(HWND parent,char* title)
	{
		while(FindWindowLike_Title(parent,title) == 0)
		{
			cppDoEvents();
		}
	}
	// wait for a window like this to appear
	inline void WaitForWindowLike_Class(HWND parent,char* winclass)
	{
		while(FindWindowLike_Class(parent,winclass) == 0)
		{
			cppDoEvents();
		}
	}
	// compare to windows, are they the same ?
	inline bool WindowCompare(HWND hwnd,HWND hwnd2)
	{
		if(hwnd == hwnd2)
		{
			return true;
		}
		
		return false;
	}
	// is this window handle valid?
	inline bool isValidHandle(HWND hwnd)
	{
		if(hwnd == 0)
		{
			return false;
		}
		
		return true;
	}
	// Show this window
	inline void ShowWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_SHOW);
	}
	// Hide this Window
	inline void HideWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_HIDE);
	}
	// Minimize this Window
	inline void MiniWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_MINIMIZE);
	}
	// Maximize this Window
	inline void MaxWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_MAXIMIZE);
	}
	// restore this window
	inline void RestoreWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_RESTORE);
	}
	// send a menu command
	inline void SendMenuCommand(HWND hwnd,int cmd)
	{
		
		SendMessage(hwnd,WM_COMMAND,cmd,NULL);
	}
};


// the AOLCPP base object
struct AOLCPPOBJ : APIHELP
{
	// Find AOL Window Handle
	inline HWND FindAOL()
	{
		return FindWindow("AOL Frame25",NULL);
	}
	// Find the AOL MDI Handle
	inline HWND FindMDI()
	{
		return FindWindowEx(FindAOL(),0,"MDIClient",NULL);
	}
	// Get the users Screen Name
	inline void GetScreenName(char* buff)
	{
		if(FindAOL() == 0)
		{
			strcpy(buff,"AOL Not Found");
			return;
		}
		
		HWND welw;
		welw = FindWindowLike_Title(FindMDI(),"Welcome,");
		
		if(welw == 0)
		{
			strcpy(buff,"Not signed On");
			return;
		}
		
		char temp[50];
		SendMessage(welw,WM_GETTEXT,50,(LPARAM)(LPCSTR)temp);
		int fc = findstr(temp,",");
		int fi = findstr(temp,"!");
		midcopy(temp,buff,fc+2,fi);
		
	}
	// Get The Version of AOL They are running
	inline AOLVER GetAOLVersion()
	{
		if(isAOLOpen() == false)
		{
			return NOAOL;
		}
		
		HMENU mnu = GetAOLMenu();
		HMENU msub = GetSubMenu(mnu,NULL);
		int subi;
		subi = GetMenuItemID(msub,8);
		
		char stritem[100];
		GetMenuString(msub, subi, stritem, 100, 1);
		if(findstr(stritem,"&Logging...") != -1)
		{
			return AOL2;
		}
		if(findstr(stritem,"P&ersonal Filing Cabinet") != -1)
		{
			return AOL3;
		}
		
		msub = GetSubMenu(mnu,4);
		subi = GetMenuItemID(msub,9);
        GetMenuString(msub, subi, stritem, 100, 1);
		
		if(findstr(stritem,"4.0") != -1)
		{
			return AOL4;
		}
		if(findstr(stritem,"5.0") != -1)
		{
			return AOL5;
		}
		
		msub = GetSubMenu(mnu,5);
		subi = GetMenuItemID(msub,8);
		GetMenuString(msub, subi, stritem, 100, 1);
		
		if(findstr(stritem,"6.0") != -1)
		{
			return AOL6;
		}
		
		return NOAOL;
	}
	// Find a AOL Child Window
	inline HWND FindAOLChild(char* title)
	{
		return FindWindowEx(FindMDI(),0,"AOL Child",title);
	}
	// Find A AOL Child Window Like
	inline HWND FindAOLChildLike(char* title)
	{
		return FindWindowLike_Title(FindMDI(),title);
	}
	// Get The AOL Menu Handle
	inline HMENU GetAOLMenu()
	{
		return GetMenu(FindAOL());
	}
	// Close AOL
	inline void CloseAOL()
	{
		Close(FindAOL());
	}
	// is the user signed on ?
	inline bool SignedOn()
	{
		if(FindWindowLike_Title(FindMDI(),"Welcome,") == 0)
		{
			return false;
		}
		return true;
	}
	// is the user signed off ?
	inline bool SignedOff()
	{
		if(FindWindowLike_Title(FindMDI(),"Goodbye from") == 0)
		{
			return false;
		}
		return true;
	}
	// is AOL Open?
	inline bool isAOLOpen()
	{
		if(FindAOL())
		{
			return true;
		}
		
		return false;
	}
	// close all the children 
	inline void CloseAllChildren()
	{
		while(1)
		{
			HWND win;
			win = FindWindowEx(FindMDI(),0,"AOL Child",0);
			if(win == 0)
			{
				break;
			}
			else
			{
				Close(win);
			}
			cppDoEvents();
		}
	}
	// kill all the modal windows 
	inline void KillModal()
	{
		if(FindWindow("_AOL_Modal",NULL))
		{
			while(1)
			{
				HWND f;
				f = FindWindow("_AOL_Modal",NULL);
				if(f == 0)
				{
					break;
				}
				Close(f);
				
				cppDoEvents();
			}
		}
	}
	// kill all aol message boxs
	inline void KillAOLMessage()
	{
		
		HWND mod;
		mod = FindWindow("#32770", "America Online");
		if(mod == 0)
		{
			return;
		}
		while(1)
		{
			mod = FindWindow("#32770", "America Online");
			if(mod == 0)
			{
				break;
			}
			Close(mod);
			cppDoEvents();
		}
		
	}
	// special search for AOL Child Windows 
	inline HWND GetAolWindow(HWND parent, AOLTYPE aolchild, int num)
	{
		if(parent == 0) { return 0; } // No Parent 
		int count = 1;
		if(num == 0) { return 0; }
		
		HWND win;
		win = GetWindow(GetWindow(parent, GW_CHILD), GW_HWNDFIRST);
		//.ICON, LISTBOX, TREE, VIEW, RICHCNTL, STATIC,GLYPH, IMAGE, CHECKBOXICON, LISTBOX, TREE, VIEW, RICHCNTL, 
		
		STATIC,GLYPH, IMAGE, CHECKBOX
			char aolclass[50];
		
		switch(aolchild)
		{
		case ICON:
			strcpy(aolclass, "_AOL_Icon");
			break;
		case LISTBOX:
			strcpy(aolclass, "_AOL_Listbox");
			break;
		case TREE:
			strcpy(aolclass, "_AOL_Tree");
			break;
		case VIEW:
			strcpy(aolclass, "_AOL_View");
			break;
		case RICHCNTL:
			strcpy(aolclass, "RICHCNTL");
			break;
		case STATIC:
			strcpy(aolclass, "_AOL_Static");
			break;
		case GLYPH:
			strcpy(aolclass, "_AOL_Glyph");
			break;
		case IMAGE:
			strcpy(aolclass, "_AOL_Image");
			break;
		case CHECKBOX:
			strcpy(aolclass, "_AOL_Checkbox");
			break;
		}
		
		
		while(win != 0)
		{
			
			char buff[100];
			GetClassName(win,buff,100);
			if(strstr(buff,aolclass))
			{
				
				if(count == num) {
					return win; } else { count++; }
			}
			
			win = GetWindow(win, GW_HWNDNEXT);
			
		}
		
		
		return  0;
	}
    // up chat
	inline void UpChat()
	{
		HWND modal;
		modal = FindWindow("_AOL_Modal",NULL);
		char buff[255];
		SendMessage(modal,WM_GETTEXT,255,(LPARAM)(LPCSTR)buff);
		
		if((strstr(buff, "File")) || (strstr(buff, "Send")))
		{
			
			EnableWindow(FindWindow("AOL Frame25",NULL),1);
			ShowWindow(modal, SW_MINIMIZE);
			
		}
		
	}
    // un up chat
	inline void UnUpChat()
	{
		
		HWND modal;
		modal = FindWindow("_AOL_Modal",NULL);
		char buff[255];
		SendMessage(modal,WM_GETTEXT,255,(LPARAM)(LPCSTR)buff);
		
		if((strstr(buff, "File")) || (strstr(buff, "Send")))
		{
			
			EnableWindow(FindWindow("AOL Frame25",NULL),1);
			ShowWindow(modal, SW_RESTORE);
			
		}
		
	}
	
	// send a wm_command, to aitem in the aol menu by id
	inline void AOLMenuInvokeByID(int id)
	{
		SendMenuCommand(FindAOL(),id);
	}
    // run a item, off the AOL menu 
	inline void RunMenu(int menu_over,int menu_down)
	{
		HMENU aolmenu;
        aolmenu = GetAOLMenu();
		HMENU sub;
        sub = GetSubMenu(aolmenu, menu_over);
        int sub2;
        sub2 = GetMenuItemID(sub, menu_down);
        SendMessage(FindAOL(), WM_COMMAND, sub2,NULL);
	}
	// set aol's caption
	inline void SetAOLCaption(char* buffer)
	{
		SetText(FindAOL(),buffer);
	}
	// get aol's caption
	inline void GetAOLCaption(char* buffer)
	{
		GetText(FindAOL(),buffer);
	}
	// get the chat window (ethier 3.0 or 4.0)
	inline HWND GetChatWindow()
	{
		
		HWND win;
		win = GetWindow(GetWindow(FindMDI(), GW_CHILD), GW_HWNDFIRST);
		
		
		while(win != 0)
		{
			
			char buff[500];
			GetClassName(win, buff, 500);
			
			
			if(strstr(buff,"AOL Child"))
			{
				
				HWND list;
				HWND combo;
				HWND stat;
				HWND rich;
				HWND view;
				list = FindWindowEx(win,NULL, "_AOL_Listbox",NULL);
				combo = FindWindowEx(win,NULL, "_AOL_Combobox",NULL);
				stat = FindWindowEx(win,NULL, "_AOL_Static",NULL);
				rich = FindWindowEx(win,NULL, "RICHCNTL",NULL);
				view = FindWindowEx(win,NULL, "_AOL_View",NULL);
				if((list) && (combo) && (stat) && (rich))
				{
					
					return win;
				}
				if((list) && (stat) && (view)) { return win; }
			}
			
			win = GetWindow(win, GW_HWNDNEXT);
			
		}
		
		return 0;
		
	}
	// get the chat view (3.0 or 5.0)
	inline HWND GetChatView()
	{
		HWND Wnd;
		HWND chat;
		chat = GetChatWindow();
		Wnd  = FindWindowEx(chat,NULL, "_AOL_View",NULL);
		if(Wnd == 0) 
		{
			Wnd = FindWindowEx(chat,NULL, "RICHCNTL",NULL);
		}
		
		return Wnd;
	}
	// is user in a chat room?
	inline bool IsUserChatting()
	{
		if(GetChatWindow()) { return true; }
		
		return false;
	}
	
	// send text to ethier 3.0 or 4.0/5.0
	inline void SendText(char* str)
	{
		HWND chat;
		chat  =  GetChatWindow();
		HWND edit;
		HWND button;
		HWND rich;
		char text[300];
		char temp[300];
		char a[1] = "";
		edit = FindWindowEx(chat,NULL, "_AOL_Edit",NULL);
		button = GetNextWindow(edit, 2);
		
		if(edit == 0) 
		{
			//bad way of doing it
			/*edit = GetWindow(GetWindow(chat, GW_CHILD), GW_HWNDFIRST);
			
			  edit = GetNextWindow(edit, 2);
			  edit = GetNextWindow(edit, 2);
			  edit = GetNextWindow(edit, 2);
			  edit = GetNextWindow(edit, 2);
			  edit = GetNextWindow(edit, 2);
			  edit = GetNextWindow(edit, 2);
			  edit = GetNextWindow(edit, 2);
			edit = GetNextWindow(edit, 2);*/
			
			//good way	   
			rich = GetAolWindow(GetChatWindow(), RICHCNTL,2); 
			button = GetNextWindow(rich,2);
		}
		SendMessage(rich, WM_GETTEXT,300,(LPARAM)(LPCSTR) temp);
		SendMessage(rich, WM_SETTEXT,1, (LPARAM)(LPCSTR) a);
		SendMessage(rich, WM_SETTEXT,300, (LPARAM)(LPCSTR) str);
		SendMessage(rich, WM_CHAR ,  13, 0);
		
		SendMessage(rich, WM_GETTEXT,300,(LPARAM)(LPCSTR) text);
		while(strstr(text,str))
		{
			Click(button);
			SendMessage(rich, WM_GETTEXT,300,(LPARAM)(LPCSTR) text);
		}
		
		SendMessage(rich, WM_SETTEXT,300, (LPARAM)(LPCSTR) temp);
		
	}
	
	// get welcome window
	inline HWND GetWelcome()
	{
		return FindWindowLike_Title(FindMDI(),"Welcome,");
	}
	// get the buddy list window
	inline HWND GetBuddyList()
	{
		return FindWindowLike_Title(FindMDI(),"Buddy List");
	}
	
};


// the AOLCPP object for AOL 3.0
struct AOLCPP_3 : AOLCPPOBJ 
{
private:
	
	void (*ChatScan)(char* sn,char* msg);
	bool scan_set;
	int  pre_len;
	
public:
	
	// constructor
	inline AOLCPP_3()
	{
		scan_set = false;
		pre_len = -1;
	}
	
	inline ~AOLCPP_3()
	{
		
	}
	
	// is this aol3.0 ?
	inline bool isAOL30()
	{
		if(GetAOLVersion() == AOL3)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	// get the tool bar
	inline HWND GetToolBar()
	{
		
		HWND aol,toolbar;
		aol=FindWindow("AOL Frame25",NULL);
		toolbar=FindWindowEx(aol,NULL,"AOL Toolbar",NULL);
		return toolbar;
		
		return 0;
	}
	// run the toolbar 0 being first icon, 1 being second etc
	inline void RunToolBar(int b_over)
	{ 
		HWND ico;
		ico = GetAolWindow(GetToolBar(),ICON,b_over);
		Click(ico);
	}
	// open the 3.0 email box
	inline void OpenEmailBox()
	{
		RunToolBar(1); // example of toolbar run
	}
	// open a new email
	inline void OpenNewEmail()
	{
		RunToolBar(2); // example of toolbar run
	}
	// send email 3.0
	inline void SendEmail(char* sn,char* subj,char* msg)
	{
		if(SignedOn() == false)
		{
			return;
		}
		
		OpenNewEmail();
		WaitForWindowLike_Title(FindMDI(),"Compose Mail");
		HWND mail;
		mail = FindWindowLike_Title(FindMDI(),"Compose Mail");
		HWND ed;
		ed = FindWindowEx(mail,0,"_AOL_Edit",0);
		SetText(ed,sn);
		HWND sub;
		sub = FindWindowEx(mail,0,0,"Subject:");
		sub = GetNextWindow(sub,2);
		SetText(sub,subj);
		HWND rich;
		rich = FindWindowEx(mail,0,"RICHCNTL",0);
		SetText(rich,msg);
		HWND ico;
		ico = FindWindowEx(mail,0,"_AOL_Icon",0);
		Click(ico);
	}
	// send instant message
	inline void SendInstantMessage(char* sn,char* msg)
	{
		if(SignedOn() == false)
		{
			return;
		}
		
		RunMenu(4,6);
		WaitForWindowLike_Title(FindMDI(),"Send Instant Message");
		HWND imwin;
		imwin = FindWindowLike_Title(FindMDI(),"Send Instant Message");
		HWND ed;
		ed = FindWindowEx(imwin,0,"_AOL_Edit",0);
		SetText(ed,sn);
		HWND rich;
		rich = FindWindowEx(imwin,0,"RICHCNTL",0);
		SetText(rich,msg);
		HWND ico;
		ico = GetNextWindow(rich,2);
		Click(ico);
		
		while(true)
		{
			HWND eim;
			HWND emsg;
			eim = FindWindowLike_Title(FindMDI(),"Send Instant Message");
			if(eim == 0)
			{
				break;
			}
			emsg = FindWindow(NULL,"America Online");
			if(emsg)
			{
				Close(emsg);
				Close(eim);
				break;
			}
			
			cppDoEvents(); // so are program wont lock up
		}
	}
	
	// run the keyword
	inline void AolKeyword(char* word)
	{
		if(SignedOn() == false)
		{
			return; // they anit signed on
		}
		
		RunMenu(2,5);
		WaitForWindowLike_Title(FindMDI(),"Keyword");
		HWND kw;
		kw = FindWindowLike_Title(FindMDI(),"Keyword");
		HWND ed;
		ed = FindWindowEx(kw,0,"_AOL_Edit",0);
		SetText(ed,word);
		SendMessage(ed,WM_CHAR,13,0);
		KeyPress(ed,13);
	}
	// Set The Chat Com Scan CallBack Function
    inline void SetChatComScan(void (*ChatScanX)(char* sn,char* msg))
	{
		ChatScan = ChatScanX;
		scan_set = true;
	}
	//  Scan the chat
	inline void ChatComScan()
	{
		if(scan_set == true)
		{
			if(GetChatWindow())
			{
				
				
				int tlen;
				tlen = SendMessage(GetChatView(),WM_GETTEXTLENGTH,0,0);
				
				if(pre_len == -1)
				{
					pre_len = tlen;
					return; // first chat get
				}
				
				if(tlen == pre_len) // value is the same
				{
					return;
				}
				
				char chatbuff[5000];
				SendMessage(GetChatView(),WM_GETTEXT,tlen+1,(LPARAM)(LPCSTR)chatbuff);
				char newline[500];
				
				int copy_pos = pre_len;
				
				
				for(int i = tlen; i > 0; i--)
				{
					
					if(chatbuff[i] == 13)
					{
						copy_pos = i+1;
						break;
					}
					
				}
				
				rightcopy(chatbuff,newline,copy_pos);
				pre_len = tlen;
				
				char msn[100];
				char mmsg[200];
				int fcol;
				fcol = findstr(newline,":");
				leftcopy(newline,msn,fcol);
				rightcopy(newline,mmsg,fcol+3);
				ChatScan(msn,mmsg); // call users call back function
				
			}
		}
	}
	
};

// the AOLCPP object for 4.0/5.0
typedef struct AOLCPP_4 : AOLCPPOBJ
{
private:
	void (* ChatScan)(char* sn,char* msg);
	bool scan_set;
	int  pre_len;
	
public:
	
	// constructor
	inline AOLCPP_4()
	{
		scan_set = false;
		pre_len = -1;
	}
	
	// deconstructor
	inline ~AOLCPP_4()
	{
		
	}
	
    // get 4.0 toolbar
	inline HWND GetToolBar()
	{
		HWND tool;
		tool = FindWindowEx(FindAOL(),0,"AOL Toolbar",0);
		HWND Tool;
		Tool = FindWindowEx(tool,0,"_AOL_Toolbar",0);
		return Tool;
	}
	// run a icon in the toolbar
	inline void RunToolBar(int tool_over)
	{
		HWND tool;
		tool = GetToolBar();
		HWND ico;
		ico = GetAolWindow(tool,ICON,tool_over);
		Click(ico);
	}
	// Open there Email Box
	inline void OpenEmailBox()
	{
		RunToolBar(1);
	}
	
	// Open up a new Send Email
	inline void OpenNewEmail()
	{
		RunToolBar(2);
	}
	
	// is there email Box open ?
	inline bool isMailOpen()
	{
		HWND mb;
		mb = FindWindowLike_Title(FindMDI(),"Online MailBox");
		if(mb == 0)
		{
			return false;
		}
		
		return true;
	}
	// send email 4.0/5.0
	inline void SendEmail(char* sn,char* subj,char* msg)
	{
		if(SignedOn() == false)
		{
			return; // no signed on
		}
		
		OpenNewEmail();
		WaitForWindowLike_Title(FindMDI(),"Write Mail");
		HWND mail;
		mail = FindWindowLike_Title(FindMDI(),"Write Mail");
		HWND ed;
		ed = FindWindowEx(mail,0,"_AOL_Edit",0);
		SetText(ed,sn);
		HWND ed2;
		ed2 = GetNextWindow(ed,2);
		ed2 = GetNextWindow(ed2,2);
		ed2 = GetNextWindow(ed2,2);
		ed2 = GetNextWindow(ed2,2);
		SetText(ed2,subj);
		HWND ri;
		ri = FindWindowEx(mail,0,"RICHCNTL",0);
		SetText(ri,msg);
		HWND ico;
		ico = GetAolWindow(mail,ICON,16);
		Click(ico);
		
	}
	
	// keyword
	inline void AolKeyword(char* buff)
	{
		if(SignedOn() == false)
		{
			return; // there signed off
		}
		HWND kw;
		kw = FindWindowEx(GetToolBar(),0,"_AOL_ComboBox",0);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		Click(kw);
		WaitForWindowLike_Title(FindMDI(),"Keyword");
		HWND kww;
		kww = FindWindowLike_Title(FindMDI(),"Keyword");
		HWND ed;
		ed = FindWindowEx(kww,0,"_AOL_Edit",0);
		SetText(ed,buff);
		HWND ico;
		ico = FindWindowEx(kww,0,"_AOL_Icon",0);
		Click(ico);
	}
	// get chat room text 4.0/5.0
	inline void GetChatText(char* buff)
	{
		HWND view = GetChatView();
		int len;
		len = SendMessage(view,WM_GETTEXTLENGTH,0,0);
		SendMessage(view,WM_GETTEXT,len,(LPARAM)(LPCSTR)buff);
	}
	
	// scan if the callback function is set
	inline void ChatComScan()
	{
		if(scan_set == true)
		{
			if(GetChatWindow())
			{
				
				
				int tlen;
				tlen = SendMessage(GetChatView(),WM_GETTEXTLENGTH,0,0);
				
				if(pre_len == -1)
				{
					pre_len = tlen;
					return; // first chat get
				}
				
				if(tlen == pre_len) // value is the same
				{
					return;
				}
				
				char chatbuff[5000];
				SendMessage(GetChatView(),WM_GETTEXT,tlen+1,(LPARAM)(LPCSTR)chatbuff);
				char newline[500];
				
				int copy_pos = pre_len;
				
				
				for(int i = tlen; i > 0; i--)
				{
					
					if(chatbuff[i] == 13)
					{
						copy_pos = i+1;
						break;
					}
					
				}
				
				rightcopy(chatbuff,newline,copy_pos);
				pre_len = tlen;
				
				char msn[100];
				char mmsg[200];
				int fcol;
				fcol = findstr(newline,":");
				leftcopy(newline,msn,fcol);
				rightcopy(newline,mmsg,fcol+3);
				ChatScan(msn,mmsg); // call users call back function
				
			}
		}
	}
	// initlize the callback function for a chat scan
	inline void SetChatComScan( void (*ChatScanX)(char* sn, char* msg))
	{
		ChatScan = ChatScanX;
		scan_set = true;
	}
	// get mail box
	inline HWND GetMailBox()
	{
		return FindWindowLike_Title(FindMDI(),"Online MailBox");
	}
	
	// dump aol mail box to a hwnd
	inline void GetAOLMailBox(HWND hwnd)
	{
		HWND mail;
		mail = GetMailBox();
		HWND mail_tree;
		mail_tree = FindWindowEx(mail,0,"_AOL_Tree",0);
		
		int l_len;
		l_len = SendMessage(mail_tree,LB_GETCOUNT,0,0);
		for(int i = 0; i < l_len; i++)
		{
			char curitem[200];
			SendMessage(mail_tree,LB_GETTEXT,200,(LPARAM)(LPCSTR)curitem);
			SendMessage(hwnd,LB_ADDSTRING,200,(LPARAM)(LPCSTR)curitem);
		}
		
	}
	
	// send a aol 4.0 instant message
	inline void SendInstantMessage(char* sn,char* msg)
	{
		HWND buddylist;
		buddylist = GetBuddyList();
		if(buddylist == 0)
		{
			return; // no buddy list found :(
		}
		
		HWND iim;
		iim = FindWindowEx(buddylist,0,0,"IM");
		iim = GetNextWindow(iim,2);
		Click(iim);
		
		WaitForWindowLike_Title(FindMDI(),"Send Instant Message");
		
		HWND im;
		im = FindWindowLike_Title(FindMDI(),"Send Instant Message");
		HWND ed;
		ed = FindWindowEx(im,0,"_AOL_Edit",0);
		SetText(ed,sn);
		HWND rich;
		rich = FindWindowEx(im,0,"RICHCNTL",0);
		SetText(rich,msg);
		HWND ico;
		ico = GetNextWindow(rich,2);
		Click(ico);
		
		while(true) // loop to see if stuff went succesfully
		{
			HWND eim;
			HWND emsg;
			eim = FindWindowLike_Title(FindMDI(),"Send Instant Message");
			
			if(eim == 0)
			{
				break;
			}
			
			emsg = FindWindow(NULL,"America Online");
			if(emsg)
			{
				Close(emsg); // error message
				Close(eim);
				break;
			}
			
			cppDoEvents(); // make sure are program dont lock up
		}
		
		
	}
	
	// turn ghosting on
	inline void GhostOn()
	{
		if(SignedOn() == false)
		{
			return; // there not signed on !
		}
		
		HWND bud;
		bud = GetBuddyList();
		if(bud == 0)
		{
			return; // they anit got no buddy list open 
		}
		HWND set;
		set = FindWindowEx(bud,0,0,"Setup");
		set = GetNextWindow(set,2);
		Click(set);
		WaitForWindowLike_Title(FindMDI(),"'s Buddy List");
		HWND budwin;
		budwin = FindWindowLike_Title(FindMDI(),"'s Buddy List");
		HWND ico;
		ico = GetAolWindow(budwin,ICON,5);
		Click(ico);
		WaitForWindowLike_Title(FindMDI(),"Privacy Pref");
		HWND pref;
		pref = FindWindowLike_Title(FindMDI(),"Privacy Pref");
		HWND chk;
		chk = FindWindowEx(pref,0,"_AOL_Checkbox",0);
		chk = GetNextWindow(chk,2);
		chk = GetNextWindow(chk,2);
		chk = GetNextWindow(chk,2);
		chk = GetNextWindow(chk,2);
		Click(chk);
		HWND icogo;
		icogo = FindWindowEx(pref,0,"_AOL_Edit",0);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		Click(icogo);
		Click(icogo);
		WaitForWindow(NULL,"America Online");
		HWND a;
		a = FindWindow(NULL,"America Online");
		Close(a);
		Close(budwin); // all done
	}
	// turn ghosting off
	inline void GhostOff()
	{
		if(SignedOn() == false)
		{
			return; // there not signed on !
		}
		
		if(SignedOn() == false)
		{
			return; // there not signed on !
		}
		
		HWND bud;
		bud = GetBuddyList();
		if(bud == 0)
		{
			return; // they anit got no buddy list open 
		}
		HWND set;
		set = FindWindowEx(bud,0,0,"Setup");
		set = GetNextWindow(set,2);
		Click(set);
		WaitForWindowLike_Title(FindMDI(),"'s Buddy List");
		HWND budwin;
		budwin = FindWindowLike_Title(FindMDI(),"'s Buddy List");
		HWND ico;
		ico = GetAolWindow(budwin,ICON,5);
		Click(ico);
		WaitForWindowLike_Title(FindMDI(),"Privacy Pref");
		HWND pref;
		pref = FindWindowLike_Title(FindMDI(),"Privacy Pref");
		HWND chk;
		chk = FindWindowEx(pref,0,"_AOL_Checkbox",0);
		Click(chk);
		HWND icogo;
		icogo = FindWindowEx(pref,0,"_AOL_Edit",0);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		Click(icogo);
		Click(icogo);
		WaitForWindow(NULL,"America Online");
		HWND a;
		a = FindWindow(NULL,"America Online");
		Close(a);
		Close(budwin); // all done
		
	}
	
	
	
}AOLCPP_5;



// ***********************************************************************************************
// *********************************** MasterString - Simple, and Explicit String Manipluation



// string data location structure use w/ (findstrl)
struct MasStrDataLoc
{
	int* dindex;
	int  array_size;
	char* thestring;
	char* searchstr;
	bool search_status;
	
	inline MasStrDataLoc()
	{
		search_status = false;
		dindex = 0;
		array_size = 0;
		searchstr = 0;
	}
	
	inline ~MasStrDataLoc()
	{
		if(dindex != 0)
		{
			
			delete [] dindex;
			dindex = 0;
			
		}
		if(thestring != 0)
		{
			
			delete [] thestring;
			thestring = 0;
			
		}
		if(searchstr != 0)
		{
			
			delete [] searchstr;
			searchstr = 0;
			
		}
	}
	
	inline void create_array(int size)
	{
		dindex = new int[size];
		array_size = size;
	}
	
	inline void setstr(char* buff)
	{
		int len;
		len = strlen(buff);
		thestring = new char[len+1];
		stringcopy(thestring,buff);
	}
	
	inline void setstatus(bool x)
	{
		search_status = x;
	}
	
	inline void setsearchstr(char* buff)
	{
		int len;
		len = strlen(buff);
		searchstr = new char[len+1];
		stringcopy(searchstr,buff);
	}
	
	// return pointer to the string which the array holds data for
	inline char* getstr()
	{
		return thestring;
	}
	
	inline char* getsearchstr()
	{
		return searchstr;
	}
	
	inline int getarraysize()
	{
		return array_size;
	}
	
	inline int getstringpoint(int index)
	{
		if(index <= array_size)
		{
			
			return dindex[index];
			
		}
	}
	// maximum string points for search
	inline int getmaxpoint()
	{
		return array_size;
	}
	// get status
	inline bool getstatus()
	{
		return search_status;
	}
	
	inline bool wassearchsuccesful()
	{
		return getstatus();// was it succesfull?
	}
};
// find string location (dumps all locations into the location data structure (MasStrDataLoc))
bool findstrloc(char* buff,char* search,MasStrDataLoc* dloc);// standard
bool findstrlocf(char* buff,char* search,MasStrDataLoc* dloc);// forward
bool findstrlocb(char* buff,char* search,MasStrDataLoc* dloc);// backward

// master string range structure
struct MasStrRange
{
	int start_x;
	int stop_y;
	
	inline MasStrRange()
	{
		start_x = 0;
		stop_y = 0;
	}
	
	inline void SetRange(int x, int y)
	{
		start_x = x;
		stop_y = y;
	}
	
	inline int GetRangeX()
	{
		return start_x;
	}
	
	inline int GetRangeY()
	{
		return stop_y;
	}
	
	inline int GetRangeHI()
	{
		return start_x;
	}
	
	inline int GetRangeLO()
	{
		return stop_y;
	}
	
	inline int Clear()
	{
		start_x = 0;
		stop_y = 0;
	}
};

// range search structures for range style string manipulation
bool searchrange(char* buff,char* search,MasStrRange* mrang);
void copyleftrange(char* input,char* output,MasStrRange* mrang, int hi_lo);
void copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo);
void copymidrange(char* input,char* output,MasStrRange* mrang, int hi_lo,MasStrRange* mrangx, int hi_lox);
bool isearchrange(int startx, char* buff,char* search,MasStrRange* mrang);

// master string list structure string data
struct MasStrList_String
{
	char* thestring;
	
	inline ~MasStrList_String()
	{
		delete [] thestring;
	}
	
	inline void set(char* buff)
	{
		int len;
		len = strlen(buff) + 1;
		thestring = new char[len];
		stringcopy(thestring,buff);
	}
	
	inline char* get()
	{
		return thestring;
	}
};
// master string list , list handler structure
struct MasStrList
{
	MasStrList_String* strings;
	int list_size;
	
	inline ~MasStrList()
	{
		delete [] strings;
	}
	
	inline MasStrList(int list_size)
	{
		create(list_size);
	}
	
	inline MasStrList()
	{
		list_size = 0;
		strings = NULL;
	}
	
	inline void create(int list_sizez)
	{
		list_size = list_sizez;
		strings = new MasStrList_String[list_size];
	}
	
	inline char* getstr(int index)
	{
		return strings[index].get();
	}
	
	inline int getcount()
	{
		return list_size;
	}
};

// create string list
void createstrlist(char* buffer, char* list_marker,MasStrList* list);


// charwrap  easy to use char array, that automaticly removes itself from freestore
struct charwrap
{
	char* str;
	
	inline charwrap(int size)
	{
		str = new char[size];
	}
	
	inline charwrap(char* buff)
	{
		set(buff);
	}
	
	inline charwrap(char* buff,bool x)
	{
		set(buff);
		strclearn();
	}
	
	inline ~charwrap()
	{
		delete [] str; // delete that shit
	}
	
	inline void set(char* buff)
	{
		int len;
		len = strlen(buff) + 1;
		str = new char[len];
		stringcopy(str,buff);
	}
	
	inline void snew(int size)
	{
		str = new char[size];
	}
	
	// clear off freestore
	inline void clear()
	{
		delete [] str;
		str = NULL;
	}
	
	inline void strclear()
	{
		int len;
		len = getlen(str);
		
		for(int i = 0; i < len; i++)
		{
			str[i] = 0;
		}
	}
	
	inline void strclearn()
	{
		stringcopy(str,"");
	}
	
	inline char* get()
	{
		return str;
	}
	
	inline int len()
	{
		return getlen(str);
	}
	
	inline void qmsg()
	{
		MessageBox(0,str,"QMSG",MB_OK|MB_ICONINFORMATION);
	}
	
};

// structure of string manipulation algorithims to use for objects to inhert
struct MasStrObj
{
    inline void mstr_stringcopy(char* input,char* output)
	{
		stringcopy(input,output);
	}
	
	inline void mstr_stringattach(char* input,char* output)
	{
		stringattach(input,output);
	}
	
	inline void mstr_leftcopy(char* input,char* output,int pos)
	{
		leftcopy(input,output,pos);
	}
	
	inline void mstr_rightcopy(char* input,char* output,int pos)
	{
		rightcopy(input,output,pos);
	}
	
	inline void mstr_midcopy(char* input,char* output,int start_pos,int stop_pos)
	{
		midcopy(input,output,start_pos,stop_pos);
	}
	
	inline void mstr_trimspace(char* buff)
	{
		trimspace(buff);
	}
	
	inline int mstr_findstr(char* buffer,char* search)
	{
		return findstr(buffer,search);
	}
	
	inline int mstr_ifindstr(int i,char* buffer,char* search)
	{
		return ifindstr(i,buffer,search);
	}
	
	inline int mstr_findstrb(char* body,char* search)
	{
		return findstrb(body,search);
	}
	
	inline int mstr_ifindstrb(int startx,char* body,char* search)
	{
		return ifindstrb(startx,body,search);
	}
	
	inline int mstr_fsearchstr(int start,int stop,char* buff,char* search)
	{
		return fsearchstr(start,stop,buff,search);
	}
	
	inline int mstr_bsearchstr(int start,int stop,char* buff,char* search)
	{
		return bsearchstr(start,stop,buff,search);
	}
	
	inline int mstr_getlen(char* buff)
	{
		int len;
		len = strlen(buff);
		return len;
	}
	
	inline int mstr_lcase(char* buffer)
	{
		lcase(buffer);
	}
	
	inline int mstr_ucase(char* buffer)
	{
		ucase(buffer);
	}
	
	inline int mstr_ucasel(char c)
	{
		return ucasel(c);
	}
	
	inline int mstr_lcasel(char c)
	{
		return lcasel(c);
	}
	
	inline bool mstr_findstrloc(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrloc(buff,search,dloc);
	}
	
	inline bool mstr_findstrlocf(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrlocf(buff,search,dloc);
	}
	
	inline bool mstr_findstrlocb(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrlocb(buff,search,dloc);
	}
	
	inline bool mstr_searchrange(char* buff,char* search,MasStrRange* mrang)
	{
		return searchrange(buff,search,mrang);
	}
	
	inline bool mstr_isearchrange(int startx, char* buff,char* search,MasStrRange* mrang)
	{
		return isearchrange(startx,buff,search,mrang);
	}
	
	inline void mstr_copyleftrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
	{
		copyleftrange(input,output,mrang,hi_lo);
	}
	
	inline void mstr_copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
	{
		copyrightrange(input,output,mrang,hi_lo);
	}
	
	inline void mstr_copymidrange(char* input,char* output,MasStrRange* mrang,int hi_lo,MasStrRange* mrangx,int hi_lox)
	{
		copymidrange(input,output,mrang,hi_lo,mrangx,hi_lox);
	}
	
	inline int mstr_findoccourance(char* buffer,char* searchx)
	{
		return findoccourance(buffer,searchx);
	}
	
	inline void mstr_convertinteger(int integer,char* buff,int base)
	{
		convertinteger(integer,buff,base);
	}
	
	inline int mstr_convertstring(char* buff)
	{
		return convertstring(buff);
	}
	
	inline bool mstr_ishexc(char c)
	{
		return ishexc(c);
	}
	
	inline bool mstr_ishex(char* buff)
	{
		return ishex(buff);
	}
	
	inline int mstr_hextointc(char c)
	{
		return hextointc(c);
	}
	inline int mstr_hextoint(char* buff)
	{
		return hextoint(buff);
	}
	
	inline void mstr_tripchardown(char* buff,int by)
	{
		tripchardown(buff,by);
	}
	
	inline void mstr_tripcharup(char* buff, int by)
	{
		tripcharup(buff,by);
	}
	inline void mstr_replacechar(char* buff,char findchr,char replace)
	{
		replacechar(buff,findchr,replace);
	}
	inline void mstr_replacestr(char* buff,char* findstr,char* replacex,char* output)
	{
		replacestr(buff,findstr,replacex,output);
	}
	inline void mstr_rmvinst(char* buff,char* findchr,char* re,char* out)
	{
		rmvinst(buff,findchr,re,out);
	}
	
	inline char mstr_randomchar(int max)
	{
		return randomchar(max);
	}
	inline char mstr_randomchar(int max, int up)
	{
		return randomchar(max,up);
	}
	inline void mstr_randomstr(char* buff,int max, int size)
	{
		randomstr(buff,max,size);
	}
	inline void mstr_removechar(char* input,char* output,char c)
	{
		removechar(input,output,c);
	}
	inline char mstr_findchar(char* str,char c)
	{
		return findchar(str,c);
	}
	inline char mstr_ifindchar(int start,char* str,char c)
	{
		return ifindchar(start,str,c);
	}
	inline char mstr_findcharb(char* str,char c)
	{
		return findcharb(str,c);
	}
	inline char mstr_ifindcharb(int start,char* str,char c)
	{
		return ifindcharb(start,str,c);
	}
	inline char mstr_findcharcf(char* str,int start,int stop,char c)
	{
		return findcharcf(str,start,stop,c);
	}
	inline char mstr_findcharcb(char* str,int start,int stop,char c)
	{
		return findcharcb(str,start,stop,c);
	}
	inline void mstr_removestr(char* str,char* output,char* strsearch)
	{
		removestr(str,output,strsearch);
	}
	inline void mstr_removestrinstance(char* str,char* output,char* strx)
	{
		rmvstrx(str,output,strx);
	}
	inline void mstr_savestr(char* filename,char* string)
	{
		strsavefile(filename,string);
	}
	inline bool mstr_loadstr(char* filename,char* output)
	{
		return strloadfile(filename,output);
	}
	inline int  mstr_getfilestrlen(char* filename)
	{
		return getfilestringlength(filename);
	}
	inline int mstr_reversestr(char* str_input,char* str_output)
	{
		reversestring(str_input,str_output);
	}
	inline bool mstr_isstrvalid(char* str)
	{
		return isstrvalid(str);
	}
	inline bool mstr_mstrcmp(char* buff1,char* buff2)
	{
		return mstrcmp(buff1,buff2);
	}
	
	inline bool mstr_mstrcmpl(char* buff1,char* buff2)
	{
		return mstrcmpx(buff1,buff2);
	}
	
	inline bool mstr_insidestr(char* buff1,char* buff2)
	{
		return insidestr(buff1,buff2);
	}
	inline bool mstr_insidestrl(char* buff1,char* buff2)
	{
		return insidestrx(buff1,buff2);
	}
	inline void mstr_strsep(char* str,char* lstr,int lpos,char* rstr,int rpos)
	{
		strsep(str,lstr,lpos,rstr,rpos);
	}
	inline int mstr_getnullpos(char* str)
	{
		return getnullpos(str);
	}
	inline void mstr_rmvnullset(char* str)
	{
		rmvnullset(str);
	}
	inline void mstr_strsetnull(char* str,int pos)
	{
		strsetnull(str,pos);
	}
	inline void mstr_trimcom(char* input,char* output, char start_c,char stop_c)
	{
		trimcom(input,output,start_c,stop_c);
	}
	inline void mstr_asmtrim(char* input,char* output)
	{
		asmtrim(input,output);
	}
};

// the MasterString Object

struct MasterString : MasStrObj
{
	char* str;
	int array_size;
	bool str_on;
	
	/********** constructors & deconstructors ****************/
	inline MasterString()
	{
		str_on = false;
		array_size = 0;
		str = NULL;
	}
	
	inline MasterString(int size)
	{
		set(size,"");
	}
	
	inline MasterString(char* buff)
	{
		int size = strlen(buff) + 2;
		set(size,buff);
	}
	
	inline MasterString(int size,char* buff)
	{
		set(size,buff);
	}
	
	inline ~MasterString()
	{
		if(str_on)
		{
			delete [] str;
			str_on = false;
			
		}
	}
	
	/* internal functions **************************/
	inline void set(int size,char* buff)
	{
		if(str_on == false)
		{
			str = new char[size];
			str_on = true;
		}
		else
		{
			delete [] str;
			str = new char[size];
		}
		
		mstr_stringcopy(str,buff);
		array_size = size;
	}
	
	inline void add(char* buff)
	{
		int total_length = GetStringLength() + strlen(buff) + 2;
		
		if(total_length > GetStringLength())
		{
			char* ptemp;
			ptemp = new char[GetStringLength()+1];
			strcpy(ptemp,str);
			
			delete [] str;
			str = 0;// set pointer to 0 
			str = new char[total_length+2];
			strcpy(str,ptemp);
			delete [] ptemp;
			strcat(str,buff);
		}
		else
		{
			strcat(str,buff);
		}
	}
	
	inline void unset()
	{
		if(str_on == true)
		{
			delete [] str;
			str_on = false;
		}
	}
	
	inline char* get()
	{
		return str;
	}
	
	// operators *************************
	
	inline void operator=(char* buffer)
	{
		// set
		int len;
		len = strlen(buffer)+2;
		set(len,buffer);
	}
	
	inline void operator+=(char* buffer)
	{
		add(buffer);
	}
	inline void operator+=(int x)
	{
		char buffer[30];
		itoa(x,buffer,10);
		add(buffer);
	}
	
	inline void operator+=(long x)
	{
		char buffer[30];
		itoa(x,buffer,10);
		add(buffer);
	}
	
	// misc *********************************
	
	inline int GetStringLength()
	{
		return mstr_getlen(str);
	}
	
	inline char* GetCharPointer()
	{
		return str;
	}
	
	inline int FindChar(char c)
	{
		return mstr_findchar(str,c);
	}
	
	inline int FindCharEx(int pre_pos,char c)
	{
		return mstr_ifindchar(pre_pos,str,c);
	}
	inline int FindCharBackward(char c)
	{
		return mstr_findcharb(str,c);
	}
	inline int FindCharBackwardEx(int pre_pos,char c)
	{
		return mstr_ifindcharb(pre_pos,str,c);
	}
	inline int FindCharControledForward(int start,int stop,char c)
	{
		return mstr_findcharcf(str,start,stop,c);
	}
	inline int FindCharControledBackward(int start,int stop,char c)
	{
		return mstr_findcharcb(str,start,stop,c);
	}
	inline int FindString(char* search)
	{
		return mstr_findstr(str,search);
	}
	
	inline int FindStringEx(int index,char* search)
	{
		return mstr_ifindstr(index,str,search);
	}
	
	inline int FindStringBackward(char* search)
	{
		return mstr_findstrb(str,search);
	}
	inline int FindStringBackwardEx(int index,char* search)
	{
		return mstr_ifindstrb(index,str,search);
	}
	inline int FindOccourance(char* search)
	{
		return mstr_findoccourance(str,search);
	}
	inline void StringCopy(char* buff)
	{
		mstr_stringcopy(str,buff);
	}
	inline void StringAttach(char* buff)
	{
		mstr_stringattach(str,buff);
	}
	inline void StringResize(int newSize)
	{
		char* ptemp;
		ptemp = new char[strlen(str)+1];
		strcpy(ptemp,str);
		
		delete [] str;
		str = new char[newSize];
		strcpy(str,ptemp);
		delete [] ptemp;
	}
	inline void StringLeft(char* output,int pos)
	{
		mstr_leftcopy(str,output,pos);
	}
	inline void StringRight(char* output,int pos)
	{
		mstr_rightcopy(str,output,pos);
	}
	inline void StringMid(char* output,int x,int y)
	{
		mstr_midcopy(str,output,x,y);
	}
	inline void TrimSpace()
	{
		trimspace(str);
	}
	
	inline void UpperCase()
	{
		ucase(str);
	}
	inline void LowerCase()
	{
		lcase(str);
	}
	inline char ExtractChar(int index)
	{
		if(index <= GetStringLength())
		{
			return str[index];
		}
		return 0;
	}
	inline int ForwardStringSearch(int start,int stop,char* search)
	{
		return mstr_fsearchstr(start,stop,str,search);
	}
	
	inline int BackwardStringSearch(int start,int stop,char* search)
	{
		return mstr_bsearchstr(start,stop,str,search);
	}
	inline bool FindStringLocation(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrloc(str,search,dloc);
	}
	inline bool FindStringLocationF(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrlocf(str,search,dloc);
	}
	inline bool FindStringLocationB(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrlocb(str,search,dloc);
	}
	inline void SearchRange(char* search,MasStrRange* mrang)
	{
		mstr_searchrange(str,search,mrang);
	}
	inline void SearchRangeEx(int startx,char* search,MasStrRange* mrang)
	{
		mstr_isearchrange(startx,str,search,mrang);
	}
	inline void CopyLeftRange(char* output, MasStrRange* mrang,int hi)
	{
		mstr_copyleftrange(str,output,mrang,hi);
	}
	inline void CopyRightRange(char* output, MasStrRange* mrang,int hi)
	{
		mstr_copyrightrange(str,output,mrang,hi);
	}
	inline void CopyMidRange(char* output,MasStrRange* mrang,int hi, MasStrRange* mrangx,int hix)
	{
		mstr_copymidrange(str,output,mrang,hi,mrangx,hix);
	}
	
	inline int GetHexValue()
	{
		return mstr_hextoint(str);
	}
	inline int GetDecValue()
	{
		return atoi(str);
	}
	inline int ConvertToInteger()
	{
		return atoi(str);
	}
	inline bool IsHex()
	{
		return mstr_ishex(str);
	}
	
	inline void qprint()
	{
		cout << str;
	}
	inline void qmsg()
	{
		MessageBox(0,str,"QMSG",MB_ICONINFORMATION);
	}
	inline void ClearString()
	{
		for(int z = 0; z < GetStringLength(); z++)
		{
			str[z] = 0;
		}
	}
	inline void SetWindowText(HWND hwnd)
	{
		SendMessage(hwnd,WM_SETTEXT,strlen(str),(LPARAM)(LPCSTR)str);
	}
	inline void AddToList(HWND hwnd)
	{
		SendMessage(hwnd,LB_ADDSTRING,strlen(str),(LPARAM)(LPCSTR)str);
	}
	inline void AddToCombo(HWND hwnd)
	{
		SendMessage(hwnd,CB_ADDSTRING,strlen(str),(LPARAM)(LPCSTR)str);
	}
	
	inline void CopyTextFromHWND(HWND hwnd)
	{
		char* buffer;
		int len;
		len = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
		buffer = new char[len+1];
		SendMessage(hwnd,WM_GETTEXT,len,(LPARAM)(LPCSTR)buffer);
		
		set(len+1,buffer);
		
		delete [] buffer;
	}
	
	inline void AttachTextFromHWND(HWND hwnd)
	{
		char* buffer;
		int len;
		len = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
		buffer = new char[len+1];
		SendMessage(hwnd,WM_GETTEXT,len,(LPARAM)(LPCSTR)buffer);
		
		add(buffer);
		
		delete [] buffer;
	}
	inline void ReplaceCharacter(char findchr,char replace)
	{
		mstr_replacechar(str,findchr,replace);
	}
	inline void RandomizeString()
	{
		randomstr(str,255,strlen(str));
	}
	inline void ReplaceString(char* search, char* replacestr)
	{
		if(mstr_findstr(str,search) != -1)
		{
			
			char* output;
			output = new char[strlen(str)+10];
			mstr_replacestr(str,search,replacestr,output);
			set(strlen(output)+10,output);
			delete [] output;
			output = 0;
			
		}
	}
	inline void RemoveCharacters(char c)
	{
		char* output;
		output = new char[strlen(str)+10];
		mstr_removechar(str,output,c);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}
	inline void RemoveString(char* search)
	{
		if(mstr_findstr(str,search) != -1)
		{
			char* output;
			output = new char[strlen(str)+10];
			mstr_removestr(str,output,search);
			set(strlen(output)+10,output);
			delete [] output;
			output = 0;
		}
	}
	inline void RemoveSingleInstanceOfString(char* search)
	{
		if(mstr_findstr(str,search) != -1)
		{
			char* output;
			output = new char[strlen(str)+10];
			rmvstrx(str,output,search);
			set(strlen(output)+10,search);
			delete [] output;
			output = 0;
		}
	}
	inline void SaveToFile(char* filename)
	{
		mstr_savestr(filename,str);
	}
	inline void LoadStringFromFile(char* filename)
	{
		if(getfilestringlength(filename) == -1)
		{
			return; // failure file not found
		}
		
		char* temp;
		temp = new char[getfilestringlength(filename)+20];
		mstr_loadstr(filename,temp);
		set(strlen(temp)+20,temp);
		delete [] temp;
		temp = 0;
	}
	inline bool IsStringValid()
	{
		return mstr_isstrvalid(str);
	}
	
	inline int ReverseString() // reverse the string
	{
		char* temp;
		temp = new char[GetStringLength()+10];
		
		reversestring(str,temp);
		set(strlen(temp)+10,temp);
		
		delete [] temp;
		temp = 0;
	}
	
	inline bool StringCompare(char* buff)
	{
		return mstr_mstrcmp(str,buff);
	}
	inline bool StringCompare_NOCASE(char* buff)
	{
		return mstr_mstrcmpl(str,buff);
	}
	inline bool IsInsideString(char* buff)
	{
		return mstr_insidestr(str,buff);
	}
	inline bool IsInsideString_NOCASE(char* buff)
	{
		return mstr_insidestrl(str,buff);
	}
	inline void SeperateString(char* lbuff,int lpos,char* rbuff,int rpos)
	{
		mstr_strsep(str,lbuff,lpos,rbuff,rpos);
	}
	inline void AsmTrim()
	{
		// trim string as tho it were assembly language source
		char* output;
		output = new char[GetStringLength()+10];
		asmtrim(str,output);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}
	
	inline void TrimComments(char start_c,char stop_c)
	{
		char* output;
		output = new char[GetStringLength()+10];
		trimcom(str,output,start_c,stop_c);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}
};

// MasterString Item Structure 
struct ListItem
{
	int list_index;
	
	inline void setindex(int i)
	{
		list_index = i;
	}
	
	inline int getindex()
	{
		return list_index;
	}
};

struct MasterStringItem : MasterString,ListItem
{
	bool on;
	
	inline MasterStringListItem()
	{
		on = false;
	}
	
	inline void seton(bool x)
	{
		on = x;
	}
	
	inline bool geton()
	{
		return on;
	}
};

// example of a list using MasterStrings
struct MasterStringList 
{
	MasterStringItem* item;
	bool ion;
	int array_size;
	int off;
	
	inline MasterStringList()
	{
		ion = false;
		off = 0;
	}
	
	inline ~MasterStringList()
	{
		if(ion == true)
		{
			delete [] item;
			item = NULL;
		}
	}
	
	inline MasterStringList(int size)
	{
		createList(size);
	}
	
	inline void createList(int size)
	{
		item = new MasterStringItem[size];
		ion = true;
		array_size = size;
	}
	
	inline int  GetArraySize()
	{
		return array_size;
	}
	
	inline char* GetListStringPointerByIndex(int index)
	{
		return item[index].get();
	}
	
	inline int AddString(char* buffer)
	{
		item[off].set(strlen(buffer)+10,buffer);
		int xoff = off;
		off++;
		return xoff;
	}
	
	inline int GetListLength()
	{
		return off;
	}
	
	inline void GetString(int index,char* output)
	{
		strcpy(output,item[index].get());
		
	}
	
	
	inline void Clear()
	{
		for(int i = 0; i < off; i++)
		{
			item[i].ClearString();
		}
		
		off = 0;
	}
};

struct MasterEntry : ListItem
{
	MasterString name;
	MasterString value;
	bool on_switch;
	
	inline MasterEntry()
	{
		name = "";
		value = "";
		on_switch = false;
	}
	
	inline bool amion()
	{
		return on_switch;
	}
	
};

// easy to use INI object, using MasterStrings
struct MasterINI
{
	MasterEntry* masEntry;
	bool mas_on;
	int array_size;
	int off_count;
	
	// constructors/deconstructors
	
	inline MasterINI()
	{
		masEntry = 0;
		mas_on = false;
		off_count = 0;
	}
	
	inline MasterINI(int size)
	{
		set(size);
	}
	
	inline ~MasterINI()
	{
		if(mas_on)
		{
			delete [] masEntry;
			masEntry = 0;
		}
	}
	
	inline set(int size)
	{
		if(mas_on == true)
		{
			delete [] masEntry;
			masEntry = 0;
		}
		
		masEntry = new MasterEntry[size];
		mas_on = true;
		array_size = size;
		off_count = 0;
	}
	
	inline int getsize()
	{
		return array_size;
	}
	
	inline void Create(int size)
	{
		set(size);
	}
	
	inline bool AddEntry(char* name,char* value)
	{
		if(off_count < getsize())
		{
			
			
			masEntry[off_count].name = name;
			masEntry[off_count].value = value;
			masEntry[off_count].list_index = off_count;
			
			off_count++;
			return true;
		}
		
		return false;
	}
	
	inline bool GetEntry(char* name,char* output_value)
	{
		for(int i = 0; i < getsize(); i++)
		{
			if(findstr(masEntry[i].name.get(),name) != -1)
			{
				stringcopy(output_value,masEntry[i].value.get());
				return true;
			}
		}
		
		strcpy(output_value,"*NULL*");
		return false;
	}
};

bool SaveMasterINI(char* filename,MasterINI* mini); // Save INI
bool LoadMasterINI(char* filename,MasterINI* mini); // Load INI

struct MasCharList // char list based on the \n (breaks strings into lines) (for use with MasAsm)
{
	MasterString* list;
	bool list_on;
	int array_size;
	int list_len;
	
	
	inline MasCharList()
	{
		list = 0;
		list_on = false;
	}
	
	inline MasCharList(char* buff)
	{
		BuildList(buff);
	}
	
	inline ~MasCharList()
	{
		if(list_on == true)
		{
			
			delete [] list;
			list = 0;
			
		}
	}
	
	inline void BuildList(char* buff)
	{
		int size;
		size = countlines(buff) + 1;
		list = new MasterString[size];
		list_on = true;
		array_size = size;
		// format the characters into this array
		int pre_pos = 0;
		int acount = 0;
		
		while(1)
		{
			int find_x;
			find_x = ifindstr(pre_pos,buff,"\n");
			
			if(find_x == -1)
			{
				break;// all done !
			}
			
			
			char* temp;
			temp = new char[strlen(buff)+1];
			
			midcopy(buff,temp,pre_pos,find_x);
			pre_pos = find_x;
			
			// add
			list[acount] = temp;
			acount++;
			
			
			delete [] temp;
			temp = 0;
			
		}
		
		list_len = acount;
		
	}
	
	inline int GetLength()
	{
		return list_len;
	}
	
	inline MasterString* GetMasterString(int index)
	{
		return (MasterString*)&list[index];
	}
	
};


static AOLCPP_4 aol4;// aolcpp4 object
static AOLCPP_3 aol3; // aol3 object
static APIHELP  apihlp; // static apihelp
static AOLCPPOBJ aolobj; // aol object


// C++ Version of DoEvents
void cppDoEvents() 
{ 
	MSG Msg; 
	while(PeekMessage(&Msg,NULL,0,0,PM_REMOVE))
	{
		if (Msg.message == WM_QUIT)break;
		TranslateMessage(&Msg); 
		DispatchMessage(&Msg);
	} 
}   

// FindWindowLike
HWND FindWindowLike_Class(HWND Parent, char* Class)
{
	
    HWND win;
    win = GetWindow(GetWindow(Parent, GW_CHILD), GW_HWNDFIRST);
	
	
	while(win != 0)
	{
		
		char buff[500];
		GetClassName(win, buff, 500);
		
		
		
		if(strstr(buff,Class))
		{
			
			return win;
		}
		
		
		win = GetWindow(win, GW_HWNDNEXT);
		
	}
	
	return 0;
	
}

/*
FindWindowLike_Title
Synthax:

  HWND hWnd;
  hWnd = FindWindowLike_Title(ParentWindow, "Title String");
  
	
*/

HWND FindWindowLike_Title(HWND Parent, char* Title)
{
    HWND win;
    win = GetWindow(GetWindow(Parent, GW_CHILD), GW_HWNDFIRST);
	
	
	while(win != 0)
	{
		
		char buff[500];
		SendMessage(win, WM_GETTEXT,500, (LPARAM)(LPCSTR) buff);
		
		if(strstr(buff,Title))
		{
			
			return win;
		}
		
		
		win = GetWindow(win, GW_HWNDNEXT);
		
	}
	
	return 0;
	
}


/********************** STRING MANIPULATION **************************************************/

// master string
// jared bruni
// my string algorithims :)

// string copy
void stringcopy(char* input,char* output)
{
	strcpy(input,output);
}

// string attach
void stringattach(char* input,char* output)
{
	strcat(input,output);
}

// left copy
void leftcopy(char* input,char* output,int pos)
{
	int index = 0;
	for(int i = 0; i < pos; i++)
	{
		output[index] = input[i];
		index++;
	}
	output[index] = 0;
}
// right copy
void rightcopy(char* input,char* output,int pos)
{
	int index = 0;
	int len = strlen(input);
	for(int i = pos; i < len; i++)
	{
		output[index] = input[i];
		index++;
	}
	output[index] = 0;
	
}
// mid copy
void midcopy(char* input,char* output,int start_pos, int stop_pos)
{
	int index = 0;
	for(int i = start_pos; i < stop_pos; i++)
	{
		output[index] = input[i];
		index++;
	}
	
	output[index] = 0;
}

// trim the space
void trimspace(char* buffer)
{
	int len;
	len = strlen(buffer);
	char* ptemp;
	ptemp = new char[len+1];
	strcpy(ptemp,buffer);
	
	int index = 0;
	for(int z = 0; z < len; z++)
	{
		if(ptemp[z] != ' ')
		{
			buffer[index] = ptemp[z];
			index++;
		}
	}
	buffer[index] = 0;
	
	delete [] ptemp;
}

int findstr(char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search); // search len
	
	for(int i = 0; i < len; i++)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}
			
			if(ichk == true)
			{
				return i;
			}
		}
	}
	
	return -1; // failure
}

int ifindstr(int startx,char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search); // search len
	
	for(int i = startx+1; i < len; i++)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}
			
			if(ichk == true)
			{
				return i;
			}
		}
	}
	
	return -1; // failure
}

int findstrb(char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search);
	
	for(int i = len; i > 0; i--)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}
			
			if(ichk == true)
			{
				return i; // found it
			}
		}
		
	}
	return -1; // failure
}
// find inside backwards string loop
int ifindstrb(int startx, char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search);
	
	for(int i = startx-1; i > 0; i--)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}
			
			if(ichk == true)
			{
				return i; // found it
			}
		}
		
	}
	return -1; // failure
}
// forward search string (controled range) 
int fsearchstr(int start,int stop,char* buff,char* search)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	
	for(int i = start; i < stop; i++)
	{
		if(buff[i] == search[0])
		{
			bool ichk = true;
			
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}
			
			if(ichk == true)
			{
				return i; // found it
			}
		}
	}
	
	return -1; // failure
}

// backward search string (controled range)
int bsearchstr(int start,int stop,char* buff,char* search)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	
	for(int i = start; i > stop; i--)
	{
		if(buff[i] == search[0])
		{
			bool ichk = true;
			
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}
			
			if(ichk == true)
			{
				return i; // found it;
			}
		}
	}
	
	return -1;// failure
}
// getting length
int getlen(char* buff)
{
	return strlen(buff);// use strlen :)
}
// lower case
void lcase(char* buffer)
{
	int len = getlen(buffer);
	
	for(int i = 0; i < len; i++)
	{
		buffer[i] = tolower(buffer[i]);
	}
}
// upercase
void ucase(char* buffer)
{
	int len = getlen(buffer);
	
	for(int i = 0; i < len; i++)
	{
		buffer[i] = toupper(buffer[i]);
	}
}
// uppercase letter
int ucasel(char c)
{
	return tolower(c);
}

// lowercase letter
int lcasel(char c)
{
	return tolower(c);
}

// find string location algorithims
bool findstrloc(char* buff,char* search,MasStrDataLoc* dloc)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	int* f;
	int  f_i = 0;
	f = new int[len+1];// big just in case
	
	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;
			
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
					
				}
				else
				{
					ic = false;
				}
			}
			
			if(ic == true)
			{
				f[f_i] = i;
				f_i++;
			}
		}
	}
	
	dloc->create_array(f_i);
	dloc->setstr(buff);
	dloc->setsearchstr(search);
	for(int p = 0; p < f_i; p++)
	{
		dloc->dindex[p] = f[p];
	}
	delete [] f;
	
	if(f_i != 0)
	{
		dloc->setstatus(true);
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus(false); 
		return false; // not found
	}
}
// find string location forward search
bool findstrlocf(char* buff,char* search,MasStrDataLoc* dloc)
{
	return findstrloc(buff,search,dloc);
}
// find string location backwards search
bool findstrlocb(char* buff,char* search,MasStrDataLoc* dloc)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	int* f;
	int  f_i = 0;
	f = new int[len+1];// big just in case
	
	for(int i = len; i > 0; i--)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;
			
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
					
				}
				else
				{
					ic = false;
				}
			}
			
			if(ic == true)
			{
				f[f_i] = i;
				f_i++;
			}
		}
	}
	
	dloc->create_array(f_i);
	dloc->setstr(buff);
	dloc->setsearchstr(search);
	for(int p = 0; p < f_i; p++)
	{
		dloc->dindex[p] = f[p];
	}
	delete [] f;
	
	if(f_i != 0)
	{
		dloc->setstatus(true);
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus(false);
		return false; // not found
	}
}

// string ( range based ) manipulation algorithims
bool searchrange(char* buff,char* search,MasStrRange* mrang)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);
	
	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ik = true;
			
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ik = false;
				}
			}
			
			if(ik == true)
			{
				mrang->SetRange(i,i+len2);
				return true;
			}
		}
	}
	mrang->SetRange(0,0);
	return false;
}
// string range manipluation ex (i)
bool isearchrange(int startx, char* buff,char* search,MasStrRange* mrang)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);
	
	for(int i = startx+1; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ik = true;
			
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ik = false;
				}
			}
			
			if(ik == true)
			{
				mrang->SetRange(i,i+len2);
				return true;
			}
		}
	}
	mrang->SetRange(0,0);
	return false;
}

// find the occourance amount of a specific string
int findoccourance(char* buff,char* search)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);
	
	int occ = 0;
	
	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;
			
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ic = false;
				}
			}
			
			if(ic == true)
			{
				occ++;
			}
			
		}
	}
	
	if(occ == 0)
	{
		
		return -1; // failure
		
	}
	else
	{
		return occ;
	}
}

// string range manipulation copy left range
void copyleftrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
{
	if(hi_lo == MRANGE_HI)
	{
		leftcopy(input,output,mrang->GetRangeHI());
	}
	else
	{
		leftcopy(input,output,mrang->GetRangeLO());
	}
}
// string range manipulation copy right range
void copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
{
	if(hi_lo == MRANGE_HI)
	{
		rightcopy(input,output,mrang->GetRangeHI());
	}
	else
	{
		rightcopy(input,output,mrang->GetRangeLO());
	}
}
// string range manipulation mid copy
void copymidrange(char* input,char* output,MasStrRange* mrang, int hi_lo,MasStrRange* mrangx, int hi_lox)
{
	int cx;
	int cy;
	
	if(hi_lo == MRANGE_HI)
	{
		cx = mrang->GetRangeHI();
	}
	else
	{
		cx = mrang->GetRangeLO();
	}
	
	if(hi_lox == MRANGE_HI)
	{
		cy = mrangx->GetRangeHI();
	}
	else
	{
		cy =mrangx->GetRangeLO();
	}
	
	midcopy(input,output,cx,cy);
}

// create a list from string data
void createstrlist(char* buff,char* search,MasStrList* list)
{
	int occ;
	occ = findoccourance(buff,search);
	
	if(occ == -1)
	{
		return; // failure
	}
	list->create(occ);
	
	int occ_i = 0;
	
	MasStrDataLoc dloc;
	
	if(findstrloc(buff,search,&dloc))
	{
		int pre_pos = 0;
		
		for(int z = 0; z < dloc.getmaxpoint(); z++)
		{
			int cur = 0;
			cur = dloc.dindex[z];
			charwrap cwrap(buff);
			cwrap.strclearn();
			midcopy(buff,cwrap.get(),pre_pos,cur);
			list->strings[occ_i].set(cwrap.get());
			occ_i++;
			pre_pos = cur;
		}
		
		charwrap cwrapx(buff,true);
		rightcopy(buff,cwrapx.get(),pre_pos);
		list->strings[occ_i].set(cwrapx.get());
		occ_i++;
	}
	
	return;
}
// conversion of integers
void convertinteger(int integer,char* buff,int base)
{
	itoa(integer,buff,base);
}
// conversion of strings
int convertstring(char* buff)
{
	return atoi(buff);
}
// could this be a hexidecimal digit?
bool ishexc(char c)
{
	c = lcasel(c);
	switch(c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		return true;
		break;
	}
	return false;
}
// does this string contain a non-hexidecimal digit?
bool ishex(char* buff)
{
	int len;
	len = strlen(buff);
	
	for(int i = 0; i < len; i++)
	{
		if(ishexc(buff[i]) == false)
		{
			return false;
		}
	}
	return true;
}

// hexidecimal digit to integer value
int hextointc(char c)
{
	if(ishexc(c) == false)
	{
		return -1; // failure, not a hex digit
	}
	
	c = lcasel(c);
	
	switch(c)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	case 'a':
		return 10;
		break;
	case 'b':
		return 11;
	case 'c':
		return 12;
	case 'd':
		return 13;
	case 'e':
		return 14;
	case 'f':
		return 15;
	}
	
	return -1; // failure ? never would get here
}

// convert hex value into a integer
int hextoint(char* buff)
{
	int rt = 0;
	
	if(buff[1] == 0)
	{
		return hextointc(buff[0]);
	}
	
	int len = strlen(buff);
	int* hexval;
	hexval = new int[len+1];
	int  hexvali = 0;
	
	for(int i = 0; i < len; i++)
	{
		hexval[hexvali] = hextointc(buff[i]);
		hexvali++;
	}
	
    int index = 0;
	
	for(int z = hexvali-1; z >= 0; z--)
	{
		int cur;
		if(index == 0)
		{
			cur = hexval[z];
			index = 16;
		}
		else
		{
			
			cur = hexval[z] * index;
			index = index * 16;
		}
		
		rt = rt + cur;
	}
	
	delete [] hexval;
	
	return rt;
} 


void tripcharup(char* buff, int up)
{
	int len;
	len = strlen(buff);
	
	for(int i = 0; i < len; i++)
	{
		if(buff[i] != 0)
		{
			
			buff[i] = buff[i] + up;
			
		}
	}
}

void tripchardown(char* buff,int up)
{
	int len;
	len = strlen(buff);
	
	for(int i = 0; i < len; i++)
	{
		if(buff[i] != 0)
		{
			
			buff[i] = buff[i] - up;
			
		}
	}
}
// replace single instance of a character
void replacechar(char* buff,char findchr,char replace)
{
	int len;
	len = strlen(buff);
	
	for(int z = 0; z < len; z++)
	{
		if(buff[z] == findchr)
		{
			buff[z] = replace;
		}
	}
}

void rmvinst(char* buff,char* findstr,char* replacex,char* output)
{
	
	int xt = ifindstr(NOPREV,buff,findstr);
	
	
	char* temp;
	temp = new char[strlen(buff)+1];
	stringcopy(temp,buff);
	
	char* ltemp;
	char* rtemp;
	
	ltemp = new char[strlen(buff)+1];
	rtemp = new char[strlen(buff)+1];
	
	leftcopy(buff,ltemp,xt);
	rightcopy(buff,rtemp,xt+strlen(findstr));
	
	
	cout << "\n#: " << ltemp << replacex << rtemp << endl;
	
	
	strcpy(output,ltemp);
	strcat(output,replacex);
	strcat(output,rtemp);
	
	delete [] temp;
	delete [] ltemp;
	delete [] rtemp;
}


// replace string
void replacestr(char* buff,char* findstr,char* replacex,char* output)
{
	int xt;
	xt = ifindstr(0,buff,findstr);
	
	if(xt == -1)
	{
		return; // failure no string to replace
	}
	
	char* ptemp;
	char* outtemp;
	ptemp = new char[strlen(buff) + 500];
	outtemp = new char[strlen(buff) + 500];
	stringcopy(ptemp,buff);
	
	while(1)
	{
		int xr;
		xr = ifindstr(0,ptemp,findstr);
		if(xr == -1)
		{
			break;
		}
		else
		{
			rmvinst(ptemp,findstr,replacex,outtemp);
			stringcopy(ptemp,outtemp);
		}
	}
	
	stringcopy(output,ptemp);
	
	delete [] ptemp;
	delete [] outtemp;
	
}

// random char
char randomchar(int max)
{
	int x;
	x = rand()%max;
	char c;
	c = x;
	return c;
}
// random char + up
char randomchar(int max,int up)
{
	int x;
	x = rand()%max+up;
	char c;
	c = x;
	return c;
}
// random string
void randomstr(char* buff,int max, int size)
{
	for(int i = 0; i < size; i++)
	{
		if(rand()%2)
		{
			buff[i] = randomchar(max);
		}
		else
		{
			buff[i] = randomchar(max,rand()%10);
		}
	}
}
// remove char
void removechar(char* in,char* out,char c)
{
	int len;
	len = strlen(in);
	int ic = 0;
	for(int i = 0; i < len; i++)
	{
		if(in[i] != c)
		{
			out[ic] = in[i];
			ic++;
		}
	}
	out[ic] = 0;
}

// find single character in string
int findchar(char* str,char c)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	
	return -1; // failure
}
// find char ex (inside)
int ifindchar(int start,char* str,char c)
{
	int len = strlen(str);
	for(int i = start+1; i < len; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	
	return -1;
}
// find single char backward
int findcharb(char* str,char c)
{
	int len;
	len = strlen(str);
	for(int i = len; i > 0; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	
	return -1;
}
// find single char backward
int ifindcharb(int start,char* str,char c)
{
	int len;
	len = strlen(str);
	for(int i = start-1; i > 0; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	return -1;
}

int  findcharcf(char* str,int start,int stop,char c)
{
	for(int i = start; i < stop; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	
	return -1; // failure
}
int  findcharcb(char* str,int start,int stop,char c)
{
	for(int i = stop; i > start; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	return -1;// failure
}
// remove instances of string
void removestr(char* input,char* output,char* string)
{
	
	char* buff = input;
	char* findstr = string;
	
	int xt;
	xt = ifindstr(NULLPOS,buff,findstr);
	
	if(xt == -1)
	{
		return; // failure no string to replace
	}
	
	char* ptemp;
	char* outtemp;
	ptemp = new char[strlen(buff) + 500];
	outtemp = new char[strlen(buff) + 500];
	stringcopy(ptemp,buff);
	
	while(1)
	{
		int xr;
		xr = ifindstr(0,ptemp,findstr);
		if(xr == -1)
		{
			break;
		}
		else
		{
			rmvstrx(ptemp,findstr,outtemp);
			stringcopy(ptemp,outtemp);
		}
	}
	
	stringcopy(output,ptemp);
	
	delete [] ptemp;
	delete [] outtemp;
	
}

void rmvstrx(char* buff,char* output,char* string)
{
	int xt = ifindstr(NOPREV,buff,string);
	
	char* temp;
	temp = new char[strlen(buff)+1];
	stringcopy(temp,buff);
	
	char* ltemp;
	char* rtemp;
	
	ltemp = new char[strlen(buff)+1];
	rtemp = new char[strlen(buff)+1];
	
	leftcopy(buff,ltemp,xt);
	rightcopy(buff,rtemp,xt+strlen(string));
	
	strcpy(output,ltemp);
	strcat(output,rtemp);
	
	delete [] temp;
	delete [] ltemp;
	delete [] rtemp;
}

void strsavefile(char* filename,char* buff)
{
	ofstream fout(filename);
	
	fout << buff;
	
	fout.close();
}

int getfilestringlength(char* filename)
{
	int count = 0;
	ifstream fin(filename);
	if(fin)
	{
		char ch;
		while(fin.get(ch))
		{
			count++;
		}
		
		fin.close();
		return count;
		
	} else { return -1; } // failure
	
	return -1;
}

bool strloadfile(char* file,char* output)
{
	int count = 0;
	ifstream fin(file);
	if(fin)
	{
		char ch;
		int str_i = 0;
		while(fin.get(ch))
		{
			output[str_i] = ch;
			str_i++;
		}
		
		output[str_i] = 0;
		return true;
	}
	else
	{
		return false;
	}
	
	return false;
}

void reversestring(char* input,char* output)
{
	int len;
	len = strlen(input);
	int fcount = 0;
	
	for(int i = len; i > 0; i--)
	{
		output[fcount] = input[i];
		fcount++;
	}
	
	output[fcount] = 0;
}

bool isstrvalid(char* string)
{
	int len = strlen(string);
	for(int i = 0; i < len; i++)
	{
		if(string[i] == 0)
		{
			return true; // true it is a null terminated string!
		}
	}
	
	return false;
}

// Save Master INI
bool SaveMasterINI(char* filename,MasterINI* mini)
{
	ofstream fout(filename,ios::binary);
	
	if(fout)
	{
		
		
		fout.write((char*)&mini,sizeof(mini));
		
		fout.close();
		
		return true;
		
	}
	fout.close();
	return false;
}
// Load master INI
bool LoadMasterINI(char* filename,MasterINI* mini)
{
	ifstream fin(filename,ios::binary);
	
	if(fin)
	{
		fin.read((char*)&mini,sizeof(mini));
	}
	
	fin.close();
	return false;
}

// string compare (case sensitive)
bool mstrcmp(char* buff1,char* buff2)
{
	int len;
	int len2;
	len = strlen(buff1);
	len2 = strlen(buff2);
	
	if(len != len2)
	{
		return false; // not equal length
	}
	
	for(int i = 0; i < len; i++)
	{
		if(buff1[i] != buff2[i])
		{
			return false;
		}
	}
	
	return true;
}

// string compare (not case sensitive)
bool mstrcmpx(char* buff1,char* buff2)
{
	int len;
	int len2;
	len = strlen(buff1);
	len2 = strlen(buff2);
	
	if(len != len2)
	{
		return false; // not equal length
	}
	
	for(int i = 0; i < len; i++)
	{
		if(tolower(buff1[i]) != tolower(buff2[i]))
		{
			return false;
		}
	}
	
	return true;
}

bool insidestr(char* buff1,char* buff2)
{
	int chk;
	chk = findstr(buff1,buff2);
	
	if(chk == -1)
	{
		return false;
	}
	
	return true;
}

bool insidestrx(char* buff1,char* buff2)
{
	char* pbuff1;
	char* pbuff2;
	
	pbuff1 = new char[strlen(buff1)+1];
	pbuff2 = new char[strlen(buff2)+1];
	
	stringcopy(pbuff1,buff1);
	stringcopy(pbuff2,buff2);
	
	lcase(pbuff1);
	lcase(pbuff2);
	
	int chk;
	chk = findstr(pbuff1,buff2);
	
	delete [] pbuff1;
	delete [] pbuff2;
	pbuff1 = 0;
	pbuff2 = 0;
	
	if(chk == -1)
	{
		return false;
	}
	
	return true;
}
// string seperation from 2 points
void strsep(char* str, char* sleft, int go_left, char* sright, int go_right)
{
	leftcopy(str,sleft,go_left);
	rightcopy(str,sright,go_right);
}
void strsetnull(char* str,int pos)
{
	str[pos] = 0;
}

void rmvnullset(char* str)
{
	int len;
	len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == 0)
		{
			str[i] = ' ';
		}
	}
}

int getnullpos(char* str)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == 0)
		{
			return i;
		}
	}
	
	return -1; // failure to find 0
}
// trim commented characters () 
void trimcom(char* str, char* output,char start_c,char stop_c)
{
	int len = strlen(str);
	int index = 0;
	
	bool iadd = true;
	
	for(int z = 0; z < len; z++)
	{
		if(str[z] == start_c)
		{
			iadd = false; 
		}
		
		if(str[z] == stop_c)
		{
			iadd = true;
		}
		
		if(iadd == true)
		{
			output[index] = str[z];
			index++;
		}
	}
	
	output[index] = 0;
}

// trim comments to an assembly language source file
void asmtrim(char* input,char* output)
{
	trimcom(input,output,';','\n');
}

// count the number of lines exisitng within the source
int countlines(char* buffer)
{
	return findoccourance(buffer,"\n");
}
// get the first letter thats not a space
int getfirstletter(char* buff)
{
	int len = strlen(buff);
	
	for(int i = 0; i < len; i++)
	{
		if(buff[i] != ' ')
		{
			return i;
		}
	}
	return -1; // failure! no letters
}

#endif

/* MasterString2 
   string library

  written by Jared Bruni
  www.LostSideDead.com

  "Open  Source, Open Mind" 


  freestyle-> spin_it();
*/

#ifdef MASTER_STRING2
#ifndef MASTERSTRING2
#define MASTERSTRING2



// optomized algorithms
// namespace for masterstring
namespace masterstring
{
	int i,z,j,len;
	bool check;
	unsigned int mstrlen(char* str);
	void mstrcpy(char* dest, char* source);
	void mstrcat(char* dest, char* source);
	void mstrleft(char* source,char* output,unsigned int pos);
	void mstrright(char* source,char* output, unsigned int pos);
	void mstrmid(char* source,char* output, unsigned int pos, unsigned int pos2);
	void mstrvbmid(char* source, char* output, unsigned int pos, unsigned int pos2);
	bool mstrcmp(char* string1,char* string2);
	void killspace(char* in, char* out);
	unsigned int mcharoccourance(char* source, char c);
	unsigned int mstrfind(char* source, char* string);
	unsigned int mstrifind(unsigned int start, char* source, char* string);
	unsigned int mstrbfind(char* source, char* string);
	unsigned int mstribfind(unsigned int start, char* source, char* string);
}

/*************************  string algorithms **********************************************/

// mstrlen  - get string length
unsigned int masterstring::mstrlen(char* str)
{
    char* temp = str;
	i = 0;
	while( *temp++)
	{
		i++;
	}

	return i;
}
// mstrcpy - string copy
void masterstring::mstrcpy(char* dest,char* source)
{
	z =  mstrlen(source);
	for(i = 0; i < z; i++)
	{
		dest[i] = source[i];
	}
	dest[z] = 0;
}

// mstrcat - string concatination
void masterstring::mstrcat(char* dest,char* source)
{
	z = mstrlen(source);
	j = mstrlen(dest);
	for(i = 0; i < z; i++)
	{
 		dest[i+j] = source[i];
	}
	dest[j+z] = 0;

}

// mstrleft - left string copy 
void masterstring::mstrleft(char* source,char* output,unsigned int pos)
{
	for(i = 0; i < (int) pos; i++)
	{
		output[i] = source[i];
	}
	output[pos] = 0;
}

// mstrright - right string copy
void masterstring::mstrright(char* string,char* output, unsigned int pos)
{
	len = mstrlen(string);
    z = 0;
	for(i = pos; i < len; i++)
	{
    	output[z] = string[i];
		z++;
	}
	
	output[z] = 0;
}
// mstrmid - middle string copy
void masterstring::mstrmid(char* string,char* out, unsigned int start, unsigned int stop)
{
	z = 0;
	for(i = start; i < (int) stop; i++)
	{
		out[z] = string[i];
		z++;
	}
	out[z] =0;
}
// mstrvbmind - middle string copy vb style
void masterstring::mstrvbmid(char* source, char* output, unsigned int start, unsigned int length)
{
	z = 0;
	for(i = start; i < (int)start+(int)length; i++)
	{
		output[z] = source[i];
		z++;
	}
	output[z] = 0;	
}
// mstrcmp - string compare
bool masterstring::mstrcmp(char* string1,char* string2)
{
	len = mstrlen(string1);
	z = mstrlen(string2);
	if(len != z)
	{
		return false;
	}

	for(i = 0; i < len; i++)
	{
		if( string1[i] != string2[i] )
		{
			return false;
		}
	}
	return true;
}

// killspace - kill space from a string
void masterstring::killspace(char* in, char* out)
{
	j = mstrlen(in);
	z = 0;
	for(i = 0; i < j; i++)
	{
		if(in[i] != ' ')
		{

		out[z] = in[i];
		z++;

		}
	}
	out[z] = 0;
}

// mcharoccourance - find number of occourances of a char
unsigned int masterstring::mcharoccourance(char* source, char c)
{
	z = 0;
	j = mstrlen(source);
	for(i = 0; i < j; i++)
	{
		if(source[i] == c)
		{
			z++;
		}
	}

	return z;
}

// mstrfind - find a string within a string
unsigned int masterstring::mstrfind(char* source, char* string)
{
	j = mstrlen(source);
	len = mstrlen(string);
	for(i = 0; i < j; i++)
	{
		if(source[i] == string[0])
		{
			check = true;

			for(z = 0; z < len; z++)
			{
				if(source[i+z] != string[z])
				{
					check = false;
				}
			}

			if(check == true)
			{
				return i;
			}
		}
	}

	return -1; // fail
}

//mstrifind - master string start pos find
unsigned int masterstring::mstrifind(unsigned int start, char* source, char* string)
{
	j = mstrlen(source);
	len = mstrlen(string);
	for(i = start; i < j; i++)
	{
		if(source[i] == string[0])
		{
			check = true;

			for(z = 0; z < len; z++)
			{
				if(source[i+z] != string[z])
				{
					check = false;
				}
			}

			if(check == true)
			{
				return i;
			}
		}
	}

	return -1; // fail
}

// mstrbfind - string backwards find
unsigned int masterstring::mstrbfind(char* source, char* string)
{
	j = mstrlen(source);
	len = mstrlen(string);
	for(i = j; i >= 0; i--)
	{
		if(source[i] == string[0])
		{
			check = true;

			for(z = 0; z < len; z++)
			{
				if(source[i+z] != string[z])
				{
					check = false;
				}
			}

			if(check == true)
			{
				return i;
			}
		}
	}

	return -1; // fail
}

// mstribfind - string backwards position find
unsigned int masterstring::mstribfind(unsigned int start, char* source, char* string)
{
	j = mstrlen(source);
	len = mstrlen(string);
	for(i = start; i >= 0; i--)
	{
		if(source[i] == string[0])
		{
			check = true;

			for(z = 0; z < len; z++)
			{
				if(source[i+z] != string[z])
				{
					check = false;
				}
			}

			if(check == true)
			{
				return i;
			}
		}
	}

	return -1; // fail
}

#endif

// use a #define MASTERSTRING1
// before including the masterstring header
// to use masterstring 1 algorithms
#ifdef MASTERSTRING1
// masterstring - null terminated string manipulation 
// class hierarchy , as well as a large series of string related algorithims
// by jared bruni 
// my new string algorithims
// jared@lostsidedead.com

// some very important algorithims
// I totaly re-wrote all these from scratch
// so it would work better with the new masasm (my newest project)
// www.lostsidedead.com

// this source file is dedicated to my buds (hehe)


/************ Using MasterString ********************

  Within this source file consits of a series of
  algorithims and classes. You can inturn use these
  different aspects of the source to produce your
  own string classes, or to simply manipulate 
  char arrays. There are multiple levels of functionality
  as well as a few base classes for your classes to
  inhert from. This source is to be thought of as the
  layer ontop of string.h , allowing for simplicity
  as well as expanding the types of things it can do.

  The Functions**************************************

  All the simple functions with lowercased names, are
  the c-style functions. These allow you to pass a pointer
  to the character array, and manipulate it , in the way
  it describes (ex: findstr,stringcopy) etc these functions
  are very useful when directly manipulating character arrays
  and provide a much deeper form of control over the array.
  There are seires of different forms of string searches,
  which allow you to have full control. One of my favorite
  new ones which Im going to talk about here is findstrloc.
  findstrloc stands for find string location, its prototype is
  the following.

  void findstrloc(char* buff,char* search,MasStrDataLoc* dloc);

  This function cycles through the buffer, and every time it
  finds an instance of search, it leaves a refrence to it
  inside the MasStrDataLoc structure. Pretty nifty, but
  there are other ways to be able to cycle through all the
  characters, with very explicit searchs.

  findstr
  ifindstr
  findstrb
  ifindstrb

  etc

  These forms of searching for strings within your strings are
  extermly useful. They allow you to start off at the begining
  and then continue searching were you left off at. Allows you
  to search forward, backward, and even within a range of those
  two points. findstrcf (find string cycle forward) and findstrcb 
  (find string cycle backward). There are also a seires of functions
  that directly manipulate with ranges. These searchs, return a structure
  (MasStrRange) which contains two points. One for the starting location
  of the sub string, and one for were it stops. Pretty nifty when needing
  to have a full detailed structure of were things are at, to make
  the whole manipulation proccess easy. 


  The Classes / Structures *************************

  The next layer ontop of these functions, is the
  MasStrObj. This is a object, to use as a base
  object to inhert into your string classes, or
  whatever other class would need the structure
  of these functions.

  MasterString object

  The master string object, is a String class, which rather
  then attempting to just encapsulate all the string functionality
  it instead, trys to simplfy the proccess of using the object
  but still consist of the same amount of power. The MasterString
  inherts from MasStrObj, and then expands upon this to provide
  a autosizing string. It does this by creating a pointer to memory
  on the freestore, and then freeing that memory at appropriate times.
  It also has another layer, were the methods which use a form
  of hungarin notation (FindWindow LikeThis) automaticly point to the
  string within the Object. Let me give a example of this.

  theres the function findstr, and then the method within the
  MasterString object, FindString

  the following would be how you would call it

  char string1[100];
  stringcopy(string1, "stuff is x here");
  int placeval;
  placeval = findstr(string1,"x");

  using the MasterString , its actualy quite simpler

  MasterString str("stuff is x here");
  int placeval;
  placeval = str.FindString("x");

  When using the MasterString object, it basicly lets you
  encapsulate what character array the low level functions
  are pointing to, while still allowing you the ability
  to directly call any of the other functions.

  MasterStringList ********************************

  The MasterStringList class , is pretty simple to grasp
  and use. Its simply a class which holds a list of
  MasterStrings :)
  This class incorperates multiple inheritance one of my
  favorite features of the C++ language

  MasterINI ***************************************

  The MasterINI class is also fairly simple. It is a
  object that is kinda like a INI file. You basicly
  put in strings, by there name, and what the value is
  for that name, and it can then be saved & loaded.
  Its really easy to use / work, just remember to always
  create your size, or its gonna trip! example:

  MasterINI mstr(100); // allows 100 entrys

  MasterINI mstrx; // has no size
  mstrx.Create(100);// now has the size of 100 entrys


  - Jared Bruni

  Master@LostSideDead.com -

****************************************************/


#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream.h>
#include <fstream.h>

#define NOTFOUND -1
#define INULL    -1
#define NOPREV   -1
#define NULLI    -1
#define STRBEGIN -1
#define MRANGE_HI 1
#define MRANGE_LO 0
#define NULLPOS  -1

// string algorithims
void stringcopy(char* dest,char* from); // string copy
void stringattach(char* dest,char* from); // string attach
void leftcopy(char* from,char* dest,int pos);// left copy (leftstr)
void rightcopy(char* from,char* dest,int pos);// right copy (rightstr)
void midcopy(char* from,char* dest,int start_pos,int stop_pos);// middle copy (midstr)
void trimspace(char* buff);// trim space characters
int findstr(char* buffer,char* search);// find string search
int ifindstr(int i,char* buffer,char* search);// find string search from position
int findstrb(char* buffer,char* search); // backwards search
int ifindstrb(int i,char* buffer,char* search); // inside backwards search
int fsearchstr(int start,int stop,char* buff,char* search);// fully controled range search (forward)
int bsearchstr(int start,int stop,char* buff,char* search);// fully controled range search (backward)
void removestr(char* buff,char* str);// remove instances of str in buff
int getlen(char* buff);// get length of the string
void lcase(char* buff);// lower case string
void ucase(char* buff);// upper case string
int  lcasel(int c);// lower case letter
int  ucasel(int c);// upper case letter
int  findoccurance(char* buff,char* search);// find occourances of a specific string
void convertinteger(int integer,char* buff,int base); // convert integer to string
int  convertstring(char* buff); // convert string to integer
bool ishexc(char c);// is this character a hexidecimal digit?
bool ishex(char* buff);// is this string a hexidecimal value?
int  hextointc(char c);// hexidecimal digit to integer value
int  hextoint(char* buff); // hexidecimal digits to integer value
int findoccourance(char* buff,char* search);// find the numeric of times a string occours
void tripcharup(char* buff,int upby);// bump the digits up X times
void tripchardown(char* buff,int downby);// dump the digits down  X times
void replacechar(char* string,char findchr,char replace);// replace single character, through out all instances
void replacestr(char* string,char* findstr,char* rep,char* output);// replace string inside string
void rmvinst(char* buff,char* findstr,char* replace,char* output); // remove single instance of string
char randomchar(int max);// produce a random character
char randomchar(int max,int up);// produce a random character, and then make it + up
void randomstr(char* buff,int char_max,int char_size);// random string
void removechar(char* input,char* output,char c); // remove characters from buffer
int  findchar(char* str,char c);// find single char (forward)
int  ifindchar(int start,char* str,char c); // inside find single char (forward)
int  findcharb(char* str,char c);// find single char (backward)
int  ifindcharb(int start,char* str,char c); // find single char backward ex
int  findcharcf(char* str,int start,int stop,char c);// find single char controled forward
int  findcharcb(char* str,int start,int stop,char c);// find single char controled backward
void removestr(char* input,char* output,char* string); // remove instance of string
void rmvstrx(char* buff,char* output,char* string); // remove single instance of string
void strsavefile(char* filename,char* string);// save the string as a text file
int  getfilestringlength(char* filename);// get the string length of a text file
bool strloadfile(char* filename,char* output);// load a string from a text file
void reversestring(char* input,char* output); // reverse sring
bool isstrvalid(char* string); // checks to see if the string is valid or not (is null terminated)
// string compares
bool mstrcmp(char* buff1,char* buff2); // case sensitive compare
bool mstrcmpx(char* buff1,char* buff2);// not case sensitive compare
bool insidestr(char* buff1,char* buff2); // am i inside this string?
bool insidestrx(char* buff1,char* buff2);// am i inside this string lowercased ?
void strsep(char* str, char* sleft, int go_left, char* sright, int go_right);// seperate into 2 seperate strings from 2 seperate points
void strsetnull(char* str,int pos); // reset the 0's position
void rmvnullset(char* str); // remove the 0 to end the string
int  getnullpos(char* str); // get the position of the null
void trimcom(char* buff, char* output, char startstr,char stopstr); 
void asmtrim(char* input,char* output);
int  countlines(char* buffer); // counts how many \n characters exisit
int  getfirstletter(char* buffer); // get first letter thats not a space

// string data location structure use w/ (findstrl)
struct MasStrDataLoc
{
	int* dindex;
	int  array_size;
	char* thestring;
	char* searchstr;
	bool search_status;

	inline MasStrDataLoc()
	{
		search_status = false;
		dindex = 0;
		array_size = 0;
		searchstr = 0;
	}
	
	inline ~MasStrDataLoc()
	{
		if(dindex != 0)
		{

		delete [] dindex;
		dindex = 0;

		}
		if(thestring != 0)
		{

		delete [] thestring;
		thestring = 0;

		}
		if(searchstr != 0)
		{

		delete [] searchstr;
		searchstr = 0;

		}
	}

	inline void create_array(int size)
	{
		dindex = new int[size];
		array_size = size;
	}

	inline void setstr(char* buff)
	{
		int len;
		len = strlen(buff);
		thestring = new char[len+1];
		stringcopy(thestring,buff);
	}

	inline void setstatus(bool x)
	{
		search_status = x;
	}

	inline void setsearchstr(char* buff)
	{
		int len;
		len = strlen(buff);
		searchstr = new char[len+1];
		stringcopy(searchstr,buff);
	}

	// return pointer to the string which the array holds data for
	inline char* getstr()
	{
		return thestring;
	}

	inline char* getsearchstr()
	{
		return searchstr;
	}

	inline int getarraysize()
	{
		return array_size;
	}

	inline int getstringpoint(int index)
	{
		if(index <= array_size)
		{

		return dindex[index];

		}
	}
	// maximum string points for search
	inline int getmaxpoint()
	{
		return array_size;
	}
	// get status
	inline bool getstatus()
	{
		return search_status;
	}

	inline bool wassearchsuccesful()
	{
		return getstatus();// was it succesfull?
	}
};
// find string location (dumps all locations into the location data structure (MasStrDataLoc))
bool findstrloc(char* buff,char* search,MasStrDataLoc* dloc);// standard
bool findstrlocf(char* buff,char* search,MasStrDataLoc* dloc);// forward
bool findstrlocb(char* buff,char* search,MasStrDataLoc* dloc);// backward

// master string range structure
struct MasStrRange
{
	int start_x;
	int stop_y;

	inline MasStrRange()
	{
		start_x = 0;
		stop_y = 0;
	}

	inline void SetRange(int x, int y)
	{
		start_x = x;
		stop_y = y;
	}

	inline int GetRangeX()
	{
		return start_x;
	}

	inline int GetRangeY()
	{
		return stop_y;
	}

	inline int GetRangeHI()
	{
		return start_x;
	}

	inline int GetRangeLO()
	{
		return stop_y;
	}

	inline int Clear()
	{
		start_x = 0;
		stop_y = 0;
	}
};

// range search structures for range style string manipulation
bool searchrange(char* buff,char* search,MasStrRange* mrang);
void copyleftrange(char* input,char* output,MasStrRange* mrang, int hi_lo);
void copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo);
void copymidrange(char* input,char* output,MasStrRange* mrang, int hi_lo,MasStrRange* mrangx, int hi_lox);
bool isearchrange(int startx, char* buff,char* search,MasStrRange* mrang);

// master string list structure string data
struct MasStrList_String
{
	char* thestring;

	inline ~MasStrList_String()
	{
		delete [] thestring;
	}

	inline void set(char* buff)
	{
		int len;
		len = strlen(buff) + 1;
		thestring = new char[len];
		stringcopy(thestring,buff);
	}

	inline char* get()
	{
		return thestring;
	}
};
// master string list , list handler structure
struct MasStrList
{
	MasStrList_String* strings;
	int list_size;

	inline ~MasStrList()
	{
		delete [] strings;
	}

	inline MasStrList(int list_size)
	{
		create(list_size);
	}

	inline MasStrList()
	{
		list_size = 0;
		strings = NULL;
	}

	inline void create(int list_sizez)
	{
		list_size = list_sizez;
		strings = new MasStrList_String[list_size];
	}

	inline char* getstr(int index)
	{
		return strings[index].get();
	}

	inline int getcount()
	{
		return list_size;
	}
};

// create string list
void createstrlist(char* buffer, char* list_marker,MasStrList* list);


// charwrap  easy to use char array, that automaticly removes itself from freestore
struct charwrap
{
	char* str;

	inline charwrap(int size)
	{
		str = new char[size];
	}

	inline charwrap(char* buff)
	{
		set(buff);
	}

	inline charwrap(char* buff,bool x)
	{
		set(buff);
		strclearn();
	}

	inline ~charwrap()
	{
		delete [] str; // delete that shit
	}

	inline void set(char* buff)
	{
		int len;
		len = strlen(buff) + 1;
		str = new char[len];
		stringcopy(str,buff);
	}

	inline void snew(int size)
	{
		str = new char[size];
	}

	// clear off freestore
	inline void clear()
	{
		delete [] str;
		str = NULL;
	}

	inline void strclear()
	{
		int len;
		len = getlen(str);

		for(int i = 0; i < len; i++)
		{
			str[i] = 0;
		}
	}

	inline void strclearn()
	{
		stringcopy(str,"");
	}

	inline char* get()
	{
		return str;
	}

	inline int len()
	{
		return getlen(str);
	}

	inline void qmsg()
	{
		MessageBox(0,str,"QMSG",MB_OK|MB_ICONINFORMATION);
	}

};

// structure of string manipulation algorithims to use for objects to inhert
struct MasStrObj
{
    inline void mstr_stringcopy(char* input,char* output)
	{
		stringcopy(input,output);
	}

	inline void mstr_stringattach(char* input,char* output)
	{
		stringattach(input,output);
	}

	inline void mstr_leftcopy(char* input,char* output,int pos)
	{
		leftcopy(input,output,pos);
	}

	inline void mstr_rightcopy(char* input,char* output,int pos)
	{
		rightcopy(input,output,pos);
	}

	inline void mstr_midcopy(char* input,char* output,int start_pos,int stop_pos)
	{
		midcopy(input,output,start_pos,stop_pos);
	}

	inline void mstr_trimspace(char* buff)
	{
		trimspace(buff);
	}

	inline int mstr_findstr(char* buffer,char* search)
	{
		return findstr(buffer,search);
	}

	inline int mstr_ifindstr(int i,char* buffer,char* search)
	{
		return ifindstr(i,buffer,search);
	}

	inline int mstr_findstrb(char* body,char* search)
	{
		return findstrb(body,search);
	}

	inline int mstr_ifindstrb(int startx,char* body,char* search)
	{
		return ifindstrb(startx,body,search);
	}

	inline int mstr_fsearchstr(int start,int stop,char* buff,char* search)
	{
		return fsearchstr(start,stop,buff,search);
	}

	inline int mstr_bsearchstr(int start,int stop,char* buff,char* search)
	{
		return bsearchstr(start,stop,buff,search);
	}

	inline int mstr_getlen(char* buff)
	{
		int len;
		len = strlen(buff);
		return len;
	}

	inline int mstr_lcase(char* buffer)
	{
		lcase(buffer);
	}

	inline int mstr_ucase(char* buffer)
	{
		ucase(buffer);
	}

	inline int mstr_ucasel(char c)
	{
		return ucasel(c);
	}

	inline int mstr_lcasel(char c)
	{
		return lcasel(c);
	}

	inline bool mstr_findstrloc(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrloc(buff,search,dloc);
	}

	inline bool mstr_findstrlocf(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrlocf(buff,search,dloc);
	}

	inline bool mstr_findstrlocb(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrlocb(buff,search,dloc);
	}

	inline bool mstr_searchrange(char* buff,char* search,MasStrRange* mrang)
	{
		return searchrange(buff,search,mrang);
	}

	inline bool mstr_isearchrange(int startx, char* buff,char* search,MasStrRange* mrang)
	{
		return isearchrange(startx,buff,search,mrang);
	}

	inline void mstr_copyleftrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
	{
		copyleftrange(input,output,mrang,hi_lo);
	}

	inline void mstr_copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
	{
		copyrightrange(input,output,mrang,hi_lo);
	}

	inline void mstr_copymidrange(char* input,char* output,MasStrRange* mrang,int hi_lo,MasStrRange* mrangx,int hi_lox)
	{
		copymidrange(input,output,mrang,hi_lo,mrangx,hi_lox);
	}

	inline int mstr_findoccourance(char* buffer,char* searchx)
	{
		return findoccourance(buffer,searchx);
	}

	inline void mstr_convertinteger(int integer,char* buff,int base)
	{
		convertinteger(integer,buff,base);
	}

	inline int mstr_convertstring(char* buff)
	{
		return convertstring(buff);
	}

	inline bool mstr_ishexc(char c)
	{
		return ishexc(c);
	}

	inline bool mstr_ishex(char* buff)
	{
		return ishex(buff);
	}

	inline int mstr_hextointc(char c)
	{
		return hextointc(c);
	}
	inline int mstr_hextoint(char* buff)
	{
		return hextoint(buff);
	}

	inline void mstr_tripchardown(char* buff,int by)
	{
		tripchardown(buff,by);
	}

	inline void mstr_tripcharup(char* buff, int by)
	{
		tripcharup(buff,by);
	}
	inline void mstr_replacechar(char* buff,char findchr,char replace)
	{
		replacechar(buff,findchr,replace);
	}
	inline void mstr_replacestr(char* buff,char* findstr,char* replacex,char* output)
	{
		replacestr(buff,findstr,replacex,output);
	}
	inline void mstr_rmvinst(char* buff,char* findchr,char* re,char* out)
	{
		rmvinst(buff,findchr,re,out);
	}

	inline char mstr_randomchar(int max)
	{
		return randomchar(max);
	}
	inline char mstr_randomchar(int max, int up)
	{
		return randomchar(max,up);
	}
	inline void mstr_randomstr(char* buff,int max, int size)
	{
		randomstr(buff,max,size);
	}
	inline void mstr_removechar(char* input,char* output,char c)
	{
		removechar(input,output,c);
	}
	inline char mstr_findchar(char* str,char c)
	{
		return findchar(str,c);
	}
	inline char mstr_ifindchar(int start,char* str,char c)
	{
		return ifindchar(start,str,c);
	}
	inline char mstr_findcharb(char* str,char c)
	{
		return findcharb(str,c);
	}
	inline char mstr_ifindcharb(int start,char* str,char c)
	{
		return ifindcharb(start,str,c);
	}
	inline char mstr_findcharcf(char* str,int start,int stop,char c)
	{
		return findcharcf(str,start,stop,c);
	}
	inline char mstr_findcharcb(char* str,int start,int stop,char c)
	{
		return findcharcb(str,start,stop,c);
	}
	inline void mstr_removestr(char* str,char* output,char* strsearch)
	{
		removestr(str,output,strsearch);
	}
	inline void mstr_removestrinstance(char* str,char* output,char* strx)
	{
		rmvstrx(str,output,strx);
	}
	inline void mstr_savestr(char* filename,char* string)
	{
		strsavefile(filename,string);
	}
	inline bool mstr_loadstr(char* filename,char* output)
	{
		return strloadfile(filename,output);
	}
	inline int  mstr_getfilestrlen(char* filename)
	{
		return getfilestringlength(filename);
	}
	inline int mstr_reversestr(char* str_input,char* str_output)
	{
		reversestring(str_input,str_output);
	}
	inline bool mstr_isstrvalid(char* str)
	{
		return isstrvalid(str);
	}
	inline bool mstr_mstrcmp(char* buff1,char* buff2)
	{
		return mstrcmp(buff1,buff2);
	}

	inline bool mstr_mstrcmpl(char* buff1,char* buff2)
	{
		return mstrcmpx(buff1,buff2);
	}

	inline bool mstr_insidestr(char* buff1,char* buff2)
	{
		return insidestr(buff1,buff2);
	}
	inline bool mstr_insidestrl(char* buff1,char* buff2)
	{
		return insidestrx(buff1,buff2);
	}
	inline void mstr_strsep(char* str,char* lstr,int lpos,char* rstr,int rpos)
	{
		strsep(str,lstr,lpos,rstr,rpos);
	}
	inline int mstr_getnullpos(char* str)
	{
		return getnullpos(str);
	}
	inline void mstr_rmvnullset(char* str)
	{
		rmvnullset(str);
	}
	inline void mstr_strsetnull(char* str,int pos)
	{
		strsetnull(str,pos);
	}
	inline void mstr_trimcom(char* input,char* output, char start_c,char stop_c)
	{
		trimcom(input,output,start_c,stop_c);
	}
	inline void mstr_asmtrim(char* input,char* output)
	{
		asmtrim(input,output);
	}
};

// the MasterString Object

struct MasterString : MasStrObj
{
	char* str;
	int array_size;
	bool str_on;

	/********** constructors & deconstructors ****************/
	inline MasterString()
	{
		str_on = false;
		array_size = 0;
		str = NULL;
	}

	inline MasterString(int size)
	{
		set(size,"");
	}

	inline MasterString(char* buff)
	{
		int size = strlen(buff) + 2;
		set(size,buff);
	}

	inline MasterString(int size,char* buff)
	{
		set(size,buff);
	}

	inline ~MasterString()
	{
		if(str_on)
		{
			delete [] str;
			str_on = false;

		}
	}

	/* internal functions **************************/
	inline void set(int size,char* buff)
	{
		if(str_on == false)
		{
			str = new char[size];
			str_on = true;
		}
		else
		{
			delete [] str;
			str = new char[size];
		}

		mstr_stringcopy(str,buff);
		array_size = size;
	}

	inline void add(char* buff)
	{
		int total_length = GetStringLength() + strlen(buff) + 2;

		if(total_length > GetStringLength())
		{
			char* ptemp;
			ptemp = new char[GetStringLength()+1];
			strcpy(ptemp,str);

			delete [] str;
			str = 0;// set pointer to 0 
			str = new char[total_length+2];
			strcpy(str,ptemp);
			delete [] ptemp;
			strcat(str,buff);
		}
		else
		{
			strcat(str,buff);
		}
	}

	inline void unset()
	{
		if(str_on == true)
		{
			delete [] str;
			str_on = false;
		}
	}

	inline char* get()
	{
		return str;
	}

	// operators *************************

	inline void operator=(char* buffer)
	{
		// set
		int len;
		len = strlen(buffer)+2;
		set(len,buffer);
	}

	inline void operator+=(char* buffer)
	{
		add(buffer);
	}
	inline void operator+=(int x)
	{
		char buffer[30];
		itoa(x,buffer,10);
		add(buffer);
	}

	inline void operator+=(long x)
	{
		char buffer[30];
		itoa(x,buffer,10);
		add(buffer);
	}

	// misc *********************************

	inline int GetStringLength()
	{
		return mstr_getlen(str);
	}

	inline char* GetCharPointer()
	{
		return str;
	}

	inline int FindChar(char c)
	{
		return mstr_findchar(str,c);
	}

	inline int FindCharEx(int pre_pos,char c)
	{
		return mstr_ifindchar(pre_pos,str,c);
	}
	inline int FindCharBackward(char c)
	{
		return mstr_findcharb(str,c);
	}
	inline int FindCharBackwardEx(int pre_pos,char c)
	{
		return mstr_ifindcharb(pre_pos,str,c);
	}
	inline int FindCharControledForward(int start,int stop,char c)
	{
		return mstr_findcharcf(str,start,stop,c);
	}
	inline int FindCharControledBackward(int start,int stop,char c)
	{
		return mstr_findcharcb(str,start,stop,c);
	}
	inline int FindString(char* search)
	{
		return mstr_findstr(str,search);
	}

	inline int FindStringEx(int index,char* search)
	{
		return mstr_ifindstr(index,str,search);
	}

	inline int FindStringBackward(char* search)
	{
		return mstr_findstrb(str,search);
	}
	inline int FindStringBackwardEx(int index,char* search)
	{
		return mstr_ifindstrb(index,str,search);
	}
	inline int FindOccourance(char* search)
	{
		return mstr_findoccourance(str,search);
	}
	inline void StringCopy(char* buff)
	{
		mstr_stringcopy(str,buff);
	}
	inline void StringAttach(char* buff)
	{
		mstr_stringattach(str,buff);
	}
	inline void StringResize(int newSize)
	{
		char* ptemp;
		ptemp = new char[strlen(str)+1];
		strcpy(ptemp,str);

		delete [] str;
		str = new char[newSize];
		strcpy(str,ptemp);
		delete [] ptemp;
	}
	inline void StringLeft(char* output,int pos)
	{
		mstr_leftcopy(str,output,pos);
	}
	inline void StringRight(char* output,int pos)
	{
		mstr_rightcopy(str,output,pos);
	}
	inline void StringMid(char* output,int x,int y)
	{
		mstr_midcopy(str,output,x,y);
	}
	inline void TrimSpace()
	{
		trimspace(str);
	}

	inline void UpperCase()
	{
		ucase(str);
	}
	inline void LowerCase()
	{
		lcase(str);
	}
	inline char ExtractChar(int index)
	{
		if(index <= GetStringLength())
		{
			return str[index];
		}
		return 0;
	}
	inline int ForwardStringSearch(int start,int stop,char* search)
	{
		return mstr_fsearchstr(start,stop,str,search);
	}

	inline int BackwardStringSearch(int start,int stop,char* search)
	{
		return mstr_bsearchstr(start,stop,str,search);
	}
	inline bool FindStringLocation(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrloc(str,search,dloc);
	}
	inline bool FindStringLocationF(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrlocf(str,search,dloc);
	}
	inline bool FindStringLocationB(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrlocb(str,search,dloc);
	}
	inline void SearchRange(char* search,MasStrRange* mrang)
	{
		mstr_searchrange(str,search,mrang);
	}
	inline void SearchRangeEx(int startx,char* search,MasStrRange* mrang)
	{
		mstr_isearchrange(startx,str,search,mrang);
	}
	inline void CopyLeftRange(char* output, MasStrRange* mrang,int hi)
	{
		mstr_copyleftrange(str,output,mrang,hi);
	}
	inline void CopyRightRange(char* output, MasStrRange* mrang,int hi)
	{
		mstr_copyrightrange(str,output,mrang,hi);
	}
	inline void CopyMidRange(char* output,MasStrRange* mrang,int hi, MasStrRange* mrangx,int hix)
	{
		mstr_copymidrange(str,output,mrang,hi,mrangx,hix);
	}
	
	inline int GetHexValue()
	{
		return mstr_hextoint(str);
	}
	inline int GetDecValue()
	{
		return atoi(str);
	}
	inline int ConvertToInteger()
	{
		return atoi(str);
	}
	inline bool IsHex()
	{
		return mstr_ishex(str);
	}

	inline void qprint()
	{
		cout << str;
	}
	inline void qmsg()
	{
		MessageBox(0,str,"QMSG",MB_ICONINFORMATION);
	}
	inline void ClearString()
	{
		for(int z = 0; z < GetStringLength(); z++)
		{
			str[z] = 0;
		}
	}
	inline void SetWindowText(HWND hwnd)
	{
		SendMessage(hwnd,WM_SETTEXT,strlen(str),(LPARAM)(LPCSTR)str);
	}
	inline void AddToList(HWND hwnd)
	{
		SendMessage(hwnd,LB_ADDSTRING,strlen(str),(LPARAM)(LPCSTR)str);
	}
	inline void AddToCombo(HWND hwnd)
	{
		SendMessage(hwnd,CB_ADDSTRING,strlen(str),(LPARAM)(LPCSTR)str);
	}

	inline void CopyTextFromHWND(HWND hwnd)
	{
		char* buffer;
		int len;
		len = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
		buffer = new char[len+1];
		SendMessage(hwnd,WM_GETTEXT,len,(LPARAM)(LPCSTR)buffer);
		
		set(len+1,buffer);

		delete [] buffer;
	}
	
	inline void AttachTextFromHWND(HWND hwnd)
	{
		char* buffer;
		int len;
		len = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
		buffer = new char[len+1];
		SendMessage(hwnd,WM_GETTEXT,len,(LPARAM)(LPCSTR)buffer);
		
		add(buffer);

		delete [] buffer;
	}
	inline void ReplaceCharacter(char findchr,char replace)
	{
		mstr_replacechar(str,findchr,replace);
	}
	inline void RandomizeString()
	{
		randomstr(str,255,strlen(str));
	}
	inline void ReplaceString(char* search, char* replacestr)
	{
		if(mstr_findstr(str,search) != -1)
		{

		char* output;
		output = new char[strlen(str)+10];
		mstr_replacestr(str,search,replacestr,output);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
		
		}
	}
	inline void RemoveCharacters(char c)
	{
		char* output;
		output = new char[strlen(str)+10];
		mstr_removechar(str,output,c);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}
	inline void RemoveString(char* search)
	{
		if(mstr_findstr(str,search) != -1)
		{
			char* output;
			output = new char[strlen(str)+10];
			mstr_removestr(str,output,search);
			set(strlen(output)+10,output);
			delete [] output;
			output = 0;
		}
	}
	inline void RemoveSingleInstanceOfString(char* search)
	{
		if(mstr_findstr(str,search) != -1)
		{
			char* output;
			output = new char[strlen(str)+10];
			rmvstrx(str,output,search);
			set(strlen(output)+10,search);
			delete [] output;
			output = 0;
		}
	}
	inline void SaveToFile(char* filename)
	{
		mstr_savestr(filename,str);
	}
	inline void LoadStringFromFile(char* filename)
	{
		if(getfilestringlength(filename) == -1)
		{
			return; // failure file not found
		}

		char* temp;
		temp = new char[getfilestringlength(filename)+20];
		mstr_loadstr(filename,temp);
		set(strlen(temp)+20,temp);
		delete [] temp;
		temp = 0;
	}
	inline bool IsStringValid()
	{
		return mstr_isstrvalid(str);
	}

	inline int ReverseString() // reverse the string
	{
		char* temp;
		temp = new char[GetStringLength()+10];

		reversestring(str,temp);
		set(strlen(temp)+10,temp);

		delete [] temp;
		temp = 0;
	}

	inline bool StringCompare(char* buff)
	{
		return mstr_mstrcmp(str,buff);
	}
	inline bool StringCompare_NOCASE(char* buff)
	{
		return mstr_mstrcmpl(str,buff);
	}
	inline bool IsInsideString(char* buff)
	{
		return mstr_insidestr(str,buff);
	}
	inline bool IsInsideString_NOCASE(char* buff)
	{
		return mstr_insidestrl(str,buff);
	}
	inline void SeperateString(char* lbuff,int lpos,char* rbuff,int rpos)
	{
		mstr_strsep(str,lbuff,lpos,rbuff,rpos);
	}
	inline void AsmTrim()
	{
		// trim string as tho it were assembly language source
		char* output;
		output = new char[GetStringLength()+10];
		asmtrim(str,output);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}

	inline void TrimComments(char start_c,char stop_c)
	{
		char* output;
		output = new char[GetStringLength()+10];
		trimcom(str,output,start_c,stop_c);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}
};

// MasterString Item Structure 
struct ListItem
{
	int list_index;

	inline void setindex(int i)
	{
		list_index = i;
	}

	inline int getindex()
	{
		return list_index;
	}
};

struct MasterStringItem : MasterString,ListItem
{
	bool on;

	inline MasterStringListItem()
	{
		on = false;
	}

	inline void seton(bool x)
	{
		on = x;
	}

	inline bool geton()
	{
		return on;
	}
};

// example of a list using MasterStrings
struct MasterStringList 
{
	MasterStringItem* item;
	bool ion;
	int array_size;
	int off;

	inline MasterStringList()
	{
		ion = false;
		off = 0;
	}

	inline ~MasterStringList()
	{
		if(ion == true)
		{
			delete [] item;
			item = NULL;
		}
	}

	inline MasterStringList(int size)
	{
		createList(size);
	}
	
	inline void createList(int size)
	{
		item = new MasterStringItem[size];
		ion = true;
		array_size = size;
	}

	inline int  GetArraySize()
	{
		return array_size;
	}

	inline char* GetListStringPointerByIndex(int index)
	{
		return item[index].get();
	}

	inline int AddString(char* buffer)
	{
  		item[off].set(strlen(buffer)+10,buffer);
		int xoff = off;
		off++;
		return xoff;
	}

	inline int GetListLength()
	{
		return off;
	}

	inline void GetString(int index,char* output)
	{
		strcpy(output,item[index].get());
		
	}


	inline void Clear()
	{
		for(int i = 0; i < off; i++)
		{
			item[i].ClearString();
		}

		off = 0;
	}
};

struct MasterEntry : ListItem
{
	MasterString name;
	MasterString value;
	bool on_switch;

	inline MasterEntry()
	{
		name = "";
		value = "";
		on_switch = false;
	}

	inline bool amion()
	{
		return on_switch;
	}

};

// easy to use INI object, using MasterStrings
struct MasterINI
{
	MasterEntry* masEntry;
	bool mas_on;
	int array_size;
	int off_count;

	// constructors/deconstructors

	inline MasterINI()
	{
		masEntry = 0;
		mas_on = false;
		off_count = 0;
	}
	
	inline MasterINI(int size)
	{
		set(size);
	}

	inline ~MasterINI()
	{
		if(mas_on)
		{
			delete [] masEntry;
			masEntry = 0;
		}
	}

	inline set(int size)
	{
		if(mas_on == true)
		{
			delete [] masEntry;
			masEntry = 0;
		}

		masEntry = new MasterEntry[size];
		mas_on = true;
		array_size = size;
		off_count = 0;
	}

	inline int getsize()
	{
		return array_size;
	}

	inline void Create(int size)
	{
		set(size);
	}

	inline bool AddEntry(char* name,char* value)
	{
		if(off_count < getsize())
		{


		masEntry[off_count].name = name;
		masEntry[off_count].value = value;
		masEntry[off_count].list_index = off_count;

		off_count++;
		return true;
		}

		return false;
	}

	inline bool GetEntry(char* name,char* output_value)
	{
		for(int i = 0; i < getsize(); i++)
		{
			if(findstr(masEntry[i].name.get(),name) != -1)
			{
				stringcopy(output_value,masEntry[i].value.get());
				return true;
			}
		}

		strcpy(output_value,"*NULL*");
		return false;
	}
};

bool SaveMasterINI(char* filename,MasterINI* mini); // Save INI
bool LoadMasterINI(char* filename,MasterINI* mini); // Load INI

struct MasCharList // char list based on the \n (breaks strings into lines) (for use with MasAsm)
{
	MasterString* list;
	bool list_on;
	int array_size;
	int list_len;


	inline MasCharList()
	{
		list = 0;
		list_on = false;
	}

	inline MasCharList(char* buff)
	{
		BuildList(buff);
	}

	inline ~MasCharList()
	{
		if(list_on == true)
		{

		delete [] list;
		list = 0;

		}
	}

	inline void BuildList(char* buff)
	{
		int size;
		size = countlines(buff) + 1;
		list = new MasterString[size];
		list_on = true;
		array_size = size;
		// format the characters into this array
		int pre_pos = 0;
		int acount = 0;

		while(1)
		{
			int find_x;
			find_x = ifindstr(pre_pos,buff,"\n");
			
			if(find_x == -1)
			{
				break;// all done !
			}

			
			char* temp;
			temp = new char[strlen(buff)+1];

			midcopy(buff,temp,pre_pos,find_x);
			pre_pos = find_x;
		
			// add
			list[acount] = temp;
			acount++;
		

			delete [] temp;
			temp = 0;

		}

		list_len = acount;

	}

	inline int GetLength()
	{
		return list_len;
	}

	inline MasterString* GetMasterString(int index)
	{
		return (MasterString*)&list[index];
	}

};


// string copy
void stringcopy(char* input,char* output)
{
	strcpy(input,output);
}

// string attach
void stringattach(char* input,char* output)
{
	strcat(input,output);
}

// left copy
void leftcopy(char* input,char* output,int pos)
{
	int index = 0;
	for(int i = 0; i < pos; i++)
	{
		output[index] = input[i];
		index++;
	}
	output[index] = 0;
}
// right copy
void rightcopy(char* input,char* output,int pos)
{
	int index = 0;
	int len = strlen(input);
	for(int i = pos; i < len; i++)
	{
		output[index] = input[i];
		index++;
	}
	output[index] = 0;

}
// mid copy
void midcopy(char* input,char* output,int start_pos, int stop_pos)
{
	int index = 0;
	for(int i = start_pos; i < stop_pos; i++)
	{
		output[index] = input[i];
		index++;
	}

	output[index] = 0;
}

// trim the space
void trimspace(char* buffer)
{
	int len;
	len = strlen(buffer);
	char* ptemp;
	ptemp = new char[len+1];
	strcpy(ptemp,buffer);

	int index = 0;
	for(int z = 0; z < len; z++)
	{
		if(ptemp[z] != ' ')
		{
			buffer[index] = ptemp[z];
			index++;
		}
	}
	buffer[index] = 0;

	delete [] ptemp;
}

int findstr(char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search); // search len

	for(int i = 0; i < len; i++)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i;
			}
		}
	}

	return -1; // failure
}

int ifindstr(int startx,char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search); // search len

	for(int i = startx+1; i < len; i++)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i;
			}
		}
	}

	return -1; // failure
}

int findstrb(char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search);

	for(int i = len; i > 0; i--)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it
			}
		}

	}
	return -1; // failure
}
// find inside backwards string loop
int ifindstrb(int startx, char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search);

	for(int i = startx-1; i > 0; i--)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it
			}
		}

	}
	return -1; // failure
}
// forward search string (controled range) 
int fsearchstr(int start,int stop,char* buff,char* search)
{
	int len = strlen(buff);
	int len2 = strlen(search);

	for(int i = start; i < stop; i++)
	{
		if(buff[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
			  return i; // found it
			}
		}
	}

	return -1; // failure
}

// backward search string (controled range)
int bsearchstr(int start,int stop,char* buff,char* search)
{
	int len = strlen(buff);
	int len2 = strlen(search);

	for(int i = start; i > stop; i--)
	{
		if(buff[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it;
			}
		}
	}

	return -1;// failure
}
// getting length
int getlen(char* buff)
{
	return strlen(buff);// use strlen :)
}
// lower case
void lcase(char* buffer)
{
	int len = getlen(buffer);

	for(int i = 0; i < len; i++)
	{
		buffer[i] = tolower(buffer[i]);
	}
}
// upercase
void ucase(char* buffer)
{
	int len = getlen(buffer);

	for(int i = 0; i < len; i++)
	{
		buffer[i] = toupper(buffer[i]);
	}
}
// uppercase letter
int ucasel(char c)
{
	return tolower(c);
}

// lowercase letter
int lcasel(char c)
{
	return tolower(c);
}

// find string location algorithims
bool findstrloc(char* buff,char* search,MasStrDataLoc* dloc)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	int* f;
	int  f_i = 0;
	f = new int[len+1];// big just in case

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;
				
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{

				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				f[f_i] = i;
				f_i++;
			}
		}
	}

	dloc->create_array(f_i);
	dloc->setstr(buff);
	dloc->setsearchstr(search);
	for(int p = 0; p < f_i; p++)
	{
		dloc->dindex[p] = f[p];
	}
	delete [] f;

	if(f_i != 0)
	{
		dloc->setstatus(true);
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus(false); 
		return false; // not found
	}
}
// find string location forward search
bool findstrlocf(char* buff,char* search,MasStrDataLoc* dloc)
{
	return findstrloc(buff,search,dloc);
}
// find string location backwards search
bool findstrlocb(char* buff,char* search,MasStrDataLoc* dloc)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	int* f;
	int  f_i = 0;
	f = new int[len+1];// big just in case

	for(int i = len; i > 0; i--)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;
				
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{

				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				f[f_i] = i;
				f_i++;
			}
		}
	}

	dloc->create_array(f_i);
	dloc->setstr(buff);
	dloc->setsearchstr(search);
	for(int p = 0; p < f_i; p++)
	{
		dloc->dindex[p] = f[p];
	}
	delete [] f;

	if(f_i != 0)
	{
		dloc->setstatus(true);
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus(false);
		return false; // not found
	}
}

// string ( range based ) manipulation algorithims
bool searchrange(char* buff,char* search,MasStrRange* mrang)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ik = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ik = false;
				}
			}

			if(ik == true)
			{
				mrang->SetRange(i,i+len2);
				return true;
			}
		}
	}
	mrang->SetRange(0,0);
	return false;
}
// string range manipluation ex (i)
bool isearchrange(int startx, char* buff,char* search,MasStrRange* mrang)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	for(int i = startx+1; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ik = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ik = false;
				}
			}

			if(ik == true)
			{
				mrang->SetRange(i,i+len2);
				return true;
			}
		}
	}
	mrang->SetRange(0,0);
	return false;
}

// find the occourance amount of a specific string
int findoccourance(char* buff,char* search)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	int occ = 0;

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				occ++;
			}

		}
	}

	if(occ == 0)
	{

	return -1; // failure

	}
	else
	{
		return occ;
	}
}

// string range manipulation copy left range
void copyleftrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
{
	if(hi_lo == MRANGE_HI)
	{
		leftcopy(input,output,mrang->GetRangeHI());
	}
	else
	{
		leftcopy(input,output,mrang->GetRangeLO());
	}
}
// string range manipulation copy right range
void copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
{
	if(hi_lo == MRANGE_HI)
	{
		rightcopy(input,output,mrang->GetRangeHI());
	}
	else
	{
		rightcopy(input,output,mrang->GetRangeLO());
	}
}
// string range manipulation mid copy
void copymidrange(char* input,char* output,MasStrRange* mrang, int hi_lo,MasStrRange* mrangx, int hi_lox)
{
	int cx;
	int cy;

	if(hi_lo == MRANGE_HI)
	{
		cx = mrang->GetRangeHI();
	}
	else
	{
		cx = mrang->GetRangeLO();
	}

	if(hi_lox == MRANGE_HI)
	{
		cy = mrangx->GetRangeHI();
	}
	else
	{
		cy =mrangx->GetRangeLO();
	}

	midcopy(input,output,cx,cy);
}

// create a list from string data
void createstrlist(char* buff,char* search,MasStrList* list)
{
	int occ;
	occ = findoccourance(buff,search);

	if(occ == -1)
	{
		return; // failure
	}
	list->create(occ);

	int occ_i = 0;

	MasStrDataLoc dloc;

	if(findstrloc(buff,search,&dloc))
	{
		int pre_pos = 0;

		for(int z = 0; z < dloc.getmaxpoint(); z++)
		{
			int cur = 0;
			cur = dloc.dindex[z];
			charwrap cwrap(buff);
			cwrap.strclearn();
			midcopy(buff,cwrap.get(),pre_pos,cur);
			list->strings[occ_i].set(cwrap.get());
			occ_i++;
			pre_pos = cur;
		}

		charwrap cwrapx(buff,true);
		rightcopy(buff,cwrapx.get(),pre_pos);
		list->strings[occ_i].set(cwrapx.get());
		occ_i++;
		}

	return;
}
// conversion of integers
void convertinteger(int integer,char* buff,int base)
{
	itoa(integer,buff,base);
}
// conversion of strings
int convertstring(char* buff)
{
	return atoi(buff);
}
// could this be a hexidecimal digit?
bool ishexc(char c)
{
	c = lcasel(c);
	switch(c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		return true;
		break;
	}
	return false;
}
// does this string contain a non-hexidecimal digit?
bool ishex(char* buff)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(ishexc(buff[i]) == false)
		{
			return false;
		}
	}
	return true;
}

// hexidecimal digit to integer value
int hextointc(char c)
{
	if(ishexc(c) == false)
	{
		return -1; // failure, not a hex digit
	}

	c = lcasel(c);

	switch(c)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	case 'a':
		return 10;
		break;
	case 'b':
		return 11;
	case 'c':
		return 12;
	case 'd':
		return 13;
	case 'e':
		return 14;
	case 'f':
		return 15;
	}

	return -1; // failure ? never would get here
}

// convert hex value into a integer
int hextoint(char* buff)
{
	int rt = 0;

	if(buff[1] == 0)
	{
		return hextointc(buff[0]);
	}

	int len = strlen(buff);
	int* hexval;
	hexval = new int[len+1];
	int  hexvali = 0;

	for(int i = 0; i < len; i++)
	{
		hexval[hexvali] = hextointc(buff[i]);
		hexvali++;
	}

    int index = 0;

	for(int z = hexvali-1; z >= 0; z--)
	{
		int cur;
		if(index == 0)
		{
			cur = hexval[z];
			index = 16;
		}
		else
		{

		cur = hexval[z] * index;
		index = index * 16;
		}
		
		rt = rt + cur;
	}

	delete [] hexval;

	return rt;
} 


void tripcharup(char* buff, int up)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] != 0)
		{

		buff[i] = buff[i] + up;

		}
	}
}

void tripchardown(char* buff,int up)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] != 0)
		{

		buff[i] = buff[i] - up;

		}
	}
}
// replace single instance of a character
void replacechar(char* buff,char findchr,char replace)
{
	int len;
	len = strlen(buff);

	for(int z = 0; z < len; z++)
	{
		if(buff[z] == findchr)
		{
			buff[z] = replace;
		}
	}
}

void rmvinst(char* buff,char* findstr,char* replacex,char* output)
{

	int xt = ifindstr(NOPREV,buff,findstr);


	char* temp;
	temp = new char[strlen(buff)+1];
	stringcopy(temp,buff);

	char* ltemp;
	char* rtemp;

	ltemp = new char[strlen(buff)+1];
	rtemp = new char[strlen(buff)+1];

	leftcopy(buff,ltemp,xt);
	rightcopy(buff,rtemp,xt+strlen(findstr));


	cout << "\n#: " << ltemp << replacex << rtemp << endl;

	
	strcpy(output,ltemp);
	strcat(output,replacex);
	strcat(output,rtemp);

	delete [] temp;
	delete [] ltemp;
	delete [] rtemp;
}


// replace string
void replacestr(char* buff,char* findstr,char* replacex,char* output)
{
	int xt;
	xt = ifindstr(0,buff,findstr);

	if(xt == -1)
	{
		return; // failure no string to replace
	}

	char* ptemp;
	char* outtemp;
	ptemp = new char[strlen(buff) + 500];
	outtemp = new char[strlen(buff) + 500];
	stringcopy(ptemp,buff);

	while(1)
	{
		int xr;
		xr = ifindstr(0,ptemp,findstr);
		if(xr == -1)
		{
			break;
		}
		else
		{
			rmvinst(ptemp,findstr,replacex,outtemp);
			stringcopy(ptemp,outtemp);
		}
	}

	stringcopy(output,ptemp);

	delete [] ptemp;
	delete [] outtemp;

}

// random char
char randomchar(int max)
{
	int x;
	x = rand()%max;
	char c;
	c = x;
	return c;
}
// random char + up
char randomchar(int max,int up)
{
	int x;
	x = rand()%max+up;
	char c;
	c = x;
	return c;
}
// random string
void randomstr(char* buff,int max, int size)
{
	for(int i = 0; i < size; i++)
	{
		if(rand()%2)
		{
			buff[i] = randomchar(max);
		}
		else
		{
			buff[i] = randomchar(max,rand()%10);
		}
	}
}
// remove char
void removechar(char* in,char* out,char c)
{
	int len;
	len = strlen(in);
	int ic = 0;
	for(int i = 0; i < len; i++)
	{
		if(in[i] != c)
		{
			out[ic] = in[i];
			ic++;
		}
	}
	out[ic] = 0;
}

// find single character in string
int findchar(char* str,char c)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1; // failure
}
// find char ex (inside)
int ifindchar(int start,char* str,char c)
{
	int len = strlen(str);
	for(int i = start+1; i < len; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1;
}
// find single char backward
int findcharb(char* str,char c)
{
	int len;
	len = strlen(str);
	for(int i = len; i > 0; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1;
}
// find single char backward
int ifindcharb(int start,char* str,char c)
{
	int len;
	len = strlen(str);
	for(int i = start-1; i > 0; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	return -1;
}

int  findcharcf(char* str,int start,int stop,char c)
{
	for(int i = start; i < stop; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1; // failure
}
int  findcharcb(char* str,int start,int stop,char c)
{
	for(int i = stop; i > start; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	return -1;// failure
}
// remove instances of string
void removestr(char* input,char* output,char* string)
{

	char* buff = input;
	char* findstr = string;

	int xt;
	xt = ifindstr(NULLPOS,buff,findstr);

	if(xt == -1)
	{
		return; // failure no string to replace
	}

	char* ptemp;
	char* outtemp;
	ptemp = new char[strlen(buff) + 500];
	outtemp = new char[strlen(buff) + 500];
	stringcopy(ptemp,buff);

	while(1)
	{
		int xr;
		xr = ifindstr(0,ptemp,findstr);
		if(xr == -1)
		{
			break;
		}
		else
		{
			rmvstrx(ptemp,findstr,outtemp);
			stringcopy(ptemp,outtemp);
		}
	}

	stringcopy(output,ptemp);

	delete [] ptemp;
	delete [] outtemp;

}

void rmvstrx(char* buff,char* output,char* string)
{
	int xt = ifindstr(NOPREV,buff,string);

	char* temp;
	temp = new char[strlen(buff)+1];
	stringcopy(temp,buff);

	char* ltemp;
	char* rtemp;

	ltemp = new char[strlen(buff)+1];
	rtemp = new char[strlen(buff)+1];

	leftcopy(buff,ltemp,xt);
	rightcopy(buff,rtemp,xt+strlen(string));
	
	strcpy(output,ltemp);
	strcat(output,rtemp);

	delete [] temp;
	delete [] ltemp;
	delete [] rtemp;
}

void strsavefile(char* filename,char* buff)
{
	ofstream fout(filename);

	fout << buff;

	fout.close();
}

int getfilestringlength(char* filename)
{
	int count = 0;
	ifstream fin(filename);
	if(fin)
	{
		char ch;
		while(fin.get(ch))
		{
			count++;
		}

		fin.close();
		return count;

	} else { return -1; } // failure

	return -1;
}

bool strloadfile(char* file,char* output)
{
	int count = 0;
	ifstream fin(file);
	if(fin)
	{
		char ch;
		int str_i = 0;
		while(fin.get(ch))
		{
			output[str_i] = ch;
			str_i++;
		}

		output[str_i] = 0;
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

void reversestring(char* input,char* output)
{
	int len;
	len = strlen(input);
	int fcount = 0;

	for(int i = len; i > 0; i--)
	{
		output[fcount] = input[i];
		fcount++;
	}
	
	output[fcount] = 0;
}

bool isstrvalid(char* string)
{
	int len = strlen(string);
	for(int i = 0; i < len; i++)
	{
		if(string[i] == 0)
		{
			return true; // true it is a null terminated string!
		}
	}

	return false;
}

// Save Master INI
bool SaveMasterINI(char* filename,MasterINI* mini)
{
	ofstream fout(filename,ios::binary);

	if(fout)
	{


	fout.write((char*)&mini,sizeof(mini));

	fout.close();

	return true;

	}
	fout.close();
	return false;
}
// Load master INI
bool LoadMasterINI(char* filename,MasterINI* mini)
{
	ifstream fin(filename,ios::binary);

	if(fin)
	{
		fin.read((char*)&mini,sizeof(mini));
	}
	
	fin.close();
	return false;
}

// string compare (case sensitive)
bool mstrcmp(char* buff1,char* buff2)
{
	int len;
	int len2;
	len = strlen(buff1);
	len2 = strlen(buff2);

	if(len != len2)
	{
		return false; // not equal length
	}

	for(int i = 0; i < len; i++)
	{
		if(buff1[i] != buff2[i])
		{
			return false;
		}
	}

	return true;
}

// string compare (not case sensitive)
bool mstrcmpx(char* buff1,char* buff2)
{
	int len;
	int len2;
	len = strlen(buff1);
	len2 = strlen(buff2);

	if(len != len2)
	{
		return false; // not equal length
	}

	for(int i = 0; i < len; i++)
	{
		if(tolower(buff1[i]) != tolower(buff2[i]))
		{
			return false;
		}
	}

	return true;
}

bool insidestr(char* buff1,char* buff2)
{
	int chk;
	chk = findstr(buff1,buff2);

	if(chk == -1)
	{
		return false;
	}
	
	return true;
}

bool insidestrx(char* buff1,char* buff2)
{
	char* pbuff1;
	char* pbuff2;

	pbuff1 = new char[strlen(buff1)+1];
	pbuff2 = new char[strlen(buff2)+1];

	stringcopy(pbuff1,buff1);
	stringcopy(pbuff2,buff2);

	lcase(pbuff1);
	lcase(pbuff2);

	int chk;
	chk = findstr(pbuff1,buff2);

	delete [] pbuff1;
	delete [] pbuff2;
	pbuff1 = 0;
	pbuff2 = 0;

	if(chk == -1)
	{
		return false;
	}
	
	return true;
}
// string seperation from 2 points
void strsep(char* str, char* sleft, int go_left, char* sright, int go_right)
{
	leftcopy(str,sleft,go_left);
	rightcopy(str,sright,go_right);
}
void strsetnull(char* str,int pos)
{
	str[pos] = 0;
}

void rmvnullset(char* str)
{
	int len;
	len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == 0)
		{
			str[i] = ' ';
		}
	}
}

int getnullpos(char* str)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == 0)
		{
			return i;
		}
	}

	return -1; // failure to find 0
}
// trim commented characters () 
void trimcom(char* str, char* output,char start_c,char stop_c)
{
	int len = strlen(str);
	int index = 0;

	bool iadd = true;

	for(int z = 0; z < len; z++)
	{
		if(str[z] == start_c)
		{
			iadd = false; 
		}

		if(str[z] == stop_c)
		{
			iadd = true;
		}

		if(iadd == true)
		{
			output[index] = str[z];
			index++;
		}
	}
	
	output[index] = 0;
}

// trim comments to an assembly language source file
void asmtrim(char* input,char* output)
{
	trimcom(input,output,';','\n');
}

// count the number of lines exisitng within the source
int countlines(char* buffer)
{
	return findoccourance(buffer,"\n");
}
// get the first letter thats not a space
int getfirstletter(char* buff)
{
	int len = strlen(buff);
	
	for(int i = 0; i < len; i++)
	{
		if(buff[i] != ' ')
		{
			return i;
		}
	}
	return -1; // failure! no letters
}

#endif
#endif

#ifdef MASTEROGL

/* MasterOGL (Master OpenGL) Engine

  written by Jared Bruni
  www.LostSideDead.com

  encapsulation of OpenGL initilization
  as well as adding in directX features

  dont forget to link to

  winmm.lib glu32.lib opengl32.lib wsock32.lib

*/


#include<windows.h>
#include<gl\gl.h>
#include<gl/glu.h>
#include<gl\glaux.h>
#include<stdio.h>

#define LBUTTON 1
#define RBUTTON 2
#define DEFAULT_PORT 02
#define JOY_DEADZONE 20 

long _stdcall event(struct HWND__* hwnd, unsigned int msg, unsigned int wparam, unsigned long lparam);
int _stdcall MasterMain();
inline void SetupPixelFormat(HDC hDC);

struct HWND__* hwnd;
struct HDC__* g_hDC;

void (*xkeypress)(int key);
void (*xmousemove)(int x, int y);
void (*xmouseclick)(int x, int y, int button);
bool Keys[255];


int _stdcall WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	return MasterMain();
}

long _stdcall event(struct HWND__* hwnd, unsigned int msg, unsigned int wparam, unsigned long lparam)
{
	static HGLRC hRC; // rendering context
	static struct HDC__* hDC; // device context
	static int width,height;
	static int x,y;
	
	switch(msg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		wglMakeCurrent(hDC,NULL);
		wglDeleteContext(hRC);
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			hDC = GetDC(hwnd);
			g_hDC = hDC;
			SetupPixelFormat(hDC);
			// create the reendering contest
			hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC,hRC);
		}
		break;
	case WM_SIZE:
		{
			width = HIWORD(lparam);
			height= LOWORD(lparam);
			
			if(height == 0)
			{
				height = 1;
			}
			
			glViewport(0,0,width,height);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			
			gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			return 0;
		}
		break;
	case WM_KEYDOWN:
		{
			xkeypress(wparam);
			Keys[wparam] = true;
		}
		break;
	case WM_KEYUP:
		{
			Keys[wparam] = false; // trick I learned from nehe's tutorials
		}
		break;
	case WM_MOUSEMOVE:
		{
			x = LOWORD(lparam);
			y = HIWORD(lparam);
			xmousemove(x,y);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			x = LOWORD(lparam);
			y = HIWORD(lparam);
			xmouseclick(x,y,LBUTTON);
		}
		break;
	case WM_RBUTTONDOWN:
		{
			x = LOWORD(lparam);
			y = HIWORD(lparam);
			xmouseclick(x,y,RBUTTON);
		}
		break;
	default: return DefWindowProc(hwnd,msg,wparam,lparam);
	}
	
	return (0);
}

class MasterOGLHWND
{
public:
	void CreateMasterOGL(char* title,int width, int height, bool fullscreen,HICON icon,HCURSOR cursor)
	{
		
		WNDCLASS wc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = NULL;
		wc.hCursor = cursor;//LoadCursor(NULL,IDC_ARROW);
		wc.hIcon = icon;//LoadIcon(NULL,IDI_APPLICATION);
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpfnWndProc = (WNDPROC) event;
		wc.lpszClassName = "MasterOGL";
		wc.lpszMenuName = NULL;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		
		RegisterClass(&wc);
		if(fullscreen == false)
		{

		hwnd = CreateWindow("MasterOGL",title,WS_OVERLAPPEDWINDOW,0,0,width,height,0,0,GetModuleHandle(NULL),0);

		}
		else
		{
		    init_fullscreen(width,height);
			hwnd = CreateWindow("MasterOGL",title,WS_POPUPWINDOW,0,0,width,height,0,0,GetModuleHandle(NULL),0);
		}

		ShowWindow(hwnd,SW_SHOW);
		UpdateWindow(hwnd);
		
	}

	void (*updatex)(int screen);
	bool done;
	int cur_screen;

	int InitLoop(void(*update)(int screen))
	{
		updatex = update;
		MSG msg;
		done = false;
		
		while(done == false)
		{
			PeekMessage(&msg,hwnd,NULL,NULL,PM_REMOVE);
			if(msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				// render
				updatex(cur_screen);
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			
		}

		return msg.wParam;
	}

	void SetScreen(int x)
	{
		cur_screen = x;
	}

	int GetScreen()
	{
		return cur_screen;
	}

	void Kill()
	{
		done = true;
	}

	void InitCallBacks(void(*keypressx)(int key),void (*mousemovex)(int x,int y),void (*mouseclickx)(int x,int y, int button))
	{
		xkeypress = keypressx;
		xmousemove = mousemovex;
		xmouseclick = mouseclickx;
	}

private:
	// initilize OpenGL, setup the pixel format
	inline void init_fullscreen(int w, int h)
	{
		DEVMODE dev;
		memset(&dev,0,sizeof(dev));
		
		dev.dmSize = sizeof(dev);
		dev.dmPelsWidth = w;
		dev.dmPelsHeight = h;
		dev.dmBitsPerPel = GetDeviceCaps(GetDC(NULL),BITSPIXEL);
		dev.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
		
		if(ChangeDisplaySettings(&dev,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			MessageBox(NULL,"Error couldnt change display mode","Error",MB_ICONERROR);
		}
	}
	
};
// set the pixel format
inline void SetupPixelFormat(HDC hDC)
{
	int nPixelFormat;
	int bits = GetDeviceCaps(GetDC(NULL),BITSPIXEL);
	
	
	static	PIXELFORMATDESCRIPTOR pfd=					{
		sizeof(PIXELFORMATDESCRIPTOR),					
			1,								
			PFD_DRAW_TO_WINDOW |						
			PFD_SUPPORT_OPENGL |						
			PFD_DOUBLEBUFFER,						
			PFD_TYPE_RGBA,							
			bits,								
			0, 0, 0, 0, 0, 0,						
			0,								
			0,								
			0,								
			0, 0, 0, 0,							
			bits,								
			0,								
			0,								
			PFD_MAIN_PLANE,							
			0,								
			0, 0, 0								
	};
	
	
	nPixelFormat = ChoosePixelFormat(hDC,&pfd);
	
	SetPixelFormat(hDC,nPixelFormat,&pfd);
}

// directX add-ons'


// initilize and kill winsock
void initwinsock();
void killwinsock();

// structure to automaticly initlize and kill winsock
struct AutoWinSockHandle
{
	inline AutoWinSockHandle()
	{
		initwinsock();
	}
	
	inline ~AutoWinSockHandle()
	{
		killwinsock();
	}
};

static AutoWinSockHandle sock_handle; // automaticly construct, and deconstruct
// winsock with this static structure

struct MasterSocket
{
	SOCKET socketx; // the socket structure
	HWND  hwnd; // handle of the window the socket is attached to
	UINT  SOCKET_ID; // socket ID
	void CreateSocket(HWND hwndx,UINT SOCKET_IDx);// create the socket
	void Listen(UINT port);// listen on the socket
	void Connect(char* ipaddress,UINT port);// connect with the socket
	void Send(char* buff, int len); // send data with a connected socket
	int Recive(char* buff,int len);// recive data
	void Accept(); // accept a incomin socket
	const UINT GetID();// get the ID of this socket
	void Close();// close the socket
};

// initilze windows sockets
void initwinsock()
{
	
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 1, 1 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		MessageBox(0,"Error Couldnt Init Winsock!","Aborting",MB_ICONINFORMATION);
		PostQuitMessage(0);
		return;
	}
	
	
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 ) {
		WSACleanup( );
		return;   
		
	}
}

// killwinsock, on lcose
void killwinsock()
{
	WSACleanup();
}

// the master socket data structure
void MasterSocket::CreateSocket(HWND hwndx, UINT SOCKET_IDx)
{
	hwnd = hwndx;
	SOCKET_ID = SOCKET_IDx;
	socketx = socket(AF_INET,SOCK_STREAM,0);
	WSAAsyncSelect(socketx,hwnd,SOCKET_ID,FD_CONNECT|FD_READ|FD_CLOSE|FD_ACCEPT);
}

// begin listening
void MasterSocket::Listen(UINT port)
{
	if(port == DEFAULT_PORT) { port = 7; }
	struct sockaddr_in addy;
	// begin watching on port 7
	addy.sin_family = AF_INET;
	addy.sin_port = htons(port);
	addy.sin_addr.s_addr = INADDR_ANY; //inet_addr("172.129.243.252");
   	bind(socketx,(struct sockaddr*)&addy,sizeof(addy));
	listen(socketx,5);
}
// connect to a remote socket
void MasterSocket::Connect(char* ipaddress,UINT port)
{
	struct sockaddr_in addy2;
	if(port == DEFAULT_PORT) { port = 7; }
	
	addy2.sin_family = AF_INET;
	addy2.sin_port = htons(port);
	addy2.sin_addr.s_addr = inet_addr(ipaddress);
	connect(socketx,(struct sockaddr*)&addy2,sizeof(addy2));
}
// accept a request from remote socket
void MasterSocket::Accept()
{
	struct sockaddr cli_addr;
    int clilen;
	clilen = sizeof(cli_addr);
	socketx = accept(socketx,(struct sockaddr*)&cli_addr,&clilen);
}

// send data once socket is connected
void MasterSocket::Send(char* buff, int len)
{
	send(socketx,buff,len,0);
}
// recive data from a connected socket
int MasterSocket::Recive(char* buff,int len)
{
	return recv(socketx,buff,len,0);
}
// get the ID of a given socket, for the wndproc callback
const UINT MasterSocket::GetID()
{
	return (const UINT)SOCKET_ID;
}
// close an open socket
void MasterSocket::Close()
{
	closesocket(socketx);
}

// masterjoystick

struct MasterJoyStick
{
	JOYINFOEX joystickInfoEx ;// information about are joystick
	JOYCAPS   joystickCaps; // caps structure
	bool joystickPresent;
	bool joystickHasThrottle;
	bool joystickActive;
	unsigned int joystickDeadXMin,joystickDeadXMax,joystickDeadYMin,joystickDeadYMax;
	unsigned int GetJoysticks(); // returns the number of joysticks the drivers support
	bool         JoyExisit(); // does a joystick exisit
	bool         SetupJoystick(); // setup the default joystick
	bool         GetJoystickCoords(JOYINFOEX* info); // get joystick coords structure
	bool         JoyStop();
	bool         JoyForward();
	bool         JoyBackward();
	bool         JoyRight();
	bool         JoyLeft();
	int          GetButtonPressed(JOYINFOEX*);
	int          JoyButtonDown();
	
	inline ~MasterJoyStick()
	{
		ZeroMemory(&joystickInfoEx,sizeof(joystickInfoEx));
	} 
};


//***********
// MasterJoyStick

// return how many joysticks there are
unsigned int MasterJoyStick::GetJoysticks()
{
	return joyGetNumDevs();
}
// does joysticks exisit
bool MasterJoyStick::JoyExisit()
{
	joystickInfoEx.dwSize = sizeof(JOYINFOEX);
	joystickPresent = (joyGetPosEx(JOYSTICKID1,&joystickInfoEx) == JOYERR_NOERROR);
	if(!joystickPresent)
	{
		return false;
	}
	
	return true;
}
// setup this joystick
bool MasterJoyStick::SetupJoystick()
{
	if(JoyExisit() == false)
	{
		return false;
	}
	
	joyGetDevCaps(JOYSTICKID1,&joystickCaps,sizeof(joystickCaps));
	joystickHasThrottle = (joystickCaps.wCaps & JOYCAPS_HASZ);
	int joystickDeadSize = (joystickCaps.wXmax - joystickCaps.wXmin) * JOY_DEADZONE / 100;
	joystickDeadXMax = (joystickCaps.wXmax - joystickCaps.wYmin) / 2 + (joystickDeadSize / 2);
	joystickDeadXMin = joystickDeadXMax - joystickDeadSize;
	joystickDeadSize = (joystickCaps.wYmax - joystickCaps.wYmin) * JOY_DEADZONE / 100;
	joystickDeadYMax = (joystickCaps.wYmax - joystickCaps.wYmin) / 2 + (joystickDeadSize / 2);
	joystickDeadYMin = joystickDeadYMax - joystickDeadSize;
	return true;
}
// get joystick cordinates
bool MasterJoyStick::GetJoystickCoords(JOYINFOEX* info)
{
	if(!joystickPresent) return false;
	info->dwSize  = sizeof(JOYINFOEX);
	info->dwFlags = JOY_RETURNX | JOY_RETURNY;
	return (!joyGetPosEx(JOYSTICKID1,info));
}
// is the joystick still
bool MasterJoyStick::JoyStop()
{
	if(!GetJoystickCoords(&joystickInfoEx)) return false;
	return (( joystickInfoEx.dwYpos > joystickDeadYMin) && (joystickInfoEx.dwYpos < joystickDeadYMax) &&
		(joystickInfoEx.dwXpos > joystickDeadXMin) &&
		(joystickInfoEx.dwXpos < joystickDeadXMax));
}

// is the joystick being pressed forward (UP)
bool MasterJoyStick::JoyForward()
{
	if(!GetJoystickCoords(&joystickInfoEx)) return false;
	return (joystickInfoEx.dwYpos < joystickDeadYMin);
}
// is the joystick being pressed backwards (DOWN)
bool MasterJoyStick::JoyBackward()
{
	if(!GetJoystickCoords(&joystickInfoEx)) return false;
	return(joystickInfoEx.dwYpos > joystickDeadYMax);
}
// is the joystick being pressed left 
bool MasterJoyStick::JoyLeft()
{
	if(!GetJoystickCoords(&joystickInfoEx)) return false;
	return(joystickInfoEx.dwXpos < joystickDeadXMin);
}
// is the joystick being pressed right
bool MasterJoyStick::JoyRight()
{
	if(!GetJoystickCoords(&joystickInfoEx)) return false;
	return (joystickInfoEx.dwXpos > joystickDeadXMax);
}
// get the currently pressed button
int MasterJoyStick::GetButtonPressed(JOYINFOEX* info)
{
	if(!joystickPresent) { return 0; }
	
	info->dwSize = sizeof(joystickInfoEx);
	info->dwFlags =  JOY_RETURNBUTTONS;
	joyGetPosEx(JOYSTICKID1,info);
	int x = info->dwButtonNumber;	
	return x;
}

// get the pressed button
int MasterJoyStick::JoyButtonDown()
{
	return GetButtonPressed(&joystickInfoEx);
}

#endif


#ifdef MASASM
/* MasterString2 
   string library

  written by Jared Bruni
  www.LostSideDead.com

  "Open  Source, Open Mind" 


  freestyle-> spin_it();
*/


#ifndef MASTERSTRING2
#define MASTERSTRING2



// optomized algorithms
// namespace for masterstring
namespace masterstring
{
	int i,z,j,len;
	bool check;
	unsigned int mstrlen(char* str);
	void mstrcpy(char* dest, char* source);
	void mstrcat(char* dest, char* source);
	void mstrleft(char* source,char* output,unsigned int pos);
	void mstrright(char* source,char* output, unsigned int pos);
	void mstrmid(char* source,char* output, unsigned int pos, unsigned int pos2);
	void mstrvbmid(char* source, char* output, unsigned int pos, unsigned int pos2);
	bool mstrcmp(char* string1,char* string2);
	void killspace(char* in, char* out);
	unsigned int mcharoccourance(char* source, char c);
	unsigned int mstrfind(char* source, char* string);
	unsigned int mstrifind(unsigned int start, char* source, char* string);
	unsigned int mstrbfind(char* source, char* string);
	unsigned int mstribfind(unsigned int start, char* source, char* string);

	/* tokenize class */

class Tokenize
{
	struct Token
	{
		char* str;
		Token()
		{
			str = NULL;
		}

		~Token()
		{
			if(str != NULL)
			{
				delete [] str;
				str = NULL;
			}

		}

		void set(char* xstr)
		{
			if(str != NULL)
			{
				delete [] str;
				str = NULL;
			}

			str = new char [ masterstring::mstrlen(xstr) + 1 ];
			masterstring::mstrcpy(str,xstr);
		}
	};

	Token* tokens;
	int off_pos;

	int tokencount(char* s, char c)
	{
		int amt = 0;

		for(unsigned int i = 0; i < masterstring::mstrlen(s); i++)
		{
			if(s[i] == c)
			{
				amt++;
			}
		}
	
		return amt;
	}


public:

	Tokenize()
	{
		tokens = NULL;
	}

	~Tokenize()
	{
		if(tokens != NULL)
		{
			delete [] tokens;
			tokens = NULL;
		}

	}
	int length;

	void tokenize(char* str, char sep)
	{
		off_pos = 0;
		length = 0;

		if(tokens != NULL)
		{
			delete [] tokens;
			tokens = NULL;
		}

		if(tokencount(str,sep) == 0)
		{
			return;
		}

		tokens = new Token[tokencount(str,sep) + 1 ];
	 
		for(unsigned int i = 0; i < masterstring::mstrlen(str); i++)
		{
			if(str[i] == sep)
			{
				char* temp = new char [ masterstring::mstrlen(str) + 1 ];
				masterstring::mstrmid(str,temp,off_pos,i);
				tokens[length].set(temp);
				length++;
				off_pos = i + 1;
				delete [] temp;
				temp = NULL;
			}
		}

		char* temp = new char [ masterstring::mstrlen(str) + 1 ];
		masterstring::mstrright(str,temp,off_pos);
		tokens[length].set(temp);
		length++;
		delete [] temp;
	}

	char* operator[](int pos)
	{
		if(pos >= 0 && pos < length)
		{
			return tokens[pos].str;
		}

		return NULL;
	}

};

	/* tokenize quotes class */

class TokenizeQuotes
{
	struct Token
	{
		char* str;
		Token()
		{
			str = NULL;
		}

		~Token()
		{
			if(str != NULL)
			{
				delete [] str;
				str = NULL;
			}

		}

		void set(char* xstr)
		{
			if(str != NULL)
			{
				delete [] str;
				str = NULL;
			}

			str = new char [ masterstring::mstrlen(xstr) + 1 ];
			masterstring::mstrcpy(str,xstr);
		}
	};

	Token* tokens;
	int off_pos;

	int tokencount(char* s, char c)
	{
		int amt = 0;
		bool go = true;

		for(unsigned int i = 0; i < masterstring::mstrlen(s); i++)
		{
			if(s[i] == '\"') 
			{
				go = !go;
			}


			if(s[i] == c && go == true)
			{
				amt++;
			}
		}
	
		return amt;
	}


public:

	TokenizeQuotes()
	{
		tokens = NULL;
	}

	~TokenizeQuotes()
	{
		if(tokens != NULL)
		{
			delete [] tokens;
			tokens = NULL;
		}

	}
	int length;

	void tokenize(char* str, char sep)
	{
		off_pos = 0;
		length = 0;

		if(tokens != NULL)
		{
			delete [] tokens;
			tokens = NULL;
		}

		if(tokencount(str,sep) == 0)
		{
			return;
		}

		tokens = new Token[tokencount(str,sep) + 1 ];
		bool go = true;

		for(unsigned int i = 0; i < masterstring::mstrlen(str); i++)
		{
			if(str[i] == '\"')
			{
				go = !go;
			}


			if(str[i] == sep && go == true)
			{
				char* temp = new char [ masterstring::mstrlen(str) + 1 ];
				masterstring::mstrmid(str,temp,off_pos,i);
				tokens[length].set(temp);
				length++;
				off_pos = i + 1;
				delete [] temp;
				temp = NULL;
			}
		}

		char* temp = new char [ masterstring::mstrlen(str) + 1 ];
		masterstring::mstrright(str,temp,off_pos);
		tokens[length].set(temp);
		length++;
		delete [] temp;
	}

	char* operator[](int pos)
	{
		if(pos >= 0 && pos < length)
		{
			return tokens[pos].str;
		}

		return NULL;
	}

};

}

/*************************  string algorithms **********************************************/

// mstrlen  - get string length
unsigned int masterstring::mstrlen(char* str)
{
    char* temp = str;
	i = 0;
	while( *temp++)
	{
		i++;
	}

	return i;
}
// mstrcpy - string copy
void masterstring::mstrcpy(char* dest,char* source)
{
	z =  mstrlen(source);
	for(i = 0; i < z; i++)
	{
		dest[i] = source[i];
	}
	dest[z] = 0;
}

// mstrcat - string concatination
void masterstring::mstrcat(char* dest,char* source)
{
	z = mstrlen(source);
	j = mstrlen(dest);
	for(i = 0; i < z; i++)
	{
 		dest[i+j] = source[i];
	}
	dest[j+z] = 0;

}

// mstrleft - left string copy 
void masterstring::mstrleft(char* source,char* output,unsigned int pos)
{
	for(i = 0; i < (int) pos; i++)
	{
		output[i] = source[i];
	}
	output[pos] = 0;
}

// mstrright - right string copy
void masterstring::mstrright(char* string,char* output, unsigned int pos)
{
	len = mstrlen(string);
    z = 0;
	for(i = pos; i < len; i++)
	{
    	output[z] = string[i];
		z++;
	}
	
	output[z] = 0;
}
// mstrmid - middle string copy
void masterstring::mstrmid(char* string,char* out, unsigned int start, unsigned int stop)
{
	z = 0;
	for(i = start; i < (int) stop; i++)
	{
		out[z] = string[i];
		z++;
	}
	out[z] =0;
}
// mstrvbmind - middle string copy vb style
void masterstring::mstrvbmid(char* source, char* output, unsigned int start, unsigned int length)
{
	z = 0;
	for(i = start; i < (int)start+(int)length; i++)
	{
		output[z] = source[i];
		z++;
	}
	output[z] = 0;	
}
// mstrcmp - string compare
bool masterstring::mstrcmp(char* string1,char* string2)
{
	len = mstrlen(string1);
	z = mstrlen(string2);
	if(len != z)
	{
		return false;
	}

	for(i = 0; i < len; i++)
	{
		if( string1[i] != string2[i] )
		{
			return false;
		}
	}
	return true;
}

// killspace - kill space from a string
void masterstring::killspace(char* in, char* out)
{
	j = mstrlen(in);
	z = 0;
	for(i = 0; i < j; i++)
	{
		if(in[i] != ' ')
		{

		out[z] = in[i];
		z++;

		}
	}
	out[z] = 0;
}

// mcharoccourance - find number of occourances of a char
unsigned int masterstring::mcharoccourance(char* source, char c)
{
	z = 0;
	j = mstrlen(source);
	for(i = 0; i < j; i++)
	{
		if(source[i] == c)
		{
			z++;
		}
	}

	return z;
}

// mstrfind - find a string within a string
unsigned int masterstring::mstrfind(char* source, char* string)
{
	j = mstrlen(source);
	len = mstrlen(string);
	for(i = 0; i < j; i++)
	{
		if(source[i] == string[0])
		{
			check = true;

			for(z = 0; z < len; z++)
			{
				if(source[i+z] != string[z])
				{
					check = false;
				}
			}

			if(check == true)
			{
				return i;
			}
		}
	}

	return -1; // fail
}

//mstrifind - master string start pos find
unsigned int masterstring::mstrifind(unsigned int start, char* source, char* string)
{
	j = mstrlen(source);
	len = mstrlen(string);
	for(i = start; i < j; i++)
	{
		if(source[i] == string[0])
		{
			check = true;

			for(z = 0; z < len; z++)
			{
				if(source[i+z] != string[z])
				{
					check = false;
				}
			}

			if(check == true)
			{
				return i;
			}
		}
	}

	return -1; // fail
}

// mstrbfind - string backwards find
unsigned int masterstring::mstrbfind(char* source, char* string)
{
	j = mstrlen(source);
	len = mstrlen(string);
	for(i = j; i >= 0; i--)
	{
		if(source[i] == string[0])
		{
			check = true;

			for(z = 0; z < len; z++)
			{
				if(source[i+z] != string[z])
				{
					check = false;
				}
			}

			if(check == true)
			{
				return i;
			}
		}
	}

	return -1; // fail
}

// mstribfind - string backwards position find
unsigned int masterstring::mstribfind(unsigned int start, char* source, char* string)
{
	j = mstrlen(source);
	len = mstrlen(string);
	for(i = start; i >= 0; i--)
	{
		if(source[i] == string[0])
		{
			check = true;

			for(z = 0; z < len; z++)
			{
				if(source[i+z] != string[z])
				{
					check = false;
				}
			}

			if(check == true)
			{
				return i;
			}
		}
	}

	return -1; // fail
}



#endif

// use a #define MASTERSTRING1
// before including the masterstring header
// to use masterstring 1 algorithms
#ifdef MASTERSTRING1
// masterstring - null terminated string manipulation 
// class hierarchy , as well as a large series of string related algorithims
// by jared bruni 
// my new string algorithims
// jared@lostsidedead.com

// some very important algorithims
// I totaly re-wrote all these from scratch
// so it would work better with the new masasm (my newest project)
// www.lostsidedead.com

// this source file is dedicated to my buds (hehe)


/************ Using MasterString ********************

  Within this source file consits of a series of
  algorithims and classes. You can inturn use these
  different aspects of the source to produce your
  own string classes, or to simply manipulate 
  char arrays. There are multiple levels of functionality
  as well as a few base classes for your classes to
  inhert from. This source is to be thought of as the
  layer ontop of string.h , allowing for simplicity
  as well as expanding the types of things it can do.

  The Functions**************************************

  All the simple functions with lowercased names, are
  the c-style functions. These allow you to pass a pointer
  to the character array, and manipulate it , in the way
  it describes (ex: findstr,stringcopy) etc these functions
  are very useful when directly manipulating character arrays
  and provide a much deeper form of control over the array.
  There are seires of different forms of string searches,
  which allow you to have full control. One of my favorite
  new ones which Im going to talk about here is findstrloc.
  findstrloc stands for find string location, its prototype is
  the following.

  void findstrloc(char* buff,char* search,MasStrDataLoc* dloc);

  This function cycles through the buffer, and every time it
  finds an instance of search, it leaves a refrence to it
  inside the MasStrDataLoc structure. Pretty nifty, but
  there are other ways to be able to cycle through all the
  characters, with very explicit searchs.

  findstr
  ifindstr
  findstrb
  ifindstrb

  etc

  These forms of searching for strings within your strings are
  extermly useful. They allow you to start off at the begining
  and then continue searching were you left off at. Allows you
  to search forward, backward, and even within a range of those
  two points. findstrcf (find string cycle forward) and findstrcb 
  (find string cycle backward). There are also a seires of functions
  that directly manipulate with ranges. These searchs, return a structure
  (MasStrRange) which contains two points. One for the starting location
  of the sub string, and one for were it stops. Pretty nifty when needing
  to have a full detailed structure of were things are at, to make
  the whole manipulation proccess easy. 


  The Classes / Structures *************************

  The next layer ontop of these functions, is the
  MasStrObj. This is a object, to use as a base
  object to inhert into your string classes, or
  whatever other class would need the structure
  of these functions.

  MasterString object

  The master string object, is a String class, which rather
  then attempting to just encapsulate all the string functionality
  it instead, trys to simplfy the proccess of using the object
  but still consist of the same amount of power. The MasterString
  inherts from MasStrObj, and then expands upon this to provide
  a autosizing string. It does this by creating a pointer to memory
  on the freestore, and then freeing that memory at appropriate times.
  It also has another layer, were the methods which use a form
  of hungarin notation (FindWindow LikeThis) automaticly point to the
  string within the Object. Let me give a example of this.

  theres the function findstr, and then the method within the
  MasterString object, FindString

  the following would be how you would call it

  char string1[100];
  stringcopy(string1, "stuff is x here");
  int placeval;
  placeval = findstr(string1,"x");

  using the MasterString , its actualy quite simpler

  MasterString str("stuff is x here");
  int placeval;
  placeval = str.FindString("x");

  When using the MasterString object, it basicly lets you
  encapsulate what character array the low level functions
  are pointing to, while still allowing you the ability
  to directly call any of the other functions.

  MasterStringList ********************************

  The MasterStringList class , is pretty simple to grasp
  and use. Its simply a class which holds a list of
  MasterStrings :)
  This class incorperates multiple inheritance one of my
  favorite features of the C++ language

  MasterINI ***************************************

  The MasterINI class is also fairly simple. It is a
  object that is kinda like a INI file. You basicly
  put in strings, by there name, and what the value is
  for that name, and it can then be saved & loaded.
  Its really easy to use / work, just remember to always
  create your size, or its gonna trip! example:

  MasterINI mstr(100); // allows 100 entrys

  MasterINI mstrx; // has no size
  mstrx.Create(100);// now has the size of 100 entrys


  - Jared Bruni

  Master@LostSideDead.com -

****************************************************/


#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream.h>
#include <fstream.h>

#define NOTFOUND -1
#define INULL    -1
#define NOPREV   -1
#define NULLI    -1
#define STRBEGIN -1
#define MRANGE_HI 1
#define MRANGE_LO 0
#define NULLPOS  -1

// string algorithims
void stringcopy(char* dest,char* from); // string copy
void stringattach(char* dest,char* from); // string attach
void leftcopy(char* from,char* dest,int pos);// left copy (leftstr)
void rightcopy(char* from,char* dest,int pos);// right copy (rightstr)
void midcopy(char* from,char* dest,int start_pos,int stop_pos);// middle copy (midstr)
void trimspace(char* buff);// trim space characters
int findstr(char* buffer,char* search);// find string search
int ifindstr(int i,char* buffer,char* search);// find string search from position
int findstrb(char* buffer,char* search); // backwards search
int ifindstrb(int i,char* buffer,char* search); // inside backwards search
int fsearchstr(int start,int stop,char* buff,char* search);// fully controled range search (forward)
int bsearchstr(int start,int stop,char* buff,char* search);// fully controled range search (backward)
void removestr(char* buff,char* str);// remove instances of str in buff
int getlen(char* buff);// get length of the string
void lcase(char* buff);// lower case string
void ucase(char* buff);// upper case string
int  lcasel(int c);// lower case letter
int  ucasel(int c);// upper case letter
int  findoccurance(char* buff,char* search);// find occourances of a specific string
void convertinteger(int integer,char* buff,int base); // convert integer to string
int  convertstring(char* buff); // convert string to integer
bool ishexc(char c);// is this character a hexidecimal digit?
bool ishex(char* buff);// is this string a hexidecimal value?
int  hextointc(char c);// hexidecimal digit to integer value
int  hextoint(char* buff); // hexidecimal digits to integer value
int findoccourance(char* buff,char* search);// find the numeric of times a string occours
void tripcharup(char* buff,int upby);// bump the digits up X times
void tripchardown(char* buff,int downby);// dump the digits down  X times
void replacechar(char* stringk,char findchr,char replace);// replace single character, through out all instances
void replacestr(char* stringk,char* findstr,char* rep,char* output);// replace string inside string
void rmvinst(char* buff,char* findstr,char* replace,char* output); // remove single instance of string
char randomchar(int max);// produce a random character
char randomchar(int max,int up);// produce a random character, and then make it + up
void randomstr(char* buff,int char_max,int char_size);// random string
void removechar(char* input,char* output,char c); // remove characters from buffer
int  findchar(char* str,char c);// find single char (forward)
int  ifindchar(int start,char* str,char c); // inside find single char (forward)
int  findcharb(char* str,char c);// find single char (backward)
int  ifindcharb(int start,char* str,char c); // find single char backward ex
int  findcharcf(char* str,int start,int stop,char c);// find single char controled forward
int  findcharcb(char* str,int start,int stop,char c);// find single char controled backward
void removestr(char* input,char* output,char* string); // remove instance of string
void rmvstrx(char* buff,char* output,char* string); // remove single instance of string
void strsavefile(char* filename,char* string);// save the string as a text file
int  getfilestringlength(char* filename);// get the string length of a text file
bool strloadfile(char* filename,char* output);// load a string from a text file
void reversestring(char* input,char* output); // reverse sring
bool isstrvalid(char* string); // checks to see if the string is valid or not (is null terminated)
// string compares
bool mstrcmp(char* buff1,char* buff2); // case sensitive compare
bool mstrcmpx(char* buff1,char* buff2);// not case sensitive compare
bool insidestr(char* buff1,char* buff2); // am i inside this string?
bool insidestrx(char* buff1,char* buff2);// am i inside this string lowercased ?
void strsep(char* str, char* sleft, int go_left, char* sright, int go_right);// seperate into 2 seperate strings from 2 seperate points
void strsetnull(char* str,int pos); // reset the 0's position
void rmvnullset(char* str); // remove the 0 to end the string
int  getnullpos(char* str); // get the position of the null
void trimcom(char* buff, char* output, char startstr,char stopstr); 
void asmtrim(char* input,char* output);
int  countlines(char* buffer); // counts how many \n characters exisit
int  getfirstletter(char* buffer); // get first letter thats not a space

// string data location structure use w/ (findstrl)
struct MasStrDataLoc
{
	int* dindex;
	int  array_size;
	char* thestring;
	char* searchstr;
	bool search_status;

	inline MasStrDataLoc()
	{
		search_status = false;
		dindex = 0;
		array_size = 0;
		searchstr = 0;
	}
	
	inline ~MasStrDataLoc()
	{
		if(dindex != 0)
		{

		delete [] dindex;
		dindex = 0;

		}
		if(thestring != 0)
		{

		delete [] thestring;
		thestring = 0;

		}
		if(searchstr != 0)
		{

		delete [] searchstr;
		searchstr = 0;

		}
	}

	inline void create_array(int size)
	{
		dindex = new int[size];
		array_size = size;
	}

	inline void setstr(char* buff)
	{
		int len;
		len = strlen(buff);
		thestring = new char[len+1];
		stringcopy(thestring,buff);
	}

	inline void setstatus(bool x)
	{
		search_status = x;
	}

	inline void setsearchstr(char* buff)
	{
		int len;
		len = strlen(buff);
		searchstr = new char[len+1];
		stringcopy(searchstr,buff);
	}

	// return pointer to the string which the array holds data for
	inline char* getstr()
	{
		return thestring;
	}

	inline char* getsearchstr()
	{
		return searchstr;
	}

	inline int getarraysize()
	{
		return array_size;
	}

	inline int getstringpoint(int index)
	{
		if(index <= array_size)
		{

		return dindex[index];

		}
	}
	// maximum string points for search
	inline int getmaxpoint()
	{
		return array_size;
	}
	// get status
	inline bool getstatus()
	{
		return search_status;
	}

	inline bool wassearchsuccesful()
	{
		return getstatus();// was it succesfull?
	}
};
// find string location (dumps all locations into the location data structure (MasStrDataLoc))
bool findstrloc(char* buff,char* search,MasStrDataLoc* dloc);// standard
bool findstrlocf(char* buff,char* search,MasStrDataLoc* dloc);// forward
bool findstrlocb(char* buff,char* search,MasStrDataLoc* dloc);// backward

// master string range structure
struct MasStrRange
{
	int start_x;
	int stop_y;

	inline MasStrRange()
	{
		start_x = 0;
		stop_y = 0;
	}

	inline void SetRange(int x, int y)
	{
		start_x = x;
		stop_y = y;
	}

	inline int GetRangeX()
	{
		return start_x;
	}

	inline int GetRangeY()
	{
		return stop_y;
	}

	inline int GetRangeHI()
	{
		return start_x;
	}

	inline int GetRangeLO()
	{
		return stop_y;
	}

	inline int Clear()
	{
		start_x = 0;
		stop_y = 0;
	}
};

// range search structures for range style string manipulation
bool searchrange(char* buff,char* search,MasStrRange* mrang);
void copyleftrange(char* input,char* output,MasStrRange* mrang, int hi_lo);
void copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo);
void copymidrange(char* input,char* output,MasStrRange* mrang, int hi_lo,MasStrRange* mrangx, int hi_lox);
bool isearchrange(int startx, char* buff,char* search,MasStrRange* mrang);

// master string list structure string data
struct MasStrList_String
{
	char* thestring;

	inline ~MasStrList_String()
	{
		delete [] thestring;
	}

	inline void set(char* buff)
	{
		int len;
		len = strlen(buff) + 1;
		thestring = new char[len];
		stringcopy(thestring,buff);
	}

	inline char* get()
	{
		return thestring;
	}
};
// master string list , list handler structure
struct MasStrList
{
	MasStrList_String* strings;
	int list_size;

	inline ~MasStrList()
	{
		delete [] strings;
	}

	inline MasStrList(int list_size)
	{
		create(list_size);
	}

	inline MasStrList()
	{
		list_size = 0;
		strings = NULL;
	}

	inline void create(int list_sizez)
	{
		list_size = list_sizez;
		strings = new MasStrList_String[list_size];
	}

	inline char* getstr(int index)
	{
		return strings[index].get();
	}

	inline int getcount()
	{
		return list_size;
	}
};

// create string list
void createstrlist(char* buffer, char* list_marker,MasStrList* list);


// charwrap  easy to use char array, that automaticly removes itself from freestore
struct charwrap
{
	char* str;

	inline charwrap(int size)
	{
		str = new char[size];
	}

	inline charwrap(char* buff)
	{
		set(buff);
	}

	inline charwrap(char* buff,bool x)
	{
		set(buff);
		strclearn();
	}

	inline ~charwrap()
	{
		delete [] str; // delete that shit
	}

	inline void set(char* buff)
	{
		int len;
		len = strlen(buff) + 1;
		str = new char[len];
		stringcopy(str,buff);
	}

	inline void snew(int size)
	{
		str = new char[size];
	}

	// clear off freestore
	inline void clear()
	{
		delete [] str;
		str = NULL;
	}

	inline void strclear()
	{
		int len;
		len = getlen(str);

		for(int i = 0; i < len; i++)
		{
			str[i] = 0;
		}
	}

	inline void strclearn()
	{
		stringcopy(str,"");
	}

	inline char* get()
	{
		return str;
	}

	inline int len()
	{
		return getlen(str);
	}

	inline void qmsg()
	{
		MessageBox(0,str,"QMSG",MB_OK|MB_ICONINFORMATION);
	}

};

// structure of string manipulation algorithims to use for objects to inhert
struct MasStrObj
{
    inline void mstr_stringcopy(char* input,char* output)
	{
		stringcopy(input,output);
	}

	inline void mstr_stringattach(char* input,char* output)
	{
		stringattach(input,output);
	}

	inline void mstr_leftcopy(char* input,char* output,int pos)
	{
		leftcopy(input,output,pos);
	}

	inline void mstr_rightcopy(char* input,char* output,int pos)
	{
		rightcopy(input,output,pos);
	}

	inline void mstr_midcopy(char* input,char* output,int start_pos,int stop_pos)
	{
		midcopy(input,output,start_pos,stop_pos);
	}

	inline void mstr_trimspace(char* buff)
	{
		trimspace(buff);
	}

	inline int mstr_findstr(char* buffer,char* search)
	{
		return findstr(buffer,search);
	}

	inline int mstr_ifindstr(int i,char* buffer,char* search)
	{
		return ifindstr(i,buffer,search);
	}

	inline int mstr_findstrb(char* body,char* search)
	{
		return findstrb(body,search);
	}

	inline int mstr_ifindstrb(int startx,char* body,char* search)
	{
		return ifindstrb(startx,body,search);
	}

	inline int mstr_fsearchstr(int start,int stop,char* buff,char* search)
	{
		return fsearchstr(start,stop,buff,search);
	}

	inline int mstr_bsearchstr(int start,int stop,char* buff,char* search)
	{
		return bsearchstr(start,stop,buff,search);
	}

	inline int mstr_getlen(char* buff)
	{
		int len;
		len = strlen(buff);
		return len;
	}

	inline int mstr_lcase(char* buffer)
	{
		lcase(buffer);
	}

	inline int mstr_ucase(char* buffer)
	{
		ucase(buffer);
	}

	inline int mstr_ucasel(char c)
	{
		return ucasel(c);
	}

	inline int mstr_lcasel(char c)
	{
		return lcasel(c);
	}

	inline bool mstr_findstrloc(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrloc(buff,search,dloc);
	}

	inline bool mstr_findstrlocf(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrlocf(buff,search,dloc);
	}

	inline bool mstr_findstrlocb(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrlocb(buff,search,dloc);
	}

	inline bool mstr_searchrange(char* buff,char* search,MasStrRange* mrang)
	{
		return searchrange(buff,search,mrang);
	}

	inline bool mstr_isearchrange(int startx, char* buff,char* search,MasStrRange* mrang)
	{
		return isearchrange(startx,buff,search,mrang);
	}

	inline void mstr_copyleftrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
	{
		copyleftrange(input,output,mrang,hi_lo);
	}

	inline void mstr_copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
	{
		copyrightrange(input,output,mrang,hi_lo);
	}

	inline void mstr_copymidrange(char* input,char* output,MasStrRange* mrang,int hi_lo,MasStrRange* mrangx,int hi_lox)
	{
		copymidrange(input,output,mrang,hi_lo,mrangx,hi_lox);
	}

	inline int mstr_findoccourance(char* buffer,char* searchx)
	{
		return findoccourance(buffer,searchx);
	}

	inline void mstr_convertinteger(int integer,char* buff,int base)
	{
		convertinteger(integer,buff,base);
	}

	inline int mstr_convertstring(char* buff)
	{
		return convertstring(buff);
	}

	inline bool mstr_ishexc(char c)
	{
		return ishexc(c);
	}

	inline bool mstr_ishex(char* buff)
	{
		return ishex(buff);
	}

	inline int mstr_hextointc(char c)
	{
		return hextointc(c);
	}
	inline int mstr_hextoint(char* buff)
	{
		return hextoint(buff);
	}

	inline void mstr_tripchardown(char* buff,int by)
	{
		tripchardown(buff,by);
	}

	inline void mstr_tripcharup(char* buff, int by)
	{
		tripcharup(buff,by);
	}
	inline void mstr_replacechar(char* buff,char findchr,char replace)
	{
		replacechar(buff,findchr,replace);
	}
	inline void mstr_replacestr(char* buff,char* findstr,char* replacex,char* output)
	{
		replacestr(buff,findstr,replacex,output);
	}
	inline void mstr_rmvinst(char* buff,char* findchr,char* re,char* out)
	{
		rmvinst(buff,findchr,re,out);
	}

	inline char mstr_randomchar(int max)
	{
		return randomchar(max);
	}
	inline char mstr_randomchar(int max, int up)
	{
		return randomchar(max,up);
	}
	inline void mstr_randomstr(char* buff,int max, int size)
	{
		randomstr(buff,max,size);
	}
	inline void mstr_removechar(char* input,char* output,char c)
	{
		removechar(input,output,c);
	}
	inline char mstr_findchar(char* str,char c)
	{
		return findchar(str,c);
	}
	inline char mstr_ifindchar(int start,char* str,char c)
	{
		return ifindchar(start,str,c);
	}
	inline char mstr_findcharb(char* str,char c)
	{
		return findcharb(str,c);
	}
	inline char mstr_ifindcharb(int start,char* str,char c)
	{
		return ifindcharb(start,str,c);
	}
	inline char mstr_findcharcf(char* str,int start,int stop,char c)
	{
		return findcharcf(str,start,stop,c);
	}
	inline char mstr_findcharcb(char* str,int start,int stop,char c)
	{
		return findcharcb(str,start,stop,c);
	}
	inline void mstr_removestr(char* str,char* output,char* strsearch)
	{
		removestr(str,output,strsearch);
	}
	inline void mstr_removestrinstance(char* str,char* output,char* strx)
	{
		rmvstrx(str,output,strx);
	}
	inline void mstr_savestr(char* filename,char* string)
	{
		strsavefile(filename,string);
	}
	inline bool mstr_loadstr(char* filename,char* output)
	{
		return strloadfile(filename,output);
	}
	inline int  mstr_getfilestrlen(char* filename)
	{
		return getfilestringlength(filename);
	}
	inline int mstr_reversestr(char* str_input,char* str_output)
	{
		reversestring(str_input,str_output);
	}
	inline bool mstr_isstrvalid(char* str)
	{
		return isstrvalid(str);
	}
	inline bool mstr_mstrcmp(char* buff1,char* buff2)
	{
		return mstrcmp(buff1,buff2);
	}

	inline bool mstr_mstrcmpl(char* buff1,char* buff2)
	{
		return mstrcmpx(buff1,buff2);
	}

	inline bool mstr_insidestr(char* buff1,char* buff2)
	{
		return insidestr(buff1,buff2);
	}
	inline bool mstr_insidestrl(char* buff1,char* buff2)
	{
		return insidestrx(buff1,buff2);
	}
	inline void mstr_strsep(char* str,char* lstr,int lpos,char* rstr,int rpos)
	{
		strsep(str,lstr,lpos,rstr,rpos);
	}
	inline int mstr_getnullpos(char* str)
	{
		return getnullpos(str);
	}
	inline void mstr_rmvnullset(char* str)
	{
		rmvnullset(str);
	}
	inline void mstr_strsetnull(char* str,int pos)
	{
		strsetnull(str,pos);
	}
	inline void mstr_trimcom(char* input,char* output, char start_c,char stop_c)
	{
		trimcom(input,output,start_c,stop_c);
	}
	inline void mstr_asmtrim(char* input,char* output)
	{
		asmtrim(input,output);
	}
};

// the MasterString Object

struct MasterString : MasStrObj
{
	char* str;
	int array_size;
	bool str_on;

	/********** constructors & deconstructors ****************/
	inline MasterString()
	{
		str_on = false;
		array_size = 0;
		str = NULL;
	}

	inline MasterString(int size)
	{
		set(size,"");
	}

	inline MasterString(char* buff)
	{
		int size = strlen(buff) + 2;
		set(size,buff);
	}

	inline MasterString(int size,char* buff)
	{
		set(size,buff);
	}

	inline ~MasterString()
	{
		if(str_on)
		{
			delete [] str;
			str_on = false;

		}
	}

	/* internal functions **************************/
	inline void set(int size,char* buff)
	{
		if(str_on == false)
		{
			str = new char[size];
			str_on = true;
		}
		else
		{
			delete [] str;
			str = new char[size];
		}

		mstr_stringcopy(str,buff);
		array_size = size;
	}

	inline void add(char* buff)
	{
		int total_length = GetStringLength() + strlen(buff) + 2;

		if(total_length > GetStringLength())
		{
			char* ptemp;
			ptemp = new char[GetStringLength()+1];
			strcpy(ptemp,str);

			delete [] str;
			str = 0;// set pointer to 0 
			str = new char[total_length+2];
			strcpy(str,ptemp);
			delete [] ptemp;
			strcat(str,buff);
		}
		else
		{
			strcat(str,buff);
		}
	}

	inline void unset()
	{
		if(str_on == true)
		{
			delete [] str;
			str_on = false;
		}
	}

	inline char* get()
	{
		return str;
	}

	// operators *************************

	inline void operator=(char* buffer)
	{
		// set
		int len;
		len = strlen(buffer)+2;
		set(len,buffer);
	}

	inline void operator+=(char* buffer)
	{
		add(buffer);
	}
	inline void operator+=(int x)
	{
		char buffer[30];
		itoa(x,buffer,10);
		add(buffer);
	}

	inline void operator+=(long x)
	{
		char buffer[30];
		itoa(x,buffer,10);
		add(buffer);
	}

	// misc *********************************

	inline int GetStringLength()
	{
		return mstr_getlen(str);
	}

	inline char* GetCharPointer()
	{
		return str;
	}

	inline int FindChar(char c)
	{
		return mstr_findchar(str,c);
	}

	inline int FindCharEx(int pre_pos,char c)
	{
		return mstr_ifindchar(pre_pos,str,c);
	}
	inline int FindCharBackward(char c)
	{
		return mstr_findcharb(str,c);
	}
	inline int FindCharBackwardEx(int pre_pos,char c)
	{
		return mstr_ifindcharb(pre_pos,str,c);
	}
	inline int FindCharControledForward(int start,int stop,char c)
	{
		return mstr_findcharcf(str,start,stop,c);
	}
	inline int FindCharControledBackward(int start,int stop,char c)
	{
		return mstr_findcharcb(str,start,stop,c);
	}
	inline int FindString(char* search)
	{
		return mstr_findstr(str,search);
	}

	inline int FindStringEx(int index,char* search)
	{
		return mstr_ifindstr(index,str,search);
	}

	inline int FindStringBackward(char* search)
	{
		return mstr_findstrb(str,search);
	}
	inline int FindStringBackwardEx(int index,char* search)
	{
		return mstr_ifindstrb(index,str,search);
	}
	inline int FindOccourance(char* search)
	{
		return mstr_findoccourance(str,search);
	}
	inline void StringCopy(char* buff)
	{
		mstr_stringcopy(str,buff);
	}
	inline void StringAttach(char* buff)
	{
		mstr_stringattach(str,buff);
	}
	inline void StringResize(int newSize)
	{
		char* ptemp;
		ptemp = new char[strlen(str)+1];
		strcpy(ptemp,str);

		delete [] str;
		str = new char[newSize];
		strcpy(str,ptemp);
		delete [] ptemp;
	}
	inline void StringLeft(char* output,int pos)
	{
		mstr_leftcopy(str,output,pos);
	}
	inline void StringRight(char* output,int pos)
	{
		mstr_rightcopy(str,output,pos);
	}
	inline void StringMid(char* output,int x,int y)
	{
		mstr_midcopy(str,output,x,y);
	}
	inline void TrimSpace()
	{
		trimspace(str);
	}

	inline void UpperCase()
	{
		ucase(str);
	}
	inline void LowerCase()
	{
		lcase(str);
	}
	inline char ExtractChar(int index)
	{
		if(index <= GetStringLength())
		{
			return str[index];
		}
		return 0;
	}
	inline int ForwardStringSearch(int start,int stop,char* search)
	{
		return mstr_fsearchstr(start,stop,str,search);
	}

	inline int BackwardStringSearch(int start,int stop,char* search)
	{
		return mstr_bsearchstr(start,stop,str,search);
	}
	inline bool FindStringLocation(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrloc(str,search,dloc);
	}
	inline bool FindStringLocationF(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrlocf(str,search,dloc);
	}
	inline bool FindStringLocationB(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrlocb(str,search,dloc);
	}
	inline void SearchRange(char* search,MasStrRange* mrang)
	{
		mstr_searchrange(str,search,mrang);
	}
	inline void SearchRangeEx(int startx,char* search,MasStrRange* mrang)
	{
		mstr_isearchrange(startx,str,search,mrang);
	}
	inline void CopyLeftRange(char* output, MasStrRange* mrang,int hi)
	{
		mstr_copyleftrange(str,output,mrang,hi);
	}
	inline void CopyRightRange(char* output, MasStrRange* mrang,int hi)
	{
		mstr_copyrightrange(str,output,mrang,hi);
	}
	inline void CopyMidRange(char* output,MasStrRange* mrang,int hi, MasStrRange* mrangx,int hix)
	{
		mstr_copymidrange(str,output,mrang,hi,mrangx,hix);
	}
	
	inline int GetHexValue()
	{
		return mstr_hextoint(str);
	}
	inline int GetDecValue()
	{
		return atoi(str);
	}
	inline int ConvertToInteger()
	{
		return atoi(str);
	}
	inline bool IsHex()
	{
		return mstr_ishex(str);
	}

	inline void qprint()
	{
		cout << str;
	}
	inline void qmsg()
	{
		MessageBox(0,str,"QMSG",MB_ICONINFORMATION);
	}
	inline void ClearString()
	{
		for(int z = 0; z < GetStringLength(); z++)
		{
			str[z] = 0;
		}
	}
	inline void SetWindowText(HWND hwnd)
	{
		SendMessage(hwnd,WM_SETTEXT,strlen(str),(LPARAM)(LPCSTR)str);
	}
	inline void AddToList(HWND hwnd)
	{
		SendMessage(hwnd,LB_ADDSTRING,strlen(str),(LPARAM)(LPCSTR)str);
	}
	inline void AddToCombo(HWND hwnd)
	{
		SendMessage(hwnd,CB_ADDSTRING,strlen(str),(LPARAM)(LPCSTR)str);
	}

	inline void CopyTextFromHWND(HWND hwnd)
	{
		char* buffer;
		int len;
		len = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
		buffer = new char[len+1];
		SendMessage(hwnd,WM_GETTEXT,len,(LPARAM)(LPCSTR)buffer);
		
		set(len+1,buffer);

		delete [] buffer;
	}
	
	inline void AttachTextFromHWND(HWND hwnd)
	{
		char* buffer;
		int len;
		len = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
		buffer = new char[len+1];
		SendMessage(hwnd,WM_GETTEXT,len,(LPARAM)(LPCSTR)buffer);
		
		add(buffer);

		delete [] buffer;
	}
	inline void ReplaceCharacter(char findchr,char replace)
	{
		mstr_replacechar(str,findchr,replace);
	}
	inline void RandomizeString()
	{
		randomstr(str,255,strlen(str));
	}
	inline void ReplaceString(char* search, char* replacestr)
	{
		if(mstr_findstr(str,search) != -1)
		{

		char* output;
		output = new char[strlen(str)+10];
		mstr_replacestr(str,search,replacestr,output);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
		
		}
	}
	inline void RemoveCharacters(char c)
	{
		char* output;
		output = new char[strlen(str)+10];
		mstr_removechar(str,output,c);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}
	inline void RemoveString(char* search)
	{
		if(mstr_findstr(str,search) != -1)
		{
			char* output;
			output = new char[strlen(str)+10];
			mstr_removestr(str,output,search);
			set(strlen(output)+10,output);
			delete [] output;
			output = 0;
		}
	}
	inline void RemoveSingleInstanceOfString(char* search)
	{
		if(mstr_findstr(str,search) != -1)
		{
			char* output;
			output = new char[strlen(str)+10];
			rmvstrx(str,output,search);
			set(strlen(output)+10,search);
			delete [] output;
			output = 0;
		}
	}
	inline void SaveToFile(char* filename)
	{
		mstr_savestr(filename,str);
	}
	inline void LoadStringFromFile(char* filename)
	{
		if(getfilestringlength(filename) == -1)
		{
			return; // failure file not found
		}

		char* temp;
		temp = new char[getfilestringlength(filename)+20];
		mstr_loadstr(filename,temp);
		set(strlen(temp)+20,temp);
		delete [] temp;
		temp = 0;
	}
	inline bool IsStringValid()
	{
		return mstr_isstrvalid(str);
	}

	inline int ReverseString() // reverse the string
	{
		char* temp;
		temp = new char[GetStringLength()+10];

		reversestring(str,temp);
		set(strlen(temp)+10,temp);

		delete [] temp;
		temp = 0;
	}

	inline bool StringCompare(char* buff)
	{
		return mstr_mstrcmp(str,buff);
	}
	inline bool StringCompare_NOCASE(char* buff)
	{
		return mstr_mstrcmpl(str,buff);
	}
	inline bool IsInsideString(char* buff)
	{
		return mstr_insidestr(str,buff);
	}
	inline bool IsInsideString_NOCASE(char* buff)
	{
		return mstr_insidestrl(str,buff);
	}
	inline void SeperateString(char* lbuff,int lpos,char* rbuff,int rpos)
	{
		mstr_strsep(str,lbuff,lpos,rbuff,rpos);
	}
	inline void AsmTrim()
	{
		// trim string as tho it were assembly language source
		char* output;
		output = new char[GetStringLength()+10];
		asmtrim(str,output);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}

	inline void TrimComments(char start_c,char stop_c)
	{
		char* output;
		output = new char[GetStringLength()+10];
		trimcom(str,output,start_c,stop_c);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}
};

// MasterString Item Structure 
struct ListItem
{
	int list_index;

	inline void setindex(int i)
	{
		list_index = i;
	}

	inline int getindex()
	{
		return list_index;
	}
};

struct MasterStringItem : MasterString,ListItem
{
	bool on;

	inline MasterStringListItem()
	{
		on = false;
	}

	inline void seton(bool x)
	{
		on = x;
	}

	inline bool geton()
	{
		return on;
	}
};

// example of a list using MasterStrings
struct MasterStringList 
{
	MasterStringItem* item;
	bool ion;
	int array_size;
	int off;

	inline MasterStringList()
	{
		ion = false;
		off = 0;
	}

	inline ~MasterStringList()
	{
		if(ion == true)
		{
			delete [] item;
			item = NULL;
		}
	}

	inline MasterStringList(int size)
	{
		createList(size);
	}
	
	inline void createList(int size)
	{
		item = new MasterStringItem[size];
		ion = true;
		array_size = size;
	}

	inline int  GetArraySize()
	{
		return array_size;
	}

	inline char* GetListStringPointerByIndex(int index)
	{
		return item[index].get();
	}

	inline int AddString(char* buffer)
	{
  		item[off].set(strlen(buffer)+10,buffer);
		int xoff = off;
		off++;
		return xoff;
	}

	inline int GetListLength()
	{
		return off;
	}

	inline void GetString(int index,char* output)
	{
		strcpy(output,item[index].get());
		
	}


	inline void Clear()
	{
		for(int i = 0; i < off; i++)
		{
			item[i].ClearString();
		}

		off = 0;
	}
};

struct MasterEntry : ListItem
{
	MasterString name;
	MasterString value;
	bool on_switch;

	inline MasterEntry()
	{
		name = "";
		value = "";
		on_switch = false;
	}

	inline bool amion()
	{
		return on_switch;
	}

};

// easy to use INI object, using MasterStrings
struct MasterINI
{
	MasterEntry* masEntry;
	bool mas_on;
	int array_size;
	int off_count;

	// constructors/deconstructors

	inline MasterINI()
	{
		masEntry = 0;
		mas_on = false;
		off_count = 0;
	}
	
	inline MasterINI(int size)
	{
		set(size);
	}

	inline ~MasterINI()
	{
		if(mas_on)
		{
			delete [] masEntry;
			masEntry = 0;
		}
	}

	inline set(int size)
	{
		if(mas_on == true)
		{
			delete [] masEntry;
			masEntry = 0;
		}

		masEntry = new MasterEntry[size];
		mas_on = true;
		array_size = size;
		off_count = 0;
	}

	inline int getsize()
	{
		return array_size;
	}

	inline void Create(int size)
	{
		set(size);
	}

	inline bool AddEntry(char* name,char* value)
	{
		if(off_count < getsize())
		{


		masEntry[off_count].name = name;
		masEntry[off_count].value = value;
		masEntry[off_count].list_index = off_count;

		off_count++;
		return true;
		}

		return false;
	}

	inline bool GetEntry(char* name,char* output_value)
	{
		for(int i = 0; i < getsize(); i++)
		{
			if(findstr(masEntry[i].name.get(),name) != -1)
			{
				stringcopy(output_value,masEntry[i].value.get());
				return true;
			}
		}

		strcpy(output_value,"*NULL*");
		return false;
	}
};

bool SaveMasterINI(char* filename,MasterINI* mini); // Save INI
bool LoadMasterINI(char* filename,MasterINI* mini); // Load INI

struct MasCharList // char list based on the \n (breaks strings into lines) (for use with MasAsm)
{
	MasterString* list;
	bool list_on;
	int array_size;
	int list_len;


	inline MasCharList()
	{
		list = 0;
		list_on = false;
	}

	inline MasCharList(char* buff)
	{
		BuildList(buff);
	}

	inline ~MasCharList()
	{
		if(list_on == true)
		{

		delete [] list;
		list = 0;

		}
	}

	inline void BuildList(char* buff)
	{
		int size;
		size = countlines(buff) + 1;
		list = new MasterString[size];
		list_on = true;
		array_size = size;
		// format the characters into this array
		int pre_pos = 0;
		int acount = 0;

		while(1)
		{
			int find_x;
			find_x = ifindstr(pre_pos,buff,"\n");
			
			if(find_x == -1)
			{
				break;// all done !
			}

			
			char* temp;
			temp = new char[strlen(buff)+1];

			midcopy(buff,temp,pre_pos,find_x);
			pre_pos = find_x;
		
			// add
			list[acount] = temp;
			acount++;
		

			delete [] temp;
			temp = 0;

		}

		list_len = acount;

	}

	inline int GetLength()
	{
		return list_len;
	}

	inline MasterString* GetMasterString(int index)
	{
		return (MasterString*)&list[index];
	}

};


// string copy
void stringcopy(char* input,char* output)
{
	strcpy(input,output);
}

// string attach
void stringattach(char* input,char* output)
{
	strcat(input,output);
}

// left copy
void leftcopy(char* input,char* output,int pos)
{
	int index = 0;
	for(int i = 0; i < pos; i++)
	{
		output[index] = input[i];
		index++;
	}
	output[index] = 0;
}
// right copy
void rightcopy(char* input,char* output,int pos)
{
	int index = 0;
	int len = strlen(input);
	for(int i = pos; i < len; i++)
	{
		output[index] = input[i];
		index++;
	}
	output[index] = 0;

}
// mid copy
void midcopy(char* input,char* output,int start_pos, int stop_pos)
{
	int index = 0;
	for(int i = start_pos; i < stop_pos; i++)
	{
		output[index] = input[i];
		index++;
	}

	output[index] = 0;
}

// trim the space
void trimspace(char* buffer)
{
	int len;
	len = strlen(buffer);
	char* ptemp;
	ptemp = new char[len+1];
	strcpy(ptemp,buffer);

	int index = 0;
	for(int z = 0; z < len; z++)
	{
		if(ptemp[z] != ' ')
		{
			buffer[index] = ptemp[z];
			index++;
		}
	}
	buffer[index] = 0;

	delete [] ptemp;
}

int findstr(char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search); // search len

	for(int i = 0; i < len; i++)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i;
			}
		}
	}

	return -1; // failure
}

int ifindstr(int startx,char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search); // search len

	for(int i = startx+1; i < len; i++)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i;
			}
		}
	}

	return -1; // failure
}

int findstrb(char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search);

	for(int i = len; i > 0; i--)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it
			}
		}

	}
	return -1; // failure
}
// find inside backwards string loop
int ifindstrb(int startx, char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search);

	for(int i = startx-1; i > 0; i--)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it
			}
		}

	}
	return -1; // failure
}
// forward search string (controled range) 
int fsearchstr(int start,int stop,char* buff,char* search)
{
	int len = strlen(buff);
	int len2 = strlen(search);

	for(int i = start; i < stop; i++)
	{
		if(buff[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
			  return i; // found it
			}
		}
	}

	return -1; // failure
}

// backward search string (controled range)
int bsearchstr(int start,int stop,char* buff,char* search)
{
	int len = strlen(buff);
	int len2 = strlen(search);

	for(int i = start; i > stop; i--)
	{
		if(buff[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it;
			}
		}
	}

	return -1;// failure
}
// getting length
int getlen(char* buff)
{
	return strlen(buff);// use strlen :)
}
// lower case
void lcase(char* buffer)
{
	int len = getlen(buffer);

	for(int i = 0; i < len; i++)
	{
		buffer[i] = tolower(buffer[i]);
	}
}
// upercase
void ucase(char* buffer)
{
	int len = getlen(buffer);

	for(int i = 0; i < len; i++)
	{
		buffer[i] = toupper(buffer[i]);
	}
}
// uppercase letter
int ucasel(char c)
{
	return tolower(c);
}

// lowercase letter
int lcasel(char c)
{
	return tolower(c);
}

// find string location algorithims
bool findstrloc(char* buff,char* search,MasStrDataLoc* dloc)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	int* f;
	int  f_i = 0;
	f = new int[len+1];// big just in case

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;
				
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{

				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				f[f_i] = i;
				f_i++;
			}
		}
	}

	dloc->create_array(f_i);
	dloc->setstr(buff);
	dloc->setsearchstr(search);
	for(int p = 0; p < f_i; p++)
	{
		dloc->dindex[p] = f[p];
	}
	delete [] f;

	if(f_i != 0)
	{
		dloc->setstatus(true);
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus(false); 
		return false; // not found
	}
}
// find string location forward search
bool findstrlocf(char* buff,char* search,MasStrDataLoc* dloc)
{
	return findstrloc(buff,search,dloc);
}
// find string location backwards search
bool findstrlocb(char* buff,char* search,MasStrDataLoc* dloc)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	int* f;
	int  f_i = 0;
	f = new int[len+1];// big just in case

	for(int i = len; i > 0; i--)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;
				
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{

				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				f[f_i] = i;
				f_i++;
			}
		}
	}

	dloc->create_array(f_i);
	dloc->setstr(buff);
	dloc->setsearchstr(search);
	for(int p = 0; p < f_i; p++)
	{
		dloc->dindex[p] = f[p];
	}
	delete [] f;

	if(f_i != 0)
	{
		dloc->setstatus(true);
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus(false);
		return false; // not found
	}
}

// string ( range based ) manipulation algorithims
bool searchrange(char* buff,char* search,MasStrRange* mrang)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ik = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ik = false;
				}
			}

			if(ik == true)
			{
				mrang->SetRange(i,i+len2);
				return true;
			}
		}
	}
	mrang->SetRange(0,0);
	return false;
}
// string range manipluation ex (i)
bool isearchrange(int startx, char* buff,char* search,MasStrRange* mrang)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	for(int i = startx+1; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ik = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ik = false;
				}
			}

			if(ik == true)
			{
				mrang->SetRange(i,i+len2);
				return true;
			}
		}
	}
	mrang->SetRange(0,0);
	return false;
}

// find the occourance amount of a specific string
int findoccourance(char* buff,char* search)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	int occ = 0;

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				occ++;
			}

		}
	}

	if(occ == 0)
	{

	return -1; // failure

	}
	else
	{
		return occ;
	}
}

// string range manipulation copy left range
void copyleftrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
{
	if(hi_lo == MRANGE_HI)
	{
		leftcopy(input,output,mrang->GetRangeHI());
	}
	else
	{
		leftcopy(input,output,mrang->GetRangeLO());
	}
}
// string range manipulation copy right range
void copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
{
	if(hi_lo == MRANGE_HI)
	{
		rightcopy(input,output,mrang->GetRangeHI());
	}
	else
	{
		rightcopy(input,output,mrang->GetRangeLO());
	}
}
// string range manipulation mid copy
void copymidrange(char* input,char* output,MasStrRange* mrang, int hi_lo,MasStrRange* mrangx, int hi_lox)
{
	int cx;
	int cy;

	if(hi_lo == MRANGE_HI)
	{
		cx = mrang->GetRangeHI();
	}
	else
	{
		cx = mrang->GetRangeLO();
	}

	if(hi_lox == MRANGE_HI)
	{
		cy = mrangx->GetRangeHI();
	}
	else
	{
		cy =mrangx->GetRangeLO();
	}

	midcopy(input,output,cx,cy);
}

// create a list from string data
void createstrlist(char* buff,char* search,MasStrList* list)
{
	int occ;
	occ = findoccourance(buff,search);

	if(occ == -1)
	{
		return; // failure
	}
	list->create(occ);

	int occ_i = 0;

	MasStrDataLoc dloc;

	if(findstrloc(buff,search,&dloc))
	{
		int pre_pos = 0;

		for(int z = 0; z < dloc.getmaxpoint(); z++)
		{
			int cur = 0;
			cur = dloc.dindex[z];
			charwrap cwrap(buff);
			cwrap.strclearn();
			midcopy(buff,cwrap.get(),pre_pos,cur);
			list->strings[occ_i].set(cwrap.get());
			occ_i++;
			pre_pos = cur;
		}

		charwrap cwrapx(buff,true);
		rightcopy(buff,cwrapx.get(),pre_pos);
		list->strings[occ_i].set(cwrapx.get());
		occ_i++;
		}

	return;
}
// conversion of integers
void convertinteger(int integer,char* buff,int base)
{
	itoa(integer,buff,base);
}
// conversion of strings
int convertstring(char* buff)
{
	return atoi(buff);
}
// could this be a hexidecimal digit?
bool ishexc(char c)
{
	c = lcasel(c);
	switch(c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		return true;
		break;
	}
	return false;
}
// does this string contain a non-hexidecimal digit?
bool ishex(char* buff)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(ishexc(buff[i]) == false)
		{
			return false;
		}
	}
	return true;
}

// hexidecimal digit to integer value
int hextointc(char c)
{
	if(ishexc(c) == false)
	{
		return -1; // failure, not a hex digit
	}

	c = lcasel(c);

	switch(c)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	case 'a':
		return 10;
		break;
	case 'b':
		return 11;
	case 'c':
		return 12;
	case 'd':
		return 13;
	case 'e':
		return 14;
	case 'f':
		return 15;
	}

	return -1; // failure ? never would get here
}

// convert hex value into a integer
int hextoint(char* buff)
{
	int rt = 0;

	if(buff[1] == 0)
	{
		return hextointc(buff[0]);
	}

	int len = strlen(buff);
	int* hexval;
	hexval = new int[len+1];
	int  hexvali = 0;

	for(int i = 0; i < len; i++)
	{
		hexval[hexvali] = hextointc(buff[i]);
		hexvali++;
	}

    int index = 0;

	for(int z = hexvali-1; z >= 0; z--)
	{
		int cur;
		if(index == 0)
		{
			cur = hexval[z];
			index = 16;
		}
		else
		{

		cur = hexval[z] * index;
		index = index * 16;
		}
		
		rt = rt + cur;
	}

	delete [] hexval;

	return rt;
} 


void tripcharup(char* buff, int up)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] != 0)
		{

		buff[i] = buff[i] + up;

		}
	}
}

void tripchardown(char* buff,int up)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] != 0)
		{

		buff[i] = buff[i] - up;

		}
	}
}
// replace single instance of a character
void replacechar(char* buff,char findchr,char replace)
{
	int len;
	len = strlen(buff);

	for(int z = 0; z < len; z++)
	{
		if(buff[z] == findchr)
		{
			buff[z] = replace;
		}
	}
}

void rmvinst(char* buff,char* findstr,char* replacex,char* output)
{

	int xt = ifindstr(NOPREV,buff,findstr);


	char* temp;
	temp = new char[strlen(buff)+1];
	stringcopy(temp,buff);

	char* ltemp;
	char* rtemp;

	ltemp = new char[strlen(buff)+1];
	rtemp = new char[strlen(buff)+1];

	leftcopy(buff,ltemp,xt);
	rightcopy(buff,rtemp,xt+strlen(findstr));


	cout << "\n#: " << ltemp << replacex << rtemp << endl;

	
	strcpy(output,ltemp);
	strcat(output,replacex);
	strcat(output,rtemp);

	delete [] temp;
	delete [] ltemp;
	delete [] rtemp;
}


// replace string
void replacestr(char* buff,char* findstr,char* replacex,char* output)
{
	int xt;
	xt = ifindstr(0,buff,findstr);

	if(xt == -1)
	{
		return; // failure no string to replace
	}

	char* ptemp;
	char* outtemp;
	ptemp = new char[strlen(buff) + 500];
	outtemp = new char[strlen(buff) + 500];
	stringcopy(ptemp,buff);

	while(1)
	{
		int xr;
		xr = ifindstr(0,ptemp,findstr);
		if(xr == -1)
		{
			break;
		}
		else
		{
			rmvinst(ptemp,findstr,replacex,outtemp);
			stringcopy(ptemp,outtemp);
		}
	}

	stringcopy(output,ptemp);

	delete [] ptemp;
	delete [] outtemp;

}

// random char
char randomchar(int max)
{
	int x;
	x = rand()%max;
	char c;
	c = x;
	return c;
}
// random char + up
char randomchar(int max,int up)
{
	int x;
	x = rand()%max+up;
	char c;
	c = x;
	return c;
}
// random string
void randomstr(char* buff,int max, int size)
{
	for(int i = 0; i < size; i++)
	{
		if(rand()%2)
		{
			buff[i] = randomchar(max);
		}
		else
		{
			buff[i] = randomchar(max,rand()%10);
		}
	}
}
// remove char
void removechar(char* in,char* out,char c)
{
	int len;
	len = strlen(in);
	int ic = 0;
	for(int i = 0; i < len; i++)
	{
		if(in[i] != c)
		{
			out[ic] = in[i];
			ic++;
		}
	}
	out[ic] = 0;
}

// find single character in string
int findchar(char* str,char c)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1; // failure
}
// find char ex (inside)
int ifindchar(int start,char* str,char c)
{
	int len = strlen(str);
	for(int i = start+1; i < len; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1;
}
// find single char backward
int findcharb(char* str,char c)
{
	int len;
	len = strlen(str);
	for(int i = len; i > 0; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1;
}
// find single char backward
int ifindcharb(int start,char* str,char c)
{
	int len;
	len = strlen(str);
	for(int i = start-1; i > 0; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	return -1;
}

int  findcharcf(char* str,int start,int stop,char c)
{
	for(int i = start; i < stop; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1; // failure
}
int  findcharcb(char* str,int start,int stop,char c)
{
	for(int i = stop; i > start; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	return -1;// failure
}
// remove instances of string
void removestr(char* input,char* output,char* string)
{

	char* buff = input;
	char* findstr = string;

	int xt;
	xt = ifindstr(NULLPOS,buff,findstr);

	if(xt == -1)
	{
		return; // failure no string to replace
	}

	char* ptemp;
	char* outtemp;
	ptemp = new char[strlen(buff) + 500];
	outtemp = new char[strlen(buff) + 500];
	stringcopy(ptemp,buff);

	while(1)
	{
		int xr;
		xr = ifindstr(0,ptemp,findstr);
		if(xr == -1)
		{
			break;
		}
		else
		{
			rmvstrx(ptemp,findstr,outtemp);
			stringcopy(ptemp,outtemp);
		}
	}

	stringcopy(output,ptemp);

	delete [] ptemp;
	delete [] outtemp;

}

void rmvstrx(char* buff,char* output,char* string)
{
	int xt = ifindstr(NOPREV,buff,string);

	char* temp;
	temp = new char[strlen(buff)+1];
	stringcopy(temp,buff);

	char* ltemp;
	char* rtemp;

	ltemp = new char[strlen(buff)+1];
	rtemp = new char[strlen(buff)+1];

	leftcopy(buff,ltemp,xt);
	rightcopy(buff,rtemp,xt+strlen(string));
	
	strcpy(output,ltemp);
	strcat(output,rtemp);

	delete [] temp;
	delete [] ltemp;
	delete [] rtemp;
}

void strsavefile(char* filename,char* buff)
{
	ofstream fout(filename);

	fout << buff;

	fout.close();
}

int getfilestringlength(char* filename)
{
	int count = 0;
	ifstream fin(filename);
	if(fin)
	{
		char ch;
		while(fin.get(ch))
		{
			count++;
		}

		fin.close();
		return count;

	} else { return -1; } // failure

	return -1;
}

bool strloadfile(char* file,char* output)
{
	int count = 0;
	ifstream fin(file);
	if(fin)
	{
		char ch;
		int str_i = 0;
		while(fin.get(ch))
		{
			output[str_i] = ch;
			str_i++;
		}

		output[str_i] = 0;
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

void reversestring(char* input,char* output)
{
	int len;
	len = strlen(input);
	int fcount = 0;

	for(int i = len; i > 0; i--)
	{
		output[fcount] = input[i];
		fcount++;
	}
	
	output[fcount] = 0;
}

bool isstrvalid(char* string)
{
	int len = strlen(string);
	for(int i = 0; i < len; i++)
	{
		if(string[i] == 0)
		{
			return true; // true it is a null terminated string!
		}
	}

	return false;
}

// Save Master INI
bool SaveMasterINI(char* filename,MasterINI* mini)
{
	ofstream fout(filename,ios::binary);

	if(fout)
	{


	fout.write((char*)&mini,sizeof(mini));

	fout.close();

	return true;

	}
	fout.close();
	return false;
}
// Load master INI
bool LoadMasterINI(char* filename,MasterINI* mini)
{
	ifstream fin(filename,ios::binary);

	if(fin)
	{
		fin.read((char*)&mini,sizeof(mini));
	}
	
	fin.close();
	return false;
}

// string compare (case sensitive)
bool mstrcmp(char* buff1,char* buff2)
{
	int len;
	int len2;
	len = strlen(buff1);
	len2 = strlen(buff2);

	if(len != len2)
	{
		return false; // not equal length
	}

	for(int i = 0; i < len; i++)
	{
		if(buff1[i] != buff2[i])
		{
			return false;
		}
	}

	return true;
}

// string compare (not case sensitive)
bool mstrcmpx(char* buff1,char* buff2)
{
	int len;
	int len2;
	len = strlen(buff1);
	len2 = strlen(buff2);

	if(len != len2)
	{
		return false; // not equal length
	}

	for(int i = 0; i < len; i++)
	{
		if(tolower(buff1[i]) != tolower(buff2[i]))
		{
			return false;
		}
	}

	return true;
}

bool insidestr(char* buff1,char* buff2)
{
	int chk;
	chk = findstr(buff1,buff2);

	if(chk == -1)
	{
		return false;
	}
	
	return true;
}

bool insidestrx(char* buff1,char* buff2)
{
	char* pbuff1;
	char* pbuff2;

	pbuff1 = new char[strlen(buff1)+1];
	pbuff2 = new char[strlen(buff2)+1];

	stringcopy(pbuff1,buff1);
	stringcopy(pbuff2,buff2);

	lcase(pbuff1);
	lcase(pbuff2);

	int chk;
	chk = findstr(pbuff1,buff2);

	delete [] pbuff1;
	delete [] pbuff2;
	pbuff1 = 0;
	pbuff2 = 0;

	if(chk == -1)
	{
		return false;
	}
	
	return true;
}
// string seperation from 2 points
void strsep(char* str, char* sleft, int go_left, char* sright, int go_right)
{
	leftcopy(str,sleft,go_left);
	rightcopy(str,sright,go_right);
}
void strsetnull(char* str,int pos)
{
	str[pos] = 0;
}

void rmvnullset(char* str)
{
	int len;
	len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == 0)
		{
			str[i] = ' ';
		}
	}
}

int getnullpos(char* str)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == 0)
		{
			return i;
		}
	}

	return -1; // failure to find 0
}
// trim commented characters () 
void trimcom(char* str, char* output,char start_c,char stop_c)
{
	int len = strlen(str);
	int index = 0;

	bool iadd = true;

	for(int z = 0; z < len; z++)
	{
		if(str[z] == start_c)
		{
			iadd = false; 
		}

		if(str[z] == stop_c)
		{
			iadd = true;
		}

		if(iadd == true)
		{
			output[index] = str[z];
			index++;
		}
	}
	
	output[index] = 0;
}

// trim comments to an assembly language source file
void asmtrim(char* input,char* output)
{
	trimcom(input,output,';','\n');
}

// count the number of lines exisitng within the source
int countlines(char* buffer)
{
	return findoccourance(buffer,"\n");
}
// get the first letter thats not a space
int getfirstletter(char* buff)
{
	int len = strlen(buff);
	
	for(int i = 0; i < len; i++)
	{
		if(buff[i] != ' ')
		{
			return i;
		}
	}
	return -1; // failure! no letters
}

#endif

/* Master Assembly Script
   written by Jared Bruni
   www.LostSideDead.com
*/


#include<iostream>
#include<cstdarg>
#include<fstream>

using namespace std;
using namespace masterstring;

namespace masasm
{
	int errors = 0;// errors variable
	int i,z; // loop variables
	char program_name[255];
	
	bool fregister[30];
	
	void printerrorf(const char *error, ...);
	bool isfile(char* str);
	unsigned long getfilelen(const char *source);
	void readfile(const char *str, char *pfile);
	void compile(char* source);
	void runmxe();
	void trimcom(char* source);
	unsigned int quotesearch(unsigned int start, const char *str, const char *search);
	void killspace(char* str);
	void killwspace(char* str);
	void qkillwspace(char* str);
	int  charocc(char* str, char c);
	void addvars(char* str);
	void addcode(char* str);
	int  isinc(char* str);
	int  firstchar(char* str);
	void trimquotes(char* str,char* output);
	bool isnum(char* str);
	void setjmp(char* str);
	void replacestring(char* source,char* replace, char* with);
	void trimcolon(char* str);
	void clrflags();
	
	
	enum vartype { VAR_STRING, VAR_FLOAT, VAR_LONG ,VAR_LABEL};
	
	const int max = 500;
	
	template <class type>
	class Stack
	{
    public:
	Stack()
	{
		off_set = 0;
	}
	
	void push(type t)
	{
		if(off_set < max)
		{
			
			array[off_set] = t;
			off_set++;
			
		}
		
	}
	type pop()
	{
		type temp;
		off_set--;
		if(off_set >= 0)
		{
			
			temp = array[off_set];
			
		}
		return temp;
	}

	char* operator[](int pos)
	{
		return array[pos];
	}

	type array[max];
	int off_set;
	};
		
	
	struct CodeBlock
	{
		char inc[100];
		char* op1;
		char* op2;
		
		CodeBlock()
		{
			op1 = NULL;
			op2 = NULL;
		}
		
		~CodeBlock()
		{
			if(op1 != NULL)
			{
				delete [] op1;
			}
			
			if(op2 != NULL)
			{
				delete [] op2;
			}
		}
		
		void set(char* opcode,char* operand1,char*operand2)
		{
			mstrcpy(inc,opcode);
			op1 = new char [ mstrlen(operand1) + 1 ];
			op2 = new char [ mstrlen(operand2) + 1 ];
			mstrcpy(op1,operand1);
			mstrcpy(op2,operand2);
		}
	};
	
	struct Variables
	{
		char *var;
		vartype type;
		char name[255];
		
		Variables()
		{
			var = NULL;
		}
		
		~Variables()
		{
			if(var != NULL)
			{
				delete [] var;
				var = NULL;
			}
		}
		
		void set(const char *str)
		{
			if( var != NULL )
			{
				delete [] var;
				var = NULL;
			}
			
			var = new char [ mstrlen((char*)str) + 1 ];
			
			mstrcpy(var,(char*)str);
		}
	};
	
	struct CodeLabel
	{
		char name[255];
		int  address;
	};
	
	
	struct Program
	{
		int var_off;
		int ip;
		int i_p;
		int c_off;
		
		Variables var[10000];
		CodeBlock code[10000];
		CodeLabel code_label[1000];
		Stack<char*> stack;
		void (*interupt)(int x);
		
		Program()
		{
			var_off = 0;
			ip = 0;
			i_p = 0;
			c_off = 0;
		}
		
		~Program()
		{
			
			
		}
		
		void addcode(char* name, char* operand1,char* operand2)
		{
			code[ip].set(name,operand1,operand2);
			ip++;
		}
		
		void addvar(char* name, const char *str, vartype type)
		{
			var[var_off].set(str);
			mstrcpy(var[var_off].name,name);
			var[var_off].type = type;
			var_off++;
		}
		void addcodelabel(char* name, const char *pos)
		{
			mstrcpy(code_label[c_off].name,name);
			code_label[c_off].address = atoi(pos);
			c_off ++;
		}
		
		
		int getvarpos(char* name)
		{
			for(int r = 0; r < var_off; r++)
			{
				if(mstrfind(var[r].name,name) != -1)
				{
					return r;
				}
			}
			
			return -1;
		}
		
		int getcodepos(char* name)
		{
			for(int r = 0; r < c_off; r++)
			{
				if(mstrfind(code_label[r].name,name) != -1)
				{
					return code_label[r].address;
				}
			}
			
			return -1;
		}

		void setinterupt(void(*i)(int x))
		{
			interupt = i;
		}
	};
	
	Program program;
}

void masasm::printerrorf(const char *str, ...)
{
	va_list list; 
	char string[5000];
	va_start(list, str); 
	vsprintf((char*)string,str,list);
	va_end(list); 
//	cout << "error(" << errors << ") " << string << endl;
	errors++;
}

bool masasm::isfile(char* str)
{
	FILE* file;
	file = fopen(str,"rb+");
	if(file == NULL)
	{
		return false;
	}
	
	fclose(file);
	return true;
}


unsigned long masasm::getfilelen(const char *source)
{
	unsigned long i = 0;
	FILE* file;
	
	file = fopen(source,"rb+");
	if(file == NULL)
	{
		return -1;// faliure
	}
	
	while(1)
	{
		char c = fgetc(file);
		if(feof(file))
		{
			break;
		}
		else
		{
			i++;
		}
	}
	
	fclose(file);
	
	return i;
}


void masasm::readfile(const char *source, char *pfile)
{
	unsigned long pos = 0;
	FILE* file;
	
	file = fopen(source,"rb+");
	while(1)
	{
		char c = fgetc(file);
		if(feof(file))
		{
			break;
		}
		else
		{
			pfile[pos] = c;
			pos++;
		}
	}
	
	pfile[pos] = 0;
	
	fclose(file);
}

void masasm::compile(char* source)
{
	char* str = new char [ getfilelen(source) + 1 ];
	char* var = NULL;
	char* body = NULL;
	
	readfile(source,str);
	trimcom(str);
	unsigned int pos,pos2 = 0,vpos,vpos2,vpos3;
	int obrace,cbrace;
	obrace = charocc(str,'{');
	cbrace = charocc(str,'}');
	if(obrace != cbrace)
	{
		printerrorf(" blocks missaligned ");
		goto done;
	}
	
	pos = quotesearch(0,str,"mas");
	if(pos == -1)
	{
		printerrorf(" mas block not found ");
		goto done;
	}
	pos2 = quotesearch(pos,str,"{");
	if(pos == -1)
	{
		printerrorf(" mas blocking missing following { ");
		goto done;
	}
	
	mstrmid(str,program_name,pos+3,pos2);
	killspace(program_name);
	
	vpos = quotesearch(0,str,"var");
	if(vpos == -1)
	{
		printerrorf(" missing var block ");
		goto done;
	}
	vpos2 = quotesearch(vpos,str,"{");
	vpos3 = quotesearch(vpos2,str,"}");
	var = new char [ mstrlen(str) + 1 ];
	
	mstrmid(str,var,vpos2+1,vpos3);
	addvars(var);
	
	vpos = quotesearch(0,str,"begin");
	vpos2 = quotesearch(vpos,str,"{");
	vpos3 = quotesearch(vpos2,str,"}");
	
	body = new char [ mstrlen(str) + 1 ];
	mstrmid(str,body,vpos2+1,vpos3);
	setjmp(body);
	addcode(body);
	
	
done:
	delete [] str;
	str = NULL;
	if(var != NULL)
	{
		delete [] var;
		var = NULL;
	}
	
	if(body != NULL)
	{
		delete [] body;
		body = NULL;
	}
	
	if( errors == 0 )
	{
		runmxe();
	}
	else
	{
//		cout << " compiled with " << masasm::errors << " error(s) " << endl;
	}
}


void masasm::runmxe()
{
	
	int ip = 0; // instruction_pointer
	
	
	while(1)
	{
		if(ip > program.ip)
		{
			break;
		}
		
		int inc = isinc(program.code[ip].inc);
		
		switch(inc)
		{
		case 0x1://mov
			{
				int var1,var2;
				var1 = program.getvarpos(program.code[ip].op1);
				var2 = program.getvarpos(program.code[ip].op2);
				
				
				if(var2 == -1)
				{
					program.var[var1].set(program.code[ip].op2);
				}
				else
				{
					program.var[var1].set(program.var[var2].var);
				}
			}
			break;
		case 0x2:
			{
				system("cls");
			}
			break;
			
		case 0x3://println
			{
				if(mstrfind(program.code[ip].op1,"\"") != -1)
				{
					char* temp = new char [ mstrlen(program.code[ip].op1) + 1 ];
					trimquotes(program.code[ip].op1,temp);
					printf("%s\n",temp);
					delete [] temp;
				}
				else
				{
					int var;
					var = program.getvarpos(program.code[ip].op1);
					if(var != -1)
					{
						if(mstrfind(program.var[var].var,"\"") != -1)
						{
							char* temp = new char [ mstrlen(program.var[var].var) + 1 ];
							trimquotes(program.var[var].var,temp);
							printf("%s\n",temp);
							delete [] temp;
						}
						else
						{
							printf("%s\n",program.var[var].var);
						}
					}
				}
			}
			break;
		case 0x21:// print
			{
				if(mstrfind(program.code[ip].op1,"\"") != -1)
				{
					char* temp = new char [ mstrlen(program.code[ip].op1) + 1 ];
					trimquotes(program.code[ip].op1,temp);
//					cout << temp;
					delete [] temp;
				}
				else
				{
					int var;
					var = program.getvarpos(program.code[ip].op1);
					if(var != -1)
					{
						if(mstrfind(program.var[var].var,"\"") != -1)
						{
							char* temp = new char [ mstrlen(program.var[var].var) + 1 ];
							trimquotes(program.var[var].var,temp);
//							cout << temp;
							delete [] temp;
						}
						else
						{
//							cout <<program.var[var].var;
						}
					}
				}
			}
			break;
			
		case 0x4:
			{
				int var1;
				var1 = program.getvarpos(program.code[ip].op1);
				char input[5000];
//				cin.getline(input,5000,'\n');
				program.var[var1].set(input);
			}
			break;
		case 0x5:// return
			{
				return;
			}
			break;
		case 0x6:// cmp
			{
				clrflags();
				char* op1 = program.code[ip].op1;
				char* op2 = program.code[ip].op2;
				if(mstrfind(op1,"\"") != -1 && mstrfind(op2,"\"") != -1)
				{
					// 2 strings
					if(strcmp(op1,op2) == 0)
					{
						fregister[0] = true;
					}
					else
					{
						fregister[0] = false;
						fregister[4] = true;
					}
				}
				
				int var1,var2;
				var1 = program.getvarpos(op1);
				var2 = program.getvarpos(op2);
				
				if(var2 == -1)
				{
					int var1_val = atoi(program.var[var1].var);
					int val = atoi(op2);
					
					if(var1_val == val)
					{
						fregister[0] = true;
					}
					else
					{
						fregister[0] = false;
					}
					
					if(var1_val > val)
					{
						fregister[1] = true;
					}
					else
					{
						fregister[1] = false;
					}
					
					if(var1_val >= val)
					{
						fregister[2] = true;
					}
					
					if(var1_val <= val)
					{
						fregister[3] = true;
					}
					
					if(var1_val != val)
					{
						fregister[4] = true;
					}
				}
				else
				{
					int var1_val = atoi(program.var[var1].var);
					int val = atoi(program.var[var1].var);
					
					if(var1_val == val)
					{
						fregister[0] = true;
					}
					else
					{
						fregister[0] = false;
					}
					
					if(var1_val > val)
					{
						fregister[1] = true;
					}
					
					if(var1_val >= val)
					{
						fregister[2] = true;
					}
					
					if(var1_val <= val)
					{
						fregister[3] = true;
					}
					
					if(var1_val != val)
					{
						fregister[4] = true;
					}
					
					if(var1_val < val)
					{
						fregister[5] = true;
					}
					
				}
				
			}
			break;
		case 0x7:// jmp
			{		
				ip = atoi(program.code[ip].op1);
				continue;
			}
			break;
		case 0x8:// je (jmp if equal)
			{
				if(fregister[0] == true)
				{
					ip = atoi(program.code[ip].op1);
					continue;
				}
			}
			break;
		case 0x9:// jne
			{
				if(fregister[4] == true)
				{
					ip = atoi(program.code[ip].op1);
					continue;
				}
			}
			break;
		case 0x10://jg // jump if greater
			{
				if(fregister[1] == true)
				{
					ip = atoi(program.code[ip].op1);
					continue;
				}
			}
			break;
		case 0x11:
			{
				if(fregister[5] == true)
				{
					ip = atoi(program.code[ip].op1);
					continue;
				}
			}
			break;
		case 0x12:
			{
				if(fregister[2] == true)
				{
					ip = atoi(program.code[ip].op1);
					continue;
				}
			}
			break;
		case 0x13:
			{
				if(fregister[3] == true)
				{
					ip = atoi(program.code[ip].op1);
					continue;
				}
			}
			break;
		case 0x20:// pause
			{
				system("pause");
			}
			break;
		case 0x30:// inc
			{
				int var;
				var = program.getvarpos(program.code[ip].op1);
				long val;
				val = atol(program.var[var].var);
				val++;
				char sval[25];
				itoa(val,sval,10);
				program.var[var].set(sval);
			}
			break;
		case 0x31:// dec
			{
				int var;
				var = program.getvarpos(program.code[ip].op1);
				long val;
				val = atol(program.var[var].var);
				val--;
				char sval[25];
				itoa(val,sval,10);
				program.var[var].set(sval);
			}
			break;
		case 0x32:// add
			{
				int var1,var2;
				var1 = program.getvarpos(program.code[ip].op1);
				var2 = program.getvarpos(program.code[ip].op2);
				if(var1 != -1 && var2 != -1)
				{
					long val1,val2;
					val1 = atol(program.var[var1].var);
					val2 = atol(program.var[var2].var);
					val1 = val1 + val2;
					char sval[25];
					itoa(val1,sval,10);
					program.var[var1].set(sval);
				}
				else
				{
					long val1,val2;
					val1 = atol(program.var[var1].var);
					val2 = atol(program.code[ip].op2);
					val1 = val1 + val2;
					char sval[25];
					ltoa(val1,sval,10);
					program.var[var1].set(sval);
				}
			}
			break;
		case 0x33:// sub
			{
				int var1,var2;
				var1 = program.getvarpos(program.code[ip].op1);
				var2 = program.getvarpos(program.code[ip].op2);
				if(var1 != -1 && var2 != -1)
				{
					long val1,val2;
					val1 = atol(program.var[var1].var);
					val2 = atol(program.var[var2].var);
					val1 = val1 - val2;
					char sval[25];
					ltoa(val1,sval,10);
					program.var[var1].set(sval);
				}
				else
				{
					long val1,val2;
					val1 = atol(program.var[var1].var);
					val2 = atol(program.code[ip].op2);
					val1 = val1 - val2;
					char sval[25];
					ltoa(val1,sval,10);
					program.var[var1].set(sval);
				}
				
			}
			break;
		case 0x34:// mul
			{
				int var1,var2;
				var1 = program.getvarpos(program.code[ip].op1);
				var2 = program.getvarpos(program.code[ip].op2);
				if(var1 != -1 && var2 != -1)
				{
					long val1,val2;
					val1 = atol(program.var[var1].var);
					val2 = atol(program.var[var2].var);
					val1 = val1 * val2;
					char sval[25];
					ltoa(val1,sval,10);
					program.var[var1].set(sval);
				}
				else
				{
					long val1,val2;
					val1 = atol(program.var[var1].var);
					val2 = atol(program.code[ip].op2);
					val1 = val1 * val2;
					char sval[25];
					ltoa(val1,sval,10);
					program.var[var1].set(sval);
				}
				
			}
			break;
		case 0x35:// div
			{
				int var1,var2;
				var1 = program.getvarpos(program.code[ip].op1);
				var2 = program.getvarpos(program.code[ip].op2);
				if(var1 != -1 && var2 != -1)
				{
					long val1,val2;
					val1 = atol(program.var[var1].var);
					val2 = atol(program.var[var2].var);
					if(val1 != 0 && val2 != 0)
					{
						
						val1 = val1 / val2;
						char sval[25];
						ltoa(val1,sval,10);
						program.var[var1].set(sval);
						
					}
				}
				else
				{
					long val1,val2;
					val1 = atol(program.var[var1].var);
					val2 = atol(program.code[ip].op2);
					if( val1 != 0 && val2 != 0 )
					{
						
						val1 = val1 / val2;
						char sval[25];
						ltoa(val1,sval,10);
						program.var[var1].set(sval);
						
					}
				}
				
			}
			break;
		case 0x40://finc
			{
				int var;
				var = program.getvarpos(program.code[ip].op1);
				double val;
				val = atof(program.var[var].var);
				val++;
				char sval[25];
				gcvt(val,10,sval);
				program.var[var].set(sval);
			}
			break;
		case 0x41://fdec
			{
				int var;
				var = program.getvarpos(program.code[ip].op1);
				double val;
				val = atof(program.var[var].var);
				val--;
				char sval[25];
				gcvt(val,10,sval);
				program.var[var].set(sval);
			}
			break;
		case 0x42://fadd
			{
				int var1,var2;
				var1 = program.getvarpos(program.code[ip].op1);
				var2 = program.getvarpos(program.code[ip].op2);
				if(var1 != -1 && var2 != -1)
				{
					double val1,val2;
					val1 = atof(program.var[var1].var);
					val2 = atof(program.var[var2].var);
					val1 = val1 + val2;
					char sval[25];
					gcvt(val1,10,sval);
					program.var[var1].set(sval);
				}
				else
				{
					double val1,val2;
					val1 = atof(program.var[var1].var);
					val2 = atof(program.code[ip].op2);
					val1 = val1 + val2;
					char sval[25];
					gcvt(val1,10,sval);
					program.var[var1].set(sval);
				}
			}
			break;
		case 0x43://fsub
			{
				int var1,var2;
				var1 = program.getvarpos(program.code[ip].op1);
				var2 = program.getvarpos(program.code[ip].op2);
				if(var1 != -1 && var2 != -1)
				{
					double val1,val2;
					val1 = atof(program.var[var1].var);
					val2 = atof(program.var[var2].var);
					val1 = val1 - val2;
					char sval[25];
					gcvt(val1,10,sval);
					program.var[var1].set(sval);
				}
				else
				{
					double val1,val2;
					val1 = atof(program.var[var1].var);
					val2 = atof(program.code[ip].op2);
					val1 = val1 - val2;
					char sval[25];
					gcvt(val1,10,sval);
					program.var[var1].set(sval);
				}
			}
			break;
		case 0x44://fmul
			{
				int var1,var2;
				var1 = program.getvarpos(program.code[ip].op1);
				var2 = program.getvarpos(program.code[ip].op2);
				if(var1 != -1 && var2 != -1)
				{
					double val1,val2;
					val1 = atof(program.var[var1].var);
					val2 = atof(program.var[var2].var);
					val1 = val1 * val2;
					char sval[25];
					gcvt(val1,10,sval);
					program.var[var1].set(sval);
				}
				else
				{
					double val1,val2;
					val1 = atof(program.var[var1].var);
					val2 = atof(program.code[ip].op2);
					val1 = val1 * val2;
					char sval[25];
					gcvt(val1,10,sval);
					program.var[var1].set(sval);
				}
			}
			break;
		case 0x45://fdiv
			{
				int var1,var2;
				var1 = program.getvarpos(program.code[ip].op1);
				var2 = program.getvarpos(program.code[ip].op2);
				if(var1 != -1 && var2 != -1)
				{
					double val1,val2;
					val1 = atof(program.var[var1].var);
					val2 = atof(program.var[var2].var);
					if(val1 != 0 && val2 != 0)
					{
						
						val1 = val1 / val2;
						char sval[25];
						gcvt(val1,10,sval);
						program.var[var1].set(sval);
						
					}
				}
				else
				{
					double val1,val2;
					val1 = atof(program.var[var1].var);
					val2 = atof(program.code[ip].op2);
					if(val1 != 0 && val2 != 0)
					{
						
						val1 = val1 / val2;
						char sval[25];
						gcvt(val1,10,sval);
						program.var[var1].set(sval);
						
					}
				}
			}
			break;
		case 0x50://push
			{
				int var;
				var = program.getvarpos(program.code[ip].op1);
				program.stack.push(program.var[var].var);
			}
			break;
		case 0x51://pop
			{
				int var;
				var = program.getvarpos(program.code[ip].op1);
				char* str;
				str = program.stack.pop();
				program.var[var].set(str);
			}
			break;
		case 0x60://int
			{
				program.interupt(atoi(program.code[ip].op1));
			}
			break;
		}
		
		ip++;
		
	}
}

void masasm::addvars(char* str)
{
	killwspace(str);
	Tokenize lines;
	lines.tokenize(str,'\n');
	for(i = 0; i < lines.length; i++)
	{
		Tokenize line;
		line.tokenize(lines[i],' ');
		if(line.length > 0 )
		{
			if( mstrfind(line[0],"var") != - 1)
			{
				if( mstrfind(line[0],"&") != -1)
				{
					program.addvar(line[1],"0",VAR_LONG);
					continue;
				}
				
				if( mstrfind(line[0],"$") != -1 )
				{
					program.addvar(line[1]," ",VAR_STRING);
					continue;
				}
				
				if( mstrfind(line[0],"#") != -1 )
				{
					program.addvar(line[1],"0.0",VAR_FLOAT);
					continue;
				}
				
				printerrorf(" variable missing type value (&$#) [%s]", line[0] );
				
			}
			else
			{
				printerrorf(" invalid variable decleration ", lines[i]);
			}
		}
	}
}

void masasm::addcode(char* str)
{
	qkillwspace(str);
	TokenizeQuotes lines;
	lines.tokenize(str,'\n');
	int q = 0;
	
	// first add all the code labels to
	// a table for look up later on
	for(q = 0; q < lines.length; q++)
	{
		if(quotesearch(0,lines[q],":") != -1 )
		{
			char istr[25];
			itoa(q,istr,10);
			program.addcodelabel(lines[q],istr);
		}
	}
	// proccess code blocks
	for(q = 0; q < lines.length; q++)
	{
		if(quotesearch(0,lines[q],":") == -1 && mstrlen(lines[q]) > 3)
		{
			if(quotesearch(0,lines[q],",") == -1)
			{
				// 0 operand
				if(mstrfind(lines[q]," ") == -1)
				{
					program.addcode(lines[q],"","");
				}
				else
				{
					//1 operand
					TokenizeQuotes line;
					line.tokenize(lines[q],' ');
					program.addcode(line[0],line[1],"");
					
				}
				
			}
			else
			{
				// 2 operands
				int s_pos = quotesearch(firstchar(lines[q]),lines[q]," ");
				int c_pos = quotesearch(0,lines[q],",");
				char inc[100];
				mstrleft(lines[q],inc,s_pos);
				char* operand1 = new char [ mstrlen(lines[q]) + 1 ];
				char* operand2 = new char [ mstrlen(lines[q]) + 1 ];
				mstrmid(lines[q],operand1,s_pos+1,c_pos);
				mstrright(lines[q],operand2,c_pos+1);
				program.addcode(inc,operand1,operand2);
				delete [] operand1;
				delete [] operand2;
				
			}
		}
	}
	
	// now that the code blocks are built
	// check each ones opcode to ensure it
	// is a correct instruction
	for(q = 0; q < program.ip; q++)
	{
		if(isinc(program.code[q].inc) == -1)
		{
			printerrorf(" invalid instruction [%s]",program.code[q].inc);
		}
	}
	
}


void masasm::trimcom(char* str)
{
	char* temp = new char [ mstrlen(str) + 1 ];
	int off_pos = 0;
	bool go = true;
	
	for(i = 0; i < mstrlen(str); i++)
	{
		if( str[i] == ';' )
		{
			go = false;
		}
		
		if( str[i] == '\n' && go == false )
		{
			go = true;
		}
		
		if(go == true)
		{
			temp[off_pos] = str[i];
			off_pos++;
		}
	}
	
	temp[off_pos] = 0;
	mstrcpy(str,temp);
	delete [] temp;
	temp = 0;
}


unsigned int masasm::quotesearch(unsigned int start, const char *str, const char *search)
{
	bool go = true; 
	
	for(i = start; i < mstrlen((char*)str); i++)
	{
		if( str[i] == '\"' )
		{
			go = !go;
		}
		
		if( str[i] == search[0] && go == true )
		{
			bool ok = true;
			
			for(z = 0; z < mstrlen((char*)search); z++)
			{
				if( str[i+z] != search[z] )
				{
					ok = false;
					break;
				}
			}
			
			if(ok == true)
			{
				return i;
			}
		}
		
	}
	
	return -1;
}

void masasm::killspace(char* str)
{
	char *temp = new char [ mstrlen(str) + 1 ];
	z = 0;
	for(i = 0; i < mstrlen(str); i++)
	{
		if( str[i] != ' ' && str[i] != '\n' )
		{
			temp[z] = str[i];
			z++;
		}
	}
	
	temp[z] = 0;
	mstrcpy(str,temp);
	delete [] temp;
}

void masasm::killwspace(char* str)
{
	char *temp = new char [ mstrlen(str) + 1 ];
	z = 0;
	for(i = 0; i < mstrlen(str); i++)
	{
		if(str[i] == ' ' && str[i+1] == ' ')
		{
			continue;
		}
		else
		{
			temp[z] = str[i];
			z++;
		}
	}
	
	temp[z] = 0;
	mstrcpy(str,temp);
	delete [] temp;
}

void masasm::qkillwspace(char* str)
{
	char *temp = new char [ mstrlen(str) + 1 ];
	z = 0;
	bool go = true;
	
	for(i = 0; i < mstrlen(str); i++)
	{
		if(str[i] == '\"')
		{
			go = !go;
		}
		
		if(str[i] == ' ' && str[i+1] == ' ' && go == true)
		{
			continue;
		}
		else
		{
			temp[z] = str[i];
			z++;
		}
	}
	
	temp[z] = 0;
	mstrcpy(str,temp);
	delete [] temp;
}

int masasm::charocc(char* str, char c)
{
	int amt = 0;
	
	for(i = 0; i < mstrlen(str); i++)
	{
		if(str[i] == c)
		{
			amt++;
		}
	}
	
	return amt;
}


int masasm::isinc(char* str)
{
	
	if(strcmp(str,"mov") == 0)
	{
		return 0x1;
	}
	
	if(strcmp(str,"cls") == 0)
	{
		return 0x2;
	}
	
	if(strcmp(str,"println") == 0)
	{
		return 0x3;
	}
	
	if(strcmp(str,"input") == 0)
	{
		return 0x4;
	}
	
	if(strcmp(str,"return") == 0)
	{
		return 0x5;
	}
	
	if(strcmp(str,"cmp") == 0)
	{
		return 0x6;
	}
	
	if(strcmp(str,"jmp") == 0)
	{
		return 0x7;
	}
	if(strcmp(str,"je") == 0)
	{
		return 0x8;
	}
	
	if(strcmp(str,"jne") == 0)
	{
		return 0x9;
	}
	
	if(strcmp(str,"jg") == 0)
	{
		return 0x10;
	}
	if(strcmp(str,"jl") == 0)
	{
		return 0x11;
	}
	if(strcmp(str,"jge") == 0)
	{
		return 0x12;
	}
	if(strcmp(str,"jle") == 0)
	{
		return 0x13;
	}
	
	
	
	if(strcmp(str,"pause") == 0)
	{
		return 0x20;
	}
	
	if(strcmp(str,"print") == 0)
	{
		return 0x21;
	}
	
	if(strcmp(str,"inc") == 0)
	{
		return 0x30;
	}
	if(strcmp(str,"dec") == 0)
	{
		return 0x31;
	}
	if(strcmp(str,"add") == 0)
	{
		return 0x32;
	}
	if(strcmp(str,"sub") == 0)
	{
		return 0x33;
	}
	if(strcmp(str,"mul") == 0)
	{
		return 0x34;
	}
	if(strcmp(str,"div") == 0)
	{
		return 0x35;
	}
	
	if(strcmp(str,"finc") == 0)
	{
		return 0x40;
	}
	if(strcmp(str,"fdec") == 0)
	{
		return 0x41;
	}
	if(strcmp(str,"fadd") == 0)
	{
		return 0x42;
	}
	if(strcmp(str,"fsub") == 0)
	{
		return 0x43;
	}
	if(strcmp(str,"fmul") == 0)
	{
		return 0x44;
	}
	if(strcmp(str,"fdiv") == 0)
	{
		return 0x45;
	}

	if(strcmp(str,"push") == 0)
	{
		return 0x50;
	}
	if(strcmp(str,"pop") == 0)
	{
		return 0x51;
	}

	if(strcmp(str,"int") == 0)
	{
		return 0x60;
	}

	
	
	return -1;// failure
}

int masasm::firstchar(char* str)
{
	bool go = true;
	
	for(i = 0; i < mstrlen(str); i++)
	{
		if(str[i] == '\"')
		{
			go = !go;
		}
		
		if(go == true && str[i] != ' ' && str[i] != '\n')
		{
			return i;
		}
	}
	
	return -1; // failure
}

void masasm::trimquotes(char* str, char* output)
{
	z = 0;
	for(i = 0; i < mstrlen(str); i++)
	{
		if(str[i] != '\"')
		{
			output[z] = str[i];
			z++;
		}
	}
	
	output[z] = 0;
}

bool masasm::isnum(char* str)
{
	
	for(i = 0; i < mstrlen(str); i++)
	{
		if(isdigit(str[i]))
		{
		}
		else
		{
			return false;
		}
	}
	
	
	return true;
}


void masasm::setjmp(char* str)
{
	CodeLabel labels[1000];
	int label_off = 0;
	
	
	TokenizeQuotes token;
	token.tokenize(str,'\n');
	int address = 0;
	
	for(int r = 0; r < token.length; r++)
	{
		if(quotesearch(0,token[r],":") != -1)
		{
			trimcolon(token[r]);
			strcpy(labels[label_off].name,token[r]);
			labels[label_off].address = address;
			label_off ++;
		}
		
		if( mstrlen(token[r]) > 3 )
		{
			address ++ ;
		}
	}
	
	for(int q = 0; q < label_off; q++)
	{
		char addy[25];
		itoa(labels[q].address,addy,10);
		replacestring(str,labels[q].name,addy);
	}
}

void masasm::replacestring(char* source,char* replace, char* with)
{
	int pos;
	pos = quotesearch(0,source,replace);
	if(pos == -1)
	{
		return;
	}
	else
	{
		char* left = new char [ mstrlen(source) + 1 ];
		char* right = new char [ mstrlen(source) + 1 ];
		mstrleft(source,left,pos);
		mstrright(source,right,pos+mstrlen(replace));
		mstrcpy(source,left);
		mstrcat(source,with);
		mstrcat(source,right);
		delete [] left;
		delete [] right;
		replacestring(source,replace,with);
	}
}

void masasm::trimcolon(char* str)
{
	char* temp = new char [ mstrlen(str) + 1 ];
	z = 0;
	for(i = 0; i < mstrlen(str); i++)
	{
		if(str[i] != ':')
		{
			
			temp[z] = str[i];
			z++;
			
		}
	}
	temp[z] = 0;
	strcpy(str,temp);
	delete [] temp;
}


void masasm::clrflags()
{
	for(i  = 0; i < 30; i++)
	{
		fregister[i] = false;
	}
	
}
#endif


#ifdef MASTER_LIST

/* List Template example
   writen by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/

const int size = 100;

template<class type>
class List
{
public:
	List();
	void add(type t);
	type get(int number);
	int  length();
private:
	type list[size];
	int  pos;
};

template<class type>
List<type>::List()
{
	pos = 0;
}

template<class type>
void List<type>::add(type t)
{
	if(pos < size)
	{
		list[pos] = t;
		pos++;
	}
}

template<class type>
type List<type>::get(int number)
{
	if(number > pos) { return 0; }

	return list[number];
}

template<class type>
int List<type>::length()
{
	return pos;
}

#endif

// =]
// "you wreck me baby, yeah you break me in two"