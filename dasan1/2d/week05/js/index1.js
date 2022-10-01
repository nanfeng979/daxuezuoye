let canvasWidth = 600 // 屏幕的宽度
let canvasHeight = 600 // 屏幕的高度
let test
zhengfu = true
pointer1 = 0



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
    distance = 60

    // pen.lineStyle(1, 0xff0000, 1.0);
    // pen.fillStyle(0xFFFFFF, 1.0);
    // pen.fillRect(50, 50, 400, 200);
    // pen.strokeRect(50, 50, 400, 200);


    this.input.on("pointerdown", (pointer) => {
        pointer1 = pointer
        // pen = this.add.graphics().setVisible(false);
        pen.lineStyle(2, 0xffffff, 1)
        pen.beginPath()

        pen.moveTo(pointer.x, pointer.y)

        // let distance_angle = Phaser.Math.RND.between(-45, 45)
        distance_angle = 70
        dis_angle = 20 // 倾斜的角度
        deep = 5 // 延伸的深度
        x_positon_new = pointer.x // 树的起始点x位置
        y_positon_new = pointer.y // 树的起始点y位置


        



        // x_positon_new1 = x_positon_new - Math.cos(get_angle(distance_angle - dis_angle * 0)) * distance
        // y_positon_new1 = y_positon_new - Math.sin(get_angle(distance_angle - dis_angle * 0)) * distance
        // pen.lineTo(x_positon_new1, y_positon_new1)

        // x_positon_new2 = x_positon_new - Math.cos(get_angle(distance_angle + dis_angle * 0)) * distance
        // y_positon_new2 = y_positon_new - Math.sin(get_angle(distance_angle + dis_angle * 0)) * distance
        // pen.lineTo(x_positon_new2, y_positon_new2)
        
        // x_positon_new1 -= Math.cos(get_angle(distance_angle - dis_angle * 1)) * distance
        // y_positon_new1 -= Math.sin(get_angle(distance_angle - dis_angle * 1)) * distance
        // pen.lineTo(x_positon_new1, y_positon_new1)
        // // 返回上一个点
        // pen.lineTo(x_positon_new - Math.cos(get_angle(distance_angle - dis_angle * 0)) * distance, y_positon_new - Math.sin(get_angle(distance_angle - dis_angle * 0)) * distance)
        // x_positon_new2 -= Math.cos(get_angle(distance_angle + dis_angle * 1)) * distance
        // y_positon_new2 -= Math.sin(get_angle(distance_angle + dis_angle * 1)) * distance
        // pen.lineTo(x_positon_new2, y_positon_new2)

        // x_positon_new -= Math.cos(get_angle(distance_angle - dis_angle * 0)) * distance
        // y_positon_new -= Math.sin(get_angle(distance_angle - dis_angle * 0)) * distance
        // pen.lineTo(x_positon_new, y_positon_new)

        // x_positon_new -= Math.cos(get_angle(distance_angle - dis_angle * 1)) * distance
        // y_positon_new -= Math.sin(get_angle(distance_angle - dis_angle * 1)) * distance
        // pen.lineTo(x_positon_new, y_positon_new)


        // x_positon_new -= Math.cos(get_angle(distance_angle - dis_angle * 2)) * distance
        // y_positon_new -= Math.sin(get_angle(distance_angle - dis_angle * 2)) * distance
        // pen.lineTo(x_positon_new, y_positon_new)

        // x_positon_new -= Math.cos(get_angle(distance_angle - dis_angle * 3)) * distance
        // y_positon_new -= Math.sin(get_angle(distance_angle - dis_angle * 3)) * distance
        // pen.lineTo(x_positon_new, y_positon_new)




        x_positon_new1 = pointer.x - Math.cos(get_angle(distance_angle - dis_angle * 0)) * distance
        y_positon_new1 = pointer.y - Math.sin(get_angle(distance_angle - dis_angle * 0)) * distance
        drawTree(1, x_positon_new1, y_positon_new1)

        
        // pen.closePath()
        pen.strokePath()
        // console.log()
        
    })

}

function update ()
{
    

    
}


// 自定义函数

function get_angle(n) {
    return n * Math.PI / 180
}


function drawTree(deep1, x_positon, y_positon) {

    if(deep1 == 6) {
        return
    }
    
    pen.lineTo(x_positon, y_positon)
    
 
    // x_positon_new -= Math.cos(get_angle(distance_angle + dis_angle * (deep1))) * distance
    // y_positon_new -= Math.sin(get_angle(distance_angle + dis_angle * (deep1))) * distance
    var x_positon_left = x_positon - Math.cos(get_angle(distance_angle - dis_angle * (deep1))) * distance
    var y_positon_left = y_positon - Math.sin(get_angle(distance_angle - dis_angle * (deep1))) * distance
    pen.moveTo(x_positon, y_positon)
    drawTree(deep1 + 1, x_positon_left, y_positon_left)
    

    var x_positon_center = x_positon - Math.cos(get_angle(distance_angle)) * distance
    var y_positon_center = y_positon - Math.sin(get_angle(distance_angle)) * distance
    pen.moveTo(x_positon, y_positon)
    drawTree(deep1 + 1, x_positon_center, y_positon_center)

    var x_positon_right = x_positon - Math.cos(get_angle(distance_angle + dis_angle * (deep1))) * distance
    var y_positon_right = y_positon - Math.sin(get_angle(distance_angle + dis_angle * (deep1))) * distance
    pen.moveTo(x_positon, y_positon)
    drawTree(deep1 + 1, x_positon_right, y_positon_right)
    


    // drawTree(deep1 - 1, x, y)

        

}