#include<layout-engine.h>
#include<Arduino.h>

LayoutEngine::Element::Element(
    std::string id, 
    ElementProps props,
    std::vector<LayoutEngine::Element*> children
) {
    this->id = id;
    this->props = props;
    this->children = children;
}

std::vector<LayoutEngine::Element*> LayoutEngine::Element::getChildren(){
    return this->children;
}

std::string LayoutEngine::Element::getId() {
    return this->id;
}

/** Adds a new child element to the root */
void LayoutEngine::Element::addChildElement(Element* child) {
    this->children.push_back(child);
}

/** 
 * Traverses the element tree following 
 * Post-order Depth First Traversal (Children (L -> R), Node) 
 */
void LayoutEngine::traverseElementTree(Element* element) {
    if (element == NULL) return;

    for (Element* child : element->getChildren()) {
        traverseElementTree(child);
    }
    Serial.printf("visited %s \n", element->getId().c_str());
}
