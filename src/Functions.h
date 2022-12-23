#pragma once
#include "Classes.h"

Textures LoadTextures(const char*);
bool CheckCollisionsRectangles(Vector2, Vector2);
bool CheckCollisionTerrain(Game, int, int, int);
void HealTeammate(Game, int, int, int);
void Damage(Game, int,int ,int*, int*);
int CheckCollisions(Game, int, int, int, int, int);
void DayNightCycle(int*, int, int);
Rec** LoadEntites(int, int, Texture2D, Texture2D);
void DeallocateMem(Game, int);
Terrain* LoadTerrain(int, int, Texture2D, Texture2D, Vector2);
Potion LoadPotion(int, int, Texture2D, Game);
Avatar LoadAvatar(int, int, Texture2D, const char*);
void MoveWerewolves(Game, int, int, int, int);
void MoveVampires(Game, int, int, int, int);
bool CheckAvatarCollisions(Game, int);
void AOE_HEAL(int, int, Game, int);
Vector2 UpdateAvatar(Game, int, int, int*, float*, Sound);
void UpdateEntities(Game, int, int, int*, int*, bool*, int*, Sound);
void PauseGame(Game, int, int, bool*, bool*, Music);
float VolumeCheck(float);
void EndGame(int, int, string);
void CreateWindow(int, int, const char*);
