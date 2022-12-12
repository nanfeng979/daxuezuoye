using System.Collections;
using System.Collections.Generic;
using NUnit.Framework;
using UnityEngine;
using UnityEngine.TestTools;

using MyGame_2048;


public class T01_BaseDemo
{


    [Test]
    public void TC00_Queue()
    {
        Queue<int> data = new Queue<int>();
        data.Enqueue(2);
        data.Enqueue(2);
        int first = data.Dequeue();
        int next = data.Peek();
        Assert.AreEqual(2, first);
        Assert.AreEqual(2, next);
        data.Dequeue();
        //int d = data.Peek ();
        // Assert.IsNull (d);


    }

    [Test]
    public void TC01_Array()
    {
        int size = 4;

        int[,] data = new int[size, size];//默认值为0;  
        Assert.AreEqual(0, data[0, 0]);
        




    }

}

