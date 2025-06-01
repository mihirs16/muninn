#include <Arduino.h>
#include <layout-engine.h>

void setup() {
    Serial.begin(115200);
    LayoutEngine::Element *root = new LayoutEngine::Element("root", {
        .size = { .height = 420, .width = 300 },
        .style = { .padding = 10, .childGap = 5 },
    },
    {
        new LayoutEngine::Element("block1", {}, {
            new LayoutEngine::Element("block3"),
            new LayoutEngine::Element("block4")
        }),
        new LayoutEngine::Element("block2")
    });

    LayoutEngine::traverseElementTree(root);
}

void loop()
{
    // your loop code here
}
