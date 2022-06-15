//------------------------
//ファイル名：TableRotate.cs
//作成者　　：中山薫
//所属		：日本電子専門学校　ゲーム制作研究科
//作成日　　：2022/02/18
//最終更新　：2022/03/01
//------------------------

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TableRotate : MonoBehaviour
{
    private int RotateSpeed = 2;        //回転スピード
    private float MoveRotate;           //回転の移動量
    private bool MaxRotate;             //回転のフラグ
    private bool RightRotate;           //回転方向のフラグ
    public int nowTable = 0;            //現在の台座
    public int nowLine = 0;             //現在のライン
    private GameObject CtlObj;          //現在動かしているオブジェクト
    private bool ObjRotation = false;   //動かすフラグ
    private bool ObjRight = false;      //動かす方向
    private float ObjMove = 0.0f;       //動かした移動量
    private bool Move = false;          //プレイヤーが動けるかのフラグ
    private float nowRotate = 0.0f;     //回転前の角度
    private float nowTableRotate = 0.0f;//回転前の角度
    private float NewY = 0.0f;          //Y軸の角度
    private float TableNewY = 0.0f;     //Y軸の角度
    public GameObject Camera;           //カメラ
    private float Timer = 0.0f;         //移動のクールタイム     
    public int[] table;                 //台座の位置
    public int[] ObjRotate;             //オブジェクトの回転数
    public GameObject L_Area;           //UI確認用
    public GameObject R_Area;           //UI確認用
    public GameObjectArray[] Line;      //回転軸の数
    [System.Serializable]               //インスペクターにクラスを表示させるのに必要
    public class GameObjectArray
    {
        public GameObject[] Table;  //台座の数
    }

    void Start()
    {

    }

    void Update()
    {
        if (LightControl.onLight == false && TimerControl.FeadinTimer == true)
        {
            //台座の回転処理
            Rotation();

            //プレイヤーの移動処理
            PlayerPos();

            //オブジェクトの回転処理
            ObjectRotate();
            //Debug.Log("Line" + nowLine);
            //Debug.Log("Table" + nowTable);
            //Debug.Log(table[0] + " " + table[1]);
            //Debug.Log(ObjRotate[0] + " " + ObjRotate[1]);

        }
    }
    /* 
     * 関数名：Rotation()
     * 処理　：台座の回転処理
     * 引数　：なし
     * 戻り値：なし
     */
    private void Rotation()
    {
        //LTボタンを押すと左、RTボタンを押すと右に回転するフラグを立てる
        if (MaxRotate == false)
        {
            if (Input.GetKey("joystick button 6"))
            {
                //左回転
                RightRotate = false;
                MaxRotate = true;
                //台座の番号をリセット
                if (nowTable == 0) nowTable = 3;
                else --nowTable;
                //現在の角度(Rotate)を代入
                nowTableRotate = this.transform.localEulerAngles.y;
            }
            else if (Input.GetKey("joystick button 7"))
            {
                //右回転
                RightRotate = true;
                MaxRotate = true;
                //台座の番号をリセット
                if (nowTable == 3) nowTable = 0;
                else ++nowTable;
                //現在の角度(Rotate)を代入
                nowTableRotate = this.transform.localEulerAngles.y;
            }
        }

        //90度回転するまで回す
        if (MoveRotate <= 90.0f && MaxRotate)
        {
            //回転
            if (RightRotate) this.transform.RotateAround
               (this.transform.position, this.transform.up,
                 360.0f / -RotateSpeed * Time.deltaTime);
            else this.transform.RotateAround
                (this.transform.position, this.transform.up,
                 360.0f / RotateSpeed * Time.deltaTime);

            //回転量を保存
            MoveRotate += 360.0f / RotateSpeed * Time.deltaTime;
        }
        else
        {
            //回転後のY軸を取得
            if (RightRotate) TableNewY = nowTableRotate - 90.0f;
            else TableNewY = nowTableRotate + 90.0f;

            //代入
            this.transform.eulerAngles = new Vector3(0.0f, TableNewY, 0.0f);

            //回転量をリセット
            MoveRotate = 0.0f;
            //フラグを降ろす
            MaxRotate = false;
        }

        //移動後のTableを記憶
        table[nowLine] = nowTable;
    }

    /* 
     * 関数名：PlayerPos()
     * 処理　：プレイヤーの移動処理
     * 引数　：なし
     * 戻り値：なし
     */
    private void PlayerPos()
    {
        //プレイヤーの位置によって回転する台座の列を変える
        for (int i = 0; i < 4; ++i)
        {
            //プレイヤーの目の前の台座と中央軸で親子関係を結ぶ
            Line[nowLine].Table[i].gameObject.transform.parent
                = this.gameObject.transform;
            //結ばれた台座を赤に変える
            Line[nowLine].Table[i].gameObject.
                GetComponent<Renderer>().material.color = Color.red;
        }

        //無回転中に十字キーで移動
        if (MaxRotate == false && Move == false && 
            Input.GetAxis("Vertical") != 0.0f && Timer == 0.0f)
        {
            //移動フラグを立てる
            Move = true;
            //現在地を取得
            float LPos = L_Area.gameObject.transform.position.x;
            float RPos = R_Area.gameObject.transform.position.x;

            //入力された方向を確定させる
            float Direction;
            if (Input.GetAxis("Vertical") < 0.0f) Direction = 1.0f;
            else Direction = -1.0f;
            //入力された方向によって前、または後ろに行く
            L_Area.gameObject.transform.position = 
                new Vector3(Mathf.Clamp(LPos + 40.0f * Direction, -70.0f, -30.0f), 10.0f, 53.0f);
            R_Area.gameObject.transform.position = 
                new Vector3(Mathf.Clamp(RPos - 40.0f * Direction, 30.0f, 70.0f), 10.0f, 53.0f);
            for (int i = 0; i < Line[nowLine].Table.Length; ++i)
            {
                Line[nowLine].Table[i].gameObject.transform.parent = null;
                Line[nowLine].Table[i].gameObject.
                    GetComponent<Renderer>().material.color = Color.yellow;
            }

            //現在のLineを取得
            nowLine = 
                (int)Mathf.Clamp((float)nowLine - Direction, 0.0f, (float)Line.Length - 1.0f);

            //保存しといたTableを代入
            nowTable = table[nowLine];
        }

        //クールタイムを設ける
        if (Move)
        {
            //移動後3F以内は移動不可
            Timer += Time.deltaTime;
            if (Timer >= 0.3f)
            {
                Timer = 0.0f;
                Move = false;
            }
        }
    }

    /* 
     * 関数名：ObjectRotate()
     * 処理　：オブジェクトの回転処理
     * 引数　：なし
     * 戻り値：なし
     */
    private void ObjectRotate()
    {
        if (MaxRotate == false && Move == false)
        {
            CtlObj = null;
            CtlObj = this.transform.GetChild(nowTable).GetChild(0).gameObject;

            //親子関係をnullチェック
            if (CtlObj != null)
            {
                if (ObjRotation == false)
                {
                    if (Input.GetKey("joystick button 4"))
                    {
                        //左回転
                        ObjRight = false;
                        ObjRotation = true;
                        if (ObjRotate[nowLine] == 0) ObjRotate[nowLine] = 7;
                        else --ObjRotate[nowLine];
                        nowRotate = CtlObj.transform.localEulerAngles.y;
                    }
                    else if (Input.GetKey("joystick button 5"))
                    {
                        //右回転
                        ObjRight = true;
                        ObjRotation = true;
                        if (ObjRotate[nowLine] == 7) ObjRotate[nowLine] = 0;
                        else ++ObjRotate[nowLine];
                        nowRotate = CtlObj.transform.localEulerAngles.y;
                    }
                }

                if (ObjRotation)
                {
                    //45度回転するまで回す
                    if (ObjMove <= 45.0f)
                    {
                        //回転
                        if (ObjRight) CtlObj.transform.RotateAround(CtlObj.transform.position, CtlObj.transform.up, 360.0f / -RotateSpeed * Time.deltaTime);
                        else CtlObj.transform.RotateAround(CtlObj.transform.position, CtlObj.transform.up, 360.0f / RotateSpeed * Time.deltaTime);

                        //回転量を保存
                        ObjMove += 360.0f / RotateSpeed * Time.deltaTime;
                    }
                    else
                    {
                        //回転後のY軸を取得
                        if (ObjRight) NewY = nowRotate - 45.0f;
                        else NewY = nowRotate + 45.0f;

                        //代入
                        CtlObj.transform.eulerAngles = new Vector3(0.0f, NewY, 0.0f);
                        //回転量をリセット
                        ObjMove = 0.0f;
                        //フラグを降ろす
                        ObjRotation = false;
                    }
                }
            }
        }
    }
}