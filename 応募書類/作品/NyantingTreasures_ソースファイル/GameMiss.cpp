//------------------------
//ファイル名：GameMiss.cpp
//作成者　　：中山薫
//所属		：日本電子専門学校　ゲーム制作研究科
//作成日　　：2020/12/04
//最終更新　：2020/02/09
//------------------------

#include "COriginalGameApp.h"
#include "GameResource.h"

/*
 * ゲームミス画面の処理を行う部分
 */

 //変数宣言----------------------------
 //ミス画面のフェーズを管理する変数
ePhase g_MissPhase = eBegin;
//ミス画面から次へと進むときのフローを管理する変数
eGameStatus g_NextStatusFromMiss = eNone;

//ミス画面の画像を管理する変数
CPicture* g_pMiss = NULL;

//残機のUIの画像を管理する変数
CPicture* g_mLifeUI = NULL;
CPicture* g_mNumber[2] = { NULL, };
//タイマー
int mTimer = 0;
//ライフを減らすフラグ
bool LifeDecrease = false;

void COriginalGameApp::procGameMiss()
{
    //ケースによって切り替える
    switch (g_MissPhase)
    {
        case eBegin:
        {
            //ミス開始時の処理
            procMissBegin();
            //進行状況をメインに切り替える
            g_MissPhase = eMain;
        }
        break;
        case eMain:
        {
            //ミスのメイン処理
            procMissMain();
            //スペースキーが押されたらプレイ画面に移行
            if (mTimer == 130)
            {
                g_NextStatusFromMiss = ePlaying;
                //進行状況をエンドに切り替える
                g_MissPhase = eEnd;
            }
        }
        break;
        case eEnd:
        {
            //ミス終了時の処理
            procMissEnd();
            //再度戻ってきたときのために進行状況をリセットしておく
            g_MissPhase = eBegin;
            //次のフェーズに切り替える
            SetNextGameStatus(g_NextStatusFromMiss);
        }
    }
}

/*
* 関数名　  ：procMissBegin()
* 処理内容　：ミス画面の開始処理
*/
void COriginalGameApp::procMissBegin()
{
    //ミス画像がNULLの時のみ作成する
    if (g_pMiss == NULL)
    {
        g_pMiss = createSprite(Tex_Clear);
    }

    //残機のUIの画像がNULLの時のみ作成する
    if (g_mLifeUI == NULL)
    {
        g_mLifeUI = createSprite(Tex_LifeUI,300.0f,200.0f);
        g_mLifeUI->setPos(-170.0f, 0.0f);
        if (g_Clear == true)
        {
            g_mLifeUI->setAnimation(1);
        }
    }
    //UIの数字の画像がNULLの時のみ作成する
    for (int i = 0; i < 2; ++i)
    {
        if (g_mNumber[i] == NULL)
        {
            g_mNumber[i] = createSprite(Tex_Number, 100.0f, 100.0f);
            g_mNumber[i]->setPos(g_mLifeUI->getPos().x + 200.0f + (60.0f * i), g_mLifeUI->getPos().y);
        }
    }
    //ミスをカウント
     MissCount++;
}

/*
* 関数名　  ：procMissMain()
* 処理内容　：ミス画面のメイン処理
*/
void COriginalGameApp::procMissMain()
{
    //残機のUIの画像が作成された時のみ描画
    if (g_mLifeUI != NULL)
    {
        renderSprite(g_mLifeUI);
    }
    //UIの数字の画像が作成された時のみ描画
    for (int i = 0; i < 2; ++i)
    {
        if (g_mNumber[i])
        {
            renderSprite(g_mNumber[i]);
        }
    }

    //ミス画面が作成された時のみ描画
    if (g_pMiss != NULL)
    {
        renderSprite(g_pMiss);
    }

    //UIに数字を代入
    g_mNumber[0]->setAnimation(Life / 10);
    g_mNumber[1]->setAnimation(Life - ((Life / 10) * 10));

    mTimer++;
    if (mTimer == 50)
    {
        LifeDecrease = true;
    }
    if (LifeDecrease == true)
    {
        //ライフを減らす
        Life -= 1;
        LifeDecrease = false;
    }
}

/*
* 関数名　  ：procMissEnd()
* 処理内容　：ミス画面の終了処理
*/
void COriginalGameApp::procMissEnd()
{
    //ミス画面が作成された時のみ破棄
    if (g_pMiss != NULL)
    {
        disposeSprite(g_pMiss);
        g_pMiss = NULL;
    }
    //残機のUIの画像が作成された時のみ破棄
    if (g_mLifeUI != NULL)
    {
        disposeSprite(g_mLifeUI);
        g_mLifeUI = NULL;
    }
    //UIの数字の画像が作成された時のみ破棄
    for (int i = 0; i < 2; ++i)
    {
        if (g_mNumber[i] != NULL)
        {
            disposeSprite(g_mNumber[i]);
            g_mNumber[i] = NULL;
        }
    }

    //リセット
    mTimer = 0;
    LifeDecrease = false;
}
