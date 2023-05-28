#include "components/Board.h"
#include "components/helper.h"
#include "components/presenter.h"
#include <iostream>
  

int main()
{
    Board board("rnbqkbnr/1ppppppp/p7/4P3/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2");
    std::cout << board.toFEN() << std::endl;
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);
    board.DoMove(CreateMove(5, 6, 5, 4, 0));
    std::cout << board.toFEN() << std::endl;
    std::cout << std::endl << presenter.ToString(board);
    board.DoMove(CreateMove(4, 4, 5, 5, CAPTURE));
    std::cout << board.toFEN() << std::endl;
    std::cout << std::endl << presenter.ToString(board);
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
