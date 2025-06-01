#include<layout-engine.h>
#include<Arduino.h>

LayoutEngine::Element::Element(
    std::string id, 
    ElementProps props,
    std::vector<Element*> children
) {
    this->id = id;
    this->props = props;
    this->children = children;
}

LayoutEngine::Element::Element(
    std::string id,
    std::vector<Element*> children
) {
    this->id = id;
    this->props = {
        .position = { .x = 0, .y = 0 },
        .size = { .height = 0, .width = 0 },
        .style = {
            .padding = 0,
            .childGap = 0,
            .borderWidth = 1,
        }
    };
    this->children = children;
}

std::vector<LayoutEngine::Element*> LayoutEngine::Element::getChildren(){
    return this->children;
}

std::string LayoutEngine::Element::getId() {
    return this->id;
}

LayoutEngine::ElementProps LayoutEngine::Element::getProps() {
    return this->props;
}

/** 
 * Goes through the Element tree following pre-order depth first traversal.
 * Updates the sizes of all growable children based on available space in the Element.
 * Assumes symmetry and grows all growable children uniformly.
 */
void LayoutEngine::GrowChildren(Element* root) {
    if (root == NULL) return;

    ElementProps props = root->getProps();
    std::vector<Element*> children = root->getChildren();
    int numChildren = children.size();

    if (numChildren > 0) {
        int gaps = (numChildren - 1) * props.style.childGap;
        int padding = 2 * props.style.padding;
        int remainingWidth = int((props.size.width - gaps - padding) / 2) * 2;
        int growWidth = remainingWidth / numChildren;
        while (remainingWidth > 0) {
            for (Element* child: children) {
                ElementProps childProps = child->getProps();
                Size grownChildSize = {
                    .height = childProps.size.height,
                    .width = childProps.size.width + growWidth
                };
                child->updateSize(grownChildSize);
                remainingWidth -= growWidth;
            }
            growWidth = remainingWidth / numChildren;
        }
    }

    Serial.printf("%s width %d\n", root->getId().c_str(), root->getProps().size.width);
    for (Element* child: children) {
        GrowChildren(child);
    }
}
