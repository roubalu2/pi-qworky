//
//  Computer.cpp
//  Gomoku
//
//  Created by Thanh Dang on 9/3/15.
//  Copyright (c) 2015 ga. All rights reserved.
//
//  Varianta pocitace od autora viz vyse upravena tak, aby fungovala s nasi hrou

#include <iostream>

#include "Pocitac_hard.h"
#include "Deska.h"


using namespace std;

char playerSymbol = 'X';
char computerSymbol = 'O';


//find next move with the help of alpha-beta
//want to maximize the evaluation function. It's good for the computer
vector<int> Pocitac_hard::tah(Deska & deska){
	vector<int> v = {0,0};
	int M = INT_MIN, x = -1, y = -1;

	for (int i = 0; i <= VelPol-1;i++){
		for (int j = 0; j <= VelPol-1; j++){
			if (deska.nacti(i, j) == '-' && adjacentPlaced(deska, i, j) ){
				int temp = minimaxAlphaBeta (deska, 2, true,INT_MIN, INT_MAX, i, j);
				if (M < temp){
					M = temp;
					x = i;
					y = j;
				}

			}
		}
	}
	if (x == -1 && y == -1){
		x = VelPol/2;
		y = VelPol/2;
	}
	v[0] = x;
	v[1] = y;
	return v;
}




//minimaxAlphaBeta algorithm with alpha-beta to help determine the next move for the computer
//Use evaluation function with depth here.
//higher score is good for computer, lower score is good for player
//isMax = true if the move at (x,y) is of computer
int Pocitac_hard::minimaxAlphaBeta(Deska & deska, int depth, bool isMax, int alpha, int beta, int x , int y){

	char z = isMax ?  playerSymbol  :  computerSymbol;
	deska.hodnota(x,y,z);

	if (deska.vyhra(x,y)){
		deska.hodnota(x,y,'-');
		if (isMax){//computer wins
			return INT_MAX;
		}else {
			return INT_MIN;// player wins, therefore, need to minimize score so computer will not choose this path
		}
	}else if (deska.remiza()){
		deska.hodnota(x,y,'-');
		return 0;
	}
	if (depth == 0){
		int value = 0;
		if (checkVisitedBoard(deska) == true){
			value = getEvaluation(deska); // evaluation of board was already stored
		}else{
			value = evaluation(deska, isMax); //need to compute evaluation of this new board
			insertToHashMap(deska, value); //store evaluation of this new board into memory
		}
		deska.hodnota(x,y,'-');

		//cout <<"evaluation at "<<x <<" "<<y<< " is "<< value <<endl;
		return value;
	}

	//save the X positions of available cells into firstCoord, Y positions of available cells into secondCoord
	vector<int> firstCoord;
	vector<int> secondCoord;
	for (int i = 0; i < VelPol; i++){
		for (int j = 0; j<VelPol; j++){
			if (deska.nacti(i,j) == '-' && adjacentPlaced(deska, i, j)){
				firstCoord.push_back(i);
				secondCoord.push_back(j);
			}
		}
	}

	int len = (int) firstCoord.size();
	if (isMax == true){ // try to minimize because now is player's turn
		int m = INT_MAX;
		for (int i = 0; i < len; i++){
			int temp = minimaxAlphaBeta(deska,depth - 1, false, alpha, beta, firstCoord[i], secondCoord[i]);
			if (m > temp){
				m = temp;
			}
			if (beta > m){
				beta = m;
			 }
			 if (alpha >= beta){
				break;
			 }
		}
		deska.hodnota(x,y,'-');

		return m;
	}else {//try to maximize
		int M = INT_MIN;
		for (int i = 0; i < len; i++){
			int temp = minimaxAlphaBeta(deska, depth - 1, true, alpha, beta, firstCoord[i], secondCoord[i]);
			if (M < temp){
				M = temp;
			}
			if (alpha < M){
				alpha = M;
			 }
			 if (alpha >= beta){
				break;
			 }
		}
		deska.hodnota(x,y,'-');

		return M;
	}
}




int Pocitac_hard::evaluation(Deska & deska, bool isMax){//if isMax is true, computer is about to make the move at (x,y)

	int sum = 0;
	vector<int> computerPattern(VelVyh+1,0);
	vector<int> playerPattern(VelVyh+1,0);

	for (int  i = 0 ; i < VelPol; i++){
		for (int j = 0; j < VelPol ; j++){
			if (deska.nacti(i,j) != '-'){

				//count patterns in columns
				char z = deska.nacti(i,j);
				bool needMax = z == computerSymbol;



				int sameSymbol = 1; // count same symbols in columns
				int k = 1;
				while (i- k >= 0 && deska.nacti(i-k, j)  == z){
					sameSymbol++;
					k++;
				}


				//consider value at i - k later to see if it's blocked or not
				int l = 1;
				while (i + l <= VelPol-1 && deska.nacti(i+l, j) == z){
					sameSymbol++;
					l++;
				}

				if (sameSymbol >= VelVyh){
					if (needMax) computerPattern[VelVyh]++;
					else playerPattern[VelVyh]++;
				}else if (sameSymbol == VelVyh - 1 && (deska.prazdne(i-k,j) || deska.prazdne(i+l,j))){
					if (needMax) computerPattern[VelVyh-1]++;
					else playerPattern[VelVyh-1]++;
				}else if (sameSymbol == VelVyh - 2 && (deska.prazdne(i-k,j) || deska.prazdne(i+l,j))){
					if (needMax) computerPattern[VelVyh-2]++;
					else playerPattern[VelVyh-2]++;
				}else if (sameSymbol == VelVyh - 2 && (deska.prazdne(i-k,j) && deska.prazdne(i+l,j))){
					if (needMax) computerPattern[VelVyh-3]++;
					else playerPattern[VelVyh-3]++;
				}else if (sameSymbol == VelVyh - 3 && deska.prazdne(i-k,j) && deska.prazdne(i+l,j)){
					if (needMax) computerPattern[VelVyh-4]++;
					else playerPattern[VelVyh-4]++;
				}


				//-------------------------------------------------------------------------------
				sameSymbol = 1; // count same symbols in rows
				k = 1;
				while (j - k >= 0 && deska.nacti(i, j-k)  == z){
					sameSymbol++;
					k++;
				}


				//consider value at i - k later to see if it's blocked or not
				l = 1;
				while (j + l <= VelPol-1 && deska.nacti(i, j+l) == z){
					sameSymbol++;
					l++;
				}

				if (sameSymbol >= VelVyh){
					if (needMax) computerPattern[VelVyh]++;
					else playerPattern[VelVyh]++;
				}else if (sameSymbol == VelVyh - 1 && (deska.prazdne(i,j-k) || deska.prazdne(i,j+l))){
					if (needMax) computerPattern[VelVyh-1]++;
					else playerPattern[VelVyh-1]++;
				}else if (sameSymbol == VelVyh - 2 && (deska.prazdne(i,j-k) || deska.prazdne(i,j+l))){
					if (needMax) computerPattern[VelVyh-2]++;
					else playerPattern[VelVyh-2]++;
				}else if (sameSymbol == VelVyh - 2 && (deska.prazdne(i,j-k) && deska.prazdne(i,j+l))){
					if (needMax) computerPattern[VelVyh-3]++;
					else playerPattern[VelVyh-3]++;
				}else if (sameSymbol == VelVyh - 3 && deska.prazdne(i,j-k) && deska.prazdne(i,j+l)){
					if (needMax) computerPattern[VelVyh-4]++;
					else playerPattern[VelVyh-4]++;
				}

				//--------------------------------------------------------------

				sameSymbol = 1;// count same symbols in main diagnol
				k = 1;
				while (i - k >= 0 && j - k >= 0 && deska.nacti(i-k, j- k)  == z){
					sameSymbol++;
					k++;
				}


				//consider value at i - k later to see if it's blocked or not
				l = 1;
				while (i + l <= VelPol-1 && j + l <= VelPol-1 && deska.nacti(i+l, j+l ) == z){
					sameSymbol++;
					l++;
				}

				if (sameSymbol >= VelVyh){
					if (needMax) computerPattern[VelVyh]++;
					else playerPattern[VelVyh]++;
				}else if (sameSymbol == VelVyh - 1 && (deska.prazdne(i-k,j-k) || deska.prazdne(i+l,j+l))){
					if (needMax) computerPattern[VelVyh-1]++;
					else playerPattern[VelVyh-1]++;
				}else if (sameSymbol == VelVyh - 2 && (deska.prazdne(i-k,j-k) || deska.prazdne(i+l,j+l))){
					if (needMax) computerPattern[VelVyh-2]++;
					else playerPattern[VelVyh-2]++;
				}else if (sameSymbol == VelVyh - 2 && (deska.prazdne(i-k,j-k) && deska.prazdne(i+l,j+l))){
					if (needMax) computerPattern[VelVyh-3]++;
					else playerPattern[VelVyh-3]++;
				}else if (sameSymbol == VelVyh - 3 && deska.prazdne(i-k,j-k) && deska.prazdne(i+l,j+l)){
					if (needMax) computerPattern[VelVyh-4]++;
					else playerPattern[VelVyh-4]++;
				}



				//-----------------------------------------------------------------------


				sameSymbol = 1;// count same symbols in reverse diagnols
				k = 1;
				while (i - k >= 0 && j + k <= VelPol-1 && deska.nacti(i-k, j+ k)  == z){
					sameSymbol++;
					k++;
				}


				//consider value at i - k later to see if it's blocked or not
				l = 1;
				while (i + l <= VelPol-1 && j - l >= 0 && deska.nacti(i+l, j-l ) == z){
					sameSymbol++;
					l++;
				}

				if (sameSymbol >= VelVyh){
					if (needMax) computerPattern[VelVyh]++;
					else playerPattern[VelVyh]++;
				}else if (sameSymbol == VelVyh - 1 && (deska.prazdne(i-k,j+k) || deska.prazdne(i+l,j-l))){
					if (needMax) computerPattern[VelVyh-1]++;
					else playerPattern[VelVyh-1]++;
				}else if (sameSymbol == VelVyh - 2 && (deska.prazdne(i-k,j+k) || deska.prazdne(i+l,j-l))){
					if (needMax) computerPattern[VelVyh-2]++;
					else playerPattern[VelVyh-2]++;
				}else if (sameSymbol == VelVyh - 2 && (deska.prazdne(i-k,j+k) && deska.prazdne(i+l,j-l))){
					if (needMax) computerPattern[VelVyh-3]++;
					else playerPattern[VelVyh-3]++;
				}else if (sameSymbol == VelVyh - 3 && deska.prazdne(i-k,j+k) && deska.prazdne(i+l,j-l)){
					if (needMax) computerPattern[VelVyh-4]++;
					else playerPattern[VelVyh-4]++;
				}


			}
		}
	}
	if (computerPattern[VelVyh] > 0) return INT_MAX;
	if (playerPattern[VelVyh] > 0) return INT_MIN;
	int x = 1;
	sum += computerPattern[1];
	sum -= playerPattern[1]*5;
	for (int i = 2 ; i < VelVyh ; i++){
		//cout <<computerPattern[i] << " : "<<playerPattern[i]<<endl;
		x *= 100;
		sum += computerPattern[i] * x;
		sum -= playerPattern[i] * x * 10;
	}
	return sum;
}




bool Pocitac_hard::adjacentPlaced(Deska & deska , int x, int y){

	bool value = false;
	if (deska.nacti(x,y) != '-') return false;
	vector<vector<int>> adjacent = {{-1,-1},{-1,0}, {-1,1},{0,1},{0,-1},{1,-1},{1,0},{1,1}};
	for (auto d:adjacent){

		if (x+d[0] >=0 && y+d[1]>=0 && x+d[0] <= VelPol-1 && y + d[1] <= VelPol-1){
			value = value || (deska.nacti(x+d[0],y+d[1]) != '-');
		}
	}
	return value;
}




//check if the evaluation function of a particular board is already in the memory or not
bool Pocitac_hard::checkVisitedBoard(Deska & deska){
	string s = deska.toString();
	if (hashMap.find(s) != hashMap.end()){
		return true;
	}
	return false;
}


//if the evaluation function of a board is already in the memory, just need to take it out.
// this will save time computing the evaluation function of the board.
int Pocitac_hard::getEvaluation(Deska & deska){
	if (checkVisitedBoard(deska)){
		return hashMap[deska.toString()];
	}
	return -1;
}


//insert values to hash map

void Pocitac_hard::insertToHashMap(Deska & deska, int eval){
	string s = deska.toString();
	hashMap[s] = eval;
	return;
}






