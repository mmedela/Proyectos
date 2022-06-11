const gravity = 0.7;
class Sprite{
    constructor({position, velocity, color = 'red'}){
        this.position = position;
        this.velocity = velocity;
        this.height = 150;
        this.lastKeyPressed;
        this.attackBox = {
            position: this.position,
            width: 100,
            height: 50
        }
        this.color = color;
    }

    draw(canvasContext){
        canvasContext.fillStyle = this.color;
        canvasContext.fillRect(this.position.x, this.position.y, 50, this.height);
        //Attack Box//
        canvasContext.fillStyle = 'green';
        canvasContext.fillRect(
            this.attackBox.position.x, 
            this.attackBox.position.y, 
            this.attackBox.width, 
            this.attackBox.height
        );
    }

    update(canvasContext, height){
        this.draw(canvasContext);
        this.position.y += this.velocity.y;
        this.position.x += this.velocity.x;
        if(this.position.y + this.height + this.velocity.y >= height){
            this.velocity.y = 0;
        }else{
            this.velocity.y += gravity;
        }
    }
}

export default Sprite;