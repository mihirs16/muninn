#include <canvas.h>

/**
 * @brief Initialises a canvas for drawing to the EPD
 *
 * @param height Height-wise dimension of the EPD in `px`
 * @param width Width-wise dimension of the EPD in `px`
 * @param rotation Rotation setting of the EPD (see https://learn.adafruit.com/adafruit-gfx-graphics-library/rotating-the-display)
 * @param defaultBg Default background color of the EPD when screen is clear
 */
Canvas::Canvas::Canvas(int height, int width, int rotation, BackgroundColor defaultBg) {
    this->height = height;
    this->width = width;
    this->rotation = rotation;
    this->defaultBg = defaultBg;

    display.init(115200);
    display.setRotation(rotation);
    display.setFullWindow();
    display.firstPage();
    do {
        if (defaultBg == BackgroundColor::white) {
            display.fillScreen(GxEPD_WHITE);
        }
        else {
            display.fillScreen(GxEPD_BLACK);
        }
    } while (display.nextPage());    
}

/** @brief Clears the canvas to it's default background mode */
void Canvas::Canvas::Canvas::clear() {
    display.firstPage();
    do {
        if (defaultBg == BackgroundColor::white) {
            display.fillScreen(GxEPD_WHITE); // Clear the screen to white
        }
        else {
            display.fillScreen(GxEPD_BLACK); // Clear the screen to black
        }
    } while (display.nextPage());
}
