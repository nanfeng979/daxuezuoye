using System;
using System.Collections.Generic;

namespace MyGame_2048
{
    /// <summary>
    /// 游戏核心算法类，与平台无关
    /// </summary>
    public class GameCoreOld
    {
        public static int SIZE = 4;
        private int[,] m_data;
        private int[] m_mergeArray;
        private int[] m_removeZeroArray;
        private int[,] m_oldData;
        Random m_random;
        List<Location> m_emptyLocations; //布局
        public int[,] Data
        {
            get { return m_data; }
        }

        public GameCoreOld(int Size = 4)
        {
            GameCore.SIZE = Size;
            //实例化4*4
            m_data = new int[SIZE, SIZE];
            //new 数组  每行有多少个
            m_mergeArray = new int[SIZE];// new int[m_data.GetLength(0)];
            //去零数组
            m_removeZeroArray = new int[SIZE];
            //布局
            m_emptyLocations = new List<Location>(SIZE * SIZE);
            //随机数
            m_random = new Random();
            //原来的二维数组
            m_oldData = new int[SIZE, SIZE];
        }

        private void RemoveZero()
        {
            Array.Clear(m_removeZeroArray, 0, SIZE);

            int index = 0;
            foreach (var item in m_mergeArray)
            {
                if (item != 0)
                    m_removeZeroArray[index++] = item;
            }

            m_removeZeroArray.CopyTo(m_mergeArray, 0);
        }


        /// <summary>
        /// 合并数字
        /// </summary>
        private void Merge()
        {
            RemoveZero(); //去零
            for (int i = 0; i < m_mergeArray.Length - 1; i++)
            {
                if (m_mergeArray[i] != 0 && m_mergeArray[i] == m_mergeArray[i + 1])
                {
                    m_mergeArray[i] += 1;// m_mergeArray[i + 1]
                    m_mergeArray[i + 1] = 0;
                }
            }

            RemoveZero();
        }

        /// <summary>
        /// 上移
        /// </summary>
        private void MoveUp()
        {
            for (int c = 0; c < SIZE; c++)//m_data.GetLength(1)
            {
                for (int r = 0; r < SIZE; r++)//m_data.GetLength(0)
                    m_mergeArray[r] = m_data[r, c];

                Merge();

                for (int r = 0; r < SIZE; r++)
                    m_data[r, c] = m_mergeArray[r];
            }
        }
        /// <summary>
        /// 左移
        /// </summary>
        private void MoveLeft()
        {
            for (int r = 0; r < SIZE; r++)
            {
                for (int c = 0; c < SIZE; c++)
                    m_mergeArray[c] = m_data[r, c];

                Merge();

                for (int c = 0; c < SIZE; c++)
                    m_data[r, c] = m_mergeArray[c];
            }
        }

        /// <summary>
        /// 下移
        /// </summary>
        private void MoveDown()
        {
            for (int c = 0; c < SIZE; c++)
            {
                for (int r = SIZE - 1; r >= 0; r--)
                {
                    m_mergeArray[SIZE - 1 - r] = m_data[r, c];
                }

                Merge();

                for (int r = SIZE - 1; r >= 0; r--)
                {
                    m_data[r, c] = m_mergeArray[SIZE - 1 - r];
                }
            }
        }




        /// <summary>
        /// 右移
        /// </summary>
        private void MoveRight()
        {
            for (int r = 0; r < SIZE; r++)
            {
                for (int c = SIZE - 1; c >= 0; c--)
                    m_mergeArray[SIZE - 1 - c] = m_data[r, c];

                Merge();

                for (int c = SIZE - 1; c >= 0; c--)
                    m_data[r, c] = m_mergeArray[SIZE - 1 - c];
            }
        }

        /// <summary>
        /// 地图是否发生改变
        /// </summary>
        public bool IsChange { get; set; }


        /// <summary>
        /// 移动
        /// </summary>
        /// <param name="direction"></param>
        /// <exception cref="ArgumentOutOfRangeException"></exception>
        public void Move(MoveDirection direction)
        {
            //移动前备份数据  
            Array.Copy(m_data, m_oldData, m_data.Length);

            switch (direction)
            {
                case MoveDirection.Up:
                    MoveUp();
                    break;
                case MoveDirection.Down:
                    MoveDown();
                    break;
                case MoveDirection.Left:
                    MoveLeft();
                    break;
                case MoveDirection.Right:
                    MoveRight();
                    break;
                default:
                    throw new ArgumentOutOfRangeException("direction", direction, null);
            }

            //移动后对比  重构 --> 提取方法
            CheckDataChange();
        }


        /// <summary>
        /// 检测地图是否发生变化
        /// </summary>
        private void CheckDataChange()
        {
            for (int r = 0; r < m_data.GetLength(0); r++)
            {
                for (int c = 0; c < m_data.GetLength(1); c++)
                {
                    if (m_data[r, c] != m_oldData[r, c])
                    {
                        IsChange = true; //发生改变
                        return;
                    }
                }
            }
        }

        /*
            在空白位置上， 随机生成数字(2 (80%)     4(20%))
         * 1.计算空白位置
         * 2.随机选择位置
         * 3.随机生成数字
         */




        /// <summary>
        /// 计算空格子
        /// </summary>
        public int CalculateEmpty()
        {
            m_emptyLocations.Clear();
            for (int r = 0; r < m_data.GetLength(0); r++)
            {
                for (int c = 0; c < m_data.GetLength(1); c++)
                {
                    if (m_data[r, c] == 0)
                    {
                        m_emptyLocations.Add(new Location(r, c));
                    }
                }
            }
            return m_emptyLocations.Count;
        }


        /// <summary>
        /// 生成新数字
        /// </summary>
        public void GenerateNumber(out Location loc, out int newNumber, bool isDemo = false)
        {
            CalculateEmpty();

            if (m_emptyLocations.Count > 0)
            {
                int emptyLocIndex = 0;
                if (!isDemo)
                    emptyLocIndex = m_random.Next(0, m_emptyLocations.Count); //0,15


                loc = m_emptyLocations[emptyLocIndex];
                newNumber = 1;
                if (!isDemo)
                    newNumber = m_random.Next(0, 10) < 3 ? 2 : 1;
                m_data[loc.RowIndex, loc.ColIndex] = newNumber;

                //将该位置清除
                m_emptyLocations.RemoveAt(emptyLocIndex);
            }
            else
            {
                newNumber = -1;
                loc = new Location(-1, -1);
            }
        }

        /// <summary>
        /// 游戏是否结束
        /// </summary>
        public bool IsOver()
        {
            if (m_emptyLocations.Count > 0) return false;


            for (int r = 0; r < SIZE; r++)
            {
                for (int c = 0; c < SIZE - 1; c++)
                {
                    if (m_data[r, c] == m_data[r, c + 1] || m_data[c, r] == m_data[c + 1, r])
                        return false;
                }
            }

            return true; //游戏结束 
        }
    }
}