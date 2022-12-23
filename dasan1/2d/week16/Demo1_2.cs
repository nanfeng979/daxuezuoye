using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

/*
现在有玩家信息类，有名字，年龄，攻击力，防御力等成员。另有装备信息类，装备类中有id，数量两个成员。
现在为其封装两个方法，一个用来存储数据，一个用来读取数据
注意，装备是个list，所以存储时候需要遍历
https://blog.csdn.net/qq_32175379/article/details/121199932
*/

public class Item
{
    public int id;
    public int num;
}

public class Player
{
    public string name;
    public int age;
    public int atk;
    public int def;
    //拥有的装备信息
    public List<Item> itemList;

    //这个变量 是一个 存储和读取的一个唯一key标识
    private string keyName;

    /// <summary>
    /// 存储数据
    /// </summary>
    public void Save()
    {
        PlayerPrefs.SetString(keyName +"_name", name);
        PlayerPrefs.SetInt(keyName + "_age", age);
        PlayerPrefs.SetInt(keyName + "_atk", atk);
        PlayerPrefs.SetInt(keyName + "_def", def);
        //存储有多少个装备
        PlayerPrefs.SetInt(keyName + "_ItemNum", itemList.Count);
        for (int i = 0; i < itemList.Count; i++)
        {
            //存储每一个装备的信息
            PlayerPrefs.SetInt(keyName + "_itemID" + i, itemList[i].id);
            PlayerPrefs.SetInt(keyName + "_itemNum" + i, itemList[i].num);
        }

        PlayerPrefs.Save();
    }
    /// <summary>
    /// 读取数据
    /// </summary>
    public void Load(string keyName)
    {
        //记录你传入的标识
        this.keyName = keyName;

        name = PlayerPrefs.GetString(keyName + "_name", "JOIN");
        age = PlayerPrefs.GetInt(keyName + "_age", 18);
        atk = PlayerPrefs.GetInt(keyName + "_atk", 10);
        def = PlayerPrefs.GetInt(keyName + "_def", 5);

        //得到有多少个装备
        int num = PlayerPrefs.GetInt(keyName + "_ItemNum", 0);
        //初始化容器
        itemList = new List<Item>();
        Item item;
        for (int i = 0; i < num; i++)
        {
            item = new Item();
            item.id = PlayerPrefs.GetInt(keyName + "_itemID" + i);
            item.num = PlayerPrefs.GetInt(keyName + "_itemNum" + i);
            itemList.Add(item);
        }
    }
}

public class Demo1_2 : MonoBehaviour
{
 

    // Start is called before the first frame update
    void Start()
    {

        //现在有玩家信息类，有名字，年龄，攻击力，防御力等成员
        //现在为其封装两个方法，一个用来存储数据，一个用来读取数据

        Player p = new Player();
        p.Load("Player");
        print("Player姓名："+p.name);
        print("Player年龄："+p.age);
        print("Player攻击力："+p.atk);
       print("Player防御力："+p.def);

       p.name = "TOM";
       p.age = 22;
       p.atk = 40;
       p.def = 10;
       // 改了过后存储
        p.Save();
 
    
 
        Player p1 = new Player();
        p1.Load("Player1");
        p1.Save();
          print("Player1姓名："+p1.name);
        print("Player1年龄："+p1.age);
        print("Player1攻击力："+p1.atk);
       print("Player1防御力："+p1.def);


        Player p2 = new Player();
        p2.Load("Player2");
        p2.Save();


        //装备信息
        print("添加装备前，Player的装备数："+p.itemList.Count);
        // for (int i = 0; i < p.itemList.Count; i++)
        // {
        //    print("道具ID：" + p.itemList[i].id);
        //    print("道具数量：" + p.itemList[i].num);
        // }

       // 为玩家添加一个装备
        Item item = new Item();
        item.id = 1;
        item.num = 1;
        p.itemList.Add(item);
        item = new Item();
        item.id = 2;
        item.num = 2;
        p.itemList.Add(item);

          //装备信息
        print("添加装备后，Player的装备数："+p.itemList.Count);
    //   for (int i = 0; i < p.itemList.Count; i++)
    //     {
    //        print("道具ID：" + p.itemList[i].id);
    //        print("道具数量：" + p.itemList[i].num);
    //     }
        p.Save();
      print("每次添加后保存后Player的装备数："+p.itemList.Count);

    }

    // Update is called once per frame
    void Update()
    {
        
    }
}


