//------------------------
//ファイル名：GameOver.cpp
//作成者　　：中山薫
//所属		：日本電子専門学校　ゲーム制作研究科
//作成日　　：2020/11/30
//最終更新　：2020/02/08
//------------------------

#include "COriginalGameApp.h"
#include "GameResource.h"

/*
 * ゲームオーバー画面の処理を行う部分
 */

 //変数宣言----------------------------
 //オーバー画面のフェーズを管理する変数
ePhase g_OverPhase = eBegin;
//オーバー画面から次へと進むときのフローを管理する変数
eGameStatus g_NextStatusFromOver = eNone;

//オーバー画面の画像を管理する変数
CPicture* g_pOver = NULL;

//吹き出しの画像を管理する変数
CPicture* g_oSpeechBalloon = NULL;
//ににの画像を管理する変数
CPicture* g_oNini = NULL;
//名前の画像を管理する変数
CPicture* g_oName = NULL;
//吹き出しのUIの画像を管理する変数
CPicture* g_oSpeechBalloonUI = NULL;
//分岐用吹き出しの画像を管理する変数
CPicture* g_oSpeechBalloonSelect = NULL;
//セリフの画像を管理する変数
CPicture* g_oDialogue = NULL;

//アニメーションのカウンター
int SpeechBalloonAnimationCounter_O = 0;
int NiniAnimationCounter_O = 0;
//アニメーションした回数
int SpeechBalloonAnimation_O = 0;
//アニメーションのフラグ
bool o_SpeechBalloonAnimation = true;
bool o_NiniAnimation = true;

//アニメーションのカウンター
int DialogueAnimationCounter_O = 0;
//アニメーションした回数
int DialogueAnimation_O = 0;
//アニメーションのフラグ
bool o_DialogueAnimation = true;

void COriginalGameApp::procGameOver()
{
    //ケースによって切り替える
    switch (g_OverPhase)
    {
        case eBegin:
        {
            //オーバー開始時の処理
            procOverBegin();
            //進行状況をメインに切り替える
            g_OverPhase = eMain;
        }
        break;
        case eMain:
        {
            //オーバーのメイン処理
            procOverMain();
            //スペースキーが押されたらプレイ画面に移行
            if (getInput()->isPressedOnce(DIK_SPACE) && o_DialogueAnimation == false)
            {
                g_NextStatusFromOver = ePlaying;
                //進行状況をエンドに切り替える
                g_OverPhase = eEnd;
            }
        }
        break;
        case eEnd:
        {
            //ミス終了時の処理
            procOverEnd();
            //再度戻ってきたときのために進行状況をリセットしておく
            g_OverPhase = eBegin;
            //次のフェーズに切り替える
            SetNextGameStatus(g_NextStatusFromOver);
        }
    }
}

/*
* 関数名　  ：procOverBegin()
* 処理内容　：オーバー画面の開始処理
*/
void COriginalGameApp::procOverBegin()
{
    //吹き出しの画像がNULLの時のみ作成
    if (g_oSpeechBalloon == NULL)
    {
        g_oSpeechBalloon = createSprite(Tex_SpeechBalloon, 1200.0f, 320.0f);
        g_oSpeechBalloon->setPos(0.0f,-100.0f);
    }
    //ににの画像がNULLの時のみ作成
    if (g_oNini == NULL)
    {
        g_oNini = createSprite(Tex_Nini, 202.0f, 236.0f);
        g_oNini->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //名前の画像がNULLの時のみ作成
    if (g_oName == NULL)
    {
        g_oName = createSprite(Tex_Name, 100.0f, 68.0f);
        g_oName->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //吹き出しのUIの画像がNULLの時のみ作成
    if (g_oSpeechBalloonUI == NULL)
    {
        g_oSpeechBalloonUI = createSprite(Tex_SpeechBalloonUI, 54.0f, 59.0f);
        g_oSpeechBalloonUI->setPos(0.0f, -WINDOW_HEIGHT);
    }
    //セリフの画像がNULLの時のみ作成
    if (g_oDialogue == NULL)
    {
        g_oDialogue = createSprite(Tex_Dialogue0_13, 870.0f, 155.0f);
        g_oDialogue->setPos(140.0f, -105.0f);
    }

    //オーバー画像がNULLの時のみ作成する
    if (g_pOver == NULL)
    {
        g_pOver = createSprite(Tex_Over);
    }
}

/*
* 関数名　  ：procOverMain()
* 処理内容　：オーバー画面のメイン処理
*/
void COriginalGameApp::procOverMain()
{
    //ににの画像が作成された時のみ描画
    if (g_oNini != NULL)
    {
        renderSprite(g_oNini);
    }
    //名前の画像が作成された時のみ描画
    if (g_oName != NULL)
    {
        renderSprite(g_oName);
    }
    //吹き出しのUIの画像が作成された時のみ描画
    if (g_oSpeechBalloonUI != NULL)
    {
        renderSprite(g_oSpeechBalloonUI);
    }

    //ミスしたステージのかつおぶしを再表示
    for (int i = 0; i < 10; ++i)
    {
        if (KatuobushiFlag[Stage - 1][i] == true)
        {
            KatuobushiFlag[Stage - 1][i] = false;
            KatuobushiCounter--;
        }
    }
    //吹き出しの画像が作成された時のみ描画
    if (g_oSpeechBalloon != NULL)
    {
        renderSprite(g_oSpeechBalloon);

        //3フレームに1回、アニメーションを切り替える
        if (o_SpeechBalloonAnimation != false)
        {
            SpeechBalloonAnimationCounter_O++;
            if (SpeechBalloonAnimationCounter_O % 3 == 0)
            {
                g_oSpeechBalloon->stepAnimation();
                SpeechBalloonAnimationCounter_O = 0;
                //何枚目のアニメーションなのかをカウントする
                SpeechBalloonAnimation_O++;
            }
            //再生し終えたら値をリセットしてフラグを無効にする
            if (SpeechBalloonAnimation_O == 8)
            {
                SpeechBalloonAnimation_O = 0;
                o_SpeechBalloonAnimation = false;
            }
        }

        //アニメーションが終わるとににと名前の画像が移動する
        if (o_SpeechBalloonAnimation == false)
        {
            g_oNini->setPos(g_oSpeechBalloon->getPos().x - 415.0f, g_oSpeechBalloon->getPos().y - 28.0f);
            g_oName->setPos(g_oSpeechBalloon->getPos().x - 419.0f, g_oSpeechBalloon->getPos().y + 127.0f);

            //セリフの画像が作成された時のみ描画
            if (g_oDialogue != NULL)
            {
                renderSprite(g_oDialogue);

                //セリフを表示させる吹き出しの画像に切り替える
                g_oSpeechBalloon->setAnimation(9);

                //4フレームに1回、アニメーションを切り替える
                if (o_DialogueAnimation != false)
                {
                    DialogueAnimationCounter_O++;
                    if (DialogueAnimationCounter_O % 4 == 0)
                    {
                        g_oDialogue->stepAnimation();
                        DialogueAnimationCounter_O = 0;
                        //何枚目のアニメーションなのかをカウントする
                        DialogueAnimation_O++;
                    }
                    //セリフ中に吹き出しのUIを移動させる
                    if (DialogueAnimation_O == 16)
                    {
                        g_oSpeechBalloonUI->setPos(g_oSpeechBalloon->getPos().x + 530.0f, g_oSpeechBalloon->getPos().y - 110.0f);
                    }

                    //ににのアニメーション
                    //10フレームに1回、アニメーションを切り替える
                    if (g_oNini != NULL && o_NiniAnimation == true && DialogueAnimation_O <= 16)
                    {
                        NiniAnimationCounter_O++;
                        if (NiniAnimationCounter_O <= 10)
                        {
                            g_oNini->setAnimation(0);
                        }
                        if (NiniAnimationCounter_O > 10)
                        {
                            g_oNini->setAnimation(1);
                        }

                        //20フレーム後に値をリセット
                        if (NiniAnimationCounter_O % 20 == 0)
                        {
                            NiniAnimationCounter_O = 0;
                        }
                    }
                    //ににの画像を調整する
                    if (g_oNini != NULL && o_NiniAnimation == true && DialogueAnimation_O > 16)
                    {
                        g_oNini->setAnimation(0);
                    }

                    //再生し終えたら値をリセットしてフラグを無効にする
                    if (DialogueAnimation_O == 31)
                    {
                        DialogueAnimation_O = 0;
                        o_DialogueAnimation = false;
                        //値をリセットしておく
                        DialogueAnimationCounter_O = 0;

                        //吹き出しのUIを移動させる
                        g_oSpeechBalloonUI->setPos(g_oSpeechBalloon->getPos().x + 530.0f, g_oSpeechBalloon->getPos().y - 110.0f);

                        //ににの画像を調整する
                        if (g_oNini != NULL && o_NiniAnimation == true)
                        {
                            g_oNini->setAnimation(0);
                        }
                    }
                }
            }
        }
    }

    //オーバー画面が作成された時のみ描画
    if (g_pOver != NULL)
    {
        renderSprite(g_pOver);
    }

    //残機を増やしておく
    Life = 5;
}

/*
* 関数名　  ：procOverEnd()
* 処理内容　：オーバー画面の終了処理
*/
void COriginalGameApp::procOverEnd()
{
    //吹き出しの画像が作成された時のみ破棄
    if (g_oSpeechBalloon != NULL)
    {
        disposeSprite(g_oSpeechBalloon);
        g_oSpeechBalloon = NULL;
    }
    //ににの画像が作成された時のみ破棄
    if (g_oNini != NULL)
    {
        disposeSprite(g_oNini);
        g_oNini = NULL;
    }
    //名前の画像が作成された時のみ破棄
    if (g_oName != NULL)
    {
        disposeSprite(g_oName);
        g_oName = NULL;
    }
    //吹き出しのUIの画像が作成された時のみ破棄
    if (g_oSpeechBalloonUI != NULL)
    {
        disposeSprite(g_oSpeechBalloonUI);
        g_oSpeechBalloonUI = NULL;
    }
    //セリフの画像が作成された時のみ破棄
    if (g_oDialogue != NULL)
    {
        disposeSprite(g_oDialogue);
        g_oDialogue = NULL;
    }

    SpeechBalloonAnimationCounter_O = 0;
    NiniAnimationCounter_O = 0;
    SpeechBalloonAnimation_O = 0;
    o_SpeechBalloonAnimation = true;
    o_NiniAnimation = true;

    DialogueAnimationCounter_O = 0 ;
    DialogueAnimation_O = 0;
    o_DialogueAnimation = true;

    //オーバー画面が作成された時のみ破棄
    if (g_pOver != NULL)
    {
        disposeSprite(g_pOver);
        g_pOver = NULL;
    }
}
