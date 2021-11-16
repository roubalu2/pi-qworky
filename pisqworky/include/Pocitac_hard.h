//
//  Computer.h
//  Gomoku
//
//  Created by Thanh Dang on 9/3/15.
//  Copyright (c) 2015 ga. All rights reserved.
//
//  Varianta pocitace od autora viz vyse upravena tak, aby fungovala s nasi hrou

#ifndef __Gomoku__Computer__
#define __Gomoku__Computer__

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Deska.h"
#include <vector>
#include <unordered_map>

using namespace std;

class Pocitac_hard{
	private:
	unordered_map<string, int> hashMap;

	public:
	vector<int> nextMove(Deska &) ;
	vector<int> tah(Deska &) ;
	int minimax(Deska &, int, bool, int, int) ;
	int minimaxAlphaBeta(Deska &, int, bool, int, int , int , int );
	int evaluation (Deska &, bool);
	bool adjacentPlaced(Deska &, int, int);
	bool checkVisitedBoard(Deska &);
	int getEvaluation(Deska & );
	void insertToHashMap(Deska &, int);
};

#endif /* defined(__Gomoku__Computer__) */
