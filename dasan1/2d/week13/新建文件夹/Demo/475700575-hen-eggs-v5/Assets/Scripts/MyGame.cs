using UnityEngine.UI;
using UnityEngine;
//using DG.Tweening;
public class MyGame : MonoBehaviour
{
    public Text info;
    
    public MoveTo move;
     RectTransform m_canvasRect;
    CanSelect m_curSelect;
    GameObject m_group_eggs;

    GameObject m_group_hens;
    GameObject m_group_cocks;


    // Start is called before the first frame update
    void Start()
    {
        m_canvasRect=GetComponent<RectTransform>();
        m_group_eggs = GameObject.FindWithTag("Eggs");
        m_group_hens = GameObject.FindWithTag("Hens");
        m_group_cocks = GameObject.FindWithTag("Cocks");

    }

    void UpdateInfo()
    {
        info.text = "鸡蛋：" + m_group_eggs.transform.childCount.ToString() +
        "  母鸡：" + m_group_hens.transform.childCount.ToString() +
         "  公鸡：" + m_group_cocks.transform.childCount.ToString();

    }
    public void ChangeColor(CanSelect s, Color c)
    {
        Image img = s.GetComponent<Image>();
        img.color = c;

    }
    public void Select(Vector2 clickedPos)
    {
        CanSelect[] cs = FindObjectsOfType<CanSelect>();
        foreach (CanSelect s in cs)
        {
            Vector2 pos = s.transform.localPosition;
            Vector2 dv = clickedPos - pos;
            if (dv.magnitude < 100 && m_curSelect != s && s.enabled)
            {
                if (m_curSelect) ChangeColor(m_curSelect, Color.white);
                m_curSelect = s;
                ChangeColor(m_curSelect, Color.red);
                return;
            }
        }
    }

    void Update()
    {
        UpdateInfo();
        Vector2 pos = Input.mousePosition;
        //   Vector2 position2 = Camera.main.ScreenToWorldPoint(pos); //mainCamera通过设置public Camera类型属性在检视器中获取游戏主摄像机
        // Debug.Log("screen w:" + Screen.width + ", h:" + Screen.height);
        // Debug.Log("click pos x:" + pos.x + ",pos y:" + pos.y);

        // float X = Input.mousePosition.x - Screen.width / 2f;
        // float Y = Input.mousePosition.y - Screen.height / 2f;
        // Vector2 tranPos = new Vector2(X, Y);

        Vector2 tranPos=Vector2.zero;
        if (RectTransformUtility.ScreenPointToLocalPointInRectangle(m_canvasRect, pos, null, out tranPos))
        {
           // Debug.Log(tranPos);
        }
        bool isKeyUp = Input.GetMouseButtonUp(1);        // 按下之后松开时会返回true

        if (isKeyUp)
            Select(tranPos);

        isKeyUp = Input.GetMouseButtonUp(0);
        if (isKeyUp && m_curSelect != null)
            m_curSelect.Goto(tranPos);

    }
}
