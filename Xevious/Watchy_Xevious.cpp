#include "Watchy_Xevious.h"
#include "Xevious.h"

#ifdef WATCHY_SIM
bool XEVI_LANG = false;
bool XEVI_NTP_SYNC = true;
#else
RTC_DATA_ATTR bool XEVI_LANG = false;
RTC_DATA_ATTR bool XEVI_NTP_SYNC;

#ifdef ARDUINO_ESP32S3_DEV
  #define ACTIVE_LOW 0
#else
  #define ACTIVE_LOW 1
#endif
#endif

bool SHOT_ZAPPER = false;

void WatchyXevious::drawWatchFace(){

    display.fillScreen(GxEPD_WHITE);

    //Hour
    int hour = currentTime.Hour;
    int baseNumber = 10;
	if(XEVI_LANG){
		baseNumber = 16;
	}
    drawSeg(hour / baseNumber, 1, 41, XEVI_LANG);
    drawSeg(hour % baseNumber, 9, 41, XEVI_LANG);

    //Minute
    drawSeg(currentTime.Minute / baseNumber, 17, 41, XEVI_LANG);
    drawSeg(currentTime.Minute % baseNumber, 25, 41, XEVI_LANG);

    //Date
    drawDate(XEVI_LANG);

    //Backgroud
    drawBackground();

    //Zapper
#ifdef WATCHY_SIM
    SHOT_ZAPPER = true;
#endif
    if (SHOT_ZAPPER) {
        drawZapper();
    };
    SHOT_ZAPPER = false;
#ifdef WATCHY_SIM
    XEVI_LANG = !XEVI_LANG;
    SHOT_ZAPPER = true;
    Sleep(2000);
    display.fillScreen(GxEPD_WHITE);
    drawWatchFace();
#endif 

}

void WatchyXevious::drawBackground() {
    // backgroun
    display.drawBitmap(0, 0, bg, INDEX_SIZE * 50, INDEX_SIZE * 50, GxEPD_BLACK);

    // title
    display.drawBitmap(INDEX_SIZE * 34, INDEX_SIZE * 45, title, INDEX_SIZE * 12, INDEX_SIZE * 4, GxEPD_BLACK);

    // credit
    drawBattery();

    // andoa
    display.drawBitmap(INDEX_SIZE * 1, INDEX_SIZE * 1, andoa_mask, INDEX_SIZE * 44, INDEX_SIZE * 20, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 1, INDEX_SIZE * 1, andoa, INDEX_SIZE * 44, INDEX_SIZE * 20, GxEPD_BLACK);

    // SOLVALU
    display.drawBitmap(INDEX_SIZE * 25, INDEX_SIZE * 20, SOLVALOU_mask, INDEX_SIZE * 24, INDEX_SIZE * 20, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 25, INDEX_SIZE * 20, SOLVALOU, INDEX_SIZE * 24, INDEX_SIZE * 20, GxEPD_BLACK);

    // SOL
    drawSOL();

    // enemy
    drawEnemy();

#ifdef WATCHY_SIM
    Sleep(400);
    display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire1, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_BLACK);
    Sleep(400);
    display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire1, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire2, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_BLACK);
    Sleep(400);
    display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire2, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire1, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_BLACK);
    Sleep(400);
    display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire1, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire2, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_BLACK);
    Sleep(400);
    display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire2, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire1, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_BLACK);
    Sleep(400);
    display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire3_mask, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire3, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_BLACK);
#else
    display.display(true);
    if(!SHOT_ZAPPER){
      delay(400);
      display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire1, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_BLACK);
      display.display(true);
      delay(400);
      display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire1, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_WHITE);
      display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire2, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_BLACK);
      display.display(true);
      delay(400);
      display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire2, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_WHITE);
      display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire1, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_BLACK);
      display.display(true);
      delay(400);
      display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire1, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_WHITE);
      display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire2, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_BLACK);
      display.display(true);
      delay(400);
      display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire2, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_WHITE);
      display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire1, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_BLACK);
      display.display(true);
      delay(400);
    }
    display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire3_mask, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 37, INDEX_SIZE * 20, fire3, INDEX_SIZE * 13, INDEX_SIZE * 26, GxEPD_BLACK);
    display.display(true);
#endif
}

void WatchyXevious::drawBattery() {
    int8_t batteryLevel = 0;
    float VBAT = getBatteryVoltage();
    if (VBAT > 3.8) {
        batteryLevel = 3;
    }
    else if (VBAT > 3.4 && VBAT <= 3.8) {
        batteryLevel = 2;
    }
    else if (VBAT > 3.0 && VBAT <= 3.4) {
        batteryLevel = 1;
    }
    else if (VBAT <= 3.0) {
        batteryLevel = 0;
    }

    for (int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++) {
        display.drawBitmap(INDEX_SIZE * 35 + INDEX_SIZE * 2 * batterySegments, INDEX_SIZE * 42, credit, INDEX_SIZE * 2, INDEX_SIZE * 2, GxEPD_BLACK); //crdit
    }
}


void WatchyXevious::drawEnemy()
{
#ifdef WATCHY_SIM
    display.drawBitmap(INDEX_SIZE * 3, INDEX_SIZE * 3, zacart_mask, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 3, INDEX_SIZE * 3, zacart, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
    Sleep(200);
    display.drawBitmap(INDEX_SIZE * 36, INDEX_SIZE * 8, zacart_mask, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 36, INDEX_SIZE * 8, zacart, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
    Sleep(300);
    display.drawBitmap(INDEX_SIZE * 18, INDEX_SIZE * 18, zacart_mask, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 18, INDEX_SIZE * 18, zacart, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
    Sleep(150);
    display.drawBitmap(INDEX_SIZE * 22, INDEX_SIZE * 5, zacart_mask, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 22, INDEX_SIZE * 5, zacart, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
    Sleep(250);
    display.drawBitmap(INDEX_SIZE * 42, INDEX_SIZE * 4, zacart_mask, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 42, INDEX_SIZE * 4, zacart, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
#else
    display.drawBitmap(INDEX_SIZE * 3, INDEX_SIZE * 3, zacart_mask, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 3, INDEX_SIZE * 3, zacart, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
    if(!SHOT_ZAPPER){display.display(true);delay(200);}
    display.drawBitmap(INDEX_SIZE * 36, INDEX_SIZE * 8, zacart_mask, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 36, INDEX_SIZE * 8, zacart, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
    if(!SHOT_ZAPPER){display.display(true);delay(300);}
    display.drawBitmap(INDEX_SIZE * 18, INDEX_SIZE * 18, zacart_mask, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 18, INDEX_SIZE * 18, zacart, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
    if(!SHOT_ZAPPER){display.display(true);delay(150);}
    display.drawBitmap(INDEX_SIZE * 22, INDEX_SIZE * 5, zacart_mask, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 22, INDEX_SIZE * 5, zacart, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
    if(!SHOT_ZAPPER){display.display(true);delay(250);}
    display.drawBitmap(INDEX_SIZE * 42, INDEX_SIZE * 4, zacart_mask, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_WHITE);
    display.drawBitmap(INDEX_SIZE * 42, INDEX_SIZE * 4, zacart, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
    if(!SHOT_ZAPPER){display.display(true);}
#endif
}

void WatchyXevious::drawZapper()
{
    for (int cnt = 20; cnt > 0; cnt-=3) {
        if (cnt == 17 || cnt == 2) {
            display.drawBitmap(INDEX_SIZE * (cnt + 1), INDEX_SIZE * (cnt + 1), explode_mask, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_WHITE);
            display.drawBitmap(INDEX_SIZE * (cnt + 1), INDEX_SIZE * (cnt + 1), explode, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        }
        else if (cnt % 6 == 2) {
            display.drawBitmap(INDEX_SIZE * cnt, INDEX_SIZE * cnt, zapper_mask, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_WHITE);
            display.drawBitmap(INDEX_SIZE * cnt, INDEX_SIZE * cnt, zapperL, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        }
        else {
            display.drawBitmap(INDEX_SIZE * cnt, INDEX_SIZE * cnt, zapper_mask, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_WHITE);
            display.drawBitmap(INDEX_SIZE * cnt, INDEX_SIZE * cnt, zapperR, INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        }
#ifdef WATCHY_SIM
        Sleep(200);
#else
        display.display(true);
        delay(200);
#endif
    }
}

void WatchyXevious::drawSeg(const int& num, const int& index_x, const int& index_y, const bool& xevi_lang)
{
    if(xevi_lang){
        display.drawBitmap(INDEX_SIZE * index_x, INDEX_SIZE * index_y, xevi_num_L_allArray[num], INDEX_SIZE * 8, INDEX_SIZE * 8, GxEPD_BLACK);
    }else{
        display.drawBitmap(INDEX_SIZE * index_x, INDEX_SIZE * index_y, arabic_num_L_allArray[num], INDEX_SIZE * 8, INDEX_SIZE * 8, GxEPD_BLACK);
    }
}

void WatchyXevious::drawDate(const bool& xevi_lang)
{
    int cYear = tmYearToCalendar(currentTime.Year);
    if (xevi_lang) {
        int hex_num[4];
        hex_num[0] = cYear / (16 * 16 * 16);
        hex_num[1] = cYear % (16 * 16 * 16) / (16 * 16);
        hex_num[2] = cYear % (16 * 16) / 16;
        hex_num[3] = cYear % 16;

        display.drawBitmap(INDEX_SIZE * 1, INDEX_SIZE * 31, xevi_num_M_allArray[hex_num[0]], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 5, INDEX_SIZE * 31, xevi_num_M_allArray[hex_num[1]], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 9, INDEX_SIZE * 31, xevi_num_M_allArray[hex_num[2]], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 13, INDEX_SIZE * 31, xevi_num_M_allArray[hex_num[3]], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);

        display.drawBitmap(INDEX_SIZE * 1, INDEX_SIZE * 36, xevi_num_M_allArray[currentTime.Month / 16], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 5, INDEX_SIZE * 36, xevi_num_M_allArray[currentTime.Month % 16], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 9, INDEX_SIZE * 36, xevi_num_M_allArray[currentTime.Day / 16], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 13, INDEX_SIZE * 36, xevi_num_M_allArray[currentTime.Day % 16], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);

        display.drawBitmap(INDEX_SIZE * 17, INDEX_SIZE * 37, xevi_WDay[currentTime.Wday - 1][0], INDEX_SIZE * 3, INDEX_SIZE * 3, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 20, INDEX_SIZE * 37, xevi_WDay[currentTime.Wday - 1][1], INDEX_SIZE * 3, INDEX_SIZE * 3, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 23, INDEX_SIZE * 37, xevi_WDay[currentTime.Wday - 1][2], INDEX_SIZE * 3, INDEX_SIZE * 3, GxEPD_BLACK);

    }
    else {
        display.drawBitmap(INDEX_SIZE * 1, INDEX_SIZE * 31, arabic_num_M_allArray[cYear / 1000], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 5, INDEX_SIZE * 31, arabic_num_M_allArray[cYear % 1000 / 100], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 9, INDEX_SIZE * 31, arabic_num_M_allArray[cYear % 100 / 10], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 13, INDEX_SIZE * 31, arabic_num_M_allArray[cYear % 10], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);

        display.drawBitmap(INDEX_SIZE * 1, INDEX_SIZE * 36, arabic_num_M_allArray[currentTime.Month / 10], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 5, INDEX_SIZE * 36, arabic_num_M_allArray[currentTime.Month % 10], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 9, INDEX_SIZE * 36, arabic_num_M_allArray[currentTime.Day / 10], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 13, INDEX_SIZE * 36, arabic_num_M_allArray[currentTime.Day % 10], INDEX_SIZE * 4, INDEX_SIZE * 4, GxEPD_BLACK);

        display.drawBitmap(INDEX_SIZE * 17, INDEX_SIZE * 37, alpha_WDay[currentTime.Wday - 1][0], INDEX_SIZE * 3, INDEX_SIZE * 3, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 20, INDEX_SIZE * 37, alpha_WDay[currentTime.Wday - 1][1], INDEX_SIZE * 3, INDEX_SIZE * 3, GxEPD_BLACK);
        display.drawBitmap(INDEX_SIZE * 23, INDEX_SIZE * 37, alpha_WDay[currentTime.Wday - 1][2], INDEX_SIZE * 3, INDEX_SIZE * 3, GxEPD_BLACK);
    }
}

void WatchyXevious::drawSOL()
{
    if (currentTime.Minute == 0) {
        XEVI_NTP_SYNC = false;
#ifndef WATCHY_SIM
        connectWiFi();
#endif
        if (WIFI_CONFIGURED) {
#ifdef WATCHY_SIM
            XEVI_NTP_SYNC = true;
#else
            XEVI_NTP_SYNC = syncNTP();
#endif
        }
    }
    if (XEVI_NTP_SYNC) {
        display.drawBitmap(INDEX_SIZE * 1, INDEX_SIZE * 19, SOL, INDEX_SIZE * 14, INDEX_SIZE * 4, GxEPD_BLACK); //ntp SOL
    }
#ifndef WATCHY_SIM
    WiFi.mode(WIFI_OFF);
    btStop();
#endif
}

#ifndef WATCHY_SIM
void WatchyXevious::handleButtonPress() {
    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();
    // Menu Button
    if (wakeupBit & MENU_BTN_MASK) {
        if (guiState ==
            WATCHFACE_STATE) { // enter menu state if coming from watch face
            showMenu(menuIndex, false);
        }
        else if (guiState ==
            MAIN_MENU_STATE) { // if already in menu, then select menu item
            switch (menuIndex) {
            case 0:
                showAbout();
                break;
            case 1:
                showBuzz();
                break;
            case 2:
                showAccelerometer();
                break;
            case 3:
                setTime();
                break;
            case 4:
                setupWifi();
                break;
            case 5:
                showUpdateFW();
                break;
            case 6:
                showSyncNTP();
                break;
            default:
                break;
            }
        }
        else if (guiState == FW_UPDATE_STATE) {
            updateFWBegin();
        }
    }
    // Back Button
    else if (wakeupBit & BACK_BTN_MASK) {
        if (guiState == MAIN_MENU_STATE) { // exit to watch face if already in menu
            RTC.read(currentTime);
            showWatchFace(false);
        }
        else if (guiState == APP_STATE) {
            showMenu(menuIndex, false); // exit to menu if already in app
        }
        else if (guiState == FW_UPDATE_STATE) {
            showMenu(menuIndex, false); // exit to menu if already in app
        }
        else if (guiState == WATCHFACE_STATE) {
            return;
        }
    }
    // Up Button
    else if (wakeupBit & UP_BTN_MASK) {
        if (guiState == MAIN_MENU_STATE) { // increment menu index
            menuIndex--;
            if (menuIndex < 0) {
                menuIndex = MENU_LENGTH - 1;
            }
            showMenu(menuIndex, true);
        }
        else if (guiState == WATCHFACE_STATE) {
            RTC.read(currentTime);
            SHOT_ZAPPER = true;
            drawWatchFace();
            display.display(true); // partial refresh
            return;
        }
    }
    // Down Button
    else if (wakeupBit & DOWN_BTN_MASK) {
        if (guiState == MAIN_MENU_STATE) { // decrement menu index
            menuIndex++;
            if (menuIndex > MENU_LENGTH - 1) {
                menuIndex = 0;
            }
            showMenu(menuIndex, true);
        }
        else if (guiState == WATCHFACE_STATE) {
            XEVI_LANG = !XEVI_LANG;     // xevi_lang
            RTC.read(currentTime);
            drawWatchFace();
            display.display(true); // partial refresh
            return;
        }
    }

    /***************** fast menu *****************/
    bool timeout = false;
    long lastTimeout = millis();
    pinMode(MENU_BTN_PIN, INPUT);
    pinMode(BACK_BTN_PIN, INPUT);
    pinMode(UP_BTN_PIN, INPUT);
    pinMode(DOWN_BTN_PIN, INPUT);
    while (!timeout) {
        if (millis() - lastTimeout > 5000) {
            timeout = true;
        }
        else {
            if (digitalRead(MENU_BTN_PIN) == ACTIVE_LOW) {
                lastTimeout = millis();
                if (guiState ==
                    MAIN_MENU_STATE) { // if already in menu, then select menu item
                    switch (menuIndex) {
                    case 0:
                        showAbout();
                        break;
                    case 1:
                        showBuzz();
                        break;
                    case 2:
                        showAccelerometer();
                        break;
                    case 3:
                        setTime();
                        break;
                    case 4:
                        setupWifi();
                        break;
                    case 5:
                        showUpdateFW();
                        break;
                    case 6:
                        showSyncNTP();
                        break;
                    default:
                        break;
                    }
                }
                else if (guiState == FW_UPDATE_STATE) {
                    updateFWBegin();
                }
            }
            else if (digitalRead(BACK_BTN_PIN) == ACTIVE_LOW) {
                lastTimeout = millis();
                if (guiState ==
                    MAIN_MENU_STATE) { // exit to watch face if already in menu
                    RTC.read(currentTime);
                    showWatchFace(false);
                    break; // leave loop
                }
                else if (guiState == APP_STATE) {
                    showMenu(menuIndex, false); // exit to menu if already in app
                }
                else if (guiState == FW_UPDATE_STATE) {
                    showMenu(menuIndex, false); // exit to menu if already in app
                }
            }
            else if (digitalRead(UP_BTN_PIN) == ACTIVE_LOW) {
                lastTimeout = millis();
                if (guiState == MAIN_MENU_STATE) { // increment menu index
                    menuIndex--;
                    if (menuIndex < 0) {
                        menuIndex = MENU_LENGTH - 1;
                    }
                    showFastMenu(menuIndex);
                }
            }
            else if (digitalRead(DOWN_BTN_PIN) == ACTIVE_LOW) {
                lastTimeout = millis();
                if (guiState == MAIN_MENU_STATE) { // decrement menu index
                    menuIndex++;
                    if (menuIndex > MENU_LENGTH - 1) {
                        menuIndex = 0;
                    }
                    showFastMenu(menuIndex);
                }
            }
        }
    }
}
#endif
