/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//definicion de variables para FPS 3d

static Camera3D camera = {0};
static Vector3 cubePosition = {0};

// Variables para el sistema de salto
static float playerHeight = 2.0f;        // Altura del jugador (ojos)
static float groundLevel = 2.0f;         // Nivel del suelo para los ojos (Y)
static float verticalVelocity = 0.0f;    // Velocidad vertical actual
static float gravity = -20.0f;           // Gravedad (negativa = hacia abajo)
static float jumpForce = 8.0f;           // Fuerza del salto
static bool isOnGround = true;           // ¿Está el jugador en el suelo?



//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;

    // Configurar cámara FPS
    camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };    // Posición del jugador
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Hacia dónde mira
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Vector arriba
    camera.fovy = 60.0f;                                 // Campo de visión
    camera.projection = CAMERA_PERSPECTIVE;              // Proyección perspectiva
    
    cubePosition = (Vector3){ 0.0f, 1.0f, 0.0f };       // Cubo elevado para verlo
    
    // Inicializar sistema de salto
    verticalVelocity = 0.0f;
    isOnGround = true;
    groundLevel = 2.0f;  // Altura de los ojos cuando está en el suelo
    
    DisableCursor();  // Ocultar cursor para modo FPS
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    float deltaTime = GetFrameTime();  // Tiempo transcurrido desde el último frame
    
    // SISTEMA DE SALTO (ANTES de UpdateCamera para que la física se aplique primero)
    
    // Detectar si presiona ESPACIO para saltar
    if (IsKeyPressed(KEY_SPACE) && isOnGround)
    {
        verticalVelocity = jumpForce;  // Aplicar impulso hacia arriba
        isOnGround = false;             // Ya no está en el suelo
        PlaySound(fxCoin);              // Sonido de salto (temporal)
    }
    
    // Aplicar gravedad (siempre, esté en el aire o no)
    verticalVelocity += gravity * deltaTime;
    
    // Actualizar SOLO la posición Y de la cámara (NO el target)
    camera.position.y += verticalVelocity * deltaTime;
    
    // Detectar colisión con el suelo
    if (camera.position.y <= groundLevel)
    {
        camera.position.y = groundLevel;    // Ajustar a la altura del suelo
        verticalVelocity = 0.0f;            // Detener velocidad vertical
        isOnGround = true;                  // Ahora está en el suelo
    }
    
    // Actualizar cámara con controles FPS (WASD + Mouse)
    // Esto permite mirar arriba/abajo libremente
    UpdateCamera(&camera, CAMERA_FIRST_PERSON);
    
    // ESC para salir
    if (IsKeyPressed(KEY_ESCAPE))
    {
        finishScreen = 1;
    }
    
    // Tecla Y para resetear posición (debug)
    if (IsKeyPressed(KEY_Y))
    {
        camera.position = (Vector3){ 0.0f, 2.0f, 4.0f }; 
        verticalVelocity = 0.0f;
        isOnGround = true;
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    // DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    // Vector2 pos = { 20, 10 };
    // DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);
    // DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

    BeginMode3D(camera);
    
        // Dibujar piso (grid)
        DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY);
        DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Pared
        DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Pared
        DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Pared
        
        // Cubo de referencia
        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
        
        DrawGrid(10, 1.0f);
        
    EndMode3D();
    
    // UI 2D encima
    DrawText("FPS CONTROLS:", 10, 10, 20, BLACK);
    DrawText("- WASD to move", 10, 35, 15, DARKGRAY);
    DrawText("- Mouse to look around", 10, 55, 15, DARKGRAY);
    DrawText("- SPACE to jump", 10, 75, 15, DARKGRAY);
    DrawText("- ESC to exit", 10, 95, 15, DARKGRAY);
    DrawText("- Y to reset position", 10, 115, 15, DARKGRAY);
    
    // Info de debug del salto
    DrawText(TextFormat("Y Position: %.2f", camera.position.y), 10, 145, 15, isOnGround ? GREEN : RED);
    DrawText(TextFormat("X Position: %.2f", camera.position.x), 10, 200, 15, PURPLE);
    DrawText(TextFormat("z Position: %.2f", camera.position.z), 10, 215, 15, PURPLE);
    DrawText(TextFormat("Velocity: %.2f", verticalVelocity), 10, 165, 15, BLUE);
    DrawText(isOnGround ? "ON GROUND" : "IN AIR", 10, 185, 15, isOnGround ? GREEN : ORANGE);
    
    DrawFPS(10, GetScreenHeight() - 30);

}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    EnableCursor();
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}