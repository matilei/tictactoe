/* Ristinolla
 *
 * Kuvaus:
 *   Ohjelma toteuttaa ristinollapelin, jossa pelialuetta pystyy
 * laajentamaan. Alussa peliruudukko on kooltaan 3 x 3. Peliruudukossa
 * on kolmenlaisia merkkejä: risti (X), nolla (0) ja tyhjä (.).
 *   Pelivuorossa ovat vuorotellen risti ja nolla, risti aloittaa.
 * Joka kierroksella vuorossa olevalle merkille kysytään koordinaatteja
 * eli kahta lukua. Vuorossa oleva merkki sijoitetaan peliruudukolla
 * annettuihin koordinaatteihin, ja vuoro siirtyy toiselle merkille.
 *   Pelin voittaa merkki, jolla saadaan ensimmäiseksi täytettyä peliruudukon
 * kokonainen rivi, kokonainen sarake tai kokonainen diagonaali.
 * Peli voi päättyä myös sellaiseen tilanteeseen, että peliruudukko on
 * täynnä merkkejä, mutta kumpikaan merkki ei voittanut.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pitää olla
 * peliruudukon sisällä, tai koordinaatit saavat ylittyä tai alittua
 * korkeintaan yhdellä. Jos annettu x- tai y-koordinaatti (rivi tai sarake)
 * ylittyy yhdellä, peliruudukko laajenee oikealle ja alaspäin. Jos taas
 * x- tai y-koordinaatti alittuu yhdelle, peliruudukko laajenee vasemmalle
 * ja alaspäin. Peliruudukko siis pysyy aina neliön muotoisena.
 *   Pelin päättyessä kerrotaan, kumpi voitti, vai voittiko kumpikaan.
 *
 * */

#include <iostream>
#include <vector>
#include <string>

namespace  {
const int BOARD_INIT_SIZE = 3;
}

/*
 * Toiminto: Alustaa pelilaudan pelin aloitusta varten
 * Parametrit:
 *  board Pelilauta joka alustetaan
 * */
void initBoard(std::vector<std::vector<char>>& board) {
    for (int y = 0; y < BOARD_INIT_SIZE; ++y) {
        std::vector<char> vector;
        for (int x = 0; x < BOARD_INIT_SIZE; ++x) {
            vector.push_back('.');
        }
        board.push_back(vector);
    }
}

/*
 * Toiminto: Tulostaa pelilaudan
 * Parametrit:
 *  board Pelilauta joka tulostetaan
 * */
void printBoard(const std::vector<std::vector<char>>& board) {
    std::vector<std::vector<char>>::size_type board_size = board.size();
    // Tulostaa x-akselin otsikkonumerot
    std::cout << "  ";
    for (unsigned x = 0; x < board_size; ++x) {
        // Jos x-akselin leveys on yli 10,
        // aloitetaan laskenta uudestaan luvusta 0
        std::cout << (x + 1) % 10 << " ";
    }
    std::cout << std::endl;

    // Tulostaa y-akselin otsikkonumerot
    for (unsigned y = 0; y < board_size; ++y) {
        std::cout << (y + 1) % 10 << " ";
        // Tulostaa peli- ja tyhjat merkit x,y koordinaateista
        for (unsigned x = 0; x < board_size; ++x) {
            std::cout << board.at(x).at(y) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/*
 * Toiminto: Merkkijonon numeerisuuden tarkistaminen
 * Parametrit:
 *  input Syotetty merkkijono
 * Paluuarvo: bool-totuusarvo joka kertoo onko merkkijono numeerinen
 * */
bool isNumerical(const std::string& input) {
    for (char ch: input) {
        if (!(ch >= '0' && ch <= '9')) {
            break;
        }
        return true;
    }
    return false;
}

/*
 * Toiminto: Koordinaattien kysyminen, lukeminen ja tarkistaminen
 * Parametrit:
 *  x, y X- ja Y-koordinaatit joiden arvot tarkastetaan oikeellisiksi
 *  character Pelimerkki jota kaytetaan vuorotulostuksessa
 *  board Pelilauta jonka pituutta ja ruutua tarkastellaan
 * Paluuarvo: bool-totuusarvo joka kertoo jatkuuko ohjelman suoritus
 * */
bool isInputCorrect(unsigned int& x,
                    unsigned int& y,
                    const char& character,
                    const std::vector<std::vector<char>>& board) {
    std::string inputX = "";
    std::string inputY = "";
    std::vector<std::vector<char>>::size_type board_size = board.size();

    // Kysytaan arvoja niin kauan kun
    // poistutaan ohjelmasta tai syotetaan oikea koordinaatti
    while (true) {
        std::cout << "For " << character
        << ", enter coordinates: x y> ";

        std::cin >> inputX;
        if (inputX == "q") {
            std::cout << "Why on earth you are giving up the game?"
            << std::endl;
            return false;
        }
        std::cin >> inputY;

        // Tarkistetaan ovatko syotetyt merkkijonot numeerisia
        if (isNumerical(inputX) && isNumerical(inputY)) {
            // Muutetaan syotetyt merkkijonot int-tyypeiksi
            x = std::stoi(inputX);
            y = std::stoi(inputY);

            // Tarkistetaan etta koordinaatit eivat
            // ylity enemman kuin yhdella tai
            // alitu ja ylity samaan aikaan
            if ((x > board_size + 1 || y > board_size + 1) ||
               ((x == 0 && y > board_size) || (y == 0 && x > board_size))) {
                std::cout << "Coordinate outside the board" << std::endl;
            } else {
                // Tarkistetaan ovatko koordinaatit laudan ulkopuolella
                if ((x == 0 || y == 0) ||
                    (x > board_size || y > board_size)) {
                    return true;
                } else {
                    // Tarkistetaan etta ruutu on tyhja mihin lisataan
                    if (board.at(x - 1).at(y - 1) == '.') {
                        return true;
                    } else {
                        std::cout << "The given place is already occupied"
                        << std::endl;
                    }
                }
            }
        } else {
            std::cout << "Coordinate outside the board" << std::endl;
        }
    }
}

/*
 * Toiminto: Pelilaudan laajentaminen tarvittaessa
 * Parametrit:
 *  x,y X- ja Y-koordinaatit joista tarkistetaan onko laajennus tarpeen
 *  board Pelilauta jota laajennetaan tarvittaessa
 * */
void expandBoard(const unsigned int& x,
                 const unsigned int& y,
                 std::vector<std::vector<char>>& board) {
    std::vector<std::vector<char>>::size_type board_size = board.size();
    unsigned int board_size_addition = board_size + 1;

    // Tarkistetaan ovatko koordinaatit pelilaudan ulkopuolella
    // jos eivat ole palataan samalla pelilaudan koolla
    if ((x == 0 || y == 0) || (x > board_size || y > board_size)) {

        // Pelilaudan laajentaminen alas ja oikealle
        if (x > board_size || y > board_size) {
            // Lisataan nykyisiin vektoreihin tyhja merkki peraan
            for (unsigned i = 0; i < board_size; ++i) {
                board.at(i).push_back('.');
            }
            // Luodaan uusi vektori pelilaudan alle
            std::vector<char> vector;
            for (unsigned i = 0; i < board_size_addition; ++i) {
                vector.push_back('.');
            }
            board.push_back(vector);

        // Pelilaudan laajentaminen ylos ja vasemmalle
        } else {
            // Luodaan uusi vektori<vektori> laajentamista varten
            // ja taytetaan se uudella koolla
            std::vector<std::vector<char>> newBoard = {};
            for (unsigned i = 0; i < board_size_addition; ++i) {
                std::vector<char> vector;
                for (unsigned j = 0; j < board_size_addition; ++j) {
                    vector.push_back('.');
                }
                newBoard.push_back(vector);
            }
            // Lisataan laajennettuun vektoriin alkuperaisen vektorin arvot
            for (unsigned i = 0; i < board_size; ++i) {
                for (unsigned j = 0; j < board_size; ++j) {
                    newBoard.at(i + 1).at(j + 1) = board.at(i).at(j);
                }
            }
            // Asetetaan laajennettu vektori alkuperaiseksi
            board = newBoard;
        }
    }
}

/*
 * Toiminto: Pelimerkin lisaaminen pelilautaan
 * Parametrit:
 *  x,y X- ja Y-koordinaatit joihin lisataan pelimerkki
 *  character Pelimerkki joka lisataan
 *  board Pelilauta johon lisataan
 * */
void addToBoard(const unsigned int& x,
                const unsigned int& y,
                const char& character,
                std::vector<std::vector<char>>& board) {
    // Jos pelilauta laajenee ylos ja vasemmalle sailytetaan arvot
    if (x == 0 || y == 0) {
        board.at(x).at(y) = character;
    // Jos syote on pelilaudalla tai laajenee alas ja oikealle,
    // vahennetaan jotta lisataan oikeaan vektorin indeksiin
    } else {
        board.at(x - 1).at(y - 1) = character;
    }
}

/*
 * Toiminto: Tarkastaa loytyyko pelilaudalta ratkaisu
 * Parametrit:
 *  board Pelilauta josta tarkistetaan mahdollinen ratkaisu
 *  character Pelimerkki jolle tarkistetaan mahdollinen voitto
 * Paluuarvo: bool-totuusarvo kertoo onko loydetty ratkaisu
 * */
bool isSolution(const char& character,
                const std::vector<std::vector<char>>& board) {
    std::vector<std::vector<char>>::size_type board_size = board.size();
    std::string character_name = "";
    unsigned full_board_counter = 0;
    unsigned left_diagonal_counter = 0;
    unsigned right_diagonal_counter = 0;

    // Asetetaan pelimerkille nimi tulostusta varten
    if (character == 'X') {
        character_name = "Cross";
    } else {
        character_name = "Nought";
    }

    // Rivi- ja sarakevoiton tarkistaminen
    // ja tayden pelilaudan tarkistaminen
    for (unsigned y = 0; y < board_size; ++y) {
        unsigned row_counter = 0;
        unsigned column_counter = 0;
        for (unsigned x = 0; x < board_size; ++x) {
            // Tarkistetaan onko millaan rivilla vain samoja pelimerkkeja
            if (board.at(x).at(y) == character) {
                ++row_counter;
            }
            // Tarkistetaan onko millaan sarakkeella vain samoja pelimerkkeja
            if (board.at(y).at(x) == character) {
                ++column_counter;
            }
            // Kasvatetaan laskuria aina kun pelilaudalle lisataan pelimerkki
            if (board.at(x).at(y) != '.') {
                ++full_board_counter;
            }
        }
        if (row_counter == board_size) {
            std::cout << character_name << " won horizontally" << std::endl;
            std::cout << "Game over!" << std::endl;
            return true;
        }
        if (column_counter == board_size) {
            std::cout << character_name << " won vertically" << std::endl;
            std::cout << "Game over!" << std::endl;
            return true;
        }
        if (full_board_counter == board_size * board_size) {
            std::cout << "No empty places" << std::endl;
            std::cout << "Game over!" << std::endl;
            return true;
        }
    }

    // Vasemmalta oikealle -diagonaalin voiton tarkistaminen
    // Tarkistetaan onko vasemmalta oikealle diagonaalin koordinaateilla
    // vain samoja pelimerkkeja
    for (unsigned y = 0, x = 0; y < board_size; ++y, ++x) {
        if (board.at(x).at(y) == character) {
            ++left_diagonal_counter;
        }
    }
    if (left_diagonal_counter == board_size) {
        std::cout << character_name << " won diagonally" << std::endl;
        std::cout << "Game over!" << std::endl;
        return true;
    }

    // Oikealta vasemmalle -diagonaalin voiton tarkistaminen
    // Tarkistetaan onko oikealta vasemmalle diagonaalin koordinaateilla
    // vain samoja pelimerkkeja
    for (unsigned y = 0, x = board_size - 1; y < board_size; ++y, --x) {
        if (board.at(x).at(y) == character) {
            ++right_diagonal_counter;
        }
    }
    if (right_diagonal_counter == board_size) {
        std::cout << character_name << " won diagonally" << std::endl;
        std::cout << "Game over!" << std::endl;
        return true;
    }
    return false;
}

int main() {
    std::vector<std::vector<char>> board = {};
    initBoard(board);

    std::cout << "Start game:" << std::endl;
    printBoard(board);

    // X aloittaa pelin
    int turn = 1;
    char character = 'X';

    unsigned int x = 0;
    unsigned int y = 0;

    // Peli kestaa niin kauan kun ratkaisu loytyy
    while (!isSolution(character, board)) {
        // Parillinen turn-vuoromuuttuja on 0 ja pariton on X
        if (turn % 2 != 0) {
            character = 'X';
        } else {
            character = '0';
        }

        // Jos palautetaan true tarkistetaan onko laajennus tarpeen
        // ja lisataan merkki pelilaudalle
        // Jos palauttaa false poistutaan while ja suljetaan ohjelma
        if (isInputCorrect(x, y, character, board)) {
            expandBoard(x, y, board);
            addToBoard(x, y, character, board);
            printBoard(board);
        } else {
            break;
        }
        // Vaihdetaan vuoro
        turn++;
    }
    return EXIT_SUCCESS;
}
