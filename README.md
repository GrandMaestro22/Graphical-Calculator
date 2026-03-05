# Graphical-Calculator

Welcome to our dual-mode scientific calculator! Whether you're a terminal purist or prefer clickable buttons, we've got you covered with both a command-line and graphical interface.

## What's Included

### 📱 Console Version (`calculator.cc`)
A straightforward terminal-based calculator that runs in a loop, letting you keep calculating without restarting. It's lightweight, fast, and perfect if you love the command line.

**Features:**
- Basic arithmetic: `+`, `-`, `*`, `/`, `%` (modulo)
- Power function: `^`
- Scientific functions: `sin`, `cos`, `tan`, `√` (square root)
- Division by zero protection (we're not monsters)
- Continuous calculation loop (ask if you want to keep going)

### 🖱️ GUI Version (`calculator_gui.cc`)
A proper graphical interface built with SFML. Click buttons, see results in real-time, and enjoy a more traditional calculator experience.

**Features:**
- All of the above (arithmetic + scientific)
- Responsive button-based interface
- Clean display showing your current calculation
- Easy decimal point handling
- Clear button to reset and start fresh

## Getting Started

### Prerequisites

**For Console Version:**
- A C++ compiler (g++, clang, MSVC, etc.)
- That's it! No external dependencies.

**For GUI Version:**
- A C++ compiler
- SFML library (Simple and Fast Multimedia Library)

### Installing SFML

Don't worry—it's easier than you'd think.

#### Windows
1. Download the pre-built binaries from [sfml-dev.org](https://www.sfml-dev.org/download.php)
2. Extract to a location (e.g., `C:\SFML-2.6.0`)
3. Note the path—you'll need it for compilation

#### macOS
```bash
brew install sfml
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get install libsfml-dev
```

## Compilation

### Console Calculator
Super simple:
```bash
g++ calculator.cc -o calculator -std=c++11
```

Or if you're using MSVC:
```bash
cl calculator.cc
```

### GUI Calculator

#### Linux/macOS
```bash
g++ calculator_gui.cc -o calculator_gui -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system
```

#### Windows (with MinGW)
```bash
g++ calculator_gui.cc -o calculator_gui.exe -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system
```

#### Windows (if SFML isn't in system PATH)
```bash
g++ calculator_gui.cc -o calculator_gui.exe -std=c++17 -I"C:\SFML-2.6.0\include" -L"C:\SFML-2.6.0\lib" -lsfml-graphics -lsfml-window -lsfml-system
```

Replace the path with wherever you installed SFML.

#### Windows (with MSVC)
```bash
cl calculator_gui.cc /I"C:\SFML-2.6.0\include" /link /LIBPATH:"C:\SFML-2.6.0\lib" sfml-graphics.lib sfml-window.lib sfml-system.lib
```

## Running the Programs

### Console Version
```bash
./calculator
```
or on Windows:
```bash
calculator.exe
```

Then just follow the on-screen prompts. Enter numbers, pick an operation, and it'll keep asking if you want to calculate again.

### GUI Version
```bash
./calculator_gui
```
or on Windows:
```bash
calculator_gui.exe
```

A window will pop up with a beautiful calculator interface. Click away!

## Usage Examples

### Console
```
Enter first number: 15
Enter operator: +
Enter second number: 27
Result: 42
Do you want to calculate another expression? (y/n): y
```

### GUI
Click the buttons to enter values, operations, and calculations. It's intuitive—like a real calculator!

## Troubleshooting

**"Font not found" error on GUI?**
- The program looks for `arial.ttf` at `C:\Windows\Fonts\arial.ttf` on Windows
- On other systems, you might need to update the font path in the code
- Feel free to reach out if you need help adjusting it

**Compilation errors with SFML?**
- Make sure SFML is properly installed
- Double-check the library linking flags (`-lsfml-graphics`, etc.)
- Verify the include paths if using custom SFML locations

**The calculator feels sluggish?**
- Try updating your graphics drivers (for GUI version)
- The console version is lightning-fast by design

## Future Improvements

- ✨ Memory functions (M+, M-, MR, MC)
- 📊 Graphical expression history
- ⌨️ Keyboard input for GUI version
- 🎨 Customizable themes
- 📐 Additional scientific functions (factorials, permutations, etc.)

## License

Feel free to use, modify, and distribute as you wish. It's just a calculator! 🧮

---

Questions or want to contribute? Feel free to reach out!
