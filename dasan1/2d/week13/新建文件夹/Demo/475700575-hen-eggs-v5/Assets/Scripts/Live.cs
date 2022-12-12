using UnityEngine;
using DG.Tweening;

public class Live : MonoBehaviour
{
    public float liveTime = 8f;

    void Start()
    {
        Destroy(gameObject, liveTime);
    }
    void OnDestroy()
    {
        //StopAllCoroutines();
        transform.DOKill();


    }
}
