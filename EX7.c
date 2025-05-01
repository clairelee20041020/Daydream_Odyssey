#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct __ShapeInterface {
    int (*isPointInside)(struct __ShapeInterface*, double, double);
} ShapeInterface;

typedef struct __Circle {
    ShapeInterface shapeInterface;
    double centerX;
    double centerY;
    double radius;
} Circle;

typedef struct __Rect {
    ShapeInterface shapeInterface;
    double left;
    double top;
    double right;
    double bottom;
} Rect;

ShapeInterface* ConstructCircle(double, double, double);
ShapeInterface* ConstructRect(double, double, double, double);
int PointIsInsideCircle(ShapeInterface*, double, double);
int PointIsInsideRect(ShapeInterface*, double, double);

int main() {
    int n = 0;
    scanf("%d", &n);

    ShapeInterface** shapeArray = malloc(sizeof(ShapeInterface*) * n);
    if (!shapeArray) {
        perror("malloc failed");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        int c = 0;
        double a1 = 0, a2 = 0, a3 = 0, a4 = 0;
        do {
            c = getchar();
        } while (c != 'C' && c != 'R');

        if (c == 'C') {
            scanf("%lf %lf %lf", &a1, &a2, &a3);
            shapeArray[i] = ConstructCircle(a1, a2, a3);
        } else {
            scanf("%lf %lf %lf %lf", &a1, &a2, &a3, &a4);
            shapeArray[i] = ConstructRect(a1, a2, a3, a4);
        }
    }

    int m = 0;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        double px = 0, py = 0;
        int collided = 0;
        scanf("%lf %lf", &px, &py);

        for (int j = 0; j < n; j++) {
            if (shapeArray[j]->isPointInside(shapeArray[j], px, py)) {
                collided = 1;
                break;
            }
        }

        if (collided)
            printf("YES\n");
        else
            printf("NO\n");
    }

    for (int i = 0; i < n; i++) {
        free(shapeArray[i]);
    }
    free(shapeArray);

    return 0;
}

ShapeInterface* ConstructCircle(double cx, double cy, double r) {
    Circle* circle = malloc(sizeof(Circle));
    if (!circle) {
        perror("malloc failed");
        exit(1);
    }
    circle->centerX = cx;
    circle->centerY = cy;
    circle->radius = r;
    circle->shapeInterface.isPointInside = PointIsInsideCircle;
    return (ShapeInterface*)circle;
}

ShapeInterface* ConstructRect(double right, double top, double left, double bottom) {
    Rect* rect = malloc(sizeof(Rect));
    if (!rect) {
        perror("malloc failed");
        exit(1);
    }
    rect->left = left;
    rect->top = top;
    rect->right = right;
    rect->bottom = bottom;
    rect->shapeInterface.isPointInside = PointIsInsideRect;
    return (ShapeInterface*)rect;
}

int PointIsInsideCircle(ShapeInterface* shape, double px, double py) {
    Circle* circle = (Circle*)shape;
    double x_dif = px - circle->centerX;
    double y_dif = py - circle->centerY;
    double distanceSquared = x_dif * x_dif + y_dif * y_dif;
    return distanceSquared <= circle->radius * circle->radius;
}

int PointIsInsideRect(ShapeInterface* shape, double px, double py) {
    Rect* rect = (Rect*)shape;
    return (px >= rect->left && px <= rect->right) && (py <= rect->top && py >= rect->bottom);
}
