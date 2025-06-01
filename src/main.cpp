#include <Arduino.h>
#include <layout-engine.h>

void setup() {
    Serial.begin(115200);
    {
        using namespace LayoutEngine;

        GrowChildren(
            new Element("root", {
                .size = { .height = 420, .width = 100 },
                .style = { .padding = 10, .childGap = 10 },
            },
            {
                new Element("block1", {
                    new Element("block3"),
                    new Element("block4")
                }),
                new Element("block2")
            })
        );
    }
}

void loop()
{
    // your loop code here
}
