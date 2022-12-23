using System.Collections;
using System.Collections.Generic;
using UnityEngine;
 

[CreateAssetMenu(fileName = "Data",
    menuName = "MyData/RoleData", order =1)] //作用在 Assets 文件夹下，鼠标右键，菜单栏中添加一个按钮项，菜单名为 menuName，并执行生成名为 fileName 的脚本，order 为按钮显示顺序
public class RoleData : ScriptableObject
{
    public string Tag;
    public string Name;
    public int HP;
    public int Power;
}

 
