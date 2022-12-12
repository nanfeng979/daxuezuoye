using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;
namespace MyGame_2048
{

/// <summary>
/// 控制游戏逻辑
/// </summary>
public class GameMgr : MonoBehaviour, IPointerDownHandler, IDragHandler
{
    GameCore gameCore;

     NumberSprite[,] numberSprites;

     Vector2 startPoint;


     bool isDown;


    /// <summary>
    /// 初始化操作
    /// </summary>
    private void Awake()
    {
        gameCore = new GameCore();
        numberSprites = new NumberSprite[GameCore.SIZE, GameCore.SIZE];
        CreateInitMap();
    }


    /// <summary>
    /// 开始游戏的时候默认创建2个数字
    /// </summary>
    private void Start()
    {
        GenerateNewNumber();
        GenerateNewNumber();
    }


    /// <summary>
    /// 检测格子变化则更新地图
    /// </summary>
    private void Update()
    {
        if (gameCore.IsChange)
        {
            UpdateMap();
            GenerateNewNumber();
            if (gameCore.IsOver())
            {
                // 游戏结束
            }
            gameCore.IsChange = false;
        }
    }


    /// <summary>
    /// 更新地图
    /// </summary>
    private void UpdateMap()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                numberSprites[i, j].SetImage(gameCore.Data[i, j]);
            }
        }
    }


    /// <summary>
    /// 创建游戏4*4初始格子
    /// </summary>
    private void CreateInitMap()
    {
        for (int i = 0; i <GameCore.SIZE; i++)
        {
            for (int j = 0; j < GameCore.SIZE; j++)
            {
                CreateSprite(i, j);
            }
        }
    }


    /// <summary>
    /// 生成新数字
    /// </summary>
    private void GenerateNewNumber()
    {
        Location location;
        int number;
        gameCore.GenerateNumber(out location, out number);
        numberSprites[location.RowIndex, location.ColIndex].SetImage(number);
        numberSprites[location.RowIndex, location.ColIndex].CreateEffect();
        
    }


    /// <summary>
    /// 根据坐标创建精灵格子
    /// </summary>
    /// <param name="r">x坐标</param>
    /// <param name="c">y坐标</param>
    private void CreateSprite(int r, int c)
    {
        GameObject go = new GameObject(string.Format("{0}-{1}", r, c));
        go.transform.SetParent(transform, false);

        Image unused = go.AddComponent<Image>();
        NumberSprite card = go.AddComponent<NumberSprite>();
        numberSprites[r, c] = card;
        card.SetImage(0);
    }

    /// <inheritdoc />
    /// <summary>
    /// 点击事件
    /// </summary>
    /// <param name="eventData"></param>
    public void OnPointerDown(PointerEventData eventData)
    {
        startPoint = eventData.position;
        isDown = true;
    }


    /// <inheritdoc />
    /// <summary>
    /// 拖拽操作
    /// </summary>
    /// <param name="eventData"></param>
    public void OnDrag(PointerEventData eventData)
    {
        if (!isDown)
        {
            return;
        }


        Vector3 offset = eventData.position - startPoint;
        float x = Mathf.Abs(offset.x);
        float y = Mathf.Abs(offset.y);


        MoveDirection? dir = null;
        // 左右 大于50像素有效，防止误触
        if (x > y && x > 50)
        {
            dir = offset.x > 0 ? MoveDirection.Right : MoveDirection.Left;
        }
        // 上下
        else if (x < y && y > 50)
        {
            dir = offset.y > 0 ? MoveDirection.Up : MoveDirection.Down;
        }

        if (dir != null)
        {
            gameCore.Move(dir.Value);
            isDown = false;
        }
    }
}
}