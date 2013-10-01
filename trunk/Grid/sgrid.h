# ifndef SGRID_H
# define SGRID_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <io.h>
#include "sHeader.h"
#include "grdTypes.h"
//#include "errorcodes.h"

#define MISSINGSHORT -32767

using namespace std;

#pragma warning(disable:4251)

class __declspec( dllexport ) sGrid
{
	public:
		
		//CONSTRUCTORS
		sGrid();
		~sGrid();
		
		//OPERATORS
		short operator()( int Column, int Row );
				
		//FUNCTIONS
		bool open( const char * Filename, bool InRam = true, GRID_TYPE GridType = USE_EXTENSION, void (*callback)( int number, const char * message ) = NULL );
		bool initialize( const char * Filename, sHeader Header, short initialValue, bool InRam = true, GRID_TYPE GridType = USE_EXTENSION );		
		bool save( const char * Filename = "", GRID_TYPE GridType = USE_EXTENSION, void (*callback)(int number, const char * message ) = NULL );
		bool close();
		void clear(short clearValue);
	
		//MAPPING FUNCTIONS
		void ProjToCell( double x, double y, long & column, long & row );
		void CellToProj( long column, long row, double & x, double & y );
					
		//DATA MEMBER ACCESS
		inline sHeader getHeader();
		void setHeader( sHeader h );
		inline short getValue( int Column, int Row );
		inline void setValue( int Column, int Row, short Value );
		bool inRam();		
		short maximum();
		short minimum();
		long LastErrorCode();

		short ** getArrayPtr();

		void asciiReadHeader( istream & in );

	private:

		inline int round( double d );
		GRID_TYPE getGridType( const char * filename );	
		void dealloc();
		void alloc();		
		inline bool inGrid( long column, long row );
		inline short getValueDisk( int column, int row );
		inline void setValueDisk( int column, int row, short value );
		void clearDisk(short clearValue);

		bool readDiskToMemory( void (*callback)(int number, const char * message ) = NULL );
		bool readDiskToDisk( void (*callback)(int number, const char * message ) = NULL );
		bool writeMemoryToDisk( void(*callback)(int number, const char * message ) = NULL );
		bool writeDiskToDisk();

		//ASCII GRID FUNCTIONS		
		bool asciiReadDiskToMemory( void (*callback)(int number, const char * message ) = NULL );
		bool asciiReadDiskToDisk( void (*callback)(int number, const char * message ) = NULL );
		bool asciiWriteMemoryToDisk( void(*callback)(int number, const char * message ) = NULL );
		bool asciiWriteDiskToDisk();		
		void asciiReadFooter( istream & in );
		void asciiWriteHeader( ostream & out );
		void asciiWriteFooter( ostream & out );
		bool asciiIsHeaderValue( CString headerValue, istream & in );
		bool asciiSaveAs( CString filename, void(*callback)(int number, const char * message) = NULL );

		//BINARY GRID FUNCTIONS
		bool binaryReadDiskToMemory( void (*callback)(int number, const char * message ) = NULL );
		bool binaryReadDiskToDisk();
		bool binaryWriteMemoryToDisk( void(*callback)(int number, const char * message ) = NULL );
		bool binaryWriteDiskToDisk();		
		bool binaryInitializeDisk( short InitialValue );			
		void binaryReadHeader( FILE * in );
		void binaryWriteHeader( FILE * out );
		short binaryGetValueDisk( int Column, int Row );
		void binarySetValueDisk( int Column, int Row, short Value );
		void binaryClearDisk(short clearValue);
		void binaryBufferRows( int CenterRow );
		bool binarySaveAs( CString filename, void(*callback)(int number, const char * message) = NULL );

		//ESRI GRID FUNCTIONS
		bool esriReadDiskToMemory( void (*callback)(int number, const char * message ) = NULL );
		bool esriReadDiskToDisk();
		bool esriWriteMemoryToDisk( void(*callback)(int number, const char * message ) = NULL );
		bool esriWriteDiskToDisk();		
		bool esriInitializeDisk( short InitialValue );			
		short esriGetValueDisk( int Column, int Row );
		void esriSetValueDisk( int Column, int Row, short Value );
		void esriClearDisk(short clearValue);
		void esriBufferRows( int CenterRow );
		bool esriSaveAs( CString filename, void(*callback)(int number, const char * message) = NULL );

		//SDTS GRID FUNCTIONS
		bool sdtsReadDiskToMemory( void(*callback)(int number, const char * message ) = NULL );
		void get_iref(double & xhrs, double & yhrs);
		void get_xref(void);
		void dem_rc(int status, int & ncol, int & nrow);
		void dem_head(int);
		void dem_mbr(int status, double & SWX, double & SWY, double & NWX, double & NWY, double & NEX, double & NEY, double & SEX, double & SEY);
		void cell_range(int status, long & voidvalue, long & fillvalue);
		void cells_out(const char * filename, int status, long fillvalue, void (*callback)(int number, const char * message ) = NULL );
		void get_nw_corner(double & upperlx, double & upperly);
		int  s123tol2(char *,long *,int);
		bool read_sdts_header(char * filename, sHeader & h, long & fillvalue);
		void baseAndId();
		char FeetOrMeters();

	private:

		sHeader gridHeader;
		bool isInRam;
		short ** data;
		short max;
		short min;
		GRID_TYPE gridType;
		CString gridFilename;

		//ASCII Specific Variables
			//Flags used to adjust reference to cell center
			bool xllcorner;
			bool yllcorner;
		//BINARY Specific Variables
			short * row_one;
			short * row_two;	//Current row
			short * row_three;
			long current_row;
			FILE * file_in_out;
			long file_position_beg_of_data;			
			DATA_TYPE data_type;
		//ESRI Specific Variables
			int grid_layer;
			void * row_buf1;		
			void * row_buf2;
			void * row_buf3;					
		//SDTS Specific Variables
			FILE *fpin;
			long int_level;
			double sfax, sfay, xorg, yorg;
			double x[5];
			double y[5];
			long nxy;
			long str_len;
			long li;
			int stat2;
			int status;
			char temp[100];
			char ice;
			char leadid;
			char ccs[4];
			char tag[10];
			char fdlen[10];
			char *fdname;
			char mod_name[10];
			char base_name[MAX_STRING_LENGTH];
			char file_name[MAX_STRING_LENGTH];
			char string[5000];
			char descr[5000];
			char frmts[500];
			int order;
			char rsnm[5];

		//Flags used to indicate if the max or min value has been overwritten
		bool findNewMax;		
		bool findNewMin;	
		
		long lastErrorCode;
};

# endif
