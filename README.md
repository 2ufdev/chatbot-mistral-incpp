# Mistral AI Chatbot

A simple C++ console-based chatbot that interacts with the Mistral AI API to provide responses to user inputs. This application is specifically designed to use the Mistral AI API for generating conversational responses, with UTF-8 support, console styling, and anti-capture protection for the console window.

## Features
- Sends user input to the Mistral AI API and displays responses.
- Supports UTF-8 encoding for multilingual input and output.
- Configures console window to prevent resizing/maximizing.
- Implements anti-capture protection for the console.

## Prerequisites
- Windows operating system
- C++ compiler (e.g., MSVC, MinGW)
- [libcurl](https://curl.se/libcurl/) library
- [nlohmann/json](https://github.com/nlohmann/json) library
- Dwmapi.lib (included with Windows SDK)
  
## Dependencies
- **libcurl**: For making HTTP requests to the Mistral AI API.
- **nlohmann/json**: For JSON parsing and creation.
- **Windows API**: For console styling and anti-capture functionality.

## Notes
- Replace the `api_key` in the code with your own Mistral AI API key, obtainable from [Mistral AI](https://mistral.ai/).
- The application is designed for Windows due to the use of `Dwmapi.lib` and Windows-specific console functions.
- Ensure your system supports UTF-8 encoding for proper text display.

# Credit FauZaPespi
- for the idea bypass screenshare
- [FauZaPespi](https://github.com/fauzapespi)

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
