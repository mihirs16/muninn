#ifndef CANVAS_H
#define CANVAS_H

#include <GxEPD2.h>
#include <GxEPD2_BW.h>
#include <display.h>

/** Contains the abstractions for setting up the EPD display for drawing */
namespace Canvas {

    /** Background color modes for the EPD */
    enum BackgroundColor { white, black };

    /** Canvas abstraction for drawing to an EPD */
    class Canvas {
        private:
            /** Height-wise dimension of the EPD in `px` */
            int height;

            /** Width-wise dimension of the EPD in `px` */
            int width;

            /**
             * Rotation setting of the EPD
             * (see
             * https://learn.adafruit.com/adafruit-gfx-graphics-library/rotating-the-display)
             */
            int rotation;

            /** Default background color of the EPD when screen is clear */
            BackgroundColor defaultBg;

        public:
            /** Initialises a canvas for drawing to the EPD */
            Canvas(int, int, int, BackgroundColor);

            /** Clears the canvas to default background */
            void clear();
    };
} // namespace Canvas

#endif // CANVAS_H
