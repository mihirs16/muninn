#ifndef GAUGE_H
#define GAUGE_H

#include <canvas.h>

namespace Canvas {
    /** Abstract Gauge can be derived from to draw gauges */
    class Gauge {
        private:
            /** Height of the gauge in `px` */
            int height;

            /** Width of the gauge in `px` */
            int width;

            /** Thickenss of the outline for the gauge in `px` */
            int outlineThickness;

            /** Reference to an instance of the Canvas */
            Canvas *canvas;

        public:
            Gauge(Canvas *, int, int, int);

            /** Draws the gauge on the canvas */
            void drawGauge(int, int);

            /** Draws the contents of the gauge (used by Gauge::drawGauge) */
            // virtual void drawGaugeContents();
    };
}

#endif // GAUGE_H
