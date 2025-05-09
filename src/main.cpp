#include <Arduino.h>
#include <canvas.h>
#include <gauge.h>

void setup() {
    Canvas::Canvas canvas = Canvas::Canvas(400, 300, 3, Canvas::BackgroundColor::white);
    Canvas::Gauge gauge = Canvas::Gauge(&canvas, 135, 135, 5);
    gauge.drawGauge(10, 10);
}

void loop()
{
    // your loop code here
}
