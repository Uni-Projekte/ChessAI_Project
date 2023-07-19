#include "gameclient.h"

void GameClient::OnMessage(websocketpp::connection_hdl, websocketpp::client<websocketpp::config::asio_client>::message_ptr msg) {
    std::cout << msg->get_payload() << std::endl;
}

GameClient::GameClient(){
    this->client = new websocketpp::client<websocketpp::config::asio_client>();
    this->client->init_asio();
    this->client->set_message_handler(this->OnMessage);
}

void GameClient::Connect() {
    websocketpp::lib::error_code ec;
    websocketpp::client<websocketpp::config::asio_client>::connection_ptr con = this->client->get_connection(URI, ec);
    if (ec) {
        std::cout << "could not create connection because: " << ec.message() << std::endl;
        exit(-1);
    }
    this->client->connect(con);

    this->client->run();
}

LoginResponse GameClient::sendLoginRequest(LoginRequest request){
    Json::Value jsonRequest;
    jsonRequest["type"] = request.msg.type;
    jsonRequest["stamp"] = request.msg.stamp;
    jsonRequest["playerID"] = request.playerID;
    jsonRequest["username"] = request.username;
    Json::FastWriter writer;
    std::string jsonString = writer.write(jsonRequest);



    std::string errors;
    LoginResponse loginResponse;
    Json::Value res;
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();

    reader->parse(this->buffer,this->buffer+1000, &res, &errors);

    loginResponse.playerName = res["playerName"].asString();
    loginResponse.playerID = res["playerID"].asInt();
    loginResponse.rating = res["rating"].asInt();

    delete reader;

    return loginResponse;
}
