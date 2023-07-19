
#include "src/helper.h"
#include "src/presenter.h"
#include "src/contest/gameclient.h"
#include <iostream>
  

int main()
{
    GameClient c;
    c.Connect();

    LoginRequest loginRequest = {"user",1,{Login,0}};

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    LoginResponse loginResponse = c.sendLoginRequest(loginRequest);
    std::cout << "LOGIN RESPONSE" << std::endl
    << "Player ID: " << loginResponse.playerID << std::endl
    << "Player Name: " << loginResponse.playerName << std::endl
    << "Rating: " <<  loginResponse.rating << std::endl;

    bool run = true;
    while(run){

    }
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
