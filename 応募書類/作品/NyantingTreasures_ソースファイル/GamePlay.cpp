//------------------------
//ファイル名：GamePlay.cpp
//作成者　　：中山薫
//所属		：日本電子専門学校　ゲーム制作研究科
//作成日　　：2020/11/30
//最終更新　：2020/02/10
//------------------------

#include "COriginalGameApp.h"
#include "GameResource.h"

//背景の数
#define BackGround0_Count (3)
#define BackGround1_Count (5)
#define BackGround2_Count (8)
#define BackGround3_Count (1)

//床の数
#define Ground0_Count (8)
#define Ground1_Count (13)
#define Ground2_Count (10)
#define Ground3_Count (3)
//穴の数
#define Hole0_Count (8)
#define Hole1_Count (16)
#define Hole2_Count (12)
//崖の数
#define CliffSide0_Count   (4)
#define CliffCenter0_Count (2)
#define CliffSide1_Count   (8)
#define CliffCenter1_Count (7)
#define CliffSide2_Count   (18)
#define CliffCenter2_Count (7)

//丘の数
#define HillSide1_Count      (12)
#define HillCenter1_Count    (9)
#define HillCollision1_Count (15)
#define HillSide2_Count      (14)
#define HillCenter2_Count    (15)
#define HillCollision2_Count (22)

//ブロックの数
#define Block1_Count (9)
#define Block2_Count (5)

//看板の数
#define Signboard0_Count (2)
#define Signboard1_Count (4)
#define Signboard2_Count (3)

//トゲの数
#define Needl2_Count (29)

//リフトの数
#define MoveLift2_Count (12)
#define FallLift2_Count (10)

//煮干しの数
#define Niboshi1_Count (78)
#define Niboshi2_Count (157)
//かつおぶしの数
#define Katuobushi_Count (10)

/*
 * ゲーム本編の処理を行う部分
 */

 //変数宣言----------------------------
 //プレイ画面のフェーズを管理する変数
ePhase g_PlayPhase = eBegin;
//プレイ画面から次へと進むときのフローを管理する変数
eGameStatus g_NextStatusFromPlay = eNone;

//背景の画像を管理する変数
CPicture* g_pBackGround[BackGround2_Count] = { NULL, };
//サイズ
const float BackGround_Size_X = WINDOW_WIDTH * 2;
const float BackGround_Size_Y = WINDOW_HEIGHT;

//床の画像を管理する変数
CPicture* g_pGround[Ground1_Count] = { NULL, };
//サイズ
const float Ground_Size_X = 810.0f;
const float Ground_Size_Y = WINDOW_HEIGHT / 8;
//設置場所
//チュートリアル
XMFLOAT2 Ground0_Pos[Ground0_Count] =
{
    {-555.0f,  -WINDOW_HEIGHT / 2 + 67.5f},
    {255.0f,   -WINDOW_HEIGHT / 2 + 67.5f},
    {1035.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {2464.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {3953.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {5631.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {7309.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {8119.0f , -WINDOW_HEIGHT / 2 + 67.5f},
};
//ステージ1
XMFLOAT2 Ground1_Pos[Ground1_Count] =
{
    {-555.0f,  -WINDOW_HEIGHT / 2 + 67.5f},
    {255.0f,   -WINDOW_HEIGHT / 2 + 67.5f},
    {1664.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {3622.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {4432.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {5242.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {6681.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {8220.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {11327.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {13975.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {15514.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {17153.0f , -WINDOW_HEIGHT / 2 + 67.5f},
    {17963.0f , -WINDOW_HEIGHT / 2 + 67.5f},
};
//ステージ2
XMFLOAT2 Ground2_Pos[Ground2_Count] =
{
    {-555.0f,  -WINDOW_HEIGHT / 2 + 67.5f},
    {255.0f,   -WINDOW_HEIGHT / 2 + 67.5f},
    {1664.0f,   -WINDOW_HEIGHT / 2 + 67.5f},
    {3073.0f,   -WINDOW_HEIGHT / 2 + 67.5f},
    {3883.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {7487.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {21347.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {23835.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {27134.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {27944.0f, -WINDOW_HEIGHT / 2 + 67.5f},
};
//ステージ3
XMFLOAT2 Ground3_Pos[Ground3_Count] =
{
    {-555.0f,  -WINDOW_HEIGHT / 2 + 67.5f},
    {255.0f,   -WINDOW_HEIGHT / 2 + 67.5f},
    {1065.0f,  -WINDOW_HEIGHT / 2 + 67.5f},
};

//穴の画像を管理する変数
CPicture* g_pHole[Hole1_Count] = { NULL, };
//サイズ
const float Hole_Size_X = 165.0f;
const float Hole_Size_Y = 135.0f;
//設置場所
//チュートリアル
XMFLOAT2 Hole0_Pos[Hole0_Count] =
{
    {1522.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {1977.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {2951.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {3466.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {4440.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {5144.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {6118.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {6822.0f, -WINDOW_HEIGHT / 2 + 67.5f},
};
//ステージ１
XMFLOAT2 Hole1_Pos[Hole1_Count] =
{
    {742.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {1177.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {2151.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {3155.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {5729.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {6194.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {7168.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {7733.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {8707.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {10840.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {11814.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {13488.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {14452.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {15027.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {16001.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {16666.0f, -WINDOW_HEIGHT / 2 + 67.5f},
};
//ステージ2
XMFLOAT2 Hole2_Pos[Hole2_Count] =
{
    {742.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {1177.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {2151.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {2586.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {4370.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {7000.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {7974.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {20900.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {21834.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {23348.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {24322.0f, -WINDOW_HEIGHT / 2 + 67.5f},
    {26647.0f, -WINDOW_HEIGHT / 2 + 67.5f},
};

//崖の画像を管理する変数
CPicture* g_pCliffSide[CliffSide2_Count] = { NULL };
CPicture* g_pCliffCenter[CliffCenter1_Count] = { NULL };
//サイズ
const float Cliff_Size_X = 135.0f;
const float Cliff_Size_Y = 540.0f;
//設置場所
//チュートリアル
XMFLOAT2 CliffSide0_Pos[CliffSide0_Count] =
{
    {4590.0f, -WINDOW_HEIGHT / 2 + 140.0f},
    {4994.0f, -WINDOW_HEIGHT / 2 + 140.0f},
    {6268.0f, -WINDOW_HEIGHT / 2 + 250.0f},
    {6672.0f, -WINDOW_HEIGHT / 2 + 250.0f},
};
XMFLOAT2 CliffCenter0_Pos[CliffCenter0_Count] =
{
    {4792.0f, -WINDOW_HEIGHT / 2 + 140.0f},
    {6470.0f, -WINDOW_HEIGHT / 2 + 250.0f},
};
//ステージ１
XMFLOAT2 CliffSide1_Pos[CliffSide1_Count] =
{
    {2301.0f, -WINDOW_HEIGHT / 2 + 85.0f},
    {2705.0f, -WINDOW_HEIGHT / 2 + 85.0f},
    {8857.0f, -WINDOW_HEIGHT / 2 + 140.0f},
    {9531.0f, -WINDOW_HEIGHT / 2 + 140.0f},
    {10016.0f, -WINDOW_HEIGHT / 2 + 140.0f},
    {10690.0f, -WINDOW_HEIGHT / 2 + 140.0f},
    {11964.0f, -WINDOW_HEIGHT / 2 + 250.0f},
    {12638.0f, -WINDOW_HEIGHT / 2 + 250.0f},
};
XMFLOAT2 CliffCenter1_Pos[CliffCenter1_Count] =
{
    {2502.0f, -WINDOW_HEIGHT / 2 + 85.0f},
    {9059.0f, -WINDOW_HEIGHT / 2 + 140.0f},
    {9329.0f, -WINDOW_HEIGHT / 2 + 140.0f},
    {10218.0f, -WINDOW_HEIGHT / 2 + 140.0f},
    {10488.0f, -WINDOW_HEIGHT / 2 + 140.0f},
    {12166.0f, -WINDOW_HEIGHT / 2 + 250.0f},
    {12436.0f, -WINDOW_HEIGHT / 2 + 250.0f},
};
//ステージ2
XMFLOAT2 CliffSide2_Pos[CliffSide2_Count] =
{
    {892.0f, -WINDOW_HEIGHT / 2 + 85.0f},
    {1027.0f, -WINDOW_HEIGHT / 2 + 85.0f},
    {2301.0f, -WINDOW_HEIGHT / 2 + 85.0f},
    {2436.0f, -WINDOW_HEIGHT / 2 + 85.0f},
    {4520.0f, -WINDOW_HEIGHT / 2 + -25.0f},
    {4924.0f, -WINDOW_HEIGHT / 2 + -25.0f},
    {8124.0f, -WINDOW_HEIGHT / 2 + 250.0f},
    {8528.0f, -WINDOW_HEIGHT / 2 + 250.0f},
    {12200.0f, -WINDOW_HEIGHT / 2 + 250.0f},
    {12604.0f, -WINDOW_HEIGHT / 2 + 250.0f},
    {12940.0f, -WINDOW_HEIGHT / 2 + 250.0f},
    {13344.0f, -WINDOW_HEIGHT / 2 + 250.0f},
    {17092.0f, -WINDOW_HEIGHT / 2 + 305.0f},
    {17496.0f, -WINDOW_HEIGHT / 2 + 305.0f},
    {17831.0f, -WINDOW_HEIGHT / 2 + 305.0f},
    {18235.0f, -WINDOW_HEIGHT / 2 + 305.0f},
    {24472.0f, -WINDOW_HEIGHT / 2 + 85.0f},
    {24876.0f, -WINDOW_HEIGHT / 2 + 85.0f},
};
XMFLOAT2 CliffCenter2_Pos[CliffCenter2_Count] =
{
    {4722.0f, -WINDOW_HEIGHT / 2 + -25.0f},
    {8326.0f, -WINDOW_HEIGHT / 2 + 250.0f},
    {12402.0f, -WINDOW_HEIGHT / 2 + 250.0f},
    {13142.0f, -WINDOW_HEIGHT / 2 + 250.0f},
    {17294.0f, -WINDOW_HEIGHT / 2 + 305.0f},
    {18033.0f, -WINDOW_HEIGHT / 2 + 305.0f},
    {24674.0f, -WINDOW_HEIGHT / 2 + 85.0f},
};

//丘の画像を管理する変数
CPicture* g_pHillSide[HillSide2_Count] = { NULL };
CPicture* g_pHillCenter[HillCenter2_Count] = { NULL };
//丘の当たり判定の画像を管理する変数
CPicture* g_pHillCollision[HillCollision2_Count] = { NULL };
//サイズ
const float Hill_Size_X = 135.0f;
const float Hill_Size_Y = 650.0f;
const float HillCollision_Size_X = 270.0f;
const float HillCollision_Size_Y = 40.0f;
//設置場所
//ステージ１
XMFLOAT2 HillSide1_Pos[HillSide1_Count] =
{
    {3896.0f, -WINDOW_HEIGHT / 2 + 60.0f},
    {4300.0f, -WINDOW_HEIGHT / 2 + 60.0f},
    {4752.0f, -WINDOW_HEIGHT / 2 + 160.0f},
    {5157.0f, -WINDOW_HEIGHT / 2 + 160.0f},
    {5609.0f, -WINDOW_HEIGHT / 2 + 260.0f},
    {6283.0f, -WINDOW_HEIGHT / 2 + 260.0f},
    {14315.0f, -WINDOW_HEIGHT / 2 + 60.0f},
    {14719.0f, -WINDOW_HEIGHT / 2 + 60.0f},
    {13641.0f, -WINDOW_HEIGHT / 2 + 310.0f},
    {14315.0f, -WINDOW_HEIGHT / 2 + 310.0f},
    {15996.0f, -WINDOW_HEIGHT / 2 + 310.0f},
    {16670.0f, -WINDOW_HEIGHT / 2 + 310.0f},
};
XMFLOAT2 HillCenter1_Pos[HillCenter1_Count] =
{
    {4098.0f, -WINDOW_HEIGHT / 2 + 60.0f},
    {4954.0f, -WINDOW_HEIGHT / 2 + 160.0f},
    {5811.0f, -WINDOW_HEIGHT / 2 + 260.0f},
    {6081.0f, -WINDOW_HEIGHT / 2 + 260.0f},
    {14517.0f, -WINDOW_HEIGHT / 2 + 60.0f},
    {13843.0f, -WINDOW_HEIGHT / 2 + 310.0f},
    {14113.0f, -WINDOW_HEIGHT / 2 + 310.0f},
    {16198.0f, -WINDOW_HEIGHT / 2 + 310.0f},
    {16468.0f, -WINDOW_HEIGHT / 2 + 310.0f},
};
XMFLOAT2 HillCollision1_Pos[HillCollision1_Count] =
{
    {3963.0f, -WINDOW_HEIGHT / 2 + 365.0f},
    {4233.0f, -WINDOW_HEIGHT / 2 + 365.0f},
    {4819.0f, -WINDOW_HEIGHT / 2 + 465.0f},
    {5089.0f, -WINDOW_HEIGHT / 2 + 465.0f},
    {5676.0f, -WINDOW_HEIGHT / 2 + 565.0f},
    {5946.0f, -WINDOW_HEIGHT / 2 + 565.0f},
    {6216.0f, -WINDOW_HEIGHT / 2 + 565.0f},
    {14382.0f, -WINDOW_HEIGHT / 2 + 365.0f},
    {14652.0f, -WINDOW_HEIGHT / 2 + 365.0f},
    {13708.0f, -WINDOW_HEIGHT / 2 + 615.0f},
    {13978.0f, -WINDOW_HEIGHT / 2 + 615.0f},
    {14248.0f, -WINDOW_HEIGHT / 2 + 615.0f},
    {16063.0f, -WINDOW_HEIGHT / 2 + 615.0f},
    {16333.0f, -WINDOW_HEIGHT / 2 + 615.0f},
    {16603.0f, -WINDOW_HEIGHT / 2 + 615.0f},
};
//ステージ2
XMFLOAT2 HillSide2_Pos[HillSide2_Count] =
{
    {3896.0f, -WINDOW_HEIGHT / 2 + 300.0f},
    {4300.0f, -WINDOW_HEIGHT / 2 + 300.0f},
    {7835.0f, -WINDOW_HEIGHT / 2 + 75.0f},
    {7970.0f, -WINDOW_HEIGHT / 2 + 75.0f},
    {7170.0f, -WINDOW_HEIGHT / 2 + 300.0f},
    {7844.0f, -WINDOW_HEIGHT / 2 + 300.0f},
    {12570.0f, -WINDOW_HEIGHT / 2 + 350.0f},
    {12974.0f, -WINDOW_HEIGHT / 2 + 350.0f},
    {21145.0f, -WINDOW_HEIGHT / 2 + 450.0f},
    {21819.0f, -WINDOW_HEIGHT / 2 + 450.0f},
    {21984.0f, -WINDOW_HEIGHT / 2 + 0.0f},
    {23198.0f, -WINDOW_HEIGHT / 2 + 0.0f},
    {25013.0f, -WINDOW_HEIGHT / 2 + 32.0f},
    {26497.0f, -WINDOW_HEIGHT / 2 + 32.0f},
};
XMFLOAT2 HillCenter2_Pos[HillCenter2_Count] =
{
    {4098.0f, -WINDOW_HEIGHT / 2 + 300.0f},
    {7372.0f, -WINDOW_HEIGHT / 2 + 300.0f},
    {7642.0f, -WINDOW_HEIGHT / 2 + 300.0f},
    {12772.0f, -WINDOW_HEIGHT / 2 + 350.0f},
    {21347.0f, -WINDOW_HEIGHT / 2 + 450.0f},
    {21617.0f, -WINDOW_HEIGHT / 2 + 450.0f},
    {22186.0f, -WINDOW_HEIGHT / 2 + 0.0f},
    {22456.0f, -WINDOW_HEIGHT / 2 + 0.0f},
    {22726.0f, -WINDOW_HEIGHT / 2 + 0.0f},
    {22996.0f, -WINDOW_HEIGHT / 2 + 0.0f},
    {25215.0f, -WINDOW_HEIGHT / 2 + 32.0f},
    {25485.0f, -WINDOW_HEIGHT / 2 + 32.0f},
    {25755.0f, -WINDOW_HEIGHT / 2 + 32.0f},
    {26025.0f, -WINDOW_HEIGHT / 2 + 32.0f},
    {26295.0f, -WINDOW_HEIGHT / 2 + 32.0f},
};
XMFLOAT2 HillCollision2_Pos[HillCollision2_Count] =
{
    {3963.0f, -WINDOW_HEIGHT / 2 + 605.0f},
    {4233.0f, -WINDOW_HEIGHT / 2 + 605.0f},
    {7902.0f, -WINDOW_HEIGHT / 2 + 380.0f},
    {7237.0f, -WINDOW_HEIGHT / 2 + 605.0f},
    {7507.0f, -WINDOW_HEIGHT / 2 + 605.0f},
    {7777.0f, -WINDOW_HEIGHT / 2 + 605.0f},
    {12637.0f, -WINDOW_HEIGHT / 2 + 655.0f},
    {12907.0f, -WINDOW_HEIGHT / 2 + 655.0f},
    {21211.0f, -WINDOW_HEIGHT / 2 + 755.0f},
    {21481.0f, -WINDOW_HEIGHT / 2 + 755.0f},
    {21751.0f, -WINDOW_HEIGHT / 2 + 755.0f},
    {22051.0f, -WINDOW_HEIGHT / 2 + 305.0f},
    {22321.0f, -WINDOW_HEIGHT / 2 + 305.0f},
    {22591.0f, -WINDOW_HEIGHT / 2 + 305.0f},
    {22861.0f, -WINDOW_HEIGHT / 2 + 305.0f},
    {23131.0f, -WINDOW_HEIGHT / 2 + 305.0f},
    {25080.0f, -WINDOW_HEIGHT / 2 + 337.0f},
    {25350.0f, -WINDOW_HEIGHT / 2 + 337.0f},
    {25620.0f, -WINDOW_HEIGHT / 2 + 337.0f},
    {25890.0f, -WINDOW_HEIGHT / 2 + 337.0f},
    {26160.0f, -WINDOW_HEIGHT / 2 + 337.0f},
    {26430.0f, -WINDOW_HEIGHT / 2 + 337.0f},
};

//トゲの画像を管理する変数
CPicture* g_pNeedl[Needl2_Count] = { NULL, };
//サイズ
const float Needl_Size_X = 200.0f;
const float Needl_Size_Y = 1000.0f;
//設置場合
//ステージ2
XMFLOAT2 Needl2_Pos[Needl2_Count] =
{
    {5500.0f,-450.0f},
    {9800.0f,-550.0f},
    {12000.0f,800.0f},
    {12772.0f,-700.0f},
    {13518.0f,-800.0f},
    {14756.0f,-1200.0f},
    {15650.0f,-700.0f},
    {16600.0f,-1400.0f},
    {17663.0f,1200.0f},
    {17663.0f,-1000.0f},
    {20125.0f,500.0f},
    {20625.0f,-800.0f},
    {22051.0f,-1500.0f},
    {22321.0f,-300.0f},
    {22591.0f,-1500.0f},
    {22861.0f,-300.0f},
    {23131.0f,-1500.0f},
    {25080.0f,-1300.0f},
    {25350.0f,-1300.0f},
    {25620.0f,-1300.0f},
    {25890.0f,-1300.0f},
    {26160.0f,-1300.0f},
    {26430.0f,-1300.0f},
    {25080.0f,1300.0f},
    {25350.0f,1300.0f},
    {25620.0f,1300.0f},
    {25890.0f,1300.0f},
    {26160.0f,1300.0f},
    {26430.0f,1300.0f},
};
//方向のフラグ
int g_NeedlDirection[Needl2_Count] = { 0,0,0,0,0,0,0,0,2,0,0,0, 4,3,4,3,4, 0,0,0,0,0,0,2,2,2,2,2,2 };
//可動式かのフラグ
int g_NeedlMove[Needl2_Count] = { 0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
//移動方向のフラグ
bool g_NeedlMoveUp[Needl2_Count] = { true, };
//移動量
float NeedlPower[Needl2_Count] =
{
    {0.0f,},
    {0.0f,},
    {0.0f,},
    {500.0f,},
    {600.0f,},
    {1000.0f,},
    {500.0f,},
    {800.0f,},
    {600.0f,},
    {600.0f,},
    {0.0f,},
    {600.0f,},
    {1200.0f,},
    {1200.0f,},
    {1200.0f,},
    {1200.0f,},
    {1200.0f,},

    {800.0f,},
    {800.0f,},
    {800.0f,},
    {800.0f,},
    {800.0f,},
    {800.0f,},

    {800.0f,},
    {800.0f,},
    {800.0f,},
    {800.0f,},
    {800.0f,},
    {800.0f,},
};
//速さ
float NeedlSpeed[2] =
{
    {15.0f},
    {5.0f},
};
//総移動
float NeedlMove[Needl2_Count] = { 0.0f, };

//リフトの画像を管理する変数
CPicture* g_pMoveLift[MoveLift2_Count] = { NULL, };
CPicture* g_pMoveLiftCollision[MoveLift2_Count] = { NULL, };
CPicture* g_pFallLift[FallLift2_Count] = { NULL, };
CPicture* g_pFallLiftCollision[FallLift2_Count] = { NULL, };
//サイズ
const float Lift_Size_X = 250.0f;
const float Lift_Size_Y = 50.0f;
const float LiftCollision_Size_X = 250.0f;
const float LiftCollision_Size_Y = 40.0f;
//設置場合
//ステージ１
XMFLOAT2 MoveLift2_Pos[MoveLift2_Count] =
{
    {1219.0f,-150.0f},
    {5250.0f,-350.0f},
    {5750.0f,-350.0f},
    {8795.0f,-50.0f},
    {10050.0f,-50.0f},
    {10750.0f,-50.0f},
    {13736.0f,-50.0f},
    {15330.0f,-500.0f},
    {16300.0f,-250.0f},
    {19500.0f,-300.0f},
    {20400.0f,-400.0f},
    {22761.0f,208.0f},
};
//リフトの移動方向のフラグ
int g_MoveLiftDirection[MoveLift2_Count] = { 0,2,2,0,0,0,0,2,0,0,2,0 }; //0..横　2..縦
//リフトの移動量
float MoveLiftPower[MoveLift2_Count] =
{
    {880.0f,},
    {600.0f,},
    {700.0f,},
    {800.0f,},
    {400.0f,},
    {1000.0f,},
    {800.0f,},
    {800.0f,},
    {600.0f,},
    {600.0f,},
    {800.0f,},
    {1000.0f,},
};
//リフトの速さ
float MoveLiftSpeed[MoveLift2_Count] =
{
    {5.0f},
    {5.0f},
    {5.0f},
    {6.0f},
    {6.0f},
    {10.0f},
    {5.0f},
    {4.0f},
    {5.0f},
    {4.0f},
    {6.0f},
    {6.0f},
};
//リフトの総移動
float MoveLiftMove[MoveLift2_Count] = { 0.0f, };

//設置場合
//ステージ１
XMFLOAT2 FallLift2_Pos[FallLift2_Count] =
{
    {2800.0f,-200.0f},
    {3200.0f,-100.0f},
    {3600.0f,0.0f},
    {6200.0f,100.0f},
    {6650.0f,-100.0f},
    {14980.0f,-50.0f},
    {16000.0f,-50.0f},
    {18527.0f,0.0f},
    {18877.0f,-50.0f},
    {19227.0f,-100.0f},
};
//落ちるリフトのフラグ
bool g_FallLift[FallLift2_Count] = { false, };
//戻るリフトのフラグ
bool g_FallLiftRivers[FallLift2_Count] = { false, };
//落ちるリフトの速さ
float FallLiftSpeed = 10.0f;
//落ちた後のカウンター
int FallLiftCounter[FallLift2_Count] = { 0, };

//ブロックの画像を管理する変数
CPicture* g_pBlock[Block1_Count] = { NULL, };
//サイズ
const float Block_Size_X = 150.0f;
const float Block_Size_Y = 150.0f;
//設置場合
//ステージ１
XMFLOAT2 Block1_Pos[Block1_Count] =
{
    {6790.0f,60.0f},
    {6940.0f,60.0f},
    {7090.0f,60.0f},
    {7240.0f,60.0f},
    {9698.0f,-410.0f},
    {9848.0f,-410.0f},
    {16004.0f,20.0f},
    {16004.0f,-155.0f},
    {16004.0f,-330.0f},
};
//ステージ2
XMFLOAT2 Block2_Pos[Block2_Count] =
{
    {21961.0f,158.0f},
    {22111.0f,158.0f},
    {22261.0f,158.0f},
    {22411.0f,158.0f},
    {22561.0f,158.0f},
};

//看板の画像を管理する変数
CPicture* g_pSignboard[Signboard1_Count] = { NULL };
CPicture* g_pSignboardArrow[Signboard1_Count] = { NULL };
//サイズ
const float Signboard_Size_X = 300.0f;
const float Signboard_Size_Y = 300.0f;
const float SignboardArrow_Size_X = 150.0f;
const float SignboardArrow_Size_Y = 130.0f;
//設置場所
//チュートリアル
XMFLOAT2 Signboard0_Pos[Signboard0_Count] =
{
    {480.0f, -255.0f},
    {8100.0f, -255.0f},
};
//ステージ1
XMFLOAT2 Signboard1_Pos[Signboard1_Count] =
{
    {480.0f, -255.0f},
    {7900.0f, -255.0f},
    {11000.0f, -255.0f},
    {17900.0f, -255.0f},
};
//ステージ2
XMFLOAT2 Signboard2_Pos[Signboard2_Count] =
{
    {480.0f, -255.0f},
    {23500.0f, -255.0f},
    {27500.0f, -255.0f},
};

//各ステージに必要なオブジェクトの数を代入する変数
int BackGround_Count = 0;
int Ground_Count = 0;
int Hole_Count = 0;
int CliffSide_Count = 0;
int CliffCenter_Count = 0;
int HillSide_Count = 0;
int HillCenter_Count = 0;
int HillCollision_Count = 0;
int Signboard_Count = 0;
int Needl_Count = 0;
int MoveLift_Count = 0;
int FallLift_Count = 0;
int Block_Count = 0;

int Niboshi_Count = 0;

//プレイヤーの情報を管理する変数
CPicture* g_pPlayer = NULL;
//サイズ
const float Player_Size_X = 283.0f;
const float Player_Size_Y = 202.0f;

//プレイヤーの当たり判定の画像を管理する変数
CPicture* g_pPlayerCollisionBottom = NULL;
CPicture* g_pPlayerCollisionSide = NULL;
//サイズ
const float PlayerCollision_Size_Bottom_X = 130.0f;
const float PlayerCollision_Size_Bottom_Y = 199.0f;
const float PlayerCollision_Size_Side_X = 175.5f;
const float PlayerCollision_Size_Side_Y = 140.0f;

//移動スピード
float PlayerSpeed = 12.0f;
//移動時のカウンター
float MTimeCounter = 0.0f;
//向いている方向の判断
bool PlayerDirection_Right = true;
//ミスの判定のフラグ
bool g_Miss = false;
//にぼしの獲得数
int NiboshiCounter = 0;

//アニメーションのカウンター
int PlayerWAnimationCounter = 0;
int PlayerRAnimationCounter = 0;
int PlayerJAnimationCounter = 0;
int PlayerMAnimationCounter = 0;
//アニメーションした回数
int PlayerWAnimation = 0;
int PlayerJAnimation = 0;
//アニメーションのフラグ
bool g_PlayerWAnimation = true;
bool g_PlayerJAnimation = true;

//設置判定のフラグ
bool g_Ground = false;
bool g_RightHit = false;
bool g_LeftHit = false;
bool g_TopHit = false;

//しゃがみのフラグ
bool g_Sit = false;
//ジャンプのフラグ
bool g_Jump = false;
bool g_JumpUp = false;
//ジャンプの高さ
float PlayerJumpPower = 175.0f;
//ジャンプの総移動
float PlayerJumpMove = 0.0f;
//ジャンプ時のカウンター
float JTimeCounter = -1.0f;
//ジャンプの方向を管理する変数
PlayerJump JumpDirection = NormalShift;

//歩いているかどうかのフラグ
bool g_Walking = false;
//走っているかどうかのフラグ
bool g_Running = false;
//壁を登っているかどうかのフラグ
bool g_Climb = false;
//壁を登れる高さ
float PlayerClimbPower = 606.0f;
//登った壁の総移動量
float PlayerClimbMove = 0.0f;

//重力の情報を管理する変数
float GTimeCounter = 0.0f;
float PlayerGurabitexi;
float g_Gurabitexi = 1.0f;

//各UIの画像を管理する変数
CPicture* g_pKatuobushiUI = NULL;
CPicture* g_pNiboshiUI = NULL;
CPicture* g_pLifeUI = NULL;
//UIの数字の画像を管理する変数
CPicture* g_pNumber[6] = { NULL, };
//サイズ
const float UI_Size_X = 150.0f;
const float UI_Size_Y = 100.0f;
const float Number_Size_X = 75.0f;
const float Number_Size_Y = 75.0f;
//設置場所
XMFLOAT2 UI_Pos = { -880.0f, 480.0f };

//カメラの位置を管理する変数
XMFLOAT3  CameraPos = { 0.0f,0.0f,0.0f };
//各ステージの端の座標を管理する変数
float End[3] = { 8504.0f, 18250.0f, 28000.0f };

//吹き出しの画像を管理する変数
CPicture* g_pSpeechBalloon = NULL;
//ににの画像を管理する変数
CPicture* g_pNini = NULL;
//ににの感情マークを管理する変数
CPicture* g_pNiniEmotion = NULL;
//名前の画像を管理する変数
CPicture* g_pName = NULL;
//吹き出しのUIの画像を管理する変数
CPicture* g_pSpeechBalloonUI = NULL;
//分岐用吹き出しの画像を管理する変数
CPicture* g_pSpeechBalloonSelect = NULL;
//サイズ
const float SpeechBalloon_Size_X = 1200.0f;
const float SpeechBalloon_Size_Y = 320.0f;
const float Nini_Size_X = 202.0f;
const float Nini_Size_Y = 236.0f;
const float NiniEmotion_Size_X = 264.0f;
const float NiniEmotion_Size_Y = 237.0f;
const float Name_Size_X = 100.0f;
const float Name_Size_Y = 68.0f;
const float SpeechBalloonUI_Size_X = 54.0f;
const float SpeechBalloonUI_Size_Y = 59.0f;
const float SpeechBalloonSelect_Size_X = 500.0f;
const float SpeechBalloonSelect_Size_Y = 200.0f;
//設置場所
XMFLOAT2 SpeechBalloon_Pos = { 0.0f, 300.0f };

//アニメーションのカウンター
int SpeechBalloonAnimationCounter = 0;
int NiniAnimationCounter = 0;
//アニメーションした回数
int SpeechBalloonAnimation = 0;
//アニメーションのフラグ
bool g_SpeechBalloonAnimation = true;
bool g_NiniAnimation = true;
//感情マークのアニメーションを管理する変数
int NiniEmotion = 0;

//セリフの画像を管理する変数
CPicture* g_pDialogue = NULL;
CPicture* g_pDialogueSelect = NULL;
//サイズ
const float Dialogue_Size_X = 870.0f;
const float Dialogue_Size_Y = 154.0f;
const float DialogueSelect_Size_X = 300.0f;
const float DialogueSelect_Size_Y = 145.0f;

//アニメーションのカウンター
int DialogueAnimationCounter = 0;
//アニメーションした回数
int DialogueAnimation = 0;
//アニメーションのフラグ
bool g_DialogueAnimation = true;

//セリフが出ているかのフラグ
bool g_Dialogue = true;
//セリフのカウント
int DialogueCount = 0;
//セリフの分岐フラグ
bool g_DialogueSelect = false;
//選択肢を管理する変数
int Select = 0;

//チュートリアルの進行を管理する変数
int Tuto = 0;

//リスポーンハウスの画像を管理する変数
CPicture* g_pHouse = NULL;
//サイズ
const float House_Size_X = 236.0f;
const float House_Size_Y = 338.0f;
//設置場所
XMFLOAT2 House_Pos = { -550.0f, -238.0f };

//宝箱の画像を管理する変数
CPicture* g_pTreasure = NULL;
//王冠の画像を管理する変数
CPicture* g_pCrown = NULL;
//アニメーションカウンター、フラグ
int CrownCounter = 0;
bool OpenTreasure = false;

//にぼしの画像を管理する変数
CPicture* g_pNiboshi[Niboshi2_Count] = { NULL, };
//サイズ
const float Niboshi_Size_X = 150.0f;
const float Niboshi_Size_Y = 50.0f;
//設置場所
//ステージ1
XMFLOAT2 Niboshi1_Pos[Niboshi1_Count] =
{
    {781.0f,-230.0f},
    {939.0f,-180.0f},
    {1119.0f,-240.0f},
    {2090.0f,-180.0f},
    {2190.0f,-60.0f},
    {2375.0f,-70.0f},
    {3896.0f,-300.0f},
    {4031.0f,-300.0f},
    {4166.0f,-300.0f},
    {4301.0f,-300.0f},
    {4098.0f,0.0f},
    {4098.0f,100.0f},
    {4098.0f,200.0f},
    {4752.0f,-250.0f},
    {4887.0f,-250.0f},
    {5022.0f,-250.0f},
    {5157.0f,-250.0f},
    {5788.0f,-230.0f},
    {5946.0f,-180.0f},
    {6126.0f,-240.0f},
    {4376.0f,20.0f},
    {4476.0f,140.0f},
    {4661.0f,130.0f},
    {5233.0f,120.0f},
    {5333.0f,240.0f},
    {5518.0f,230.0f},
    {5794.0f,120.0f},
    {5929.0f,120.0f},
    {6064.0f,120.0f},
    {6550.0f,120.0f},
    {6600.0f,20.0f},
    {6600.0f,-80.0f},
    {6600.0f,-180.0f},
    {6800.0f,200.0f},
    {6935.0f,200.0f},
    {7070.0f,200.0f},
    {7205.0f,-230.0f},
    {7343.0f,-180.0f},
    {7498.0f,-180.0f},
    {7658.0f,-240.0f},
    {8680.0f,-240.0f},
    {8680.0f,-100.0f},
    {8762.0f,0.0f},
    {9600.0f,-30.0f},
    {9948.0f,-30.0f},
    {11800.0f,-30.0f},
    {11800.0f,-130.0f},
    {11800.0f,-230.0f},
    {11800.0f,-330.0f},
    {11900.0f,50.0f},
    {12705.0f,50.0f},
    {12840.0f,140.0f},
    {13000.0f,50.0f},
    {13335.0f,-150.0f},
    {13510.0f,-250.0f},
    {14090.0f,-150.0f},
    {14214.0f,-70.0f},
    {14370.0f,-50.0f},
    {14210.0f,180.0f},
    {14370.0f,160.0f},
    {14525.0f,30.0f},
    {14075.0f,180.0f},
    {13940.0f,180.0f},
    {13805.0f,180.0f},
    {14576.0f,-300.0f},
    {14734.0f,-200.0f},
    {14905.0f,-300.0f},
    {15850.0f,-300.0f},
    {15850.0f,-200.0f},
    {15850.0f,-100.0f},
    {15850.0f,0.0f},
    {15850.0f,100.0f},
    {16000.0f,150.0f},
    {16135.0f,150.0f},
    {16509.0f,150.0f},
    {16664.0f,150.0f},
    {16135.0f,-280.0f},
    {16509.0f,-280.0f},
};
//ステージ2
XMFLOAT2 Niboshi2_Pos[Niboshi2_Count] =
{
    {1190.0f,-70.0f},
    {1325.0f,-70.0f},
    {1460.0f,-70.0f},
    {1595.0f,-70.0f},
    {1730.0f,-70.0f},
    {1865.0f,-70.0f},
    {2000.0f,-70.0f},
    {2135.0f,-70.0f},
    {2975.0f,0.0f},
    {3375.0f,100.0f},
    {3775.0f,200.0f},
    {3930.0f,200.0f},
    {4090.0f,200.0f},
    {4250.0f,200.0f},
    {5378.0f,103.0f},
    {5484.0f,200.0f},
    {5625.0f,100.0f},
    {5817.0f,200.0f},
    {5975.0f,300.0f},
    {6155.0f,200.0f},
    {6267.0f,0.0f},
    {6425.0f,100.0f},
    {6605.0f,0.0f},
    {6650.0f,-100.0f},
    {6650.0f,-200.0f},
    {7835.0f,-280.0f},
    {7970.0f,-280.0f},
    {7630.0f,-150.0f},
    {7711.0f,-50.0f},
    {7870.0f,-80.0f},
    {7170.0f,150.0f},
    {7305.0f,150.0f},
    {7440.0f,150.0f},
    {7575.0f,150.0f},
    {7710.0f,150.0f},
    {7845.0f,150.0f},
    {8528.0f,100.0f},
    {8650.0f,200.0f},
    {8821.0f,100.0f},
    {9678.0f,100.0f},
    {9784.0f,150.0f},
    {9925.0f,100.0f},
    {10478.0f,100.0f},
    {10600.0f,200.0f},
    {10771.0f,100.0f},
    {10980.0f,350.0f},
    {11100.0f,350.0f},
    {11400.0f,350.0f},
    {11520.0f,350.0f},
    {11873.0f,105.0f},
    {12000.0f,200.0f},
    {12170.0f,95.0f},
    {12570.0f,180.0f},
    {12705.0f,180.0f},
    {12840.0f,180.0f},
    {12975.0f,180.0f},
    {13396.0f,103.0f},
    {13502.0f,200.0f},
    {13643.0f,95.0f},
    {14634.0f,103.0f},
    {14740.0f,200.0f},
    {14881.0f,100.0f},
    {13800.0f,30.0f},
    {13945.0f,30.0f},
    {14090.0f,30.0f},
    {14235.0f,30.0f},
    {14380.0f,30.0f},
    {14525.0f,30.0f},
    {15330.0f,-400.0f},
    {15330.0f,-300.0f},
    {15330.0f,-200.0f},
    {15330.0f,-100.0f},
    {15330.0f,0.0f},
    {15330.0f,100.0f},
    {15330.0f,200.0f},
    {15330.0f,300.0f},
    {15528.0f,103.0f},
    {15634.0f,200.0f},
    {15775.0f,100.0f},
    {16028.0f,-97.0f},
    {16134.0f,0.0f},
    {16275.0f,-100.0f},
    {16450.0f,-20.0f},
    {16750.0f,-20.0f},
    {16946.0f,-180.0f},
    {16946.0f,-80.0f},
    {16946.0f,20.0f},
    {17046.0f,85.0f},
    {17541.0f,203.0f},
    {17788.0f,197.0f},
    {18527.0f,0.0f},
    {18527.0f,-100.0f},
    {18527.0f,-200.0f},
    {18527.0f,-300.0f},
    {18877.0f,-50.0f},
    {18877.0f,-150.0f},
    {18877.0f,-250.0f},
    {18877.0f,-350.0f},
    {19227.0f,-100.0f},
    {19227.0f,-200.0f},
    {19227.0f,-300.0f},
    {19500.0f,-220.0f},
    {19635.0f,-220.0f},
    {19770.0f,-220.0f},
    {19905.0f,-220.0f},
    {20040.0f,-220.0f},
    {20175.0f,-220.0f},
    { 20400.0f,-400.0f },
    { 20400.0f,-300.0f },
    { 20400.0f,-200.0f },
    { 20400.0f,-100.0f },
    { 20400.0f,0.0f },
    { 20400.0f,100.0f },
    { 20400.0f,200.0f },
    { 20400.0f,300.0f },
    { 20400.0f,400.0f },
    { 21145.0f,280.0f },
    { 21280.0f,280.0f },
    { 21415.0f,280.0f },
    { 21550.0f,280.0f },
    { 21685.0f,280.0f },
    { 21820.0f,280.0f },
    { 21955.0f,280.0f },
    { 22090.0f,280.0f },
    { 22225.0f,280.0f },
    { 22360.0f,280.0f },
    { 22495.0f,280.0f },
    { 22630.0f,280.0f },
    { 22765.0f,280.0f },
    { 22900.0f,280.0f },
    { 23035.0f,280.0f },
    { 23170.0f,280.0f },
    { 23305.0f,280.0f },
    { 23440.0f,280.0f },
    { 23575.0f,280.0f },
    { 22051.0f,30.0f },
    { 22321.0f,30.0f },
    { 22591.0f,30.0f },
    { 22861.0f,30.0f },
    { 23131.0f,30.0f },
    { 24282.0f,-123.0f },
    { 24388.0f,-20.0f },
    { 24529.0f,-117.0f },
    { 25013.0f,-117.0f },
    { 25148.0f,-117.0f },
    { 25283.0f,-117.0f },
    { 25418.0f,-117.0f },
    { 25553.0f,-117.0f },
    { 25688.0f,-117.0f },
    { 25823.0f,-117.0f },
    { 25958.0f,-117.0f },
    { 26093.0f,-117.0f },
    { 26228.0f,-117.0f },
    { 26363.0f,-117.0f },
    { 26498.0f,-117.0f },
    { 26633.0f,-17.0f },
    { 26768.0f,83.0f },
};

//かつおぶしの画像を管理する変数
CPicture* g_pKatuobushi[10] = { NULL, };
//サイズ
const float Katuobushi_Size_X = 150.0f;
const float Katuobushi_Size_Y = 150.0f;
//設置場所
//ステージ1
XMFLOAT2 Katuobushi1_Pos[Katuobushi_Count] =
{
    {2580.0f,-50.0f},
    {4098.0f,350.0f},
    {6234.0f,130.0f},
    {7240.0f,210.0f},
    {9773.0f,100.0f},
    {9773.0f,-260.0f},
    {13155.0f,-50.0f},
    {13635.0f,200.0f},
    {16333.0f,-200.0f},
    {16333.0f,180.0f},
};
//ステージ2
XMFLOAT2 Katuobushi2_Pos[Katuobushi_Count] =
{
    {1640.0f,70.0f},
    {4098.0f,350.0f},
    {6650.0f,-320.0f},
    {11250.0f,350.0f},
    {12772.0f,350.0f},
    {16600.0f,0.0f},
    {17663.0f,300.0f},
    {19227.0f,-430.0f },
    { 23750.0f,315.0f },
    { 26903.0f,183.0f },
};

void COriginalGameApp::procGame()
{
    //ケースによって切り替える
    switch (g_PlayPhase)
    {
    case eBegin:
    {
        if (Stage == 0)
        {
            //チュートリアル開始時の処理
            procPlayBegin_Tuto();
        }
        if (Stage == 1)
        {
            //ステージ1開始時の処理
            procPlayBegin_Stage1();
        }
        if (Stage == 2)
        {
            //ステージ2開始時の処理
            procPlayBegin_Stage2();
        }
        if (Stage == 3)
        {
            //ステージ3開始時の処理
            procPlayBegin_Stage3();
        }

        //進行状況をメインに切り替える
        g_PlayPhase = eMain;
    }
    break;
    case eMain:
    {
        XMFLOAT4 pos = g_pPlayer->getPos();

        if (Stage == 0)
        {
            //チュートリアルのメイン処理
            procPlayMain_Tuto();
        }
        if (Stage == 1)
        {
            //ステージ1のメイン処理
            procPlayMain_Stage1();
        }
        if (Stage == 2)
        {
            //ステージ2のメイン処理
            procPlayMain_Stage2();
        }
        if (Stage == 3)
        {
            //ステージ3のメイン処理
            procPlayMain_Stage3();

            //最後のセリフが出終わるとクリア
            if (g_Clear == true && g_Speech == false)
            {
                g_NextStatusFromPlay = eGameClear;
                //進行状況をエンドに切り替える
                g_PlayPhase = eEnd;
            }
        }

        if (Stage != 3)
        {
            //ステージの端またはステージチェンジで、クリア画面に移行
            if (pos.x >= End[Stage] || g_Change)
            {
                g_NextStatusFromPlay = eGameClear;
                //進行状況をエンドに切り替える
                g_PlayPhase = eEnd;
            }

            //ミスのアニメーションが終了すると、ミス画面に移行
            if (PlayerMAnimationCounter == 100)
            {
                //カウンターをリセット
                PlayerMAnimationCounter = 0;

                //ライフが0の時、ミスをするとゲームオーバー画面に移行
                if (Life == 0)
                {
                    g_NextStatusFromPlay = eGameOver;
                    //進行状況をエンドに切り替える
                    g_PlayPhase = eEnd;
                }
                else
                {
                    g_NextStatusFromPlay = eGameMiss;
                    //進行状況をエンドに切り替える
                    g_PlayPhase = eEnd;
                }
            }
        }
    }
    break;
    case eEnd:
    {
        //ステージ2終了時の処理
        procPlayEnd_Stage();

        //再度戻ってきたときのために進行状況をリセットしておく
        g_PlayPhase = eBegin;
        //次のフェーズに切り替える
        SetNextGameStatus(g_NextStatusFromPlay);
    }
    }
}

/*
* 関数名　  ：procPlayBegin_Tuto()
* 処理内容　：チュートリアル画面の開始処理
*/
void COriginalGameApp::procPlayBegin_Tuto()
{
    //プレイヤーの画像がNULLの時のみ作成
    if (g_pPlayer == NULL)
    {
        g_pPlayer = createSprite(Tex_Player, Player_Size_X, Player_Size_Y);
        g_pPlayer->setPos(-660.0f, -304.0f);
    }
    //プレイヤーの当たり判定の画像がNULLの時のみ作成
    if (g_pPlayerCollisionBottom == NULL)
    {
        g_pPlayerCollisionBottom = createSprite(Tex_PlayerCollisionBottom, PlayerCollision_Size_Bottom_X, PlayerCollision_Size_Bottom_Y);
        g_pPlayerCollisionBottom->setPos(-628.5f, -301.0f);
    }
    if (g_pPlayerCollisionSide == NULL)
    {
        g_pPlayerCollisionSide = createSprite(Tex_PlayerCollisionSide, PlayerCollision_Size_Side_X, PlayerCollision_Size_Side_Y);
        g_pPlayerCollisionSide->setPos(-606.0f, -273.0f);
    }

    //床(0)の画像がNULLの時のみ作成
    for (int i = 0; i < Ground0_Count; ++i)
    {
        if (g_pGround[i] == NULL)
        {
            g_pGround[i] = createSprite(Tex_Ground1, Ground_Size_X, Ground_Size_Y);
            g_pGround[i]->setPos(Ground0_Pos[i]);
        }
    }

    //穴(0)の画像がNULLの時のみ作成
    for (int i = 0; i < Hole0_Count; ++i)
    {
        //iが偶数の時
        if (i % 2 == 0)
        {
            //右向きの穴の画像を作成
            if (g_pHole[i] == NULL)
            {
                g_pHole[i] = createSprite(Tex_Hole1, Hole_Size_X, Hole_Size_Y);
                g_pHole[i]->setPos(Hole0_Pos[i]);
            }
        }
        //iが奇数の時
        else
        {
            //左向きの穴の画像を作成
            if (g_pHole[i] == NULL)
            {
                g_pHole[i] = createSprite(Tex_Hole1, Hole_Size_X, Hole_Size_Y);
                g_pHole[i]->setAngle({ 0.0f, 180.0f, 0.0f });
                g_pHole[i]->setPos(Hole0_Pos[i]);
            }
        }
    }

    //崖(0)の画像がNULLの時のみ作成
    for (int i = 0; i < CliffSide0_Count; ++i)
    {
        //iが偶数の時
        if (i % 2 == 0)
        {
            //右向きの崖の画像を作成
            if (g_pCliffSide[i] == NULL)
            {
                g_pCliffSide[i] = createSprite(Tex_CliffSide1, Cliff_Size_X, Cliff_Size_Y);
                g_pCliffSide[i]->setPos(CliffSide0_Pos[i]);
            }
        }
        //iが奇数の時
        else
        {
            //左向きの崖の画像を作成
            if (g_pCliffSide[i] == NULL)
            {
                g_pCliffSide[i] = createSprite(Tex_CliffSide1, Cliff_Size_X, Cliff_Size_Y);
                g_pCliffSide[i]->setAngle({ 0.0f, 180.0f, 0.0f });
                g_pCliffSide[i]->setPos(CliffSide0_Pos[i]);
            }
        }
    }
    //真ん中の崖(0)の画像がNULLの時のみ作成
    for (int i = 0; i < CliffSide0_Count; ++i)
    {
        if (g_pCliffCenter[i] == NULL)
        {
            g_pCliffCenter[i] = createSprite(Tex_CliffCenter1, Cliff_Size_X * 2, Cliff_Size_Y);
            g_pCliffCenter[i]->setPos(CliffCenter0_Pos[i]);
        }
    }

    //2回目以降は作成しない
    if (MissCount < 2)
    {
        //吹き出しの画像がNULLの時のみ作成
        if (g_pSpeechBalloon == NULL)
        {
            g_pSpeechBalloon = createSprite(Tex_SpeechBalloon, SpeechBalloon_Size_X, SpeechBalloon_Size_Y);
            g_pSpeechBalloon->setPos(SpeechBalloon_Pos);
        }
        //ににの画像がNULLの時のみ作成
        if (g_pNini == NULL)
        {
            g_pNini = createSprite(Tex_Nini, Nini_Size_X, Nini_Size_Y);
            g_pNini->setPos(0.0f, -WINDOW_HEIGHT);
        }
        //ににの感情マークの画像がNULLの時のみ作成
        if (g_pNiniEmotion == NULL)
        {
            g_pNiniEmotion = createSprite(Tex_NiniEmotion, NiniEmotion_Size_X, NiniEmotion_Size_Y);
            g_pNiniEmotion->setPos(0.0f, -WINDOW_HEIGHT);
        }
        //名前の画像がNULLの時のみ作成
        if (g_pName == NULL)
        {
            g_pName = createSprite(Tex_Name, Name_Size_X, Name_Size_Y);
            g_pName->setPos(0.0f, -WINDOW_HEIGHT);
        }
        //吹き出しのUIの画像がNULLの時のみ作成
        if (g_pSpeechBalloonUI == NULL)
        {
            g_pSpeechBalloonUI = createSprite(Tex_SpeechBalloonUI, SpeechBalloonUI_Size_X, SpeechBalloonUI_Size_Y);
            g_pSpeechBalloonUI->setPos(0.0f, -WINDOW_HEIGHT);
        }
        //分岐用吹き出しの画像がNULLの時のみ作成
        if (g_pSpeechBalloonSelect == NULL)
        {
            g_pSpeechBalloonSelect = createSprite(Tex_SpeechBalloonSelect, SpeechBalloonSelect_Size_X, SpeechBalloonSelect_Size_Y);
            g_pSpeechBalloonSelect->setPos(350.0f, 48.0f);
        }
    }

    //セリフ(0)の画像がNULLの時のみ作成
    //最初のみ作成
    if (Tuto == 0)
    {
        if (g_pDialogue == NULL)
        {
            g_pDialogue = createSprite(Tex_Dialogue0_1, Dialogue_Size_X, Dialogue_Size_Y);
            g_pDialogue->setPos(140.0f, 295.0f);
        }
        //分岐の選択肢(0)の画像がNULLの時のみ作成
        if (g_pDialogueSelect == NULL)
        {
            g_pDialogueSelect = createSprite(Tex_DialogueSelect0_1, DialogueSelect_Size_X, DialogueSelect_Size_Y);
            g_pDialogueSelect->setPos(g_pSpeechBalloonSelect->getPos().x, g_pSpeechBalloonSelect->getPos().y - 3.0f);
        }
    }

    //看板(0)の画像がNULLの時のみ作成
    for (int i = 0; i < Signboard0_Count; ++i)
    {
        if (g_pSignboard[i] == NULL)
        {
            g_pSignboard[i] = createSprite(Tex_Signboard, Signboard_Size_X, Signboard_Size_Y);
            g_pSignboard[i]->setPos(Signboard0_Pos[i]);
        }
    }
    //看板の矢印(0)の画像がNULLの時のみ作成
    for (int i = 0; i < Signboard0_Count; ++i)
    {
        if (g_pSignboardArrow[i] == NULL)
        {
            g_pSignboardArrow[i] = createSprite(Tex_SignboardArrow, SignboardArrow_Size_X, SignboardArrow_Size_Y);
            g_pSignboardArrow[i]->setPos(g_pSignboard[i]->getPos().x + 6.0f, g_pSignboard[i]->getPos().y + 17.0f);
        }
    }

    //背景(0)の画像がNULLの時のみ作成
    for (int i = 0; i < BackGround0_Count; ++i)
    {
        if (g_pBackGround[i] == NULL)
        {
            g_pBackGround[i] = createSprite(Tex_BackGround1, BackGround_Size_X, BackGround_Size_Y);
            g_pBackGround[i]->setPos(960.0f + WINDOW_WIDTH * 2 * i, 0.0f);
        }
    }

    //各ステージに必要なオブジェクトの数を代入する
    BackGround_Count = BackGround0_Count;
    Ground_Count = Ground0_Count;
    Hole_Count = Hole0_Count;
    CliffSide_Count = CliffSide0_Count;
    CliffCenter_Count = CliffCenter0_Count;
    Signboard_Count = Signboard0_Count;
}

/*
* 関数名　  ：procPlayBegin_Stage1()
* 処理内容　：ステージ1画面の開始処理
*/
void COriginalGameApp::procPlayBegin_Stage1()
{
    //プレイヤーの画像がNULLの時のみ作成
    if (g_pPlayer == NULL)
    {
        g_pPlayer = createSprite(Tex_Player, Player_Size_X, Player_Size_Y);

        //リスポーン地点に設定
        if (MissCount != 0)
        {
            g_pPlayer->setPos(-430.0f, -304.0f);
        }
        else
        {
            g_pPlayer->setPos(-818.0f, -304.0f);
        }
    }
    //プレイヤーの当たり判定の画像がNULLの時のみ作成
    if (g_pPlayerCollisionBottom == NULL)
    {
        g_pPlayerCollisionBottom = createSprite(Tex_PlayerCollisionBottom, PlayerCollision_Size_Bottom_X, PlayerCollision_Size_Bottom_Y);
        g_pPlayerCollisionBottom->setPos(-868.5f, -301.0f);
    }
    if (g_pPlayerCollisionSide == NULL)
    {
        g_pPlayerCollisionSide = createSprite(Tex_PlayerCollisionSide, PlayerCollision_Size_Side_X, PlayerCollision_Size_Side_Y);
        g_pPlayerCollisionSide->setPos(-846.0f, -273.0f);
    }

    //リスポーンハウスの画像がNULLの時のみ作成
    if (g_pHouse == NULL)
    {
        g_pHouse = createSprite(Tex_House, House_Size_X, House_Size_Y);
        g_pHouse->setPos(House_Pos);
    }

    //にぼしのUIの画像がNULLの時のみ作成
    if (g_pNiboshiUI == NULL)
    {
        g_pNiboshiUI = createSprite(Tex_NiboshiUI, UI_Size_X, UI_Size_Y);
        g_pNiboshiUI->setPos(UI_Pos);
    }
    //かつおぶしのUIの画像がNULLの時のみ作成
    if (g_pKatuobushiUI == NULL)
    {
        g_pKatuobushiUI = createSprite(Tex_KatuobushiUI, UI_Size_X, UI_Size_Y);
        g_pKatuobushiUI->setPos(UI_Pos.x, UI_Pos.y - UI_Size_Y);
    }
    //残機のUIの画像がNULLの時のみ作成
    if (g_pLifeUI == NULL)
    {
        g_pLifeUI = createSprite(Tex_LifeUI, UI_Size_X, UI_Size_Y);
        g_pLifeUI->setPos(UI_Pos.x, UI_Pos.y - UI_Size_Y * 2);
        if (g_Clear == true)
        {
            g_pLifeUI->setAnimation(1);
        }
    }
    //UIの数字の画像がNULLの時のみ作成
    for (int i = 0; i < 6; ++i)
    {
        if (g_pNumber[i] == NULL)
        {
            g_pNumber[i] = createSprite(Tex_Number, Number_Size_X, Number_Size_Y);
            g_pNumber[i]->setPos(UI_Pos.x + 115.0f + (60.0f * (i % 2)), UI_Pos.y - 100.0f * (i / 2));
        }
    }

    //床(1)の画像がNULLの時のみ作成
    for (int i = 0; i < Ground1_Count; ++i)
    {
        if (g_pGround[i] == NULL)
        {
            g_pGround[i] = createSprite(Tex_Ground1, Ground_Size_X, Ground_Size_Y);
            g_pGround[i]->setPos(Ground1_Pos[i]);
        }
    }

    //穴(1)の画像がNULLの時のみ作成
    for (int i = 0; i < Hole1_Count; ++i)
    {
        //iが偶数の時
        if (i % 2 == 0)
        {
            //右向きの穴の画像を作成
            if (g_pHole[i] == NULL)
            {
                g_pHole[i] = createSprite(Tex_Hole1, Hole_Size_X, Hole_Size_Y);
                g_pHole[i]->setPos(Hole1_Pos[i]);
            }
        }
        //iが奇数の時
        else
        {
            //左向きの穴の画像を作成
            if (g_pHole[i] == NULL)
            {
                g_pHole[i] = createSprite(Tex_Hole1, Hole_Size_X, Hole_Size_Y);
                g_pHole[i]->setAngle({ 0.0f, 180.0f, 0.0f });
                g_pHole[i]->setPos(Hole1_Pos[i]);
            }
        }
    }

    //崖(1)の画像がNULLの時のみ作成
    for (int i = 0; i < CliffSide1_Count; ++i)
    {
        //iが偶数の時
        if (i % 2 == 0)
        {
            //右向きの崖の画像を作成
            if (g_pCliffSide[i] == NULL)
            {
                g_pCliffSide[i] = createSprite(Tex_CliffSide1, Cliff_Size_X, Cliff_Size_Y);
                g_pCliffSide[i]->setPos(CliffSide1_Pos[i]);
            }
        }
        //iが奇数の時
        else
        {
            //左向きの崖の画像を作成
            if (g_pCliffSide[i] == NULL)
            {
                g_pCliffSide[i] = createSprite(Tex_CliffSide1, Cliff_Size_X, Cliff_Size_Y);
                g_pCliffSide[i]->setAngle({ 0.0f, 180.0f, 0.0f });
                g_pCliffSide[i]->setPos(CliffSide1_Pos[i]);
            }
        }
    }
    //真ん中の崖(1)の画像がNULLの時のみ作成
    for (int i = 0; i < CliffCenter1_Count; ++i)
    {
        if (g_pCliffCenter[i] == NULL)
        {
            g_pCliffCenter[i] = createSprite(Tex_CliffCenter1, Cliff_Size_X * 2, Cliff_Size_Y);
            g_pCliffCenter[i]->setPos(CliffCenter1_Pos[i]);
        }
    }

    //丘(1)の画像がNULLの時のみ作成
    for (int i = 0; i < HillSide1_Count; ++i)
    {
        //iが偶数の時
        if (i % 2 == 0)
        {
            //右向きの丘の画像を作成
            if (g_pHillSide[i] == NULL)
            {
                g_pHillSide[i] = createSprite(Tex_HillSide1, Hill_Size_X, Hill_Size_Y);
                g_pHillSide[i]->setPos(HillSide1_Pos[i]);
            }
        }
        //iが奇数の時
        else
        {
            //左向きの丘の画像を作成
            if (g_pHillSide[i] == NULL)
            {
                g_pHillSide[i] = createSprite(Tex_HillSide1, Hill_Size_X, Hill_Size_Y);
                g_pHillSide[i]->setAngle({ 0.0f, 180.0f, 0.0f });
                g_pHillSide[i]->setPos(HillSide1_Pos[i]);
            }
        }
    }
    //真ん中の丘(1)の画像がNULLの時のみ作成
    for (int i = 0; i < HillCenter1_Count; ++i)
    {
        if (g_pHillCenter[i] == NULL)
        {
            g_pHillCenter[i] = createSprite(Tex_HillCenter1, Hill_Size_X * 2, Hill_Size_Y);
            g_pHillCenter[i]->setPos(HillCenter1_Pos[i]);
        }
    }

    //丘の当たり判定(1)の画像がNULLの時のみ作成
    for (int i = 0; i < HillCollision1_Count; ++i)
    {
        if (g_pHillCollision[i] == NULL)
        {
            g_pHillCollision[i] = createSprite(Tex_HillCollision, HillCollision_Size_X, HillCollision_Size_Y);
            g_pHillCollision[i]->setPos(HillCollision1_Pos[i]);
        }
    }

    //ブロック(1)の画像がNULLの時のみ作成
    for (int i = 0; i < Block1_Count; ++i)
    {
        if (g_pBlock[i] == NULL)
        {
            g_pBlock[i] = createSprite(Tex_Block, Block_Size_X, Block_Size_Y);
            g_pBlock[i]->setPos(Block1_Pos[i]);
            //クリア済はブロックを表示
            if (g_Clear == false)
            {
                g_pBlock[i]->setAnimation(1);
            }
        }
    }

    //にぼし(1)の画像がNULLの時のみ作成
    for (int i = 0; i < Niboshi1_Count; ++i)
    {
        if (g_pNiboshi[i] == NULL)
        {
            g_pNiboshi[i] = createSprite(Tex_Niboshi, Niboshi_Size_X, Niboshi_Size_Y);
            g_pNiboshi[i]->setPos(Niboshi1_Pos[i]);
            g_pNiboshi[i]->setAngle({ 0.0f, 0.0f, -30.0f });
        }
    }
    //かつおぶし(1)の画像がNULLの時のみ作成
    for (int i = 0; i < Katuobushi_Count; ++i)
    {
        //獲得判定のあるものは作らない
        if (g_pKatuobushi[i] == NULL && KatuobushiFlag[Stage - 1][i] == false)
        {
            g_pKatuobushi[i] = createSprite(Tex_Katuobushi, Katuobushi_Size_X, Katuobushi_Size_Y);
            g_pKatuobushi[i]->setPos(Katuobushi1_Pos[i]);
        }
    }

    //看板(1)の画像がNULLの時のみ作成
    for (int i = 0; i < Signboard1_Count; ++i)
    {
        if (g_pSignboard[i] == NULL)
        {
            g_pSignboard[i] = createSprite(Tex_Signboard, Signboard_Size_X, Signboard_Size_Y);
            g_pSignboard[i]->setPos(Signboard1_Pos[i]);
        }
    }
    //看板の矢印(0)の画像がNULLの時のみ作成
    for (int i = 0; i < Signboard1_Count; ++i)
    {
        if (g_pSignboardArrow[i] == NULL)
        {
            g_pSignboardArrow[i] = createSprite(Tex_SignboardArrow, SignboardArrow_Size_X, SignboardArrow_Size_Y);
            g_pSignboardArrow[i]->setPos(g_pSignboard[i]->getPos().x + 6.0f, g_pSignboard[i]->getPos().y + 17.0f);
        }
    }

    //吹き出しの画像がNULLの時のみ作成
    if (g_pSpeechBalloon == NULL)
    {
        g_pSpeechBalloon = createSprite(Tex_SpeechBalloon, SpeechBalloon_Size_X, SpeechBalloon_Size_Y);
        g_pSpeechBalloon->setPos(SpeechBalloon_Pos);
    }
    //ににの画像がNULLの時のみ作成
    if (g_pNini == NULL)
    {
        g_pNini = createSprite(Tex_Nini, Nini_Size_X, Nini_Size_Y);
        g_pNini->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //ににの感情マークの画像がNULLの時のみ作成
    if (g_pNiniEmotion == NULL)
    {
        g_pNiniEmotion = createSprite(Tex_NiniEmotion, NiniEmotion_Size_X, NiniEmotion_Size_Y);
        g_pNiniEmotion->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //名前の画像がNULLの時のみ作成
    if (g_pName == NULL)
    {
        g_pName = createSprite(Tex_Name, Name_Size_X, Name_Size_Y);
        g_pName->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //吹き出しのUIの画像がNULLの時のみ作成
    if (g_pSpeechBalloonUI == NULL)
    {
        g_pSpeechBalloonUI = createSprite(Tex_SpeechBalloonUI, SpeechBalloonUI_Size_X, SpeechBalloonUI_Size_Y);
        g_pSpeechBalloonUI->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //分岐用吹き出しの画像がNULLの時のみ作成
    if (g_pSpeechBalloonSelect == NULL)
    {
        g_pSpeechBalloonSelect = createSprite(Tex_SpeechBalloonSelect, SpeechBalloonSelect_Size_X, SpeechBalloonSelect_Size_Y);
        g_pSpeechBalloonSelect->setPos(350.0f, 48.0f);
    }

    //セリフ(1)の画像がNULLの時のみ作成
    if (g_Clear == false)
    {
        if (g_pDialogue == NULL)
        {
            g_pDialogue = createSprite(Tex_Dialogue1_1, Dialogue_Size_X, Dialogue_Size_Y);
            g_pDialogue->setPos(140.0f, 295.0f);
        }
    }
    //クリア済みのセリフも用意する
    else
    {
        if (g_pDialogue == NULL)
        {
            g_pDialogue = createSprite(Tex_Dialogue3_1, Dialogue_Size_X, Dialogue_Size_Y);
            g_pDialogue->setPos(140.0f, 295.0f);
        }
    }
    //分岐の選択肢(1)の画像がNULLの時のみ作成
    if (g_pDialogueSelect == NULL)
    {
        g_pDialogueSelect = createSprite(Tex_DialogueSelect1_1, DialogueSelect_Size_X, DialogueSelect_Size_Y);
        g_pDialogueSelect->setPos(g_pSpeechBalloonSelect->getPos().x, g_pSpeechBalloonSelect->getPos().y - 3.0f);
    }

    //背景(1)の画像がNULLの時のみ作成
    for (int i = 0; i < BackGround1_Count; ++i)
    {
        if (g_pBackGround[i] == NULL)
        {
            g_pBackGround[i] = createSprite(Tex_BackGround1, BackGround_Size_X, BackGround_Size_Y);
            g_pBackGround[i]->setPos(960.0f + WINDOW_WIDTH * 2 * i, 0.0f);
        }
    }

    //各ステージに必要なオブジェクトの数を代入する
    BackGround_Count = BackGround1_Count;
    Ground_Count = Ground1_Count;
    Hole_Count = Hole1_Count;
    CliffSide_Count = CliffSide1_Count;
    CliffCenter_Count = CliffCenter1_Count;
    HillSide_Count = HillSide1_Count;
    HillCenter_Count = HillCenter1_Count;
    HillCollision_Count = HillCollision1_Count;
    Block_Count = Block1_Count;

    Niboshi_Count = Niboshi1_Count;
}

/*
* 関数名　  ：procPlayBegin_Stage2()
* 処理内容　：ステージ2画面の開始処理
*/
void COriginalGameApp::procPlayBegin_Stage2()
{
    //プレイヤーの画像がNULLの時のみ作成
    if (g_pPlayer == NULL)
    {
        g_pPlayer = createSprite(Tex_Player, Player_Size_X, Player_Size_Y);

        //リスポーン地点に設定
        if (MissCount != 0)
        {
            g_pPlayer->setPos(-430.0f, -304.0f);
        }
        else
        {
            g_pPlayer->setPos(-818.0f, -304.0f);
        }
    }
    //プレイヤーの当たり判定の画像がNULLの時のみ作成
    if (g_pPlayerCollisionBottom == NULL)
    {
        g_pPlayerCollisionBottom = createSprite(Tex_PlayerCollisionBottom, PlayerCollision_Size_Bottom_X, PlayerCollision_Size_Bottom_Y);
        g_pPlayerCollisionBottom->setPos(-868.5f, -301.0f);
    }
    if (g_pPlayerCollisionSide == NULL)
    {
        g_pPlayerCollisionSide = createSprite(Tex_PlayerCollisionSide, PlayerCollision_Size_Side_X, PlayerCollision_Size_Side_Y);
        g_pPlayerCollisionSide->setPos(-846.0f, -273.0f);
    }

    //リスポーンハウスの画像がNULLの時のみ作成
    if (g_pHouse == NULL)
    {
        g_pHouse = createSprite(Tex_House, House_Size_X, House_Size_Y);
        g_pHouse->setPos(House_Pos);
    }

    //にぼしのUIの画像がNULLの時のみ作成
    if (g_pNiboshiUI == NULL)
    {
        g_pNiboshiUI = createSprite(Tex_NiboshiUI, UI_Size_X, UI_Size_Y);
        g_pNiboshiUI->setPos(UI_Pos);
    }
    //かつおぶしのUIの画像がNULLの時のみ作成
    if (g_pKatuobushiUI == NULL)
    {
        g_pKatuobushiUI = createSprite(Tex_KatuobushiUI, UI_Size_X, UI_Size_Y);
        g_pKatuobushiUI->setPos(UI_Pos.x, UI_Pos.y - UI_Size_Y);
    }
    //残機のUIの画像がNULLの時のみ作成
    if (g_pLifeUI == NULL)
    {
        g_pLifeUI = createSprite(Tex_LifeUI, UI_Size_X, UI_Size_Y);
        g_pLifeUI->setPos(UI_Pos.x, UI_Pos.y - UI_Size_Y * 2);
        if (g_Clear == true)
        {
            g_pLifeUI->setAnimation(1);
        }
    }
    //UIの数字の画像がNULLの時のみ作成
    for (int i = 0; i < 6; ++i)
    {
        if (g_pNumber[i] == NULL)
        {
            g_pNumber[i] = createSprite(Tex_Number, Number_Size_X, Number_Size_Y);
            g_pNumber[i]->setPos(UI_Pos.x + 115.0f + (60.0f * (i % 2)), UI_Pos.y - 100.0f * (i / 2));
        }
    }

    //床(2)の画像がNULLの時のみ作成
    for (int i = 0; i < Ground2_Count; ++i)
    {
        if (g_pGround[i] == NULL)
        {
            g_pGround[i] = createSprite(Tex_Ground2, Ground_Size_X, Ground_Size_Y);
            g_pGround[i]->setPos(Ground2_Pos[i]);
        }
    }

    //穴(2)の画像がNULLの時のみ作成
    for (int i = 0; i < Hole2_Count; ++i)
    {
        //iが偶数の時
        if (i % 2 == 0)
        {
            //右向きの穴の画像を作成
            if (g_pHole[i] == NULL)
            {
                g_pHole[i] = createSprite(Tex_Hole2, Hole_Size_X, Hole_Size_Y);
                g_pHole[i]->setPos(Hole2_Pos[i]);
            }
        }
        //iが奇数の時
        else
        {
            //左向きの穴の画像を作成
            if (g_pHole[i] == NULL)
            {
                g_pHole[i] = createSprite(Tex_Hole2, Hole_Size_X, Hole_Size_Y);
                g_pHole[i]->setAngle({ 0.0f, 180.0f, 0.0f });
                g_pHole[i]->setPos(Hole2_Pos[i]);
            }
        }
    }

    //崖(2)の画像がNULLの時のみ作成
    for (int i = 0; i < CliffSide2_Count; ++i)
    {
        //iが偶数の時
        if (i % 2 == 0)
        {
            //右向きの崖の画像を作成
            if (g_pCliffSide[i] == NULL)
            {
                g_pCliffSide[i] = createSprite(Tex_CliffSide2, Cliff_Size_X, Cliff_Size_Y);
                g_pCliffSide[i]->setPos(CliffSide2_Pos[i]);
            }
        }
        //iが奇数の時
        else
        {
            //左向きの崖の画像を作成
            if (g_pCliffSide[i] == NULL)
            {
                g_pCliffSide[i] = createSprite(Tex_CliffSide2, Cliff_Size_X, Cliff_Size_Y);
                g_pCliffSide[i]->setAngle({ 0.0f, 180.0f, 0.0f });
                g_pCliffSide[i]->setPos(CliffSide2_Pos[i]);
            }
        }
    }
    //真ん中の崖(2)の画像がNULLの時のみ作成
    for (int i = 0; i < CliffCenter2_Count; ++i)
    {
        if (g_pCliffCenter[i] == NULL)
        {
            g_pCliffCenter[i] = createSprite(Tex_CliffCenter2, Cliff_Size_X * 2, Cliff_Size_Y);
            g_pCliffCenter[i]->setPos(CliffCenter2_Pos[i]);
        }
    }

    //丘(2)の画像がNULLの時のみ作成
    for (int i = 0; i < HillSide2_Count; ++i)
    {
        //iが偶数の時
        if (i % 2 == 0)
        {
            //右向きの丘の画像を作成
            if (g_pHillSide[i] == NULL)
            {
                g_pHillSide[i] = createSprite(Tex_CliffSide1, Hill_Size_X, Hill_Size_Y);
                g_pHillSide[i]->setPos(HillSide2_Pos[i]);
            }
        }
        //iが奇数の時
        else
        {
            //左向きの丘の画像を作成
            if (g_pHillSide[i] == NULL)
            {
                g_pHillSide[i] = createSprite(Tex_CliffSide1, Hill_Size_X, Hill_Size_Y);
                g_pHillSide[i]->setAngle({ 0.0f, 180.0f, 0.0f });
                g_pHillSide[i]->setPos(HillSide2_Pos[i]);
            }
        }
    }
    //真ん中の丘(2)の画像がNULLの時のみ作成
    for (int i = 0; i < HillCenter2_Count; ++i)
    {
        if (g_pHillCenter[i] == NULL)
        {
            g_pHillCenter[i] = createSprite(Tex_CliffCenter1, Hill_Size_X * 2, Hill_Size_Y);
            g_pHillCenter[i]->setPos(HillCenter2_Pos[i]);
        }
    }
    //丘の当たり判定(2)の画像がNULLの時のみ作成
    for (int i = 0; i < HillCollision2_Count; ++i)
    {
        if (g_pHillCollision[i] == NULL)
        {
            g_pHillCollision[i] = createSprite(Tex_HillCollision, HillCollision_Size_X, HillCollision_Size_Y);
            g_pHillCollision[i]->setPos(HillCollision2_Pos[i]);
        }
    }

    //トゲ(2)の画像がNULLの時のみ作成
    for (int i = 0; i < Needl2_Count; ++i)
    {
        if (g_pNeedl[i] == NULL)
        {
            g_pNeedl[i] = createSprite(Tex_Needl, Needl_Size_X, Needl_Size_Y);
            g_pNeedl[i]->setPos(Needl2_Pos[i]);
        }
    }

    //リフト(2)の画像がNULLの時のみ作成
    for (int i = 0; i < MoveLift2_Count; ++i)
    {
        if (g_pMoveLift[i] == NULL)
        {
            g_pMoveLift[i] = createSprite(Tex_MoveLift, Lift_Size_X, Lift_Size_Y);
            g_pMoveLift[i]->setPos(MoveLift2_Pos[i]);
        }
    }
    for (int i = 0; i < FallLift2_Count; ++i)
    {
        if (g_pFallLift[i] == NULL)
        {
            g_pFallLift[i] = createSprite(Tex_FallLift, Lift_Size_X, Lift_Size_Y);
            g_pFallLift[i]->setPos(FallLift2_Pos[i]);
        }
    }
    //リフトの当たり判定(2)の画像がNULLの時のみ作成
    for (int i = 0; i < MoveLift2_Count; ++i)
    {
        if (g_pMoveLiftCollision[i] == NULL && g_pMoveLift[i] != NULL)
        {
            g_pMoveLiftCollision[i] = createSprite(Tex_HillCollision, LiftCollision_Size_X, LiftCollision_Size_Y);
            g_pMoveLiftCollision[i]->setPos(g_pMoveLift[i]->getPos().x, g_pMoveLift[i]->getPos().y + 5.0f);
        }
    }
    for (int i = 0; i < FallLift2_Count; ++i)
    {
        if (g_pFallLiftCollision[i] == NULL && g_pFallLift[i] != NULL)
        {
            g_pFallLiftCollision[i] = createSprite(Tex_HillCollision, LiftCollision_Size_X, LiftCollision_Size_Y);
            g_pFallLiftCollision[i]->setPos(g_pFallLift[i]->getPos().x, g_pFallLift[i]->getPos().y + 5.0f);
        }
    }

    //ブロック(2)の画像がNULLの時のみ作成
    for (int i = 0; i < Block2_Count; ++i)
    {
        if (g_pBlock[i] == NULL)
        {
            g_pBlock[i] = createSprite(Tex_Block, Block_Size_X, Block_Size_Y);
            g_pBlock[i]->setPos(Block2_Pos[i]);
            //クリア済はブロックを表示
            if (g_Clear == false)
            {
                g_pBlock[i]->setAnimation(1);
            }
        }
    }

    //にぼし(2)の画像がNULLの時のみ作成
    for (int i = 0; i < Niboshi2_Count; ++i)
    {
        if (g_pNiboshi[i] == NULL)
        {
            g_pNiboshi[i] = createSprite(Tex_Niboshi, Niboshi_Size_X, Niboshi_Size_Y);
            g_pNiboshi[i]->setPos(Niboshi2_Pos[i]);
            g_pNiboshi[i]->setAngle({ 0.0f, 0.0f, -30.0f });
        }
    }

    //かつおぶし(2)の画像がNULLの時のみ作成
    for (int i = 0; i < Katuobushi_Count; ++i)
    {
        //獲得判定のあるものは作らない
        if (g_pKatuobushi[i] == NULL && KatuobushiFlag[Stage - 1][i] == false)
        {
            g_pKatuobushi[i] = createSprite(Tex_Katuobushi, Katuobushi_Size_X, Katuobushi_Size_Y);
            g_pKatuobushi[i]->setPos(Katuobushi2_Pos[i]);
        }
    }

    //看板(2)の画像がNULLの時のみ作成
    for (int i = 0; i < Signboard2_Count; ++i)
    {
        if (g_pSignboard[i] == NULL)
        {
            g_pSignboard[i] = createSprite(Tex_Signboard, Signboard_Size_X, Signboard_Size_Y);
            g_pSignboard[i]->setPos(Signboard2_Pos[i]);
        }
    }
    //看板の矢印(0)の画像がNULLの時のみ作成
    for (int i = 0; i < Signboard2_Count; ++i)
    {
        if (g_pSignboardArrow[i] == NULL)
        {
            g_pSignboardArrow[i] = createSprite(Tex_SignboardArrow, SignboardArrow_Size_X, SignboardArrow_Size_Y);
            g_pSignboardArrow[i]->setPos(g_pSignboard[i]->getPos().x + 6.0f, g_pSignboard[i]->getPos().y + 17.0f);
        }
    }

    //吹き出しの画像がNULLの時のみ作成
    if (g_pSpeechBalloon == NULL)
    {
        g_pSpeechBalloon = createSprite(Tex_SpeechBalloon, SpeechBalloon_Size_X, SpeechBalloon_Size_Y);
        g_pSpeechBalloon->setPos(SpeechBalloon_Pos);
    }
    //ににの画像がNULLの時のみ作成
    if (g_pNini == NULL)
    {
        g_pNini = createSprite(Tex_Nini, Nini_Size_X, Nini_Size_Y);
        g_pNini->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //ににの感情マークの画像がNULLの時のみ作成
    if (g_pNiniEmotion == NULL)
    {
        g_pNiniEmotion = createSprite(Tex_NiniEmotion, NiniEmotion_Size_X, NiniEmotion_Size_Y);
        g_pNiniEmotion->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //名前の画像がNULLの時のみ作成
    if (g_pName == NULL)
    {
        g_pName = createSprite(Tex_Name, Name_Size_X, Name_Size_Y);
        g_pName->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //吹き出しのUIの画像がNULLの時のみ作成
    if (g_pSpeechBalloonUI == NULL)
    {
        g_pSpeechBalloonUI = createSprite(Tex_SpeechBalloonUI, SpeechBalloonUI_Size_X, SpeechBalloonUI_Size_Y);
        g_pSpeechBalloonUI->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //分岐用吹き出しの画像がNULLの時のみ作成
    if (g_pSpeechBalloonSelect == NULL)
    {
        g_pSpeechBalloonSelect = createSprite(Tex_SpeechBalloonSelect, SpeechBalloonSelect_Size_X, SpeechBalloonSelect_Size_Y);
        g_pSpeechBalloonSelect->setPos(350.0f, 48.0f);
    }

    //セリフ(2)の画像がNULLの時のみ作成
    if (g_pDialogue == NULL)
    {
        g_pDialogue = createSprite(Tex_Dialogue2_1, Dialogue_Size_X, Dialogue_Size_Y);
        g_pDialogue->setPos(140.0f, 295.0f);
    }

    //背景(2)の画像がNULLの時のみ作成
    for (int i = 0; i < BackGround2_Count; ++i)
    {
        if (g_pBackGround[i] == NULL)
        {
            g_pBackGround[i] = createSprite(Tex_BackGround2, BackGround_Size_X, BackGround_Size_Y);
            g_pBackGround[i]->setPos(960.0f + WINDOW_WIDTH * 2 * i, 0.0f);
        }
    }

    //各ステージに必要なオブジェクトの数を代入する
    BackGround_Count = BackGround2_Count;
    Ground_Count = Ground2_Count;
    Hole_Count = Hole2_Count;
    CliffSide_Count = CliffSide2_Count;
    CliffCenter_Count = CliffCenter2_Count;
    HillSide_Count = HillSide2_Count;
    HillCenter_Count = HillCenter2_Count;
    HillCollision_Count = HillCollision2_Count;
    Needl_Count = Needl2_Count;
    MoveLift_Count = MoveLift2_Count;
    FallLift_Count = FallLift2_Count;
    Block_Count = Block2_Count;

    Niboshi_Count = Niboshi2_Count;
}

/*
* 関数名　  ：procPlayBegin_Stage3()
* 処理内容　：ステージ3画面の開始処理
*/
void COriginalGameApp::procPlayBegin_Stage3()
{
    //プレイヤーの画像がNULLの時のみ作成
    if (g_pPlayer == NULL)
    {
        g_pPlayer = createSprite(Tex_Player, Player_Size_X, Player_Size_Y);

        //リスポーン地点に設定
        if (MissCount != 0)
        {
            g_pPlayer->setPos(-430.0f, -304.0f);
        }
        else
        {
            g_pPlayer->setPos(-818.0f, -304.0f);
        }
    }
    //プレイヤーの当たり判定の画像がNULLの時のみ作成
    if (g_pPlayerCollisionBottom == NULL)
    {
        g_pPlayerCollisionBottom = createSprite(Tex_PlayerCollisionBottom, PlayerCollision_Size_Bottom_X, PlayerCollision_Size_Bottom_Y);
        g_pPlayerCollisionBottom->setPos(-868.5f, -301.0f);
    }
    if (g_pPlayerCollisionSide == NULL)
    {
        g_pPlayerCollisionSide = createSprite(Tex_PlayerCollisionSide, PlayerCollision_Size_Side_X, PlayerCollision_Size_Side_Y);
        g_pPlayerCollisionSide->setPos(-846.0f, -273.0f);
    }

    //床(3)の画像がNULLの時のみ作成
    for (int i = 0; i < Ground3_Count; ++i)
    {
        if (g_pGround[i] == NULL)
        {
            g_pGround[i] = createSprite(Tex_Ground2, Ground_Size_X, Ground_Size_Y);
            g_pGround[i]->setPos(Ground3_Pos[i]);
        }
    }

    //ににの画像がNULLの時のみ作成
    if (g_pNini == NULL)
    {
        g_pNini = createSprite(Tex_Nini, Nini_Size_X, Nini_Size_Y);
        g_pNini->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //ににの画像がNULLの時のみ作成
    if (g_pNini == NULL)
    {
        g_pNini = createSprite(Tex_Nini, Nini_Size_X, Nini_Size_Y);
        g_pNini->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //吹き出しの画像がNULLの時のみ作成
    if (g_pSpeechBalloon == NULL)
    {
        g_pSpeechBalloon = createSprite(Tex_SpeechBalloon, SpeechBalloon_Size_X, SpeechBalloon_Size_Y);
        g_pSpeechBalloon->setPos(SpeechBalloon_Pos);
    }
    //ににの画像がNULLの時のみ作成
    if (g_pNini == NULL)
    {
        g_pNini = createSprite(Tex_Nini, Nini_Size_X, Nini_Size_Y);
        g_pNini->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //ににの感情マークの画像がNULLの時のみ作成
    if (g_pNiniEmotion == NULL)
    {
        g_pNiniEmotion = createSprite(Tex_NiniEmotion, NiniEmotion_Size_X, NiniEmotion_Size_Y);
        g_pNiniEmotion->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //名前の画像がNULLの時のみ作成
    if (g_pName == NULL)
    {
        g_pName = createSprite(Tex_Name, Name_Size_X, Name_Size_Y);
        g_pName->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //吹き出しのUIの画像がNULLの時のみ作成
    if (g_pSpeechBalloonUI == NULL)
    {
        g_pSpeechBalloonUI = createSprite(Tex_SpeechBalloonUI, SpeechBalloonUI_Size_X, SpeechBalloonUI_Size_Y);
        g_pSpeechBalloonUI->setPos(0.0f, -WINDOW_HEIGHT);
    }

    //セリフ(3)の画像がNULLの時のみ作成
    if (g_pDialogue == NULL)
    {
        g_pDialogue = createSprite(Tex_Dialogue2_6, Dialogue_Size_X, Dialogue_Size_Y);
        g_pDialogue->setPos(140.0f, 295.0f);
    }

    //宝箱(3)の画像がNULLの時のみ作成
    if (g_pTreasure == NULL)
    {
        g_pTreasure = createSprite(Tex_Treasure, 200.0, 150.0);
        g_pTreasure->setPos(400.0f, -340.0f);
    }
    //王冠(3)の画像がNULLの時のみ作成
    if (g_pCrown == NULL)
    {
        g_pCrown = createSprite(Tex_Crown, 100.0, 100.0);
        g_pCrown->setPos(380.0f, -340.0f);
        g_pCrown->setActive(false);
    }

    //背景(3)の画像がNULLの時のみ作成
    for (int i = 0; i < BackGround3_Count; ++i)
    {
        if (g_pBackGround[i] == NULL)
        {
            g_pBackGround[i] = createSprite(Tex_BackGround2, BackGround_Size_X, BackGround_Size_Y);
            g_pBackGround[i]->setPos(960.0f + WINDOW_WIDTH * 2 * i, 0.0f);
        }
    }

    //各ステージに必要なオブジェクトの数を代入する
    BackGround_Count = BackGround3_Count;
    Ground_Count = Ground3_Count;
}

/*
* 関数名　  ：procPlayMain_Tuto()
* 処理内容　：チュートリアル画面のメイン処理
*/
void COriginalGameApp::procPlayMain_Tuto()
{
    //プレイヤーの処理
    if (g_pPlayer != NULL)
    {
        //ミス時、一部の処理を省く。
        if (g_Miss == false)
        {
            //会話中は動けないようにする
            if (g_Speech == false)
            {
                procPlayMain_PlayerMove();
            }
            procPlayMain_PlayerCollisionSide();
            procPlayMain_PlayerGurabitexi();
            procPlayMain_MoveScroll();
            if (g_Speech == false)
            {
                procPlayMain_PlayerSit();
                procPlayMain_PlayerJump();

                //崖登りのフラグが来るまでは登れない
                if (Tuto >= 4)
                {
                    procPlayMain_PlayerClimb();
                }
            }
            procPlayMain_PlayerCollisionBottom();

            //会話のフラグを検知する
            procPlayMain_SpeechDetection();
        }

        //ミスのチェック
        procPlayMina_MissCheck();

        //プレイヤーアニメーション
        procPlayMain_PlayerAnimation();
    }
    if (g_Speech == true)
    {
        procPlayMain_SpeechBalloonAnimation();
    }

    //プレイヤーの画像が作成された時のみ描画
    if (g_pPlayer != NULL)
    {
        renderSprite(g_pPlayer);
    }
    //プレイヤーの当たり判定の画像が作成された時のみ描画
    if (g_pPlayerCollisionBottom != NULL)
    {
        //renderSprite(g_pPlayerCollisionBottom);
    }
    if (g_pPlayerCollisionSide != NULL)
    {
        //renderSprite(g_pPlayerCollisionSide);
    }

    //床(0)の画像が作成された時のみ描画
    for (int i = 0; i < Ground0_Count; i++)
    {
        if (g_pGround[i] != NULL)
        {
            renderSprite(g_pGround[i]);
        }
    }

    //看板の矢印(0)の画像が作成された時のみ描画
    for (int i = 0; i < Signboard0_Count; ++i)
    {
        if (g_pSignboardArrow[i] != NULL)
        {
            renderSprite(g_pSignboardArrow[i]);
        }
    }
    //看板(0)の画像が作成された時のみ描画
    for (int i = 0; i < Signboard0_Count; ++i)
    {
        if (g_pSignboard[i] != NULL)
        {
            renderSprite(g_pSignboard[i]);
        }
    }

    //穴(0)の画像が作成された時のみ描画
    for (int i = 0; i < Hole0_Count; ++i)
    {
        if (g_pHole[i] != NULL)
        {
            renderSprite(g_pHole[i]);
        }
    }

    //崖(0)の画像が作成された時のみ描画
    for (int i = 0; i < CliffSide0_Count; ++i)
    {
        if (g_pCliffSide[i] != NULL)
        {
            renderSprite(g_pCliffSide[i]);
        }
    }
    //真ん中の崖(0)の画像が作成された時のみ描画
    for (int i = 0; i < CliffCenter0_Count; ++i)
    {
        if (g_pCliffCenter[i] != NULL)
        {
            renderSprite(g_pCliffCenter[i]);
        }
    }

    //背景(0)の画像が作成された時のみ描画
    for (int i = 0; i < BackGround0_Count; ++i)
    {
        if (g_pBackGround[i] != NULL)
        {
            renderSprite(g_pBackGround[i]);
        }
    }
}

/*
* 関数名　  ：procPlayMain_Stage1()
* 処理内容　：ステージ1の画面のメイン処理
*/
void COriginalGameApp::procPlayMain_Stage1()
{
    //プレイヤーの処理
    if (g_pPlayer != NULL)
    {
        //ミス時、一部の処理を省く。
        if (g_Miss == false)
        {
            //基本操作
            //会話中は動けないようにする
            if (g_Speech == false)
            {
                procPlayMain_PlayerMove();
                procPlayMain_StageChange();
            }
            procPlayMain_PlayerCollisionSide();
            procPlayMain_PlayerGurabitexi();
            if (g_Speech == false)
            {
                procPlayMain_PlayerSit();
                procPlayMain_PlayerJump();
                procPlayMain_PlayerClimb();
            }
            procPlayMain_PlayerCollisionBottom();

            //アイテムの処理
            procPlayMain_GetNiboshi();
            procPlayMain_GetKatuobushi();
            procPlayMain_CountUI();

            //スクロール
            procPlayMain_MoveScroll();
        }

        //ミスのチェック
        procPlayMina_MissCheck();

        //プレイヤーアニメーション
        procPlayMain_PlayerAnimation();

        //セリフが全て終わると常時フラグを無効にする
        if (g_AllDialogue == true)
        {
            g_Speech = false;
        }

        //初回のみ
        //会話時のみ吹き出しを表示
        if (g_Speech == true && MissCount == 0)
        {
            procPlayMain_SpeechBalloonAnimation();
        }
    }

    //プレイヤーの画像が作成された時のみ描画
    if (g_pPlayer != NULL)
    {
        renderSprite(g_pPlayer);
    }
    //プレイヤーの当たり判定の画像が作成された時のみ描画
    if (g_pPlayerCollisionBottom != NULL)
    {
        //renderSprite(g_pPlayerCollisionBottom);
    }
    if (g_pPlayerCollisionSide != NULL)
    {
        //renderSprite(g_pPlayerCollisionSide);
    }

    //リスポーンハウスの画像が作成された時のみ描画
    if (g_pHouse != NULL)
    {
        renderSprite(g_pHouse);
    }

    //にぼしのUIの画像が作成された時のみ描画
    if (g_pNiboshiUI != NULL)
    {
        renderSprite(g_pNiboshiUI);
    }
    //かつおぶしのUIの画像が作成された時のみ描画
    if (g_pKatuobushiUI != NULL)
    {
        renderSprite(g_pKatuobushiUI);
    }
    //残機のUIの画像が作成された時のみ描画
    if (g_pLifeUI != NULL)
    {
        renderSprite(g_pLifeUI);
    }
    //UIの数字の画像が作成された時のみ描画
    for (int i = 0; i < 6; ++i)
    {
        if (g_pNumber[i] != NULL)
        {
            renderSprite(g_pNumber[i]);
        }
    }

    //看板の矢印(1)の画像が作成された時のみ描画
    for (int i = 0; i < Signboard1_Count; ++i)
    {
        if (g_pSignboardArrow[i] != NULL)
        {
            renderSprite(g_pSignboardArrow[i]);
        }
    }
    //看板(1)の画像が作成された時のみ描画
    for (int i = 0; i < Signboard1_Count; ++i)
    {
        if (g_pSignboard[i] != NULL)
        {
            renderSprite(g_pSignboard[i]);
        }
    }

    //床(1)の画像が作成された時のみ描画
    for (int i = 0; i < Ground1_Count; i++)
    {
        if (g_pGround[i] != NULL)
        {
            renderSprite(g_pGround[i]);
        }
    }

    //にぼし(1)の画像が作成された時のみ描画
    for (int i = 0; i < Niboshi1_Count; ++i)
    {
        if (g_pNiboshi[i] != NULL)
        {
            renderSprite(g_pNiboshi[i]);
        }
    }
    //かつおぶし(1)の画像が作成された時のみ描画
    for (int i = 0; i < Katuobushi_Count; ++i)
    {
        if (g_pKatuobushi[i] != NULL)
        {
            renderSprite(g_pKatuobushi[i]);
        }
    }

    //ブロック(1)の画像が作成された時のみ描画
    for (int i = 0; i < Block1_Count; ++i)
    {
        if (g_pBlock[i] != NULL)
        {
            renderSprite(g_pBlock[i]);
        }
    }

    //穴(1)の画像が作成された時のみ描画
    for (int i = 0; i < Hole1_Count; ++i)
    {
        if (g_pHole[i] != NULL)
        {
            renderSprite(g_pHole[i]);
        }
    }

    //崖(1)の画像が作成された時のみ描画
    for (int i = 0; i < CliffSide1_Count; ++i)
    {
        if (g_pCliffSide[i] != NULL)
        {
            renderSprite(g_pCliffSide[i]);
        }
    }
    //真ん中の崖(1)の画像が作成された時のみ描画
    for (int i = 0; i < CliffCenter1_Count; ++i)
    {
        if (g_pCliffCenter[i] != NULL)
        {
            renderSprite(g_pCliffCenter[i]);
        }
    }

    //丘(1)の画像が作成された時のみ描画
    for (int i = 0; i < HillSide1_Count; ++i)
    {
        if (g_pHillSide[i] != NULL)
        {
            renderSprite(g_pHillSide[i]);
        }
    }
    //真ん中の丘(1)の画像が作成された時のみ描画
    for (int i = 0; i < HillCenter1_Count; ++i)
    {
        if (g_pHillCenter[i] != NULL)
        {
            renderSprite(g_pHillCenter[i]);
        }
    }
    //丘の当たり判定(1)の画像が作成された時のみ描画
    for (int i = 0; i < HillCollision1_Count; ++i)
    {
        if (g_pHillCollision[i] != NULL)
        {
            //renderSprite(g_pHillCollision[i]);
        }
    }

    //背景(1)の画像が作成された時のみ描画
    for (int i = 0; i < BackGround1_Count; ++i)
    {
        if (g_pBackGround[i] != NULL)
        {
            renderSprite(g_pBackGround[i]);
        }
    }
}

/*
* 関数名　  ：procPlayMain_Stage2()
* 処理内容　：ステージ2の画面のメイン処理
*/
void COriginalGameApp::procPlayMain_Stage2()
{
    //プレイヤーの処理
    if (g_pPlayer != NULL)
    {
        //ミス時、一部の処理を省く。
        if (g_Miss == false)
        {
            //基本操作
            //会話中は動けないようにする
            if (g_Speech == false)
            {
                procPlayMain_PlayerMove();
                procPlayMain_StageChange();
            }
            procPlayMain_PlayerCollisionSide();
            procPlayMain_PlayerGurabitexi();
            if (g_Speech == false)
            {
                procPlayMain_PlayerSit();
                procPlayMain_PlayerJump();
                procPlayMain_PlayerClimb();
            }
            procPlayMain_PlayerCollisionBottom();

            //アイテムの処理
            procPlayMain_GetNiboshi();
            procPlayMain_GetKatuobushi();
            procPlayMain_CountUI();

            //スクロール
            procPlayMain_MoveScroll();
        }


        //リフトの処理
        procPlayMain_MoveLift();
        procPlayMain_FallLift();

        //トゲの処理
        procPlayMain_NeedlMove();

        //プレイヤーアニメーション
        procPlayMain_PlayerAnimation();

        //ミスのチェック
        procPlayMina_MissCheck();

        //セリフが全て終わると常時フラグを無効にする
        if (g_AllDialogue == true)
        {
            g_Speech = false;
        }

        //初回のみ
        //会話時のみ吹き出しを表示
        if (g_Speech == true && MissCount == 0)
        {
            procPlayMain_SpeechBalloonAnimation();
        }
    }

    //プレイヤーの画像が作成された時のみ描画
    if (g_pPlayer != NULL)
    {
        renderSprite(g_pPlayer);
    }
    //プレイヤーの当たり判定の画像が作成された時のみ描画
    if (g_pPlayerCollisionBottom != NULL)
    {
        //renderSprite(g_pPlayerCollisionBottom);
    }
    if (g_pPlayerCollisionSide != NULL)
    {
        //renderSprite(g_pPlayerCollisionSide);
    }

    //リスポーンハウスの画像が作成された時のみ描画
    if (g_pHouse != NULL)
    {
        renderSprite(g_pHouse);
    }

    //にぼしのUIの画像が作成された時のみ描画
    if (g_pNiboshiUI != NULL)
    {
        renderSprite(g_pNiboshiUI);
    }
    //かつおぶしのUIの画像が作成された時のみ描画
    if (g_pKatuobushiUI != NULL)
    {
        renderSprite(g_pKatuobushiUI);
    }
    //残機のUIの画像が作成された時のみ描画
    if (g_pLifeUI != NULL)
    {
        renderSprite(g_pLifeUI);
    }
    //UIの数字の画像が作成された時のみ描画
    for (int i = 0; i < 6; ++i)
    {
        if (g_pNumber[i] != NULL)
        {
            renderSprite(g_pNumber[i]);
        }
    }

    //床(2)の画像が作成された時のみ描画
    for (int i = 0; i < Ground2_Count; i++)
    {
        if (g_pGround[i] != NULL)
        {
            renderSprite(g_pGround[i]);
        }
    }

    //トゲ(2)の画像が作成された時のみ描画
    for (int i = 0; i < Needl2_Count; ++i)
    {
        if (g_pNeedl[i] != NULL)
        {
            renderSprite(g_pNeedl[i]);
        }
    }

    //リフト(2)の画像が作成された時のみ描画
    for (int i = 0; i < MoveLift2_Count; ++i)
    {
        if (g_pMoveLift[i] != NULL)
        {
            renderSprite(g_pMoveLift[i]);
        }
    }
    for (int i = 0; i < FallLift2_Count; ++i)
    {
        if (g_pFallLift[i] != NULL)
        {
            renderSprite(g_pFallLift[i]);
        }
    }
    //リフト当たり判定(2)の画像が作成された時のみ描画
    for (int i = 0; i < MoveLift2_Count; ++i)
    {
        if (g_pMoveLiftCollision[i] != NULL)
        {
            //renderSprite(g_pMoveLiftCollision[i]);
        }
    }
    for (int i = 0; i < FallLift2_Count; ++i)
    {
        if (g_pFallLiftCollision[i] != NULL)
        {
            //renderSprite(g_pFallLiftCollision[i]);
        }
    }

    //にぼし(2)の画像が作成された時のみ描画
    for (int i = 0; i < Niboshi2_Count; ++i)
    {
        if (g_pNiboshi[i] != NULL)
        {
            renderSprite(g_pNiboshi[i]);
        }
    }
    //かつおぶし(2)の画像が作成された時のみ描画
    for (int i = 0; i < Katuobushi_Count; ++i)
    {
        if (g_pKatuobushi[i] != NULL)
        {
            renderSprite(g_pKatuobushi[i]);
        }
    }

    //看板の矢印(2)の画像が作成された時のみ描画
    for (int i = 0; i < Signboard2_Count; ++i)
    {
        if (g_pSignboardArrow[i] != NULL)
        {
            renderSprite(g_pSignboardArrow[i]);
        }
    }
    //看板(2)の画像が作成された時のみ描画
    for (int i = 0; i < Signboard2_Count; ++i)
    {
        if (g_pSignboard[i] != NULL)
        {
            renderSprite(g_pSignboard[i]);
        }
    }

    //ブロック(2)の画像が作成された時のみ描画
    for (int i = 0; i < Block2_Count; ++i)
    {
        if (g_pBlock[i] != NULL)
        {
            renderSprite(g_pBlock[i]);
        }
    }

    //穴(2)の画像が作成された時のみ描画
    for (int i = 0; i < Hole2_Count; ++i)
    {
        if (g_pHole[i] != NULL)
        {
            renderSprite(g_pHole[i]);
        }
    }

    //崖(2)の画像が作成された時のみ描画
    for (int i = 0; i < CliffSide2_Count; ++i)
    {
        if (g_pCliffSide[i] != NULL)
        {
            renderSprite(g_pCliffSide[i]);
        }
    }
    //真ん中の崖(2)の画像が作成された時のみ描画
    for (int i = 0; i < CliffCenter1_Count; ++i)
    {
        if (g_pCliffCenter[i] != NULL)
        {
            renderSprite(g_pCliffCenter[i]);
        }
    }

    //丘(2)の画像が作成された時のみ描画
    for (int i = 0; i < HillSide2_Count; ++i)
    {
        if (g_pHillSide[i] != NULL)
        {
            renderSprite(g_pHillSide[i]);
        }
    }
    //真ん中の丘(2)の画像が作成された時のみ描画
    for (int i = 0; i < HillCenter2_Count; ++i)
    {
        if (g_pHillCenter[i] != NULL)
        {
            renderSprite(g_pHillCenter[i]);
        }
    }
    //丘の当たり判定(2)の画像が作成された時のみ描画
    for (int i = 0; i < HillCollision2_Count; ++i)
    {
        if (g_pHillCollision[i] != NULL)
        {
            //renderSprite(g_pHillCollision[i]);
        }
    }

    //背景(2)の画像が作成された時のみ描画
    for (int i = 0; i < BackGround2_Count; ++i)
    {
        if (g_pBackGround[i] != NULL)
        {
            renderSprite(g_pBackGround[i]);
        }
    }
}

/*
* 関数名　  ：procPlayMain_Stage3()
* 処理内容　：ステージ3の画面のメイン処理
*/
void COriginalGameApp::procPlayMain_Stage3()
{
    //プレイヤーの処理
    if (g_pPlayer != NULL)
    {
        //基本操作
        //会話中は動けないようにする
        if (g_Speech == false && OpenTreasure == false)
        {
            procPlayMain_PlayerMove();
        }
        procPlayMain_PlayerCollisionSide();
        procPlayMain_PlayerGurabitexi();
        if (g_Speech == false && OpenTreasure == false)
        {
            procPlayMain_PlayerSit();
            procPlayMain_PlayerJump();
            procPlayMain_PlayerClimb();
        }
        procPlayMain_PlayerCollisionBottom();

        //プレイヤーアニメーション
        procPlayMain_PlayerAnimation();

        //初回のみ
        //会話時のみ吹き出しを表示
        if (g_Speech == true && MissCount == 0)
        {
            procPlayMain_SpeechBalloonAnimation();
        }

        //宝箱を開ける
        if (g_pPlayer->collision(g_pTreasure))
        {
            //フラグを有効にする
            OpenTreasure = true;
            g_pPlayer->setAnimation(0);
        }

        //宝箱を開ける
        if (OpenTreasure == true && g_Clear != true)
        {
            g_pTreasure->setAnimation(1);
            g_pCrown->setActive(true);

            //カウンターを動かす
            CrownCounter++;
            if (CrownCounter % 2 == 0)
            {
                //王冠を動かす
                g_pCrown->setPos(g_pCrown->getPos().x, g_pCrown->getPos().y + 5);
            }
            if (CrownCounter % 100 == 0)
            {
                //一定量行くと止まりフラグをリセットし、セリフに入る
                CrownCounter = 0;
                OpenTreasure = false;
                g_Speech = true;
                g_Clear = true;
            }
        }
    }

    //プレイヤーの画像が作成された時のみ描画
    if (g_pPlayer != NULL)
    {
        renderSprite(g_pPlayer);
    }
    //プレイヤーの当たり判定の画像が作成された時のみ描画
    if (g_pPlayerCollisionBottom != NULL)
    {
        //renderSprite(g_pPlayerCollisionBottom);
    }
    if (g_pPlayerCollisionSide != NULL)
    {
        //renderSprite(g_pPlayerCollisionSide);
    }

    //王冠の画像が作成された時のみ描画
    if (g_pCrown != NULL)
    {
        renderSprite(g_pCrown);
    }
    //宝箱の画像が作成された時のみ描画
    if (g_pTreasure != NULL)
    {
        renderSprite(g_pTreasure);
    }

    //床(3)の画像が作成された時のみ描画
    for (int i = 0; i < Ground3_Count; i++)
    {
        if (g_pGround[i] != NULL)
        {
            renderSprite(g_pGround[i]);
        }
    }

    //背景(3)の画像が作成された時のみ描画
    for (int i = 0; i < BackGround3_Count; ++i)
    {
        if (g_pBackGround[i] != NULL)
        {
            renderSprite(g_pBackGround[i]);
        }
    }
}

/*
* 関数名　  ：procPlaymain_PlayerMove()
* 処理内容　：プレイヤーの移動処理
*/
void COriginalGameApp::procPlayMain_PlayerMove()
{
    XMFLOAT4 pos = g_pPlayer->getPos();

    //しゃがみ状態とジャンプの時は動けないようにする
    if (g_Sit == false && g_Jump == false)
    {
        if ((getInput()->isKeyPressed(DIK_RIGHTARROW) == false && getInput()->isKeyPressed(DIK_LEFTARROW) == false) ||
            (getInput()->isKeyPressed(DIK_RIGHTARROW) == true && getInput()->isKeyPressed(DIK_LEFTARROW) == true))
        {
            //動いていない時はフラグを無効にする
            g_Walking = false;
            g_Running = false;
            //カウンターをリセットしておく
            MTimeCounter = 0.0f;
        }

        //矢印キーで移動
        else if (getInput()->isKeyPressed(DIK_RIGHTARROW) && g_RightHit == false)
        {
            //カウンターを動かす
            MTimeCounter++;
            //助走をつける
            if (MTimeCounter <= 12.0f)
            {
                pos.x += MTimeCounter;
                //歩いているフラグを有効にする
                g_Walking = true;
            }
            else
            {
                pos.x += PlayerSpeed;
                //走っているフラグを有効にする
                g_Running = true;
                //歩いているフラグを無効にする
                g_Walking = false;
            }
            //プレイヤーの向きを前にする
            g_pPlayer->setAngle({ 0.0f, 0.0f, 0.0f });
            g_pPlayerCollisionBottom->setAngle({ 0.0f, 0.0f, 0.0f });
            g_pPlayerCollisionSide->setAngle({ 0.0f, 0.0f, 0.0f });
            //方向を右向きにする
            PlayerDirection_Right = true;
        }
        else if (getInput()->isKeyPressed(DIK_LEFTARROW) && g_LeftHit == false)
        {
            //カウンターを動かす
            MTimeCounter++;
            //助走をつける
            if (MTimeCounter <= 12.0f)
            {
                pos.x -= MTimeCounter;
                //歩いているフラグを有効にする
                g_Walking = true;
            }
            else
            {
                pos.x -= PlayerSpeed;
                //走っているフラグを有効にする
                g_Running = true;
                //歩いているフラグを無効にする
                g_Walking = false;
            }
            //プレイヤーの向きを後ろにする
            g_pPlayer->setAngle({ 0.0f, 180.0f, 0.0f });
            g_pPlayerCollisionBottom->setAngle({ 0.0f, 180.0f, 0.0f });
            g_pPlayerCollisionSide->setAngle({ 0.0f, 180.0f, 0.0f });
            //方向を左向きにする
            PlayerDirection_Right = false;
        }
    }

    g_pPlayer->setPos(pos);
    //当たり判定も動かしておく
    if (PlayerDirection_Right == true)
    {
        g_pPlayerCollisionBottom->setPos(pos.x + 31.5f, pos.y + 1.5f);
        g_pPlayerCollisionSide->setPos(pos.x + 54.0f, pos.y + 31.0f);
    }
    else
    {
        g_pPlayerCollisionBottom->setPos(pos.x - 31.5f, pos.y + 1.5f);
        g_pPlayerCollisionSide->setPos(pos.x - 54.0f, pos.y + 31.0f);
    }
}

/*
* 関数名　  ：procPlayMain_PlayerCollisionBottom()
* 処理内容　：プレイヤーの上下の当たり判定処理
*/
void COriginalGameApp::procPlayMain_PlayerCollisionBottom()
{
    XMFLOAT4 pos = g_pPlayer->getPos();
    if (PlayerDirection_Right == true)
    {
        g_pPlayerCollisionBottom->setPos(pos.x + 31.5f, pos.y + 1.5f);
        g_pPlayerCollisionSide->setPos(pos.x + 54.0f, pos.y + 31.0f);
    }
    else
    {
        g_pPlayerCollisionBottom->setPos(pos.x - 31.5f, pos.y + 1.5f);
        g_pPlayerCollisionSide->setPos(pos.x - 54.0f, pos.y + 31.0f);
    }

    //フラグのリセット
    g_Ground = false;
    g_TopHit = false;

    for (int i = 0; i < Ground_Count; ++i)
    {
        if (g_pGround[i] != NULL)
        {
            if (g_pPlayerCollisionBottom->collisionBottom(g_pGround[i]))
            {
                //プレイヤーの接地フラグを有効にする
                g_Ground = true;

                //プレイヤーと当たり判定の画像を上げる
                g_pPlayer->setPos(g_pPlayer->getPos().x, g_pGround[i]->getPos().y + 165.5f);
                g_pPlayerCollisionBottom->setPos(g_pPlayerCollisionBottom->getPos().x, g_pGround[i]->getPos().y + 165.5f);
                //重力をリセットしておく
                PlayerGurabitexi = 0;
                GTimeCounter = 0;
                break;
            }
        }
    }

    //穴の接地判定
    for (int i = 0; i < Hole_Count; ++i)
    {
        if (g_pHole[i] != NULL)
        {
            if (g_pPlayerCollisionBottom->collisionBottom(g_pHole[i]))
            {
                //プレイヤーの接地フラグを有効にする
                g_Ground = true;

                //プレイヤーと当たり判定の画像を上げる
                g_pPlayer->setPos(g_pPlayer->getPos().x, g_pHole[i]->getPos().y + 165.5f);
                g_pPlayerCollisionBottom->setPos(g_pPlayerCollisionBottom->getPos().x, g_pHole[i]->getPos().y + 165.5f);
                //重力をリセットしておく
                PlayerGurabitexi = 0;
                GTimeCounter = 0;
                break;
            }
        }
    }

    //崖の接地判定
    for (int i = 0; i < CliffSide_Count; ++i)
    {
        if (g_pCliffSide[i] != NULL)
        {
            if (g_pPlayerCollisionBottom->collisionBottom(g_pCliffSide[i]))
            {
                //プレイヤーの接地フラグを有効にする
                g_Ground = true;

                //プレイヤーと当たり判定の画像を上げる
                g_pPlayer->setPos(g_pPlayer->getPos().x, g_pCliffSide[i]->getPos().y + 368.0f);
                g_pPlayerCollisionBottom->setPos(g_pPlayerCollisionBottom->getPos().x, g_pCliffSide[i]->getPos().y + 368.0f);
                //重力をリセットしておく
                PlayerGurabitexi = 0;
                GTimeCounter = 0;
                break;
            }
        }
    }
    for (int i = 0; i < CliffCenter_Count; ++i)
    {
        if (g_pCliffCenter[i] != NULL)
        {
            if (g_pPlayerCollisionBottom->collisionBottom(g_pCliffCenter[i]))
            {
                //プレイヤーの接地フラグを有効にする
                g_Ground = true;

                //プレイヤーと当たり判定の画像を上げる
                g_pPlayer->setPos(g_pPlayer->getPos().x, g_pCliffCenter[i]->getPos().y + 368.0f);
                g_pPlayerCollisionBottom->setPos(g_pPlayerCollisionBottom->getPos().x, g_pCliffCenter[i]->getPos().y + 368.0f);
                //重力をリセットしておく
                PlayerGurabitexi = 0;
                GTimeCounter = 0;
                break;
            }
        }
    }

    //丘の当たり判定
    for (int i = 0; i < HillCollision_Count; ++i)
    {
        if (g_pHillCollision[i] != NULL)
        {
            if (g_pPlayerCollisionBottom->collisionBottom(g_pHillCollision[i]) && g_JumpUp == false)
            {
                //プレイヤーの接地フラグを有効にする
                g_Ground = true;

                //プレイヤーと当たり判定の画像を上げる
                g_pPlayer->setPos(g_pPlayer->getPos().x, g_pHillCollision[i]->getPos().y + 118.0f);
                g_pPlayerCollisionBottom->setPos(g_pPlayerCollisionBottom->getPos().x, g_pHillCollision[i]->getPos().y + 118.0f);
                //重力をリセットしておく
                PlayerGurabitexi = 0;
                GTimeCounter = 0;
                break;
            }
        }
    }
    //リフトの当たり判定
    for (int i = 0; i < MoveLift_Count; ++i)
    {
        if (g_pMoveLiftCollision[i] != NULL)
        {
            if (g_pPlayerCollisionBottom->collisionBottom(g_pMoveLiftCollision[i]) && g_JumpUp == false)
            {
                //プレイヤーの接地フラグを有効にする
                g_Ground = true;

                //プレイヤーと当たり判定の画像を上げる
                g_pPlayer->setPos(g_pPlayer->getPos().x, g_pMoveLiftCollision[i]->getPos().y + 118.0f);
                g_pPlayerCollisionBottom->setPos(g_pPlayerCollisionBottom->getPos().x, g_pMoveLiftCollision[i]->getPos().y + 118.0f);
                //重力をリセットしておく
                PlayerGurabitexi = 0;
                GTimeCounter = 0;
                break;
            }
        }
    }
    for (int i = 0; i < FallLift_Count; ++i)
    {
        if (g_pFallLiftCollision[i] != NULL)
        {
            if (g_pPlayerCollisionBottom->collisionBottom(g_pFallLiftCollision[i]) && g_JumpUp == false)
            {
                //プレイヤーの接地フラグを有効にする
                g_Ground = true;
                g_FallLift[i] = true;

                //プレイヤーと当たり判定の画像を上げる
                g_pPlayer->setPos(g_pPlayer->getPos().x, g_pFallLiftCollision[i]->getPos().y + 118.0f);
                g_pPlayerCollisionBottom->setPos(g_pPlayerCollisionBottom->getPos().x, g_pFallLiftCollision[i]->getPos().y + 118.0f);
                //重力をリセットしておく
                PlayerGurabitexi = 0;
                GTimeCounter = 0;
                break;
            }
        }
    }

    //ブロックの当たり判定
    //クリアのみ判定
    if (g_Clear == true)
    {
        //下
        for (int i = 0; i < Block_Count; ++i)
        {
            if (g_pBlock[i] != NULL)
            {
                if (g_pPlayerCollisionBottom->collisionBottom(g_pBlock[i]))
                {
                    //プレイヤーの接地フラグを有効にする
                    g_Ground = true;

                    //プレイヤーと当たり判定の画像を上げる
                    g_pPlayer->setPos(g_pPlayer->getPos().x, g_pBlock[i]->getPos().y + 173.0f);
                    g_pPlayerCollisionBottom->setPos(g_pPlayerCollisionBottom->getPos().x, g_pBlock[i]->getPos().y + 173.0f);
                    //重力をリセットしておく
                    PlayerGurabitexi = 0;
                    GTimeCounter = 0;
                    break;
                }
            }
        }

        //上
        for (int i = 0; i < Block_Count; ++i)
        {
            if (g_pBlock[i] != NULL)
            {
                if (g_pPlayerCollisionBottom->collisionTop(g_pBlock[i]))
                {
                    //プレイヤーの接地フラグを有効にする
                    g_TopHit = true;

                    //プレイヤーと当たり判定の画像を上げる
                    g_pPlayer->setPos(g_pPlayer->getPos().x, g_pBlock[i]->getPos().y - 180.0f);
                    g_pPlayerCollisionBottom->setPos(g_pPlayerCollisionBottom->getPos().x, g_pBlock[i]->getPos().y - 180.0f);
                    //重力をリセットしておく
                    PlayerGurabitexi = 0;
                    GTimeCounter = 0;
                    break;
                }
            }
        }
    }
}

/*
* 関数名　  ：procPlayMain_PlayerCollisionSide()
* 処理内容　：プレイヤーの左右の当たり判定処理
*/
void COriginalGameApp::procPlayMain_PlayerCollisionSide()
{
    XMFLOAT4 pos = g_pPlayer->getPos();
    if (PlayerDirection_Right == true)
    {
        g_pPlayerCollisionBottom->setPos(pos.x + 31.5f, pos.y + 1.5f);
        g_pPlayerCollisionSide->setPos(pos.x + 54.0f, pos.y + 31.0f);
    }
    else
    {
        g_pPlayerCollisionBottom->setPos(pos.x - 31.5f, pos.y + 1.5f);
        g_pPlayerCollisionSide->setPos(pos.x - 54.0f, pos.y + 31.0f);
    }

    //フラグのリセット
    g_RightHit = false;
    g_LeftHit = false;

    //右
    //穴の接地判定
    for (int i = 0; i < Hole_Count; ++i)
    {
        if (g_pHole[i] != NULL)
        {
            if (g_pPlayerCollisionSide->collisionRight(g_pHole[i]))
            {
                //プレイヤーの接地フラグを有効にする
                g_RightHit = true;
                //歩きのフラグを無効にする
                g_Walking = false;

                //プレイヤーと当たり判定の画像を上げる
                g_pPlayer->setPos(g_pHole[i]->getPos().x - 224.0f, g_pPlayer->getPos().y);
                g_pPlayerCollisionSide->setPos(g_pHole[i]->getPos().x - 170.25f, g_pPlayerCollisionSide->getPos().y);
                break;
            }
        }
    }

    //崖の接地判定
    for (int i = 0; i < CliffSide_Count; ++i)
    {
        if (g_pCliffSide[i] != NULL)
        {
            if (g_pPlayerCollisionSide->collisionRight(g_pCliffSide[i]))
            {
                //プレイヤーの接地フラグを有効にする
                g_RightHit = true;
                //歩きのフラグを無効にする
                g_Walking = false;

                //プレイヤーと当たり判定の画像を上げる
                g_pPlayer->setPos(g_pCliffSide[i]->getPos().x - 209.0f, g_pPlayer->getPos().y);
                g_pPlayerCollisionSide->setPos(g_pCliffSide[i]->getPos().x - 155.25f, g_pPlayerCollisionSide->getPos().y);
                break;
            }
        }
    }

    //ブロックの接地判定
    //クリアのみ判定
    if (g_Clear == true)
    {
        for (int i = 0; i < Block_Count; ++i)
        {
            if (g_pBlock[i] != NULL)
            {
                if (g_pPlayerCollisionSide->collisionRight(g_pBlock[i]))
                {
                    //プレイヤーの接地フラグを有効にする
                    g_RightHit = true;
                    //歩きのフラグを無効にする
                    g_Walking = false;

                    //プレイヤーと当たり判定の画像を上げる
                    g_pPlayer->setPos(g_pBlock[i]->getPos().x - 216.5f, g_pPlayer->getPos().y);
                    g_pPlayerCollisionSide->setPos(g_pBlock[i]->getPos().x - 162.5f, g_pPlayerCollisionSide->getPos().y);
                    break;
                }
            }
        }
    }

    //左
    //穴の接地判定
    for (int i = 0; i < Hole_Count; ++i)
    {
        if (g_pHole[i] != NULL)
        {
            if (g_pPlayerCollisionSide->collisionLeft(g_pHole[i]))
            {
                //プレイヤーの接地フラグを有効にする
                g_LeftHit = true;
                //歩きのフラグを無効にする
                g_Walking = false;

                //プレイヤーと当たり判定の画像を上げる
                g_pPlayer->setPos(g_pHole[i]->getPos().x + 224.0f, g_pPlayer->getPos().y);
                g_pPlayerCollisionSide->setPos(g_pHole[i]->getPos().x + 170.25f, g_pPlayerCollisionSide->getPos().y);
                break;
            }
        }
    }

    //崖の接地判定
    for (int i = 0; i < CliffSide_Count; ++i)
    {
        if (g_pCliffSide[i] != NULL)
        {
            if (g_pPlayerCollisionSide->collisionLeft(g_pCliffSide[i]))
            {
                //プレイヤーの接地フラグを有効にする
                g_LeftHit = true;
                //歩きのフラグを無効にする
                g_Walking = false;

                //プレイヤーと当たり判定の画像を上げる
                g_pPlayer->setPos(g_pCliffSide[i]->getPos().x + 209.0f, g_pPlayer->getPos().y);
                g_pPlayerCollisionSide->setPos(g_pCliffSide[i]->getPos().x + 155.25f, g_pPlayerCollisionSide->getPos().y);
                break;
            }
        }
    }

    //ブロックの接地判定
    //クリアのみ判定
    if (g_Clear == true)
    {
        for (int i = 0; i < Block_Count; ++i)
        {
            if (g_pBlock[i] != NULL)
            {
                if (g_pPlayerCollisionSide->collisionLeft(g_pBlock[i]))
                {
                    //プレイヤーの接地フラグを有効にする
                    g_LeftHit = true;
                    //歩きのフラグを無効にする
                    g_Walking = false;

                    //プレイヤーと当たり判定の画像を上げる
                    g_pPlayer->setPos(g_pBlock[i]->getPos().x + 216.5f, g_pPlayer->getPos().y);
                    g_pPlayerCollisionSide->setPos(g_pBlock[i]->getPos().x + 162.5f, g_pPlayerCollisionSide->getPos().y);
                    break;
                }
            }
        }
    }
}

/*
* 関数名　  ：procPlayMain_PlayerGurabitexi()
* 処理内容　：プレイヤーの重力処理
*/
void COriginalGameApp::procPlayMain_PlayerGurabitexi()
{
    XMFLOAT4 pos = g_pPlayer->getPos();

    if (g_Ground == false && g_Climb == false)
    {
        //カウンターを進める
        GTimeCounter++;
        //重力を発生させる
        PlayerGurabitexi = g_Gurabitexi * GTimeCounter;
        //プレイヤーを落とす
        pos.y -= PlayerGurabitexi;
    }
    g_pPlayer->setPos(pos);
    //当たり判定も動かしておく
    if (PlayerDirection_Right == true)
    {
        g_pPlayerCollisionBottom->setPos(pos.x + 31.5f, pos.y + 1.5f);
        g_pPlayerCollisionSide->setPos(pos.x + 54.0f, pos.y + 31.0f);
    }
    else
    {
        g_pPlayerCollisionBottom->setPos(pos.x - 31.5f, pos.y + 1.5f);
        g_pPlayerCollisionSide->setPos(pos.x - 54.0f, pos.y + 31.0f);
    }
}

/*
* 関数名　  ：procPlayMain_PlayerSit()
* 処理内容　：プレイヤーのしゃがみ処理
*/
void COriginalGameApp::procPlayMain_PlayerSit()
{
    if (g_Ground == true && getInput()->isPressedOnce(DIK_SPACE))
    {
        //プレイヤーのしゃがみのフラグを有効にする
        g_Sit = true;
        //移動のフラグを無効にする
        g_Running = false;
        g_Walking = false;
        //ジャンプを通常シフトにする
        JumpDirection = NormalShift;
    }

    if (g_Sit == true)
    {
        //向いている方向によって処理を変える
        //右向きの場合
        if (PlayerDirection_Right == true)
        {
            //右矢印キーで前シフト
            if (getInput()->isPressedOnce(DIK_RIGHTARROW))
            {
                JumpDirection = FrontShift;
            }
            //左矢印キーで振り返る
            if (getInput()->isPressedOnce(DIK_LEFTARROW))
            {
                //プレイヤーの向きを後ろにする
                g_pPlayer->setAngle({ 0.0f, 180.0f, 0.0f });
                //方向を左向きにする
                PlayerDirection_Right = false;
                //ジャンプを通常シフトにしておく
                JumpDirection = NormalShift;
            }
        }

        //左向きの場合
        if (PlayerDirection_Right == false)
        {
            //左矢印キーで前シフト
            if (getInput()->isPressedOnce(DIK_LEFTARROW))
            {
                JumpDirection = FrontShift;
            }
            //右矢印キーで振り返る
            if (getInput()->isPressedOnce(DIK_RIGHTARROW))
            {
                //プレイヤーの向きを前にする
                g_pPlayer->setAngle({ 0.0f, 0.0f, 0.0f });
                //方向を右向きにする
                PlayerDirection_Right = true;
                //ジャンプを通常シフトにしておく
                JumpDirection = NormalShift;
            }
        }

        //上矢印キーで上シフト
        if (getInput()->isPressedOnce(DIK_UPARROW))
        {
            JumpDirection = UpShift;
        }

        //下矢印が押されたら解除
        if (getInput()->isPressedOnce(DIK_DOWNARROW))
        {
            g_Sit = false;
        }
    }
}

/*
* 関数名　  ：procPlayMain_PlayerJump()
* 処理内容　：プレイヤーのジャンプ処理
*/
void COriginalGameApp::procPlayMain_PlayerJump()
{
    XMFLOAT4 pos = g_pPlayer->getPos();

    if (g_Sit == true && getInput()->isKeyReleased(DIK_SPACE) && g_Ground == true)
    {
        //プレイヤーのジャンプのフラグを有効にする
        g_Jump = true;
        //プレイヤーのしゃがみのフラグを無効にする
        g_Sit = false;
        //ジャンプの総移動量をリセットする
        PlayerJumpMove = 0.0f;
        //カウンターをリセットする
        JTimeCounter = 0;
    }

    //1フレームごとの移動量を代入する変数
    float MoveUp = 0.0f;

    //シフトによって飛ぶ方向を分ける
    if (g_Jump == true)
    {
        //通常シフト
        if (JumpDirection == NormalShift)
        {
            //PlayerJumpPowerを超えるまで上昇する
            if (PlayerJumpMove < PlayerJumpPower)
            {
                //接地フラグを無効にする
                g_Ground = false;
                //上昇フラグを有効にする
                g_JumpUp = true;

                //カウンターを進める
                JTimeCounter++;
                if (JTimeCounter <= 8.0f)
                {
                    //移動量を反映させる
                    MoveUp += 28.0f - JTimeCounter;
                    pos.y += MoveUp;
                }

                else
                {
                    //移動量を反映させる
                    MoveUp += 20.0f;
                    pos.y += MoveUp;
                }
            }

            //超えたら上昇フラグを無効にする
            else
            {
                g_JumpUp = false;
            }

            //地面に落ちるまで横移動させる
            if (g_Ground == false && g_Jump == true)
            {
                //向いている方向によってx軸の方向を変える
                if (PlayerDirection_Right == true && g_RightHit == false)
                {
                    pos.x += 17.0f;
                }
                else if (PlayerDirection_Right != true && g_LeftHit == false)
                {
                    pos.x -= 17.0f;
                }
            }

            //着地するとフラグを無効にする
            else
            {
                g_Jump = false;
            }

            //総移動量に加算しておく
            PlayerJumpMove += MoveUp;
            g_pPlayer->setPos(pos);
        }

        //上シフト
        if (JumpDirection == UpShift)
        {
            //PlayerJumpPowerを超えるまで上昇する
            if (PlayerJumpMove < PlayerJumpPower)
            {
                //プレイヤーのジャンプ力の上限を増やす
                PlayerJumpPower = 400;

                //接地フラグを無効にする
                g_Ground = false;
                //上昇フラグを有効にする
                g_JumpUp = true;

                //カウンターを進める
                JTimeCounter++;
                if (JTimeCounter <= 7.0f)
                {
                    //移動量を反映させる
                    MoveUp += 40.0f - JTimeCounter;
                    pos.y += MoveUp;
                }

                else
                {
                    //移動量を反映させる
                    MoveUp += 20.0f;
                    pos.y += MoveUp;
                }
            }

            //超えたら上昇フラグを無効にする
            else
            {
                g_JumpUp = false;
            }

            //地面に落ちるまで横移動させる
            if (g_Ground == false && g_Jump == true)
            {
                //向いている方向によってx軸の方向を変える
                if (PlayerDirection_Right == true && g_RightHit == false)
                {
                    pos.x += 10.0f;
                }
                else if (PlayerDirection_Right != true && g_LeftHit == false)
                {
                    pos.x -= 10.0f;
                }
            }

            //着地するとフラグを無効にする
            else
            {
                g_Jump = false;
                //ジャンプ力を戻しておく
                PlayerJumpPower = 175;
            }

            //総移動量に加算しておく
            PlayerJumpMove += MoveUp;
            g_pPlayer->setPos(pos);
        }

        //前シフト
        if (JumpDirection == FrontShift)
        {
            //PlayerJumpPowerを超えるまで上昇する
            if (PlayerJumpMove < PlayerJumpPower)
            {
                //プレイヤーのジャンプ力の上限を減らす
                PlayerJumpPower = 150;

                //接地フラグを無効にする
                g_Ground = false;
                //上昇フラグを有効にする
                g_JumpUp = true;

                //カウンターを進める
                JTimeCounter++;
                if (JTimeCounter <= 6.0f)
                {
                    //移動量を反映させる
                    MoveUp += 16.0f - JTimeCounter;
                    pos.y += MoveUp;
                }

                else
                {
                    //移動量を反映させる
                    MoveUp += 10.0f;
                    pos.y += MoveUp;
                }
            }

            //超えたら上昇フラグを無効にする
            else
            {
                g_JumpUp = false;
            }

            //地面に落ちるまで横移動させる
            if (g_Ground == false && g_Jump == true)
            {
                if (PlayerDirection_Right == true && g_RightHit == false)
                {
                    pos.x += 25.0f;
                }
                else if (PlayerDirection_Right != true && g_LeftHit == false)
                {
                    pos.x -= 25.0f;
                }
            }

            //着地するとフラグを無効にする
            else
            {
                g_Jump = false;
                //ジャンプ力を戻しておく
                PlayerJumpPower = 175;
            }

            //総移動量に加算しておく
            PlayerJumpMove += MoveUp;
            g_pPlayer->setPos(pos);
        }
    }

    //当たり判定も動かしておく
    if (PlayerDirection_Right == true)
    {
        g_pPlayerCollisionBottom->setPos(pos.x + 31.5f, pos.y + 1.5f);
        g_pPlayerCollisionSide->setPos(pos.x + 54.0f, pos.y + 31.0f);
    }
    else
    {
        g_pPlayerCollisionBottom->setPos(pos.x - 31.5f, pos.y + 1.5f);
        g_pPlayerCollisionSide->setPos(pos.x - 54.0f, pos.y + 31.0f);
    }
}

/*
* 関数名　  ：procPlayMain_PlayerClimb()
* 処理内容　：プレイ画面の壁登りの処理
*/
void COriginalGameApp::procPlayMain_PlayerClimb()
{
    XMFLOAT4 pos = g_pPlayer->getPos();

    //1フレームごとの移動量を代入する変数
    float MoveClimb = 0.0f;

    //向いている方向によって処理を切り替える
    //右
    if (PlayerDirection_Right == true)
    {
        if (g_RightHit == true && g_Ground == true && g_Running == true)
        {
            //壁を登るフラグを有効にする
            g_Climb = true;
            //登った壁の総移動量をリセットする
            PlayerClimbMove = 0.0f;
        }

        //PlayerClimbPowerを超えるまで上昇する
        if (g_Climb == true && PlayerClimbMove < PlayerClimbPower && getInput()->isKeyPressed(DIK_RIGHTARROW))
        {
            //移動量を反映させる
            MoveClimb += 10.0f;
            pos.y += MoveClimb;
            //接地フラグを無効にする
            g_Ground = false;

            //プレイヤーの向きを上にする
            g_pPlayer->setAngle({ 0.0f, 0.0f, 90.0f });
            g_pPlayerCollisionBottom->setAngle({ 0.0f, 0.0f, 90.0f });
            g_pPlayerCollisionSide->setAngle({ 0.0f, 0.0f, 90.0f });
            //プレイヤーの位置を調整する
            pos.x += 45.0f;
            g_pPlayerCollisionBottom->setPos(pos.x - 2.0f, pos.y + 32.0f);
            g_pPlayerCollisionSide->setPos(pos.x - 30.0f, pos.y + 53.0f);

            //逆向きまたは登りきったらキャンセル
            if (PlayerDirection_Right == false || g_RightHit == false)
            {
                //フラグを無効にする
                g_Climb = false;
            }
        }

        else
        {
            //矢印キーを離してもフラグを無効にする
            g_Climb = false;

            //プレイヤーの向きを元に戻す
            g_pPlayer->setAngle({ 0.0f, 0.0f, 0.0f });
            g_pPlayerCollisionBottom->setAngle({ 0.0f, 0.0f, 0.0f });
            g_pPlayerCollisionSide->setAngle({ 0.0f, 0.0f, 0.0f });
        }

        //総移動量に加算しておく
        PlayerClimbMove += MoveClimb;

        g_pPlayer->setPos(pos);
    }

    //左
    if (PlayerDirection_Right != true)
    {
        if (g_LeftHit == true && g_Ground == true && g_Running == true)
        {
            //壁を登るフラグを有効にする
            g_Climb = true;
            //登った壁の総移動量をリセットする
            PlayerClimbMove = 0.0f;
        }

        //PlayerClimbPowerを超えるまで上昇する
        if (g_Climb == true && PlayerClimbMove < PlayerClimbPower && getInput()->isKeyPressed(DIK_LEFTARROW))
        {
            //移動量を反映させる
            MoveClimb += 10.0f;
            pos.y += MoveClimb;
            //接地フラグを無効にする
            g_Ground = false;

            //プレイヤーの向きを上にする
            g_pPlayer->setAngle({ 0.0f, 180.0f, -90.0f });
            g_pPlayerCollisionBottom->setAngle({ 0.0f, 180.0f, -90.0f });
            g_pPlayerCollisionSide->setAngle({ 0.0f, 180.0f, -90.0f });
            //プレイヤーの位置を調整する
            pos.x -= 45.0f;
            g_pPlayerCollisionBottom->setPos(pos.x + 2.0f, pos.y + 32.0f);
            g_pPlayerCollisionSide->setPos(pos.x + 30.0f, pos.y + 53.0f);

            //逆向きまたは登りきったらキャンセル
            if (PlayerDirection_Right != false || g_LeftHit == false)
            {
                //フラグを無効にする
                g_Climb = false;
            }
        }

        else
        {
            //矢印キーを離してもフラグを無効にする
            g_Climb = false;

            //プレイヤーの向きを元に戻す
            g_pPlayer->setAngle({ 0.0f, 180.0f, 0.0f });
            g_pPlayerCollisionBottom->setAngle({ 0.0f, 180.0f, 0.0f });
            g_pPlayerCollisionSide->setAngle({ 0.0f, 180.0f, 0.0f });
        }

        //総移動量に加算しておく
        PlayerClimbMove += MoveClimb;

        g_pPlayer->setPos(pos);
    }
}

/*
* 関数名　  ：procPlayMain_MoveScroll()
* 処理内容　：プレイ画面のスクロール処理
*/
void COriginalGameApp::procPlayMain_MoveScroll()
{
    CameraPos = m_pCamera->getPos();
    XMFLOAT4 pos = g_pPlayer->getPos();

    if (pos.x <= -556.0f)
    {
        CameraPos.x = 0.0f;
    }
    else if (pos.x <= End[Stage] - 1562.0f)
    {
        CameraPos.x = pos.x + 550.0f;
    }

    //クリア時、カメラをリセットしておく
    if (pos.x >= End[Stage] || g_Miss == true)
    {
        CameraPos.x = 0.0f;
    }

    m_pCamera->setPos(CameraPos);

    //UIも移動させる
    m_pCamera->update();
    if (g_pNiboshiUI != NULL)
    {
        g_pNiboshiUI->setPos(CameraPos.x - 880.0f, g_pNiboshiUI->getPos().y);
    }
    if (g_pKatuobushiUI != NULL)
    {
        g_pKatuobushiUI->setPos(CameraPos.x - 880.0f, g_pKatuobushiUI->getPos().y);
    }
    if (g_pLifeUI != NULL)
    {
        g_pLifeUI->setPos(CameraPos.x - 880.0f, g_pLifeUI->getPos().y);
    }
    for (int i = 0; i < 6; ++i)
    {
        if (g_pNumber[i] != NULL)
        {
            g_pNumber[i]->setPos(g_pNiboshiUI->getPos().x + 115.0f + (60.0f * (i % 2)), g_pNiboshiUI->getPos().y - 100.0f * (i / 2));
        }
    }

    //左端の処理
    if (pos.x <= -818.0f)
    {
        //押し返す
        g_pPlayer->setPos(-818.0f, g_pPlayer->getPos().y);
    }

    //クリア後、ステージ3に行けないようにする
    if (Stage == 2 && g_Clear == true && pos.x >= 27780.0f)
    {
        //押し返す
        g_pPlayer->setPos(27780.0f, g_pPlayer->getPos().y);
    }
}

/*
* 関数名　  ：procPlayMina_MissCheck()
* 処理内容　：プレイ画面のミスのチェック
*/
void COriginalGameApp::procPlayMina_MissCheck()
{
    XMFLOAT4 pos = g_pPlayer->getPos();
    XMFLOAT3 CameraPos = m_pCamera->getPos();
    //画面外に落下するとミス
    if (pos.y <= -614.0f)
    {
        g_Miss = true;
    }

    //トゲに当たるとミス
    for (int i = 0; i < Needl_Count; ++i)
    {
        if (g_pNeedl[i] != NULL)
        {
            if (g_pPlayerCollisionBottom->collision(g_pNeedl[i]) || g_pPlayerCollisionBottom->collision(g_pNeedl[i]))
            {
                g_Miss = true;
            }
        }
    }

    if (g_Miss == true)
    {
        //各フラグのリセット
        g_Sit = false;
        g_Running = false;
        g_Walking = false;
        g_Jump = false;

        PlayerMAnimationCounter++;
        if (PlayerMAnimationCounter % 2 == 0)
        {
            pos.y += 10.0f;
        }
        if (PlayerMAnimationCounter == 100)
        {
            //カメラの位置をリセットする
            CameraPos.x = 0.0f;
        }
    }

    g_pPlayer->setPos(pos);
    m_pCamera->setPos(CameraPos);
}

/*
* 関数名　  ：procPlayMain_MoveLift()
* 処理内容　：プレイ画面の動くリフトの処理
*/
void COriginalGameApp::procPlayMain_MoveLift()
{
    //一定量動くと向きを切り替える
    for (int i = 0; i < MoveLift_Count; ++i)
    {
        //右->左
        if (g_MoveLiftDirection[i] == 0 && MoveLiftPower[i] < MoveLiftMove[i])
        {
            g_MoveLiftDirection[i] = 1;
        }
        //左->右
        if (g_MoveLiftDirection[i] == 1 && MoveLiftMove[i] < 0.001f)
        {
            g_MoveLiftDirection[i] = 0;
        }
        //上->下
        if (g_MoveLiftDirection[i] == 2 && MoveLiftPower[i] < MoveLiftMove[i])
        {
            g_MoveLiftDirection[i] = 3;
        }
        //下->上
        if (g_MoveLiftDirection[i] == 3 && MoveLiftMove[i] < 0.001f)
        {
            g_MoveLiftDirection[i] = 2;
        }

        //移動
        //右->左
        if (g_MoveLiftDirection[i] == 0)
        {
            g_pMoveLift[i]->setPos(g_pMoveLift[i]->getPos().x + MoveLiftSpeed[i], g_pMoveLift[i]->getPos().y);
            //総移動量を加算しておく
            MoveLiftMove[i] += MoveLiftSpeed[i];

            //プレイヤーが乗っていた場合、同時に動かす
            if (g_pPlayerCollisionBottom->collisionBottom(g_pMoveLiftCollision[i]))
            {
                g_pPlayer->setPos(g_pPlayer->getPos().x + MoveLiftSpeed[i], g_pPlayer->getPos().y);
            }
        }
        //左->右
        if (g_MoveLiftDirection[i] == 1)
        {
            g_pMoveLift[i]->setPos(g_pMoveLift[i]->getPos().x - MoveLiftSpeed[i], g_pMoveLift[i]->getPos().y);
            //総移動量を減算しておく
            MoveLiftMove[i] -= MoveLiftSpeed[i];

            //プレイヤーが乗っていた場合、同時に動かす
            if (g_pPlayerCollisionBottom->collisionBottom(g_pMoveLiftCollision[i]))
            {
                g_pPlayer->setPos(g_pPlayer->getPos().x - MoveLiftSpeed[i], g_pPlayer->getPos().y);
            }
        }
        //上->下
        if (g_MoveLiftDirection[i] == 2)
        {
            g_pMoveLift[i]->setPos(g_pMoveLift[i]->getPos().x, g_pMoveLift[i]->getPos().y + MoveLiftSpeed[i]);
            //総移動量を加算しておく
            MoveLiftMove[i] += MoveLiftSpeed[i];

            //プレイヤーが乗っていた場合、同時に動かす
            if (g_pPlayerCollisionBottom->collisionBottom(g_pMoveLiftCollision[i]))
            {
                g_pPlayer->setPos(g_pPlayer->getPos().x, g_pPlayer->getPos().y + MoveLiftSpeed[i]);
            }
        }
        //下->上
        if (g_MoveLiftDirection[i] == 3)
        {
            g_pMoveLift[i]->setPos(g_pMoveLift[i]->getPos().x, g_pMoveLift[i]->getPos().y - MoveLiftSpeed[i]);
            //総移動量を減算しておく
            MoveLiftMove[i] -= MoveLiftSpeed[i];

            //プレイヤーが乗っていた場合、同時に動かす
            if (g_pPlayerCollisionBottom->collisionBottom(g_pMoveLiftCollision[i]))
            {
                g_pPlayer->setPos(g_pPlayer->getPos().x, g_pPlayer->getPos().y - MoveLiftSpeed[i]);
            }
        }

        //当たり判定も動かしておく
        g_pMoveLiftCollision[i]->setPos(g_pMoveLift[i]->getPos().x, g_pMoveLift[i]->getPos().y + 5.0f);
    }

    //当たり判定も動かしておく
    if (PlayerDirection_Right == true)
    {
        g_pPlayerCollisionBottom->setPos(g_pPlayer->getPos().x + 31.5f, g_pPlayer->getPos().y + 1.5f);
        g_pPlayerCollisionSide->setPos(g_pPlayer->getPos().x + 54.0f, g_pPlayer->getPos().y + 31.0f);
    }
    else
    {
        g_pPlayerCollisionBottom->setPos(g_pPlayer->getPos().x - 31.5f, g_pPlayer->getPos().y + 1.5f);
        g_pPlayerCollisionSide->setPos(g_pPlayer->getPos().x - 54.0f, g_pPlayer->getPos().y + 31.0f);
    }
}

/*
* 関数名　  ：procPlayMain_FallLift()
* 処理内容　：プレイ画面の落ちるリフトの処理
*/
void COriginalGameApp::procPlayMain_FallLift()
{
    for (int i = 0; i < FallLift_Count; ++i)
    {
        if (g_pFallLift[i] != NULL)
        {
            //フラグが有効になると落ちる
            if (g_FallLift[i] == true)
            {
                g_pFallLift[i]->setPos(g_pFallLift[i]->getPos().x, g_pFallLift[i]->getPos().y - FallLiftSpeed);

                //プレイヤーが乗っていた場合、同時に動かす
                if (g_pPlayerCollisionBottom->collisionBottom(g_pFallLiftCollision[i]))
                {
                    g_pPlayer->setPos(g_pPlayer->getPos().x, g_pPlayer->getPos().y - FallLiftSpeed);
                }
            }

            //画面外まで落ちるとフラグを無効にする
            if (g_pFallLift[i]->getPos().y <= -600.0f)
            {
                g_FallLift[i] = false;

                //50フレーム後に戻ってくる
                FallLiftCounter[i]++;
                if (FallLiftCounter[i] % 50 == 0)
                {
                    //戻るフラグを有効にする
                    g_FallLiftRivers[i] = true;

                    //カウンターをリセットしておく
                    FallLiftCounter[i] = 0;
                }
            }

            if (g_FallLiftRivers[i] == true && g_FallLift[i] == false)
            {
                //だんだん上げていく
                g_pFallLift[i]->setPos(g_pFallLift[i]->getPos().x, g_pFallLift[i]->getPos().y + FallLiftSpeed);

                //初期座標を超えたら止まる
                if (g_pFallLift[i]->getPos().y >= FallLift2_Pos[i].y)
                {
                    g_FallLiftRivers[i] = false;
                }
            }

            //当たり判定も動かしておく
            g_pFallLiftCollision[i]->setPos(g_pFallLift[i]->getPos().x, g_pFallLift[i]->getPos().y + 5.0f);
        }
    }

    //当たり判定も動かしておく
    if (PlayerDirection_Right == true)
    {
        g_pPlayerCollisionBottom->setPos(g_pPlayer->getPos().x + 31.5f, g_pPlayer->getPos().y + 1.5f);
        g_pPlayerCollisionSide->setPos(g_pPlayer->getPos().x + 54.0f, g_pPlayer->getPos().y + 31.0f);
    }
    else
    {
        g_pPlayerCollisionBottom->setPos(g_pPlayer->getPos().x - 31.5f, g_pPlayer->getPos().y + 1.5f);
        g_pPlayerCollisionSide->setPos(g_pPlayer->getPos().x - 54.0f, g_pPlayer->getPos().y + 31.0f);
    }
}

/*
* 関数名　  ：procPlayMain_NeedlMove()
* 処理内容　：プレイ画面の動くトゲの処理
*/
void COriginalGameApp::procPlayMain_NeedlMove()
{
    for (int i = 0; i < Needl_Count; ++i)
    {
        //下向きは下から動かす
        if (g_NeedlDirection[i] == 2)
        {
            NeedlMove[i] = NeedlPower[i];
            g_NeedlMoveUp[i] = false;
            g_NeedlDirection[i] = 1;
        }
        //周期をずらす
        if (g_NeedlDirection[i] == 3)
        {
            NeedlMove[i] = NeedlPower[i];
            g_NeedlMoveUp[i] = false;
            g_NeedlDirection[i] = 4;
        }

        if (g_pNeedl[i] != NULL && g_NeedlMove[i] == 1)
        {
            //一定量動くと向きを切り替える
            //上->下
            if (g_NeedlMoveUp[i] == true && NeedlPower[i] < NeedlMove[i])
            {
                g_NeedlMoveUp[i] = false;
            }
            //下->上
            if (g_NeedlMoveUp[i] == false && NeedlMove[i] < 0.001f)
            {
                g_NeedlMoveUp[i] = true;
            }

            //移動
            if (g_NeedlMoveUp[i] == true)
            {
                //方向によって動くスピードを変える
                if (g_NeedlDirection[i] == 1)
                {
                    g_pNeedl[i]->setPos(g_pNeedl[i]->getPos().x, g_pNeedl[i]->getPos().y + NeedlSpeed[1]);
                    //総移動量に加算しておく
                    NeedlMove[i] += NeedlSpeed[1];
                }
                else
                {
                    g_pNeedl[i]->setPos(g_pNeedl[i]->getPos().x, g_pNeedl[i]->getPos().y + NeedlSpeed[0]);
                    //総移動量に加算しておく
                    NeedlMove[i] += NeedlSpeed[0];
                }
            }
            if (g_NeedlMoveUp[i] == false)
            {
                //方向によって動くスピードを変える
                if (g_NeedlDirection[i] == 1 || g_NeedlDirection[i] == 4)
                {
                    g_pNeedl[i]->setPos(g_pNeedl[i]->getPos().x, g_pNeedl[i]->getPos().y - NeedlSpeed[0]);
                    //総移動量に減算しておく
                    NeedlMove[i] -= NeedlSpeed[0];
                }
                else
                {
                    g_pNeedl[i]->setPos(g_pNeedl[i]->getPos().x, g_pNeedl[i]->getPos().y - NeedlSpeed[1]);
                    //総移動量に減算しておく
                    NeedlMove[i] -= NeedlSpeed[1];
                }
            }
        }
    }
}

/*
* 関数名　  ：procPlayMain_PlayerAnimation()
* 処理内容　：プレイヤーのアニメーション処理
*/
void COriginalGameApp::procPlayMain_PlayerAnimation()
{
    if (g_Clear == false)
    {
        if (g_Walking == true)
        {
            if (g_PlayerWAnimation == true)
            {
                //アニメーションの範囲を決める
                g_pPlayer->setAnimationRange(14, 16);
                PlayerWAnimationCounter++;

                //5フレームに1回、アニメーションを切り替える
                if (PlayerWAnimationCounter % 5 == 0)
                {
                    g_pPlayer->stepAnimation();
                    PlayerWAnimationCounter = 0;
                    //何枚目のアニメーションなのかをカウントする
                    PlayerWAnimation++;
                }
                //4枚目で停止
                if (PlayerWAnimation == 2)
                {
                    g_pPlayer->setAnimation(16);
                    //フラグを無効にする
                    g_PlayerWAnimation = false;
                }
            }
        }
        //走り
        else if (g_Running == true)
        {
            //アニメーションの範囲を決める
            g_pPlayer->setAnimationRange(1, 6);
            PlayerRAnimationCounter++;

            //5フレームに1回、アニメーションを切り替える
            if (PlayerRAnimationCounter % 5 == 0)
            {
                g_pPlayer->stepAnimation();
                PlayerRAnimationCounter = 0;
            }
        }

        //しゃがみ
        else if (g_Sit == true)
        {
            g_pPlayer->setAnimation(7);
        }

        //ジャンプ
        else if (g_Jump == true)
        {
            //最高点までアニメーション
            if (g_PlayerJAnimation == true && PlayerJumpMove < PlayerJumpPower)
            {
                //アニメーションの範囲を決める
                g_pPlayer->setAnimationRange(8, 11);
                PlayerJAnimationCounter++;

                //3フレームに1回、アニメーションを切り替える
                if (PlayerJAnimationCounter % 3 == 0)
                {
                    g_pPlayer->stepAnimation();
                    PlayerJAnimationCounter = 0;
                    //何枚目のアニメーションなのかをカウントする
                    PlayerJAnimation++;
                }
                //4枚目で停止
                if (PlayerJAnimation == 3)
                {
                    g_pPlayer->setAnimation(11);
                    //フラグを無効にする
                    g_PlayerJAnimation = false;
                }
            }
            else if (g_Ground == false)
            {
                //最高点に行くと着地まで落下アニメーション
                g_pPlayer->setAnimation(12);
                PlayerJAnimation = 0;
            }
            else
            {
                //着地時に着地するアニメーション
                g_pPlayer->setAnimation(13);
                //カウンターをリセットしておく
                g_PlayerJAnimation = true;
            }
        }

        //ミス
        else if (g_Miss == true)
        {
            g_pPlayer->setAnimationRange(0, 17);
            g_pPlayer->setAnimation(17);
        }

        else
        {
            //止まると画像を戻す
            g_pPlayer->setAnimationRange(0, 13);
            g_pPlayer->setAnimation(0);

            //カウンターをリセットしておく
            g_PlayerWAnimation = true;

            //値をリセットしておく
            PlayerRAnimationCounter = 0;
            PlayerWAnimationCounter = 0;
            PlayerWAnimation = 0;
            PlayerJAnimationCounter = 0;
            PlayerJAnimation = 0;
        }
    }

    //クリア後
    else
    {
        if (g_Walking == true)
        {
            if (g_PlayerWAnimation == true)
            {
                //アニメーションの範囲を決める
                g_pPlayer->setAnimationRange(32, 34);
                PlayerWAnimationCounter++;

                //5フレームに1回、アニメーションを切り替える
                if (PlayerWAnimationCounter % 5 == 0)
                {
                    g_pPlayer->stepAnimation();
                    PlayerWAnimationCounter = 0;
                    //何枚目のアニメーションなのかをカウントする
                    PlayerWAnimation++;
                }
                //4枚目で停止
                if (PlayerWAnimation == 2)
                {
                    g_pPlayer->setAnimation(31);
                    //フラグを無効にする
                    g_PlayerWAnimation = false;
                }
            }
        }
        //走り
        else if (g_Running == true)
        {
            //アニメーションの範囲を決める
            g_pPlayer->setAnimationRange(19, 24);
            PlayerRAnimationCounter++;

            //4フレームに1回、アニメーションを切り替える
            if (PlayerRAnimationCounter % 4 == 0)
            {
                g_pPlayer->stepAnimation();
                PlayerRAnimationCounter = 0;
            }
        }

        //しゃがみ
        else if (g_Sit == true)
        {
            g_pPlayer->setAnimation(25);
        }

        //ジャンプ
        else if (g_Jump == true)
        {
            //最高点までアニメーション
            if (g_PlayerJAnimation == true && PlayerJumpMove < PlayerJumpPower)
            {
                //アニメーションの範囲を決める
                g_pPlayer->setAnimationRange(26, 29);
                PlayerJAnimationCounter++;

                //3フレームに1回、アニメーションを切り替える
                if (PlayerJAnimationCounter % 3 == 0)
                {
                    g_pPlayer->stepAnimation();
                    PlayerJAnimationCounter = 0;
                    //何枚目のアニメーションなのかをカウントする
                    PlayerJAnimation++;
                }
                //4枚目で停止
                if (PlayerJAnimation == 3)
                {
                    g_pPlayer->setAnimation(29);
                    //フラグを無効にする
                    g_PlayerJAnimation = false;
                }
            }
            else if (g_Ground == false)
            {
                //最高点に行くと着地まで落下アニメーション
                g_pPlayer->setAnimation(30);
                PlayerJAnimation = 0;
            }
            else
            {
                //着地時に着地するアニメーション
                g_pPlayer->setAnimation(31);
                //カウンターをリセットしておく
                g_PlayerJAnimation = true;
            }
        }

        //ミス
        else if (g_Miss == true)
        {
            g_pPlayer->setAnimationRange(18, 35);
            g_pPlayer->setAnimation(35);
        }

        else
        {
            //止まると画像を戻す
            g_pPlayer->setAnimationRange(18, 31);
            g_pPlayer->setAnimation(18);

            //カウンターをリセットしておく
            g_PlayerWAnimation = true;

            //値をリセットしておく
            PlayerRAnimationCounter = 0;
            PlayerWAnimationCounter = 0;
            PlayerWAnimation = 0;
            PlayerJAnimationCounter = 0;
            PlayerJAnimation = 0;
        }
    }
}

/*
* 関数名　  ：procPlayMain_GetNiboshi()
* 処理内容　：にぼしの獲得処理
*/
void COriginalGameApp::procPlayMain_GetNiboshi()
{
    for (int i = 0; i < Niboshi_Count; ++i)
    {
        //にぼしの画像が描画されている時のみ判定チェック
        if (g_pNiboshi[i] != NULL)
        {
            if (g_pPlayerCollisionBottom->collision(g_pNiboshi[i]) || g_pPlayerCollisionSide->collision(g_pNiboshi[i]))
            {
                //画像を破棄する
                disposeSprite(g_pNiboshi[i]);
                g_pNiboshi[i] = NULL;

                //カウンターで獲得数を数えておく
                NiboshiCounter++;
            }
        }
    }

    //にぼしを100個集めると残機が1増える
    if (NiboshiCounter == 100)
    {
        //残機を増やす
        Life++;
        //カウンターをリセットしておく
        NiboshiCounter = 0;
    }
}

/*
* 関数名　  ：procPlayMain_GetKatuobushi()
* 処理内容　：かつおぶしの獲得処理
*/
void COriginalGameApp::procPlayMain_GetKatuobushi()
{
    for (int i = 0; i < Katuobushi_Count; ++i)
    {
        //かつおぶしの画像が描画されている時のみ判定チェック
        if (g_pKatuobushi[i] != NULL)
        {
            if (g_pPlayerCollisionBottom->collision(g_pKatuobushi[i]) || g_pPlayerCollisionSide->collision(g_pKatuobushi[i]))
            {
                //画像を破棄する
                disposeSprite(g_pKatuobushi[i]);
                g_pKatuobushi[i] = NULL;

                //カウンターで獲得数を数えておく
                KatuobushiCounter++;
                //獲得判定を保存しておく
                KatuobushiFlag[Stage - 1][i] = true;
            }
        }
    }
}

/*
* 関数名　  ：procPlayMain_CountUI()
* 処理内容　：各アイテムの獲得時のUI処理
*/
void COriginalGameApp::procPlayMain_CountUI()
{
    //にぼしのカウント
    g_pNumber[0]->setAnimation(NiboshiCounter / 10);
    g_pNumber[1]->setAnimation(NiboshiCounter - ((NiboshiCounter / 10) * 10));

    //かつおぶしのカウント
    g_pNumber[2]->setAnimation(KatuobushiCounter / 10);
    g_pNumber[3]->setAnimation(KatuobushiCounter - ((KatuobushiCounter / 10) * 10));

    //残機のカウント
    g_pNumber[4]->setAnimation(Life / 10);
    g_pNumber[5]->setAnimation(Life - ((Life / 10) * 10));
}

/*
* 関数名　  ：procPlayMain_SpeechDetection()
* 処理内容　：会話のフラグを検知する処理
*/
void COriginalGameApp::procPlayMain_SpeechDetection()
{
    XMFLOAT4 pos = g_pPlayer->getPos();

    if (g_Speech == false)
    {
        //ジャンプ前のフラグ
        if (pos.x >= 1200.0f && Tuto == 0)
        {
            //設置場所を変更
            SpeechBalloon_Pos.x = m_pCamera->getPos().x;
            //フラグを有効にする
            g_Speech = true;
            //チュートリアルの進行をカウントする。
            Tuto++;
        }

        //前シフトジャンプのフラグ
        if (pos.x >= 2500.0f && Tuto == 1)
        {
            //セリフの数を調整
            DialogueCount = 12;
            //設置場所を変更
            SpeechBalloon_Pos.x = m_pCamera->getPos().x;
            //フラグを有効にする
            g_Speech = true;
            //チュートリアルの進行をカウントする。
            Tuto++;
        }

        //上シフトジャンプのフラグ
        if (pos.x >= 4100.0f && Tuto == 2)
        {
            //セリフの数を調整
            DialogueCount = 17;
            //設置場所を変更
            SpeechBalloon_Pos.x = m_pCamera->getPos().x;
            //フラグを有効にする
            g_Speech = true;
            //チュートリアルの進行をカウントする。
            Tuto++;
        }

        //壁登りのフラグ
        if (pos.x >= 5700.0f && Tuto == 3)
        {
            //セリフの数を調整
            DialogueCount = 20;
            //設置場所を変更
            SpeechBalloon_Pos.x = m_pCamera->getPos().x;
            //フラグを有効にする
            g_Speech = true;
            //チュートリアルの進行をカウントする。
            Tuto++;
        }

        //チュートリアル完了のフラグ
        if (pos.x >= 7300.0f && Tuto == 4)
        {
            //セリフの数を調整
            DialogueCount = 23;
            //設置場所を変更
            SpeechBalloon_Pos.x = m_pCamera->getPos().x;
            //フラグを有効にする
            g_Speech = true;
            //チュートリアルの進行をカウントする。
            Tuto++;
        }
    }
}

/*
* 関数名　  ：procPlayMain_SpeechBalloonAnimation()
* 処理内容　：吹き出しのアニメーション処理
*/
void COriginalGameApp::procPlayMain_SpeechBalloonAnimation()
{
    //動きを止める
    g_Jump = false;
    g_Walking = false;
    g_Running = false;

    //吹き出し、にに、ににの感情マーク、名前、吹き出しのUIの画像が破棄された場合は、再度作成
    if (g_pSpeechBalloon == NULL)
    {
        g_pSpeechBalloon = createSprite(Tex_SpeechBalloon, SpeechBalloon_Size_X, SpeechBalloon_Size_Y);
        g_pSpeechBalloon->setPos(SpeechBalloon_Pos);
    }
    if (g_pNini == NULL)
    {
        g_pNini = createSprite(Tex_Nini, Nini_Size_X, Nini_Size_Y);
        g_pNini->setPos(0.0f, -WINDOW_HEIGHT);
    }
    if (g_pNiniEmotion == NULL)
    {
        g_pNiniEmotion = createSprite(Tex_NiniEmotion, NiniEmotion_Size_X, NiniEmotion_Size_Y);
        g_pNiniEmotion->setPos(0.0f, -WINDOW_HEIGHT);
    }
    if (g_pName == NULL)
    {
        g_pName = createSprite(Tex_Name, Name_Size_X, Name_Size_Y);
        g_pName->setPos(0.0f, -WINDOW_HEIGHT);
    }
    if (g_pSpeechBalloonUI == NULL)
    {
        g_pSpeechBalloonUI = createSprite(Tex_SpeechBalloonUI, SpeechBalloonUI_Size_X, SpeechBalloonUI_Size_Y);
        g_pSpeechBalloonUI->setPos(0.0f, -WINDOW_HEIGHT);
    }

    //ににの感情マークの画像が作成された時のみ描画
    if (g_pNiniEmotion != NULL)
    {
        renderSprite(g_pNiniEmotion);
    }
    //ににの画像が作成された時のみ描画
    if (g_pNini != NULL)
    {
        renderSprite(g_pNini);
    }
    //名前の画像が作成された時のみ描画
    if (g_pName != NULL)
    {
        renderSprite(g_pName);
    }
    //吹き出しのUIの画像が作成された時のみ描画
    if (g_pSpeechBalloonUI != NULL)
    {
        renderSprite(g_pSpeechBalloonUI);
    }

    //ステージ状況とストーリの進行によってによって切り替える
    if (Stage == 0)
    {
        //1回目 「あ、、、あ、、、」
        if (DialogueCount == 0)
        {
            //にには影の画像
            g_pNini->setAnimation(2);
            //名前ははてなの画像
            g_pName->setAnimation(1);
            //ににのアニメーションを止めておく
            g_NiniAnimation = false;
        }
        //2回目　「ぼくはにに」
        if (DialogueCount == 1)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue0_2, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //名前を表示
            g_pName->setAnimation(0);
            //ににのアニメーションを動かしておく
            g_NiniAnimation = true;
        }
        //3回目　「とつぜんだけど」
        if (DialogueCount == 2)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue0_3, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //分岐のフラグを有効にする
            g_DialogueSelect = true;
            //感情マークを表示
            NiniEmotion = 2;
        }
        //4回目　「そうこなくっちゃ」　「そうか、、。」
        if (DialogueCount == 3)
        {
            //分岐の条件の寄って作成するセリフを変える
            if (Select == 0)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_4, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }

                //感情マークを表示
                NiniEmotion = 1;
            }
            else
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_6, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }

                //感情マークを表示
                NiniEmotion = 3;
            }
        }
        //5回目　「早速、ぼくと」　「大丈夫」
        if (DialogueCount == 4)
        {
            //分岐の条件の寄って作成するセリフを変える
            if (Select == 0)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_5, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }
            }
            else
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_7, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }

                //感情マークを表示
                NiniEmotion = 1;
            }
        }
        //6回目　「詳しい話は」
        if (DialogueCount == 5)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue0_8, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを非表示
            NiniEmotion = 0;
        }
        //7回目　「矢印キーで」
        if (DialogueCount == 6)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue0_9, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }
        }
        //8回目
        if (DialogueCount == 7)
        {
            //フラグを無効にする
            g_Dialogue = false;
        }
        //9回目　「いい感じ」
        if (DialogueCount == 8)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue0_10, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを表示
            NiniEmotion = 1;
        }
        //10回目　「スペースキーで」
        if (DialogueCount == 9)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue0_11, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを非表示
            NiniEmotion = 0;
        }
        //11回目　「離すとジャンプ」
        if (DialogueCount == 10)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue0_12, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }
        }
        //12回目
        if (DialogueCount == 11)
        {
            //フラグを無効にする
            g_Dialogue = false;
        }
        //13回目　「上手」　「心配ない」
        if (DialogueCount == 12)
        {
            //通常
            if (Tuto == 2)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_14, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }

                //感情マークを表示
                NiniEmotion = 1;
            }

            //穴に落ちた場合
            else if (MissCount == 1)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_13, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }
            }
        }
        //14回目　「あのにゃがい穴」
        if (DialogueCount == 13)
        {
            //通常
            if (Tuto == 2)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_15, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }

                //感情マークを非表示
                NiniEmotion = 0;
            }

            //穴に落ちた場合
            else if (MissCount == 1)
            {
                //フラグを無効にする
                g_Dialogue = false;
            }
        }
        //15回目　「しゃがんだまま」
        if (DialogueCount == 14)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue0_16, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }
        }
        //16回目　「遠くに飛べる」
        if (DialogueCount == 15)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue0_17, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }
        }
        //17回目
        if (DialogueCount == 16)
        {
            //フラグを無効にする
            g_Dialogue = false;
        }
        //18回目　「高いところ」　「心配ない」
        if (DialogueCount == 17)
        {
            //通常
            if (Tuto == 3)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_18, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }
            }

            //穴に落ちた場合
            else if (MissCount == 1)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_13, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }
            }
        }
        //19回目　「上の矢印キーを」
        if (DialogueCount == 18)
        {
            //通常
            if (Tuto == 3)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_19, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }
            }
            //穴に落ちた場合
            else if (MissCount == 1)
            {
                //フラグを無効にする
                g_Dialogue = false;
            }
        }
        //20回目
        if (DialogueCount == 19)
        {
            //フラグを無効にする
            g_Dialogue = false;
        }
        //21回目　「上ジャンプでも」
        if (DialogueCount == 20)
        {
            //通常
            if (Tuto == 4)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_20, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }

                //感情マークを表示
                NiniEmotion = 4;
            }

            //穴に落ちた場合
            else if (MissCount == 1)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_13, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }
            }
        }
        //22回目　「おもいきり崖に」
        if (DialogueCount == 21)
        {
            //通常
            if (Tuto == 4)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_21, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }

                //感情マークを表示
                NiniEmotion = 1;
            }
            //穴に落ちた場合
            else if (MissCount == 1)
            {
                //フラグを無効にする
                g_Dialogue = false;
            }
        }
        //23回目
        if (DialogueCount == 22)
        {
            //フラグを無効にする
            g_Dialogue = false;
            //感情マークを非表示
            NiniEmotion = 0;
        }
        //24回目
        if (DialogueCount == 23)
        {
            //通常
            if (Tuto == 5)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_22, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }

                //感情マークを表示
                NiniEmotion = 1;
            }
            //穴に落ちた場合
            else if (MissCount == 1)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue0_13, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }
            }
        }
        //23回目
        if (DialogueCount == 24)
        {
            //フラグを無効にする
            g_Dialogue = false;
            //感情マークを非表示
            NiniEmotion = 0;
        }
    }

    if (Stage == 1)
    {
        //2回目　「やっぱり君は」
        if (DialogueCount == 26)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue1_2, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを表示
            NiniEmotion = 1;
        }
        //3回目　「説明がまだだったね」
        if (DialogueCount == 27)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue1_3, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを表示
            NiniEmotion = 4;
        }
        //4回目　「ハンターは」
        if (DialogueCount == 28)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue1_4, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを非表示
            NiniEmotion = 0;
        }
        //5回目　「あるものって？」
        if (DialogueCount == 29)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue1_5, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //分岐のフラグを有効にする
            g_DialogueSelect = true;
            //感情マークを非表示
            NiniEmotion = 2;
        }
        //6回目　「金」　「愛」
        if (DialogueCount == 30)
        {
            //分岐の条件の寄って作成するセリフを変える
            if (Select == 0)
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue1_6, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }

                //感情マークを表示
                NiniEmotion = 4;
            }
            else
            {
                //次のセリフの画像をNULLの時のみ作成する
                if (g_pDialogue == NULL)
                {
                    g_pDialogue = createSprite(Tex_Dialogue1_7, Dialogue_Size_X, Dialogue_Size_Y);
                    g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
                }

                //感情マークを表示
                NiniEmotion = 1;
            }
        }
        //7回目　「正解は」
        if (DialogueCount == 31)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue1_8, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを表示
            NiniEmotion = 5;
        }
        //8回目　「かつおぶし」
        if (DialogueCount == 32)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue1_9, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }
        }
        //9回目　「それから、、、」
        if (DialogueCount == 33)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue1_10, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを表示
            NiniEmotion = 6;
        }
        //10回目　「興奮」
        if (DialogueCount == 34)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue1_11, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを表示
            NiniEmotion = 7;
        }
        //11回目　「平原」
        if (DialogueCount == 35)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue1_12, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);

                //感情マークを非表示
                NiniEmotion = 0;
            }
        }
        //12回目　「探索して」
        if (DialogueCount == 36)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue1_13, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }
        }
        //13回目　「もしミスしても」
        if (DialogueCount == 37)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue1_14, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }
        }
        //14回目　「健闘を祈る」
        if (DialogueCount == 38)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue1_15, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを表示
            NiniEmotion = 1;
        }
        //15回目　
        if (DialogueCount == 39)
        {
            //フラグを無効にする
            g_Dialogue = false;
            //感情マークを非表示
            NiniEmotion = 0;
        }
    }

    if (Stage == 2)
    {
        //1回目　「順調？」
        if (DialogueCount == 40)
        {
            //感情マークを表示
            NiniEmotion = 2;
        }
        //2回目　「ふむふむ」
        if (DialogueCount == 41)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue2_2, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを表示
            NiniEmotion = 1;
        }
        //3回目　「気を引き締めて」
        if (DialogueCount == 42)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue2_3, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを非表示
            NiniEmotion = 0;
        }
        //4回目
        if (DialogueCount == 43)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue2_4, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }
        }
        //5回目
        if (DialogueCount == 44)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue2_5, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }
        }
        //6回目
        if (DialogueCount == 45)
        {
            //フラグを無効にする
            g_Dialogue = false;
        }
    }

    if (Stage == 3)
    {
        //2回目　「宝箱!?」
        if (DialogueCount == 47)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue2_7, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを表示
            NiniEmotion = 5;
        }
        //3回目　「一体どんな」
        if (DialogueCount == 48)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue2_9, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを表示
            NiniEmotion = 6;
        }
        //4回目
        if (DialogueCount == 49)
        {
            //感情マークを非表示
            NiniEmotion = 0;
            //フラグを無効にする
            g_Dialogue = false;
        }
        //5回目　「王冠」
        if (DialogueCount == 50)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue2_10, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを表示
            NiniEmotion = 4;
        }
        //6回目　「君の」
        if (DialogueCount == 51)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue2_11, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを表示
            NiniEmotion = 1;
        }
        //7回目　「十分」
        if (DialogueCount == 52)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue2_12, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }
        }
        //8回目　「お疲れ」
        if (DialogueCount == 53)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue2_13, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }

            //感情マークを表示
            NiniEmotion = 1;
        }
        //9回目
        if (DialogueCount == 54)
        {
            //感情マークを非表示
            NiniEmotion = 0;
            //フラグを無効にする
            g_Dialogue = false;
        }
    }

    if (g_Clear == true)
    {
        //1回目　「余った」
        if (DialogueCount == 55)
        {
            //感情マークを表示
            NiniEmotion = 1;
        }
        //2回目　「ハウスの前で」
        if (DialogueCount == 56)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue3_2, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }
        }
        //3回目　「スペースキーを押す」
        if (DialogueCount == 57)
        {
            //次のセリフの画像をNULLの時のみ作成する
            if (g_pDialogue == NULL)
            {
                g_pDialogue = createSprite(Tex_Dialogue3_3, Dialogue_Size_X, Dialogue_Size_Y);
                g_pDialogue->setPos(SpeechBalloon_Pos.x + 140.0f, 295.0f);
            }
        }
        //4回目
        if (DialogueCount == 58)
        {
            //感情マークを非表示
            NiniEmotion = 0;
            //フラグを無効にする
            g_Dialogue = false;
            //全てのセリフが終了
            g_AllDialogue = true;
        }
    }

    //吹き出しの画像が作成された時のみ描画
    if (g_pSpeechBalloon != NULL)
    {
        renderSprite(g_pSpeechBalloon);

        //3フレームに1回、アニメーションを切り替える
        if (g_SpeechBalloonAnimation != false)
        {
            SpeechBalloonAnimationCounter++;
            if (SpeechBalloonAnimationCounter % 4 == 0)
            {
                g_pSpeechBalloon->stepAnimation();
                SpeechBalloonAnimationCounter = 0;
                //何枚目のアニメーションなのかをカウントする
                SpeechBalloonAnimation++;
            }
            //再生し終えたら値をリセットしてフラグを無効にする
            if (SpeechBalloonAnimation == 8)
            {
                SpeechBalloonAnimation = 0;
                g_SpeechBalloonAnimation = false;
            }
        }

        //アニメーションが終わるとににと名前の画像が移動する
        if (g_SpeechBalloonAnimation == false)
        {
            g_pNini->setPos(g_pSpeechBalloon->getPos().x - 415.0f, g_pSpeechBalloon->getPos().y - 28.0f);
            g_pName->setPos(g_pSpeechBalloon->getPos().x - 419.0f, g_pSpeechBalloon->getPos().y + 127.0f);

            //セリフによって感情マークを変える
            if (NiniEmotion != 0)
            {
                if (NiniEmotion == 1)
                {
                    //喜び
                    g_pNiniEmotion->setAnimation(0);
                }
                if (NiniEmotion == 2)
                {
                    //はてな
                    g_pNiniEmotion->setAnimation(1);
                }
                if (NiniEmotion == 3)
                {
                    //悲しい
                    g_pNiniEmotion->setAnimation(2);
                }
                if (NiniEmotion == 4)
                {
                    //焦り
                    g_pNiniEmotion->setAnimation(3);
                }
                if (NiniEmotion == 5)
                {
                    //発見
                    g_pNiniEmotion->setAnimation(4);
                }
                if (NiniEmotion == 6)
                {
                    //興奮
                    g_pNiniEmotion->setAnimation(5);
                }
                if (NiniEmotion == 7)
                {
                    //照れ
                    g_pNiniEmotion->setAnimation(6);
                }

                //移動
                g_pNiniEmotion->setPos(g_pNini->getPos().x + 15.0f, g_pNini->getPos().y);
            }

            //セリフの画像が作成された時のみ描画
            if (g_pDialogue != NULL)
            {
                renderSprite(g_pDialogue);

                //セリフを表示させる吹き出しの画像に切り替える
                g_pSpeechBalloon->setAnimation(9);

                //4フレームに1回、アニメーションを切り替える
                if (g_DialogueAnimation != false)
                {
                    DialogueAnimationCounter++;
                    if (DialogueAnimationCounter % 5 == 0)
                    {
                        g_pDialogue->stepAnimation();
                        DialogueAnimationCounter = 0;
                        //何枚目のアニメーションなのかをカウントする
                        DialogueAnimation++;
                    }
                    //セリフ中に吹き出しのUIを移動させる
                    if (DialogueAnimation == 16 && g_DialogueSelect == false)
                    {
                        g_pSpeechBalloonUI->setPos(g_pSpeechBalloon->getPos().x + 530.0f, g_pSpeechBalloon->getPos().y - 110.0f);
                    }

                    //ににのアニメーション
                    //10フレームに1回、アニメーションを切り替える
                    if (g_pNini != NULL && g_NiniAnimation == true && DialogueAnimation <= 16)
                    {
                        NiniAnimationCounter++;
                        if (NiniAnimationCounter <= 10)
                        {
                            g_pNini->setAnimation(0);
                        }
                        if (NiniAnimationCounter > 10)
                        {
                            g_pNini->setAnimation(1);
                        }

                        //20フレーム後に値をリセット
                        if (NiniAnimationCounter % 20 == 0)
                        {
                            NiniAnimationCounter = 0;
                        }
                    }
                    //ににの画像を調整する
                    if (g_pNini != NULL && g_NiniAnimation == true && DialogueAnimation > 16)
                    {
                        g_pNini->setAnimation(0);
                    }

                    //再生し終えたら値をリセットしてフラグを無効にする
                    if (DialogueAnimation == 31)
                    {
                        DialogueAnimation = 0;
                        g_DialogueAnimation = false;
                    }
                    //スペースキーを押すとアニメーションをスキップする
                    if (getInput()->isPressedOnce(DIK_SPACE))
                    {
                        g_pDialogue->setAnimation(31);
                        //フラグを無効にする
                        g_DialogueAnimation = false;
                        //値をリセットしておく
                        DialogueAnimationCounter = 0;
                        DialogueAnimation = 0;

                        //吹き出しのUIを移動させる
                        g_pSpeechBalloonUI->setPos(g_pSpeechBalloon->getPos().x + 530.0f, g_pSpeechBalloon->getPos().y - 110.0f);

                        //ににの画像を調整する
                        if (g_pNini != NULL && g_NiniAnimation == true)
                        {
                            g_pNini->setAnimation(0);
                        }
                    }
                }

                //セリフを再生し終わった後スペースキーを押すと、次のセリフが流れる
                //分岐中は残り続ける
                else if (getInput()->isPressedOnce(DIK_SPACE) && g_Dialogue == true && g_DialogueSelect == false)
                {
                    //感情マークと吹き出しのUIを移動させておく
                    g_pNiniEmotion->setPos(0.0f, -WINDOW_HEIGHT);
                    g_pSpeechBalloonUI->setPos(-WINDOW_HEIGHT, 0.0f);
                    //セリフの画像を消す
                    disposeSprite(g_pDialogue);
                    g_pDialogue = NULL;
                    //セリフの数を数える
                    DialogueCount++;
                    //セリフが非表示の吹き出しの画像に切り替える
                    g_pSpeechBalloon->setAnimation(8);
                    //フラグを有効にする
                    g_DialogueAnimation = true;
                }

                //分岐中は選択肢が出る
                else if (g_DialogueSelect != false)
                {
                    //ににの画像を調整する
                    g_pNini->setAnimation(0);

                    //分岐用吹き出しと分岐の選択肢の画像が作成されている時のみ描画
                    if (g_pSpeechBalloonSelect != NULL && g_pDialogueSelect != NULL)
                    {
                        renderSprite(g_pSpeechBalloonSelect);
                        renderSprite(g_pDialogueSelect);

                        //スペースキーを押すと選択肢を決定
                        if (getInput()->isPressedOnce(DIK_SPACE))
                        {
                            //選択肢の画像を消す
                            disposeSprite(g_pSpeechBalloonSelect);
                            g_pSpeechBalloonSelect = NULL;
                            disposeSprite(g_pDialogueSelect);
                            g_pDialogueSelect = NULL;

                            //感情マークを移動させておく
                            g_pNiniEmotion->setPos(-WINDOW_HEIGHT, 0.0f);
                            //フラグを無効にする
                            g_DialogueSelect = false;
                            //セリフの画像を消す
                            disposeSprite(g_pDialogue);
                            g_pDialogue = NULL;
                            //セリフの数を数える
                            DialogueCount++;
                            //セリフが非表示の吹き出しの画像に切り替える
                            g_pSpeechBalloon->setAnimation(8);
                            //フラグを有効にする
                            g_DialogueAnimation = true;
                        }

                        //矢印キーで選択肢を変更
                        if (getInput()->isPressedOnce(DIK_UPARROW))
                        {
                            //アニメーションを動かす
                            g_pSpeechBalloonSelect->setAnimation(0);
                            Select = 0;
                        }
                        if (getInput()->isPressedOnce(DIK_DOWNARROW))
                        {
                            //アニメーションを動かす
                            g_pSpeechBalloonSelect->setAnimation(1);
                            Select = 1;
                        }
                    }
                }
            }
        }

        //セリフがすべて出し終わった後、吹き出しを閉じる
        if (g_Dialogue == false)
        {
            if (g_pSpeechBalloon != NULL)
            {
                //アニメーションを逆再生する
                int SpeechBalloonBackAnimation = 9;
                //3フレームに1回、アニメーションを切り替える
                SpeechBalloonAnimationCounter++;
                if (SpeechBalloonAnimationCounter % 3 == 0)
                {
                    g_pSpeechBalloon->setAnimation(SpeechBalloonBackAnimation - (SpeechBalloonAnimationCounter / 3));
                    //何枚目のアニメーションなのかをカウントする
                    SpeechBalloonAnimation++;
                }
                //再生し終えたら値をリセットして画像を破棄
                if (SpeechBalloonAnimation == 9)
                {
                    //セリフの数を数える
                    DialogueCount++;
                    //値をリセット
                    SpeechBalloonAnimationCounter = 0;
                    SpeechBalloonAnimation = 0;
                    NiniAnimationCounter = 0;

                    //吹き出しの画像が作成された時のみ破棄
                    disposeSprite(g_pSpeechBalloon);
                    g_pSpeechBalloon = NULL;

                    //フラグをリセットする
                    g_SpeechBalloonAnimation = true;
                    g_Dialogue = true;
                    //フラグを無効にする
                    g_Speech = false;
                }
            }

            //ににの画像が作成された時のみ破棄
            if (g_pNini != NULL)
            {
                disposeSprite(g_pNini);
                g_pNini = NULL;
            }
            //ににの感情マークの画像が作成された時のみ破棄
            if (g_pNiniEmotion != NULL)
            {
                disposeSprite(g_pNiniEmotion);
                g_pNiniEmotion = NULL;
            }
            //名前の画像が作成された時のみ破棄
            if (g_pName != NULL)
            {
                disposeSprite(g_pName);
                g_pName = NULL;
            }
        }
    }
}

/*
* 関数名　  ：procPlayMain_StageChange()
* 処理内容　：ステージチェンジの処理
*/
void COriginalGameApp::procPlayMain_StageChange()
{
    if (g_pPlayerCollisionBottom->collision(g_pHouse) && getInput()->isPressedOnce(DIK_SPACE) && g_Clear == true)
    {
        //フラグを有効にする
        g_Change = true;
    }
}

/*
* 関数名　  ：procPlayEnd_Stage()
* 処理内容　：ステージの画面の終了処理
*/
void COriginalGameApp::procPlayEnd_Stage()
{
    //数値のリセットを行う関数
    procPlayEnd_ValueReset();

    //プレイヤーの画像が作成された時のみ破棄
    if (g_pPlayer != NULL)
    {
        disposeSprite(g_pPlayer);
        g_pPlayer = NULL;
    }
    //プレイヤーの当たり判定の画像が作成された時のみ破棄
    if (g_pPlayerCollisionBottom != NULL)
    {
        disposeSprite(g_pPlayerCollisionBottom);
        g_pPlayerCollisionBottom = NULL;
    }
    if (g_pPlayerCollisionSide != NULL)
    {
        disposeSprite(g_pPlayerCollisionSide);
        g_pPlayerCollisionSide = NULL;
    }

    //リスポーンハウスの画像が作成された時のみ破棄
    if (g_pHouse != NULL)
    {
        disposeSprite(g_pHouse);
        g_pHouse = NULL;
    }

    //床(2)の画像が作成された時のみ破棄
    for (int i = 0; i < Ground2_Count; ++i)
    {
        if (g_pGround[i] != NULL)
        {
            disposeSprite(g_pGround[i]);
            g_pGround[i] = NULL;
        }
    }

    //穴(2)の画像が作成された時のみ破棄
    for (int i = 0; i < Hole1_Count; ++i)
    {
        if (g_pHole[i] != NULL)
        {
            disposeSprite(g_pHole[i]);
            g_pHole[i] = NULL;
        }
    }

    //崖(2)の画像が作成された時のみ破棄
    for (int i = 0; i < CliffSide2_Count; ++i)
    {
        if (g_pCliffSide[i] != NULL)
        {
            disposeSprite(g_pCliffSide[i]);
            g_pCliffSide[i] = NULL;
        }
    }
    //真ん中の崖(2)の画像が作成された時のみ破棄
    for (int i = 0; i < CliffCenter1_Count; ++i)
    {
        if (g_pCliffCenter[i] != NULL)
        {
            disposeSprite(g_pCliffCenter[i]);
            g_pCliffCenter[i] = NULL;
        }
    }

    //丘(2)の画像が作成された時のみ破棄
    for (int i = 0; i < HillSide2_Count; ++i)
    {
        if (g_pHillSide[i] != NULL)
        {
            disposeSprite(g_pHillSide[i]);
            g_pHillSide[i] = NULL;
        }
    }
    //真ん中の丘(2)の画像が作成された時のみ破棄
    for (int i = 0; i < HillCenter2_Count; ++i)
    {
        if (g_pHillCenter[i] != NULL)
        {
            disposeSprite(g_pHillCenter[i]);
            g_pHillCenter[i] = NULL;
        }
    }
    //丘の当たり判定(2)の画像が作成された時のみ破棄
    for (int i = 0; i < HillCollision2_Count; ++i)
    {
        if (g_pHillCollision[i] != NULL)
        {
            disposeSprite(g_pHillCollision[i]);
            g_pHillCollision[i] = NULL;
        }
    }

    //リフト(2)の画像が作成された時のみ破棄
    for (int i = 0; i < MoveLift2_Count; ++i)
    {
        if (g_pMoveLift[i] != NULL)
        {
            disposeSprite(g_pMoveLift[i]);
            g_pMoveLift[i] = NULL;
        }
    }
    for (int i = 0; i < FallLift2_Count; ++i)
    {
        if (g_pFallLift[i] != NULL)
        {
            disposeSprite(g_pFallLift[i]);
            g_pFallLift[i] = NULL;
        }
    }
    //リフトの当たり判定(2)の画像が作成された時のみ破棄
    for (int i = 0; i < MoveLift2_Count; ++i)
    {
        if (g_pMoveLiftCollision[i] != NULL)
        {
            disposeSprite(g_pMoveLiftCollision[i]);
            g_pMoveLiftCollision[i] = NULL;
        }
    }
    for (int i = 0; i < FallLift2_Count; ++i)
    {
        if (g_pFallLiftCollision[i] != NULL)
        {
            disposeSprite(g_pFallLiftCollision[i]);
            g_pFallLiftCollision[i] = NULL;
        }
    }
    //トゲ(2)の画像が作成された時のみ破棄
    for (int i = 0; i < Needl2_Count; ++i)
    {
        if (g_pNeedl[i] != NULL)
        {
            disposeSprite(g_pNeedl[i]);
            g_pNeedl[i] = NULL;
        }
    }

    //ブロック(2)の画像が作成された時のみ破棄
    for (int i = 0; i < Block1_Count; ++i)
    {
        if (g_pBlock[i] != NULL)
        {
            disposeSprite(g_pBlock[i]);
            g_pBlock[i] = NULL;
        }
    }

    //看板(2)の画像が作成された時のみ破棄
    for (int i = 0; i < Signboard1_Count; ++i)
    {
        if (g_pSignboard[i] != NULL)
        {
            disposeSprite(g_pSignboard[i]);
            g_pSignboard[i] = NULL;
        }
    }
    //看板の矢印(2)の画像が作成された時のみ破棄
    for (int i = 0; i < Signboard1_Count; ++i)
    {
        if (g_pSignboardArrow[i] != NULL)
        {
            disposeSprite(g_pSignboardArrow[i]);
            g_pSignboardArrow[i] = NULL;
        }
    }

    //にぼし(2)の画像が作成された時のみ破棄
    for (int i = 0; i < Niboshi2_Count; ++i)
    {
        if (g_pNiboshi[i] != NULL)
        {
            disposeSprite(g_pNiboshi[i]);
            g_pNiboshi[i] = NULL;
        }
    }
    //かつおぶし(2)の画像が作成された時のみ破棄
    for (int i = 0; i < Katuobushi_Count; ++i)
    {
        if (g_pKatuobushi[i] != NULL)
        {
            disposeSprite(g_pKatuobushi[i]);
            g_pKatuobushi[i] = NULL;
        }
    }

    //にぼしのUI(2)の画像が作成された時のみ破棄
    {
        if (g_pNiboshiUI != NULL)
        {
            disposeSprite(g_pNiboshiUI);
            g_pNiboshiUI = NULL;
        }
    }
    //かつおぶしのUI(2)の画像が作成された時のみ破棄
    {
        if (g_pKatuobushiUI != NULL)
        {
            disposeSprite(g_pKatuobushiUI);
            g_pKatuobushiUI = NULL;
        }
    }
    //残機のUI(2)の画像が作成された時のみ破棄
    {
        if (g_pLifeUI != NULL)
        {
            disposeSprite(g_pLifeUI);
            g_pLifeUI = NULL;
        }
    }
    //UIの数字(2)の画像が作成された時のみ破棄
    for (int i = 0; i < 6; ++i)
    {
        if (g_pNumber[i] != NULL)
        {
            disposeSprite(g_pNumber[i]);
            g_pNumber[i] = NULL;
        }
    }

    //吹き出しの画像が作成された時のみ破棄
    if (g_pSpeechBalloon != NULL)
    {
        disposeSprite(g_pSpeechBalloon);
        g_pSpeechBalloon = NULL;
    }
    //ににの画像が作成された時のみ破棄
    if (g_pNini != NULL)
    {
        disposeSprite(g_pNini);
        g_pNini = NULL;
    }
    //ににの表示の画像が作成された時のみ破棄
    if (g_pNiniEmotion != NULL)
    {
        disposeSprite(g_pNiniEmotion);
        g_pNiniEmotion = NULL;
    }
    //名前の画像が作成された時のみ破棄
    if (g_pName != NULL)
    {
        disposeSprite(g_pName);
        g_pName = NULL;
    }
    //吹き出しのUIの画像が作成された時のみ破棄
    if (g_pSpeechBalloonUI != NULL)
    {
        disposeSprite(g_pSpeechBalloonUI);
        g_pSpeechBalloonUI = NULL;
    }
    //分岐用の吹き出しのUIの画像が作成された時のみ破棄
    if (g_pSpeechBalloonSelect != NULL)
    {
        disposeSprite(g_pSpeechBalloonSelect);
        g_pSpeechBalloonSelect = NULL;
    }
    //セリフの画像が作成された時のみ破棄
    if (g_pDialogue != NULL)
    {
        disposeSprite(g_pDialogue);
        g_pDialogue = NULL;
    }

    //宝箱の画像が作成された時のみ破棄
    if (g_pTreasure != NULL)
    {
        disposeSprite(g_pTreasure);
        g_pName = NULL;
    }
    //王冠の画像が作成された時のみ破棄
    if (g_pCrown != NULL)
    {
        disposeSprite(g_pCrown);
        g_pName = NULL;
    }

    //背景(1)の画像が作成された時のみ破棄
    for (int i = 0; i < BackGround2_Count; ++i)
    {
        if (g_pBackGround[i] != NULL)
        {
            disposeSprite(g_pBackGround[i]);
            g_pBackGround[i] = NULL;
        }
    }
}

/*
* 関数名　  ：procPlayEnd_ValueReset()
* 処理内容　：プレイヤーの各変数のリセットの処理
*/
void COriginalGameApp::procPlayEnd_ValueReset()
{
    if (Stage == 0)
    {
        //ミス用のセリフを出すために一度だけリセットしておく
        if (MissCount == 0)
        {
            g_Speech = true;
        }
    }
    //吹き出しの表示座標をリセットしておく
    SpeechBalloon_Pos = { 0.0f, 300.0f };

    //各フラグのリセット
    g_Miss = false;

    for (int i = 0; i < MoveLift_Count; ++i)
    {
        MoveLiftMove[i] = 0.0f;
    }
    for (int i = 0; i < FallLift_Count; ++i)
    {
        g_FallLift[i] = false;
    }

    for (int i = 0; i < Needl2_Count; ++i)
    {
        NeedlMove[i] = 0.0f;
        g_NeedlMoveUp[i] = true;
    }

    g_NeedlDirection[13] = 3;
    g_NeedlDirection[15] = 3;

    g_NeedlDirection[28] = 2;
    g_NeedlDirection[27] = 2;
    g_NeedlDirection[26] = 2;
    g_NeedlDirection[25] = 2;
    g_NeedlDirection[24] = 2;
    g_NeedlDirection[23] = 2;
}
