using DG.Tweening;
using UnityEngine;
using UnityEngine.UI;
namespace MyGame_2048
{
    public class CardMgr : MonoBehaviour
    {
        RectTransform rectTransform;
        // Start is called before the first frame update
        void Start()
        {
            rectTransform = GetComponent<RectTransform>();
            CreateEffect(new Vector2(0, 80), 0.25f, 1f);

        }

        public void CreateEffect(Vector2 pos, float scale, float duration)
        {
            //transform.DOScale(Vector3.one*scale, duration);
            //transform.DOMove(pos, duration);
            rectTransform.DOAnchorPos(pos, duration);
            rectTransform.DOPunchScale(Vector3.one * scale, duration).OnComplete(OnEndAniamte);

        }
        void OnEndAniamte()
        {
            Debug.LogFormat("OnEndAniamte");
        }

    }
}
