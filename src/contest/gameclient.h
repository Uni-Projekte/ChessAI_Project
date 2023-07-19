#include <json/json.h>

#ifndef CHESSAI_PROJECT_GAMECLIENT_H
#define CHESSAI_PROJECT_GAMECLIENT_H

enum RequestType {
    Login = 0,
    GetGames = 1,
    CreateGame = 2,
    JoinGame = 3,
    Move = 4,
    Database = 5,
    StartTournament = 6,
    GetPlayers = 7,
    GameStarted = 8,

    Error = -1,
    IllegalMove = -2,
    NotImplemented = -3,
    InvalidRequest = -4,
    Unauthorized = -5,
    Full = -6,
    NotFound = -7,
};

class gameclient {

};


#endif //CHESSAI_PROJECT_GAMECLIENT_H

