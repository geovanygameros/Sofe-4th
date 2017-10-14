#ifndef __JumpingHippo_SCENE_H__
#define __JumpingHippo_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class JumpingHippo : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    Sprite* hippoSprite;
    
    void initHippoSprite();
    
    void initSpawner();

    void spawnSprite(float dt);
    
    void initClickListener();

    JumpingHippo* context = this;

    CREATE_FUNC(JumpingHippo);

    int enemyCount = 0; //variable de clase
    int jumpCounter = 0;
};


#endif // JumpingHippo
