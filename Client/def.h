#pragma once


#define SINGLE(type) public:\
                        static type* GetInst()\
                        {\
                            static type mgr;\
                            return &mgr;\
                        }\
                        private:\
                            type();\
                            ~type();

#define DT CTimeMgr::GetInst()->GetDeltaTime()
#define FDT CTimeMgr::GetInst()->GetFocusDeltaTime()

#define IsPressed(KEY) KEY_STATE::PRESS == CKeyMgr::GetInst()->GetKeyState(KEY)
#define IsTap(KEY) KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(KEY)
#define IsRelease(KEY) KEY_STATE::RELEASE == CKeyMgr::GetInst()->GetKeyState(KEY)

#define SAFE_DELETE(p) if(nullptr != p) delete p; p = nullptr;
#define CLONE(type) virtual type* Clone() override { return new type(*this); }
#define COLLISION_LAYER(layer1, layer2) CCollisionMgr::GetInst()->CollisionLayerCheck(layer1, layer2)
#define IsLive(ptr) nullptr != ptr && IsValid(ptr)

#define MISSILE_MAX_SPEED 400.f
#define MAX_LAYER 20
#define PI 3.14159265f

#define TILE_SIZE 32
#define BUTTON_OUT_SIZE Vec2(4.f, 2.f)
#define	LASER_SIZE Vec2(6.f, 6.f)
#define PLAYER_SIZE Vec2(20.f, 32.f)
#define MINE_SIZE Vec2(20.f, 20.f)



#define LTRECT ((vColPos.x - vColScale.x / 2.f < vPlayerColPos.x && vColPos.x - vColScale.x / 2.f + 5.f > vPlayerColPos.x) && (vColPos.y - vColScale.y / 2.f < vPlayerColPos.y && vColPos.y - vColScale.y / 2.f + 5.f > vPlayerColPos.y))

#define RTRECT ((vColPos.x + vColScale.x / 2.f > vPlayerColPos.x && vColPos.x + vColScale.x / 2.f - 5.f < vPlayerColPos.x) && (vColPos.y - vColScale.y / 2.f < vPlayerColPos.y && vColPos.y - vColScale.y / 2.f + 5.f > vPlayerColPos.y))

#define LBRECT ((vColPos.x - vColScale.x / 2.f < vPlayerColPos.x && vColPos.x - vColScale.x / 2.f + 5.f > vPlayerColPos.x) && (vColPos.y + vColScale.y / 2.f > vPlayerColPos.y && vColPos.y + vColScale.y / 2.f - 5.f < vPlayerColPos.y))

#define RBRECT ((vColPos.x + vColScale.x / 2.f > vPlayerColPos.x && vColPos.x + vColScale.x / 2.f - 5.f < vPlayerColPos.x) && (vColPos.y + vColScale.y / 2.f > vPlayerColPos.y && vColPos.y + vColScale.y / 2.f - 5.f < vPlayerColPos.y))

#define GetpPlayer dynamic_cast<CPlayer*>(CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::PLAYER).at(0))
#define AddObject_D(pObject, LAYERTYPE) CSceneMgr::GetInst()->GetCurScene()->AddObject(pObject, LAYERTYPE);

#define SwitchTrueFalse(toSwitch) \
if(toSwitch == true) \
    toSwitch = false; \
else\
    toSwitch = true

#define IsDebugModeD CDebugMgr::GetInst()->IsDebugMode()
#define GetModeStatusD CDebugMgr::GetInst()->GetModeStatus()

#define IsInvincibleD (GetModeStatusD & (WORD)DEBUG_MODE::PLAYER_INVINCIBLE)


enum SCENE_TYPE
{
    TOOL,
    LOGO,
    START,
    STAGE_01,
    STAGE_02,
    STAGE_03,
    STAGE_04,
    STAGE_05,
    STAGE_06,
    STAGE_07,
    STAGE_08,
    STAGE_09,
    STAGE_10,
    STAGE_11,
    STAGE_12,
    STAGE_13,
    STAGE_14,
    STAGE_15,
    STAGE_16,
    ENDING,
    END,
};

enum class PEN_COLOR
{
    RED,
    GREEN,
    BLUE,
    WHITE,
    BROWN,
    END,
};

enum class BRUSH_COLOR
{
    HOLLOW, // 투명 브러쉬
    BLACK,  // 검은 브러쉬
    GRAY,	// 회색 브러쉬
    END,
};

enum class COMPONENT_TYPE
{	
    AI,
    ANIMATOR,	
    RIGIDBODY,
    COLLIDER,
    GAUGE,
    POS_SELECTOR,
    END,
};



enum class LAYER_TYPE
{
    //DEFAULT,
    //BACKGROUND,
    TILE,
    TILE_ADDED,
    EFFECT,
    CRYSTAL, 
    COLLIDEROBJ,
    BLOCKCHECKER,
    PLAYER,
    PLAYER_OPTION,
    SPAWNER,
    MINE,
    PROJECTILES,
    FRAGMENT,
    EXPLOSION,
    LASERBODY,
    LASER,
    LASERSTOPPER,
    
    UI = MAX_LAYER - 1,
    END = MAX_LAYER,
};

enum class EVENT_TYPE
{
    CREATE_OBJECT, // first : Object Adress, second : Layer Type
    DELETE_OBJECT, // first : Object Adress, 
    SCENE_CHANGE,  // first : Scene Type

    END,
};

//enum class TILE_TYPE
//{
//	SPAWN		= 31,
//	WALL		= 192,
//	BLOCK		= 193,
//	BACKGROUND	= 20,
//	EXIT		= 63,
//	BUTTON		= 95 // 임시
//};

enum class MISSILE_OPTION
{
    GUIDED,
    LINE,
    ACCEL,
    ACCELX,
    EXPLOSIVE,
    EXPLOSIVE_X,
    FRAGMENTS,
    FRAGMENTS_X,
};

enum class EXPLOSION_TYPE
{
    FIRST,
    SECOND,
    THIRD,
};

enum class COLLISION_DIRECTION
{
    HORIZONTAL,
    VERTICAL,
    HORIZONTAL_VERTICAL,
    NONE
};

enum class COLLIDER_TYPE
{
    BLOCK,
    EXIT_BLOCK,
    SPAWN,
    WALL,
    THORN,
    BUTTON_IN,
    BUTTON_OUT,
    SCENE_CHANGE,
    END
};

enum class RECTPOSITION
{
    LT,
    RT,
    LB,
    RB,
};

enum class MOVE_DIRECTION
{
    L,
    JL,
    R,
    JR,
    U,
    D,
    
};

enum class CRYSTAL_TYPE
{
    STARTER,
    ENHANCER,
    END,
};

enum class LASER_TYPE
{
    HORIZONTAL,
    VERTICAL
};

enum class TOOL_MODE
{
    TILE,
    TILE_SELECT,
    OBJECT,
    ANIMATION,
    NONE
};

enum class DEBUG_MODE
{
    COLLIDER_RENDER = 0x01,
    PLAYER_INVINCIBLE = 0x02,
    FOCUS_MAX = 0x04,  
};