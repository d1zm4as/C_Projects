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

void DrawSecondHand(struct tm *t){
    float alpha_deg = ((float)(t->tm_sec))*6;
    printf("Current hour  = %d, current alpha deg =  %f\n",t->tm_hour, alpha_deg);
    float x_outer = center.x+secondHandLength*sinf(alpha_deg*DEG2RAD);
    float y_outer = center.y-secondHandLength*cosf(alpha_deg*DEG2RAD);
    Vector2 outer = {x_outer,y_outer};
    DrawLineEx(center, outer,2,LIME);
}




void DrawMinuteHand(struct tm *t){
    float second_alpha_progress = ((float)t->tm_min)/60;
    float alpha_deg = ((float)(t->tm_hour))*6+6.0*second_alpha_progress;
    printf("Current hour  = %d, current alpha deg =  %f\n",t->tm_hour, alpha_deg);
    float x_outer = center.x+minuteHandLength*sinf(alpha_deg*DEG2RAD);
    float y_outer = center.y-minuteHandLength*cosf(alpha_deg*DEG2RAD);
    Vector2 outer = {x_outer,y_outer};
    DrawLineEx(center, outer,6,BLUE);
}

void DrawHourHand(struct tm *t){
    float minute_alpha_progress = ((float)t->tm_min)/60;
    float alpha_deg = ((float)(t->tm_hour%12))*30+30.0*minute_alpha_progress;
    printf("Current hour  = %d, current alpha deg =  %f\n",t->tm_hour, alpha_deg);
    float x_outer = center.x+HourHandLenght*sinf(alpha_deg*DEG2RAD);
    float y_outer = center.y-HourHandLenght*cosf(alpha_deg*DEG2RAD);
    Vector2 outer = {x_outer,y_outer};
    DrawLineEx(center, outer,3,RED);
        // float x_innner = center.x+clockRadius*0.9*sinf(alpha_deg*DEG2RAD);
        // float y_inner = center.y+clockRadius*0.9*cosf(alpha_deg*DEG2RAD);
        // Vector2 outer = {x_outer,y_outer};
}

void DrawMinuteMarkers(){
    float alpha_deg = 0;
    for (int i = 0; i<60; i++){

        float outerPositionPercentage = 0.98;
        float innerPositionPercentage = 0.98 - (i%5==0?0.12:0.08);


        float x_innner = center.x+clockRadius*innerPositionPercentage*sinf(alpha_deg*DEG2RAD);
        float y_inner = center.y+clockRadius*innerPositionPercentage*cosf(alpha_deg*DEG2RAD);
        Vector2 inner = {x_innner,y_inner};
        float x_outer = center.x+clockRadius*outerPositionPercentage*sinf(alpha_deg*DEG2RAD);
        float y_outer = center.y+clockRadius*outerPositionPercentage*cosf(alpha_deg*DEG2RAD);
        Vector2 outer = {x_outer,y_outer};
        
        DrawLineEx(inner, outer,3,GRAY);
        alpha_deg+=360/60;
        
    }
        
}

int main(){

    time_t now = time(NULL);
    char *now_str = ctime(&now);
    printf("Now: %s\n",now_str);
    struct  tm *t = localtime(&now);
    
    InitWindow(WIDTH,HEIGHT, "Analog Clock");
    
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        now = time(NULL);
        t = localtime(&now);
        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircleV(center,clockRadius,RAYWHITE);
            DrawMinuteMarkers();
            DrawHourHand( t);
            DrawMinuteHand(t);
            DrawSecondHand(t);
            // DrawHourHand(center,t);
            // DrawMinuteMarkers(center,clockRadius);

        EndDrawing();
    }
    CloseWindow();
}
