//------------------------
//ファイル名：GameClear.cpp
//作成者　　：中山薫
//所属		：日本電子専門学校　ゲーム制作研究科
//作成日　　：2020/12/04
//最終更新　：2020/02/09
//------------------------

#include "COriginalGameApp.h"
#include "GameResource.h"

/*
 * ゲームクリア画面の処理を行う部分
 */

//変数宣言----------------------------
//クリア画面のフェーズを管理する変数
ePhase g_ClearPhase = eBegin;
//クリア画面から次へと進むときのフローを管理する変数
eGameStatus g_NextStatusFromClear = eNone;

//クリア画面の画像を管理する変数
CPicture* g_pClear = NULL;
//ENDカードの画像を管理する変数
CPicture* g_pEND[3] = { NULL,};

//タイマー
int Timer = 0;

void COriginalGameApp::procClear()
{
    //ケースによって切り替える
    switch (g_ClearPhase)
    {
        case eBegin:
        {
            //クリア開始時の処理
            procClearBegin();
            //進行状況をメインに切り替える
            g_ClearPhase = eMain;
        }
        break;
        case eMain:
        {
            if (Stage == 3)
            {
                //クリアのメイン処理
                procClearMain();

                if (Timer >= 100  && getInput()->isPressedOnce(DIK_SPACE))
                {
                    g_NextStatusFromClear = eOpening;
                    //進行状況をエンドに切り替える
                    g_ClearPhase = eEnd;
                }
            }
            else
            {
                //ステージチェンジの場合は交互に移動する
                if (g_Change == true)
                {
                    if (Stage == 1)
                    {
                        Stage = 2;
                        g_Change = false;
                    }
                    else if (Stage == 2)
                    {
                        Stage = 1;
                        g_Change = false;
                    }
                }
                else
                {
                    //次のステージへ移行する
                    ++Stage;
                }

                g_NextStatusFromClear = ePlaying;
                //進行状況をエンドに切り替える
                g_ClearPhase = eEnd;
            }
        }
        break;
        case eEnd:
        {
            //クリア終了時の処理
            procClearEnd();
            //再度戻ってきたときのために進行状況をリセットしておく
            g_ClearPhase = eBegin;
            //次のフェーズに切り替える
            SetNextGameStatus(g_NextStatusFromClear);
        }
    }
}

/*
* 関数名　  ：procClearBegin()
* 処理内容　：クリア画面の開始処理
*/
void COriginalGameApp::procClearBegin()
{
    //クリア画像がNULLの時のみ作成する
    if (g_pClear == NULL)
    {
        g_pClear = createSprite(Tex_Clear);
    }

    //ENDカードの画像がNULLの時のみ作成する
    if (Stage == 3)
    {
        if (g_pEND[0] == NULL)
        {
            g_pEND[0] = createSprite(Tex_E,250.0f, 250.0f);
            g_pEND[0]->setPos(330.0f, -400.0f);
            g_pEND[0]->setActive(false);
        }
        if (g_pEND[1] == NULL)
        {
            g_pEND[1] = createSprite(Tex_N, 250.0f, 250.0f);
            g_pEND[1]->setPos(580.0f, -400.0f);
            g_pEND[1]->setActive(false);
        }
        if (g_pEND[2] == NULL)
        {
            g_pEND[2] = createSprite(Tex_D, 250.0f, 250.0f);
            g_pEND[2]->setPos(830.0f, -400.0f);
            g_pEND[2]->setActive(false);
        }
    }

    //セリフを出すようにしておく
    g_Speech = true;

    //ミスした回数をリセットしておく
    MissCount = 0;
}

/*
* 関数名　  ：procClearMain()
* 処理内容　：クリア画面のメイン処理
*/
void COriginalGameApp::procClearMain()
{
    //タイマーを作動
    Timer++;

    //ENDカードが作成された時のみ描画
    for (int i = 0; i < 3; ++i)
    {
        if (g_pEND[i] != NULL)
        {
            renderSprite(g_pEND[i]);
        }
    }

    //タイマーによってENDカードを表示
    if (Timer % 10 == 0)
    {
        g_pEND[0]->setActive(true);
    }
    if (Timer % 40 == 0)
    {
        g_pEND[1]->setActive(true);
    }
    if (Timer % 70 == 0)
    {
        g_pEND[2]->setActive(true);
    }

    //クリア画面が作成された時のみ描画
    if (g_pClear != NULL)
    {
        renderSprite(g_pClear);
    }
}

/*
* 関数名　  ：procClearEnd()
* 処理内容　：クリア画面の終了処理
*/
void COriginalGameApp::procClearEnd()
{
    //クリア画面が作成された時のみ破棄
    if (g_pClear != NULL)
    {
        disposeSprite(g_pClear);
        g_pClear = NULL;
    }
}
