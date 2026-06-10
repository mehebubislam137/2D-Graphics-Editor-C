#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 60
#define COLS 60
#define MAX_OBJECTS 100

char canvas[ROWS][COLS];

// Object Structure
typedef struct {
    int id;
    int type; // 1-Line 2-Rectangle 3-Triangle 4-Circle

    int x1, y1, x2, y2;
    int x3, y3;
    int radius;
} Object;

Object objects[MAX_OBJECTS];
int objectCount = 0;

void initializeCanvas();
void displayCanvas();
void plot(int x, int y, char ch);
void drawLine(int x1, int y1, int x2, int y2, char ch);
void drawRectangle(int x1, int y1, int x2, int y2, char ch);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, char ch);
void drawCircle(int xc, int yc, int r, char ch);
void drawObject(Object obj, char ch);
void addObject();
void deleteObject();
void modifyObject();

int main() {
    initializeCanvas();
    int choice;
    while (1) {

        printf("\n===== 2D Graphics Editor =====\n");
        printf("1. Add Object\n");
        printf("2. Delete Object\n");
        printf("3. Modify Object\n");
        printf("4. Display Picture\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");

        scanf("%d", &choice);

        switch (choice) {

        case 1:
            addObject();
            break;

        case 2:
            deleteObject();
            break;

        case 3:
            modifyObject();
            break;

        case 4:
            displayCanvas();
            break;

        case 5:
            return 0;

        default:
            printf("Invalid Choice\n");
        }
    }

    return 0;
}

// Initialize Canvas 
void initializeCanvas() {
    for (int i=0; i<ROWS; i++)
        for (int j=0; j<COLS; j++)
            canvas[i][j]='_';
}

//  Display Canvas 
void displayCanvas(){
    printf("\n");

    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLS; j++){
            if(canvas[i][j]=='_'){
                printf("  ");
            }else{
                printf("%c ",canvas[i][j]);
            }
        }
        printf("\n");
    }
}

// Plot Pixel
void plot(int x, int y, char ch) {
    if (x>=0 && x<ROWS && y>=0 && y<COLS)
        canvas[x][y]=ch;
}

// Draw Line 
void drawLine(int x1, int y1, int x2, int y2, char ch) {
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);

    int sx = (x1<x2) ? 1 : -1;
    int sy = (y1<y2) ? 1 : -1;

    int err=dx-dy;

    while(1){
        plot(x1, y1, ch);

        if (x1==x2 && y1==y2){
            break;
        }

        int e2=2*err;

        if (e2>-dy){
            err-=dy;
            x1+=sx;
        }

        if (e2<dx){
            err+=dx;
            y1+=sy;
        }
    }
}

// Draw Rectangle 
void drawRectangle(int x1, int y1, int x2, int y2, char ch) {

    drawLine(x1, y1, x1, y2, ch);
    drawLine(x1, y2, x2, y2, ch);
    drawLine(x2, y2, x2, y1, ch);
    drawLine(x2, y1, x1, y1, ch);
}

// Draw Triangle
void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3,
                  char ch) {

    drawLine(x1, y1, x2, y2, ch);
    drawLine(x2, y2, x3, y3, ch);
    drawLine(x3, y3, x1, y1, ch);
}

// Draw Circle
void drawCircle(int xc, int yc, int r, char ch) {

    int x = 0;
    int y = r;
    int d = 1 - r;

    while(x<=y){

        plot(xc+x, yc+y, ch);
        plot(xc-x, yc+y, ch);
        plot(xc+x, yc-y, ch);
        plot(xc-x, yc-y, ch);

        plot(xc+y, yc+x, ch);
        plot(xc-y, yc+x, ch);
        plot(xc+y, yc-x, ch);
        plot(xc-y, yc-x, ch);

        if (d<0){
            d+=2*x+3;
        }else{
            d+=2*(x-y)+5;
            y--;
        }
        x++;
    }
}
// Draw Object 
void drawObject(Object obj, char ch) {

    switch (obj.type) {

    case 1:
        drawLine(obj.x1, obj.y1,
                 obj.x2, obj.y2, ch);
        break;

    case 2:
        drawRectangle(obj.x1, obj.y1,
                      obj.x2, obj.y2, ch);
        break;

    case 3:
        drawTriangle(obj.x1, obj.y1,
                     obj.x2, obj.y2,
                     obj.x3, obj.y3, ch);
        break;

    case 4:
        drawCircle(obj.x1, obj.y1,
                   obj.radius, ch);
        break;
    }
}

// Add Object
void addObject() {

    Object obj;

    obj.id=objectCount+1;

    printf("\n1.Line\n2.Rectangle\n3.Triangle\n4.Circle\n");
    printf("Enter object type: ");
    scanf("%d", &obj.type);

    if(obj.type == 1){
        printf("Enter x1 y1 x2 y2: ");
        scanf("%d%d%d%d",
              &obj.x1, &obj.y1,
              &obj.x2, &obj.y2);
    }

    else if(obj.type == 2){
        printf("Enter top-left and bottom-right coordinates:\n");
        scanf("%d%d%d%d",
              &obj.x1, &obj.y1,
              &obj.x2, &obj.y2);
    }

    else if(obj.type == 3){
        printf("Enter x1 y1 x2 y2 x3 y3:\n");
        scanf("%d%d%d%d%d%d",
              &obj.x1, &obj.y1,
              &obj.x2, &obj.y2,
              &obj.x3, &obj.y3);
    }

    else if(obj.type == 4){
        printf("Enter center x y and radius:\n");
        scanf("%d%d%d",
              &obj.x1, &obj.y1,
              &obj.radius);
    }

    objects[objectCount++] = obj;

    drawObject(obj, '*');
}

// Delete Object
void deleteObject() {

    int id;
    printf("Enter Object ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < objectCount; i++) {

        if (objects[i].id == id) {
            drawObject(objects[i], '_');

            for (int j = i; j < objectCount - 1; j++)
                objects[j] = objects[j + 1];

            objectCount--;

            printf("Object Deleted\n");
            return;
        }
    }

    printf("Object Not Found\n");
}

// Modify Object 
void modifyObject() {

    int id;

    printf("Enter Object ID to modify: ");
    scanf("%d", &id);

    for (int i=0; i<objectCount; i++) {
        if (objects[i].id==id) {
            drawObject(objects[i], '_');
            printf("Re-enter details:\n");

            Object obj;
            obj.id=id;

            printf("1.Line\n2.Rectangle\n3.Triangle\n4.Circle\n");
            printf("Enter type: ");
            scanf("%d", &obj.type);

            if (obj.type==1){
                scanf("%d%d%d%d",
                      &obj.x1, &obj.y1,
                      &obj.x2, &obj.y2);

            }else if (obj.type==2){
                scanf("%d%d%d%d",
                      &obj.x1, &obj.y1,
                      &obj.x2, &obj.y2);

            }else if (obj.type==3){
                scanf("%d%d%d%d%d%d",
                      &obj.x1, &obj.y1,
                      &obj.x2, &obj.y2,
                      &obj.x3, &obj.y3);

            }else if (obj.type==4){
                scanf("%d%d%d",
                      &obj.x1, &obj.y1,
                      &obj.radius);

            }
            objects[i]=obj;

            drawObject(obj, '*');

            printf("Object Modified\n");
            return;
        }
    }

    printf("Object Not Found\n");
}
