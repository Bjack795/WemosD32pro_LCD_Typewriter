// Adjust the following values to match your needs
// -----------------------------------------------
#define   servername "fileserver"  // Set your server's logical name here e.g. if 'myserver' then address is http://myserver.local/
//#define local_IP "192.168.188.24"
IPAddress local_IP(192, 168, 188, 14); // Set your server's fixed IP address here (modificato)
IPAddress gateway(192, 168, 188, 1);    // Set your network Gateway usually your Router base address (modificato)
IPAddress subnet(255, 255, 255, 0);   // Set your network sub-network mask here
IPAddress dns(192,168,188,1);           // Set your network DNS usually your Router base address(modificato)
const char ssid_1[]     = "FRITZ!Box 7490";
const char password_1[] = "4e6b6666";

const char ssid_2[]     = "your_SSID2";
const char password_2[] = "your_PASSWORD_for SSID2";

const char ssid_3[]     = "your_SSID3";
const char password_3[] = "your_PASSWORD_for SSID3";

const char ssid_4[]     = "your_SSID4";
const char password_4[] = "your_PASSWORD_for SSID4";


