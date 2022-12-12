using UnityEngine;
using NUnit.Framework;


using MyGame_2048;


public class T02_GameCore
{
    GameCore gameCore;
    [SetUp]
    public void SetUp()
    {
        gameCore = new GameCore();
        //Debug.Log ("create new gamecore");

    }
    [TearDown]
    public void TearDown()
    {
        //  GameObject.DestroyImmediate(m_tile.gameObject);
    }

    [Test]
    public void TC01_RandomGenerateNumber()
    {

        Location loc;
        int newNumber;
        gameCore.GenerateNumber(out loc, out newNumber);

        Assert.IsTrue(newNumber == 1 || newNumber == 2);
        Assert.IsTrue(loc.RowIndex < 4 && loc.RowIndex >= 0);
        Assert.IsTrue(loc.ColIndex < 4 && loc.ColIndex >= 0);
        //Debug.Log(newNumber);
        //Debug.Log(loc);

    }
    [Test]
    public void TC02_DemoGenerateNumber()
    {

        Location loc;
        int newNumber;
        gameCore.GenerateNumber(out loc, out newNumber, true);

        Assert.IsTrue(newNumber == 1);
        Assert.IsTrue(loc.RowIndex == 0 && loc.ColIndex == 0);

        gameCore.GenerateNumber(out loc, out newNumber, true);
        // Debug.Log(newNumber);
        // Debug.Log(loc);
        Assert.IsTrue(newNumber == 1);
        Assert.IsTrue(loc.RowIndex == 0 && loc.ColIndex == 1);

        int freeNum = gameCore.CalculateEmpty();
        Assert.AreEqual(freeNum, 14);


    }
    [Test]
    public void TC03_MoveRight()
    {

        Location loc;
        int newNumber;
        gameCore.GenerateNumber(out loc, out newNumber, true);
        gameCore.GenerateNumber(out loc, out newNumber, true);
        gameCore.Move(MoveDirection.Right);

        Assert.IsTrue(gameCore.Data[0, 3] == 2);
        Assert.IsTrue(gameCore.IsChange);



    }
    [Test]
    public void TC03_MoveLeft()
    {

        Location loc;
        int newNumber;
        gameCore.GenerateNumber(out loc, out newNumber, true);
        gameCore.GenerateNumber(out loc, out newNumber, true);
        gameCore.Move(MoveDirection.Left);

        Assert.IsTrue(gameCore.Data[0, 0] == 2);
        Assert.IsTrue(gameCore.IsChange);



    }

}

