#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Bancomat.h"
#include "Tranzactie.h"
#include "Bancomat.cpp"
#include "Tranzactie.cpp"
#include "RBTree.h"
#include "RBTree.cpp"

using namespace std;

enum class AppState {
    Main,            // Main application state
    AddTranzactie,   // State for adding a new Tranzactie
    ShowTranzactions, // State for showing Tranzactions
    ShowRBTree,      // State for showing the RBTree
};
bool isButtonClicked(const sf::RectangleShape& button, const sf::Vector2i& mousePosition) {
    return button.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}
// Function to draw Bancomat and Tranzactii on the SFML window
void drawTranzactieDetails(sf::RenderWindow& window, const Tranzactie& tranzactie, sf::Font& font) {
    sf::Text text("Tranzactie Details:", font, 15);
    text.setPosition(10, 10);
    window.draw(text);

    std::ostringstream details;
    details << "Data: " << tranzactie.getData() << "\n";
    details << "Tip: " << (tranzactie.getTip() == TipTranzactie::intrare ? "Intrare" : "Iesire") << "\n";
    details << "Suma: " << tranzactie.getSuma() << "\n";
    details << "Descriere: " << tranzactie.getDescriere() << "\n";

    sf::Text tranzactieText(details.str(), font, 15);
    tranzactieText.setPosition(10, 50);
    window.draw(tranzactieText);
}

void drawButton(sf::RenderWindow& window, const sf::Text& buttonText, const sf::RectangleShape& buttonShape) {
    window.draw(buttonShape);
    window.draw(buttonText);
}

void readFromFile(Bancomat& b, RbTree<Tranzactie>& t) {
    ifstream f("tranzactiiTransilvania.txt");
    int n;
    f >> n;
    for (int i = 0; i < n; i++) {
        Date d;
        int zi, luna, an;
        char dot;
        f >> zi >> dot >> luna >> dot >> an;
        d.setZi(zi);
        d.setLuna(luna);
        d.setAn(an);

        TipTranzactie tip;
        string s;
        f >> s;
        if (s == "intrare")
            tip = intrare;
        else
            tip = iesire;
        string suma;
        f >> suma;
        string descriere;
        f >> descriere;
        Tranzactie tranzactie(d, tip, suma, descriere);
        t.insert(tranzactie);
        b.adaugaTranzactie(tranzactie);
    }
    f.close();
}

template <class T>
void drawRBTree(sf::RenderWindow& window, const RbNode<T>* node, const sf::Font& font, float x, float y, float xOffset, float level) {
    if (node == nullptr)
        return;

    const float radius = 20.0f;
    const float lineLength = 50.0f;
    const float yOffset = 100.0f;

    sf::CircleShape circle(radius);
    circle.setFillColor(node->isBlack() ? sf::Color::Black : sf::Color::Red);
    circle.setPosition(x - radius, y - radius);

    sf::Text text(std::to_string(node->getData()), font, 15);
    text.setPosition(x - radius / 2, y - radius / 2);

    window.draw(circle);
    window.draw(text);

    if (node->getLeft() != nullptr) {
        // Draw left child
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(x, y);
        line[0].color = sf::Color::Blue;
        line[1].position = sf::Vector2f(x - xOffset, y + yOffset);
        line[1].color = sf::Color::Blue;

        window.draw(line);
        drawRBTree(window, node->getLeft(), font, x - xOffset, y + yOffset, xOffset / 2, level + 1);
    }

    if (node->getRight() != nullptr) {
        // Draw right child
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(x, y);
        line[0].color = sf::Color::Blue;
        line[1].position = sf::Vector2f(x + xOffset, y + yOffset);
        line[1].color = sf::Color::Blue;

        window.draw(line);
        drawRBTree(window, node->getRight(), font, x + xOffset, y + yOffset, xOffset / 2, level + 1);
    }
}



int main() {
    Bancomat Transilvania(2000);
    RbTree<Tranzactie> TransilvaniaTranzactii;
    readFromFile(Transilvania, TransilvaniaTranzactii);
    const RbNode<Tranzactie>* root = TransilvaniaTranzactii.getRoot();

    

    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tranzactie UI");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("Kanit-Black.ttf")) {
        // Handle font loading error
        return EXIT_FAILURE;
    }

    // Example Tranzactie
    Tranzactie exampleTranzactie(Date(1, 1, 2022), TipTranzactie::intrare, "1000", "Salary");

    // Create buttons
    sf::RectangleShape addButton(sf::Vector2f(200, 50));
    addButton.setFillColor(sf::Color::Green);
    addButton.setPosition(10, 500);

    sf::Text addButtonText("Add Tranzactie", font, 20);
    addButtonText.setPosition(20, 510);

    sf::RectangleShape showButton(sf::Vector2f(200, 50));
    showButton.setFillColor(sf::Color::Blue);
    showButton.setPosition(220, 500);

    sf::Text showButtonText("Show Tranzactions", font, 20);
    showButtonText.setPosition(230, 510);

    sf::RectangleShape showRBTreeButton(sf::Vector2f(200, 50));
    showRBTreeButton.setFillColor(sf::Color::Red);
    showRBTreeButton.setPosition(430, 500);

    sf::Text showRBTreeButtonText("Show RBTree", font, 20);
    showRBTreeButtonText.setPosition(440, 510);

    // Application state
    AppState currentState = AppState::Main;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Check for button clicks
            if (event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                // Check if the "Add Tranzactie" button is clicked
                if (addButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    // Switch to AddTranzactie state
                    currentState = AppState::AddTranzactie;
                }

                // Check if the "Show Tranzactions" button is clicked
                if (showButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    // Switch to ShowTranzactions state
                    currentState = AppState::ShowTranzactions;
                }

                // Check if the "Show RBTree" button is clicked
                if (showRBTreeButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    // Switch to ShowRBTree state
                    currentState = AppState::ShowRBTree;
                }
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw buttons based on the current state
        switch (currentState) {
            case AppState::Main:
                drawButton(window, addButtonText, addButton);
                drawButton(window, showButtonText, showButton);
                drawButton(window, showRBTreeButtonText, showRBTreeButton);
                break;

            case AppState::AddTranzactie: {
    // Text input fields
    sf::Text dateText("Date (DD.MM.YYYY): ", font, 15);
    dateText.setPosition(10, 100);

    sf::Text tipText("Tip (intrare/iesire): ", font, 15);
    tipText.setPosition(10, 150);

    sf::Text sumaText("Suma: ", font, 15);
    sumaText.setPosition(10, 200);

    sf::Text descriereText("Descriere: ", font, 15);
    descriereText.setPosition(10, 250);

    // Add a "Back to Menu" button
    sf::RectangleShape backButton(sf::Vector2f(200, 50));
    backButton.setFillColor(sf::Color::Yellow);
    backButton.setPosition(10, 300);

    sf::Text backButtonText("Back to Menu", font, 20);
    backButtonText.setPosition(20, 310);

    // Add a "Add Tranzactie" button
    sf::RectangleShape addTranzactieButton(sf::Vector2f(200, 50));
    addTranzactieButton.setFillColor(sf::Color::Green);
    addTranzactieButton.setPosition(220, 300);

    sf::Text addTranzactieButtonText("Add Tranzactie", font, 20);
    addTranzactieButtonText.setPosition(230, 310);

    // Initialize textboxes
    sf::Text dateInputText("", font, 15);
    dateInputText.setPosition(200, 100);

    sf::Text tipInputText("", font, 15);
    tipInputText.setPosition(200, 150);

    sf::Text sumaInputText("", font, 15);
    sumaInputText.setPosition(200, 200);

    sf::Text descriereInputText("", font, 15);
    descriereInputText.setPosition(200, 250);

    // Draw text input fields
    window.draw(dateText);
    window.draw(tipText);
    window.draw(sumaText);
    window.draw(descriereText);

    window.draw(dateInputText);
    window.draw(tipInputText);
    window.draw(sumaInputText);
    window.draw(descriereInputText);

    // Draw buttons
    drawButton(window, backButtonText, backButton);
    drawButton(window, addTranzactieButtonText, addTranzactieButton);

    // Handle events
    sf::Event event;
    sf::Text* activeTextBox = nullptr;  // Declare activeTextBox here
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonReleased) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            // Check if the "Back to Menu" button is clicked
            if (isButtonClicked(backButton, mousePosition)) {
                currentState = AppState::Main;
            } else if (isButtonClicked(addTranzactieButton, mousePosition)) {
                // Handle "Add Tranzactie" button click
                Date d;
                int zi, luna, an;
                char dot;
                stringstream ss(dateInputText.getString());
                ss >> zi >> dot >> luna >> dot >> an;
                d.setZi(zi);
                d.setLuna(luna);
                d.setAn(an);

                TipTranzactie tip;
                if (tipInputText.getString() == "intrare")
                    tip = intrare;
                else
                    tip = iesire;
                Tranzactie tranzactie(d, tip, sumaInputText.getString(), descriereInputText.getString());
                TransilvaniaTranzactii.insert(tranzactie);
                Transilvania.adaugaTranzactie(tranzactie);
                currentState = AppState::Main;
            }
        } else if (event.type == sf::Event::TextEntered) {
            // Handle text input
            if (event.text.unicode == 8 && activeTextBox->getString().getSize() > 0) {
                // Handle backspace
                activeTextBox->setString(activeTextBox->getString().substring(0, activeTextBox->getString().getSize() - 1));
            } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                // Handle printable characters
                activeTextBox->setString(activeTextBox->getString() + static_cast<char>(event.text.unicode));
            }
        }

        // Check if any of the text boxes are clicked
        if (dateInputText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            activeTextBox = &dateInputText;
        } else if (tipInputText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            activeTextBox = &tipInputText;
        } else if (sumaInputText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            activeTextBox = &sumaInputText;
        } else if (descriereInputText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            activeTextBox = &descriereInputText;
        } else {
            activeTextBox = nullptr;
        }
    }

    // Display the contents of the window
    window.display();
}
break;




                




            case AppState::ShowTranzactions: {
    // Set the background color to black
    window.clear(sf::Color::Black);

    // Add a "Back to Menu" button
    sf::RectangleShape backButton(sf::Vector2f(200, 50));
    backButton.setFillColor(sf::Color::Yellow);
    backButton.setPosition(490, 500);

    sf::Text backButtonText("Back to Menu", font, 20);
    backButtonText.setPosition(500, 510);

    // Draw buttons
    drawButton(window, backButtonText, backButton);

    // Draw Tranzactions
    int visibleTransactions = 5; // Number of transactions visible at a time
    int totalTransactions = Transilvania.getTranzactii().size();
    int startIndex = 0; // Index of the first visible transaction

    sf::Event event;
while (window.isOpen() ) {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonReleased) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            // Check if the "Back to Menu" button is clicked
            if (isButtonClicked(backButton, mousePosition)) {
                currentState = AppState::Main; // Go back to the main menu
                break;
            }
        } else if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                // Scroll up
                if (event.mouseWheelScroll.delta > 0 && startIndex > 0) {
                    startIndex--;
                }
                // Scroll down
                else if (event.mouseWheelScroll.delta < 0 && startIndex + visibleTransactions < totalTransactions) {
                    startIndex++;
                }
            }
        }
    }

    // Set the background color to black
    window.clear(sf::Color::Black);

    // Draw buttons
    drawButton(window, backButtonText, backButton);

    // Draw Tranzactions
    for (int i = startIndex; i < std::min(startIndex + visibleTransactions, totalTransactions); i++) {
        std::ostringstream details;
        details << "Data: " << Transilvania.getTranzactii()[i].getData() << "\n";
        details << "Tip: " << (Transilvania.getTranzactii()[i].getTip() == TipTranzactie::intrare ? "Intrare" : "Iesire") << "\n";
        details << "Suma: " << Transilvania.getTranzactii()[i].getSuma() << "\n";
        details << "Descriere: " << Transilvania.getTranzactii()[i].getDescriere() << "\n";

        sf::Text tranzactieText(details.str(), font, 15);
        tranzactieText.setPosition(10, 100 * (i - startIndex) + 80);
        window.draw(tranzactieText);
    }

    // Display the contents of the window
    window.display();
}
            }
break;






           case AppState::ShowRBTree: {
    // Set the background color to black
    window.clear(sf::Color::Black);

    // Draw the Red-Black Tree
    drawRBTree(window, root, font, /* specify other parameters */);

    // Add a "Back to Menu" button
    sf::RectangleShape backButton(sf::Vector2f(200, 50));
    backButton.setFillColor(sf::Color::Yellow);
    backButton.setPosition(490, 500);

    sf::Text backButtonText("Back to Menu", font, 20);
    backButtonText.setPosition(500, 510);

    // Draw buttons
    drawButton(window, backButtonText, backButton);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        // Check if the "Back to Menu" button is clicked
        if (isButtonClicked(backButton, mousePosition)) {
            currentState = AppState::Main;
        }
    }
    break;
}





        // Display the contents of the window
        window.display();
    }

    return EXIT_SUCCESS;
}
