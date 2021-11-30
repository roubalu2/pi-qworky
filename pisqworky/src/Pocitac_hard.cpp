#include <iostream>

#include "Pocitac_hard.h"
#include "Deska.h"


using namespace std;

char playerSymbol = 'X';
char computerSymbol = 'O';



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



int Pocitac_hard::minimaxAlphaBeta(Deska & deska, int depth, bool isMax, int alpha, int beta, int x , int y){

	char z = isMax ?  playerSymbol  :  computerSymbol;
	deska.hodnota(x,y,z);

	if (deska.vyhra(x,y)){
		deska.hodnota(x,y,'-');
		if (isMax){
			return INT_MAX;
		}else {
			return INT_MIN;
		}
	}else if (deska.remiza()){
		deska.hodnota(x,y,'-');
		return 0;
	}
	if (depth == 0){
		int value = 0;
		if (checkVisitedBoard(deska) == true){
			value = getEvaluation(deska);
		}else{
			value = evaluation(deska, isMax);
			insertToHashMap(deska, value);
		}
		deska.hodnota(x,y,'-');


		return value;
	}


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
	if (isMax == true){
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
	}else {
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




int Pocitac_hard::evaluation(Deska & deska, bool isMax){

	int sum = 0;
	vector<int> computerPattern(VelVyh+1,0);
	vector<int> playerPattern(VelVyh+1,0);

	for (int  i = 0 ; i < VelPol; i++){
		for (int j = 0; j < VelPol ; j++){
			if (deska.nacti(i,j) != '-'){


				char z = deska.nacti(i,j);
				bool needMax = z == computerSymbol;



				int sameSymbol = 1;
				int k = 1;
				while (i- k >= 0 && deska.nacti(i-k, j)  == z){
					sameSymbol++;
					k++;
				}



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
				sameSymbol = 1;
				k = 1;
				while (j - k >= 0 && deska.nacti(i, j-k)  == z){
					sameSymbol++;
					k++;
				}



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

				sameSymbol = 1;
				k = 1;
				while (i - k >= 0 && j - k >= 0 && deska.nacti(i-k, j- k)  == z){
					sameSymbol++;
					k++;
				}



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


				sameSymbol = 1;
				k = 1;
				while (i - k >= 0 && j + k <= VelPol-1 && deska.nacti(i-k, j+ k)  == z){
					sameSymbol++;
					k++;
				}



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





bool Pocitac_hard::checkVisitedBoard(Deska & deska){
	string s = deska.toString();
	if (hashMap.find(s) != hashMap.end()){
		return true;
	}
	return false;
}


int Pocitac_hard::getEvaluation(Deska & deska){
	if (checkVisitedBoard(deska)){
		return hashMap[deska.toString()];
	}
	return -1;
}



void Pocitac_hard::insertToHashMap(Deska & deska, int eval){
	string s = deska.toString();
	hashMap[s] = eval;
	return;
}






