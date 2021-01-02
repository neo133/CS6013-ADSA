// Assignmet 3 ADSA
// Global DNA Sequence Alignment (Based on Needleman-Wunsch Algorithm) 

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// initialize column 0 and row 0 of score matrix
void initmat(vector<vector<int>>*scrmat, int tarseqlen, int queseqlen, int gap) {

	scrmat->at(0).at(0) = 0; //first cell of matrix is set to 0
	// column 0 of the matrix with gap penalty.
	for(int x = 0; x <= tarseqlen; x++) {
		scrmat->at(x).at(0) = gap * x;
	}	
	// row 0 of the matrix with gap penalty.
	for(int x = 0; x <= queseqlen; x++) {
		scrmat->at(0).at(x) = gap * x;
	}
}

// score matrix computation
void scoremat(vector<vector<int>>*scrmat, int gap, string &tarseq, string &queseq, int mismatch, int tarlen, int qlen) {

	for(int x = 1; x <= tarlen; x++) {
		for(int y = 1; y <= qlen; y++) {
			int penalty=0; //match val
			char chart   = tarseq[ x-1 ];
			char charque   = queseq[ y-1 ];

			if(chart != charque) {
				penalty = mismatch; //mismatch val
			}
			//val from diagonal.
			int diag = penalty + scrmat->at(x-1).at(y-1);
			//val from top.
			int top = gap + scrmat->at(x-1).at(y);
			//val from left.
			int left = gap + scrmat->at(x).at(y-1);

			//final val at x,y is the min of the above 3 values
			scrmat->at(x).at(y) = min(min(diag,top), left);
        }
    }
}

//traceback to 0 in the score matrix from optimal value located at the bottom right corner
void traceback(vector<vector<int>>*scrmat, int gap, string &tarseq, 
					string &queseq, string &optarg, string &optque, int mismatch, int tarlen, int qlen) {

	for ( ; qlen >= 1 && tarlen >= 1; --tarlen) {

		char chart = tarseq[ tarlen-1 ];
		char charque = queseq[ qlen-1 ]; 

		int penalty=0;//match val
		if(chart != charque) {
			penalty = mismatch; //mismatch val
		}	
			//val from diagonal.
		int diag = penalty + scrmat->at(tarlen-1).at(qlen-1); 
			//val from top.
		int top = gap + scrmat->at(tarlen-1).at(qlen);
			//val from left.
		int left = gap + scrmat->at(tarlen).at(qlen-1);

 
		// if current value from diagonal add the character to both optimal seq
		if(diag == scrmat->at(tarlen).at(qlen)) {
			optque  = charque + optque;
			optarg = chart + optarg;
			--qlen;
		}
		// if current value from top insert gap in optimalquery seq
		else if(top == scrmat->at(tarlen).at(qlen)) {
			optque  = '_' + optque;
			optarg = chart + optarg;
		}
		// if current value from left side insert gap in optimaltarget seq
		else {
			optque  = charque + optque;
			optarg = '_' + optarg;
			--qlen;
		}
	}
	
	if(qlen > 0 || tarlen > 0) {
		//if query seq length is greater than target seq add spaces in optimaltarget seq and add character of query seq in optimalquery seq.
		while( (qlen >= 1) && (tarlen < 1) ) {
			optarg = '_' + optarg;
			optque  = queseq[ qlen-1 ] + optque;
			--qlen;
		}
		//if target seq is larger then query seq add spaces in optimalquery seq and add character of target seq in optimaltarget seq.
		while( (tarlen >= 1) && (qlen < 1) ) {
			optque  = '_' + optque;
			optarg = tarseq[ tarlen-1 ] + optarg;			
			--tarlen;
		}
	}
}

//driver code
int main() {

	int gap,mismatch,queseqlen,tarseqlen; 
	string target;
	string query;
	cin>>tarseqlen>>queseqlen; //target sequence and query sequence length
	cin>>gap>>mismatch; //gap cost and mismatch cost
	cin>>target;
	cin>>query;
	int targlen= tarseqlen; int quelen = queseqlen;
	string optarg = ""; string optque  = "";
	vector< vector < int > >scrmat( tarseqlen + 1, vector< int >( quelen + 1 )); //score matrix

	initmat(&scrmat, tarseqlen, quelen, gap); //initialize 0 at first row and col of the score matrix
	scoremat(&scrmat, gap, target, query, mismatch, targlen, quelen); //fill the entries of the score matrix
	traceback(&scrmat, gap, target, query, optarg, optque, mismatch, targlen, quelen); //traceback to 0 from bottom right optimal value to get the sequence
	//the score at right bottom corner in the score matrix is optimal
	cout<<scrmat[tarseqlen][quelen]<<endl;
	cout<<optarg<<endl;
	cout<<optque<<endl;
	
	return 0; 
} 
