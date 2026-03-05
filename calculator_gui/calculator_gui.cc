#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Calculator {
private:
    string display;
    double firstNum;
    double secondNum;
    char operation;
    bool hasOperation;
    bool resultDisplayed;

public:
    Calculator() : display("0"), firstNum(0), secondNum(0), operation('\0'), 
                   hasOperation(false), resultDisplayed(false) {}

    void appendDigit(char digit) {
        if (resultDisplayed) {
            display = "";
            resultDisplayed = false;
        }
        if (display == "0") {
            display = digit;
        } else {
            display += digit;
        }
    }

    void appendDecimal() {
        if (display.find('.') == string::npos) {
            display += '.';
        }
    }

    void setOperation(char op) {
        if (!hasOperation) {
            firstNum = stod(display);
            hasOperation = true;
            operation = op;
            display = "0";
        }
    }

    void calculate() {
        if (!hasOperation) return;

        secondNum = stod(display);
        double result = 0;

        switch (operation) {
            case '+': result = firstNum + secondNum; break;
            case '-': result = firstNum - secondNum; break;
            case '*': result = firstNum * secondNum; break;
            case '/': 
                if (secondNum == 0) {
                    display = "Error: Div by 0";
                    return;
                }
                result = firstNum / secondNum; 
                break;
            case '^': result = pow(firstNum, secondNum); break;
            case '%': result = (int)firstNum % (int)secondNum; break;
        }

        display = to_string(result);
        // Remove trailing zeros after decimal
        if (display.find('.') != string::npos) {
            display.erase(display.find_last_not_of('0') + 1, string::npos);
            if (display.back() == '.') display.pop_back();
        }

        hasOperation = false;
        resultDisplayed = true;
    }

    void applyScientific(char func) {
        double num = stod(display);
        double result = 0;

        switch (func) {
            case 's': result = sin(num); break;  // sin
            case 'c': result = cos(num); break;  // cos
            case 't': result = tan(num); break;  // tan
            case 'q':  // sqrt
                if (num < 0) {
                    display = "Error: Negative sqrt";
                    return;
                }
                result = sqrt(num);
                break;
            case 'l': result = log10(num); break;  // log base 10
            case 'n': result = log(num); break;    // natural log
        }

        display = to_string(result);
        if (display.find('.') != string::npos) {
            display.erase(display.find_last_not_of('0') + 1, string::npos);
            if (display.back() == '.') display.pop_back();
        }
        hasOperation = false;
        resultDisplayed = true;
    }

    void clear() {
        display = "0";
        firstNum = 0;
        secondNum = 0;
        operation = '\0';
        hasOperation = false;
        resultDisplayed = false;
    }

    string getDisplay() const {
        return display;
    }
};

class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;
    string label;
    bool isPressed;

    Button() : isPressed(false) {}

    void init(float x, float y, float width, float height, const string& lbl, 
              const sf::Font& font, unsigned int charSize) {
        label = lbl;
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(sf::Color(200, 200, 200));
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2);

        text.setFont(font);
        text.setString(lbl);
        text.setCharacterSize(charSize);
        text.setFillColor(sf::Color::Black);

        // Center text on button
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            x + (width - textBounds.width) / 2,
            y + (height - textBounds.height) / 2 - 5
        );
    }

    bool isClicked(sf::Vector2f mousePos) const {
        return shape.getGlobalBounds().contains(mousePos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }
};

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(500, 700), "Scientific Calculator");
    window.setFramerateLimit(60);

    // Load font (using default system font path on Windows)
    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        cerr << "Error loading font. Make sure arial.ttf is available.\n";
        return -1;
    }

    Calculator calc;

    // Display text
    sf::Text displayText;
    displayText.setFont(font);
    displayText.setCharacterSize(40);
    displayText.setFillColor(sf::Color::Black);
    displayText.setPosition(20, 30);

    // Display background
    sf::RectangleShape displayBg(sf::Vector2f(460, 80));
    displayBg.setPosition(20, 20);
    displayBg.setFillColor(sf::Color(230, 230, 230));
    displayBg.setOutlineColor(sf::Color::Black);
    displayBg.setOutlineThickness(2);

    // Create buttons
    vector<Button> buttons;
    
    // Number buttons (3x4 grid)
    vector<string> numberLabels = {"7", "8", "9", "4", "5", "6", "1", "2", "3", "0"};
    int idx = 0;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 3; col++) {
            if (idx < 10) {
                Button btn;
                btn.init(20 + col * 110, 150 + row * 70, 100, 60, 
                        numberLabels[idx], font, 24);
                buttons.push_back(btn);
                idx++;
            }
        }
    }

    // Operation buttons
    vector<string> opLabels = {"+", "-", "*", "/", "^", "%", "=", "C"};
    vector<pair<float, float>> opPositions = {
        {350, 150}, {350, 220}, {350, 290}, {350, 360}, {350, 430},
        {350, 500}, {230, 500}, {20, 500}
    };

    for (size_t i = 0; i < opLabels.size(); i++) {
        Button btn;
        btn.init(opPositions[i].first, opPositions[i].second, 100, 60, 
                opLabels[i], font, 24);
        buttons.push_back(btn);
    }

    // Scientific buttons
    vector<string> sciLabels = {"sin", "cos", "tan", "√", "log", "ln"};
    vector<pair<float, float>> sciPositions = {
        {20, 570}, {130, 570}, {240, 570}, {350, 570}, {20, 630}, {130, 630}
    };

    for (size_t i = 0; i < sciLabels.size(); i++) {
        Button btn;
        btn.init(sciPositions[i].first, sciPositions[i].second, 100, 50, 
                sciLabels[i], font, 18);
        buttons.push_back(btn);
    }

    // Decimal button
    Button decimalBtn;
    decimalBtn.init(240, 500, 100, 60, ".", font, 24);
    buttons.push_back(decimalBtn);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                // Check number buttons (0-9)
                for (int i = 0; i < 10; i++) {
                    if (buttons[i].isClicked(mousePos)) {
                        calc.appendDigit('0' + i);
                    }
                }

                // Decimal button
                if (buttons[28].isClicked(mousePos)) {
                    calc.appendDecimal();
                }

                // Operation buttons: +, -, *, /, ^, %, =, C
                if (buttons[10].isClicked(mousePos)) calc.setOperation('+');
                if (buttons[11].isClicked(mousePos)) calc.setOperation('-');
                if (buttons[12].isClicked(mousePos)) calc.setOperation('*');
                if (buttons[13].isClicked(mousePos)) calc.setOperation('/');
                if (buttons[14].isClicked(mousePos)) calc.setOperation('^');
                if (buttons[15].isClicked(mousePos)) calc.setOperation('%');
                if (buttons[16].isClicked(mousePos)) calc.calculate();
                if (buttons[17].isClicked(mousePos)) calc.clear();

                // Scientific buttons: sin, cos, tan, sqrt, log, ln
                if (buttons[18].isClicked(mousePos)) calc.applyScientific('s');
                if (buttons[19].isClicked(mousePos)) calc.applyScientific('c');
                if (buttons[20].isClicked(mousePos)) calc.applyScientific('t');
                if (buttons[21].isClicked(mousePos)) calc.applyScientific('q');
                if (buttons[22].isClicked(mousePos)) calc.applyScientific('l');
                if (buttons[23].isClicked(mousePos)) calc.applyScientific('n');
            }
        }

        // Update display
        displayText.setString(calc.getDisplay());

        // Draw
        window.clear(sf::Color::White);
        window.draw(displayBg);
        window.draw(displayText);

        for (auto& btn : buttons) {
            btn.draw(window);
        }

        window.display();
    }

    return 0;
}
