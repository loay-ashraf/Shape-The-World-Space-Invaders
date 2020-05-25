// Sprite.h
// Runs on LM4F120/TM4C123
// Jonathan Valvano
// September 26, 2013
// Example code from edX chapter 15

void Sprite_Init(int Level);
void Sprite_Draw(void);
void Sprite_MovePlayer(int x_position);
void Sprite_MissileAttack(void);
void Sprite_SpecialMissileAttack(void);
void Sprite_CheckCollision(void);
int Sprite_CheckStatus(void);
