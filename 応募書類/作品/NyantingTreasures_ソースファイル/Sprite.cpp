//------------------------
//ファイル名：Sprite.cpp
//作成者　　：中山薫(一部改変)
//所属		：日本電子専門学校　ゲーム制作研究科
//作成日　　：2020/11/30
//最終更新　：2020/02/10
//------------------------

#include "stdafx.h"
#include "COriginalGameApp.h"
#include "GameResource.h"
#include "UV.h"

/**
 * 関数名 : createSprite()
 * 処理内容 : 指定されたパスにある画像を、指定されたサイズで作成する
 * 引数 :	path_		画像のあるパス
 *			width_		作成する画像の幅
 *			height_		作成する画像の高さ
 * 戻り値 : 作成した画像を管理するオブジェクト
 */
CPicture* COriginalGameApp::createSprite (LPCWSTR path_, float width_, float height_)
{
	vector <QuadrangleTexel>  singleTexels = 
	{
		QuadrangleTexel{ { 0.0, 1.0 },{ 0.0, 0.0 },{ 1.0, 1.0 },{ 1.0, 0.0 } }	//!< 指定するUV座標の配列が一つの配列
	};
	XMFLOAT2 spriteSize = { width_, height_};
	CPicture* object = NULL;

	//プレイヤーのアニメーション
	if (path_ == Tex_Player)
	{
	object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
		{ 0.0f,0.0f,0.0f,0.0f },	//スプライトの位置
		spriteSize,					//スプライトのサイズ
		kTexelPlayer);				//指定するUV座標の配列
	}

	//UIの数字のアニメーション
	else if (path_ == Tex_Number)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelNumber);		//指定するUV座標の配列
	}

	//吹き出しのアニメーション
	else if (path_ == Tex_SpeechBalloon)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelSpeechBalloon);		//指定するUV座標の配列
	}
	//ににのアニメーション
	else if (path_ == Tex_Nini)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelNini);				//指定するUV座標の配列
	}
	//ににの感情マークのアニメーション
	else if (path_ == Tex_NiniEmotion)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelNiniEmotion);				//指定するUV座標の配列
	}
	//名前のアニメーション
	else if (path_ == Tex_Name)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelName);				//指定するUV座標の配列
	}
	//分岐用吹き出しのアニメーション
	else if (path_ == Tex_SpeechBalloonSelect)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelSpeechBalloonSelect);				//指定するUV座標の配列
	}

	//分岐用吹き出しのアニメーション
	else if (path_ == Tex_LifeUI)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelLifeUI);				//指定するUV座標の配列
	}

	//セリフのアニメーション
	else if (path_ == Tex_Dialogue0_1  || path_ == Tex_Dialogue0_2  || path_ == Tex_Dialogue0_3  || path_ == Tex_Dialogue0_4  || path_ == Tex_Dialogue0_5  ||
		     path_ == Tex_Dialogue0_6  || path_ == Tex_Dialogue0_7  || path_ == Tex_Dialogue0_8  || path_ == Tex_Dialogue0_9  || path_ == Tex_Dialogue0_10 ||
			 path_ == Tex_Dialogue0_11 || path_ == Tex_Dialogue0_12 || path_ == Tex_Dialogue0_13 || path_ == Tex_Dialogue0_14 || path_ == Tex_Dialogue0_15 ||
		     path_ == Tex_Dialogue0_16 || path_ == Tex_Dialogue0_17 || path_ == Tex_Dialogue0_18 || path_ == Tex_Dialogue0_19 || path_ == Tex_Dialogue0_20 ||
		     path_ == Tex_Dialogue0_21 || path_ == Tex_Dialogue0_22 ||
		 	 path_ == Tex_Dialogue1_1  || path_ == Tex_Dialogue1_2  || path_ == Tex_Dialogue1_3  || path_ == Tex_Dialogue1_4  || path_ == Tex_Dialogue1_5  ||
			 path_ == Tex_Dialogue1_6  || path_ == Tex_Dialogue1_7  || path_ == Tex_Dialogue1_8  || path_ == Tex_Dialogue1_9  || path_ == Tex_Dialogue1_10 ||
		 	 path_ == Tex_Dialogue1_11 || path_ == Tex_Dialogue1_12 || path_ == Tex_Dialogue1_13 || path_ == Tex_Dialogue1_14 || path_ == Tex_Dialogue1_15 ||
		     path_ == Tex_Dialogue2_1  || path_ == Tex_Dialogue2_2  || path_ == Tex_Dialogue2_3  || path_ == Tex_Dialogue2_4  || path_ == Tex_Dialogue2_5  ||
		     path_ == Tex_Dialogue2_6  || path_ == Tex_Dialogue2_7  || path_ == Tex_Dialogue2_9  || path_ == Tex_Dialogue2_10 || 
	  	     path_ == Tex_Dialogue2_11 || path_ == Tex_Dialogue2_12 || path_ == Tex_Dialogue2_13 ||
		     path_ == Tex_Dialogue3_1  || path_ == Tex_Dialogue3_2  || path_ == Tex_Dialogue3_3)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelDialogue);			//指定するUV座標の配列
	}
	
	//ブロックのアニメーション
	else if (path_ == Tex_Block)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelBlock);				//指定するUV座標の配列
	}

	//宝箱のアニメーション
	else if (path_ == Tex_Treasure)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelBlock);				//指定するUV座標の配列
	}

	// それ以外は基本的な作成
	else
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< スプライトの位置
			spriteSize,					//!< スプライトのサイズ
			singleTexels);				//!< 指定するUV座標の配列
	}
	return object;
}

CFont* COriginalGameApp::createFont(LPCWSTR path_, int digits_, float width_, float height_)
{
	XMFLOAT2 spriteSize = { width_, height_ };
	CFont* objects = NULL;

	return objects;
}
