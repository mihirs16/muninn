#include<gauge.h>

/**
 * @param canvas
 * @param height
 * @param width
 * @param outlineThickness
 */
Canvas::Gauge::Gauge(Canvas *canvas, int height, int width, int outlineThickness) {
    this->height = height;
    this->width = width;
    this->outlineThickness = outlineThickness;
}

/**
 * @brief Draws the outline of the gauge on the canvas
 * 
 * @param x coordinate of the top left corner of the gauge
 * @param y coordinate of the top left corner of the gauge
 */
void Canvas::Gauge::drawGauge(int x, int y) {
    do {
        display.drawRect(x, y, width, height, GxEPD_BLACK);
        if (outlineThickness > 0) {
            display.fillRect(x, y, width, height, GxEPD_BLACK);

            int t = outlineThickness;
            display.fillRect(x + t, y + t, width - (2 * t), height - (2 * t), GxEPD_WHITE);
        }
    } while (display.nextPage());
}
