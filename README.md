# ESP32 GitHub Issue Creator via HTTP POST

This project demonstrates how to use an ESP32 microcontroller with PlatformIO to create an issue in a GitHub repository by sending a POST request to the GitHub API. The example code shows how to establish a secure HTTPS connection with GitHub's API using `WiFiClientSecure` and includes the necessary headers and payload structure for successful communication.

## Features

- Connects the ESP32 to a Wi-Fi network.
- Establishes a secure HTTPS connection to the GitHub API.
- Sends a POST request with JSON payload to create a new issue.
- Configurable headers, including `Authorization` and `User-Agent`.
- Suitable for IoT projects that require interaction with GitHub for issue tracking or automation.

## Prerequisites

Before using this code, ensure you have the following:

- **ESP32 microcontroller**
- **PlatformIO** (installed as a plugin for Visual Studio Code or as a standalone IDE)
- **GitHub personal access token** with permission to create issues
- **Wi-Fi network credentials** (SSID and password)

## Installation

1. **Clone the repository** to your local machine:

    ```sh
    git clone https://github.com/your-username/esp32-github-issue-creator.git
    ```

2. **Navigate to the project directory:**

    ```sh
    cd esp-issuer
    ```

3. **Open the project in PlatformIO:**

    - If using Visual Studio Code, open the folder with PlatformIO.
    - If using PlatformIO IDE, open the project directory.

4. **Update the following placeholders in `src/main.cpp` with your information:**

    - `your_SSID` and `your_PASSWORD`: Your Wi-Fi network credentials.
    - `your_github_token`: Your GitHub personal access token.
    - `OWNER` and `REPO`: The GitHub repository owner and name.

5. **Build and upload the code to your ESP32:**

    - Use the PlatformIO toolbar or commands to build and upload the code.

## Usage

After uploading the code, the ESP32 will:

1. Connect to the specified Wi-Fi network.
2. Establish a secure connection to the GitHub API.
3. Send a POST request to create a new issue in the specified repository.

### Example Request

The code sends a POST request to the following URL with the provided headers:

```cpp
client.print(String("POST ") + githubApiPath + " HTTP/1.1\r\n" +
             "Host: " + githubApiHost + "\r\n" +
             "Accept: application/vnd.github+json\r\n"+
             "Authorization: Bearer " + githubToken + "\r\n" +
             "X-GitHub-Api-Version: 2022-11-28\r\n" +
             "Content-Type: application/json\r\n" +
             "Content-Length: " + String(jsonPayload.length()) + "\r\n" +
             "User-Agent: ESP32/1.0\r\n" +
             "Connection: close\r\n\r\n" +
             jsonPayload);
