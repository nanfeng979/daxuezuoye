using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class Demo1 : MonoBehaviour
{
    static string k_Name = "Player";
    public InputField nameInputField;
    void Start()
    {
        if (PlayerPrefs.HasKey(k_Name) && nameInputField != null)
        {
            nameInputField.text = PlayerPrefs.GetString(k_Name);
        }

    }

    public void OnNameChanged(string name)
    {
        //Debug.Log(name);
        PlayerPrefs.SetString(k_Name, name);
        PlayerPrefs.Save();
    }

}
