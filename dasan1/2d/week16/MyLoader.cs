using System.Collections;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

//https://docs.unity3d.com/ScriptReference/AsyncOperation-progress.html
public class MyLoader : MonoBehaviour
{
    public Text text;
    public Slider slider;

    WaitForSeconds m_delay_3s;

    void Start()
    {
        m_delay_3s= new WaitForSeconds(3f);
        StartCoroutine(LoadScene());

        
    }

   IEnumerator LoadScene()  {
       yield return  m_delay_3s;

        //AsyncOperation asyncOperation = SceneManager.LoadSceneAsync("main");
        AsyncOperation asyncOperation = SceneManager.LoadSceneAsync(SceneManager.GetActiveScene().buildIndex+1);
        asyncOperation.allowSceneActivation = false;

        while (!asyncOperation.isDone)     {
            
            text.text = "Loading progress: " + (asyncOperation.progress * 100) + "%";
             slider.value=asyncOperation.progress;
            if (asyncOperation.progress >= 0.9f)   {
                slider.value=1f;
                text.text = "Press the space bar to continue";
                if (Input.GetKeyDown(KeyCode.Space))
                       asyncOperation.allowSceneActivation = true;
            }
           

            
            yield return null;
        }
    }

}
