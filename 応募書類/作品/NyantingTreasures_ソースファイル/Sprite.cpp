//------------------------
//�t�@�C�����FSprite.cpp
//�쐬�ҁ@�@�F���R�O(�ꕔ����)
//����		�F���{�d�q���w�Z�@�Q�[�����쌤����
//�쐬���@�@�F2020/11/30
//�ŏI�X�V�@�F2020/02/10
//------------------------

#include "stdafx.h"
#include "COriginalGameApp.h"
#include "GameResource.h"
#include "UV.h"

/**
 * �֐��� : createSprite()
 * �������e : �w�肳�ꂽ�p�X�ɂ���摜���A�w�肳�ꂽ�T�C�Y�ō쐬����
 * ���� :	path_		�摜�̂���p�X
 *			width_		�쐬����摜�̕�
 *			height_		�쐬����摜�̍���
 * �߂�l : �쐬�����摜���Ǘ�����I�u�W�F�N�g
 */
CPicture* COriginalGameApp::createSprite (LPCWSTR path_, float width_, float height_)
{
	vector <QuadrangleTexel>  singleTexels = 
	{
		QuadrangleTexel{ { 0.0, 1.0 },{ 0.0, 0.0 },{ 1.0, 1.0 },{ 1.0, 0.0 } }	//!< �w�肷��UV���W�̔z�񂪈�̔z��
	};
	XMFLOAT2 spriteSize = { width_, height_};
	CPicture* object = NULL;

	//�v���C���[�̃A�j���[�V����
	if (path_ == Tex_Player)
	{
	object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
		{ 0.0f,0.0f,0.0f,0.0f },	//�X�v���C�g�̈ʒu
		spriteSize,					//�X�v���C�g�̃T�C�Y
		kTexelPlayer);				//�w�肷��UV���W�̔z��
	}

	//UI�̐����̃A�j���[�V����
	else if (path_ == Tex_Number)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//�X�v���C�g�̈ʒu
			spriteSize,					//�X�v���C�g�̃T�C�Y
			kTexelNumber);		//�w�肷��UV���W�̔z��
	}

	//�����o���̃A�j���[�V����
	else if (path_ == Tex_SpeechBalloon)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//�X�v���C�g�̈ʒu
			spriteSize,					//�X�v���C�g�̃T�C�Y
			kTexelSpeechBalloon);		//�w�肷��UV���W�̔z��
	}
	//�ɂɂ̃A�j���[�V����
	else if (path_ == Tex_Nini)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//�X�v���C�g�̈ʒu
			spriteSize,					//�X�v���C�g�̃T�C�Y
			kTexelNini);				//�w�肷��UV���W�̔z��
	}
	//�ɂɂ̊���}�[�N�̃A�j���[�V����
	else if (path_ == Tex_NiniEmotion)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//�X�v���C�g�̈ʒu
			spriteSize,					//�X�v���C�g�̃T�C�Y
			kTexelNiniEmotion);				//�w�肷��UV���W�̔z��
	}
	//���O�̃A�j���[�V����
	else if (path_ == Tex_Name)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//�X�v���C�g�̈ʒu
			spriteSize,					//�X�v���C�g�̃T�C�Y
			kTexelName);				//�w�肷��UV���W�̔z��
	}
	//����p�����o���̃A�j���[�V����
	else if (path_ == Tex_SpeechBalloonSelect)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//�X�v���C�g�̈ʒu
			spriteSize,					//�X�v���C�g�̃T�C�Y
			kTexelSpeechBalloonSelect);				//�w�肷��UV���W�̔z��
	}

	//����p�����o���̃A�j���[�V����
	else if (path_ == Tex_LifeUI)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//�X�v���C�g�̈ʒu
			spriteSize,					//�X�v���C�g�̃T�C�Y
			kTexelLifeUI);				//�w�肷��UV���W�̔z��
	}

	//�Z���t�̃A�j���[�V����
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
			{ 0.0f,0.0f,0.0f,0.0f },	//�X�v���C�g�̈ʒu
			spriteSize,					//�X�v���C�g�̃T�C�Y
			kTexelDialogue);			//�w�肷��UV���W�̔z��
	}
	
	//�u���b�N�̃A�j���[�V����
	else if (path_ == Tex_Block)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//�X�v���C�g�̈ʒu
			spriteSize,					//�X�v���C�g�̃T�C�Y
			kTexelBlock);				//�w�肷��UV���W�̔z��
	}

	//�󔠂̃A�j���[�V����
	else if (path_ == Tex_Treasure)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//�X�v���C�g�̈ʒu
			spriteSize,					//�X�v���C�g�̃T�C�Y
			kTexelBlock);				//�w�肷��UV���W�̔z��
	}

	// ����ȊO�͊�{�I�ȍ쐬
	else
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< �X�v���C�g�̈ʒu
			spriteSize,					//!< �X�v���C�g�̃T�C�Y
			singleTexels);				//!< �w�肷��UV���W�̔z��
	}
	return object;
}

CFont* COriginalGameApp::createFont(LPCWSTR path_, int digits_, float width_, float height_)
{
	XMFLOAT2 spriteSize = { width_, height_ };
	CFont* objects = NULL;

	return objects;
}
