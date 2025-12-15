/*
 * Smart Lighting Control System
 * نظام التحكم الذكي بالإضاءة
 * 
 * تاريخ الإنشاء: ديسمبر 2025
 * المطور: Youcef
 * 
 * الوصف: نظام تحكم ذكي بالإضاءة يدعم وضعين:
 * - الوضع التلقائي: بناءً على مستشعر الضوء
 * - الوضع اليدوي: التحكم عن بعد عبر Firebase
 */

#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "config.h"

// متغيرات Firebase
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// متغيرات التوقيت
unsigned long sendDataPrevMillis = 0;
const unsigned long UPDATE_INTERVAL = 1000; // التحديث كل ثانية

// متغيرات المستشعرات والتحكم
int nivosvjetlosti = 0;      // مستوى الإضاءة اليدوي
int senzor = 0;              // قراءة المستشعر
int granica = 500;           // الحد الفاصل (القيمة الافتراضية)
bool automatski = true;      // الوضع التلقائي (افتراضياً)
bool signupOK = false;       // حالة الاتصال بـ Firebase

// دالة الإعداد الأولي
void setup() {
  // إعداد المنافذ
  pinMode(D1, OUTPUT);       // منفذ التحكم بالإضاءة
  pinMode(A0, INPUT);        // منفذ مستشعر الضوء
  
  // بدء الاتصال التسلسلي
  Serial.begin(115200);
  Serial.println("\n\n=================================");
  Serial.println("Smart Lighting Control System");
  Serial.println("نظام التحكم الذكي بالإضاءة");
  Serial.println("December 2025");
  Serial.println("=================================\n");
  
  // الاتصال بشبكة WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    Serial.print(".");
    delay(500);
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✓ WiFi Connected Successfully!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Signal Strength: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm\n");
  } else {
    Serial.println("\n✗ WiFi Connection Failed!");
    Serial.println("Please check your credentials in config.h");
    return;
  }

  // إعداد Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Serial.println("Connecting to Firebase...");
  
  // تسجيل الدخول إلى Firebase (Anonymous)
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("✓ Firebase Connected Successfully!\n");
    signupOK = true;
  }
  else {
    Serial.printf("✗ Firebase Connection Failed!\n");
    Serial.printf("Error: %s\n\n", config.signer.signupError.message.c_str());
  }

  // تعيين دالة callback للتحقق من التوكن
  config.token_status_callback = tokenStatusCallback;
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
  Serial.println("System Initialized Successfully!");
  Serial.println("=================================\n");
}

// الحلقة الرئيسية
void loop() {
  // التحقق من جاهزية Firebase والتحديث كل ثانية
  if (Firebase.ready() && signupOK && 
      (millis() - sendDataPrevMillis > UPDATE_INTERVAL || sendDataPrevMillis == 0)) {
    
    sendDataPrevMillis = millis();
    
    // قراءة حالة الوضع التلقائي من Firebase
    if (Firebase.RTDB.getBool(&fbdo, "/rasvjeta/automatski")) {   
      if (fbdo.dataType() == "boolean") {
        automatski = fbdo.boolData();
        Serial.print("Mode: ");
        Serial.println(automatski ? "AUTOMATIC" : "MANUAL");
      }
    }
    else {
      Serial.print("Error reading mode: ");
      Serial.println(fbdo.errorReason());
    }
    
    // الوضع التلقائي
    if (automatski) {
      handleAutomaticMode();
    }
    // الوضع اليدوي
    else {
      handleManualMode();
    }
    
    Serial.println("---");
  }
}

// دالة معالجة الوضع التلقائي
void handleAutomaticMode() {
  // قراءة قيمة المستشعر
  senzor = analogRead(A0);
  Serial.print("Sensor Reading: ");
  Serial.println(senzor);
  
  // رفع قيمة المستشعر إلى Firebase
  if (Firebase.RTDB.setInt(&fbdo, "rasvjeta/senzor", senzor)) {
    Serial.println("✓ Sensor data uploaded");
  }
  else {
    Serial.print("✗ Upload failed: ");
    Serial.println(fbdo.errorReason());
  }
  
  // قراءة قيمة الحد الفاصل من Firebase
  if (Firebase.RTDB.getInt(&fbdo, "/rasvjeta/granica")) {
    if (fbdo.dataType() == "int") {
      granica = fbdo.intData();
      Serial.print("Threshold: ");
      Serial.println(granica);
    }
  }
  else {
    Serial.print("Error reading threshold: ");
    Serial.println(fbdo.errorReason());
  }
  
  // التحكم بالإضاءة بناءً على المستشعر
  if (senzor < granica) {
    analogWrite(D1, 255);
    Serial.println("💡 Light: ON (Full brightness)");
  }
  else {
    analogWrite(D1, 0);
    Serial.println("💡 Light: OFF");
  }
}

// دالة معالجة الوضع اليدوي
void handleManualMode() {
  // قراءة مستوى الإضاءة من Firebase
  if (Firebase.RTDB.getInt(&fbdo, "/rasvjeta/nivosvjetlosti")) {
    if (fbdo.dataType() == "int") {
      nivosvjetlosti = fbdo.intData();
      
      // التأكد من أن القيمة ضمن النطاق الصحيح (0-255)
      nivosvjetlosti = constrain(nivosvjetlosti, 0, 255);
      
      analogWrite(D1, nivosvjetlosti);
      
      Serial.print("💡 Light Level: ");
      Serial.print(nivosvjetlosti);
      Serial.print("/255 (");
      Serial.print(map(nivosvjetlosti, 0, 255, 0, 100));
      Serial.println("%)");
    }
  }
  else {
    Serial.print("Error reading light level: ");
    Serial.println(fbdo.errorReason());
  }
}
