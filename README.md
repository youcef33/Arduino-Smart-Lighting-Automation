#  Smart Lighting Control System
## نظام التحكم الذكي بالإضاءة

[![Arduino](https://img.shields.io/badge/Arduino-Compatible-00979D?style=flat&logo=arduino)](https://www.arduino.cc/)
[![ESP8266](https://img.shields.io/badge/ESP8266-Supported-E7352C?style=flat&logo=espressif)](https://www.espressif.com/)
[![ESP32](https://img.shields.io/badge/ESP32-Supported-E7352C?style=flat&logo=espressif)](https://www.espressif.com/)
[![Firebase](https://img.shields.io/badge/Firebase-Realtime%20DB-FFCA28?style=flat&logo=firebase)](https://firebase.google.com/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

**تاريخ المشروع:** ديسمبر 2025  
**Project Date:** December 2025

---

##  نظرة عامة | Overview

نظام تحكم ذكي بالإضاءة يعمل بواسطة **ESP8266/ESP32** ويتصل بقاعدة بيانات **Firebase Realtime Database** للتحكم عن بُعد. يدعم النظام وضعين للعمل:

A smart lighting control system powered by **ESP8266/ESP32** connected to **Firebase Realtime Database** for remote control. The system supports two operation modes:

###  الوضع التلقائي | Automatic Mode
- يعتمد على قراءات **مستشعر الضوء (LDR)**
- تشغيل/إطفاء الإضاءة بناءً على عتبة محددة
- Based on **Light Sensor (LDR)** readings
- Turns lights ON/OFF based on a threshold value

###  الوضع اليدوي | Manual Mode
- التحكم الكامل عن بُعد عبر Firebase
- ضبط مستوى الإضاءة (0-255)
- Full remote control via Firebase
- Adjust brightness level (0-255)

---

##  المميزات | Features

 **وضعان للتحكم**: تلقائي ويدوي  
 **Dual Control Modes**: Automatic and Manual

 **التحكم عن بُعد**: عبر تطبيق ويب أو موبايل  
 **Remote Control**: Via web or mobile app

 **مراقبة فورية**: قراءة بيانات المستشعر في الوقت الفعلي  
 **Real-time Monitoring**: Live sensor data reading

 **توفير الطاقة**: إضاءة ذكية حسب الحاجة  
 **Energy Saving**: Smart lighting based on needs

 **سهولة التركيب**: دليل شامل خطوة بخطوة  
 **Easy Installation**: Comprehensive step-by-step guide

---

##  المكونات المطلوبة | Required Components

| المكون | الكمية | الملاحظات |
|--------|--------|-----------|
| ESP8266 أو ESP32 | 1 | NodeMCU أو D1 Mini |
| مستشعر ضوء LDR | 1 | Light Dependent Resistor |
| LED أو مصباح | 1 | حسب الاستخدام |
| مقاومة 10kΩ | 1 | للمستشعر |
| مقاومة 220Ω | 1 | للـ LED (إذا لزم) |
| أسلاك توصيل | - | Jumper Wires |
| لوحة تجارب | 1 | Breadboard (اختياري) |

---

##  مخطط التوصيل | Circuit Diagram

```
ESP8266/ESP32          LDR Sensor          LED/Light
┌─────────────┐       ┌──────────┐       ┌─────────┐
│             │       │          │       │         │
│         A0  ├───────┤ LDR      │       │         │
│             │       │          │       │         │
│         D1  ├───────────────────────────┤  +      │
│             │       │          │       │         │
│        GND  ├───────┤ 10kΩ     │       │  -      │
│             │       └──────────┘       └─────────┘
│        3.3V ├───────┤ VCC
│             │
└─────────────┘
```

### توصيل المستشعر | Sensor Connection:
- **A0** → LDR + مقاومة 10kΩ (Voltage Divider)
- **GND** → أرضي المقاومة
- **3.3V** → الطرف الآخر للـ LDR

### توصيل الإضاءة | Light Connection:
- **D1** → LED موجب (عبر مقاومة 220Ω)
- **GND** → LED سالب

---

##  التثبيت | Installation

###  تثبيت Arduino IDE
قم بتنزيل وتثبيت Arduino IDE من الموقع الرسمي:  
Download and install Arduino IDE from:  
🔗 https://www.arduino.cc/en/software

###  إضافة دعم ESP8266/ESP32
في Arduino IDE:
1. اذهب إلى: `File` → `Preferences`
2. في "Additional Board Manager URLs" أضف:
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
https://dl.espressif.com/dl/package_esp32_index.json
```
3. اذهب إلى: `Tools` → `Board` → `Boards Manager`
4. ابحث عن "ESP8266" و "ESP32" وقم بتثبيتهما

###  تثبيت مكتبة Firebase
1. اذهب إلى: `Sketch` → `Include Library` → `Manage Libraries`
2. ابحث عن: **"Firebase ESP Client"**
3. قم بتثبيت المكتبة من Mobizt

###  إعداد Firebase

#### إنشاء مشروع Firebase:
1. اذهب إلى: https://console.firebase.google.com/
2. انقر على "Add Project" أو "إضافة مشروع"
3. أدخل اسم المشروع (مثال: `smart-lighting-system`)
4. اتبع خطوات الإعداد

#### تفعيل Realtime Database:
1. من القائمة الجانبية، اختر **"Realtime Database"**
2. انقر على **"Create Database"**
3. اختر المنطقة (مثال: `europe-west1`)
4. ابدأ في **"Test Mode"** (للتجربة)

#### الحصول على بيانات الاعتماد:
1. **API Key**: 
   - اذهب إلى `Project Settings` → `General`
   - انسخ **"Web API Key"**

2. **Database URL**:
   - من صفحة Realtime Database
   - انسخ الرابط الموجود أعلى الصفحة  
   مثال: `https://your-project.firebaseio.com/`

###  إعداد الكود

1. **استنساخ المشروع**:
```bash
git clone https://github.com/your-username/smart-lighting-system.git
cd smart-lighting-system
```

2. **إنشاء ملف الإعدادات**:
```bash
cp config.example.h config.h
```

3. **تعديل ملف config.h**:
افتح `config.h` وضع بياناتك:
```cpp
#define WIFI_SSID "اسم_شبكة_الواي_فاي"
#define WIFI_PASSWORD "كلمة_مرور_الواي_فاي"
#define API_KEY "مفتاح_API_من_Firebase"
#define DATABASE_URL "https://your-project.firebaseio.com/"
```

###  رفع الكود
1. افتح `main.ino` في Arduino IDE
2. اختر اللوحة: `Tools` → `Board` → `ESP8266` أو `ESP32`
3. اختر المنفذ: `Tools` → `Port`
4. انقر على **Upload** 

---

##  البنية في Firebase | Firebase Structure

يجب إنشاء الهيكل التالي في قاعدة بيانات Firebase:

```json
{
  "rasvjeta": {
    "automatski": true,
    "senzor": 450,
    "granica": 500,
    "nivosvjetlosti": 128
  }
}
```

### شرح الحقول | Field Descriptions:

| الحقل | النوع | الوصف | القيم |
|-------|------|-------|-------|
| **automatski** | Boolean | تفعيل/تعطيل الوضع التلقائي | `true` / `false` |
| **senzor** | Integer | قراءة المستشعر الحالية (للقراءة فقط) | 0 - 1023 |
| **granica** | Integer | العتبة للتبديل التلقائي | 0 - 1023 |
| **nivosvjetlosti** | Integer | مستوى الإضاءة اليدوي | 0 - 255 |

---

##  كيفية الاستخدام | How to Use

### الوضع التلقائي:
1. اضبط `automatski` على `true` في Firebase
2. اضبط قيمة `granica` (مثلاً: 500)
3. عندما تكون قراءة `senzor` **أقل من** `granica` → الإضاءة **تشتغل**
4. عندما تكون قراءة `senzor` **أكبر من** `granica` → الإضاءة **تنطفئ**

### الوضع اليدوي:
1. اضبط `automatski` على `false` في Firebase
2. اضبط `nivosvjetlosti` بين 0 (مطفأة) و 255 (كامل الإضاءة)
3. مثال: `nivosvjetlosti = 128` → إضاءة 50%

---

##  مراقبة النظام | System Monitoring

افتح **Serial Monitor** في Arduino IDE بسرعة `115200` لمشاهدة:

```
=================================
Smart Lighting Control System
نظام التحكم الذكي بالإضاءة
December 2025
=================================

Connecting to WiFi.....
✓ WiFi Connected Successfully!
IP Address: 192.168.1.100
Signal Strength: -45 dBm

Connecting to Firebase...
✓ Firebase Connected Successfully!

System Initialized Successfully!
=================================

Mode: AUTOMATIC
Sensor Reading: 420
✓ Sensor data uploaded
Threshold: 500
 Light: ON (Full brightness)
---
```

---

## 🔧 استكشاف الأخطاء | Troubleshooting

### لا يتصل بالواي فاي
- **تحقق من**: اسم الشبكة وكلمة المرور في `config.h`
- **تأكد**: أن الشبكة 2.4GHz (ESP8266 لا يدعم 5GHz)

###  فشل الاتصال بـ Firebase
- **تحقق من**: `API_KEY` و `DATABASE_URL`
- **تأكد**: أن قواعد الأمان في وضع "Test Mode"
- **افحص**: اتصال الإنترنت

###  المستشعر يعطي قراءات خاطئة
- **تحقق من**: توصيل LDR والمقاومة 10kΩ
- **اختبر**: بتغطية المستشعر وتعريضه للضوء
- **اضبط**: قيمة `granica` حسب الإضاءة المحيطة

###  الإضاءة لا تستجيب
- **تحقق من**: توصيل المنفذ D1
- **اختبر**: بتغيير القيمة يدوياً في Firebase
- **افحص**: الطاقة الكهربائية للمصباح

---

##  إنشاء تطبيق ويب للتحكم (اختياري)

يمكنك إنشاء واجهة ويب بسيطة للتحكم:

```html
<!DOCTYPE html>
<html>
<head>
    <title>Smart Light Control</title>
    <script src="https://www.gstatic.com/firebasejs/9.x.x/firebase-app.js"></script>
    <script src="https://www.gstatic.com/firebasejs/9.x.x/firebase-database.js"></script>
</head>
<body>
    <h1>🏠 Smart Lighting Control</h1>
    
    <label>
        <input type="checkbox" id="autoMode"> الوضع التلقائي
    </label>
    
    <div id="manualControl">
        <label>مستوى الإضاءة:</label>
        <input type="range" id="brightness" min="0" max="255" value="128">
        <span id="brightnessValue">128</span>
    </div>
    
    <div>
        <label>العتبة:</label>
        <input type="number" id="threshold" value="500">
    </div>
    
    <script>
        // Initialize Firebase
        const firebaseConfig = {
            apiKey: "YOUR_API_KEY",
            databaseURL: "YOUR_DATABASE_URL"
        };
        firebase.initializeApp(firebaseConfig);
        const db = firebase.database();
        
        // Add your control logic here
    </script>
</body>
</html>
```

---

## هيكل المشروع | Project Structure

```
smart-lighting-system/
│
├── main.ino                 # الكود الرئيسي
├── config.h                 # ملف الإعدادات (لا يُرفع)
├── config.example.h         # نموذج الإعدادات
├── .gitignore              # ملفات يتم تجاهلها في Git
├── README.md               # هذا الملف
├── LICENSE                 # رخصة MIT
│
└── docs/                   # مجلد التوثيق
    ├── circuit-diagram.png
    └── screenshots/
```

---

##  المساهمة | Contributing

المساهمات مرحب بها! إذا كنت تريد تحسين المشروع:

Contributions are welcome! If you want to improve the project:

1. Fork المشروع
2. أنشئ فرع جديد (`git checkout -b feature/amazing-feature`)
3. Commit التغييرات (`git commit -m 'Add amazing feature'`)
4. Push إلى الفرع (`git push origin feature/amazing-feature`)
5. افتح Pull Request

---

##  الترخيص | License

هذا المشروع مرخص تحت رخصة MIT - انظر ملف [LICENSE](LICENSE) للتفاصيل.

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

##  المطور | Developer

**Youcef**  
 ديسمبر 2025 | December 2025  
🇩🇿 الجزائر | Algeria

---

##  شكر وتقدير | Acknowledgments

- **Firebase** - لتوفير خدمة قاعدة البيانات المجانية
- **Espressif** - لتطوير ESP8266 و ESP32
- **Arduino Community** - للدعم والمكتبات
- **Mobizt** - لمكتبة Firebase ESP Client الرائعة

---

##  الدعم | Support

إذا واجهت أي مشكلة:  
If you encounter any issues:

- افتح [Issue](../../issues) على GitHub
- راجع قسم [Troubleshooting](#-استكشاف-الأخطاء--troubleshooting)
- تحقق من [Firebase Documentation](https://firebase.google.com/docs)

---

<div align="center">

### ⭐ إذا أعجبك المشروع، لا تنسَ إعطائه نجمة!
### ⭐ If you like this project, don't forget to give it a star!

صُنع بـ  في الجزائر  
Made with  in Algeria

**© 2025 Youcef. All rights reserved.**

</div>
#   A r d u i n o - S m a r t - L i g h t i n g - A u t o m a t i o n  
 