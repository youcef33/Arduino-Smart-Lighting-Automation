/*
 * Configuration Template File
 * ملف قالب الإعدادات
 * 
 * تعليمات:
 * 1. انسخ هذا الملف وأعد تسميته إلى "config.h"
 * 2. استبدل القيم الوهمية ببياناتك الحقيقية
 * 3. لا ترفع ملف config.h إلى GitHub أبداً!
 * 
 * Instructions:
 * 1. Copy this file and rename it to "config.h"
 * 2. Replace the placeholder values with your actual credentials
 * 3. Never upload config.h to GitHub!
 */

#ifndef CONFIG_H
#define CONFIG_H

// ========================================
// WiFi Configuration
// إعدادات الواي فاي
// ========================================
#define WIFI_SSID "YOUR_WIFI_SSID_HERE"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD_HERE"

// ========================================
// Firebase Configuration
// إعدادات Firebase
// ========================================
#define API_KEY "YOUR_FIREBASE_API_KEY_HERE"
#define DATABASE_URL "https://YOUR_PROJECT_ID.firebaseio.com/"

/*
 * كيفية الحصول على بيانات Firebase:
 * How to get Firebase credentials:
 * 
 * 1. اذهب إلى: https://console.firebase.google.com/
 *    Go to: https://console.firebase.google.com/
 * 
 * 2. أنشئ مشروع جديد أو اختر مشروع موجود
 *    Create a new project or select existing one
 * 
 * 3. API_KEY: 
 *    Project Settings > General > Web API Key
 * 
 * 4. DATABASE_URL:
 *    Realtime Database > Data > Copy the URL
 *    مثال: https://your-project-12345.firebaseio.com/
 *    Example: https://your-project-12345.firebaseio.com/
 */

#endif // CONFIG_H
