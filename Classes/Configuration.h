#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

//Environment:
#define SCENE_SPEED 5
#define TURN_ON_TEST 1
#define GRAVITY_FACTOR -10

//Character:
//Speed in each frame.
#define SUBMARINE_SMOOTH_ACCELERATION 10
#define SUBMARINE_ACCELERATION_X 15
#define SUBMARINE_ACCELERATION_Y 10
#define SUBMARINE_SPEED_Y 0.5
#define SUBMARINE_SPEED_X 0.2
#define SUBMARINE_SCALE 0.25

#define SHARK_SCALE 0.5
//Obstacles:
#define OBSTACLE_SPEED 250
//#define 
//Resources Paths:

//Intro Scene:
#define RES_BACKGROUND "Background/BG Preview.png"
#define RES_GAME_TITLE "Game Title.png"

//Entities:
#define RES_ENTITY_SUBMARINE "Submarine Sprite Sheets/Sumbarine-1/Submarine-1_%03d.png"
#define RES_ENTITY_SUBMARINE_FIRST_TEXTURE "Submarine Sprite Sheets/Sumbarine-1/Submarine-1_000.png"
#define RES_ENTITY_SUBMARINE_BODY "Submarine Sprite Sheets/Sumbarine-1/Submarine-1_000.json"
#define RES_ENTITY_SUBMARINE_DAMAGED_FIRST_TEXTURE "Submarine Sprite Sheets/Sumbarine-1/Submarine-1-die_000.png"
#define RES_ENTITY_SUBMARINE_DAMAGED "Submarine Sprite Sheets/Sumbarine-1/Submarine-1-die_%03d.png"

#define RES_ENTITY_SHARK "Shark Sprite Sheets/Shark-2/Swim_%03d.png"
#define RES_ENTITY_SHARK_FIRST_TEXTURE "Shark Sprite Sheets/Shark-2/Swim_000.png"
#define RES_ENTITY_SHARK_BODY "Shark Sprite Sheets/Shark-2/Swim_000.json"
#define RES_ENTITY_SHARK_HIT_FIRST_TEXTURE "Shark Sprite Sheets/Shark-2/Hit_000.png"
#define RES_ENTITY_SHARK_HIT "Shark Sprite Sheets/Shark-2/Hit_%03d.png"

#define RES_ENTITY_OBSTACLE_ROCK_UP "Obstacles/1.png"
#define RES_ENTITY_OBSTACLE_ROCK_UP_BODY "Obstacles/1.json"

#define RES_ENTITY_OBSTACLE_ROCK_DOWN "Obstacles/2.png"
#define RES_ENTITY_OBSTACLE_ROCK_DOWN_BODY "Obstacles/2.json"

//UI:
#define RES_UI_BUTTON_PLAY "GameUi/ButtonPlay.png"
#define RES_UI_BUTTON_PLAY_CLICKED "GameUi/ButtonPlayC.png"

#define RES_UI_BUTTON_REPLAY "GameUi/Ui images/Buttons (6).png"
#define RES_UI_BUTTON_MENU "GameUi/Ui images/Buttons (4).png"

#define RES_UI_BUTTON_INCREASE_X "GameUi/Ui images/Buttons (47).png"
#define RES_UI_BUTTON_INCREASE_Y "GameUi/Ui images/Buttons (45).png"

//Other:
#define RES_NOTHING_BACKGROUND "Submarine Sprite Sheets/Sumbarine-1/empty.png"
#endif