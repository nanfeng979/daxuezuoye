
export class GameScene extends Phaser.Scene {
  //private lines: Phaser.GameObjects.Graphics[] = [];
  private graphics!: Phaser.GameObjects.Graphics;
  private kD2R: number = Phaser.Math.DEG_TO_RAD;//Math.PI / 180;
  private depth: number = 10;
  private lineLength: number = 5;
  constructor() {
    super({
      key: 'GameScene'
    });
  }

  init(): void {

  }
  create(): void {
    let tree_color = [0xfe0000, 0xfda128, 0xfcff00, 0xade702, 0x00e1fd, 0x278dff, 0xb628fe, 0xfb28dc, 0x8424e1]
    let random_color_index = Math.floor(Math.random() * tree_color.length)
    let random_color = tree_color[random_color_index]

    this.graphics = this.add.graphics().setVisible(false);
    this.graphics.lineStyle(5, 0xFF00FF, 1.0);
    this.graphics.beginPath();
    this.graphics.moveTo(10, 10);
    this.graphics.lineTo(20, 20);
    this.graphics.generateTexture('tree', 500, 400);
    this.graphics.closePath();
    this.graphics.strokePath();

    
    this.input.on("pointerdown", (pointer) => {
      let tree = this.add.image(pointer.x, pointer.y, 'tree');
      tree.setTint(Phaser.Math.RND.pick(tree_color));
      tree.angle = Phaser.Math.RND.between(-20, 21);

      


      console.log(1)
    })
  }

  
}