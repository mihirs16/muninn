#include <Arduino.h>
#include <layout-engine.h>

void setup() {
    Serial.begin(115200);
    {
        using namespace LayoutEngine;

        GrowChildren(
            new Element("root", {
                .axis = "vertical",
                .size = { .height = 420, .width = 100 },
            },
            {
                new Element("block1", {
                    .axis = "horizontal"
                },
                {
                    new Element("block3"),
                    new Element("block4")
                }),
                new Element("block2", {
                    .axis = "horizontal"
                },
                {
                    new Element("block5"),
                    new Element("block6")
                })
            })
        );
    }
}

void loop()
{
    // your loop code here
}
