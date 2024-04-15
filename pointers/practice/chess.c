#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char board[][8] = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
                  {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                  {'0', '0', '0', '0', '0', '0', '0', '0'},
                  {'0', '0', '0', '0', '0', '0', '0', '0'},
                  {'0', '0', '0', '0', '0', '0', '0', '0'},
                  {'0', '0', '0', '0', '0', '0', '0', '0'},
                  {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                  {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
int king[2];
int bKing[] = {0, 4};
int wKing[] = {7, 4};
int checker[2];
int check = 0;
int checkmate = 0;
int draw = 0;
int pasa;
int passant[2];
int wshort = 1;
int wlong = 1;
int bshort = 0;
int blong = 0;
int promoted[2];
int turn = 1;
int calcresult = 0;

int **pinned(int *a, int x, int y, int (*func)(int)){
    //vertical
    if(x > 0 && x < 7){
        int flag = 0;
        int it = 1;
        while(x+it < 7 && board[x+it][y] == '0'){
            it++;
        }
        int piece = tolower(board[x+it][y]);
        if(func(board[x+it][y]) == 0 && piece == 'k'){
            flag = 1;
        }else if(func(board[x+it][y]) && (piece == 'r' || piece == 'q')){
            flag = 2;
        }
        if(flag){
            int it2 = 1;
            while(x-it2 > 0 && board[x-it2][y] == '0'){
                it2++;
            }
            piece = tolower(board[x-it2][y]);
            if(flag == 1 && func(board[x-it2][y]) && (piece == 'r' || piece == 'q')){
                if(!check){
                    piece = tolower(board[x][y]);
                    if(piece == 'r' || piece == 'q'){
                        int **movements = malloc(sizeof(int*)*it2+it-1);
                        for(int i = 0; i < it2; i++){
                            movements[i] = malloc(sizeof(int)*2);
                            movements[i][0] = x-i-1;
                            movements[i][1] = y;
                        }
                        for(int i = 0; i < it-1; i++){
                            movements[i+it2] = malloc(sizeof(int)*2);
                            movements[i+it2][0] = x+i+1;
                            movements[i+it2][1] = y;
                        }
                        *a = it2+it-1;
                        return movements;
                    }else if(board[x][y] == 'P'){
                        if(it2 > 2 && x == 6){
                            int **movements = malloc(sizeof(int*)*2);
                            for(int i = 0; i < 2; i++){
                                movements[i] = malloc(sizeof(int)*2);
                                movements[i][0] = x-i-1;
                                movements[i][1] = y;
                            }
                            *a = 2;
                            return movements;
                        }else if(it2 > 1){
                            int **movements = malloc(sizeof(int*));
                            movements[0] = malloc(sizeof(int)*2);
                            movements[0][0] = x-1;
                            movements[0][1] = y;
                            *a = 1;
                            return movements;
                        }
                    }else if(board[x][y] == 'p'){
                        if(it > 2 && x == 1){
                            int **movements = malloc(sizeof(int*)*2);
                            for(int i = 0; i < 2; i++){
                                movements[i] = malloc(sizeof(int)*2);
                                movements[i][0] = x+i+1;
                                movements[i][1] = y;
                            }
                            *a = 2;
                            return movements;
                        }else if(it > 1){
                            int **movements = malloc(sizeof(int*));
                            movements[0] = malloc(sizeof(int)*2);
                            movements[0][0] = x+1;
                            movements[0][1] = y;
                            *a = 1;
                            return movements;
                        }
                    }
                }
                *a = -1;
                return NULL;
            }else if(flag == 2 && func(board[x-it2][y]) == 0 && piece == 'k'){
                if(!check){
                    piece = tolower(board[x][y]);
                    if(piece == 'r' || piece == 'q'){
                        int **movements = malloc(sizeof(int*)*it+it2-1);
                        for(int i = 0; i < it; i++){
                            movements[i] = malloc(sizeof(int)*2);
                            movements[i][0] = x+i+1;
                            movements[i][1] = y;
                        }
                        for(int i = 0; i < it2-1; i++){
                            movements[i+it] = malloc(sizeof(int)*2);
                            movements[i+it][0] = x-i-1;
                            movements[i+it][1] = y;
                        }
                        *a = it+it2-1;
                        return movements;
                    }else if(board[x][y] == 'p'){
                        if(it > 2 && x == 1){
                            int **movements = malloc(sizeof(int*)*2);
                            for(int i = 0; i < 2; i++){
                                movements[i] = malloc(sizeof(int)*2);
                                movements[i][0] = x+i+1;
                                movements[i][1] = y;
                            }
                            *a = 2;
                            return movements;
                        }else if(it > 1){
                            int **movements = malloc(sizeof(int*));
                            movements[0] = malloc(sizeof(int)*2);
                            movements[0][0] = x+1;
                            movements[0][1] = y;
                            *a = 1;
                            return movements;
                        }
                    }else if(board[x][y] == 'P'){
                        if(it2 > 2 && x == 6){
                            int **movements = malloc(sizeof(int*)*2);
                            for(int i = 0; i < 2; i++){
                                movements[i] = malloc(sizeof(int)*2);
                                movements[i][0] = x-i-1;
                                movements[i][1] = y;
                            }
                            *a = 2;
                            return movements;
                        }else if(it2 > 1){
                            int **movements = malloc(sizeof(int*));
                            movements[0] = malloc(sizeof(int)*2);
                            movements[0][0] = x-1;
                            movements[0][1] = y;
                            *a = 1;
                            return movements;
                        }
                    }
                }
                *a = -1;
                return NULL;
            }
        }
    }
    //horizontal
    if(y > 0 && y < 7){
        int flag = 0;
        int it = 1;
        while(y+it < 7 && board[x][y+it] == '0'){
            it++;
        }
        int piece = tolower(board[x][y+it]);
        if(func(board[x][y+it]) == 0 && piece == 'k'){
            flag = 1;
        }else if(func(board[x][y+it]) && (piece == 'r' || piece == 'q')){
            flag = 2;
        }
        if(flag){
            int it2 = 1;
            while(y-it2 > 0 && board[x][y-it2] == '0'){
                it2++;
            }
            piece = tolower(board[x][y-it2]);
            if(flag == 1 && func(board[x][y-it2]) && (piece == 'r' || piece == 'q')){
                if(!check){
                    piece = tolower(board[x][y]);
                    if(piece == 'r' || piece == 'q'){
                        int **movements = malloc(sizeof(int*)*it2+it-1);
                        for(int i = 0; i < it2; i++){
                            movements[i] = malloc(sizeof(int)*2);
                            movements[i][0] = x;
                            movements[i][1] = y-i-1;
                        }
                        for(int i = 0; i < it-1; i++){
                            movements[i+it2] = malloc(sizeof(int)*2);
                            movements[i+it2][0] = x;
                            movements[i+it2][1] = y+i+1;
                        }
                        *a = it2+it-1;
                        return movements;
                    }
                }
                *a = -1;
                return NULL;
            }else if(flag == 2 && func(board[x][y-it2]) == 0 && piece == 'k'){
                if(!check){
                    piece = tolower(board[x][y]);
                    if(piece == 'r' || piece == 'q'){
                        int **movements = malloc(sizeof(int*)*it+it2-1);
                        for(int i = 0; i < it; i++){
                            movements[i] = malloc(sizeof(int)*2);
                            movements[i][0] = x;
                            movements[i][1] = y+i+1;
                        }
                        for(int i = 0; i < it2-1; i++){
                            movements[i+it] = malloc(sizeof(int)*2);
                            movements[i+it][0] = x;
                            movements[i+it][1] = y-i-1;
                        }
                        *a = it+it2-1;
                        return movements;
                    }
                }
                *a = -1;
                return NULL;
            }
        }
    }
    if(x < 7 && y < 7 && x > 0 && y > 0){
        //positive slope
        int flag = 0;
        int it = 1;
        while(x+it < 7 && y+it < 7 && board[x+it][y+it] == '0'){
            it++;
        }
        int piece = tolower(board[x+it][y+it]);
        if(func(board[x+it][y+it]) == 0 && piece == 'k'){
            flag = 1;
        }else if(func(board[x+it][y+it]) && (piece == 'b' || piece == 'q')){
            flag = 2;
        }
        if(flag){
            int it2 = 1;
            while(x-it2 > 0 && y-it2 > 0 && board[x-it2][y-it2] == '0'){
                it2++;
            }
            int piece = tolower(board[x-it2][y-it2]);
            if(flag == 1 && func(board[x-it2][y-it2]) && (piece == 'b' || piece == 'q')){
                if(!check){
                    piece = tolower(board[x][y]);
                    if(piece == 'b'|| piece == 'q'){
                        int **movements = malloc(sizeof(int*)*it2+it-1);
                        for(int i = 0; i < it2; i++){
                            movements[i] = malloc(sizeof(int)*2);
                            movements[i][0] = x-i-1;
                            movements[i][1] = y-i-1;
                        }
                        for(int i = 0; i < it-1; i++){
                            movements[i+it2] = malloc(sizeof(int)*2);
                            movements[i+it2][0] = x+i+1;
                            movements[i+it2][1] = y+i+1;
                        }
                        *a = it2+it-1;
                        return movements;
                    }else if(it2 == 1 && board[x][y] == 'P'){
                        int **movements = malloc(sizeof(int*));
                        movements[0] = malloc(sizeof(int)*2);
                        movements[0][0] = x-it2;
                        movements[0][1] = y-it2;
                        *a = it2;
                        return movements;
                    }
                }
                *a = -1;
                return NULL;
            }else if(flag == 2 && func(board[x-it2][y-it2]) == 0 && piece == 'k'){
                if(!check){
                    piece = tolower(board[x][y]);
                    if(piece == 'b' || piece == 'q'){
                        int **movements = malloc(sizeof(int*)*it+it2-1);
                        for(int i = 0; i < it; i++){
                            movements[i] = malloc(sizeof(int)*2);
                            movements[i][0] = x+i+1;
                            movements[i][1] = y+i+1;
                        }
                        for(int i = 0; i < it2-1; i++){
                            movements[i+it] = malloc(sizeof(int)*2);
                            movements[i+it][0] = x-i-1;
                            movements[i+it][1] = y-i-1;
                        }
                        *a = it;
                        return movements;
                    }else if(it == 1 && board[x][y] == 'p'){
                        int **movements  = malloc(sizeof(int*));
                        movements[0] = malloc(sizeof(int)*2);
                        movements[0][0] = x+it;
                        movements[0][1] = y+it;
                        *a = it;
                        return movements;
                    }
                }
                *a = -1;
                return NULL;
            }
        }else{
            //negative slope
            flag = 0;
            it = 1;
            while(x+it < 7 && y-it >0 && board[x+it][y-it] == '0'){
                it++;
            }
            piece = tolower(board[x+it][y-it]);
            if(func(board[x+it][y-it]) == 0 && piece == 'k'){
                flag = 1;
            }else if(func(board[x+it][y-it]) && (piece == 'b' || piece == 'q')){
                flag = 2;
            }
            if(flag){
                int it2 = 1;
                while(x-it2 > 0 && y+it2 < 7 && board[x-it2][y+it2] == '0'){
                    it2++;
                }
                piece = tolower(board[x-it2][y+it2]);
                if(flag == 1 && func(board[x-it2][y+it2]) && (piece == 'b' || piece == 'q')){
                    if(!check){
                        piece = tolower(board[x][y]);
                        if(piece == 'b'|| piece == 'q'){
                            int **movements = malloc(sizeof(int*)*it2+it-1);
                            for(int i = 0; i < it2; i++){
                                movements[i] = malloc(sizeof(int)*2);
                                movements[i][0] = x-i-1;
                                movements[i][1] = y+i+1;
                            }
                            for(int i = 0; i < it-1; i++){
                                movements[i] = malloc(sizeof(int)*2);
                                movements[i][0] = x+i+1;
                                movements[i][1] = y-i-1;
                            }
                            *a = it2+it-1;
                            return movements;
                        }else if(it2 == 1 && board[x][y] == 'P'){
                            int **movements = malloc(sizeof(int*));
                            movements[0] = malloc(sizeof(int)*2);
                            movements[0][0] = x-it2;
                            movements[0][1] = y+it2;
                            *a = it2;
                            return movements;
                        }
                    }
                    *a = -1;
                    return NULL;
                }else if(flag == 2 && func(board[x-it2][y+it2]) == 0 && piece == 'k'){
                    if(!check){
                        piece = tolower(board[x][y]);
                        if(piece == 'b'|| piece == 'q'){
                            int **movements = malloc(sizeof(int*)*it+it2-1);
                            for(int i = 0; i < it; i++){
                                movements[i] = malloc(sizeof(int)*2);
                                movements[i][0] = x+i+1;
                                movements[i][1] = y-i-1;
                            }
                            for(int i = 0; i < it2-1; i++){
                                movements[i+it] = malloc(sizeof(int)*2);
                                movements[i][0] = x-i-1;
                                movements[i][1] = y+i+1;
                            }
                            *a = it+it2-1;
                            return movements;
                        }else if(it == 1 && board[x][y] == 'p'){
                            int **movements = malloc(sizeof(int*));
                            movements[0] = malloc(sizeof(int)*2);
                            movements[0][0] = x+it;
                            movements[0][1] = y-it;
                            *a = it;
                            return movements;
                        }
                    }
                    *a = -1;
                    return NULL;
                }
            }
        }
    }
    *a = 0;
    return NULL;
}

int **rescue(int *a, int x, int y, int **moves){
    int blockable[7][2];
    int count = 0;
    if(king[0] == checker[0]){
        if(king[1] > checker[1]){
            for(int i = 0; i < king[1] - checker[1]; i++){
                blockable[i][0] = king[0];
                blockable[i][1] = king[1]-i-1;
                count++;
            }
        }else{
            for(int i = 0; i < checker[1] - king[1]; i++){
                blockable[i][0] = king[0];
                blockable[i][1] = king[1]+i+1;
                count++;
            }
        }
    }else if(king[1] == checker[1]){
        if(king[0] > checker[0]){
            for(int i = 0; i < king[0] - checker[0]; i++){
                blockable[i][0] = king[0]-i-1;
                blockable[i][1] = king[1];
                count++;
            }
        }else{
            for(int i = 0; i < checker[0] - king[0]; i++){
                blockable[i][0] = king[0]+i+1;
                blockable[i][1] = king[1];
                count++;
            }
        }
    }else if(king[0]+king[1] == checker[0]+checker[1]){
        if(king[0] > checker[0]){
            for(int i = 0; i < king[0]-checker[0]; i++){
                blockable[i][0] = king[0]-i-1;
                blockable[i][1] = king[1]+i+1;
                count++;
            }
        }else{
            for(int i = 0; i < checker[0]-king[0]; i++){
                blockable[i][0] = king[0]+i+1;
                blockable[i][1] = king[1]-i-1;
                count++;
            }
        }
    }else if(king[0]-king[1] == checker[0]-checker[1]){
        if(king[0] > checker[0]){
            for(int i = 0; i < king[0]-checker[0]; i++){
                blockable[i][0] = king[0]-i-1;
                blockable[i][1] = king[1]-i-1;
                count++;
            }
        }else{
            for(int i = 0; i < checker[0]-king[0]; i++){
                blockable[i][0] = king[0]+i+1;
                blockable[i][1] = king[1]+i+1;
                count++;
            }
        }
    }else{
        blockable[0][0] = checker[0];
        blockable[0][1] = checker[1];
        count++;
    }
    int conteo = 0;
    int realMoves[2][2];
    for(int i = 0; i < count; i++){
        for(int j = 0; j < *a; j++){
            if(blockable[i][0] == moves[j][0] && blockable[i][1] == moves[j][1]){
                realMoves[conteo][0] = blockable[i][0];
                realMoves[conteo][1] = blockable[i][1];
                conteo++;
            }
        }
    }
    int **movements = malloc(sizeof(int*)*conteo);
    for(int i = 0; i < conteo; i++){
        movements[i] = malloc(sizeof(int)*2);
        movements[i][0] = realMoves[i][0];
        movements[i][1] = realMoves[i][1];
    }
    free(moves);
    *a = conteo;
    if(*a == 0){
        free(movements);
        return NULL;
    }
    return movements;
}

int **bpawn(int *a, int x, int y){
    if(check > 1){
        *a = 0;
        return NULL;
    }
    int **moves = pinned(a, x, y, isupper);
    if(*a > 0){
        return moves;
    }else if(*a == -1){
        *a = 0;
        return moves;
    }
    int draft[4][2];
    int count = 0;
    if(board[x+1][y] == '0'){
        draft[count][0] = x+1;
        draft[count][1] = y;
        count++;
        if(x == 1 && board[x+2][y] == '0'){
            draft[count][0] = x+2;
            draft[count][1] = y;
            count++;
        }
    }
    if(isupper(board[x+1][y-1])){
        draft[count][0] = x+1;
        draft[count][1] = y-1;
        count++;
    }
    if(isupper(board[x+1][y+1])){
        draft[count][0] = x+1;
        draft[count][1] = y+1;
        count++;
    }
    if(pasa && passant[0] == x && (passant[1] == y+1 || passant[1] == y-1)){
        draft[count][0] = x+1;
        draft[count][1] = passant[1];
        count++;
    }
    int **movements = malloc(sizeof(int*)*count);
    for(int i = 0; i < count; i++){
        movements[i] = malloc(sizeof(int)*2);
    }
    for(int i = 0; i < count; i++){
        movements[i][0] = draft[i][0];
        movements[i][1] = draft[i][1];
    }
    *a = count;
    if(*a == 0){
        free(movements);
        return NULL;
    }
    if(check == 1){
        return rescue(a, x, y, movements);
    }
    return movements;
}

int **wpawn(int *a, int x, int y){
    if(check > 1){
        *a = 0;
        return NULL;
    }
    int **moves = pinned(a, x, y, islower);
    if(*a > 0){
        return moves;
    }else if(*a == -1){
        *a = 0;
        return moves;
    }
    int draft[4][2];
    int count = 0;
    if(board[x-1][y] == '0'){
        draft[count][0] = x-1;
        draft[count][1] = y;
        count++;
        if(x == 6 && board[x-2][y] == '0'){
            draft[count][0] = x-2;
            draft[count][1] = y;
            count++;
        }
    }
    if(islower(board[x-1][y-1])){
        draft[count][0] = x-1;
        draft[count][1] = y-1;
        count++;
    }
    if(islower(board[x-1][y+1])){
        draft[count][0] = x-1;
        draft[count][1] = y+1;
        count++;
    }
    if(pasa && passant[0] == x && (passant[1] == y+1 || passant[1] == y-1)){
        draft[count][0] = x-1;
        draft[count][1] = passant[1];
        count++;
    }
    int **movements = malloc(sizeof(int*)*count);
    for(int i = 0; i < count; i++){
        movements[i] = malloc(sizeof(int)*2);
    }
    for(int i = 0; i < count; i++){
        movements[i][0] = draft[i][0];
        movements[i][1] = draft[i][1];
    }
    *a = count;
    if(*a == 0){
        free(movements);
        return NULL;
    }
    if(check == 1){
        return rescue(a, x, y, movements);
    }
    return movements;
}

int **rookMoves(int *a, int x, int y, int (*func)(int)){
    int draft[14][2];
    int count = 0;
    if(x < 7){
        int it = 1;
        while(x+it < 7 && board[x+it][y] == '0'){
            draft[count][0] = x+it;
            draft[count][1] = y;
            count++;
            it++;
        }
        if(func(board[x+it][y]) || board[x+it][y] == '0'){
            draft[count][0] = x+it;
            draft[count][1] = y;
            count++;
        }
    }if(x > 0){
        int it = 1;
        while(x-it>0 && board[x-it][y] == '0'){
            draft[count][0] = x-it;
            draft[count][1] = y;
            count++;
            it++;
        }
        if(func(board[x-it][y]) || board[x-it][y] == '0'){
            draft[count][0] = x-it;
            draft[count][1] = y;
            count++;
        }
    }if(y < 7){
        int it = 1;
        while(y+it<7 && board[x][y+it] == '0'){
            draft[count][0] = x;
            draft[count][1] = y+it;
            count++;
            it++;
        }
        if(func(board[x][y+it]) || board[x][y+it] == '0'){
            draft[count][0] = x;
            draft[count][1] = y+it;
            count++;
        }
    }if(y > 0){
        int it = 1;
        while(y-it>0 && board[x][y-it] == '0'){
            draft[count][0] = x;
            draft[count][1] = y-it;
            count++;
            it++;
        }
        if(func(board[x][y-it]) || board[x][y-it] == '0'){
            draft[count][0] = x;
            draft[count][1] = y-it;
            count++;
        }
    }
    int **movements = malloc(sizeof(int*)*count);
    for(int i = 0; i < count; i++){
        movements[i] = malloc(sizeof(int)*2);
    }
    for(int i = 0; i < count; i++){
        movements[i][0] = draft[i][0];
        movements[i][1] = draft[i][1];
    }
    *a = count;
    return movements;
}

int **rook(int *a, int x, int y, int (*func)(int)){
    if(check > 1){
        *a = 0;
        return NULL;
    }
    int **moves = pinned(a, x, y, func);
    if(*a > 0){
        return moves;
    }else if(*a == -1){
        *a = 0;
        return moves;
    }
    int ** movements = rookMoves(a, x, y, func);
    if(*a == 0){
        free(movements);
        return NULL;
    }
    if(check == 1){
        return rescue(a, x, y, movements);
    }
    return movements;
}

int **knightMoves(int *a, int x, int y, int (*func)(int)){
    int draft[8][2];
    int count = 0;
    int r[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int c[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    for(int i = 0; i < sizeof(r)/sizeof(int); i++){
        if(x+r[i] >= 0 && y+c[i] >= 0 && x+r[i] <= 7 && y+c[i] <= 7){
            if(func(board[x+r[i]][y+c[i]]) || board[x+r[i]][y+c[i]] == '0'){
                draft[count][0] = x+r[i];
                draft[count][1] = y+c[i];
                count++;
            }
        }
    }
    int **movements = malloc(sizeof(int*)*count);
    for(int i = 0; i < count; i++){
        movements[i] = malloc(sizeof(int)*2);
    }
    for(int i = 0; i < count; i++){
        movements[i][0] = draft[i][0];
        movements[i][1] = draft[i][1];
    }
    *a = count;
    return movements;
}

int **knight(int *a, int x, int y, int (*func)(int)){
    if(check > 1){
        *a = 0;
        return NULL;
    }
    int **moves = pinned(a, x, y, func);
    if(*a > 0){
        return moves;
    }else if(*a == -1){
        *a = 0;
        return moves;
    }
    int **movements = knightMoves(a, x, y, func);
    if(*a == 0){
        free(movements);
        return NULL;
    }
    if(check == 1){
        moves = rescue(a, x, y, movements);
        return moves;
    }
    return movements;
}

int **bishopMoves(int *a, int x, int y, int (*func)(int)){
    int draft[13][2];
    int count = 0;
    if(x < 7 && y < 7){
        int it = 1;
        while(x+it < 7 && y+it < 7 && board[x+it][y+it] == '0'){
            draft[count][0] = x+it;
            draft[count][1] = y+it;
            count++;
            it++;
        }
        if(func(board[x+it][y+it]) || board[x+it][y+it] == '0'){
            draft[count][0] = x+it;
            draft[count][1] = y+it;
            count++;
        }
    }
    if(x > 0 && y > 0){
        int it = 1;
        while(x-it > 0 && y-it > 0 && board[x-it][y-it] == '0'){
            draft[count][0] = x-it;
            draft[count][1] = y-it;
            count++;
            it++;
        }
        if(func(board[x-it][y-it]) || board[x-it][y-it] == '0'){
            draft[count][0] = x-it;
            draft[count][1] = y-it;
            count++;
        }
    }
    if(x < 7 && y > 0){
        int it = 1;
        while(x+it < 7 && y-it > 0 && board[x+it][y-it] == '0'){
            draft[count][0] = x+it;
            draft[count][1] = y-it;
            count++;
            it++;
        }
        if(func(board[x+it][y-it]) || board[x+it][y-it] == '0'){
            draft[count][0] = x+it;
            draft[count][1] = y-it;
            count++;
        }
    }
    if(x > 0 && y < 7){
        int it = 1;
        while(x-it > 0 && y+it < 7 && board[x-it][y+it] == '0'){
            draft[count][0] = x-it;
            draft[count][1] = y+it;
            count++;
            it++;
        }
        if(func(board[x-it][y+it]) || board[x-it][y+it] == '0'){
            draft[count][0] = x-it;
            draft[count][1] = y+it;
            count++;
        }
    }
    int **movements = malloc(sizeof(int*)*count);
    for(int i = 0; i < count; i++){
        movements[i] = malloc(sizeof(int)*2);
    }
    for(int i = 0; i < count; i++){
        movements[i][0] = draft[i][0];
        movements[i][1] = draft[i][1];
    }
    *a = count;
    return movements;
}

int **bishop(int *a, int x, int y, int (*func)(int)){
    if(check > 1){
        *a = 0;
        return NULL;
    }
    int **moves = pinned(a, x, y, func);
    if(*a > 0){
        return moves;
    }else if(*a == -1){
        *a = 0;
        return moves;
    }
    int **movements = bishopMoves(a, x, y, func);
    if(*a == 0){
        free(movements);
        return NULL;
    }
    if(check == 1){
        return rescue(a, x, y, movements);
    }
    return movements;
}

int **queeMoves(int *a, int x, int y, int (*func)(int)){
    int b;
    int **roo = rook(&b, x, y, func);
    int c;
    int **bisho = bishop(&c, x, y, func);
    *a = b+c;
    int **movements = malloc(sizeof(int*)*(*a));
    for(int i = 0; i < *a; i++){
        movements[i] = malloc(sizeof(int)*2);
    }
    for(int i = 0; i < b; i++){
        movements[i][0] = roo[i][0];
        movements[i][1] = roo[i][1];
    }
    for(int i = 0; i < c; i++){
        movements[i+b][0] = bisho[i][0];
        movements[i+b][1] = bisho[i][1];
    }
    free(roo);
    free(bisho);
    if(*a == 0){
        free(movements);
        return NULL;
    }
    return movements;
}

int **queen(int *a, int x, int y, int (*func)(int)){
    if(check > 1){
        *a = 0;
        return NULL;
    }
    int **moves = pinned(a, x, y, func);
    if(*a > 0){
        return moves;
    }else if(*a == -1){
        *a = 0;
        return moves;
    }
    int **movements = queeMoves(a, x, y, func);
    if(check == 1){
        return rescue(a, x, y, movements);
    }
    return movements;
}

int isKnight(int x, int y, int (*func2)(int)){
    int r[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int c[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    for(int i = 0; i < sizeof(r)/sizeof(int); i++){
        if(x+r[i] >= 0 && y+c[i] >= 0 && x+r[i] <= 7 && y+c[i] <= 7){
            if(board[x+r[i]][y+c[i]] == func2('n')){
                return 1;
            }
        }
    }
    return 0;
}

int discoverPosSlope(int x, int y, int (*func)(int), int *kin){
    int it = 1;
    if(kin[0] > x){
        while(kin[0]-it > 0 && kin[1]-it > 0 && board[kin[0]-it][kin[1]-it] == '0'){
            it++;
        }
        if(board[kin[0]-it][kin[1]-it] == func('b') || board[kin[0]-it][kin[1]-it] == func('q')){
            return 1;
        }
    }else{
        while(kin[0]+it < 7 && kin[1]+it < 7 && board[kin[0]+it][kin[1]+it] == '0'){
            it++;
        }
        if(board[kin[0]+it][kin[1]+it] == func('b') || board[kin[0]+it][kin[1]+it] == func('q')){
            return 1;
        }
    }
    return 0;
}

int discoverNegSlope(int x, int y, int (*func)(int), int *kin){
    int it = 1;
    if(kin[0] > x){
        while(kin[0]-it > 0 && kin[1]+it < 7 && board[kin[0]-it][kin[1]+it] == '0'){
            it++;
        }
        if(board[kin[0]-it][kin[1]+it] == func('b') || board[kin[0]-it][kin[1]+it] == func('q')){
            return 1;
        }
    }else{
        while(kin[0]+it < 7 && kin[1]-it > 0 && board[kin[0]-it][kin[1]+it] == '0'){
            it++;
        }
        if(board[kin[0]+it][kin[1]-it] == func('b') || board[kin[0]-it][kin[1]+it] == func('q')){
            return 1;
        }
    }
    return 0;
}

int discoverVertical(int x, int y, int (*func)(int), int *kin){
    int it = 1;
    if(kin[0] > x){
        while(kin[0]-it > 0 && board[kin[0]-it][kin[1]] == '0'){
            it++;
        }
        if(board[kin[0]-it][kin[1]] == func('r') || board[kin[0]-it][kin[1]] == func('q')){
            return 1;
        }
    }else{
        while(kin[0]+it < 7 && board[kin[0]+it][kin[1]] == '0'){
            it++;
        }
        if(board[kin[0]+it][kin[1]] == func('r') || board[kin[0]+it][kin[1]] == func('q')){
            return 1;
        }
    }
    return 0;
}

int discoverHorizontal(int x, int y, int (*func)(int), int *kin){
    int it = 1;
    if(kin[1] > y){
        while(kin[1]-it > 0 && board[kin[0]][kin[1]-it] == '0'){
            it++;
        }
        if(board[kin[0]][kin[1]-it] == func('r') || board[kin[0]][kin[1]-it] == func('q')){
            return 1;
        }
    }else{
        while(kin[1]+it < 7 && board[kin[0]][kin[1]+it] == '0'){
            it++;
        }
        if(board[kin[0]][kin[1]+it] == func('r') || board[kin[0]][kin[1]+it] == func('q')){
            return 1;
        }
    }
    return 0;
}

int canMove(int x, int y, int (*func)(int)){
    int kin[2] = {x, y};
    if(y+1 > 7 || board[x][y+1] != func('k')){
        if(y+1 > 7 || !discoverHorizontal(x, y+1, func, kin)){
            if(y-1 < 0 || board[x][y-1] != func('k')){
                if(y-1 < 0 || !discoverHorizontal(x, y-1, func, kin)){
                    if(x+1 > 7 || board[x+1][y] != func('k')){
                        if(x+1 > 7 || !discoverVertical(x+1, y, func, kin)){
                            if(x-1 < 0 || board[x-1][y] != func('k')){
                                if(x-1 < 0 || !discoverVertical(x-1, y, func, kin)){
                                    if(x+1 > 7 || y+1 > 7 || board[x+1][y+1] != func('k') && board[x+1][y+1] != 'P'){
                                        if(x+1 > 7 || y+1 > 7 || !discoverPosSlope(x+1, y+1, func, kin)){
                                            if(x-1 < 0 || y-1 < 0 || board[x-1][y-1] != func('k') && board[x-1][y-1] != 'p'){
                                                if(x-1 < 0 || y-1 < 0 || !discoverPosSlope(x-1, y-1, func, kin)){
                                                    if(x+1 > 7 || y-1 < 0 || board[x+1][y-1] != func('k') && board[x+1][y-1] != 'P'){
                                                        if(x+1 > 7 || y-1 < 0 || !discoverNegSlope(x+1, y-1, func, kin)){
                                                            if(x-1 < 0 || y+1 > 7 || board[x-1][y+1] != func('k') && board[x-1][y+1] != 'p'){
                                                                if(x-1 < 0 || y+1 > 7 || !discoverNegSlope(x-1, y+1, func, kin)){
                                                                    if(!isKnight(x, y, func)){
                                                                        return 1;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int **kingg(int *a, int x, int y, int (*func)(int)){
    int r[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int c[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int posMovs[8][2];
    int count = 0;
    for(int i = 0; i < 8; i++){
        if(x+r[i] >= 0 && y+c[i] >= 0 && x+r[i] <= 7 && y+c[i] <= 7){
            if(func(board[x+r[i]][y+c[i]]) || board[x+r[i]][y+c[i]] == '0'){
                posMovs[count][0] = x+r[i];
                posMovs[count][1] = y+c[i];
                count++;
            }
        }
    }
    int count2 = 0;
    int (*func2)(int);
    if(func == islower){
        func2 = tolower;
    }else{
        func2 = toupper;
    }
    char temp = board[x][y];
    board[x][y] = '0';
    for(int i = 0; i < count; i++){
        if(canMove(posMovs[i][0], posMovs[i][1], func2)){
            posMovs[count2][0] = posMovs[i][0];
            posMovs[count2][1] = posMovs[i][1];
            count2++;
        }
    }
    board[x][y] = temp;
    int scastle, lcastle;
    if(x == wKing[0] && y == wKing[1]){
        scastle = wshort;
        lcastle = wlong;
    }else{
        scastle = bshort;
        lcastle = blong;
    }
    if(!check){
        if(scastle == 1 && board[x][y+1] == '0' && board[x][y+2] == '0'){
            for(int i = 0; i < count2; i++){
                if(posMovs[i][0] == x && posMovs[i][1] == y+1){
                    if(canMove(x, y+2, func2)){
                        posMovs[count2][0] = x;
                        posMovs[count2][1] = y+2;
                        count2++;
                    }
                    break;
                }
            }
        }
        if(lcastle == 1 && board[x][y-1] == '0' && board[x][y-2] == '0' && board[x][y-3] == '0'){
            for(int i = 0; i < count2; i++){
                if(posMovs[i][0] == x && posMovs[i][1] == y-1){
                    if(canMove(x, y-2, func2) && canMove(x, y-3, func2)){
                        posMovs[count2][0] = x;
                        posMovs[count2][1] = y-2;
                        count2++;
                    }
                    break;
                }
            }
        }
    }
    int **movements = malloc(sizeof(int*)*count2);
    for(int i = 0; i < count2; i++){
        movements[i] = malloc(sizeof(int)*2);
        movements[i][0] = posMovs[i][0];
        movements[i][1] = posMovs[i][1];
    }
    *a = count2;
    if(*a > 0){
        return movements;
    }
    return NULL;
}

void uncoverPosSlope(int xorigin, int yorigin, int (*func)(int), int *kin){
    int it = 1;
    if(kin[0] > xorigin){
        while(kin[0]-it > 0 && kin[1]-it > 0 && board[kin[0]-it][kin[1]-it] == '0'){
            it++;
        }
        if(board[kin[0]-it][kin[1]-it] == func('b') || board[kin[0]-it][kin[1]-it] == func('q')){
            checker[0] = kin[0]-it;
            checker[1] = kin[1]-it;
            king[0] = kin[0];
            king[1] = kin[1];
            check++;
        }
    }else{
        while(kin[0]+it < 7 && kin[1]+it < 7 && board[kin[0]+it][kin[1]+it] == '0'){
            it++;
        }
        if(board[kin[0]+it][kin[1]+it] == func('b') || board[kin[0]+it][kin[1]+it] == func('q')){
            checker[0] = kin[0]+it;
            checker[1] = kin[1]+it;
            king[0] = kin[0];
            king[1] = kin[1];
            check++;
        }
    }
}

void uncoverNegSlope(int xorigin, int yorigin, int (*func)(int), int *kin){
    int it = 1;
    if(kin[0] > xorigin){
        while(kin[0]-it > 0 && kin[1]+it < 7 && board[kin[0]-it][kin[1]+it] == '0'){
            it++;
        }
        if(board[kin[0]-it][kin[1]+it] == func('b') || board[kin[0]-it][kin[1]+it] == func('q')){
            checker[0] = kin[0]-it;
            checker[1] = kin[1]+it;
            king[0] = kin[0];
            king[1] = kin[1];
            check++;
        }
    }else{
        while(kin[0]+it < 7 && kin[1]-it > 0 && board[kin[0]+it][kin[1]-it] == '0'){
            it++;
        }
        if(board[kin[0]+it][kin[1]-it] == func('b') || board[kin[0]+it][kin[1]-it] == func('q')){
            checker[0] = kin[0]+it;
            checker[1] = kin[1]-it;
            king[0] = kin[0];
            king[1] = kin[1];
            check++;
        }
    }
}

void uncoverVertical(int xorigin, int yorigin, int (*func)(int), int *kin){
    int it = 1;
    if(kin[0] > xorigin){
        while(kin[0]-it > 0 && board[kin[0]-it][kin[1]] == '0'){
            it++;
        }
        if(board[kin[0]-it][kin[1]] == func('r') || board[kin[0]-it][kin[1]] == func('q')){
            checker[0] = kin[0]-it;
            checker[1] = kin[1];
            king[0] = kin[0];
            king[1] = kin[1];
            check++;
        }
    }else{
        while(kin[0]+it < 7 && board[kin[0]+it][kin[1]] == '0'){
            it++;
        }
        if(board[kin[0]+it][kin[1]] == func('r') || board[kin[0]+it][kin[1]] == func('q')){
            checker[0] = kin[0]+it;
            checker[1] = kin[1];
            king[0] = kin[0];
            king[1] = kin[1];
            check++;
        }
    }
}

void uncoverHorizontal(int xorigin, int yorigin, int (*func)(int), int *kin){
    int it = 1;
    if(kin[1] > yorigin){
        while(kin[1]-it > 0 && board[kin[0]][kin[1]-it] == '0'){
            it++;
        }
        if(board[kin[0]][kin[1]-it] == func('r') || board[kin[0]][kin[1]-it] == func('q')){
            checker[0] = kin[0];
            checker[1] = kin[1]-it;
            king[0] = kin[0];
            king[1] = kin[1];
            check++;
        }
    }else{
        while(kin[1]+it < 7 && board[kin[0]][kin[1]+it] == '0'){
            it++;
        }
        if(board[kin[0]][kin[1]+it] == func('r') || board[kin[0]][kin[1]+it] == func('q')){
            checker[0] = kin[0];
            checker[1] = kin[1]+it;
            king[0] = kin[0];
            king[1] = kin[1];
            check++;
        }
    }
}

int checkPawn(int xorigin, int yorigin, int xdestiny, int ydestiny, int (*func)(int)){
    /*int kin[2];
    if(func(board[bKing[0]][bKing[1]])){
        kin[0] = bKing[0];
        kin[1] = bKing[1];
    }else{
        kin[0] = wKing[0];
        kin[1] = wKing[1];
    }*/
    int kin[2];
    int value = 1;
    if(board[bKing[0]][bKing[1]] == func('k')){
        kin[0] = wKing[0];
        kin[1] = wKing[1];
    }else{
        kin[0] = bKing[0];
        kin[1] = bKing[1];
    }
    if(xdestiny == 0 || xdestiny == 7){
        promoted[0] = xdestiny;
        promoted[1] = ydestiny;
        value = 2;
    }
    if(pasa && ydestiny == passant[1] && xdestiny == passant[0] + xdestiny - xorigin){
        board[passant[0]][passant[1]] = '0';
    }
    if((xorigin-xdestiny)%2 == 0){
        pasa = 2;
        passant[0] = xdestiny;
        passant[1] = ydestiny;
    }
    if(yorigin == ydestiny){
        if(ydestiny-1 == kin[1] || ydestiny+1 == kin[1]){
            if(xorigin-xdestiny == 1 || xorigin-xdestiny == -1){
                if(2*xdestiny-xorigin == kin[0]){
                    king[0] = kin[0];
                    king[1] = kin[1];
                    checker[0] = xdestiny;
                    checker[1] = ydestiny;
                    check++;
                }
            }else if(2*xdestiny-xorigin+1 == kin[0]){
                king[0] = kin[0];
                king[1] = kin[1];
                checker[0] = xdestiny;
                checker[1] = ydestiny;
                check++;
            }
        }else{
            if(kin[0]+kin[1] == xorigin+yorigin){
                uncoverNegSlope(xorigin, yorigin, func, kin);
            }else if(kin[0]-kin[1] == xorigin-yorigin){
                uncoverPosSlope(xorigin, yorigin, func, kin);
            }else if(kin[0] == xorigin){
                uncoverHorizontal(xorigin, yorigin, func, kin);
            }
        }
    }else{
        if(2*xdestiny-xorigin == kin[0] && (ydestiny-1 == kin[1] || ydestiny+1 == kin[1])){
            king[0] = kin[0];
            king[1] = kin[1];
            checker[0] = xdestiny;
            checker[1] = ydestiny;
            check++;
            if(yorigin == kin[1]){
                uncoverVertical(xorigin, yorigin, func, kin);
            }
        }else{
            if(kin[0] == xorigin){
                uncoverHorizontal(xorigin, yorigin, func, kin);
            }else if(kin[1] == yorigin){
                uncoverVertical(xorigin, yorigin, func, kin);
            }else if(kin[0]+kin[1] == xorigin+yorigin && xorigin+yorigin != xdestiny+ydestiny){
                uncoverNegSlope(xorigin, yorigin, func, kin);
            }else if(kin[0]-kin[1] == xorigin-yorigin && xorigin-yorigin != xdestiny+xdestiny){
                uncoverPosSlope(xorigin, yorigin, func, kin);
            }
        }
    }
    return value;
}

void checkRook(int xorigin, int yorigin, int xdestiny, int ydestiny, int (*func)(int)){
    int kin[2];
    /*if(yorigin == 0){
        if(blong && board[xdestiny][ydestiny] == 'r'){
            blong = 0;
        }else if(wlong && board[xdestiny][ydestiny] == 'R'){
            wlong = 0;
        }
    }else if(yorigin == 7){
        if(bshort && board[xdestiny][ydestiny] == 'r'){
            bshort = 0;
        }else if(wshort && board[xdestiny][ydestiny] == 'R'){
            wshort = 0;
        }
    }*/
    if(board[bKing[0]][bKing[1]] == func('k')){
        kin[0] = wKing[0];
        kin[1] = wKing[1];
    }else{
        kin[0] = bKing[0];
        kin[1] = bKing[1];
    }
    if(xdestiny == kin[0]){
        uncoverHorizontal(xdestiny, ydestiny, func, kin);
    }else if(ydestiny == kin[1]){
        uncoverVertical(xdestiny, ydestiny, func, kin);
    }
    if(xorigin+yorigin == kin[0]+kin[1]){
        uncoverNegSlope(xorigin, yorigin, func, kin);
    }else if(xorigin-yorigin == kin[0]-kin[1]){
        uncoverPosSlope(xorigin, yorigin, func, kin);
    }
}

void checkKnight(int xorigin, int yorigin, int xdestiny, int ydestiny, int (*func)(int)){
    int kin[2];
    if(board[bKing[0]][bKing[1]] == func('k')){
        kin[0] = wKing[0];
        kin[1] = wKing[1];
    }else{
        kin[0] = bKing[0];
        kin[1] = bKing[1];
    }
    if(abs(xdestiny-kin[0]) == 1 && abs(ydestiny-kin[1]) == 2 || abs(xdestiny-kin[0]) == 2 && abs(ydestiny-kin[1]) == 1){
        king[0] = kin[0];
        king[1] = kin[1];
        checker[0] = xdestiny;
        checker[1] = ydestiny;
        check++;
    }
    if(xorigin == kin[0]){
        uncoverHorizontal(xorigin, yorigin, func, kin);
    }else if(yorigin == kin[1]){
        uncoverVertical(xorigin, yorigin, func, kin);
    }else if(xorigin+yorigin == kin[0]+kin[1]){
        uncoverNegSlope(xorigin, yorigin, func, kin);
    }else if(xorigin-yorigin == kin[0]-kin[1]){
        uncoverPosSlope(xorigin, yorigin, func, kin);
    }
}

void checkBishop(int xorigin, int yorigin, int xdestiny, int ydestiny, int (*func)(int)){
    int kin[2];
    if(board[bKing[0]][bKing[1]] == func('k')){
        kin[0] = wKing[0];
        kin[1] = wKing[1];
    }else{
        kin[0] = bKing[0];
        kin[1] = bKing[1];
    }
    if(xdestiny+ydestiny == kin[0]+kin[1]){
        uncoverNegSlope(xdestiny, ydestiny, func, kin);
    }else if(xdestiny-ydestiny == kin[0]-kin[1]){
        uncoverPosSlope(xdestiny, ydestiny, func, kin);
    }
    if(xorigin == kin[0]){
        uncoverHorizontal(xorigin, yorigin, func, kin);
    }else if(yorigin == kin[1]){
        uncoverVertical(xorigin, yorigin, func, kin);
    }
}

void checkQueen(int xdestiny, int ydestiny, int (*func)(int)){
    int kin[2];
    if(board[bKing[0]][bKing[1]] == func('k')){
        kin[0] = wKing[0];
        kin[1] = wKing[1];
    }else{
        kin[0] = bKing[0];
        kin[1] = bKing[1];
    }
    if(xdestiny == kin[0]){
        uncoverHorizontal(xdestiny, ydestiny, func, kin);
    }else if(ydestiny == kin[1]){
        uncoverVertical(xdestiny, ydestiny, func, kin);
    }else if(xdestiny+ydestiny == kin[0]+kin[1]){
        uncoverNegSlope(xdestiny, ydestiny, func, kin);
    }else if(xdestiny-ydestiny == kin[0]-kin[1]){
        uncoverPosSlope(xdestiny, ydestiny, func, kin);
    }
}

void checkKing(int xorigin, int yorigin, int xdestiny, int ydestiny, int (*func)(int)){
    int kin[2];
    if(board[xdestiny][ydestiny] == 'k'){
        bKing[0] = xdestiny;
        bKing[1] = ydestiny;
        blong = 0;
        bshort = 0;
        kin[0] = wKing[0];
        kin[1] = wKing[1];
    }else{
        wKing[0] = xdestiny;
        wKing[1] = ydestiny;
        wlong = 0;
        wshort = 0;
        kin[0] = bKing[0];
        kin[1] = bKing[1];
    }
    int sum = ydestiny - yorigin;
    if(sum % 2 == 0){
        if(sum > 0){
            board[xorigin][ydestiny-1] = board[xorigin][7];
            board[xorigin][7] = '0';
            if(kin[1] == ydestiny-1){
                uncoverVertical(xorigin, ydestiny-1, func, kin);
            }
            if(kin[0] == xorigin){
                uncoverHorizontal(xorigin, ydestiny-1, func, kin);
            }
        }else{
            board[xorigin][ydestiny+1] = board[xorigin][0];
            board[xorigin][0] = '0';
            if(kin[1] == ydestiny+1){
                uncoverVertical(xorigin, ydestiny+1, func, kin);
            }
            if(kin[0] == xorigin){
                uncoverHorizontal(xorigin, ydestiny+1, func, kin);
            }
        }
    }else{
        if(xorigin == kin[0]){
            uncoverHorizontal(xorigin, yorigin, func, kin);
        }else if(yorigin == kin[1]){
            uncoverVertical(xorigin, yorigin, func, kin);
        }else if(xorigin+yorigin == kin[0]+kin[1]){
            uncoverNegSlope(xorigin, yorigin, func, kin);
        }else if(xorigin-yorigin == kin[0]-kin[1]){
            uncoverPosSlope(xorigin, yorigin, func, kin);
        }
    }
}

int promote(char type){
    type = tolower(type);
    int (*func)(int);
    if(islower(board[promoted[0]][promoted[1]])){
        func = tolower;
    }else{
        func = toupper;
    }
    int kin[2];
    if(board[bKing[0]][bKing[1]] == func('k')){
        kin[0] = wKing[0];
        kin[1] = wKing[1];
    }else{
        kin[0] = bKing[0];
        kin[1] = bKing[1];
    }
    if(type == 'q'){
        board[promoted[0]][promoted[1]] = func('q');
        checkQueen(promoted[0], promoted[1], func);
        return 1;
    }else if(type == 'r'){
        board[promoted[0]][promoted[1]] = func('r');
        if(promoted[0] == kin[0]){
            uncoverHorizontal(promoted[0], promoted[1], func, kin);
        }else if(promoted[1] == kin[1]){
            uncoverVertical(promoted[0], promoted[1], func, kin);
        }
        return 1;
    }else if(type == 'b'){
        board[promoted[0]][promoted[1]] = func('b');
        if(promoted[0]+promoted[1] == kin[0]+kin[1]){
            uncoverNegSlope(promoted[0], promoted[1], func, kin);
        }else if(promoted[0]-promoted[1] == kin[0]-kin[1]){
            uncoverPosSlope(promoted[0], promoted[1], func, kin);
        }
        return 1;
    }else if(type == 'n'){
        board[promoted[0]][promoted[1]] = func('n');
        if(abs(promoted[0]-kin[0]) == 1 && abs(promoted[1]-kin[1]) == 2 || abs(promoted[0]-kin[0]) == 2 && abs(promoted[1]-kin[1]) == 1){
            checker[0] = promoted[0];
            checker[1] = promoted[1];
            king[0] = kin[0];
            king[1] = kin[1];
            check++;
        }
        return 1;
    }else{
        return 0;
    }
}

int **calculateMovements(int *a, int x, int y){
    if(x >= 0 && x < 8 && y >= 0 && y < 8){
	calcresult = 1;
        if(turn){
            switch(board[x][y]){
                case 'P':
                    return wpawn(a, x, y);
                case 'R':
                    return rook(a, x, y, islower);
                case 'N':
                    return knight(a, x, y, islower);
                case 'B':
                    return bishop(a, x, y, islower);
                case 'Q':
                    return queen(a, x, y, islower);
                case 'K':
                    return kingg(a, x, y, islower);
                default:
		    calcresult = -1;
                    return NULL;
            }
        }else{
            switch(board[x][y]){
                case 'p':
                    return bpawn(a, x, y);
                case 'r':
                    return rook(a, x, y, isupper);
                case 'n':
                    return knight(a, x, y, isupper);
                case 'b':
                    return bishop(a, x, y, isupper);
                case 'q':
                    return queen(a, x, y, isupper);
                case 'k':
                    return kingg(a, x, y, isupper);
                default:
		    calcresult = -1;
                    return NULL;
            }
        }
    }else{
	calcresult = -2;
        return NULL;
    }
}

int gameState(){
    int (*func)(int);
    if(turn){
        func = islower;
    }else{
        func = isupper;
    }
    if(check){
        int a = 0;
        if(kingg(&a, king[0], king[1], func)){
            return 1;
        }else{
            int **movements = NULL;
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(!func(board[i][j]) && board[i][j] != 'k' && board[i][j] != 'K' && board[i][j] != '0'){
                        int a = 0;
                        movements = calculateMovements(&a, i, j);
                        free(movements);
                        if(a){
                            return 1;
                        }
                    }
                }
            }
            checkmate = 1;
            return 2;
        }
    }else{
        int **movements = NULL;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(!func(board[i][j]) && board[i][j] != '0'){
                    int a = 0;
                    movements = calculateMovements(&a, i, j);
                    free(movements);
                    if(a){
                        return 0;
                    }
                }
            }
        }
        draw = 1;
        return 3;
    }
}

int move(int xorigin, int yorigin, int xdestiny, int ydestiny){
    int a = 0;
    int **movements = calculateMovements(&a, xorigin, yorigin);
    for(int i = 0; i < a; i++){
        if(xdestiny == movements[i][0] && ydestiny == movements[i][1]){
            free(movements);
            if(check){
                check = 0;
            }
            board[xdestiny][ydestiny] = board[xorigin][yorigin];
            board[xorigin][yorigin] = '0';
            if(wshort && board[7][7] != 'R'){
                wshort = 0;
            }else if(wlong && board[7][0] != 'R'){
                wlong = 1;
            }else if(bshort && board[0][7] != 'r'){
                bshort = 0;
            }else if(blong && board[0][0] != 'r'){
                blong = 0;
            }
            int value = 1;
            if(pasa > 0){
                pasa--;
            }
            switch(board[xdestiny][ydestiny]){
                case 'p':
                    value = checkPawn(xorigin, yorigin, xdestiny, ydestiny, tolower);
                    break;
                case 'r':
                    checkRook(xorigin, yorigin, xdestiny, ydestiny, tolower);
                    break;
                case 'n':
                    checkKnight(xorigin, yorigin, xdestiny, ydestiny, tolower);
                    break;
                case 'b':
                    checkBishop(xorigin, yorigin, xdestiny, ydestiny, tolower);
                    break;
                case 'q':
                    checkQueen(xdestiny, ydestiny, tolower);
                    break;
                case 'k':
                    checkKing(xorigin, yorigin, xdestiny, ydestiny, tolower);
                    break;
                case 'P':
                    value = checkPawn(xorigin, yorigin, xdestiny, ydestiny, toupper);
                    break;
                case 'R':
                    checkRook(xorigin, yorigin, xdestiny, ydestiny, toupper);
                    break;
                case 'N':
                    checkKnight(xorigin, yorigin, xdestiny, ydestiny, toupper);
                    break;
                case 'B':
                    checkBishop(xorigin, yorigin, xdestiny, ydestiny, toupper);
                    break;
                case 'Q':
                    checkQueen(xdestiny, ydestiny, toupper);
                    break;
                case 'K':
                    checkKing(xorigin, yorigin, xdestiny, ydestiny, toupper);
                    break;
            }
            if(turn){
                turn = 0;
            }else{
                turn = 1;
            }
            return value;
        }
    }
    free(movements); // need to free stuff inside movements. this code sucks
    if(calcresult < 0 && calcresult > -3){
        return calcresult;
    }
    else{
        return 0;
    }
}

///////////////////////////////////////

void input1(int *x, int *y){
    char cha;
    do{
        char c;
        while((c = getchar()) != '\n' && c != EOF);
        printf("input the file (from 'a' to 'h'): ");
        cha = getchar();
        if(cha > 'h' || cha < 'a'){
            printf("thats not a valid option. try again.\n");
        }
    }while(cha > 'h' || cha < 'a');
    *y = cha - 'a';
    do{
        printf("input the row (from 1 to 8): ");
        scanf("%d", x);
        if(*x < 1 || *x > 8){
            printf("thats not a valid option. try again.\n");
        }
    }while(*x < 1 || *x > 8);
    *x = 8 - *x;
}

void input2(){
    printf("what would you like to do:\n\t1: list the posible movements of a piece.\n\t2: Command a move.\n");
    printf("input the number corresponding to the option you want\n");
    int option = 0;
    scanf("%d", &option);
    if(option == 1){
        int a = 0;
        int x = 0;
        int y = 0;
        input1(&x, &y);
        int **movements = calculateMovements(&a, x, y);
        if(a > 0){
            for(int i = 0; i < a; i++){
                char fila = movements[i][1] + 'a';
                int col = 8 - movements[i][0];
                printf("<%c, %d>\n", fila, col);

            }
            free(movements);
        }else{
            if(calcresult == -1){
                printf("thats not a valid piece to move\n");
            }else if(calcresult == -2){
                printf("those are not valid coordinates\n");
            }else{
                printf("there are no valid moves for that piece\n");
            }
        }
    }else if(option == 2){
        int xorigin = 0, yorigin = 0, xdestiny = 0, ydestiny = 0;
        printf("Input the coordinates of the piece to move\n");
        input1(&xorigin, &yorigin);
        printf("Input the coordinates for the destination of the piece\n");
        input1(&xdestiny, &ydestiny);
        int e = move(xorigin, yorigin, xdestiny, ydestiny);
        if(e == 2){
            int u = 0;
            do{
                printf("select the type of piece you want the pawn to be promoted to. (q, r, b, n): ");
                char c;
                while((c = getchar()) != '\n' && c != EOF);
                char ch = getchar();
                u = promote(ch);
                if(!u){
                    printf("thats not a valid piece type. try again.\n");
                }
            }while(!u);
            int o = gameState();
            if(o == 1){
                printf("check\n");
            }else if(o == 2){
                printf("checkmate\n");
            }else if(o == 3){
                printf("stalemate\n");
            }
        }else if(e == 1){
            printf("move done succesfully\n");
            int o = gameState();
            if(o == 1){
                printf("check\n");
            }else if(o == 2){
                printf("checkmate\n");
            }else if(o == 3){
                printf("stalemate\n");
            }
        }else if(e == 0){
            printf("that is not a valid move\n");
        }else if(e == -1){
            printf("thats not a valid piece to move\n");
        }else if(e == -2){
            printf("those are not valid coordinates\n");
        }
    }else{
        printf("that option does not exist\n");
        char c;
        while((c = getchar()) != '\n' && c != EOF);
    }
}

int main(){
    for(int i = 0; i < sizeof(board)/ sizeof(board[0]); i++){
        for(int j = 0; j < sizeof(board[0]); j++){
            putchar(board[i][j]);
            putc('\t', stdout);
        }
        putchar('\n');
    }

    while(!checkmate && !draw){
        input2();
        for(int i = 0; i < sizeof(board)/ sizeof(board[0]); i++){
            for(int j = 0; j < sizeof(board[0]); j++){
                putchar(board[i][j]);
                putc('\t', stdout);
            }
            putchar('\n');
        }
    }
    return 0;
}
