//
//  ConstUtil.hpp
//  dungeonTiles
//
//  Created by Moon on 16/7/21.
//
//

#ifndef ConstUtil_hpp
#define ConstUtil_hpp

#include <stdio.h>
#include "cocos2d.h"

#define DesignResolutionWidth 1080
#define DesignResolutionHeight 1920

#define DRAGON_PIC "dragon.png"
#define LIFE_PIC "life.png"
#define SWORD_PIC "sword.png"
#define GOLD_PIC "gold.png"
#define EXCHANGE_PIC "exchange.png"
#define BACKGROUND_PIC "background.png"
#define GRID_PIC "grid.png"
#define DRAGON_COME_PIC "Card/dragon_come.png"
#define SPLASH_PIC "splash.png"

#define SWORD_CARD "sword_card.png"
#define LIFE_CARD "life_card.png"
#define DRAGON_CARD "dragon_card.png"
#define GOLD_CARD "gold_card.png"

#define GUIDE1 "Guide/guide1.png"
#define GUIDE2 "Guide/guide2.png"
#define GUIDE3 "Guide/guide3.png"

#define BTN_CONTINUE "game_button_continue.png"
#define BTN_SETTING "game_button_setting.png"
#define BTN_TUTORIAL "game_button_tutorial.png"
#define BTN_RETRY "game_button_retry.png"
#define BTN_MENU "game_button_menu.png"
#define BTN_PLAY "game_button_play.png"
#define BTN_HELP "game_button_help.png"
#define BTN_SOUND_OPEN "button_sound_open.png"
#define BTN_SOUND_OFF "button_sound_off.png"
#define BTN_BGM_OPEN "button_bgm_open.png"
#define BTN_BGM_OFF "button_bgm_off.png"
#define BTN_FINGER_TOUCH "finger_touch.png"
#define BTN_FINGER_MOVE "finger_move.png"
#define SKILL_NG "skill_ng.png"


#define NEXT_COLOR "next_color.png"

#define SKILL_NG "skill_ng.png"
#define SKILL_PLATE "skill_plate.png"
#define SKILL_CLOSE "skill_colose.png"
#define LOGO "logo.png"
#define GAMEOVER_RIBBON "gameover_ribbon.png"
#define GAMEOVER_RESULT_CARD "gameover_result_card.png"
#define GAMEOVER_CARD "gameover_card.png"
#define BUTTON_EXCHANGE "button_exchange.png"

#define PARTICLE_DRAGON_CURVE "Particle/particle_dragon_curve.plist"
#define PARTICLE_GOLD_CURVE "Particle/particle_gold_curve.plist"
#define PARTICLE_SWORD_CURVE "Particle/particle_sword_curve.plist"
#define PARTICLE_LIFE_CURVE "Particle/particle_life_curve.plist"

#define PARTICLE_BACKGROUND1 "Particle/particle_background1.plist"
#define PARTICLE_BACKGROUND2 "Particle/particle_background2.plist"
#define PARTICLE_BACKGROUND3 "Particle/particle_background3.plist"

#define PARTICLE_FIRE1 "Particle/particle_fire1.plist"
#define PARTICLE_FIRE2 "Particle/particle_fire2.plist"

#define PARTICLE_DRAGON_CARD_BG "Particle/particle_dragon_card_bg.plist"
#define PARTICLE_LIFE_CARD_BG "Particle/particle_life_card_bg.plist"
#define PARTICLE_SWORD_CARD_BG "Particle/particle_sword_card_bg.plist"
#define PARTICLE_GOLD_CARD_BG "Particle/particle_gold_card_bg.plist"

#define PARTICLE_DRAGON_BROKEN "Particle/particle_dragon_broken.plist"
#define PARTICLE_GOLD_BROKEN "Particle/particle_gold_broken.plist"
#define PARTICLE_SWORD_BROKEN "Particle/particle_sword_broken.plist"
#define PARTICLE_LIFE_BROKEN "Particle/particle_life_broken.plist"

#define PARTICLE_SWORD_SMOKE "Particle/particle_sword_smoke.plist"
#define PARTICLE_LIFE_SMOKE "Particle/particle_life_smoke.plist"
#define PARTICLE_DRAGON_SMOKE "Particle/particle_dragon_smoke.plist"
#define PARTICLE_GOLD_SMOKE "Particle/particle_gold_smoke.plist"

#define PARTICLE_DRAGON_COME "Particle/particle_dragon_come.plist"

#define FONT_ROUND_ZN "fonts/round_zn.ttf"

#define COLOR3B_NUMBER Color3B(78,22,64)
#define COLOR3B_SWORD_BG Color3B(37,165,153)
#define COLOR3B_GOLD_BG Color3B(254,201,39)
#define COLOR3B_DRAGON_BG Color3B(187,169,163)
#define COLOR3B_LIFE_BG Color3B(238,82,79)
#define COLOR3B_GAME_BG Color3B(138, 0, 139)
#define COLOR3B_MENU_BG Color3B(188,170,164)

#define AUDIO_BACKGROUND1 "Music/anotherplanet.m4a"
#define AUDIO_BACKGROUND2 "Music/apoptosis.m4a"
#define AUDIO_BUTTON "Music/button.wav"
#define AUDIO_BUTTON_SYSTEM "Music/button_system.wav"
#define AUDIO_DRAGON "Music/dragon.wav"
#define AUDIO_DRAGON_ATTACK "Music/dragon_attack.wav"
#define AUDIO_GOLD "Music/gold.wav"
#define AUDIO_LIFE "Music/life.wav"
#define AUDIO_SWORD "Music/sword.wav"
#define AUDIO_SWORD_ATTACK "Music/sword_attack.wav"
#define AUDIO_SWIPE "Music/swipe.wav"
#define AUDIO_POST_BONUS "Music/post_bonus.wav"
#define AUDIO_SHOOT "Music/shoot.wav"
#define AUDIO_GAMEOVER_SWORD "Music/gameover_sword.wav"
#define AUDIO_DRAGON_COME "Music/dragon_come.wav"

const int CARD_NUMBER_SIZE=50;
const int GUIDE_LALBEL_SIZE=120;
const int SCORE_NUMBER_SIZE=70;
const int NEXT_COLOR_SIZE=50;
const int CARD_SCORE_SIZE=70;

const int BACKGROUND_EXCHANGE_SPEED=20;

const int DRAGON_TAG=1;
const int LIFE_TAG=2;
const int SWORD_TAG=3;
const int GOLD_TAG=4;
const int EXCHANGE_TAG=5;
const int CELL_SIZE=240;

const int CARD_SIZE=190;

enum GameState
{
    GameStart=1,
    GameRunning=2,
    GamePause=3,
    GameOver=4,
    GameReset=5,
    Guide=6
};

enum CardState{
    Nochange=0,
    Move=1
};

enum MoveDirection{
    Left=1,
    Right=2,
    Up=3,
    Down=4
};

#endif /* ConstUtil_hpp */
