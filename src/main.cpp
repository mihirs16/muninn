#include <Arduino.h>
#include <layout-engine.h>

void setup() {
    Serial.begin(115200);
    {
        using namespace LayoutEngine;

        BuildLayout(
            new Element("root", {
                .axis = "vertical",
                .size = { .height = 420, .width = 100 },
                .style = { .borderWidth = 1 }
            },
            {
                new Element("block1", {
                    .style = {
                        .padding = 1,
                        .childGap = 1,
                        .borderWidth = 1
                    }
                },
                {
                    new Element("block3", { .style = { .borderWidth = 1 } }, {}),
                    new Element("block4", { .style = { .borderWidth = 1 } }, {}),
                    new Element("block5", { .style = { .borderWidth = 1 } }, {})
                }),
                new Element("block2", {
                    .style = {
                        .padding = 1,
                        .childGap = 1,
                        .borderWidth = 1
                    }
                },
                {
                    new Element("block5", { .style = { .borderWidth = 1 } }, {}),
                    new Element("block6", { .style = { .borderWidth = 1 } }, {})
                })
            })
        );
    }
}

void loop()
{
    // your loop code here
}
