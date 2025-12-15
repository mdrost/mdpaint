#ifndef MDP_VIPSSVGTEMPLATES_H
#define MDP_VIPSSVGTEMPLATES_H

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define INT_MIN_STR STR(INT_MIN)
#define INT_STRLEN (sizeof(INT_MIN_STR) - 1)

static const char svgPointTemplate[] =
    "<svg xmlns='http://www.w3.org/2000/svg' width='%d' height='%d'>"
    "<circle cx='%.1f' cy='%.1f' r='0.5' fill='black'/>"
    "</svg>"; // 2 ints, 2 doubles

static const int SVG_POINT_SIZE = sizeof(svgPointTemplate)
                                  + 2 * (-2 + INT_STRLEN) // 2 ints
                                  + 2 * (-2 + INT_STRLEN + 2); // 2 doubles

static const char svgLineTemplate[] =
    "<svg xmlns='http://www.w3.org/2000/svg' width='%d' height='%d'>"
    "<line x1='%.1f' y1='%.1f' x2='%.1f' y2='%.1f' stroke-width='1' stroke='black' stroke-linecap='round' shape-rendering='crispEdges'/>"
    "</svg>"; // 2 ints, 4 doubles

static const int SVG_LINE_SIZE = sizeof(svgLineTemplate)
                                 + 2 * (-2 + INT_STRLEN) // 2 ints
                                 + 4 * (-2 + INT_STRLEN + 2); // 4 doubles

static const char svgRectangleTemplate[] =
    "<svg xmlns='http://www.w3.org/2000/svg' width='%d' height='%d'>"
    "<rect x='%.1f' y='%.1f' width='%d' height='%d' stroke-width='1' stroke='black' fill='none' shape-rendering='crispEdges'/>"
    "</svg>"; // 2 ints, 2 doubles, 2 ints

static const int SVG_RECTANGLE_SIZE = sizeof(svgRectangleTemplate)
                                      + 2 * (-2 + INT_STRLEN) // 2 ints
                                      + 2 * (-2 + INT_STRLEN + 2) // 2 doubles
                                      + 2 * (-2 + INT_STRLEN); // 2 ints

static const char svgEllipseTemplate[] =
    "<svg xmlns='http://www.w3.org/2000/svg' width='%d' height='%d'>"
    "<ellipse cx='%.1f' cy='%.1f' rx='%.1f' ry='%.1f' stroke-width='1' stroke='black' fill='none' shape-rendering='crispEdges'/>"
    "</svg>"; // 2 ints, 4 doubles

static const int SVG_ELLIPSE_SIZE = sizeof(svgEllipseTemplate)
                                    + 2 * (-2 + INT_STRLEN) // 2 ints
                                    + 4 * (-2 + INT_STRLEN + 2); // 4 doubles

#endif // MDP_VIPSSVGTEMPLATES_H
