#ifndef HOOTILITIES
#define HOOTILITIES

#include "TChain.h"
#include "TLegend.h"
#include "TCut.h"
#include <vector>

void compareDataMC( vector<TChain*> chmc , vector<char*> labels , TChain* chdata , char* var , 
		    TCut sel , TCut weight , int nbins ,  float xmin , float xmax , char* xtitle , 
		    bool overlayData = true , bool residual = false, bool drawLegend = true , 
		    bool log = false , bool normalize = false , bool fit = false, char* flavor = "all" );

void printYields( vector<TChain*> chmc , vector<char*> labels , TChain* chdata , TCut sel , TCut weight , bool latex = false );
void initSymbols(bool);
void  printLine(bool);
void deleteHistos();
TLegend *getLegend( vector<TChain*> chmc , vector<char*> labels , bool overlayData, 
		    float x1 = 0.7, float y1 = 0.45 , float x2 = 0.87 , float y2 = 0.94 );

char* pm;         
char* delim;      
char* delimstart; 
char* delimend;   
char* ee;         
char* mm;         
char* em;         

int   width1;
int   width2;
int   linelength;

#endif
