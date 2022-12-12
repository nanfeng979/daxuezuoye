using System;
using UnityEngine;
using DG.Tweening;
using UnityEngine.Events;

// [Serializable]
// public class OnMoved : UnityEvent { }
public class MoveTo : MonoBehaviour
{
    static float MAX_STEP=300f;
    public UnityAction OnArrived;
    public float speed = 10f;
    Vector2 m_target;


    public bool stoped;

    void Start()
    {
        stoped = true;

    }
    public void SetTarget(Vector2 target, float delay)
    {
        stoped = false;
        var pos = target;
        if (pos.x > MAX_STEP) pos.x = MAX_STEP;
        if (pos.x < -MAX_STEP) pos.x = -MAX_STEP;
        if (pos.y > MAX_STEP) pos.y = MAX_STEP;
        if (pos.y < -MAX_STEP) pos.y = -MAX_STEP;
        m_target = pos;
        SetFlip();
        transform.DOLocalMove(m_target, delay).OnComplete(OnMoved);
    }
    void OnMoved()
    {
        stoped = true;
        OnArrived?.Invoke();

    }
    public void SetFlip()
    {
        Vector2 pos = transform.localPosition;
        Vector2 df = m_target - pos;
        var s = transform.localScale;
        if (m_target.x < pos.x)
            s.x = -1;
        else
            s.x = 1;
        transform.localScale = s;
    }
    // void Update()
    // {
    //     Vector2 pos = transform.localPosition;
    //     Vector2 dv = (m_target - pos);
    //     stoped = false;
    //     if (dv.magnitude < 5f)
    //     {
    //         dv = Vector2.zero;
    //         stoped = true;
    //     }
    //     else
    //     {
    //         dv = dv.normalized;
    //     }
    //     if (dv.magnitude > 1f) SetFlip();
    //     transform.localPosition = pos + dv * speed * Time.deltaTime;

    // }

}
