#ifndef LAYOUT_ENGINE_ROOT_H
#define LAYOUT_ENGINE_ROOT_H

#include<vector>
#include<string>

namespace LayoutEngine {
    struct Position {
        /** Pixel position on the horizontal axis (left-to-right)*/
        int x;

        /** Pixel position on the vertical axis (top-to-bottom) */
        int y;
    };

    struct Size {
        /** Number of pixels occupied on the y-axis (top-to-bottom) */
        int height;

        /** Number of pixels occupied on the x-axis (left-to-right) */
        int width;
    };

    struct Style {
        /** Number of pixels to leave as margin from the borders */
        int padding;

        /** Number of pixels between each child of this Element */
        int childGap;

        /** 
         * Number of pixels occupied by the border inside the element
         * (inset border thickness) 
         */
        int borderWidth;
    };

    /** Options for an element which can be provided at initialization */
    struct ElementProps {
        /** Axis of layout can be `horizontal` | `vertical` */
        std::string axis;

        /** Position of the element in `px` */
        Position position;

        /** Size of the element in `px` */
        Size size;

        /** Styling properties of the element */
        Style style;
    };

    /** Generic element representing an area on the display */
    class Element {
        private:
            /** Unique identifier for an Element */
            std::string id;

            /** Properties of this Element */
            ElementProps props;
            
            /** Children of this element */
            std::vector<Element*> children;

        public:
            /** Define a generic element representing an area on the display */
            Element(
                std::string id, 
                ElementProps props, 
                std::vector<Element*> children = {}
            );
            Element(
                std::string id,
                std::vector<Element*> children = {}
            );

            /** Returns an iterator (vector) for children */
            std::vector<Element*> getChildren();

            /** Returns the unique identifier for this element */
            std::string getId();

            /** Returns the styling properties of the element */
            ElementProps getProps();

            /** Updates the size of the child */
            void updateSize(Size size);

    };

    void GrowChildren(Element* element);

    // void PositionElements(Element* element);
}

#endif // LAYOUT_ENGINE_ROOT_H
