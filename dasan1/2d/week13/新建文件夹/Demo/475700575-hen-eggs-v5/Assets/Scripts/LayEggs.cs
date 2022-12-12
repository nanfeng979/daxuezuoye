using UnityEngine;
using UnityEngine.UI;
public class LayEggs : MonoBehaviour
{
    public GameObject[] eggsPrefabs;
    public string groupName = "Eggs";
     GameObject m_group;
    void Start()
    {
        m_group = GameObject.FindWithTag(groupName);
    }
    public void MakeEgg()
    {
        // int eggstyle = Random.Range(0, 3)+1;
        // Sprite sp=Resources.Load<Sprite>("egg" + eggstyle);
        int size = eggsPrefabs.Length;
        GameObject egg = GameObject.Instantiate(eggsPrefabs[Random.Range(0, size)]);
        egg.transform.SetParent(m_group.transform);
        egg.transform.position = transform.position + new Vector3(50f, -25f, 0f);
    }
}
