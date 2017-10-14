#include "JumpingHippo.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* JumpingHippo::createScene()
{
    return JumpingHippo::create();
}

bool JumpingHippo::init()
{
    if ( !Scene::initWithPhysics() )
    {


        return false;
    }

    getPhysicsWorld()->setGravity(Vec2::ZERO);

    initHippoSprite();
    initSpawner();
    initClickListener();

    return true;
}

void JumpingHippo::initHippoSprite()
{
    hippoSprite = Sprite::create("Hippo.png");
    
    hippoSprite->setPosition(Director::getInstance()->getVisibleSize()/2);
    hippoSprite->setScale(0.1f);

    
    addChild(hippoSprite, 1);
    
}


void JumpingHippo::initSpawner()
{


    auto size = Director::getInstance()->getVisibleSize();
    schedule([=](float dt){


        if (enemyCount % 2 == 0) {
            Sprite *spikesSprite = Sprite::create("SpikeBall.png");
            context->addChild(spikesSprite);

            spikesSprite->setScale(0.25f);
            spikesSprite->setPosition(Vec2(size.width, size.height / 2));
            auto jump = JumpBy::create(0.8, Vec2::ZERO, 150, 1);
            auto moveToLeft = MoveTo::create(2.f, Vec2(-100, size.height / 2));
            spikesSprite->runAction(jump);
            spikesSprite->runAction(moveToLeft);
        }else {


            Sprite *spikesSprite = Sprite::create("SpikeBall.png");
            context->addChild(spikesSprite);

            spikesSprite->setScale(0.25f);
            spikesSprite->setPosition(Vec2(size.width, size.height / 2));

            auto moveToLeft = MoveTo::create(2.f, Vec2(-100, size.height / 2));
            spikesSprite->runAction(moveToLeft);


        }

        enemyCount++;
    }, 1.f, -1, 1.f, "spawnerCallBack");
}



void JumpingHippo::initClickListener()
{
    auto scoreLabel = Label::create();
    addChild(scoreLabel);
    auto mouseListener = EventListenerTouchOneByOne::create();
    
    mouseListener->onTouchBegan = [=](Touch* touch, Event* event){
        auto rotate = RotateBy::create(0.4, 360);
        auto jump = JumpBy::create(0.8, Vec2::ZERO, 150, 1);

        if (hippoSprite -> getPosition()== Director::getInstance()->getVisibleSize()/2){
            hippoSprite->runAction(rotate);
            hippoSprite->runAction(jump);
            jumpCounter++;
            auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
            audio->playEffect("please.wav", false, 1.0f, 1.0f, 1.0f);
            scoreLabel->setPosition(Vec2(50,100));
            scoreLabel->setSystemFontSize(12);
            scoreLabel->setString(std::to_string(jumpCounter));

        }


        return true;
    };
    mouseListener->onTouchMoved = [=](Touch* touch, Event* event){};
    
    mouseListener->onTouchEnded = [=](Touch* touch, Event* event){

    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

