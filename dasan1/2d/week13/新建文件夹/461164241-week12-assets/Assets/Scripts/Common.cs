namespace MyGame_2048
{
   public enum MoveDirection
    {
        //******定义值*******
        Up,
        Down,
        Left,
        Right
    }

   public struct Location
    {
        /// <summary>
        /// 行索引
        /// </summary>
        public int RowIndex { get; set; }

        /// <summary>
        /// 列索引
        /// </summary>
        public int ColIndex { get; set; }

        public Location(int r, int c)
        {
            this.RowIndex = r;
            this.ColIndex = c;
        }
        public override string ToString()
        {
            return string.Format("({0},{1})", this.RowIndex, this.ColIndex);
        }
    }
}