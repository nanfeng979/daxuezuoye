using UnityEngine;

public class CanSelect : MonoBehaviour
{
    Walk m_walk;
    MoveTo m_move;

    void Start(){
        m_walk=GetComponent<Walk>();
        m_move=GetComponent<MoveTo>();
        m_move.OnArrived+=LayEgg;
     }

    public void Goto(Vector2 pos){
        this.enabled=false;
        m_move.SetTarget(pos,1.6f);
        if(m_walk) m_walk.enabled=false;
    }

    void LayEgg()
    {
        LayEggs le = GetComponent<LayEggs>();
        if (le) le.MakeEgg();
        this.enabled=true;
        if(m_walk) m_walk.enabled=false;
    }
    
}
