using UnityEngine;

public class Walk : MonoBehaviour
{
    public float step = 200f;
    Vector2[] m_dirs = { Vector2.left, Vector2.up, Vector2.right, Vector2.down };
    MoveTo m_move;
    void Start()
    {
        m_move = GetComponent<MoveTo>();
        m_move.OnArrived += MakeTarget;
        MakeTarget();
    }
    void MakeTarget()
    {
        var canSelect = GetComponent<CanSelect>();
         if (!this.enabled|| canSelect && canSelect.enabled)
            return;
       
        Vector3 dir = m_dirs[Random.Range(0, 4)];
        Vector3 pos = transform.localPosition + step * dir;
        m_move.SetTarget(pos,1);
    }



}
