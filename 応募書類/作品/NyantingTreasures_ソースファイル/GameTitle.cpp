//------------------------
//ファイル名：GameTitle.cpp
//作成者　　：中山薫
//所属		：日本電子専門学校　ゲーム制作研究科
//作成日　　：2020/11/30
//最終更新　：2020/02/09
//------------------------

#include "COriginalGameApp.h"
#include "GameResource.h"

/*
 * タイトルの処理を行う部分
 */

//変数宣言----------------------------
//タイトル画面のフェーズを管理する変数
ePhase g_TitlePhase = eBegin;
//タイトルから次へと進むときのフローを管理する変数
eGameStatus g_NextStatusFromTitle = eNone;

//タイトル画面の画像を管理する変数
CPicture* g_pTitle = NULL;
CPicture* g_tPlayer = NULL;

//タイマー
int tTimer = 0;
//フラグ
bool MovePlayer = false;

void COriginalGameApp::procTitle()
{
    //ケースによって切り替える
    switch (g_TitlePhase)
    {
        case eBegin:
        {
            //タイトル開始時の処理
            procTitleBegin();
            //進行状況をメインに切り替える
            g_TitlePhase = eMain;
        }
        break;
        case eMain:
        {
            //タイトルのメイン処理
            procTitleMain();
            //スペースキーが押されたらゲーム画面に移行
            if (g_tPlayer->getPos().x >= 960.0f)
            {
                g_NextStatusFromTitle = ePlaying;
                //進行状況をエンドに切り替える
                g_TitlePhase = eEnd;
            }
        }
        break;
        case eEnd:
        {
            //タイトル終了時の処理
            procTitleEnd();
            //再度戻ってきたときのために進行状況をリセットしておく
            g_TitlePhase = eBegin;
            //次のフェーズに切り替える
            SetNextGameStatus(g_NextStatusFromTitle);
        }
    }
}

/*
* 関数名　  ：procTitleBegin()
* 処理内容　：タイトル画面の開始処理
*/
void COriginalGameApp::procTitleBegin()
{
    //タイトル画像がNULLの時のみ作成する
    if (g_pTitle == NULL)
    {
        g_pTitle = createSprite(Tex_Title);
    }
    //プレイヤーがNULLの時のみ作成する
    if (g_tPlayer == NULL)
    {
        
        g_tPlayer = createSprite(Tex_Player, 283.0f, 202.0f);
        g_tPlayer->setPos(-700.0f, -304.0f);
    }

    if (g_Clear == true)
    {
        Stage = 1;
    }
}

/*
* 関数名　  ：procTitleMain()
* 処理内容　：タイトル画面のメイン処理
*/
void COriginalGameApp::procTitleMain()
{
    //プレイヤーが作成された時のみ描画
    if (g_tPlayer != NULL)
    {
        renderSprite(g_tPlayer);
    }
    //タイトル画面が作成された時のみ描画
    if (g_pTitle != NULL)
    {
        renderSprite(g_pTitle);
    }

    if (getInput()->isPressedOnce(DIK_SPACE))
    {
        MovePlayer = true;
    }

    if (MovePlayer == true)
    {
        //タイマーを進める
        ++tTimer;
        //アニメーションの範囲を決める
        g_tPlayer->setAnimationRange(1, 6);

        if (tTimer % 2 == 0)
        {
            g_tPlayer->setPos(g_tPlayer->getPos().x + 20.0f, g_tPlayer->getPos().y);
        }
        if (tTimer % 5 == 0)
        {
            g_tPlayer->stepAnimation();
        }

        if (g_tPlayer->getPos().x >= 960.0f)
        {
            MovePlayer = false;
        }

    }
}

/*
* 関数名　  ：procTitleEnd()
* 処理内容　：タイトル画面の終了処理
*/
void COriginalGameApp::procTitleEnd()
{
    //タイトル画面が作成された時のみ破棄
    if (g_pTitle != NULL)
    {
        disposeSprite(g_pTitle);
        g_pTitle = NULL;
    }
}
