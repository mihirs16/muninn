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

void LayoutEngine::Element::updatePosition(Position position) {
    this->props.position = position;
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
        int borders = 2 * props.style.borderWidth;

        // since all children are growable and symmetric
        // the remaining space in this element is 
        // the space left after padding and gaps
        int totalSpaceAlongAxis = props.axis == "horizontal" ? props.size.width : props.size.height;
        int totalSpaceAcrossAxis = props.axis == "horizontal" ? props.size.height : props.size.width;

        int remainingSpaceAlongAxis = int((totalSpaceAlongAxis - gaps - padding - borders) / 2) * 2;
        int remainingSpaceAcrossAxis = int((totalSpaceAcrossAxis - gaps - padding - borders) / 2) * 2;

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

/**
 * Goes throught the Element tree following pre-order depth first traversal.
 * Calculates the position of all children.
 */
void LayoutEngine::PositionElements(Element *root) {
    if (root == NULL) return;

    ElementProps props = root->getProps();
    std::vector<Element*> children = root->getChildren();
    int numChildren = children.size();

    for (int i = 0; i < numChildren; i++) {
        int childX = props.position.x + props.style.borderWidth + props.style.padding;
        int childY = props.position.y + props.style.borderWidth + props.style.padding;
        Element* child = children[i];

        // first child is positioned relative to this element (left-to-right)
        // first child is at the top-left corner and thus axis agnostic
        if (i == 0) {
            child->updatePosition({
                .x = childX,
                .y = childY
            });
            continue;
        }

        Element* prevChild = children[i - 1];
        ElementProps prevProps = prevChild->getProps();

        if (props.axis == "horizontal") {
            childX += prevProps.size.width + (i * props.style.childGap);
        } else {
            childY += prevProps.size.height + (i * props.style.childGap);
        }

        child->updatePosition({
            .x = childX,
            .y = childY
        });
    }

    Serial.printf(
        "%s position (%d,%d)\n",
        root->getId().c_str(),
        root->getProps().position.x,
        root->getProps().position.y
    );
    for (Element* child: children) {
        PositionElements(child);
    }
}

/**
 * Builds the layout for a given element tree.
 * Makes multiple passes over the element tree:
 * `Grow Sizing` -> `Relative Positioning`
 * Updates each element in the Element tree.
 */
void LayoutEngine::BuildLayout(Element *root) {
    GrowChildren(root);
    PositionElements(root);
}