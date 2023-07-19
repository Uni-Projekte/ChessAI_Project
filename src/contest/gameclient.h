#include "../json/json.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#ifndef CHESSAI_PROJECT_GAMECLIENT_H
#define CHESSAI_PROJECT_GAMECLIENT_H

#define URI "ws://127.0.0.1:8025/websockets/game"

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

typedef struct {
    RequestType type;
    int stamp; //number | any
} Message;

typedef struct{
    std::string playerName;
    int playerID;
    int rating;
} Player;

typedef struct{
    std::vector<Player> activePlayerList;
    int ID;
    int timeLeft[2];
    std::vector<int> moveTimestamps;
    std::vector<std::string> moveHistory;
    int maxPlayerNumber; // = 2
    Player currentPlayer;
    Player* winner;
    std::string fen;
    bool inThreeFoldRepetition;
    bool insufficientMaterial;
    bool stalemate;
    bool checkMate;
    bool check;
    bool over;
    bool draw;
} GameInfo;

// login

typedef struct {
    std::string username;
    int playerID;
    Message msg;
} LoginRequest;

typedef Player LoginResponse;

// get games

typedef Message GetGamesRequest;

typedef struct {
    std::vector<GameInfo> games;
} GetGamesResponse;

// create game

typedef struct {
    std::string username;
    int playerID;
    int timeout;
    int gameRetentionTime;
} CreateGameRequest;

typedef GameInfo CreateGameResponse;

// join game

enum JoinType {
    JTPlayer = 1,
};

typedef struct {
    std::string username;
    int playerID;
    JoinType joinAsPlayer;
    int gameID;
} JoinGameRequest;

typedef GameInfo JoinGameResponse;

// move

typedef struct {
    std::string username;
    int playerID;
    int gameID;
    std::string move;
} MoveRequest;

typedef GameInfo MoveResponse;

// start tournament

typedef struct {
    int ticks;
    int gameTimeout;
    int gameRetentionTime;
} StartTournamentRequest;

typedef Message StartTournamentResponse;

// game started

typedef Message GameStartedResponse;

class GameClient {
private:
    websocketpp::client<websocketpp::config::asio_client> *client;
    websocketpp::client<websocketpp::config::asio_client>::connection_ptr connection;
    std::thread *tMain;

public:
    GameClient();
    void Connect();
    void static OnMessage(websocketpp::connection_hdl, websocketpp::client<websocketpp::config::asio_client>::client::message_ptr msg);
    void sendRequest();
    MoveRequest createRequest();
    void handleRequest();

    MoveRequest createRequest(std::string username, int playerID, int gameID, std::string move);

    void parseRequest();

    LoginResponse sendLoginRequest(LoginRequest request);
};


#endif //CHESSAI_PROJECT_GAMECLIENT_H

