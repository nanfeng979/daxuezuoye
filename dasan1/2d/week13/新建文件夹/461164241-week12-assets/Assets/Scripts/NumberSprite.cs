using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;
namespace MyGame_2048
{
    /// <inheritdoc />
    /// <summary>
    /// 定义精灵行为
    /// </summary>
    public class NumberSprite : MonoBehaviour
    {
        private Image image;

        /// <summary>
        /// 获取当前组件上上的图片
        /// </summary>
        private void Awake()
        {
            image = GetComponent<Image>();
        }

        /// <summary>
        /// 设置图片
        /// </summary>
        /// <param name="number"></param>
        public void SetImage(int number)
        {
           
            image.sprite = ResourceManager.LoadSprite(number);
        }


        /// <summary>
        /// 生成特效果
        /// </summary>
        public void CreateEffect()
        {
            // gameObject.transform.DOScale(Vector3.zero, 0.3f);
              transform.DOPunchScale(Vector3.one * 0.25f, 0.3f);
        }
    }
}