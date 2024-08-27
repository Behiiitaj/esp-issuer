#include <WiFiClientSecure.h>
#include <HTTPClient.h>

const char* githubApiHost = "api.github.com"; // GitHub API host
const char* githubApiPath = "/repos/OWNER/REPO/issues"; // Replace with your repo details
const char* githubToken = "your_github_token";  // Replace with your GitHub token

const char* wifi_ssid = "your_SSID";
const char* wifi_pass = "your_PASSWORD";

void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_pass);

  log_i("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED){
    log_i(".");
    delay(100);
  }
  log_i("local ip: %s", (WiFi.localIP().toString()).c_str());

  WiFiClientSecure client;
  client.setInsecure();

  log_i("Connecting to ");
  log_i("%s",githubApiHost);

  if (!client.connect(githubApiHost, 443)) {
    log_i("Connection failed!");
    return;
  }

  // Create the JSON payload
  String jsonPayload = R"({
    "title": "Found a bug",
    "body": "I'm having a problem with this.",
    "labels": ["bug"]
  })";

  // Send the HTTP POST request
  client.print(String("POST ") + githubApiPath + " HTTP/1.1\r\n" +
               "Host: " + githubApiHost + "\r\n" +
               "Accept: application/vnd.github+json\r\n" +
               "Authorization: Bearer " + githubToken + "\r\n" +
               "X-GitHub-Api-Version: 2022-11-28\r\n" +
               "Content-Type: application/json\r\n" +
               "Content-Length: " + String(jsonPayload.length()) + "\r\n" +
               "User-Agent: ESP32/1.0\r\n" +
               "Connection: close\r\n\r\n" +  
               jsonPayload);

  // Wait for the response
  log_i("Sending request...");
  while (client.connected() || client.available()) {
    if (client.available()) {
      String line = client.readStringUntil('\n');
      log_i("%s",line.c_str());
      if (line == "\r") {
        log_i("Headers received");
        break;
      }
    }
  }

  // Print the response
  log_i("Reply was:");
  String line;
  while (client.available()) {
    line = client.readStringUntil('\n');
    log_i("%s",line.c_str());
  }
  log_i("Closing connection");
}

void loop() { vTaskDelay(1000); }
