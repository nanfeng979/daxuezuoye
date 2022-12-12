using UnityEngine;
using UnityEngine.UI;

public class Grow : MonoBehaviour
{
    Image m_image;
    public Sprite[] m_sprites;
    public float m_time;

    int idx = 0;
    // Start is called before the first frame update
    void Start()
    {
        m_image = GetComponent<Image>();
        InvokeRepeating("ChangeSprite", m_time, m_time);

    }

    void ChangeSprite()
    {
        CanSelect canSelect = GetComponent<CanSelect>();
        if (canSelect)
            canSelect.enabled = true;

        idx += 1;
        if (idx >= m_sprites.Length)
            idx = m_sprites.Length - 1;
        m_image.sprite = m_sprites[idx];

    }

}
