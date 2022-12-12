using UnityEngine;
using UnityEngine.UI;

public class MakeNext : MonoBehaviour
{
    public GameObject nextPrefab;
    public string groupName = "";
    public float delayTime = 8f;
    GameObject m_group;
    // Start is called before the first frame update
    void Start()
    {
        m_group = GameObject.FindWithTag(groupName);
        Invoke("MakeObj", delayTime);
    }
    void MakeObj()
    {
        if (nextPrefab == null)
            return;
        GameObject obj = GameObject.Instantiate(nextPrefab);
        obj.transform.SetParent(m_group.transform);
        obj.transform.position = transform.position;

    }



}
