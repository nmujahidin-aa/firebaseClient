/**
 * This example is for new users who are familiar with other legacy Firebase libraries.
 * It shows how to set, push, and get values to/from Realtime Database.
 * All functions in this example are blocking (synchronous).
 *
 * This example is for ESP32, ESP8266, and Raspberry Pi Pico W.
 * You can adapt the WiFi and SSL client library for your devices.
 */

/** Change your Realtime database security rules as follows:
{
  "rules": {
    ".read": true,
    ".write": true
  }
}
*/

#include <Arduino.h>
#if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <FirebaseClient.h>
#include <WiFiClientSecure.h>

#define WIFI_SSID "poco"
#define WIFI_PASSWORD "123456789"

#define DATABASE_URL "https://trans-sibi-default-rtdb.firebaseio.com/"

WiFiClientSecure ssl;
DefaultNetwork network;
AsyncClientClass client(ssl, getNetwork(network));

FirebaseApp app;
RealtimeDatabase Database;
AsyncResult result;
NoAuth noAuth;

void printError(int code, const String &msg)
{
    Firebase.printf("Error, msg: %s, code: %d\n", msg.c_str(), code);
}

void setup()
{
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Firebase.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);

    ssl.setInsecure();
#if defined(ESP8266)
    ssl.setBufferSizes(1024, 1024);
#endif

    // Initialize the authentication handler.
    initializeApp(client, app, getAuth(noAuth));

    // Binding the authentication handler with your Database class object.
    app.getApp<RealtimeDatabase>(Database);

    // Set your database URL
    Database.url(DATABASE_URL);

    // In sync functions, we have to set the operating result for the client that works with the function.
    client.setAsyncResult(result);

    // Set, push and get integer value

    Serial.print("Set int... ");
    bool status = Database.set<int>(client, "/test/int", 12345);
    if (status)
        Serial.println("ok");
    else
        printError(client.lastError().code(), client.lastError().message());

    Serial.print("Push int... ");
    String name1 = Database.push<int>(client, "/test/push", 12345);
    if (client.lastError().code() == 0)
        Firebase.printf("ok, name: %s\n", name1.c_str());
    else
        printError(client.lastError().code(), client.lastError().message());

    Serial.print("Get int... ");
    int v1 = Database.get<int>(client, "/test/int");
    if (client.lastError().code() == 0)
        Serial.println(v1);
    else
        printError(client.lastError().code(), client.lastError().message());

    // Set, push and get Boolean value

    Serial.print("Set bool... ");
    status = Database.set<bool>(client, "/test/bool", true);
    if (status)
        Serial.println("ok");
    else
        printError(client.lastError().code(), client.lastError().message());

    Serial.print("Push bool... ");
    String name2 = Database.push<bool>(client, "/test/push", true);
    if (client.lastError().code() == 0)
        Firebase.printf("ok, name: %s\n", name2.c_str());

    Serial.print("Get bool... ");
    bool v2 = Database.get<bool>(client, "/test/bool");
    if (client.lastError().code() == 0)
        Serial.println(v2);
    else
        printError(client.lastError().code(), client.lastError().message());

    // Set, push, and get String value

    Serial.print("Set string... ");
    status = Database.set<String>(client, "/test/string", "hello");
    if (status)
        Serial.println("ok");
    else
        printError(client.lastError().code(), client.lastError().message());

    Serial.print("Push String... ");
    String name3 = Database.push<String>(client, "/test/push", "hello");
    if (client.lastError().code() == 0)
        Firebase.printf("ok, name: %s\n", name3.c_str());

    Serial.print("Get string... ");
    String v3 = Database.get<String>(client, "/test/string");
    if (client.lastError().code() == 0)
        Serial.println(v3);
    else
        printError(client.lastError().code(), client.lastError().message());

    // Set, push, and get float value

    Serial.print("Set float... ");
    status = Database.set<number_t>(client, "/test/float", number_t(123.456, 2));
    if (status)
        Serial.println("ok");
    else
        printError(client.lastError().code(), client.lastError().message());

    Serial.print("Push float... ");
    String name4 = Database.push<number_t>(client, "/test/push", number_t(123.456, 2));
    if (client.lastError().code() == 0)
        Firebase.printf("ok, name: %s\n", name4.c_str());

    Serial.print("Get float... ");
    float v4 = Database.get<float>(client, "/test/float");
    if (client.lastError().code() == 0)
        Serial.println(v4);
    else
        printError(client.lastError().code(), client.lastError().message());

    // Set, push, and get double value

    Serial.print("Set double... ");
    status = Database.set<number_t>(client, "/test/double", number_t(1234.56789, 4));
    if (status)
        Serial.println("ok");
    else
        printError(client.lastError().code(), client.lastError().message());

    Serial.print("Push double... ");
    String name5 = Database.push<number_t>(client, "/test/push", number_t(1234.56789, 4));
    if (client.lastError().code() == 0)
        Firebase.printf("ok, name: %s\n", name5.c_str());

    Serial.print("Get double... ");
    double v5 = Database.get<double>(client, "/test/double");
    if (client.lastError().code() == 0)
        Serial.println(v5);
    else
        printError(client.lastError().code(), client.lastError().message());

    // Set, push, and get JSON value

    Serial.print("Set JSON... ");
    status = Database.set<object_t>(client, "/test/json", object_t("{\"test\":{\"data\":123}}"));
    if (status)
        Serial.println("ok");
    else
        printError(client.lastError().code(), client.lastError().message());

    Serial.print("Push JSON... ");
    String name6 = Database.push<object_t>(client, "/test/push", object_t("{\"test\":{\"data\":123}}"));
    if (client.lastError().code() == 0)
        Firebase.printf("ok, name: %s\n", name6.c_str());

    Serial.print("Get JSON... ");
    String v6 = Database.get<String>(client, "/test/json");
    if (client.lastError().code() == 0)
        Serial.println(v6);
    else
        printError(client.lastError().code(), client.lastError().message());

    // Set, push and get Array value

    Serial.print("Set Array... ");
    status = Database.set<object_t>(client, "/test/array", object_t("[1,2,\"test\",true]"));
    if (status)
        Serial.println("ok");
    else
        printError(client.lastError().code(), client.lastError().message());

    Serial.print("Push Array... ");
    String name7 = Database.push<object_t>(client, "/test/push", object_t("[1,2,\"test\",true]"));
    if (client.lastError().code() == 0)
        Firebase.printf("ok, name: %s\n", name7.c_str());

    Serial.print("Get Array... ");
    String v7 = Database.get<String>(client, "/test/array");
    if (client.lastError().code() == 0)
        Serial.println(v7);
    else
        printError(client.lastError().code(), client.lastError().message());
}

void loop()
{
    // No polling required for async tasks in this example as we're using sync functions.
}
