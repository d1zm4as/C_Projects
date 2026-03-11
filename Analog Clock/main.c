#include <stdio.h>
#include <time.h>
#include <math.h>
#include <raylib.h>

const int HEIGHT =  600;
const int WIDTH =  600;
const float xCenter = WIDTH/2;
const float yCenter = HEIGHT/2;
const Vector2 center  = {xCenter,yCenter};
const float clockRadius = HEIGHT*0.4;
const float HourHandLenght = clockRadius*0.4;
const float minuteHandLength = clockRadius *0.65;
const float secondHandLength = clockRadius *0.8;

void DrawMinuteMarkers(Vector2 center,float clockRadius){
    float alpha_deg = 0;
    for (int i = 0; i<60; i++){
        float x_innner = center.x+clockRadius*0.9*sinf(alpha_deg*DEG2RAD);
        float y_inner = center.y+clockRadius*0.9*cosf(alpha_deg*DEG2RAD);
        Vector2 inner = {x_innner,y_inner};
        float x_outer = center.x+clockRadius*0.98*sinf(alpha_deg*DEG2RAD);
        float y_outer = center.y+clockRadius*0.98*cosf(alpha_deg*DEG2RAD);
        Vector2 outer = {x_outer,y_outer};
        DrawLineEx(inner, outer,3,GRAY);
        alpha_deg+=360/60;
        
    }
        
}

int main(){

    time_t now = time(NULL);
    char *now_str = ctime(&now);
    printf("Now: %s\n",now_str);
    struct  tm *t = localtime(now);
    
    InitWindow(WIDTH,HEIGHT, "Analog Clock");

    float xCenter =WIDTH/2;
    float yCenter = HEIGHT/2;
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircleV(center,clockRadius,RAYWHITE);
            DrawMinuteMarkers(center,clockRadius);
            DrawHourHand(center,t);
        EndDrawing();
    }
    CloseWindow();
}
