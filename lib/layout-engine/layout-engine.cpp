#include<layout-engine.h>
#include<Arduino.h>

LayoutEngine::Element::Element(
    std::string id, 
    ElementProps props,
    std::vector<Element*> children
) {
    // handle default value for axis
    props.axis = props.axis == "" ? "horizontal" : props.axis;

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
        .axis = "horizontal",
        .position = { .x = 0, .y = 0 },
        .size = { .height = 0, .width = 0 },
        .style = {
            .padding = 0,
            .childGap = 0,
            .borderWidth = 1,
        },
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

void LayoutEngine::Element::updateSize(Size size) {
    this->props.size = size;
}

/** 
 * Goes through the Element tree following pre-order depth first traversal.
 * Updates the sizes of all growable children based on available space in the Element along the axis.
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

        // since all children are growable and symmetric
        // the remaining space in this element is 
        // the space left after padding and gaps
        int totalSpaceAlongAxis = props.axis == "horizontal" ? props.size.width : props.size.height;
        int totalSpaceAcrossAxis = props.axis == "horizontal" ? props.size.height : props.size.width;

        int remainingSpaceAlongAxis = int((totalSpaceAlongAxis - gaps - padding) / 2) * 2;
        int remainingSpaceAcrossAxis = int((totalSpaceAcrossAxis - gaps - padding) / 2) * 2;

        int growSizeAlongAxis = remainingSpaceAlongAxis / numChildren;
        int growSizeAcrossAxis = remainingSpaceAcrossAxis;

        while (remainingSpaceAlongAxis > 0 || remainingSpaceAcrossAxis > 0) {
            // grow all children by grow size
            for (Element* child: children) {
                ElementProps childProps = child->getProps();
                int grownHeight = childProps.size.height;
                int grownWidth = childProps.size.width;

                if (props.axis == "horizontal") {
                    grownHeight = growSizeAcrossAxis;
                    grownWidth += growSizeAlongAxis;
                } else {
                    grownHeight += growSizeAlongAxis;
                    grownWidth = growSizeAcrossAxis;
                }

                child->updateSize({
                    .height = grownHeight,
                    .width = grownWidth
                });
                remainingSpaceAlongAxis -= growSizeAlongAxis;
                remainingSpaceAcrossAxis -= growSizeAcrossAxis;
            }

            // update grow size after growing all children
            growSizeAlongAxis = remainingSpaceAlongAxis / numChildren;
            growSizeAcrossAxis = remainingSpaceAcrossAxis;
        }
    }

    Serial.printf(
        "%s size %dx%d\n",
        root->getId().c_str(),
        root->getProps().size.height,
        root->getProps().size.width
    );
    for (Element* child: children) {
        GrowChildren(child);
    }
}
