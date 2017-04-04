#ifndef CONFIG_H
#define CONFIG_H

//zakomentowac do testowania bez komunikacji z serwerem
#define TCP

//liczba klatek na sekunde wyswietlanych przez okno
#define FPS 30

//okresla czy ma byc wywolywana funkcja sendCommands pod koniec trwania tury
//#define SEND_COMMANDS_LATE

//dlugosc trwania tury (czas po jakim zostanie wywolana funkcja sendCommands jesli jest zdefiniowane SEND_COMMANDS_LATE)
#define TURN_DURATION 1.0

//okresla czy dlugosc trwania tury ma byc mierzony automatycznie (powoduje to strate dwoch tur przy uruchomieniu programu)
#define AUTO_TURN_DURATION

//wspolczynnik przez ktory jest mnozona zmierzona dlugosc trwania tury (jesli zdefiniowano AUTO_TURN_DURATION)
#define TURN_DURATION_RATIO 0.6

//komenda do uzyskania liczby tur (jesli jest zakomentowana, funkcja turns_left() zawsze zwraca 0)
#define TURNS_LEFT_COMMAND "TURNS_LEFT"

//czy w razie bledow rzucac wyjatki ktore restartuja gre
//#define THROW_EXCEPTIONS

//czy mozna zaznaczac prostakaty myszka
#define ENABLE_RECT_SELECTION

//liczba pikseli od granicy okna gdzie po najechaniu kursorem okno sie przesuwa
#define WINDOW_BORDER 30

//czy ma byc pokazywane okno pokazujace zawartosc strumieni
#define STREAM_WINDOW

//czy przebieg gry ma byc zapisywany do pliku
#define SAVE_GAME

#endif // CONFIG_H
