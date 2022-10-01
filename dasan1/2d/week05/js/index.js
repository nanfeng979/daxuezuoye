let canvasWidth = 600 // 屏幕的宽度
let canvasHeight = 600 // 屏幕的高度

var config = {
    type: Phaser.AUTO,
    width: canvasWidth,
    height: canvasHeight,
    parent: "frame", // 将整个屏幕放在id=frame的DOM节点内
    backgroundColor: "#003412",
    scene: {
        preload: preload,
        create: create,
        update: update
    }
};

var game = new Phaser.Game(config);

function preload ()
{
    
}

function create ()
{

    pen = this.add.graphics()
    colors = [0xfe0000, 0xfda128, 0xfcff00, 0xade702, 0x00e1fd, 0x278dff, 0xb628fe, 0xfb28dc, 0x8424e1]
    drawAll(300, 400)
    // pen.generateTexture('tree', 600, 600);
    // pen.destroy(true);
    // this.input.on("pointerdown", (pointer) => {
    //     let tree = this.add.image(pointer.x, pointer.y, 'tree');
    //     tree.setTint(Phaser.Math.RND.pick(colors));
    //     tree.angle = Phaser.Math.RND.between(-20, 21);
    // })
    
}

function update ()
{
}


// 自定义函数

function get_angle(n) {
    return n * Math.PI / 180
}

function drawTree(x_positon, y_positon, distance, init_angle, angle, deep) {
    if(deep == 0) {
        return
    }
    
    pen.lineTo(x_positon, y_positon)
    distance *= 0.9
    
    let x_positon_new = x_positon - Math.cos(get_angle(init_angle)) * distance
    let y_positon_new = y_positon - Math.sin(get_angle(init_angle)) * distance

    // pen.moveTo(x_positon, y_positon)
    drawTree(x_positon_new, y_positon_new, distance, init_angle, angle, deep - 1)

    pen.moveTo(x_positon, y_positon)
    drawTree(x_positon_new, y_positon_new, distance, init_angle - angle, angle, deep - 1)

    pen.moveTo(x_positon, y_positon)
    drawTree(x_positon_new, y_positon_new, distance, init_angle + angle, angle, deep - 1)

}

function drawAll(x, y) {
    
    pen.lineStyle(2, 0xffffff, 1)
    pen.beginPath()

    pen.moveTo(x, y)
    drawTree(x, y, 70, Phaser.Math.RND.between(70, 110), 25, 8)

    pen.closePath()
    pen.strokePath()
}